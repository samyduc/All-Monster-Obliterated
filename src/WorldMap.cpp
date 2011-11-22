
///=============================================================================
///
/// \file           WorldMap.cpp
///
/// \date           Creation date:  30/12/2009
/// \date           Latest update:  30/12/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief
///
///=============================================================================

// Header of the class
#include "WorldMap.hpp"
//-----------------------------------------------------------------------------/

// Dependancies
#include <boost/foreach.hpp>
#include "CKernel.hpp"
#include "IData.hpp"
#include "CompLocation.hpp"
//-----------------------------------------------------------------------------/

WorldMap::WorldMap()
{

}

bool WorldMap::update()
{
    BOOST_FOREACH(int id, m_playerIdList)
    {
        updatePlayer(id);
    }
    return (true);
}

bool WorldMap::updatePlayer(int id)
{
    CompLocation* loc = CKernel::data()->getGameObjectLocation(id);
    Triplet_f newPos = loc->position() + loc->desiredVel();
    loc->setPosition(newPos);
    return (true);
}

void addEntity(int id, const Triplet_f& pos)
{

}

void removeEntity(int id)
{

}


