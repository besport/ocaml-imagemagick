# +-----------------------------------------------------------------+
# | Copyright (C) 2010  Florent Monnier                             |
# +-----------------------------------------------------------------+
# | This binding aims to provide the ImageMagick methods to OCaml.  |
# +-----------------------------------------------------------------+
# | This program is free software; you can redistribute it and/or   |
# | modify it under the terms of the GNU General Public License     |
# | as published by the Free Software Foundation; either version 2  |
# | of the License, or (at your option) any later version.          |
# |                                                                 |
# | This program is distributed in the hope that it will be useful, |
# | but WITHOUT ANY WARRANTY; without even the implied warranty of  |
# | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the   |
# | GNU General Public License for more details.                    |
# |                                                                 |
# | http://www.gnu.org/licenses/gpl.html                            |
# |                                                                 |
# | You should have received a copy of the GNU General Public       |
# | License along with this program; if not,                        |
# | write to the Free Software Foundation, Inc.,                    |
# | 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA    |
# +-----------------------------------------------------------------+

# path to the MagickCore-config utility
MAGICK_INSTALLED_DIR='/usr/bin/'

MAGICK_PREFIX := $(shell $(MAGICK_INSTALLED_DIR)MagickCore-config --prefix)

MAGICK_CLIBS := $(shell $(MAGICK_INSTALLED_DIR)MagickCore-config --libs)

MAGICK_CLIBS_ := $(shell ocaml mlarg.ml $(MAGICK_CLIBS))

MAGICK_CFLAGS := $(shell $(MAGICK_INSTALLED_DIR)MagickCore-config --cflags)

OCAML_LIB_DIR := $(shell ocamlfind printconf destdir)

MLIM_PREFIX := $(OCAML_LIB_DIR)/libMagick

all: byte opt
byte: magick.cma
opt: magick.cmxa

imagemagick_wrap.o: imagemagick_wrap.c imagemagick_list.h imagemagick.h
	gcc -fPIC -c -I"$(OCAML_LIB_DIR)" $(MAGICK_CFLAGS) imagemagick_wrap.c

imagemagick_list.o: imagemagick_list.c imagemagick.h
	gcc -fPIC -c -I"$(OCAML_LIB_DIR)" $(MAGICK_CFLAGS) imagemagick_list.c

dllimagemagick_stubs.so: imagemagick_wrap.o imagemagick_list.o
	ocamlmklib  -o  imagemagick_stubs  $^  \
	     $(MAGICK_CLIBS)

magick.mli: magick.ml
	ocamlc -i $< > $@

magick.cmi: magick.mli
	ocamlc -c $<

magick.cmo: magick.ml magick.cmi
	ocamlc -c $<

magick.cma:  magick.cmo  dllimagemagick_stubs.so
	ocamlc -a  -o $@  $<  -dllib -limagemagick_stubs \
	     $(MAGICK_CLIBS_)

magick.cmx: magick.ml magick.cmi
	ocamlopt -c $<

magick.cmxa:  magick.cmx  dllimagemagick_stubs.so
	ocamlopt -a  -o $@  $<  -cclib -limagemagick_stubs \
	     $(MAGICK_CLIBS_)

clean:
	rm -f *.[oa] *.so *.cm[ixoa] *.cmxa

install:
	if [ ! -d $(MLIM_PREFIX) ]; then install -d $(MLIM_PREFIX) ; fi
	install	-m 0755	 dllimagemagick_stubs.so  $(MLIM_PREFIX)/
	install	-m 0644 \
	    META        \
	    magick.mli	\
	    magick.cmi	\
	    magick.cma	\
	    magick.cmxa	\
	    magick.a	\
	    libimagemagick_stubs.a	\
	    $(MLIM_PREFIX)/

uninstall:
	rm -f $(MLIM_PREFIX)/*
	rmdir $(MLIM_PREFIX)

IMAGE := image.png

test:
	@echo
	@echo "  Press Q to close images"
	@echo
	ocaml bigarray.cma magick.cma ./examples/example_01.ml $(IMAGE)
	ocaml bigarray.cma magick.cma ./examples/example_02.ml $(IMAGE)
	ocaml bigarray.cma magick.cma ./examples/example_03.ml $(IMAGE)
	ocaml bigarray.cma magick.cma ./examples/example_thumbnail.ml $(IMAGE)
	ocaml bigarray.cma magick.cma ./examples/example_compression.ml $(IMAGE)
	ocaml bigarray.cma magick.cma ./examples/drawing.ml
	@echo
#	@touch ./examples/.t

doc: magick.mli
	if [ ! -d $@ ]; then mkdir $@ ; fi
	ocamldoc  $<  -colorize-code -html  -d $@
clean-doc:
	rm -f doc/*
	rmdir doc/

DIST_VERSION := 0.33
DIST_DIR := OCaml-ImageMagick-$(DIST_VERSION)
EXEMPLE_DIR := $(DIST_DIR)/examples

dist:
	mkdir -p $(DIST_DIR)
	cp \
	    README.txt            \
	    LICENSE_GPL.txt       \
	    Makefile              \
	    imagemagick.h         \
	    imagemagick_list.c    \
	    imagemagick_list.h    \
	    imagemagick_wrap.c    \
	    magick.ml             \
	    magick.mli            \
	    mlarg.ml              \
	    image.png             \
	    $(DIST_DIR)/
	sed -i -e "s/@VERSION@/$(DIST_VERSION)/g" $(DIST_DIR)/imagemagick.h
	sed -e 's/@VERSION@/$(DIST_VERSION)/' META > $(DIST_DIR)/META
	mkdir -p $(EXEMPLE_DIR)
	cp \
	    examples/example_01.ml           \
	    examples/example_02.ml           \
	    examples/example_03.ml           \
	    examples/example_compression.ml  \
	    examples/example_thumbnail.ml    \
	    examples/drawing.ml              \
	    $(EXEMPLE_DIR)/
	tar cf $(DIST_DIR).tar $(DIST_DIR)
	gzip --best $(DIST_DIR).tar
	mv $(DIST_DIR).tar.gz $(DIST_DIR).tgz
	ls -l $(DIST_DIR).tgz

.PHONY: all opt byte clean clean-doc dist install uninstall
