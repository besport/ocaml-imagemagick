# Copyright (C) 2022  Florent Monnier
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to modify it and redistribute it
# freely.
#
# This software is provided "AS-IS", without any express or implied warranty.
# In no event will the authors be held liable for any damages arising from
# the use of this software.


# Check the result of the following command to adapt this Makefile
# GraphicsMagick-config --cppflags --ldflags --libs

# $ GraphicsMagick-config --cppflags
# -I/usr/include/GraphicsMagick

# $ GraphicsMagick-config --ldflags
# -L/usr/lib -Wl,--as-needed -Wl,--no-undefined -Wl,-z,relro -Wl,-O1 -Wl,--build-id -Wl,--enable-new-dtags -L/usr/lib

# $ GraphicsMagick-config --libs
# -lGraphicsMagick -llcms2 -lfreetype -lX11 -llzma -lbz2 -lz -lltdl -lm -lpthread

.PHONY: opt

all: magick.cma
opt: magick.cmxa


magick.cmi: magick.mli
	ocamlc -c $<

magick.cmo: magick.ml magick.cmi
	ocamlc -c $<

magick.cmx: magick.ml magick.cmi
	ocamlopt -c $<

magick.cma:  magick.cmo  dllmagick_stubs.so
	ocamlc -a -o $@ $< \
            -dllib -lmagick_stubs \
            -ccopt -L/usr/lib \
            -cclib -lGraphicsMagick

magick.cmxa:  magick.cmx  dllmagick_stubs.so
	ocamlopt -a -o $@ $< \
	    -cclib -lmagick_stubs \
            -ccopt -L/usr/lib \
            -cclib -lGraphicsMagick

magick_stubs.o: magick_stubs.c
	ocamlc -c -I /usr/include/GraphicsMagick $<

dllmagick_stubs.so: magick_stubs.o
	ocamlmklib -o magick_stubs $< \
            -L/usr/lib \
            -lGraphicsMagick

.PHONY: install
install: META magick.cma magick.cmxa
	ocamlfind install magick META \
	    *.cm[ioxa] *.cmx[as] magick.{a,mli} *magick_stubs.{a,so}

.PHONY: uninstall
uninstall:
	ocamlfind remove magick

.PHONY: doc
doc: magick.mli
	mkdir -p doc
	ocamldoc -d doc -html magick.mli

.PHONY: edit
edit:
	vim magick.ml magick.mli magick_stubs.c

clean:
	$(RM) *.[oa] *.so *.cm[ixoat] *.cmx[as]

