
///=============================================================================
///
/// \file           CNetwork.cpp
///
/// \date           Creation date:  09/08/2008
/// \date           Latest update:  08/08/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          An implementation of the Network module, using raknet.
///
///=============================================================================

// Header of the class
#include "CNetwork.hpp"
//-----------------------------------------------------------------------------/

// Dependancies
#include <iostream>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <RakNet/RakNetworkFactory.h>
#include <RakNet/BitStream.h>
#include <RakNet/MessageIdentifiers.h>
#include <RakNet/RakSleep.h>
#include <RakNet/StringCompressor.h>
#include "CKernel.hpp"
#include "ILog.hpp"
#include "IData.hpp"
#include "IDataBase.hpp"
#include "IPhysic.hpp"
#include "IAdmin.hpp"
#include "CompLocation.hpp"
#include "CompInfo.hpp"
//-----------------------------------------------------------------------------/
#define TICK_DEFAULT 0.05
#define TICK_MAX_DEFAULT 100000
#define MSG_ADMIN '+'
//-----------------------------------------------------------------------------/

void CNetwork::init(const std::string& path)
{
    m_readTimer.reset(new boost::timer());
    m_peer = RakNetworkFactory::GetRakPeerInterface();
    m_peer->SetIncomingPassword("azerty", (int)strlen("azerty"));
    m_listenPort = 4400;
    m_readTimer->restart();
    m_tick_rate = TICK_DEFAULT;
    m_tick = 0;
    m_tick_max = TICK_MAX_DEFAULT;
    CKernel::log()->addLog(this, "CNetwork::init done");
}

bool CNetwork::update()
{
    Packet *packet = m_peer->Receive();
    while(packet)
    {
        handlePacket(packet);
        m_peer->DeallocatePacket(packet);
        packet = m_peer->Receive();
    }

    if (m_readTimer->elapsed() > m_tick_rate)
    {
        RakNet::BitStream bs;
        typedef std::map<int, CompLocation*> LocationMap;
        BOOST_FOREACH(LocationMap::value_type value, CKernel::data()->getAllLocation())
        {
            //TODO(#2#) BE SURE ABOUT NETWORK PERFORMANCE
            if(value.second->getTick() == m_tick)
            {
                bs.Reset();
                bs.Write((MessageID)ID_ENTITY_POS);
                bs.Write(value.first);
                bs.Write(value.second->position());
                bs.Write(value.second->direction());
                bs.Write(value.second->velocity());
                CompInfo* info = CKernel::data()->getGameObjectInfo(value.first);
                if (info)
                {
                    sendToAllInMap(info->map(), bs);
                }
            }
        }

        m_readTimer->restart();
        if(m_tick >= m_tick_max) m_tick = 0;
        else ++m_tick;
    }

    return (true);
}

int CNetwork::getTick()
{
    return m_tick;
}

void CNetwork::destroy()
{
    m_peer->Shutdown(300);
    RakNetworkFactory::DestroyRakPeerInterface(m_peer);
    CKernel::log()->addLog(this, "CNetwork::destroy done");
}

const std::string& CNetwork::name() const
{
    static std::string str("network");
    return (str);
}

void CNetwork::addEntity(int id, int map, const std::string& type)
{

}

void CNetwork::removeEntity(int id, int map)
{

}

void CNetwork::handlePacket(Packet *p)
{
    RakNet::BitStream dataStream(p->data, p->length, false);

    unsigned char packetID;
    dataStream.Read(packetID);

    switch (packetID)
    {
        case ID_NEW_INCOMING_CONNECTION:
            CKernel::log()->addLog(this, "CNetwork::handlePacket connection incoming : "
                                   + std::string(p->systemAddress.ToString()));
            break;

        case ID_CONNECTION_LOST:
        case ID_DISCONNECTION_NOTIFICATION:
            handlePlayerDisconnection(p);
            break;
        case CONNECT_PLAYER:
            handlePlayerConnection(p);
            break;

        case ID_PLAYER_CONTROL:
            handlePlayerControl(p);
            break;

        case ID_SHOT_FIRED:
            handleShotFired(p);
            break;

        case ID_CHAT_MESSAGE:
            handleChatMessage(p);
            break;

        case ID_PLAYER_NEED_INFO:
            handlePlayerNeedInfo(p);
            break;

        case REGISTRATION_PLAYER:
            handleRegistrationNewPlayer(p);
            break;

        case ID_LEAVE_MAP:
            handlePlayerLeaveMap(p);
            break;

        default:
            CKernel::log()->addLog(this, "CNetwork::handlePacket unknow packet : "
                                   + boost::lexical_cast<std::string>(packetID)
                                   + std::string(" ") + std::string(p->systemAddress.ToString()));
            break;
    }
}

