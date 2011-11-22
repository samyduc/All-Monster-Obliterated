
///=============================================================================
///
/// \file           CompLocation.hpp
/// \class          CompLocation
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

// Include guard
#ifndef COMPLOCATION_HPP_INCLUDED
#define COMPLOCATION_HPP_INCLUDED
//-----------------------------------------------------------------------------/

// Mother classes
#include "Component.hpp"
//-----------------------------------------------------------------------------/

// Dependancies
#include "Triplet.hpp"
//-----------------------------------------------------------------------------/

class CompLocation : public Component
{
// Methods
public:
    CompLocation(int id, const Triplet_f& pos, const Triplet_f& dir);
	virtual ~CompLocation();

    void setPosition(const Triplet_f& pos);
    const Triplet_f& position() const;

    void setDirection(const Triplet_f& dir);
    const Triplet_f& direction() const;

    void setVelocity(const Triplet_f& vel);
    const Triplet_f& velocity() const;

    void setDesiredVel(const Triplet_f& vel);
    const Triplet_f& desiredVel() const;

    void setDesiredAngle(float angle);
    float desiredAngle() const;

    void setNormal(const Triplet_f& normal) {m_normal = normal; m_isImpact = true;}
    const Triplet_f& getNormal() {m_isImpact = false; return (m_normal);}

    bool isImpact() {return (m_isImpact);}

// Properties
protected:
    Triplet_f m_position;
    Triplet_f m_direction;
    Triplet_f m_velocity;

    Triplet_f m_desiredVel;
    float m_desiredAngle;

// TODO (#1#): clean this hack
    Triplet_f m_normal;
    bool m_isImpact;
}; // CompLocation

#endif // COMPLOCATION_HPP_INCLUDED


