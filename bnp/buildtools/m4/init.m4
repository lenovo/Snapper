#-------------------------------------------------------------------------
# Copyright (c) 2018-present, Lenovo. All rights reserved. 
# Licensed under BSD, see COPYING.BSD file for details.
#---------------------------------------------------------------------------

#--------------------------------------------------------------------
AC_INIT(BMC, 1.0.0, support@lenovo.com)
AC_CONFIG_AUX_DIR([../bnp/buildtools/m4/config])
AM_INIT_AUTOMAKE([-Wall -Werror foreign -Wno-portability subdir-objects])
AM_SILENT_RULES([yes])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([../bnp/buildtools/m4])

#--------------------------------------------------------------------
AM_PROG_LIBTOOL
AC_PROG_CC
AC_PROG_CXX
LT_INIT([shared])

#--------------------------------------------------------------------
BMC_RULES="\$(abs_top_srcdir)/../bnp/buildtools/bmc-rules.mk"
AC_SUBST(BMC_RULES)

#--------------------------------------------------------------------
AM_CONDITIONAL(BLD_X86,  [test "${host_cpu}"  = "i686" -o "${host_cpu}"  = "x86_64" ])
AM_CONDITIONAL(BLD_SH4,  [test "${host_cpu}"  = "sh4"])
AM_CONDITIONAL(BLD_ARM,  [test "${host_cpu}"  = "arm"])

AM_COND_IF(BLD_X86,IS_TGT_X86=1,IS_TGT_X86=0)
AM_COND_IF(BLD_SH4,IS_TGT_SH4=1,IS_TGT_SH4=0)
AM_COND_IF(BLD_ARM,IS_TGT_ARM=1,IS_TGT_ARM=0)
AC_SUBST(IS_TGT_X86)
AC_SUBST(IS_TGT_SH4)
AC_SUBST(IS_TGT_ARM)

#--------------------------------------------------------------------
STRICT=1
AC_SUBST(STRICT)


