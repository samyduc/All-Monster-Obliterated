
///=============================================================================
///
/// \file           PhysicMap.cpp
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
#include "PhysicMap.hpp"
//-----------------------------------------------------------------------------/

// Dependancies
#include <iostream>
#include "Matrix.hpp"
#include "PhysicLoader.hpp"
#include "PhysicEntityLoader.hpp"
#include "CKernel.hpp"
#include "IData.hpp"
#include "INetwork.hpp"
#include "CompLocation.hpp"
//-----------------------------------------------------------------------------/

PhysicMap::PhysicMap()
{
    float min[] = {-2000, -2000, -2000};
    float max[] = {2000, 2000, 2000};
    m_world = NewtonCreate(0, 0);
    NewtonSetWorldSize(m_world, min, max);
    NewtonSetSolverModel(m_world, 0);
    NewtonSetFrictionModel(m_world, 0);

    m_mapID = NewtonMaterialCreateGroupID(m_world);
    m_playerID = NewtonMaterialCreateGroupID(m_world);

    NewtonMaterialSetDefaultSoftness(m_world, m_mapID, m_playerID, 0.0f);
	NewtonMaterialSetDefaultElasticity(m_world, m_mapID, m_playerID, 0.2f);
	NewtonMaterialSetDefaultFriction(m_world, m_mapID, m_playerID, 0.5f, 0.0f);

	NewtonMaterialSetDefaultSoftness(m_world, m_playerID, m_playerID, 0.0f);
	NewtonMaterialSetDefaultElasticity(m_world, m_playerID, m_playerID, 0.2f);
	NewtonMaterialSetDefaultFriction(m_world, m_playerID, m_playerID, 0.5f, 0.0f);
}

bool PhysicMap::update()
{
    NewtonUpdate(m_world, 0.01f);
    return (true);
}

void PhysicMap::loadMap(const std::string& name)
{
    PhysicLoader loader(m_world);
    loader.parseFile(name);
}

// TODO (#1#): use a "physicComponent" instead
void PhysicMap::addEntity(int id, const std::string& type)
{
    PhysicEntityLoader loader(m_world);
    std::string path("../media/" + type + ".def");
    NewtonBody* body = loader.parseEntity(id, path, m_playerID);

    if (body)
    {
// TODO (Benjamin#1#): used as debug for uninitialised entity
        Matrix_f matrix;
        matrix.setPosition(Triplet_f(-5, -5, -5));
        NewtonBodySetMatrix(body, matrix.raw());

        NewtonBodySetForceAndTorqueCallback(body, playerForceAndTorque);

        m_bodyMap.insert(BodyMap::value_type(id, body));
    }
}

void PhysicMap::removeEntity(int id)
{
    BodyMap::const_iterator it = m_bodyMap.find(id);
    if (it != m_bodyMap.end())
    {
        NewtonDestroyBody(m_world, it->second);
    }
}

void PhysicMap::moveEntity(int id, const Triplet_f& pos)
{
    BodyMap::const_iterator it = m_bodyMap.find(id);
    if (it != m_bodyMap.end() && it->second != 00)
    {
        Matrix_f matrix;
        matrix.setPosition(pos);
        NewtonBodySetMatrix(it->second, matrix.raw());
    }
}

void PhysicMap::rayCast(int srcID, const Triplet_f& start, const Triplet_f& end)
{
    ShotInfo info(srcID, 0, start, end);
    NewtonWorldRayCast(m_world, &start.x, &end.x, callbackFilter, &info, 00);
    // TODO (#2#): line too long
    CKernel::network()->sendShotFired(info.idShooter, info.idTarget, info.endPos);
}


void PhysicMap::playerForceAndTorque(const NewtonBody* nBody)
{
    int id = (int)(NewtonBodyGetUserData(nBody));
    CompLocation* loc = CKernel::data()->getGameObjectLocation(id);
    float fMasse, ixx, iyy, izz;
    NewtonBodyGetMassMatrix(nBody, &fMasse, &ixx, &iyy, &izz);

    // Apply gravity force
    Triplet_f gravity(0, -fMasse * 9.81f, 0);
    NewtonBodyAddForce(nBody, &gravity.x);

    // Apply movment force
    Triplet_f desiredVel = loc->desiredVel() * 20;
    Triplet_f currentVel;
    NewtonBodyGetVelocity(nBody,&currentVel.x);
	Triplet_f forceApply = (desiredVel - currentVel) * fMasse * 10;
	forceApply.y = 0;
    NewtonBodyAddForce(nBody, &forceApply.x);

    // Apply rotation
    Matrix_f mat;
    NewtonBodyGetMatrix(nBody, mat.raw());
    mat.setRotationY(loc->desiredAngle());
    NewtonBodySetMatrix(nBody, mat.raw());

    // Apply shot recoil
    if (loc->isImpact())
    {
        Triplet_f impact = loc->getNormal() * -3;
        NewtonAddBodyImpulse(nBody, &impact.x, &mat.position().x);
    }

    // Update the game object
    loc->setPosition(mat.position());
    loc->setDirection(Triplet_f(loc->desiredAngle()));
    loc->setVelocity(currentVel);
}

float PhysicMap::callbackFilter(const NewtonBody* body, const float* normal,
    int coll, void* data, float ratio)
{
 // TODO (Benjamin#1#): it sometimes find 2 target (should not)
   ShotInfo* info = static_cast<ShotInfo*>(data);
    int target = (int)(NewtonBodyGetUserData(body));

    if (target != info->idShooter)
    {
        CompLocation* loc = CKernel::data()->getGameObjectLocation(target);
        if (loc)
        {
            loc->setNormal(Triplet_f(normal[0], normal[1], normal[2]));
        }

        info->idTarget = target;
        info->endPos = info->startPos + (info->maxPos - info->startPos) * ratio;
        return (ratio);
    }
    else
    {
        return (1.0f);
    }
}


