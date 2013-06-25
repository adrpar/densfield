# Copyright (C) 2009, 2010, Steffen Knollmann
# Released under the terms of the GNU General Public License version 3.

###########################################################################
##  NOTE:   Normally you should not be required to edit this file.       ##
##          The setting of compilers and additional programs needed      ##
##          for the build process is done in 'Makefile.config' in        ##
##          this directory.  Compile time options are set in             ##
##          'config.h'.                                                  ##
###########################################################################

ifeq ($(shell if test -e Makefile.config ; then echo "true" ; fi),true)
CONFIG_AVAILABLE=true
else
CONFIG_AVAILABLE=false
endif

REPO_AVAILABLE=false
GITDIR_AVAILABLE=false
  SVNDIR_AVAILABLE=false
ifeq ($(shell if test -d .git ; then echo "true" ; fi),true)
GITDIR_AVAILABLE=true
REPO_AVAILABLE=true
else
  ifeq ($(shell if test -d .svn ; then echo "true" ; fi),true)
  SVNDIR_AVAILABLE=true
  REPO_AVAILABLE=true
  endif
endif

.PHONY: all clean dist-clean doc tarball

ifeq ($(CONFIG_AVAILABLE),true)
include Makefile.config


all:
ifeq ($(REPO_AVAILABLE),true)
	scripts/insert_revision.sh
endif
	$(MAKE) -C src

clean:
	touch version.h
	$(MAKE) -C src clean

dist-clean:
	$(MAKE) -C src dist-clean
	find . -name *.d.[0-9]* -exec rm {} \;
ifeq ($(REPO_AVAILABLE),true)
	rm -f version.h
endif
	rm -f Makefile.config config.h config.log
else
all:
	@echo -n "Please run ./configure first "
	@echo "(check ./configure --help for options)"
endif

ifeq ($(REPO_AVAILABLE),true)
tarball:
	@scripts/insert_revision.sh
	@scripts/make_tar.sh
	@rm -f version.h
endif
