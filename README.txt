
WHAT:
      This binding is an ImageMagick interface for OCaml.

AUTHOR:
      Copyright (C) 2004 2005 2006 2010 Florent Monnier


NOTICE:
      "ImageMagick" is a registered trademark owned by ImageMagick Studio LLC
      http://tarr.uspto.gov/servlet/tarr?regser=serial&entry=78333969


REQUISITES:
      OCaml, which can be obtained from:
        https://ocaml.org/

      ImageMagick, which you will find at:
        https://imagemagick.org/archive/releases/

      A build environment with:
       - bash, make, sed, install


VERSIONS:
      This binding (this current verison) has been tested with OCaml version
        '4.14.0' and ImageMagick version '7.0.8'.

      Previous versions of this binding have been tested with OCaml versions
        '3.08.4', '3.09.0', '3.09.2', '3.11.1' and '3.11.2' and ImageMagick versions
        '6.2.4', '6.2.5', '6.2.6', '6.5.7' and '6.6.1'.

      The old versions of this binding are still available at:
        http://decapode314.free.fr/ocaml/ImageMagick/IM-old.html

      Please report success or failure with other versions.

BETA:
      The interface to ImageMagick for OCaml is still in beta developement
      and I have had very few feedback about success or failure from users yet,
      so you should consider it as experimental and use it at your own risks!
      Be warn that the name of the functions and the labeling may change too,
      and you can also make requests for changes.

BUGS:
      As I don't want you to be afraid by theese, I have put the bugs
      descriptions at the end of this file :-)


INSTALL:
      Run "make" to build the library, and "make install" to install it.

OPAM:
      Install with opam with the command:
        opam install . --working-dir

TEST:
      Run "make test" to run the examples in the 'examples' directory,
      or "make test IMAGE=some_img.png" with an other black and white image
      or logo.

DOCUMENTATION:
      Run "make doc" to produce the HTML documentation.

      You can also find the html documentation of the last release at:
        http://decapode314.free.fr/ocaml/ImageMagick/doc/


TODO:
      Next steps with OCaml-libMagick will be to improve the functional module.
      Enhance the scripts to generate the 'imagemagick_list.c' file.
      Wrapping not just the MagickCore but the MagickWand API too (well maybe...)
      Trying to make this interface compatible with GraphicsMagick?
      Use the OCaml BigArray module to improve the interoperability between 
      the OCaml and the ImageMagick worlds.

WIZARD:
      If you wish to thank the author of ImageMagick, you can consider sending
      to him a picture postcard of the area where you live. Send postcards to:
          ImageMagick Studio LLC
          P.O. Box 40
          Landenberg, PA  19350
          USA
      He is also interested in receiving currency or stamps from around the world
      for his collection.


CONTRIBUTORS:
      Thanks to Matthieu Dubuget for his help to write the first Makefile with 
        OCamlMakefile, and for his help to resolve the dependencies of compilation.
      Thanks to Hugo Heuzard for various fixes for the Makefile.
      Thanks to John Cristy for answering ALL my questions about the MagickCore API.
      Thanks to Fabrice Le Fessant <fabrissimo@gmail.com> for having found bugs
        with allocated values not registered with CAMLlocal.
      Thanks to Christophe Troestler <Christophe.Troestler@umh.ac.be> for his help 
        with big arrays.
      Thanks to Bruspal for his book about the C language.
      Thanks to all the guys of fr.comp.lang.caml who have answered to my questions.
      Thanks to the authors of OCaml for this wonderfull language and
        thanks to the authors of ImageMagick for this wonderfull library.



HOW TO USE IN THE BUILD DIRECTORY:
  Use in byte-code:
        ocamlc -I . magick.cma  test.ml -o test.byte

  Use in native-code:
        ocamlopt -I . magick.cmxa test.ml -o test.opt

  Use in interactive-mode:
        ocaml -I . magick.cma

  Use in script-mode:
        ocaml -I . magick.cma  test.ml image.png
     or
        chmod u+x test.ml
        ./test.ml image.png
     with the 2 first lines:
        #!/usr/bin/env ocaml
        #load "magick.cma"



HOW TO USE WITH THIS LIBRARY INSTALLED:
  Use in byte-code:
        ocamlc -I $(ocamlfind query magick)  magick.cma  test.ml -o test.byte

  Use in native-code:
        ocamlopt -I $(ocamlfind query magick)  magick.cmxa test.ml -o test.opt

  Use in interactive-mode:
        ocaml -I $(ocamlfind query magick)  magick.cma

  Use in script-mode:
        ocaml -I $(ocamlfind query magick)  magick.cma  test.ml image.png
     or
        chmod u+x test.ml
        ./test.ml image.png
     with the 3 first lines:
        #!/usr/bin/env ocaml
        #directory "+magick"
        #load "magick.cma"




LICENSE:
      This library is distributed under the terms of the zlib license:

      This software is provided 'as-is', without any express or implied
      warranty.  In no event will the authors be held liable for any damages
      arising from the use of this software.

      Permission is granted to anyone to use this software for any purpose,
      including commercial applications, and to alter it and redistribute it
      freely.
    
      You should have received a copy of the Zlib license along with
      this program in the file 'LICENSE.txt';
      if not, you can find it on the web at:
        https://opensource.org/licenses/Zlib



KNOWN BUGS:
   MINOR:
      Images added into image lists are pointers, so if the image is not used
      after it has been added into the list it could be garbage collected while
      the list still points to it. As a temporary fix, use the function no_op
      (see the documentation for more details).

   MAJOR:
      The DrawInfo structure is not freed with DestroyDrawInfo() at the end of
      the draw_* functions, because it sometimes produces segfaults, I don't
      know why, in fact it should not, so I have leaved the DestroyDrawInfo()
      calls commented in the source, but perhaps this could lead to a memory
      leak, but I have never experienced such a problem yet though, even with
      big long time living scripts with lots of images loaded.
      It is possible to enable the free() of the (DrawInfo *) structures with 
      setting MAKE_DESTROY_DRAWINFO to 1.
      Please report success or failure related to this issue.


