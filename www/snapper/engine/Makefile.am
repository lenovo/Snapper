#-------------------------------------------------------------------------
# Copyright (c) 2018-present, Lenovo. All rights reserved. 
# Licensed under BSD, see COPYING.BSD file for details.
#---------------------------------------------------------------------------

#---------------------------------------------------------------------------
PKGSRC_TGT = rootfs
EXPORT_SUBDIR = engine

#---------------------------------------------------------------------------
lib_LTLIBRARIES = libsnapper_engine.la libsnapper_provider.la libsnapper_datainterface.la libsnapper_jwt.la librfmon_clt.la
libsnapper_engine_la_LDFLAGS = -avoid-version
libsnapper_provider_la_LDFLAGS = -avoid-version
libsnapper_datainterface_la_LDFLAGS = -avoid-version
libsnapper_jwt_la_LDFLAGS = -avoid-version
librfmon_clt_la_LDFLAGS = -avoid-version

bin_PROGRAMS = snapper_autogen_schema snapper_autogen_msgreg snapper_autogen_privreg
#               snapper_monitor
#               rf_update


EXPORT_INCS = \
		engine_api.h \
		topology.h \
		request_context.h \
		request_handler.h \
		rf_shm_session.h \
		rf_debug.h \
		rf_engine_error.h \
		protocol.h \
		json_cache.h \
		cache_common.h \
		datainf/BSONCache.h \
		jwt/rf_jwt.h \
		monitor/rfmon_clt.h \
		monitor/eventing.h \
		helper/helpercmn.h

#---------------------------------------------------------------------------
SNAPPER_DIR=$(PKGSRC_DIR)/var/www/snapper
ODATA_SUPPRESSIONS = -std=c++11 -fno-strict-aliasing \
					-Werror  \
					-Wno-unknown-pragmas \
					-Wno-reorder \
					-Wno-unused-function \
					-Wmissing-format-attribute \
					-Wno-attributes \
					-Wno-char-subscripts \
					-Wno-sign-compare \
					-Wno-parentheses \
					-Wno-unused-variable \
					-Wno-deprecated \
					-Wno-return-type \
					-Wno-write-strings \
					-Wno-format-nonliteral \
					-Wno-int-to-pointer-cast

libsnapper_engine_la_CPPFLAGS = $(AM_CPPFLAGS) -fPIC -I $(top_srcdir)/snapper/include $(ODATA_SUPPRESSIONS)
libsnapper_engine_la_SOURCES = \
  engine_api.cpp \
  engine_cache.cpp \
  request_context.cpp \
  request_handler.cpp \
  authorization.cpp \
  sessions.cpp \
  topology.cpp \
  rf_shm_session.cpp \
  json_cache.cpp

libsnapper_provider_la_CPPFLAGS = $(AM_CPPFLAGS) -fPIC -I $(top_srcdir)/snapper/include $(ODATA_SUPPRESSIONS)
libsnapper_provider_la_SOURCES = \
  providers/base/SnapperProvider.cpp  \
  providers/base/SnapperMessage.cpp  \
  providers/base/SnapperPrivilege.cpp  \
  providers/base/SnapperRegistry.cpp  \
  providers/base/SnapperSchema.cpp  \
  providers/base/ProviderHelper.cpp \
  providers/MessageRegistryFileCollection.cpp \
  providers/MessageRegistryFile.cpp \
  providers/JsonSchemaFileCollection.cpp \
  providers/JsonSchemaFile.cpp \
  providers/ServiceRoot.cpp \
  providers/Task.cpp \
  providers/TaskCollection.cpp \
  providers/ComputerSystemCollection.cpp \
  providers/ComputerSystem.cpp \
  providers/Chassis.cpp  \
  providers/ChassisCollection.cpp \
  providers/Manager.cpp \
  providers/ManagerCollection.cpp \
  providers/Thermal.cpp  \
  providers/Temperature.cpp \
  providers/Fan.cpp  \
  providers/Power.cpp  \
  providers/Voltage.cpp  \
  providers/PowerControl.cpp  \
  providers/PowerSupply.cpp  \
  providers/Bios.cpp \
  providers/MemoryCollection.cpp \
  providers/Memory.cpp \
  providers/ProcessorCollection.cpp \
  providers/Processor.cpp \
  providers/PCIeFunction.cpp  \
  providers/PCIeDevice.cpp \
  providers/NetworkInterfaceCollection.cpp \
  providers/NetworkInterface.cpp \
  providers/NetworkAdapterCollection.cpp \
  providers/NetworkAdapter.cpp \
  providers/NetworkPortCollection.cpp \
  providers/NetworkPort.cpp \
  providers/EthernetInterfaceCollection.cpp \
  providers/EthernetInterface.cpp \
  providers/Storage.cpp \
  providers/StorageCollection.cpp \
  providers/StorageController.cpp \
  providers/Drive.cpp



