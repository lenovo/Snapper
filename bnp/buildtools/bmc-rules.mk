#-------------------------------------------------------------------------
# Copyright (c) 2018-present, Lenovo. All rights reserved. 
# Licensed under BSD, see COPYING.BSD file for details.
#---------------------------------------------------------------------------

#---------------------------------------------------------------------------
TOP_DIR=$(shell realpath $(abs_top_srcdir)/..)
COMP_DIR=$(shell realpath $(abs_top_srcdir))
SRC_DIR=$(shell realpath $(srcdir))
COMP_NAME=$(shell basename $(COMP_DIR))
BNP_DIR=$(TOP_DIR)/bnp/buildtools
EXPORT_DIR=$(TOP_DIR)/export
STUB_DIR=$(TOP_DIR)/www/stublib
EXPORT_INCDIR=$(EXPORT_DIR)/include/$(COMP_NAME)/$(EXPORT_SUBDIR)
EXPORT_LIBDIR=$(EXPORT_DIR)/lib/$(host_cpu)
LIBLIST_DIR=$(TOP_DIR)/pkgsrc-$(host_cpu)/liblist
PKGSRC_DIR=$(TOP_DIR)/pkgsrc-$(host_cpu)/$(PKGSRC_TGT)
INSTALL_SCRIPT=$(BNP_DIR)/pkgsrc_install
PREPARE_SCRIPT=$(BNP_DIR)/prep_autotools
LIBLIST_SCRIPT=$(BNP_DIR)/lib_list
LIBSMRT_SCRIPT=$(BNP_DIR)/lib_smart
ROOTFS_SCRIPT=$(BNP_DIR)/install_rootfs
CHKSRC_SCRIPT=$(BNP_DIR)/check-src
XDO=$(BNP_DIR)/xdo
prefix=$(PKGSRC_DIR)
INSTALL_FILE=@export BMC_SRCDIR=$(srcdir);export BMC_TGTDIR=$(PKGSRC_DIR);$(INSTALL_SCRIPT)
ARCH=$(host_cpu)
export BMC_TGTDIR=$(PKGSRC_DIR)
SUBCOMP_NAME=$(COMP_NAME)$(shell echo $(PWD) | sed "s@$(abs_top_builddir)@@")

Color_Off='\e[0m'       # Text Reset
BWhite='\e[1;37m'       # White
On_Red='\e[41m'         # Red

#---------------------------------------------------------------------------
COMPLIBS_BASIC=

#---------------------------------------------------------------------------
ifeq ($(IS_TGT_X86),1)
GNUINC_DIRS=-I$(XROOT)/usr/include
GNULIB_DIRS=-L$(XROOT)/lib/i386-linux-gnu -L$(XROOT)/usr/lib/i386-linux-gnu
endif


#---------------------------------------------------------------------------
ifeq ($(STRICT),1)
#AM_CPPFLAGS    =   -Werror -Wshadow
AM_CPPFLAGS =   -Werror -DIMM_STRICT=1 -Wno-error=shadow
endif
AM_CPPFLAGS     += $(ELIE_CPPFLAGS) 
#AM_CPPFLAGS     += -Wformat-security -Wformat-nonliteral -Wformat=2 -Wall
AM_CPPFLAGS     += -fstack-protector -D_FORTIFY_SOURCE=2
AM_CPPFLAGS     += -D__LITTLE_ENDIAN__
AM_CPPFLAGS     += -D__SIM_X86__
ifeq ($(IMM_DEBUG),1)
AM_CPPFLAGS 	+= -g
endif
AM_CPPFLAGS     += -I$(EXPORT_DIR)/include -I$(EXPORT_DIR)/usr/include -I$(STUB_DIR)/include
AM_CPPFLAGS     += -I$(XROOT)/usr/include
AM_CPPFLAGS     += -I$(XROOT)/usr/include/libxml2
AM_CPPFLAGS     += -I$(XROOT)/usr/include/python3.6m
#AM_CPPFLAGS     += -I${SDKTARGETSYSROOT}/usr/include/libxml2
#AM_CPPFLAGS     += $(GNUINC_DIRS)

AM_CPPFLAGS     += $(IMM_CPPFLAGS)