void CNetwork::handleRegistrationNewPlayer(Packet* p)
{
    RakNet::BitStream dataStream(p->data, p->length, false);
    MessageID packetID;
    std::string pseudo;
    std::string password;
    std::string type;

    dataStream.Read(packetID);
    stringCompressor->DecodeString(&pseudo, 50, &dataStream);
    stringCompressor->DecodeString(&password, 50, &dataStream);
    stringCompressor->DecodeString(&type, 50, &dataStream);

    //TODO(#2#)Replace when client side type is done
    if(type == "") type = "player_medium";

    RakNet::BitStream bs;
    if(CKernel::database()->isPlayerExist(pseudo))
    {
        bs.Write((MessageID)REGISTRATION_FAIL);
        stringCompressor->EncodeString("Player already Exists", 50, &bs);
        CKernel::log()->addLog(this, "CNetwork::handleRegistrationNewPlayer Player already Exists "
                                   + pseudo + std::string(" ") + std::string(p->systemAddress.ToString()));
    }
    else
    {
        if(CKernel::database()->addNewPlayer(pseudo, password, type) >= 0)
        {
            bs.Write((MessageID)REGISTRATION_SUCCESSFULL);
            stringCompressor->EncodeString("", 50, &bs);
            CKernel::log()->addLog(this, "CNetwork::handleRegistrationNewPlayer Player Register "
                                   + pseudo + std::string(" ") + std::string(p->systemAddress.ToString()));
        }
        else
        {
            bs.Write((MessageID)REGISTRATION_FAIL);
            stringCompressor->EncodeString("CDataBase->addNewPlayer", 50, &bs);
            CKernel::log()->addLog(this, "CNetwork::handleRegistrationNewPlayer Player Registration fail "
                                   + pseudo + std::string(" ") + std::string(p->systemAddress.ToString()));
        }
    }
    m_peer->Send(&bs, LOW_PRIORITY, RELIABLE_ORDERED, 0, p->systemAddress, false);
}

void CNetwork::handlePlayerConnection(Packet* p)
{
    RakNet::BitStream dataStream(p->data, p->length, false);
    MessageID packetID;
    std::string pseudo;
    std::string password;
    std::string type;
    int id;

    dataStream.Read(packetID);
    stringCompressor->DecodeString(&pseudo, 50, &dataStream);
    stringCompressor->DecodeString(&password, 50, &dataStream);

    CKernel::log()->addLog(this, "CNetwork::handleNewPlayer player incoming "
                            + pseudo + std::string(" ") + std::string(p->systemAddress.ToString()));

    RakNet::BitStream bs;

    if(CKernel::database()->isPasswordMatch(pseudo, password, id, type))
    {
        if(isPlayerConnected(id)) return;
        bs.Write((MessageID)CONNECT_PLAYER);
        stringCompressor->EncodeString(CKernel::data()->getMapName(), 50, &bs);
        bs.Write(id);
        stringCompressor->EncodeString(type, 50, &bs);

        CKernel::addEntity(id, 1, type);
        CKernel::physic()->moveEntity(id, 1, Triplet_f(0, 5, 0));
        CKernel::data()->nameEntity(id, 1, pseudo);
        m_clientMap.insert(boost::bimap<SystemAddress, int>::value_type(p->systemAddress, id));

        m_peer->Send(&bs, LOW_PRIORITY, RELIABLE_ORDERED, 0, p->systemAddress, false);
    }
}

void CNetwork::handlePlayerDisconnection(Packet* p)
{
    boost::bimap<SystemAddress, int>::left_iterator it;
    it = m_clientMap.left.find(p->systemAddress);

    if(it != m_clientMap.left.end())
    {
        int id = it->second;
        CKernel::removeEntity(it->second, 1);
        sendRemovePlayer(id);
        m_clientMap.left.erase(it);

        CKernel::log()->addLog(this, "CNetwork::handlePacket player leaving : "
                                   + std::string(p->systemAddress.ToString()));
    }
}

bool CNetwork::isPlayerConnected(int id)
{
    bool toReturn = false;
    boost::bimap<SystemAddress, int>::right_iterator it;
    it = m_clientMap.right.find(id);

    if(it != m_clientMap.right.end())
    {
        toReturn = true;
        CKernel::log()->addLog(this, "CNetwork::isPlayerConnected player already connected : "
                                   + boost::lexical_cast<std::string>(id));
    }
    return toReturn;
}

void CNetwork::disconnectPlayer(int id)
{
    boost::bimap<SystemAddress, int>::right_iterator it;

    it = m_clientMap.right.find(id);

    if(it != m_clientMap.right.end())
    {
            SystemAddress addr = it->second;
            m_peer->CloseConnection(addr, true, 0, LOW_PRIORITY);
            CKernel::log()->addLog(this, "CNetwork::disconnectPlayer player leaving : "
                                   + std::string(addr.ToString()));
    }
}

void CNetwork::handlePlayerNeedInfo(Packet* p)
{
    RakNet::BitStream dataStream(p->data, p->length, false);
    unsigned char packetID;
    int id;
    dataStream.Read(packetID);
    dataStream.Read(id);

    RakNet::BitStream bs;
    CompInfo* info = CKernel::data()->getGameObjectInfo(id);
    bs.Write((MessageID)ID_ENTITY_INFO);
    bs.Write(id);
    stringCompressor->EncodeString(info->type(), 50, &bs);
    stringCompressor->EncodeString(info->name(), 50, &bs);
    m_peer->Send(&bs, LOW_PRIORITY, RELIABLE_ORDERED, 0, p->systemAddress, false);
}

