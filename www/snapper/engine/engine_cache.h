/*---------------------------------------------------------------------------
//  Copyright (c) 2018-present, Lenovo. All rights reserved.
//  Licensed under BSD, see COPYING.BSD file for details.
//---------------------------------------------------------------------------
*/

#ifndef _ENGINE_CACHE_H
#define _ENGINE_CACHE_H

int CHK_REFRESH_BIT(unsigned char *map, unsigned int type);
void refresh_engine_data();
void prefetch_engine_data(std::shared_ptr <::odata::edm::edm_model> model);
bool is_ready();

#endif
