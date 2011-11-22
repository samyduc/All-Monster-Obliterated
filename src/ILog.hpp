

///=============================================================================
///
/// \file           ILog.hpp
/// \class          ILog
///
/// \date           Creation date:  28/12/2009
/// \date           Latest update:  28/12/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          An interface for the Log module.
///
///=============================================================================

// Include guard
#ifndef ILOG_HPP_INCLUDED
#define ILOG_HPP_INCLUDED
//-----------------------------------------------------------------------------/

// Dependancies
#include <iostream>
#include <string>
//-----------------------------------------------------------------------------/

// Forward declarations
class IModule;
//-----------------------------------------------------------------------------/

class ILog
{
// Methods
public:
    virtual void addLog(IModule *module, std::string log) = 0;
}; // ILog

#endif // ILOG_HPP_INCLUDED


