
///=============================================================================
///
/// \file           CPhysic.cpp
///
/// \date           Creation date:  09/08/2008
/// \date           Latest update:  08/08/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          An implementation of the Physic module, using Newton.
///
///=============================================================================

// Header of the class
#include "CPhysic.hpp"
//-----------------------------------------------------------------------------/

// Dependancies
#include <iostream>
#include <boost/foreach.hpp>
#include "PhysicMap.hpp"
#include "WorldMap.hpp"
#include "CKernel.hpp"
#include "ILog.hpp"
//-----------------------------------------------------------------------------/

void CPhysic::init(const std::string& path)
{
    m_worldMap = new WorldMap();
    m_mapContainer.insert(MapContainer::value_type(1, new PhysicMap()));
	CKernel::log()->addLog(this, "CPhysic::init done");
}

bool CPhysic::update()
{
    bool retVal = m_worldMap->update();
    BOOST_FOREACH(MapContainer::value_type mapPair, m_mapContainer)
    {
        retVal |= mapPair.second->update();
    }
    return (retVal);
}

void CPhysic::destroy()
{
    delete (m_worldMap);
    //TODO(#3#) delete all the Maps and empty the std::map
    /*BOOST_FOREACH(MapContainer::value_type mapPair, m_mapContainer)
    {
        delete (mapPair.second);
        m_mapContainer.erase(mapPair);
    }*/
    CKernel::log()->addLog(this, "CPhysic::destroy done");
}

const std::string& CPhysic::name() const
{
    static std::string str("physic");
    return (str);
}

void CPhysic::loadMap(int mapID, const std::string& name)
{
    m_mapContainer[mapID]->loadMap(name);
    CKernel::log()->addLog(this, "CPhysic::loadMap " + name);
}

void CPhysic::addEntity(int id, int map, const std::string& type)
{
    m_mapContainer[map]->addEntity(id, type);
}

void CPhysic::removeEntity(int id, int map)
{
    m_mapContainer[map]->removeEntity(id);
}

void CPhysic::moveEntity(int id, int map, const Triplet_f& pos)
{
    m_mapContainer[map]->moveEntity(id, pos);
}

// TODO (#2#): line too long
void CPhysic::rayCast(int mapID, int source, const Triplet_f& start, const Triplet_f& end)
{
    m_mapContainer[mapID]->rayCast(source, start, end);
}


