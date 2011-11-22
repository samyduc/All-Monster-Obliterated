
///=============================================================================
///
/// \file           CNetwork.hpp
/// \class          CNetwork
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

// Include guard
#ifndef CNETWORK_HPP_INCLUDED
#define CNETWORK_HPP_INCLUDED
//-----------------------------------------------------------------------------/

// Mother classes
#include "INetwork.hpp"
#include "IModule.hpp"
#include "Singleton.hpp"
//-----------------------------------------------------------------------------/

// Dependancies
#include <RakNet/RakPeerInterface.h>
#include <boost/timer.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/bimap.hpp>
//-----------------------------------------------------------------------------/

class CNetwork : public INetwork, public IModule, public Singleton<CNetwork>
{
    friend class Singleton<CNetwork>;

// Enumerations
public:
    enum PACKET_ID
    {
        ID_PLAYER_CONTROL = 106,
        ID_MAP_NAME = 107,
        ID_ENTITY_POS = 108,
        ID_CLIENT_ID = 109,
        ID_SHOT_FIRED = 110,
        ID_SHOT_RESULT = 111,
        ID_CHAT_MESSAGE = 112,
        ID_ENTITY_INFO = 113,
        ID_PLAYER_NEED_INFO = 114,
        REGISTRATION_PLAYER = 115,
        REGISTRATION_SUCCESSFULL = 116,
        REGISTRATION_FAIL = 117,
        CONNECT_PLAYER = 118,
        CONNECT_PLAYER_OK = 119,
        CONNECT_PLAYER_KO = 120,
        ID_REMOVE_ENTITY = 121,
        ID_PLAYER_NOT_PLAY = 122,
        ID_LEAVE_MAP = 123,
        ID_ENTER_MAP = 124
    };

// Methods (IModule)
public:

    void init(const std::string& path);
    bool update();
    void destroy();

    const std::string& name() const;

    void addEntity(int id, int map, const std::string& type);
    void removeEntity(int id, int map);

// Methods (INetwork)
public:
    void listen();

    void sleep(int ms);

    void sendShotFired(int source, int target, const Triplet_f& impact);
    void sendChatMessage(const std::string& mes);

    void disconnectPlayer(int id);
    void setTickRate(float tick);

    int getTick();

// Methods
protected:
    virtual ~CNetwork() {}

    void handlePacket(Packet* p);
    void handlePlayerConnection(Packet* p);
    void handlePlayerDisconnection(Packet* p);
    void handleRegistrationNewPlayer(Packet* p);
    void handlePlayerControl(Packet* p);
    void handleShotFired(Packet* p);
    void handleChatMessage(Packet* p);
    void handlePlayerLeaveMap(Packet* p);
    void handlePlayerNeedInfo(Packet* p);

    void sendToAllInMap(int map, const RakNet::BitStream& bs);
    void sendChatCommand(const std::string& mes, SystemAddress p);
    void sendRemovePlayer(int id);

    bool isPlayerConnected(int id);

// Properties
protected:
    bool m_continue;
    RakPeerInterface* m_peer;
    unsigned short m_listenPort;
    boost::bimap<SystemAddress, int> m_clientMap;

    boost::scoped_ptr<boost::timer> m_readTimer;
    float m_tick_rate;
    int m_tick;
    int m_tick_max;
}; // CNetwork

#endif // CNETWORK_HPP_INCLUDED


