
///=============================================================================
///
/// \file           CKernel.cpp
///
/// \date           Creation date:  09/08/2008
/// \date           Latest update:  08/08/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          Static class that manages all the modules
///
///=============================================================================

// Header of the class
#include "CKernel.hpp"
//-----------------------------------------------------------------------------/

// Dependancies
#include <iostream>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include "FPSManager.hpp"
#include "CData.hpp"
#include "CDataBase.hpp"
#include "CNetwork.hpp"
#include "CPhysic.hpp"
#include "CLog.hpp"
#include "CAdmin.hpp"
//-----------------------------------------------------------------------------/

std::vector<IModule*> CKernel::m_moduleVect;

void CKernel::init(const std::string& path)
{
    //CLog must be the first initialized module
    m_moduleVect.push_back(CLog::getInstance());
    m_moduleVect.push_back(CData::getInstance());
    m_moduleVect.push_back(CDataBase::getInstance());
    m_moduleVect.push_back(CNetwork::getInstance());
    m_moduleVect.push_back(CPhysic::getInstance());
    m_moduleVect.push_back(CAdmin::getInstance());

    BOOST_FOREACH(IModule* m, m_moduleVect)
    {
        m->init(path);
    }

    network()->listen();
    physic()->loadMap(1, data()->getMapName());
    //data()->addGameObject("player_light", "Bot 1", Triplet_f(0, 5, 0));
    int id = uniqueID();
    addEntity(id, 1, "player_light");
    physic()->moveEntity(id, 1, Triplet_f(5, 5, 0));
    data()->nameEntity(id, 1, "root_bot");
}

bool CKernel::update()
{
    static bool running = true;
    static FPSManager fps(100);

    fps.startFrame();

    BOOST_FOREACH(IModule* m, m_moduleVect)
    {
        running &= m->update();
    }

    fps.endFrame();

    return (running);
}

void CKernel::addEntity(int id, int map, const std::string& type)
{
    std::cout << "adding entity..." << std::endl;
    BOOST_FOREACH(IModule* m, m_moduleVect)
    {
        m->addEntity(id, map, type);
    }
    std::cout << "entity added" << std::endl;
}

void CKernel::removeEntity(int id, int map)
{
    std::cout << "removing entity..." << std::endl;
    BOOST_FOREACH(IModule* m, m_moduleVect)
    {
        m->removeEntity(id, map);
    }
    std::cout << "entity removed" << std::endl;
}

void CKernel::destroy()
{
    BOOST_REVERSE_FOREACH(IModule* m, m_moduleVect)
    {
        m->destroy();
    }
}

int CKernel::uniqueID()
{
 // TODO (Benjamin#1#): find why 0 crash on first client connection
    static int id = 10000;
    return (++id);
}

IData* CKernel::data()
{
    return (CData::getInstance());
}

IDataBase* CKernel::database()
{
    return (CDataBase::getInstance());
}


INetwork* CKernel::network()
{
    return (CNetwork::getInstance());
}

IPhysic* CKernel::physic()
{
    return (CPhysic::getInstance());
}

ILog* CKernel::log()
{
    return (CLog::getInstance());
}

IAdmin* CKernel::admin()
{
    return (CAdmin::getInstance());
}
