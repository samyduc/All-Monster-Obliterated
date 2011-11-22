
///=============================================================================
///
/// \file           PhysicEntityLoader.hpp
/// \class          PhysicEntityLoader
///
/// \date           Creation date:  24/01/2010
/// \date           Latest update:  24/01/2010
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          Loads collision primitives in Newton using a xml file
///
///=============================================================================

// Include guard
#ifndef PHYSICENTITYLOADER_HPP_INCLUDED
#define PHYSICENTITYLOADER_HPP_INCLUDED
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

class PhysicEntityLoader
{

protected:
    enum PRIMITIVE
    {
        BOX,
        SPHERE
    };

// Methods
public:
    PhysicEntityLoader(NewtonWorld* world);
    virtual ~PhysicEntityLoader() {}

    NewtonBody* parseEntity(int id, const std::string& fileName, int material);

// Methods
protected:
    NewtonBody* processShape(TiXmlElement* element, PRIMITIVE shape);

    Triplet_f parsePos(TiXmlElement* e);
    Triplet_f parseScale(TiXmlElement* e);

// Properties
protected:
    NewtonWorld* m_world;
}; // PhysicEntityLoader

#endif // PHYSICENTITYLOADER_HPP_INCLUDED


