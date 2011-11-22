
///=============================================================================
///
/// \file           PhysicMap.hpp
/// \class          PhysicMap
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

// Include guard
#ifndef PHYSICMAP_HPP_INCLUDED
#define PHYSICMAP_HPP_INCLUDED
//-----------------------------------------------------------------------------/

// Dependancies
#include <string>
#include <map>
#include <Newton/Newton.h>
#include "Triplet.hpp"
//-----------------------------------------------------------------------------/

class PhysicMap
{
// Utility structure
protected:
    typedef struct ShotInfo
    {
// TODO (#2#): line too long
        ShotInfo(int shooter, int target, const Triplet_f& start, const Triplet_f& end) :
            idShooter(shooter), idTarget(target), startPos(start), endPos(end), maxPos(end) {};

        int idShooter;
        int idTarget;
        Triplet_f startPos;
        Triplet_f endPos;
        Triplet_f maxPos;
    } ShotInfo;

// Methods
public:
    PhysicMap();
    virtual ~PhysicMap() {}

    bool update();

    void addEntity(int id, const std::string& type);
    void removeEntity(int id);

    void moveEntity(int id, const Triplet_f& pos);

    void loadMap(const std::string& name);

    void rayCast(int srcID, const Triplet_f& start, const Triplet_f& end);

// Methods
protected:
    static void playerForceAndTorque(const NewtonBody* nBody);
    static float callbackFilter(const NewtonBody* body,
        const float* normal, int coll, void* data, float ratio);

// Properties
protected:
    NewtonWorld* m_world;
    int m_mapID;
    int m_playerID;

    typedef std::map<int, NewtonBody*> BodyMap;
    BodyMap m_bodyMap;
}; // PhysicLoader

#endif // PHYSICMAP_HPP_INCLUDED


