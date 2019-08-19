#-------------------------------------------------------------------------
# Copyright (c) 2018-present, Lenovo. All rights reserved. 
# Licensed under BSD, see COPYING.BSD file for details.
#---------------------------------------------------------------------------

#---------------------------------------------------------------------------
PKGSRC_TGT = rootfs


#---------------------------------------------------------------------------
lib_LTLIBRARIES = libstub.la
libstub_la_LDFLAGS = -avoid-version

libstub_la_CPPFLAGS = $(AM_CPPFLAGS) -fPIC
libstub_la_SOURCES = cim_stub.cpp



#---------------------------------------------------------------------------
include $(BMC_RULES)