AM_LDFLAGS      += -Wl,-rpath=/lib:/usr/lib
AM_LDFLAGS      += -L$(PKGSRC_DIR)/lib -L$(XROOT)/lib -L$(XROOT)/usr/lib $(GNULIB_DIRS) $(COMPLIBS_BASIC)
AM_LDFLAGS      += $(ELIE_LDFLAGS)
AM_LDFLAGS    	+= $(IMM_LDFLAGS)

ifeq ($(IS_TGT_X86),1)
LIBTOOLFLAGS    = --quiet
#LIBTOOLFLAGS    = --debug
else
#LIBTOOLFLAGS    = --quiet -Wnone
LIBTOOLFLAGS    = --debug
endif

# use all the cpus unless we cannot detect any, then default to one cpu
CPUS=$(shell cat /proc/cpuinfo | grep lm | wc -l)
ifeq ("$(CPUS)", "0")
    CPUS=1
endif
#CPUS=1
AM_MAKEFLAGS_EXT= -j $(CPUS)

# allow other targets to build in parallel
ifeq ("$(PARALLEL)","1")
    DATA_MAKEFLAGS_EXT = $(AM_MAKEFLAGS_EXT)
endif

#---------------------------------------------------------------------------
# export a sub_comp dir to enable sub component use its top level dir
ifneq ("$(SUBCOMP_DIR)","")
    export SUBCOMP_DIR
endif

ifneq ("$(SUBCOMP_DIR)","")
    AM_CPPFLAGS  += -I$(SUBCOMP_DIR)/
endif

#---------------------------------------------------------------------------
AM_VERBOSE_INSTALL = $(if $(V),,@echo " INSTALL " $@;)
AM_MK_HUSH = $(if $(V),,@)
AM_CP_HUSH = $(if $(V),v,)
AM_TR_HUSH = $(if $(V),v,)
AM_RM_HUSH = $(if $(V),v,)
AM_ID_HUSH = $(if $(V),v,)
AM_IN_HUSH = $(if $(V),v,)
AM_VV_HUSH = $(if $(V),v,)
AM_CU_HUSH = $(if $(V),V=1,)
AM_SDK_HUSH = $(if $(V),-v,)
AM_SHOW_HUSH = $(if $(V),1,)

#---------------------------------------------------------------------------
check-sdk:
	$(AM_MK_HUSH)test -n "$(BMC_SDK)" || ( echo "!-> No SDK selected in environment.. please build from makebmc environment (or use make_under_sdk wrapper)"; false )

prepare:
	$(AM_MK_HUSH)cd $(COMP_DIR) && $(PREPARE_SCRIPT)

pristine:
	$(AM_MK_HUSH)cd $(COMP_DIR) && $(PREPARE_SCRIPT) -pristine

#---------------------------------------------------------------------------
$(EXPORT_INCDIR):
	$(AM_MK_HUSH)mkdir -p $(EXPORT_INCDIR)

test-recursive:
	$(foreach subdir,$(SUBDIRS),$(MAKE) -C $(subdir) $(AM_MAKEFLAGS) install_incs;)

install_incs-recursive:
	$(AM_MK_HUSH)list='$(SUBDIRS)'; for subdir in $$list; do \
		test "$$subdir" = . || ($(am__cd) $$subdir && $(MAKE) $(AM_MAKEFLAGS) install_incs); \
		test $$? -eq 0 || exit 1; \
	done

incs install_incs:: check-sdk $(EXPORT_INCDIR) install_incs-recursive
	$(AM_MK_HUSH)test -z "$(EXPORT_INCS)" || echo " -> Exporting include files for subcomponent [$(SUBCOMP_NAME)]"
	$(AM_MK_HUSH)test -z "$(SDK_INCS)"    || echo " -> Exporting $(SDK_INC_SRC) include files for subcomponent [$(SUBCOMP_NAME)]"
	$(AM_MK_HUSH)for F in $(EXPORT_INCS); do cp -u -a$(AM_CP_HUSH) $(srcdir)/$$F $(EXPORT_INCDIR); done
	@#$(AM_MK_HUSH)${XDO} 'for F in $(EXPORT_INCS)' 'cp -u -a$(AM_CP_HUSH) $(srcdir)/$$F $(EXPORT_INCDIR)'
	$(AM_MK_HUSH)test -z "$(EXPORT_INCS_HOOK)" || $(MAKE) $(AM_MAKEFLAGS) $(EXPORT_INCS_HOOK) || exit 1

