
///=============================================================================
///
/// \file           IModule.hpp
/// \class          IModule
///
/// \date           Creation date:  31/12/2008
/// \date           Latest update:  08/08/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          Interface used by all modules
///
///=============================================================================

// Include guard
#ifndef IMODULE_HPP_INCLUDED
#define IMODULE_HPP_INCLUDED
//-----------------------------------------------------------------------------/

// Dependancies
#include <string>
//-----------------------------------------------------------------------------/

class IModule
{
// Methods
public:
    virtual void init(const std::string& path) = 0;
    virtual bool update() = 0;
    virtual void destroy() = 0;

    virtual const std::string& name() const = 0;

    virtual void addEntity(int id, int map, const std::string& type) = 0;
    virtual void removeEntity(int id, int map) = 0;
}; // IModule

#endif // IMODULE_HPP_INCLUDED


