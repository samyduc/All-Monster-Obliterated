
///=============================================================================
///
/// \file           CompInfo.cpp
///
/// \date           Creation date:  09/08/2009
/// \date           Latest update:  09/08/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief
///
///=============================================================================

// Header of the class
#include "CompInfo.hpp"
//-----------------------------------------------------------------------------/

CompInfo::CompInfo(int id, int map, const std::string& type, const std::string& name) :
    Component(id), m_type(type), m_name(name), m_map(map)
{

}

CompInfo::~CompInfo()
{

}

void CompInfo::setType(const std::string& type)
{
    m_type = type;
}

std::string CompInfo::type() const
{
    return (m_type);
}

void CompInfo::setName(const std::string& name)
{
    m_name = name;
}

const std::string& CompInfo::name() const
{
    return (m_name);
}

void CompInfo::setMap(int map)
{
    m_map = map;
}

const int CompInfo::map() const
{
    return (m_map);
}


