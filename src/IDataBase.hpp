

///=============================================================================
///
/// \file           IDataBase.hpp
/// \class          IDataBase
///
/// \date           Creation date:  28/12/2009
/// \date           Latest update:  28/12/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          An interface for the DataBase module.
///
///=============================================================================

// Include guard
#ifndef IDATABASE_HPP_INCLUDED
#define IDATABASE_HPP_INCLUDED
//-----------------------------------------------------------------------------/

// Dependancies
#include <string>
//-----------------------------------------------------------------------------/

class IDataBase
{
// Methods
public:
    virtual int addNewPlayer(const std::string& name, const std::string& password, const std::string& type) = 0;
    virtual void getPlayerLocation(const std::string& name) = 0;

    virtual bool isPlayerExist(const std::string& pseudo) = 0;
    virtual bool isPasswordMatch(const std::string& pseudo, const std::string& password, int & id, std::string & type) = 0;

}; // IDataBase

#endif // IDATABASE_HPP_INCLUDED


