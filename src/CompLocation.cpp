
///=============================================================================
///
/// \file           CompLocation.cpp
///
/// \date           Creation date:  07/08/2009
/// \date           Latest update:  08/08/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          Represents the location of an object (position, orientation)
///
///=============================================================================

// Header of the class
#include "CompLocation.hpp"
//-----------------------------------------------------------------------------/

CompLocation::CompLocation(int id, const Triplet_f& pos, const Triplet_f& dir) :
    Component(id), m_position(pos), m_direction(dir)
{
    m_isImpact = false;
    m_desiredAngle = 0;
}

CompLocation::~CompLocation()
{

}

void CompLocation::setPosition(const Triplet_f& pos)
{
    setTick();
    m_position = pos;
}

const Triplet_f& CompLocation::position() const
{
    return (m_position);
}

void CompLocation::setDirection(const Triplet_f& dir)
{
    setTick();
    m_direction = dir;
}

const Triplet_f& CompLocation::direction() const
{
    return (m_direction);
}

void CompLocation::setVelocity(const Triplet_f& vel)
{
    m_velocity = vel;
}

const Triplet_f& CompLocation::velocity() const
{
    return (m_velocity);
}

void CompLocation::setDesiredVel(const Triplet_f& vel)
{
    m_desiredVel = vel;
}

const Triplet_f& CompLocation::desiredVel() const
{
    return (m_desiredVel);
}

void CompLocation::setDesiredAngle(float angle)
{
    m_desiredAngle = angle;
}

float CompLocation::desiredAngle() const
{
    return (m_desiredAngle);
}


