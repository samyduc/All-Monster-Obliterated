
///=============================================================================
///
/// \file           CKernel.hpp
/// \class          CKernel
///
/// \date           Creation date:  09/08/2008
/// \date           Latest update:  08/08/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          Static class that manages all the modules
///
///=============================================================================

// Include guard
#ifndef CKERNEL_HPP_INCLUDED
#define CKERNEL_HPP_INCLUDED
//-----------------------------------------------------------------------------/

// Dependancies
#include <vector>
#include <string>
//-----------------------------------------------------------------------------/

// Forward declarations
class IModule;
class IData;
class IDataBase;
class INetwork;
class IPhysic;
class ILog;
class IAdmin;
//-----------------------------------------------------------------------------/

class CKernel
{
// Methods
public:
    static void init(const std::string& path);
    static bool update();
    static void destroy();

    static int CKernel::uniqueID();

    static void addEntity(int id, int map, const std::string& type);
    static void removeEntity(int id, int map);

    static IData* data();
    static IDataBase* database();
    static INetwork* network();
    static IPhysic* physic();
    static ILog* log();
    static IAdmin* admin();

protected:
    static std::vector<IModule*> m_moduleVect;
}; // CKernel

#endif // CKERNEL_HPP_INCLUDED


