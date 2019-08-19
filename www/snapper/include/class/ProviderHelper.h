//---------------------------------------------------------------------
// <copyright file="ProviderHelper.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------
#pragma once 
#include <www/engine/request_context.h>

#define RF_TYPE_PCIKEY      1
#define RF_TYPE_FUNKEY      2

#define SDR_IDX_RECORD_TYPE         3
#define SDR_IDX_RECORD_LEN          4
#define SDR_IDX_OWNER_ID            5
#define SDR_IDX_OWNER_LUN           6
#define SDR_IDX_SENSOR_NUMBER       7
#define SDR_IDX_ENTITY_ID           8
#define SDR_IDX_ENTITY_INST         9
#define SDR_IDX_SENSOR_TYPE         12
#define SDR_IDX_READING_TYPE        13
#define SDR_IDX_ASSERT_THR_MASK_1   14
#define SDR_IDX_ASSERT_THR_MASK_2   15
#define SDR_IDX_DEASSERT_THR_MASK_1 16
#define SDR_IDX_DEASSERT_THR_MASK_2 17
#define SDR_IDX_READABLE_THR        18
#define SDR_IDX_SETTABLE_THR        19
#define SDR_IDX_UNIT1               20
#define SDR_IDX_UNIT2               21
#define SDR_IDX_NOMINAL_READING     31
#define SDR_IDX_ID                  32
#define SDR_IDX_MAX_READING         34
#define SDR_IDX_MIN_READING         35


#define SDR_IDX_TYPE1_SENSOR_ID_LEN 47
#define SDR_IDX_TYPE1_SENSOR_ID   48
#define SDR_IDX_TYPE2_SENSOR_ID_LEN  31
#define SDR_IDX_TYPE2_SENSOR_ID   32

namespace snapper { namespace providers 
{

std::string serialize_Task_objs(unsigned int taskid, shared_ptr<::snapper::service::request_context> request);
int GetHostPowerState(unsigned int *powerstate);
std::string tz_rf2aim(std::string rf_tz);
std::string tz_aim2rf(std::string aim_tz);

}}

