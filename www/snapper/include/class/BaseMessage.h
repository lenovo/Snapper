//---------------------------------------------------------------------
// <copyright file="BaseMessage.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 
#include "class/_pBaseMessage.h"

namespace snapper { namespace providers 
{

class BaseMessage : public _pBaseMessage
{
public:
    BaseMessage()
    {}

    virtual ~BaseMessage()    
    {}
};

}}

