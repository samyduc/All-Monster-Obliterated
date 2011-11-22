
///=============================================================================
///
/// \file           WorldMap.hpp
/// \class          WorldMap
///
/// \date           Creation date:  31/12/2009
/// \date           Latest update:  31/12/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief
///
///=============================================================================

// Include guard
#ifndef WORLDMAP_HPP_INCLUDED
#define WORLDMAP_HPP_INCLUDED
//-----------------------------------------------------------------------------/

// Dependancies
#include <string>
#include <list>
#include "Triplet.hpp"
//-----------------------------------------------------------------------------/

class WorldMap
{
// Methods
public:
    WorldMap();
    virtual ~WorldMap() {}

    bool update();

    void addEntity(int id, const Triplet_f& pos);
    void removeEntity(int id);

// Methods
protected:
    bool updatePlayer(int id);

// Properties
protected:
    std::list<int> m_playerIdList;

}; // WorldMap

#endif // WORLDMAP_HPP_INCLUDED


