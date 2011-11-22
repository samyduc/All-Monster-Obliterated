
///=============================================================================
///
/// \file           Component.hpp
/// \class          Component
///
/// \date           Creation date:  07/08/2009
/// \date           Latest update:  08/08/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          Base class for any object's capacity
///
///=============================================================================

// Include guard
#ifndef COMPONENT_HPP_INCLUDED
#define COMPONENT_HPP_INCLUDED

//Dependencies
#include "INetwork.hpp"
#include "CKernel.hpp"
//-----------------------------------------------------------------------------/

class Component
{
// Methods
public:
    Component(int id = 0) : m_id(id) {}
	virtual ~Component() {}

	virtual void update() {}

	void setId(int id) {m_id = id;}
	int getId() const {return (m_id);}

	void setTick(int tick = -1) {
	    if(tick = -1)
            m_tick = CKernel::network()->getTick();
        else m_tick = tick;
        }
	int getTick() const {return (m_tick);}

// Properties
protected:
	int m_id;
	int m_tick;
}; // Component

#endif // ICOMPONENT_HPP_INCLUDED


