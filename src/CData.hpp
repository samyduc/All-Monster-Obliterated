
///=============================================================================
///
/// \file           CData.hpp
/// \class          CData
///
/// \date           Creation date:  25/06/2009
/// \date           Latest update:  08/08/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          An implementation of the Data module.
///
///=============================================================================

// Include guard
#ifndef CDATA_HPP_INCLUDED
#define CDATA_HPP_INCLUDED
//-----------------------------------------------------------------------------/

// Mother classes
#include "IData.hpp"
#include "IModule.hpp"
#include "Singleton.hpp"
#include "Triplet.hpp"
//-----------------------------------------------------------------------------/

// Dependancies
#include <map>
//-----------------------------------------------------------------------------/

class CData : public IData, public IModule, public Singleton<CData>
{
    friend class Singleton<CData>;

// Methods (IModule)
public:
    void init(const std::string& path);
    bool update();
    void destroy();

    const std::string& name() const;

    void addEntity(int id, int map, const std::string& type);
    void removeEntity(int id, int map);

// Methods (IData)
public:
 // TODO (Benjamin#1#): merge the 2 objects
    CompLocation* getGameObjectLocation(int id) const;
    CompInfo* getGameObjectInfo(int id) const;

    void nameEntity(int id, int map, const std::string& name);

    std::map<int, CompLocation*> getAllLocation();

    const std::string& getMapName() const;

// Methods
protected:
    virtual ~CData() {}

// Properties
protected:
    std::string m_mapName;

    typedef std::map<int, CompLocation*> LocationMap;
    LocationMap m_locationMap;

    typedef std::map<int, CompInfo*> InfoMap;
    InfoMap m_infoMap;
}; // CData

#endif // CDATA_HPP_INCLUDED