#---------------------------------------------------------------------------
$(EXPORT_LIBDIR):
	$(AM_MK_HUSH)mkdir -p $(EXPORT_LIBDIR)

export_libs-recursive:
	$(AM_MK_HUSH)list='$(SUBDIRS)'; for subdir in $$list; do \
		test "$$subdir" = . || ($(am__cd) $$subdir && $(MAKE) $(AM_MAKEFLAGS) export_libs); \
		test $$? -eq 0 || exit 1; \
	done

export_libs:: $(EXPORT_LIBDIR) export_libs-recursive
	$(AM_MK_HUSH)test -n "$(EXPORT_LIBS)" || echo " -> Exporting libraries for subcomponent [$(SUBCOMP_NAME)]" || true
	$(AM_MK_HUSH)for F in $(EXPORT_LIBS); do cp -a$(AM_CP_HUSH) $$F $(EXPORT_LIBDIR); done


#---------------------------------------------------------------------------
install_libs-recursive:
	$(AM_MK_HUSH)list='$(SUBDIRS)'; for subdir in $$list; do \
		($(am__cd) $$subdir && $(MAKE) $(AM_MAKEFLAGS) install_libs); \
		test $$? -eq 0 || exit 1; \
	done

libs install_libs: check-sdk install_libs-recursive
	$(AM_MK_HUSH)test -z "$(lib_LTLIBRARIES)"    || echo " -> Installing libraries for subcomponent [$(SUBCOMP_NAME)]"
	$(AM_MK_HUSH)test -z "$(lib_LTLIBRARIES)"    || $(MAKE) $(AM_MAKEFLAGS) $(AM_MAKEFLAGS_EXT) install-libLTLIBRARIES || exit 1
	$(AM_MK_HUSH)test -z "$(noinst_LTLIBRARIES)" || $(MAKE) $(AM_MAKEFLAGS) $(AM_MAKEFLAGS_EXT) $(noinst_LTLIBRARIES)  || exit 1
	$(AM_MK_HUSH)test -z "$(noinst_LIBRARIES)"   || $(MAKE) $(AM_MAKEFLAGS) $(AM_MAKEFLAGS_EXT) $(noinst_LIBRARIES)    || exit 1
	$(AM_MK_HUSH)test -z "$(INSTALL_LIBS_HOOK)"  || $(MAKE) $(AM_MAKEFLAGS) $(INSTALL_LIBS_HOOK)   || exit 1
	$(AM_MK_HUSH)test -z "$(lib_LTLIBRARIES)"    || $(LIBLIST_SCRIPT) $(COMP_NAME)  $(LIBLIST_DIR) $(lib_LTLIBRARIES)
	$(AM_MK_HUSH)test -z "$(lib_LTLIBRARIES)"    || $(LIBSMRT_SCRIPT) CREATE $(PKGSRC_DIR) $(LIBLIST_DIR) $(lib_LTLIBRARIES)
	$(AM_MK_HUSH)test -z '$(TBD)'                || echo -e "${BWhite}${On_Red}\r!!! TBD !!! -> $(TBD) (`pwd | awk -F/ '{print $$(NF-3)\"/\"$$(NF-1)\"/\"$$(NF)}'`) !!! TBD !!!${Color_Off}"


#---------------------------------------------------------------------------
custom-recursive:
	$(AM_MK_HUSH)list='$(SUBDIRS)'; for subdir in $$list; do \
		($(am__cd) $$subdir && $(MAKE) $(AM_MAKEFLAGS) custom); \
		test $$? -eq 0 || exit 1; \
	done

custom: check-sdk custom-recursive
	$(AM_MK_HUSH)test -z "$(CUSTOM_TGTS)" || echo " -> Building custom package for subcomponent [$(SUBCOMP_NAME)]"
	$(AM_MK_HUSH)test -z "$(CUSTOM_TGTS)" || $(MAKE) $(AM_MAKEFLAGS) $(CUSTOM_TGTS) || exit 1
	$(AM_MK_HUSH)test -z '$(TBD)'         || echo -e "${BWhite}${On_Red}\r!!! TBD !!! -> $(TBD) (`pwd | awk -F/ '{print $$(NF-3)\"/\"$$(NF-1)\"/\"$$(NF)}'`) !!! TBD !!!${Color_Off}"


