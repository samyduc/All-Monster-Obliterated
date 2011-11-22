
///=============================================================================
///
/// \file           PhysicLoader.hpp
/// \class          PhysicLoader
///
/// \date           Creation date:  04/08/2009
/// \date           Latest update:  08/08/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          Loads collision primitives in Newton using a xml file
///
///=============================================================================

// Include guard
#ifndef PHYSICLOADER_HPP_INCLUDED
#define PHYSICLOADER_HPP_INCLUDED
//-----------------------------------------------------------------------------/

// Dependancies
#include <string>
#include <Newton/Newton.h>
#include "Triplet.hpp"
//-----------------------------------------------------------------------------/

// Forward declarations
class TiXmlElement;
class TiXmlNode;
//-----------------------------------------------------------------------------/

class PhysicLoader
{

protected:
    enum PRIMITIVE
    {
        BOX,
        SPHERE
    };

// Methods
public:
    PhysicLoader(NewtonWorld* world);
    virtual ~PhysicLoader() {}

    void parseFile(const std::string& fileName);

// Methods
protected:
    void processShape(TiXmlElement* element, PRIMITIVE shape);

    Triplet_f parseTriplet(TiXmlElement* element);

// Properties
protected:
    NewtonWorld* m_world;
}; // PhysicLoader

#endif // PHYSICLOADER_HPP_INCLUDED


