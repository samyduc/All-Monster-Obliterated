
///=============================================================================
///
/// \file           CPhysic.hpp
/// \class          CPhysic
///
/// \date           Creation date:  25/01/2009
/// \date           Latest update:  08/08/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          An implementation of the Physic module, using Newton.
///
///=============================================================================

// Include guard
#ifndef CPHYSIC_HPP_INCLUDED
#define CPHYSIC_HPP_INCLUDED
//-----------------------------------------------------------------------------/

// Mother classes
#include "IPhysic.hpp"
#include "IModule.hpp"
#include "Singleton.hpp"
//-----------------------------------------------------------------------------/

// Dependancies
#include <map>
//-----------------------------------------------------------------------------/

// Forward declarations
class PhysicMap;
class WorldMap;
//-----------------------------------------------------------------------------/

class CPhysic : public IPhysic, public IModule, public Singleton<CPhysic>
{
    friend class Singleton<CPhysic>;

// Methods (IModule)
public:
    void init(const std::string& path);
    bool update();
    void destroy();

    const std::string& name() const;

    void addEntity(int id, int map, const std::string& type);
    void removeEntity(int id, int map);

// Methods (IPhysic)
public:
    void loadMap(int mapID, const std::string& name);
    void moveEntity(int id, int map, const Triplet_f& pos);

    // TODO (#2#): line too long
    void rayCast(int mapID, int source, const Triplet_f& start, const Triplet_f& end);

// Methods
protected:
    virtual ~CPhysic() {}

// Properties
protected:
    WorldMap* m_worldMap;

    typedef std::map<int, PhysicMap*> MapContainer;
    MapContainer m_mapContainer;
}; // CPhysic

#endif // CPHYSIC_HPP_INCLUDED