#---------------------------------------------------------------------------
prebuilt-recursive:
	$(AM_MK_HUSH)list='$(SUBDIRS)'; for subdir in $$list; do \
		($(am__cd) $$subdir && $(MAKE) $(AM_MAKEFLAGS) install_prebuilt); \
		test $$? -eq 0 || exit 1; \
	done

install_prebuilt: check-sdk prebuilt-recursive
	$(AM_MK_HUSH)test -z "$(PKGSRC_TGT)"  || echo " -> Building prebuilt package for subcomponent [$(SUBCOMP_NAME)]"
	$(AM_MK_HUSH)test -z "$(PKGSRC_TGT)"  || $(MAKE) $(AM_MAKEFLAGS) install-prebuilt || exit 1


#---------------------------------------------------------------------------
install_bins-recursive:
	$(AM_MK_HUSH)list='$(SUBDIRS)'; for subdir in $$list; do \
		($(am__cd) $$subdir && $(MAKE) $(AM_MAKEFLAGS) install_bins); \
		test $$? -eq 0 || exit 1; \
	done

bins install_bins: check-sdk install_bins-recursive
	$(AM_MK_HUSH)echo " -> Building bins for subcomponent [$(SUBCOMP_NAME)]"
	$(AM_MK_HUSH) $(MAKE) $(AM_MAKEFLAGS) $(AM_MAKEFLAGS_EXT) install-exec
	$(AM_MK_HUSH)test -z '$(TBD)' || echo -e "${BWhite}${On_Red}\r!!! TBD !!! -> $(TBD) (`pwd | awk -F/ '{print $$(NF-3)\"/\"$$(NF-1)\"/\"$$(NF)}'`) !!! TBD !!!${Color_Off}"

#---------------------------------------------------------------------------
exec install_exec: install-exec

#---------------------------------------------------------------------------
install_data-recursive:
	$(AM_MK_HUSH)list='$(SUBDIRS)'; for subdir in $$list; do \
		($(am__cd) $$subdir && $(MAKE) $(AM_MAKEFLAGS) install_data); \
		test $$? -eq 0 || exit 1; \
	done

data install_data: check-sdk install_data-recursive
	$(AM_MK_HUSH) test -z "$(LTLIBRARIES)" || echo " --> creating library during DATA target: $(LTLIBRARIES)" 
	$(AM_MK_HUSH) test -z "$(LTLIBRARIES)" || $(MAKE) $(AM_MAKEFLAGS) $(DATA_MAKEFLAGS_EXT) $(LTLIBRARIES) install-data || exit 1
	$(AM_MK_HUSH) test -n "$(LTLIBRARIES)" || $(MAKE) $(AM_MAKEFLAGS) install-data-am install-rootfs || exit 1

#---------------------------------------------------------------------------
.PHONY: rootfs install-rootfs
rootfs install-rootfs:
	$(AM_MK_HUSH)cd $(COMP_DIR) && CP_HUSH=$(AM_CP_HUSH) $(ROOTFS_SCRIPT) $(COMP_NAME) $(SRC_DIR) $(TOP_DIR)/pkgsrc-$(host_cpu)/rootfs

#---------------------------------------------------------------------------
find sym findsym symbol:
	$(AM_MK_HUSH) $(LIBSMRT_SCRIPT) FINDSYM $(LIBLIST_DIR)

#---------------------------------------------------------------------------
tbd-recursive:
	$(AM_MK_HUSH)list='$(SUBDIRS)'; for subdir in $$list; do \
		($(am__cd) $$subdir && $(MAKE) $(AM_MAKEFLAGS) tbd); \
		test $$? -eq 0 || exit 1; \
	done

tbd: tbd-recursive
	$(AM_MK_HUSH)test -z '$(TBD)' || echo -e "${BWhite}${On_Red}\r!!! TBD !!! -> $(TBD) (`pwd | awk -F/ '{print $$(NF-3)\"/\"$$(NF-1)\"/\"$$(NF)}'`) !!! TBD !!!${Color_Off}"


