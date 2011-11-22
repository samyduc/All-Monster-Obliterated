
///=============================================================================
///
/// \file           PhysicEntityLoader.cpp
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

// Header of the class
#include "PhysicEntityLoader.hpp"
//-----------------------------------------------------------------------------/

// Dependancies
#include <tinyXML/tinyxml.h>
#include "Matrix.hpp"
#include <iostream>
//-----------------------------------------------------------------------------/

// Namespaces resolution
using namespace std;
//-----------------------------------------------------------------------------/

PhysicEntityLoader::PhysicEntityLoader(NewtonWorld* world) : m_world(world)
{

}

NewtonBody* PhysicEntityLoader::parseEntity(int id, const std::string& fileName, int material)
{
    TiXmlDocument doc(fileName);
    NewtonBody* body(00);
    doc.LoadFile();

    TiXmlElement* root = doc.RootElement();
    if (root)
    {
        TiXmlElement* subElement = root->FirstChildElement("box");
        if (subElement)
        {
            body = processShape(subElement, BOX);
        }

        subElement = root->FirstChildElement("sphere");
        if (subElement)
        {
            body = processShape(subElement, SPHERE);
        }
    }
    if (body)
    {
        NewtonBodySetMaterialGroupID(body, material);
        NewtonBodySetUserData(body, (void*)id);
        NewtonBodySetAutoFreeze(body, false);
        Triplet_f pin(0, 1, 0);
        NewtonConstraintCreateUpVector(m_world, &pin.x, body);
    }

    return (body);
}

NewtonBody* PhysicEntityLoader::processShape(TiXmlElement* element, PRIMITIVE shape)
{
    if (!element) {return(00);}

    NewtonCollision* collision = NewtonCreateNull(m_world);
    Triplet_f size = parseScale(element->FirstChildElement("size"));
    switch (shape)
    {
        case BOX:
            collision = NewtonCreateBox(m_world, size.x, size.y, size.z, 00);
            break;

        case SPHERE:
            collision = NewtonCreateSphere(m_world, size.x, size.y, size.z, 00);
            break;
    }

    NewtonBody* body = NewtonCreateBody(m_world, collision);
    NewtonReleaseCollision(m_world, collision);

    Matrix_f matrix;
    matrix.setPosition(parsePos(element->FirstChildElement("position")));
    NewtonBodySetMatrix(body, matrix.raw());
    NewtonBodySetMassMatrix(body, 30.0f, 1.0f, 1.0f, 1.0f);
    NewtonBodySetLinearDamping(body, 0.3f);
    NewtonBodySetContinuousCollisionMode(body, 1);
    return (body);
}

Triplet_f PhysicEntityLoader::parsePos(TiXmlElement* e)
{
    Triplet_f vect(0, 0, 0);
    if (e)
    {
        e->QueryValueAttribute("x", &vect.x);
        e->QueryValueAttribute("y", &vect.y);
        e->QueryValueAttribute("z", &vect.z);
    }
    return (vect);
}

Triplet_f PhysicEntityLoader::parseScale(TiXmlElement* e)
{
    Triplet_f vect(1, 1, 1);
    if (e)
    {
        e->QueryValueAttribute("x", &vect.x);
        e->QueryValueAttribute("y", &vect.y);
        e->QueryValueAttribute("z", &vect.z);
    }
    return (vect);
}


