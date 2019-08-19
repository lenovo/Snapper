#-------------------------------------------------------------------------
# Copyright (c) 2018-present, Lenovo. All rights reserved. 
# Licensed under BSD, see COPYING.BSD file for details.
#---------------------------------------------------------------------------

#---------------------------------------------------------------------------
PKGSRC_TGT = rootfs
EXPORT_SUBDIR = snapper

#---------------------------------------------------------------------------
SNAPPER_DIR=$(PKGSRC_DIR)/var/www/snapper
SNAPPER_APPDIR=$(SNAPPER_DIR)/app
PYTHON=python

snapperCPPFLAGS=$(AM_CPPFLAGS) -fPIC -Wno-strict-prototypes \
                   -Wno-unused-value \
                   -Wno-unused-variable \
                   -Wno-unused-local-typedefs
snapperLDFLAGS=$(CC) -shared $(AM_LDFLAGS)

RFDIRS = bin schema_xml schema_json openmodules mockup
#---------------------------------------------------------------------------
install-data-local:
	$(AM_MK_HUSH)install -$(AM_IN_HUSH)d $(SNAPPER_DIR)
	$(AM_MK_HUSH)cd $(srcdir) && list='$(RFDIRS)'; for subdir in $$list; do \
		if [ -e  ]; then \
		    $(PYTHON) -m compileall $$subdir > /dev/null; \
			cp -rf $$subdir $(SNAPPER_DIR); \
		fi; \
	done ;

install-exec-local:
	$(AM_MK_HUSH)install -$(AM_IN_HUSH)d $(SNAPPER_APPDIR)
	$(AM_MK_HUSH)cd $(srcdir) && \
	    export INC_DIR=$(EXPORT_DIR)/include; \
	    export CFLAGS="$(snapperCPPFLAGS)"; \
	    export LDSHARED="$(snapperLDFLAGS)"; \
	    $(PYTHON) setup.py build > ./rf.log 2>&1; \
	    if [ $${?} -ne 0 ]; then \
	    echo "******setup.py failed to build snapper code******. Please check $(srcdir)/rf.log"; exit 1; \
	    fi; \
	    $(PYTHON) -m compileall . >> ./rf.log 2>&1; \
	    cp -rf ./build/lib*/app/* $(SNAPPER_APPDIR); find $(SNAPPER_APPDIR) -name "*.pyy" | xargs rm -f


clean-local:
	$(AM_MK_HUSH)cd $(srcdir) && \
		export INC_DIR=$(EXPORT_DIR)/include; \
		$(PYTHON) setup.py clean --all > /dev/null 2>&1; \
		rm build rf.log -rf; \
		(find . -name *.pyc | xargs rm -f)
#---------------------------------------------------------------------------
include $(BMC_RULES)
