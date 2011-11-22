///=============================================================================
///
/// \file           IAdmin.hpp
/// \class          IAdmin
///
/// \date           Creation date:  08/01/2010
/// \date           Latest update:  08/01/2010
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          An interface for the Admin module.
///
///=============================================================================

// Include guard
#ifndef IADMIN_HPP_INCLUDED
#define IADMIN_HPP_INCLUDED
//-----------------------------------------------------------------------------/

// Dependancies
#include <string>
#include "Triplet.hpp"
//-----------------------------------------------------------------------------/

class IAdmin
{
// Methods
public:
    virtual void handleAdminCommand(int id_admin, std::string) = 0;

}; // IAdmin
#endif // IADMIN_HPP_INCLUDED


