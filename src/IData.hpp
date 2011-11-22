
///=============================================================================
///
/// \file           IData.hpp
/// \class          IData
///
/// \date           Creation date:  25/06/2009
/// \date           Latest update:  08/08/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          An interface for the Data module.
///
///=============================================================================

// Include guard
#ifndef IDATA_HPP_INCLUDED
#define IDATA_HPP_INCLUDED
//-----------------------------------------------------------------------------/

// Dependancies
#include <string>
#include <map>
#include "Triplet.hpp"
//-----------------------------------------------------------------------------/

// Forward declarations
class CompLocation;
class CompInfo;
//-----------------------------------------------------------------------------/

class IData
{
// Methods
public:
    virtual CompLocation* getGameObjectLocation(int id) const = 0;
    virtual CompInfo* getGameObjectInfo(int id) const = 0;

    virtual void nameEntity(int id, int map, const std::string& name) = 0;

    virtual std::map<int, CompLocation*> getAllLocation() = 0;

    virtual const std::string& getMapName() const = 0;
}; // IData

#endif // IDATA_HPP_INCLUDED


