//=============================================================================
///
/// \file           CAdmin.hpp
/// \class          CAdmin
///
/// \date           Creation date:  08/01/2010
/// \date           Latest update:  08/01/2010
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          An implementation of the Admin module.
///
///=============================================================================


#ifndef CADMIN_HPP_INCLUDED
#define CADMIN_HPP_INCLUDED

//-----------------------------------------------------------------------------/

// Mother classes
#include "IAdmin.hpp"
#include "IModule.hpp"
#include "Singleton.hpp"
//-----------------------------------------------------------------------------/

// Dependancies
#include <boost/scoped_ptr.hpp>
#include <boost/timer.hpp>
#include <string>
#include <vector>
#include <map>
//-----------------------------------------------------------------------------/

//-----------------------------------------------------------------------------/

class CAdmin : public IAdmin, public IModule, public Singleton<CAdmin>
{
    friend class Singleton<CAdmin>;

// Methods (IModule)
public:

    enum ITEM_ID
    {
        WOOD_BOX = 0,
        CORPSE = 1,
    };

    void init(const std::string& path);
    bool update();
    void destroy();

    const std::string& name() const;

    void addEntity(int id, int map, const std::string& type) {};
    void removeEntity(int id, int map) {};

// Methods (IDataBase)
public:
    void handleAdminCommand(int id_admin, std::string);


// Methods
protected:
    virtual ~CAdmin() {}
    bool isAdmin(const int id);
    void addItem(std::vector<std::string> & a);
    void dbInit(std::vector<std::string> & a);
    void kickPlayer(std::vector<std::string> & a);
    void netTick(std::vector<std::string> & a);

// Properties
protected:
    std::map<std::string, void (CAdmin::*)(std::vector<std::string> &) > m_commandMap;

}; //CAdmin


#endif // CADMIN_HPP_INCLUDED
