//=============================================================================
///
/// \file           CDataBase.cpp
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

// Header of the class
#include "CDataBase.hpp"
//-----------------------------------------------------------------------------/

// Dependancies
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <sstream>
#include "CKernel.hpp"
#include "ILog.hpp"
//-----------------------------------------------------------------------------/

#define SAVE_WORLD_TIME 600
#define MAX_CHAR "50"

void CDataBase::init(const std::string& path)
{
    m_readTimer.reset(new boost::timer());
    m_readTimer->restart();

    db_name = "../media/db2.sqlite3";
    if(sqlite3_open(db_name.c_str(), &db))
    {
        CKernel::log()->addLog(this, "CDataBase::init " + std::string(sqlite3_errmsg(db)));
        sqlite3_close(db);
    }
    else
    {
        CKernel::log()->addLog(this, "CDataBase::init done");
    }

}

bool CDataBase::update()
{
    if (m_readTimer->elapsed() > SAVE_WORLD_TIME)
    {
        //TODO(#2#) Save the current world state and objects in DataBase
        m_readTimer->restart();
    }
    return(true);
}

void CDataBase::destroy()
{
    sqlite3_close(db);
    CKernel::log()->addLog(this, "CDatabase::destroy done");
}

const std::string& CDataBase::name() const
{
    static std::string str("database");
    return (str);
}

int CDataBase::linkId()
{
    static int id = 1;

    while(isKeyExist(id)) ++id;

    return id++;
}

int CDataBase::addNewPlayer(const std::string& name, const std::string& password, const std::string& type)
{
    int row;
    int column;
    char *zErrMsg = 0;
    char **pazResult;
    int toReturn = 0;
    std::stringstream requete;
    int id = linkId();

    requete << "INSERT into player (id, username, password, type, rights, creation_time) values("
            << id << ", \""<< name << "\" , " << "\"" << password << "\" , " << "\""
            << type << "\" , \""<< "u" << "\" , " << "DATE()" <<");";
    std::cout << requete.str() << std::endl;
    if(sqlite3_get_table(db, requete.str().c_str(), &pazResult, &row, &column, &zErrMsg) != SQLITE_OK)
    {
        CKernel::log()->addLog(this, "CDataBase::addNewPlayer " + std::string(zErrMsg));
        toReturn = -1;
    }
    sqlite3_free(zErrMsg);
    sqlite3_free_table(pazResult);
    return toReturn;
}

void CDataBase::getPlayerLocation(const std::string& name)
{
}

bool CDataBase::isPlayerExist(const std::string& name)
{
    bool toReturn = true;
    int row;
    int column;
    char *zErrMsg = 0;
    char **pazResult;
    std::stringstream requete;

    requete << "SELECT username FROM player WHERE username = \""
            << name << "\"" << ";";

    if(sqlite3_get_table(db, requete.str().c_str(), &pazResult, &row, &column, &zErrMsg) != SQLITE_OK)
    {
        CKernel::log()->addLog(this, "CDataBase::isPlayerExist " + std::string(zErrMsg));
    }
    /*
    * if requet send back an empty table (0 row)
    * username doesn't exist
    */
    if(row != 1)
    {
        toReturn = false;
    }
    CKernel::log()->addLog(this, "CDataBase::isPlayerExist " + name +
                    boost::lexical_cast<std::string>(static_cast<bool>(toReturn)));

    sqlite3_free(zErrMsg);
    sqlite3_free_table(pazResult);
    return(toReturn);
}

bool CDataBase::isPasswordMatch(const std::string& name, const std::string& password, int & id, std::string & type)
{
    bool toReturn = true;
    int row;
    int column;
    char *zErrMsg = 0;
    char **pazResult;
    std::stringstream requete;

    requete << "SELECT id, type FROM player WHERE username = \""
            << name << "\" AND password = \"" << password << "\" ;";

    if(sqlite3_get_table(db, requete.str().c_str(), &pazResult, &row, &column, &zErrMsg) != SQLITE_OK)
    {
        CKernel::log()->addLog(this, "CDataBase::isPasswordMatch " + std::string(zErrMsg));
    }
    /*
    * if requet send back an empty table (0 row)
    * username doesn't exist
    * password doesn't match
    */
    if(row != 1)
    {
        std::cout << "over lol db fail" << std::endl;
        toReturn = false;
        CKernel::log()->addLog(this, "CDataBase::isPasswordMatch " + name + std::string(" | ") + password);
    }
    else
    {
        id = boost::lexical_cast<int>(pazResult[2]);
        type = pazResult[3];
    }

    sqlite3_free(zErrMsg);
    sqlite3_free_table(pazResult);
    return(toReturn);
}

bool CDataBase::isKeyExist(int key)
{
    bool toReturn = true;
    int row;
    int column;
    char *zErrMsg = 0;
    char **pazResult;
    std::stringstream requete;

    requete << "SELECT id FROM player WHERE id = "
            << key << ";";

    if(sqlite3_get_table(db, requete.str().c_str(), &pazResult, &row, &column, &zErrMsg) != SQLITE_OK)
    {
        CKernel::log()->addLog(this, "CDataBase::isKeyExist " + std::string(zErrMsg));
    }

    if(row != 1)
    {
        toReturn = false;
        CKernel::log()->addLog(this, "CDataBase::isKeyExist "
                               + boost::lexical_cast<std::string>(static_cast<int>(toReturn))
                               + " "
                               +boost::lexical_cast<std::string>(static_cast<bool>(toReturn)));
    }

    sqlite3_free(zErrMsg);
    sqlite3_free_table(pazResult);
    return(toReturn);
}

