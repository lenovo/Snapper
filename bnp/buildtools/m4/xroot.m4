#-------------------------------------------------------------------------
# Copyright (c) 2018-present, Lenovo. All rights reserved. 
# Licensed under BSD, see COPYING.BSD file for details.
#---------------------------------------------------------------------------

AM_COND_IF(BLD_X86,XROOT=/)
AC_SUBST(XROOT)
