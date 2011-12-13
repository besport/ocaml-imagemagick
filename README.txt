
WHAT:
      This binding is an ImageMagick interface for Objective Caml.

AUTHOR:
      Copyright (C) 2004 2005 2006 2010 Florent Monnier <fmonnier@linux-nantes.org>


LICENSE:
      This binding is released under the GNU General Public Licence.
      (The ImageMagick's license is compatible with the GPL.)
      The licence is in the file "LICENSE_GPL.txt" or on the web:
        http://www.fsf.org/licensing/licenses/gpl.html


NOTICE:
      "ImageMagick" is a registered trademark owned by ImageMagick Studio LLC
      http://tarr.uspto.gov/servlet/tarr?regser=serial&entry=78333969


REQUISITES:
      Objective Caml, which can be obtained from:
       - http://caml.inria.fr/ocaml/
      ImageMagick, which you will find at:
       - http://www.imagemagick.org/script/download.php
      A build environment with:
       - bash, make, sed, install


VERSIONS:
      This binding (this current verison) has been tested with OCaml version
        '3.11.2' and ImageMagick version '6.6.1-5'.
      Previous versions of this binding have been tested with OCaml versions
        '3.08.4', '3.09.0', '3.09.2' and '3.11.1' and ImageMagick versions
        '6.2.4', '6.2.5', '6.2.6' and '6.5.7'.
      The old versions of this binding are still available at:
        http://www.linux-nantes.fr.eu.org/~fmonnier/OCaml/IM-old.php
      Please report success or failure with other versions.
      If you encounter problems to compile from sources, email me and
        I will make a static binary available.

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

STATIC:
      If you wish a static version, just follow the instructions in the Makefile.

TEST:
      Run "make test" to run the examples in the 'examples' directory,
      or "make test IMAGE=some_img.png" with an other black and white image
      or logo.

DOCUMENTATION:
      Run "make doc" to produce the HTML documentation.

      You can also find the html documentation of the last release at:
      http://www.linux-nantes.org/~fmonnier/OCaml/ImageMagick/IM-doc/

THREADS:
      For threads issues, read this:
      http://www.imagemagick.org/script/architecture.php#threads

TODO:
      Next steps with OCaml-libMagick will be to improve the functional module.
      Enhance the scripts to generate the 'imagemagick_list.c' file.
      Wrapping not just the MagickCore but the MagickWand API too (well maybe...)
      Trying to make this interface compatible with GraphicsMagick.
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

THANKS:
      Thanks to Matthieu Dubuget for his help to write the first Makefile with 
        OCamlMakefile, and for his help to resolve the dependencies of compilation.
      Thanks to John Cristy for answering ALL my questions about the MagickCore API.
      Thanks to Fabrice Le Fessant <fabrissimo@gmail.com> for having found bugs
        with allocated values not registered with CAMLlocal.
      Thanks to Christophe Troestler <Christophe.Troestler@umh.ac.be> for his help 
        with big arrays.
      Thanks to Bruspal for his book about the C language.
      Thanks to all the guys of fr.comp.lang.caml who have answered to my questions.
      Thanks to the authors of Objective Caml for this wonderfull language and 
        thanks to the authors of ImageMagick for this wonderfull library.



HOW TO USE IN THE BUILD DIRECTORY:
  Use in byte-code:
        ocamlc bigarray.cma magick.cma  test.ml -o test.run

  Use in native-code:
        ocamlopt bigarray.cmxa magick.cmxa test.ml -o test.opt

  Use in interactive-mode:
        ocaml bigarray.cma magick.cma

  Use in script-mode:
        ocaml bigarray.cma magick.cma  test.ml image.png
     or
        chmod u+x test.ml
        ./test.ml image.png
     with the 2 first lines:
        #!/usr/bin/env ocaml
        #load "magick.cma"



HOW TO USE WITH THIS LIBRARY INSTALLED:
  Use in byte-code:
        ocamlc -I +libMagick bigarray.cma magick.cma  test.ml -o test.run

  Use in native-code:
        ocamlopt -I +libMagick bigarray.cma magick.cmxa test.ml -o test.opt

  Use in interactive-mode:
        ocaml -I +libMagick bigarray.cma magick.cma

  Use in script-mode:
        ocaml -I +libMagick bigarray.cma magick.cma  test.ml image.png
     or
        chmod u+x test.ml
        ./test.ml image.png
     with the 3 first lines:
        #!/usr/bin/env ocaml
        #directory "+libMagick" ;;
        #load "magick.cma" ;;




COPYING:
      This program is free software; you can redistribute it and/or
      modify it under the terms of the GNU General Public License
      as published by the Free Software Foundation; either version 2
      of the License, or (at your option) any later version.
    
      This program is distributed in the hope that it will be useful,
      but WITHOUT ANY WARRANTY; without even the implied warranty of
      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
      See the GNU General Public License for more details.
    
      You should have received a copy of the GNU General Public
      License along with this program in the file 'LICENSE_GPL.txt';
      if not, you can find it on the web at:
        http://www.fsf.org/licensing/licenses/gpl.html



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

   MEDIUM:
      Imper in french sounds close to "impaire" which could be understood like
      odd or the cloth you wear when it's raining out, so you can stay behind 
      the computer ;)
      If you really prefer fun programming, you won't understand why this part
      of the binding, since for imperative the wand api should be chosen.
      When to fix all this arround, just put your hands in ;)


