
///=============================================================================
///
/// \file           main.cpp
///
/// \date           Creation date:  09/08/2008
/// \date           Latest update:  08/08/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          Entry point of the program
///
///=============================================================================

// Dependancies
#include "CKernel.hpp"
//-----------------------------------------------------------------------------/

int main(int argc, const char* argv[])
{
    CKernel::init("../media/config.xml");
    while (CKernel::update());
    CKernel::destroy();

    return (0);
}


