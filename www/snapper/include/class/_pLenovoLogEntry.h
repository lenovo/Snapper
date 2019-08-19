//---------------------------------------------------------------------
// <copyright file="_pLenovoLogEntry.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

        enum LEDState 
        {
            LEDState_Lit,
            LEDState_Blinking,
            LEDState_Off,
            LEDState_ControlPattern,
        };

        enum Serviceable 
        {
            Serviceable_NotServiceable,
            Serviceable_ServiceableByLenovo,
            Serviceable_ServiceableByCustomer,
        };

        enum Source 
        {
            Source_Unknown,
            Source_Other,
            Source_Audit,
            Source_Cooling,
            Source_Power,
            Source_Disks,
            Source_Memory,
            Source_Processors,
            Source_System,
            Source_Test,
        };

