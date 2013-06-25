# Copyright (C) 2010, Steffen Knollmann
# Released under the terms of the GNU General Public License version 3.

NAME=io

include ../../Makefile.config

.PHONY: all clean dist-clean

sources = io_file.c \
          io_art_header.c \
          io_art.c \
          io_gadget_header.c \
          io_mgadget.c \
          io_gadget.c \
          io_logging.c \
          io_util.c \
          io_artnew.c \
          art.c \
          artHeader.c 

include ../../Makefile.rules

all:
	${MAKE} lib${NAME}.a

clean:
	rm -f lib${NAME}.a $(sources:.c=.o)

dist-clean:
	$(MAKE) clean
	rm -f $(sources:.c=.d)

lib${NAME}.a: $(sources:.c=.o)
	$(AR) -r lib${NAME}.a $(sources:.c=.o)

-include $(sources:.c=.d)
