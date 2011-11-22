//=============================================================================
///
/// \file           CAdmin.cpp
/// \class          CAdmin
///
/// \date           Creation date:  08/01/2010
/// \date           Latest update:  08/01/2010
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          An implementation of the Admin module.
///
///=============================================================================

// Header of the class
#include "CAdmin.hpp"
//-----------------------------------------------------------------------------/

// Dependancies
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include "CKernel.hpp"
#include "ILog.hpp"
#include "IPhysic.hpp"
#include "IData.hpp"
#include "IDataBase.hpp"
#include "INetwork.hpp"
#include "CompLocation.hpp"
//-----------------------------------------------------------------------------/
#define KICK_PLAYER "kick" //+kick "id"
#define DB_INIT "db_init" //+db_init "path"
#define NET_TICK "net_tick"//+net_tick "f_value"
#define ADD_ITEM "add_item"//+add_item "id_item"
//-----------------------------------------------------------------------------/


void CAdmin::init(const std::string& path)
{
    m_commandMap[KICK_PLAYER] = &CAdmin::kickPlayer;
    m_commandMap[DB_INIT] = &CAdmin::dbInit;
    m_commandMap[NET_TICK] = &CAdmin::netTick;
    m_commandMap[ADD_ITEM] = &CAdmin::addItem;

    CKernel::log()->addLog(this, "CAdmin::init done");
}

bool CAdmin::update()
{
    return(true);
}

void CAdmin::destroy()
{
    CKernel::log()->addLog(this, "CAdmin::destroy done");
}

const std::string& CAdmin::name() const
{
    static std::string str("Admin");
    return (str);
}

void CAdmin::handleAdminCommand(int id_admin, std::string mes)
{
    std::vector<std::string> mes_vect;

    boost::split( mes_vect, mes, boost::is_any_of(": "));
    if(mes_vect.size() == 0) return;
    if(!isAdmin(id_admin)) return;
    std::string command = mes_vect[0];

    //put id_admin at the first index
    try
    {
        mes_vect[0] = boost::lexical_cast<std::string>(id_admin);
    }
    catch(boost::bad_lexical_cast &)
    {
        return;
    }
    std::map<std::string, void (CAdmin::*)(std::vector<std::string> &) >::iterator it;
    it = m_commandMap.find(command);

    if(it != m_commandMap.end())
        (this->*m_commandMap[command])(mes_vect);
}


void CAdmin::kickPlayer(std::vector<std::string> & arg)
{
    int id;
    if(arg.size() != 2 ) return;
    try
    {
        id = boost::lexical_cast<int>(static_cast<std::string>(arg[1]));
    }
    catch(boost::bad_lexical_cast &)
    {
        return;
    }

    CKernel::log()->addLog(this, "kickPlayer "
                        + boost::lexical_cast<std::string>(id));

    CKernel::network()->disconnectPlayer(id);
}

//TODO(#3#)Delete this function
void CAdmin::dbInit(std::vector<std::string> & arg)
{
    if(arg.size() != 2 ) return;

    CKernel::log()->addLog(this, "dbInit "
                        + arg[1]);

    //CKernel::database()->CreateEmptyTable(arg[1]);
}

void CAdmin::netTick(std::vector<std::string> & arg)
{
    if(arg.size() != 2 ) return;

    float tick;
    try
    {
        tick = boost::lexical_cast<float>(arg[1]);
    }
    catch(boost::bad_lexical_cast &)
    {
        return;
    }
    CKernel::network()->setTickRate(tick);
}

bool CAdmin::isAdmin(int id)
{
    bool toReturn = true;
    //std::string name = CKernel::data()->getGameObjectInfo(id)->name();
    //TODO(#2#)DataBase Verification of Admin right
    CKernel::log()->addLog(this, "CAdmin::isAdmin "
                           + boost::lexical_cast<std::string>(id));
    return toReturn;
}

void CAdmin::addItem(std::vector<std::string> & arg)
{
    if(arg.size() != 2) return;

    int id_admin;
    try
    {
        id_admin = boost::lexical_cast<int>(arg[0]);
    }
    catch(boost::bad_lexical_cast &)
    {
        return;
    }

    int id_item;
    try
    {
        id_item = boost::lexical_cast<int>(arg[1]);
    }
    catch(boost::bad_lexical_cast &)
    {
        return;
    }

    CKernel::log()->addLog(this, "CAdmin::addItem "
                           + boost::lexical_cast<std::string>(id_admin));

    CompLocation* location = CKernel::data()->getGameObjectLocation(id_admin);
    if(!location) return;
    // TODO (Benjamin#1#): use the CKernel::add instead (done)
    int id = 0;
    switch(id_item)
    {
        case WOOD_BOX:
            //CKernel::data()->addGameObject("crate", "", location->position() + Triplet_f(0, 10, 0));
            id = CKernel::uniqueID();
            CKernel::addEntity(id, 1, "crate");
            CKernel::physic()->moveEntity(id, 1, location->position() + Triplet_f(0, 10, 0));
            break;

        case CORPSE:
            //CKernel::data()->addGameObject("player_medium", "bot", location->position() + Triplet_f(0, 10, 0));
            id = CKernel::uniqueID();
            CKernel::addEntity(id, 1, "player_medium");
            CKernel::physic()->moveEntity(id, 1, location->position() + Triplet_f(0, 10, 0));
            CKernel::data()->nameEntity(id, 1, "admin_bot");
            break;

        default:
            break;
    }
}
