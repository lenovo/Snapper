//---------------------------------------------------------------------
// <copyright file="_pResource.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

        enum PowerState 
        {
            PowerState_On,
            PowerState_Off,
            PowerState_PoweringOn,
            PowerState_PoweringOff,
        };

        enum IndicatorLED 
        {
            IndicatorLED_Lit,
            IndicatorLED_Blinking,
            IndicatorLED_Off,
        };

        enum ResetType 
        {
            ResetType_On,
            ResetType_ForceOff,
            ResetType_GracefulShutdown,
            ResetType_GracefulRestart,
            ResetType_ForceRestart,
            ResetType_Nmi,
            ResetType_ForceOn,
            ResetType_PushPowerButton,
            ResetType_PowerCycle,
        };

        enum Health 
        {
            Health_OK,
            Health_Warning,
            Health_Critical,
        };

        enum State 
        {
            State_Enabled,
            State_Disabled,
            State_StandbyOffline,
            State_StandbySpare,
            State_InTest,
            State_Starting,
            State_Absent,
            State_UnavailableOffline,
            State_Deferring,
            State_Quiesced,
            State_Updating,
        };

