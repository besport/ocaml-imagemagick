# +-----------------------------------------------------------------+
# | Copyright (C) 2010  Florent Monnier                             |
# +-----------------------------------------------------------------+
# | This binding aims to provide the ImageMagick methods to OCaml.  |
# +-----------------------------------------------------------------+
# | This software is provided 'as-is', without any express or       |
# | implied warranty.  In no event will the authors be held liable  |
# | for any damages arising from the use of this software.          |
# |                                                                 |
# | Permission is granted to anyone to use this software for any    |
# | purpose, including commercial applications, and to alter it and |
# | redistribute it freely.                                         |
# +-----------------------------------------------------------------+
# | Contact: Florent Monnier <monnier.florent (at) gmail.com>       |
# +-----------------------------------------------------------------+

# path to the MagickCore-config utility
MAGICK_INSTALLED_BIN := $(shell which MagickCore-config)

MAGICK_PREFIX := $(shell $(MAGICK_INSTALLED_BIN) --prefix)

MAGICK_CLIBS := $(shell $(MAGICK_INSTALLED_BIN) --libs)

MAGICK_CLIBS_ := $(shell ocaml mlarg.ml $(MAGICK_CLIBS))

MAGICK_CFLAGS := $(shell $(MAGICK_INSTALLED_BIN) --cflags)

OCAML_DIR := $(shell ocamlfind printconf stdlib)

all: byte opt
byte: magick.cma
opt: magick.cmxa magick.cmxs

imagemagick_wrap.o: imagemagick_wrap.c imagemagick_list.h imagemagick.h
	gcc -fPIC -c -I"$(OCAML_DIR)" $(MAGICK_CFLAGS) imagemagick_wrap.c

imagemagick_list.o: imagemagick_list.c imagemagick.h
	gcc -fPIC -c -I"$(OCAML_DIR)" $(MAGICK_CFLAGS) imagemagick_list.c

dllimagemagick_stubs.so: imagemagick_wrap.o imagemagick_list.o
	ocamlmklib  -o  imagemagick_stubs  $^  $(MAGICK_CLIBS)

magick.mli: magick.ml
	ocamlc -i $< > $@

magick.cmi: magick.mli
	ocamlc -c $<

magick.cmo: magick.ml magick.cmi
	ocamlc -c $<

magick.cma:  magick.cmo  dllimagemagick_stubs.so
	ocamlc -a  -o $@  $<  -dllib -limagemagick_stubs $(MAGICK_CLIBS_)

magick.cmx: magick.ml magick.cmi
	ocamlopt -c $<

magick.cmxa:  magick.cmx  dllimagemagick_stubs.so
	ocamlopt -a  -o $@  $<  -cclib -limagemagick_stubs $(MAGICK_CLIBS_)

magick.cmxs: magick.cmxa  dllimagemagick_stubs.so
	ocamlopt -shared -linkall -I ./ -o $@  $<  -cclib -limagemagick_stubs $(MAGICK_CLIBS_)


clean:
	rm -f *.[oa] *.so *.cm[ixoa] *.cmx[as]

install:
	ocamlfind install magick META \
	    magick.mli	\
	    magick.cmi	\
	    magick.cma	\
	    magick.cmxa	\
	    magick.cmxs	\
	    magick.a	\
	    dllimagemagick_stubs.so \
	    libimagemagick_stubs.a

uninstall:
	ocamlfind remove magick

IMAGE := image.png

test: magick.cma
	@echo
	@echo "  Press Q to close images"
	@echo
	ocaml -w -6 -I . magick.cma ./examples/example_01.ml $(IMAGE)
	ocaml -w -6 -I . magick.cma ./examples/example_02.ml $(IMAGE)
	ocaml -w -6 -I . magick.cma ./examples/example_03.ml $(IMAGE)
	ocaml -w -6 -I . magick.cma ./examples/example_thumbnail.ml $(IMAGE)
	ocaml -w -6 -I . magick.cma ./examples/example_compression.ml $(IMAGE)
	ocaml -w -6 -I . magick.cma ./examples/drawing.ml
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
	    LICENSE.txt           \
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
