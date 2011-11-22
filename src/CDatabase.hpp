//=============================================================================
///
/// \file           CDataBase.hpp
/// \class          CDataBase
///
/// \date           Creation date:  28/12/2009
/// \date           Latest update:  28/12/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          An implementation of the DataBase module.
///
///=============================================================================


#ifndef CDATABASE_HPP_INCLUDED
#define CDATABASE_HPP_INCLUDED
//-----------------------------------------------------------------------------/

// Mother classes
#include "IDataBase.hpp"
#include "IModule.hpp"
#include "Singleton.hpp"
//-----------------------------------------------------------------------------/

// Dependancies
#include <boost/scoped_ptr.hpp>
#include <boost/timer.hpp>
#include <sqlite3/sqlite3.h>
#include <string>
//-----------------------------------------------------------------------------/

class CDataBase : public IDataBase, public IModule, public Singleton<CDataBase>
{
    friend class Singleton<CDataBase>;

// Methods (IModule)
public:
    void init(const std::string& path);
    bool update();
    void destroy();

    const std::string& name() const;

    void addEntity(int id, int map, const std::string& type) {};
    void removeEntity(int id, int map) {};

// Methods (IDataBase)
public:
// TODO (Benjamin#1#): change method name (too similar with addEntity)
    int addNewPlayer(const std::string& name, const std::string& password, const std::string& type);
    void getPlayerLocation(const std::string& name);

    bool isPlayerExist(const std::string& pseudo);
    bool isPasswordMatch(const std::string& pseudo, const std::string& password, int & id, std::string & type);

// Methods
protected:
    virtual ~CDataBase() {}
    bool isKeyExist(int key);
    int linkId();

// Properties
protected:
    boost::scoped_ptr<boost::timer> m_readTimer;
    sqlite3 *db;
    std::string db_name;
}; //CDataBase


#endif // CDATABASE_HPP_INCLUDED
