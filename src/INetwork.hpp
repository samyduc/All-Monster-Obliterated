
///=============================================================================
///
/// \file           INetwork.hpp
/// \class          INetwork
///
/// \date           Creation date:  11/08/2008
/// \date           Latest update:  08/08/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          An interface for the Network module.
///
///=============================================================================

// Include guard
#ifndef INETWORK_HPP_INCLUDED
#define INETWORK_HPP_INCLUDED
//-----------------------------------------------------------------------------/

// Dependancies
#include "Triplet.hpp"
//-----------------------------------------------------------------------------/

class INetwork
{
// Methods
public:
    virtual void listen() = 0;

    virtual void sleep(int ms) = 0;

// TODO (#2#): line too long
    virtual void sendShotFired(int source, int target, const Triplet_f& impact) = 0;
    virtual void sendChatMessage(const std::string& mes) = 0;

    virtual void disconnectPlayer(int id) = 0;
    virtual void setTickRate(float tick) = 0;

    virtual int getTick() = 0;
}; // INetwork

#endif // INETWORK_HPP_INCLUDED


