
///=============================================================================
///
/// \file           CompInfo.hpp
/// \class          CompInfo
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

// Include guard
#ifndef COMPINFO_HPP_INCLUDED
#define COMPINFO_HPP_INCLUDED
//-----------------------------------------------------------------------------/

// Mother classes
#include "Component.hpp"
//-----------------------------------------------------------------------------/

// Dependancies
#include <string>
//-----------------------------------------------------------------------------/

class CompInfo : public Component
{
public:
    enum COLOR
    {
        BLACK, WHITE, RED, GREEN,
        BLUE, YELLOW, MAGENTA, CYAN
    };

// Methods
public:
    CompInfo(int id, int map, const std::string& type = "", const std::string& name = "");
	virtual ~CompInfo();

    void setType(const std::string& type);
    std::string type() const;

    void setName(const std::string& name);
    const std::string& name() const;

    void setMap(int map);
    const int map() const;

// Properties
protected:
    std::string m_type;
    std::string m_name;
    int m_map;
}; // CompInfo

#endif // COMPINFO_HPP_INCLUDED


