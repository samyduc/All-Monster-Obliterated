
///=============================================================================
///
/// \file           PhysicLoader.cpp
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

// Header of the class
#include "PhysicLoader.hpp"
//-----------------------------------------------------------------------------/

// Dependancies
#include <tinyXML/tinyxml.h>
#include "Matrix.hpp"
#include <iostream>
//-----------------------------------------------------------------------------/

// Namespaces resolution
using namespace std;
//-----------------------------------------------------------------------------/

PhysicLoader::PhysicLoader(NewtonWorld* world) : m_world(world)
{

}

void PhysicLoader::parseFile(const string& fileName)
{
    TiXmlDocument doc(fileName);
    doc.LoadFile();

    TiXmlElement* root = doc.RootElement();
    if (root)
    {
        TiXmlElement* subElement = root->FirstChildElement("box");
        while(subElement)
        {
            processShape(subElement, BOX);
            subElement = subElement->NextSiblingElement("box");
        }

        subElement = root->FirstChildElement("sphere");
        while(subElement)
        {
            processShape(subElement, SPHERE);
            subElement = subElement->NextSiblingElement("sphere");
        }
    }
}

void PhysicLoader::processShape(TiXmlElement* element, PRIMITIVE shape)
{
    if (!element) {return;}

    NewtonCollision* collision = 00;
    Triplet_f size = parseTriplet(element->FirstChildElement("size"));
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
    matrix.setPosition(parseTriplet(element->FirstChildElement("position")));
    NewtonBodySetMatrix(body, matrix.raw());
}

Triplet_f PhysicLoader::parseTriplet(TiXmlElement* element)
{
    Triplet_f vect;
    if (element)
    {
        element->QueryValueAttribute("x", &vect.x);
        element->QueryValueAttribute("y", &vect.y);
        element->QueryValueAttribute("z", &vect.z);
    }
    return (vect);
}


