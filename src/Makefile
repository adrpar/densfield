# Copyright (C) 2009, Steffen Knollmann

include ../Makefile.config

.PHONY: all clean dist-clean libutil/libutil.a libio/libio.a libadts/libadts.a

# Define the sources
sources = gen_fields.c \
          mapParticlesToGrid.c \
          normalizeGrids.c \
          writeGrid.c

# Include additional rules
include ../Makefile.rules

# Catch empty call
all:
	$(MAKE) gen_fields

# Cleaning up
clean:
	$(MAKE) -C libadts clean
	$(MAKE) -C libio clean
	$(MAKE) -C libutil clean
	rm -f gen_fields  $(sources:.c=.o)

dist-clean:
	$(MAKE) clean
	$(MAKE) -C libadts dist-clean
	$(MAKE) -C libio dist-clean
	$(MAKE) -C libutil dist-clean
	rm -f $(sources:.c=.d)

# How to build the main programs
gen_fields: $(sources:.c=.o) \
        libadts/libadts.a \
        libio/libio.a \
        libutil/libutil.a \
        ../version.h 
	$(CC) $(CFLAGS) -o gen_fields $(sources:.c=.o) \
	                          libutil/libutil.a \
	                          libadts/libadts.a \
	                          libio/libio.a \
	                          libutil/libutil.a -lm

# Now include all objects
-include $(sources:.c=.d)

# External dependencies
libadts/libadts.a:
	$(MAKE) -C libadts

libutil/libutil.a:
	$(MAKE) -C libutil

libio/libio.a:
	$(MAKE) -C libio
