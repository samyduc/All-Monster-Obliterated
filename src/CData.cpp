
///=============================================================================
///
/// \file           CData.cpp
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

// Header of the class
#include "CData.hpp"
//-----------------------------------------------------------------------------/

// Dependancies
#include <boost/lexical_cast.hpp>
#include "CKernel.hpp"
#include "IPhysic.hpp"
#include "ILog.hpp"
#include "CompLocation.hpp"
#include "CompInfo.hpp"
//-----------------------------------------------------------------------------/

void CData::init(const std::string& path)
{
    m_mapName = "../media/map_2.scene";
    CKernel::log()->addLog(this, "CData::init done");
}

bool CData::update()
{
    return (true);
}

void CData::destroy()
{

}

const std::string& CData::name() const
{
    static std::string str("data");
    return (str);
}

void CData::addEntity(int id, int map, const std::string& type)
{
    CompLocation* loc = new CompLocation(id, Triplet_f(0, 0, 0), Triplet_f(0, 0, 0));
    m_locationMap.insert(LocationMap::value_type(id, loc));
    CompInfo* info = new CompInfo(id, map, type, "");
    m_infoMap.insert(InfoMap::value_type(id, info));
}

void CData::removeEntity(int id, int map)
{
    LocationMap::iterator it_locationMap = m_locationMap.find(id);
    if (it_locationMap != m_locationMap.end())
    {
        delete it_locationMap->second;
        m_locationMap.erase(it_locationMap);
    }

    InfoMap::iterator it_infoMap = m_infoMap.find(id);
    if (it_infoMap != m_infoMap.end())
    {
        delete it_infoMap->second;
        m_infoMap.erase(it_infoMap);
    }
}

CompLocation* CData::getGameObjectLocation(int id) const
{
    LocationMap::const_iterator it = m_locationMap.find(id);
    if (it == m_locationMap.end())
    {
        return (00);
    }
    else
    {
        return (it->second);
    }
}

CompInfo* CData::getGameObjectInfo(int id) const
{
    InfoMap::const_iterator it = m_infoMap.find(id);
    if (it == m_infoMap.end())
    {
        return (00);
    }
    else
    {
        return (it->second);
    }
}

void CData::nameEntity(int id, int map, const std::string& name)
{
    CompInfo* info = getGameObjectInfo(id);
    if (info)
    {
        info->setName(name);
    }
}

std::map<int, CompLocation*> CData::getAllLocation()
{
    return (m_locationMap);
}

const std::string& CData::getMapName() const
{
    return (m_mapName);
}