void CNetwork::handlePlayerControl(Packet* p)
{
    RakNet::BitStream dataStream(p->data, p->length, false);

    unsigned char packetID;
    int id;
    Triplet_f vel;
    float angle;
    dataStream.Read(packetID);
    dataStream.Read(id);
    dataStream.Read(vel);
    dataStream.Read(angle);

    CompLocation* loc = CKernel::data()->getGameObjectLocation(id);
    if (loc)
    {
        loc->setDesiredVel(vel);
        loc->setDesiredAngle(angle);
    }
}

void CNetwork::handleShotFired(Packet* p)
{
    RakNet::BitStream dataStream(p->data, p->length, false);

    unsigned char packetID;
    int shooterID;
    Triplet_f start, end;
    dataStream.Read(packetID);
    dataStream.Read(shooterID);
    dataStream.Read(start);
    dataStream.Read(end);

    CKernel::physic()->rayCast(1, shooterID, start, end);
}

void CNetwork::handleChatMessage(Packet* p)
{
    RakNet::BitStream dataStream(p->data, p->length, false);

    unsigned char packetID;
    std::string mes;
    std::string command ;
    dataStream.Read(packetID);
    stringCompressor->DecodeString(&mes, 50, &dataStream);

    command = mes.substr(mes.find_first_of(":")+2, mes.size());

    if(command.empty()) return (void)0;

    switch(command[0])
    {
        case MSG_ADMIN:
            CKernel::admin()->handleAdminCommand(m_clientMap.left.at(p->systemAddress),
                                                  command.substr(1, command.size()));
            sendChatCommand(mes, p->systemAddress);
            break;
        default:
            sendChatMessage(mes);
            break;
    }
}

void CNetwork::handlePlayerLeaveMap(Packet* p)
{
    std::cout << "player leaving map" << std::endl;

    boost::bimap<SystemAddress, int>::left_iterator it;
    it = m_clientMap.left.find(p->systemAddress);

    if(it != m_clientMap.left.end())
    {
        int id = it->second;
        CompLocation* loc = CKernel::data()->getGameObjectLocation(id);
        if (loc && loc->position().y < 0)
        {
            disconnectPlayer(id);
            RakNet::BitStream bs;
            bs.Write((MessageID)ID_LEAVE_MAP);
            m_peer->Send(&bs, LOW_PRIORITY, RELIABLE_ORDERED, 0, p->systemAddress, false);
        }
    }
}

void CNetwork::sendToAllInMap(int map, const RakNet::BitStream& bs)
{
    boost::bimap<SystemAddress, int>::iterator it;
    for (it = m_clientMap.begin(); it != m_clientMap.end(); ++it)
    {
        CompInfo* info = CKernel::data()->getGameObjectInfo(it->right);
        if (info && info->map() == map)
        {
            m_peer->Send(&bs, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, it->left, false);
        }
    }
}

void CNetwork::listen()
{
    SocketDescriptor socketDescriptor(m_listenPort,"");
	m_peer->Startup(32, 30, &socketDescriptor, 1);
	m_peer->SetMaximumIncomingConnections(20);
	CKernel::log()->addLog(this, "CNetwork::listen port "
                            + boost::lexical_cast<std::string>(m_listenPort));
}

void CNetwork::sleep(int ms)
{
    if (ms > 2)
    {
        RakSleep(ms);
    }
}

void CNetwork::sendShotFired(int source, int target, const Triplet_f& impact)
{
    RakNet::BitStream bs;
    bs.Write((MessageID)ID_SHOT_RESULT);
    bs.Write(source);
    bs.Write(target);
    bs.Write(impact);

    sendToAllInMap(1, bs);
}

void CNetwork::sendChatCommand(const std::string& mes, SystemAddress p)
{
    RakNet::BitStream bs;
    bs.Write((MessageID)ID_CHAT_MESSAGE);
    stringCompressor->EncodeString(mes, 50, &bs);

    m_peer->Send(&bs, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, p, false);
}

void CNetwork::sendChatMessage(const std::string& mes)
{
    RakNet::BitStream bs;
    bs.Write((MessageID)ID_CHAT_MESSAGE);
    stringCompressor->EncodeString(mes, 50, &bs);

    sendToAllInMap(1, bs);
}

void CNetwork::sendRemovePlayer(int id)
{
    RakNet::BitStream bs;

    bs.Write((MessageID)ID_REMOVE_ENTITY);
    bs.Write(id);
    sendToAllInMap(1, bs);
}

void CNetwork::setTickRate(float tick)
{
    if(tick <= 0)
    {
        m_tick_rate = TICK_DEFAULT;
    }
    else
    {
        m_tick_rate = tick;
    }
    CKernel::log()->addLog(this, "CNetwork::setTickRate change to "
                           + boost::lexical_cast<std::string>(m_tick_rate));
}


