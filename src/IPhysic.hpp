
///=============================================================================
///
/// \file           IPhysic.hpp
/// \class          IPhysic
///
/// \date           Creation date:  03/01/2009
/// \date           Latest update:  08/08/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          An interface for the Physic module.
///
///=============================================================================

// Include guard
#ifndef IPHYSIC_HPP_INCLUDED
#define IPHYSIC_HPP_INCLUDED
//-----------------------------------------------------------------------------/

// Dependancies
#include <string>
#include "Triplet.hpp"
//-----------------------------------------------------------------------------/

class IPhysic
{
// Methods
public:
    virtual void loadMap(int mapID, const std::string& name) = 0;
    virtual void moveEntity(int id, int map, const Triplet_f& pos) = 0;

// TODO (#2#): line too long
    virtual void rayCast(int mapID, int source, const Triplet_f& start, const Triplet_f& end) = 0;
}; // IPhysic

#endif // IPHYSIC_HPP_INCLUDED


