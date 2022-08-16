
WHAT:
      GraphicsMagick bindings for OCaml.

AUTHOR:
      Copyright (C) 2022 Florent Monnier


NOTICE:
      We switched these bindings from ImageMagick to GraphicsMagick
      because GraphicsMagick is beleaved to be a fork with a more stable API.


REQUISITES:
      OCaml, which can be obtained from:
        https://ocaml.org/

      A build environment with:
       - bash, make

      And ocamlfind to install.

      GraphicsMagick, which you can find at:
        http://www.graphicsmagick.org/

      Or on debian / chrome-book:
        sudo apt-get install graphicsmagick
        sudo apt-get install libgraphicsmagick-dev

      On Mageia:
        su - -c 'urpmi graphicsmagick libgraphicsmagick3 libgraphicsmagick-devel'


VERSIONS:
      This binding (this current verison) has been tested with OCaml version
        '4.14.0' and GraphicsMagick versions '1.3.35', '1.3.36'.

      Please report success or failure with other versions.


INSTALL:
      Run "make" to build the library, and "make install" to install it.


OPAM:
      Install with opam with the command:
        opam install . --working-dir


DOCUMENTATION:
      Run "make doc" to produce the HTML documentation.

      You can also find the html documentation of the last release at:
        http://decapode314.free.fr/ocaml/GraphicsMagick/doc/



HOW TO USE WITH THIS LIBRARY INSTALLED:
  Use in byte-code:
        ocamlc -I $(ocamlfind query magick)  magick.cma  test.ml -o test.byte

  Use in native-code:
        ocamlopt -I $(ocamlfind query magick)  magick.cmxa test.ml -o test.opt

  Use in interactive-mode:
        ocaml -I $(ocamlfind query magick)  magick.cma

  Use in script-mode:
        ocaml -I $(ocamlfind query magick)  magick.cma  test.ml
     or
        chmod u+x test.ml
        ./test.ml image.png
     with the 3 first lines:
        #!/usr/bin/env ocaml
        #directory "+magick"
        #load "magick.cma"




LICENSE:
      This library is distributed under the terms of the Zlib license:

      Permission is granted to anyone to use this software for any purpose,
      including commercial applications, and to modify it and redistribute it
      freely.
    
      This software is provided "AS-IS", without any express or implied
      warranty.  In no event will the authors be held liable for any damages
      arising from the use of this software.

      You should have received a copy of the Zlib license along with
      this program in the file 'LICENSE.txt';
      if not, you can find it on the web at:
        https://opensource.org/licenses/Zlib



BUGS:
      Please report bugs.