#keep oem providers last

libsnapper_datainterface_la_CPPFLAGS = $(AM_CPPFLAGS) -fPIC -I $(top_srcdir)/snapper/include $(ODATA_SUPPRESSIONS)
libsnapper_datainterface_la_SOURCES = \
  datainf/datainf_log.cpp \
  datainf/BSONCache.cpp \
  datainf/BSONCache_Config.cpp \
  datainf/DataInterfaceConfigMgr.cpp \
  datainf/DataInterfaceMgr.cpp \
  datainf/DataInterface.cpp

libsnapper_jwt_la_CPPFLAGS = $(AM_CPPFLAGS) -fPIC -I $(top_srcdir)/snapper/engine/jwt 
libsnapper_jwt_la_SOURCES = jwt/jwt.c jwt/base64.c jwt/jwt-openssl.c jwt/rf_jwt.c
#jwt-gnutls.c

librfmon_clt_la_CPPFLAGS = $(AM_CPPFLAGS) -fPIC
librfmon_clt_la_SOURCES = monitor/rfmon_clt.c


#---------------------------------------------------------------------------

## !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
## !!!!the flags should be equivalent to snapper_core_lib in  ***snapper/pyapp/setup.py***, PLEASE make them consistent !!!!!!!!
## !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
py_snapper_ldflags = \
   -lxml2 -lboost_filesystem -lboost_system -lboost_locale \
   -lodata -lsnapper_engine -lsnapper_provider -lsnapper_datainterface -lsnapper_jwt -lrfmon_clt -ljansson -lstub \
   -lcurl -lboost_thread

snapper_helper_ldflags = \
   -lrfmon_clt  -lstub -luuid -lm -lcurl

## !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
## !!!!the flags should be equivalent to snapper_core_lib in  ***snapper/pyapp/setup.py***, PLEASE make them consistent !!!!!!!!
## !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
py_bin_ldflags = \
   -lxml2 -lboost_filesystem -lboost_system -lboost_locale \
   -lodata -lsnapper_engine -lsnapper_provider -lsnapper_datainterface -lsnapper_jwt -lrfmon_clt -ljansson -lstub \
   -luuid -lpam -lcurl -lboost_thread

#snapper_monitor_CPPFLAGS = $(AM_CPPFLAGS) -fPIC -I $(top_srcdir)/snapper/include $(ODATA_SUPPRESSIONS)
#snapper_monitor_SOURCES  = monitor/monitor.cpp monitor/task_sm.cpp monitor/trigger.cpp monitor/trigger_config.cpp monitor/eventing.cpp
#snapper_monitor_LDFLAGS  = $(AM_LDFLAGS) $(py_snapper_ldflags)

snapper_autogen_schema_CPPFLAGS = $(AM_CPPFLAGS) -fPIC -I $(top_srcdir)/snapper/include $(ODATA_SUPPRESSIONS)
snapper_autogen_schema_SOURCES  = util/snapper_autogen_schema.cpp
snapper_autogen_schema_LDFLAGS  = $(AM_LDFLAGS) $(py_bin_ldflags)

snapper_autogen_msgreg_CPPFLAGS = $(AM_CPPFLAGS) -fPIC -I $(top_srcdir)/snapper/include $(ODATA_SUPPRESSIONS)
snapper_autogen_msgreg_SOURCES  = util/snapper_autogen_msgreg.cpp util/message_registeries_autogen.cpp
snapper_autogen_msgreg_LDFLAGS  = $(AM_LDFLAGS) $(py_bin_ldflags)

snapper_autogen_privreg_CPPFLAGS = $(AM_CPPFLAGS) -fPIC -I $(top_srcdir)/snapper/include $(ODATA_SUPPRESSIONS)
snapper_autogen_privreg_SOURCES  = util/snapper_autogen_privreg.cpp util/privilege_registeries_autogen.cpp
snapper_autogen_privreg_LDFLAGS  = $(AM_LDFLAGS) $(py_bin_ldflags)

#rf_update_CPPFLAGS = $(AM_CPPFLAGS) -fPIC -I $(top_srcdir)/snapper/include $(ODATA_SUPPRESSIONS)
#rf_update_SOURCES  = helper/UpdateFirmware.cpp
#rf_update_LDFLAGS  =  $(AM_LDFLAGS)  $(snapper_helper_ldflags)

#---------------------------------------------------------------------------
install-data-local:
	(find ${PWD} -type f -a \( -name "*.so" -o -name "*.a" -o -name "*.o" \) | xargs ${STRIP} --strip-unneeded )
	$(AM_MK_HUSH)install -$(AM_IN_HUSH)d $(SNAPPER_DIR)
	$(AM_MK_HUSH)cd $(srcdir) && (cp -rf di_metadata $(SNAPPER_DIR) )


#---------------------------------------------------------------------------
include $(BMC_RULES)
