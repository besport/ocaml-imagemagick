(* {{{ COPYING *)
(*
 * +-----------------------------------------------------------------+
 * | Copyright (C) 2004 2005 2006 Florent Monnier                    |
 * +-----------------------------------------------------------------+
 * | This binding aims to provide the ImageMagick methods to OCaml.  |
 * +-----------------------------------------------------------------+
 * | 
 * | Permission is hereby granted, free of charge, to any person obtaining a
 * | copy of this software and associated files (the "Software"), to deal in
 * | the Software without restriction, including without limitation the rights
 * | to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * | copies of the Software, and to permit persons to whom the Software is
 * | furnished to do so, subject to the following requests:
 * | 
 * | The above copyright notice and this permission notice may be included in
 * | all copies or substantial portions of the Software.
 * | 
 * | The Software is provided "AS IS", without warranty of any kind, express or
 * | implied, including but not limited to the warranties of merchantability,
 * | fitness for a particular purpose and noninfringement.  In no event shall
 * | the authors or copyright holders be liable for any claim, damages or other
 * | liability, whether in an action of contract, tort or otherwise, arising
 * | from, out of or in connection with the Software or the use or other
 * | dealings in the Software.
 * +
 *
 * }}} *)


external sizeof_quantum: unit -> int = "im_sizeof_quantum"
external sizeof_quantum_bit: unit -> int = "im_sizeof_quantum_bit"


type image_handle


(* {{{ root functions *)

(* external constituteimage : int -> int -> string -> image_handle  = "imper_constituteimage" *)

external read_image  : filename:string -> image_handle  = "im_readimage"

(* external freeimage : image_handle -> unit  = "imper_freeimage" *)

(* external newmagickimage : int -> int -> int -> int -> int -> int -> image_handle
                  = "imper_newmagickimage_bytecode" "imper_newmagickimage_native" *)

external get_canvas : width:int -> height:int -> color:string -> image_handle  = "im_getimagecanvas"
external create_image  : width:int -> height:int -> pseudo_format:string -> image_handle  = "im_create_image"

external clone_image : image_handle -> image_handle  = "im_cloneimage"



external write_image : image_handle -> filename:string -> unit  = "im_writeimage"

external display : image_handle -> unit  = "im_displayimages"


(* blobs *)

external image_to_stdout : image_handle -> unit    = "imper_imagetoblob_stdout"
external blob_of_image : image_handle -> int list  = "imper_imagetoblob_bytes"


let dump_to_stdout t_img =
  let rec dumper = function
    oo, [] -> close_out oo
  | oo, b::l -> begin output_byte oo b; dumper(oo,l) end
  in
  dumper(stdout, blob_of_image t_img)
;;


(* get infos on images *)

external get_image_width:   image_handle -> int  = "imper_getimagewidth"
external get_image_height:  image_handle -> int  = "imper_getimageheight"
external get_image_depth:   image_handle -> int  = "imper_getimagedepth"
external get_image_quality: image_handle -> int  = "imper_getimagequality"

external get_image_mimetype:  image_handle -> string  = "imper_getimagemimetype"
external get_image_size:  image_handle -> string  = "imper_getimagesize"

external get_image_colors:  image_handle -> int  = "imper_getimagecolors"
external get_image_colorspace:  image_handle -> int  = "imper_getimagecolorspace"


external ping_image_infos : string -> int * int * int * int * int * string  = "imper_ping_image_infos"
external ping_image : string -> bool  = "imper_ping_image"


(* Please notice that getnumbercolors and getimagehistogram have been swapped
   between the libMagick and the OCaml-binding,
   because getnumbercolors returns an image histogram,
   and getimagehistogram only returns the number of colors. *)
external get_number_colors : image_handle -> int  = "imper_getimagehistogram"
external get_image_histogram : image_handle -> histogram_file:string -> int  = "imper_getnumbercolors"

external get_max_colormap : unit -> int  = "imper_getmaxcolormap"

type image_type =
 | Undefined_image_type
 | Bilevel
 | Grayscale
 | GrayscaleMatte
 | Palette
 | PaletteMatte
 | TrueColor
 | TrueColorMatte
 | ColorSeparation
 | ColorSeparationMatte
 | Optimize

external get_image_type : image_handle -> image_type  = "imper_getimagetype"


let string_of_image_type image_type =
  match image_type with
  | Undefined_image_type -> "Undefined"
  | Bilevel              -> "Bilevel"
  | Grayscale            -> "Grayscale"
  | GrayscaleMatte       -> "GrayscaleMatte"
  | Palette              -> "Palette"
  | PaletteMatte         -> "PaletteMatte"
  | TrueColor            -> "TrueColor"
  | TrueColorMatte       -> "TrueColorMatte"
  | ColorSeparation      -> "ColorSeparation"
  | ColorSeparationMatte -> "ColorSeparationMatte"
  | Optimize             -> "Optimize"


(* }}} *)
(* {{{ types *)


type magick_boolean =
 | MagickFalse
 | MagickTrue

let magick_boolean_of_string str =
  match String.lowercase_ascii str with
  | "false" | "magick-false" | "magickfalse" -> MagickFalse
  | "true"  | "magick-true"  | "magicktrue"  -> MagickTrue
  | _ -> raise Not_found


type noise_type =
 | UndefinedNoise
 | UniformNoise
 | GaussianNoise
 | MultiplicativeGaussianNoise
 | ImpulseNoise
 | LaplacianNoise
 | PoissonNoise



type resize_filter =
 | Undefined_resize_filter
 | Point
 | Box
 | Triangle
 | Hermite
 | Hanning
 | Hamming
 | Blackman
 | Gaussian
 | Quadratic
 | Cubic
 | Catrom
 | Mitchell
 | Lanczos
 | Bessel
 | Sinc


let resize_filter_of_string str =
  match String.lowercase_ascii str with
  | "undefined" -> Undefined_resize_filter
  | "point"     -> Point
  | "box"       -> Box
  | "triangle"  -> Triangle
  | "hermite"   -> Hermite
  | "hanning"   -> Hanning
  | "hamming"   -> Hamming
  | "blackman"  -> Blackman
  | "gaussian"  -> Gaussian
  | "quadratic" -> Quadratic
  | "cubic"     -> Cubic
  | "catrom"    -> Catrom
  | "mitchell"  -> Mitchell
  | "lanczos"   -> Lanczos
  | "bessel"    -> Bessel
  | "sinc"      -> Sinc
  | _           -> Undefined_resize_filter

let resize_filter_of_string' str =
  match String.lowercase_ascii str with
  | "undefined" -> Undefined_resize_filter
  | "point"     -> Point
  | "box"       -> Box
  | "triangle"  -> Triangle
  | "hermite"   -> Hermite
  | "hanning"   -> Hanning
  | "hamming"   -> Hamming
  | "blackman"  -> Blackman
  | "gaussian"  -> Gaussian
  | "quadratic" -> Quadratic
  | "cubic"     -> Cubic
  | "catrom"    -> Catrom
  | "mitchell"  -> Mitchell
  | "lanczos"   -> Lanczos
  | "bessel"    -> Bessel
  | "sinc"      -> Sinc
  | _           -> raise Not_found

let string_of_resize_filter = function
  | Undefined_resize_filter -> "undefined"
  | Point      -> "point"
  | Box        -> "box"
  | Triangle   -> "triangle"
  | Hermite    -> "hermite"
  | Hanning    -> "hanning"
  | Hamming    -> "hamming"
  | Blackman   -> "blackman"
  | Gaussian   -> "gaussian"
  | Quadratic  -> "quadratic"
  | Cubic      -> "cubic"
  | Catrom     -> "catrom"
  | Mitchell   -> "mitchell"
  | Lanczos    -> "lanczos"
  | Bessel     -> "bessel"
  | Sinc       -> "sinc"



type channel_type =
 | Undefined_Channel
 | Red
 | Gray
 | Cyan
 | Green
 | Magenta
 | Blue
 | Yellow
 | Alpha
 | Opacity
 | Black
 | Index
 | All_Channels
 | Default_Channels


let channel_type_of_string str =
  match String.lowercase_ascii str with
  | "default_channels"
  | "default"   -> Default_Channels
  | "red"       -> Red
  | "gray"      -> Gray
  | "cyan"      -> Cyan
  | "green"     -> Green
  | "magenta"   -> Magenta
  | "blue"      -> Blue
  | "yellow"    -> Yellow
  | "alpha"     -> Alpha
  | "opacity"   -> Opacity
  | "black"     -> Black
  | "index"     -> Index
  | "all_channels"
  | "all"       -> All_Channels
  | "undefined_channel"
  | "undefined" -> Undefined_Channel
  | _           -> Default_Channels

let channel_type_of_string' str =
  match String.lowercase_ascii str with
  | "default_channels"
  | "default"   -> Default_Channels
  | "red"       -> Red
  | "gray"      -> Gray
  | "cyan"      -> Cyan
  | "green"     -> Green
  | "magenta"   -> Magenta
  | "blue"      -> Blue
  | "yellow"    -> Yellow
  | "alpha"     -> Alpha
  | "opacity"   -> Opacity
  | "black"     -> Black
  | "index"     -> Index
  | "all_channels"
  | "all"       -> All_Channels
  | "undefined_channel"
  | "undefined" -> Undefined_Channel
  | _           -> raise Not_found


let string_of_channel_type = function
  | Undefined_Channel -> "undefined"
  | Red               -> "red"      
  | Gray              -> "gray"     
  | Cyan              -> "cyan"     
  | Green             -> "green"    
  | Magenta           -> "magenta"  
  | Blue              -> "blue"     
  | Yellow            -> "yellow"   
  | Alpha             -> "alpha"    
  | Opacity           -> "opacity"  
  | Black             -> "black"    
  | Index             -> "index"    
  | All_Channels      -> "all"
  | Default_Channels  -> "default"



type composite_operator =
  | Undefined_composite_operator
  | No_composite_operator
  | Alpha
  | Atop
  | Blend
  | Blur
  | Bumpmap
  | ChangeMask
  | Clear
  | ColorBurn
  | ColorDodge
  | Colorize
  | CopyBlack
  | CopyBlue
  | Copy
  | CopyCyan
  | CopyGreen
  | CopyMagenta
  | CopyAlpha
  | CopyRed
  | CopyYellow
  | Darken
  | DarkenIntensity
  | Difference
  | Displace
  | Dissolve
  | Distort
  | DivideDst
  | DivideSrc
  | DstAtop
  | Dst
  | DstIn
  | DstOut
  | DstOver
  | Exclusion
  | HardLight
  | HardMix
  | Hue
  | In
  | Intensity
  | Lighten
  | LightenIntensity
  | LinearBurn
  | LinearDodge
  | LinearLight
  | Luminize
  | Mathematics
  | MinusDst
  | MinusSrc
  | Modulate
  | ModulusAdd
  | ModulusSubtract
  | Multiply
  | Out
  | Over
  | Overlay
  | PegtopLight
  | PinLight
  | Plus
  | Replace
  | Saturate
  | Screen
  | SoftLight
  | SrcAtop
  | Src
  | SrcIn
  | SrcOut
  | SrcOver
  | Threshold
  | VividLight
  | Xor
  | Stereo


let composite_operator_of_string str_op =
  match String.lowercase_ascii str_op with
  | "undefined"   -> Undefined_composite_operator
  | "no"          -> No_composite_operator

  | "Alpha"            | "alpha"                                  -> Alpha
  | "Atop"             | "atop"                                   -> Atop
  | "Blend"            | "blend"                                  -> Blend
  | "Blur"             | "blur"                                   -> Blur
  | "Bumpmap"          | "bumpmap"                                -> Bumpmap
  | "ChangeMask"       | "change-mask"       | "changemask"       -> ChangeMask
  | "Clear"            | "clear"                                  -> Clear
  | "ColorBurn"        | "color-burn"        | "colorburn"        -> ColorBurn
  | "ColorDodge"       | "color-dodge"       | "colordodge"       -> ColorDodge
  | "Colorize"         | "colorize"                               -> Colorize
  | "CopyBlack"        | "copy-black"        | "copyblack"        -> CopyBlack
  | "CopyBlue"         | "copy-blue"         | "copyblue"         -> CopyBlue
  | "Copy"             | "copy"                                   -> Copy
  | "CopyCyan"         | "copy-cyan"         | "copycyan"         -> CopyCyan
  | "CopyGreen"        | "copy-green"        | "copygreen"        -> CopyGreen
  | "CopyMagenta"      | "copy-magenta"      | "copymagenta"      -> CopyMagenta
  | "CopyAlpha"        | "copy-alpha"        | "copyalpha"        -> CopyAlpha
  | "CopyRed"          | "copy-red"          | "copyred"          -> CopyRed
  | "CopyYellow"       | "copy-yellow"       | "copyyellow"       -> CopyYellow
  | "Darken"           | "darken"                                 -> Darken
  | "DarkenIntensity"  | "darken-intensity"  | "darkenintensity"  -> DarkenIntensity
  | "Difference"       | "difference"                             -> Difference
  | "Displace"         | "displace"                               -> Displace
  | "Dissolve"         | "dissolve"                               -> Dissolve
  | "Distort"          | "distort"                                -> Distort
  | "DivideDst"        | "divide-dst"        | "dividedst"        -> DivideDst
  | "DivideSrc"        | "divide-src"        | "dividesrc"        -> DivideSrc
  | "DstAtop"          | "dstatop"                                -> DstAtop
  | "Dst"              | "dst"                                    -> Dst
  | "DstIn"            | "dst-in"            | "dstin"            -> DstIn
  | "DstOut"           | "dst-out"           | "dstout"           -> DstOut
  | "DstOver"          | "dst-over"          | "dstover"          -> DstOver
  | "Exclusion"        | "exclusion"                              -> Exclusion
  | "HardLight"        | "hard-light"        | "hardlight"        -> HardLight
  | "HardMix"          | "hard-mix"          | "hardmix"          -> HardMix
  | "Hue"              | "hue"                                    -> Hue
  | "In"               | "in"                                     -> In
  | "Intensity"        | "intensity"                              -> Intensity
  | "Lighten"          | "lighten"                                -> Lighten
  | "LightenIntensity" | "lighten-intensity" | "lightenintensity" -> LightenIntensity
  | "LinearBurn"       | "linear-burn"       | "linearburn"       -> LinearBurn
  | "LinearDodge"      | "linear-dodge"      | "lineardodge"      -> LinearDodge
  | "LinearLight"      | "linear-light"      | "linearlight"      -> LinearLight
  | "Luminize"         | "luminize"                               -> Luminize
  | "Mathematics"      | "mathematics"                            -> Mathematics
  | "MinusDst"         | "minus-dst"         | "minusdst"         -> MinusDst
  | "MinusSrc"         | "minus-src"         | "minussrc"         -> MinusSrc
  | "Modulate"         | "modulate"                               -> Modulate
  | "ModulusAdd"       | "modulus-add"       | "modulusadd"       -> ModulusAdd
  | "ModulusSubtract"  | "modulus-subtract"  | "modulussubtract"  -> ModulusSubtract
  | "Multiply"         | "multiply"                               -> Multiply
  | "Out"              | "out"                                    -> Out
  | "Over"             | "over"                                   -> Over
  | "Overlay"          | "overlay"                                -> Overlay
  | "PegtopLight"      | "pegtop-light"      | "pegtoplight"      -> PegtopLight
  | "PinLight"         | "pin-light"         | "pinlight"         -> PinLight
  | "Plus"             | "plus"                                   -> Plus
  | "Replace"          | "replace"                                -> Replace
  | "Saturate"         | "saturate"                               -> Saturate
  | "Screen"           | "screen"                                 -> Screen
  | "SoftLight"        | "soft-light"        | "softlight"        -> SoftLight
  | "SrcAtop"          | "src-atop"          | "srcatop"          -> SrcAtop
  | "Src"              | "src"                                    -> Src
  | "SrcIn"            | "src-in"            | "srcin"            -> SrcIn
  | "SrcOut"           | "src-out"           | "srcout"           -> SrcOut
  | "SrcOver"          | "src-over"          | "srcover"          -> SrcOver
  | "Threshold"        | "threshold"                              -> Threshold
  | "VividLight"       | "vivid-light"                            -> VividLight
  | "Xor"              | "xor"                                    -> Xor
  | "Stereo"           | "stereo"                                 -> Stereo

  | _             -> Undefined_composite_operator


let composite_operator_of_string' str_op =
  match String.lowercase_ascii str_op with
  | "undefined"   -> Undefined_composite_operator
  | "no"          -> No_composite_operator

  | "Alpha"            | "alpha"                                  -> Alpha
  | "Atop"             | "atop"                                   -> Atop
  | "Blend"            | "blend"                                  -> Blend
  | "Blur"             | "blur"                                   -> Blur
  | "Bumpmap"          | "bumpmap"                                -> Bumpmap
  | "ChangeMask"       | "change-mask"       | "changemask"       -> ChangeMask
  | "Clear"            | "clear"                                  -> Clear
  | "ColorBurn"        | "color-burn"        | "colorburn"        -> ColorBurn
  | "ColorDodge"       | "color-dodge"       | "colordodge"       -> ColorDodge
  | "Colorize"         | "colorize"                               -> Colorize
  | "CopyBlack"        | "copy-black"        | "copyblack"        -> CopyBlack
  | "CopyBlue"         | "copy-blue"         | "copyblue"         -> CopyBlue
  | "Copy"             | "copy"                                   -> Copy
  | "CopyCyan"         | "copy-cyan"         | "copycyan"         -> CopyCyan
  | "CopyGreen"        | "copy-green"        | "copygreen"        -> CopyGreen
  | "CopyMagenta"      | "copy-magenta"      | "copymagenta"      -> CopyMagenta
  | "CopyAlpha"        | "copy-alpha"        | "copyalpha"        -> CopyAlpha
  | "CopyRed"          | "copy-red"          | "copyred"          -> CopyRed
  | "CopyYellow"       | "copy-yellow"       | "copyyellow"       -> CopyYellow
  | "Darken"           | "darken"                                 -> Darken
  | "DarkenIntensity"  | "darken-intensity"  | "darkenintensity"  -> DarkenIntensity
  | "Difference"       | "difference"                             -> Difference
  | "Displace"         | "displace"                               -> Displace
  | "Dissolve"         | "dissolve"                               -> Dissolve
  | "Distort"          | "distort"                                -> Distort
  | "DivideDst"        | "divide-dst"        | "dividedst"        -> DivideDst
  | "DivideSrc"        | "divide-src"        | "dividesrc"        -> DivideSrc
  | "DstAtop"          | "dstatop"                                -> DstAtop
  | "Dst"              | "dst"                                    -> Dst
  | "DstIn"            | "dst-in"            | "dstin"            -> DstIn
  | "DstOut"           | "dst-out"           | "dstout"           -> DstOut
  | "DstOver"          | "dst-over"          | "dstover"          -> DstOver
  | "Exclusion"        | "exclusion"                              -> Exclusion
  | "HardLight"        | "hard-light"        | "hardlight"        -> HardLight
  | "HardMix"          | "hard-mix"          | "hardmix"          -> HardMix
  | "Hue"              | "hue"                                    -> Hue
  | "In"               | "in"                                     -> In
  | "Intensity"        | "intensity"                              -> Intensity
  | "Lighten"          | "lighten"                                -> Lighten
  | "LightenIntensity" | "lighten-intensity" | "lightenintensity" -> LightenIntensity
  | "LinearBurn"       | "linear-burn"       | "linearburn"       -> LinearBurn
  | "LinearDodge"      | "linear-dodge"      | "lineardodge"      -> LinearDodge
  | "LinearLight"      | "linear-light"      | "linearlight"      -> LinearLight
  | "Luminize"         | "luminize"                               -> Luminize
  | "Mathematics"      | "mathematics"                            -> Mathematics
  | "MinusDst"         | "minus-dst"         | "minusdst"         -> MinusDst
  | "MinusSrc"         | "minus-src"         | "minussrc"         -> MinusSrc
  | "Modulate"         | "modulate"                               -> Modulate
  | "ModulusAdd"       | "modulus-add"       | "modulusadd"       -> ModulusAdd
  | "ModulusSubtract"  | "modulus-subtract"  | "modulussubtract"  -> ModulusSubtract
  | "Multiply"         | "multiply"                               -> Multiply
  | "Out"              | "out"                                    -> Out
  | "Over"             | "over"                                   -> Over
  | "Overlay"          | "overlay"                                -> Overlay
  | "PegtopLight"      | "pegtop-light"      | "pegtoplight"      -> PegtopLight
  | "PinLight"         | "pin-light"         | "pinlight"         -> PinLight
  | "Plus"             | "plus"                                   -> Plus
  | "Replace"          | "replace"                                -> Replace
  | "Saturate"         | "saturate"                               -> Saturate
  | "Screen"           | "screen"                                 -> Screen
  | "SoftLight"        | "soft-light"        | "softlight"        -> SoftLight
  | "SrcAtop"          | "src-atop"          | "srcatop"          -> SrcAtop
  | "Src"              | "src"                                    -> Src
  | "SrcIn"            | "src-in"            | "srcin"            -> SrcIn
  | "SrcOut"           | "src-out"           | "srcout"           -> SrcOut
  | "SrcOver"          | "src-over"          | "srcover"          -> SrcOver
  | "Threshold"        | "threshold"                              -> Threshold
  | "VividLight"       | "vivid-light"                            -> VividLight
  | "Xor"              | "xor"                                    -> Xor
  | "Stereo"           | "stereo"                                 -> Stereo

  | _             -> raise Not_found



let string_of_composite_operator comp_op =
  match comp_op with
  | Undefined_composite_operator -> "Undefined"
  | No_composite_operator -> "No"
  | Alpha            -> "Alpha"
  | Atop             -> "Atop"
  | Blend            -> "Blend"
  | Blur             -> "Blur"
  | Bumpmap          -> "Bumpmap"
  | ChangeMask       -> "ChangeMask"
  | Clear            -> "Clear"
  | ColorBurn        -> "ColorBurn"
  | ColorDodge       -> "ColorDodge"
  | Colorize         -> "Colorize"
  | CopyBlack        -> "CopyBlack"
  | CopyBlue         -> "CopyBlue"
  | Copy             -> "Copy"
  | CopyCyan         -> "CopyCyan"
  | CopyGreen        -> "CopyGreen"
  | CopyMagenta      -> "CopyMagenta"
  | CopyAlpha        -> "CopyAlpha"
  | CopyRed          -> "CopyRed"
  | CopyYellow       -> "CopyYellow"
  | Darken           -> "Darken"
  | DarkenIntensity  -> "DarkenIntensity"
  | Difference       -> "Difference"
  | Displace         -> "Displace"
  | Dissolve         -> "Dissolve"
  | Distort          -> "Distort"
  | DivideDst        -> "DivideDst"
  | DivideSrc        -> "DivideSrc"
  | DstAtop          -> "DstAtop"
  | Dst              -> "Dst"
  | DstIn            -> "DstIn"
  | DstOut           -> "DstOut"
  | DstOver          -> "DstOver"
  | Exclusion        -> "Exclusion"
  | HardLight        -> "HardLight"
  | HardMix          -> "HardMix"
  | Hue              -> "Hue"
  | In               -> "In"
  | Intensity        -> "Intensity"
  | Lighten          -> "Lighten"
  | LightenIntensity -> "LightenIntensity"
  | LinearBurn       -> "LinearBurn"
  | LinearDodge      -> "LinearDodge"
  | LinearLight      -> "LinearLight"
  | Luminize         -> "Luminize"
  | Mathematics      -> "Mathematics"
  | MinusDst         -> "MinusDst"
  | MinusSrc         -> "MinusSrc"
  | Modulate         -> "Modulate"
  | ModulusAdd       -> "ModulusAdd"
  | ModulusSubtract  -> "ModulusSubtract"
  | Multiply         -> "Multiply"
  | Out              -> "Out"
  | Over             -> "Over"
  | Overlay          -> "Overlay"
  | PegtopLight      -> "PegtopLight"
  | PinLight         -> "PinLight"
  | Plus             -> "Plus"
  | Replace          -> "Replace"
  | Saturate         -> "Saturate"
  | Screen           -> "Screen"
  | SoftLight        -> "SoftLight"
  | SrcAtop          -> "SrcAtop"
  | Src              -> "Src"
  | SrcIn            -> "SrcIn"
  | SrcOut           -> "SrcOut"
  | SrcOver          -> "SrcOver"
  | Threshold        -> "Threshold"
  | VividLight       -> "VividLight"
  | Xor              -> "Xor"
  | Stereo           -> "Stereo"


(* }}} *)


(* {{{ Imperative module *)

module Imper = struct


external plasma_image : image_handle -> x1:int -> y1:int -> x2:int -> y2:int ->
              attenuate:int -> depth:int -> unit
          = "imper_plasmaimage_bytecode"
            "imper_plasmaimage_native"


external flip:      image_handle -> unit  = "imper_flipimage"
external flop:      image_handle -> unit  = "imper_flopimage"
external magnify:   image_handle -> unit  = "imper_magnifyimage"
external minify:    image_handle -> unit  = "imper_minifyimage"
external enhance:   image_handle -> unit  = "imper_enhanceimage"
external trim:      image_handle -> unit  = "imper_trimimage"
external despeckle: image_handle -> unit  = "imper_despeckle"


external negate :  image_handle -> grayscale:magick_boolean -> unit  = "imper_negateimage"
let negate t_img ?(grayscale=MagickFalse) () = negate t_img ~grayscale


external contrast:  image_handle -> sharpen:magick_boolean -> unit = "imper_contrastimage"
external equalize:  image_handle -> unit                           = "imper_equalizeimage"
external normalize: image_handle -> unit                           = "imper_normalizeimage"
external white_threshold: image_handle -> threshold:string -> unit = "imper_whitethresholdimage"
external black_threshold: image_handle -> threshold:string -> unit = "imper_blackthresholdimage"
external cyclecolormap: image_handle -> displace:int -> unit       = "imper_cyclecolormapimage"
external solarize:  image_handle -> threshold:float -> unit        = "imper_solarizeimage"

external modulate' : image_handle -> factors:string -> unit   = "imper_modulateimage"

let modulate t_img ?(brightness=100) ?(saturation=100) ?(hue=100) () =
  let br = string_of_int  brightness
  and sa = string_of_int  saturation
  and hu = string_of_int  hue
  in
  modulate' t_img ~factors:(br ^","^ sa ^","^ hu)



external blur :  image_handle -> radius:float -> sigma:float -> unit = "imper_blurimage"
let blur t_img ?(radius=0.0) ~sigma () = blur t_img ~radius ~sigma

external gaussian_blur : image_handle -> radius:float -> sigma:float -> unit = "imper_gaussianblurimage"
let gaussian_blur t_img ?(radius=0.0) ~sigma () = gaussian_blur t_img ~radius ~sigma

external motion_blur :  image_handle -> radius:float -> sigma:float -> angle:float -> unit = "imper_motionblurimage"
let motion_blur t_img ?(radius=0.0) ~sigma ~angle () = motion_blur t_img ~radius ~sigma ~angle

external charcoal :  image_handle -> radius:float -> sigma:float -> unit = "imper_charcoalimage"
let charcoal t_img ?(radius=0.0) ~sigma () = charcoal t_img ~radius ~sigma

external edge :  image_handle -> radius:float -> unit  = "imper_edgeimage"

external emboss :  image_handle -> radius:float -> sigma:float -> unit = "imper_embossimage"
let emboss t_img ?(radius=0.0) ~sigma () = emboss t_img ~radius ~sigma

external implode:       image_handle -> amount:float -> unit       = "imper_implodeimage"
external oilpaint:      image_handle -> radius:float -> unit       = "imper_oilpaintimage"
external roll:          image_handle -> x:int -> y:int -> unit     = "imper_rollimage"

external shade: image_handle -> gray:magick_boolean -> azimuth:float -> elevation:float -> unit = "imper_shadeimage"
let shade t_img ?(gray=MagickTrue) ~azimuth ~elevation () = shade t_img ~gray ~azimuth ~elevation

external spread : image_handle -> radius:float -> unit    = "imper_spreadimage"
external swirl :  image_handle -> degrees:float -> unit   = "imper_swirlimage"

external sharpen: image_handle -> float -> float -> unit  = "imper_sharpenimage"
let sharpen t_img ?(radius=0.0) ~sigma () = sharpen t_img radius sigma

external unsharpmask : image_handle -> radius:float -> sigma:float -> amount:float -> threshold:float -> unit
                                                                        = "imper_unsharpmaskimage"

external wave :  image_handle -> amplitude:float -> wave_length:float -> unit  = "imper_waveimage"

external rotate : image_handle -> degrees:float -> unit   = "imper_rotateimage"
external shear :  image_handle -> x:float -> y:float -> unit  = "imper_shearimage"

external affine_transform : image_handle ->
  sx:float ->
  rx:float ->
  ry:float ->
  sy:float ->
  tx:float ->
  ty:float ->
  unit    = "imper_affinetransformimage_bytecode"
            "imper_affinetransformimage_native"

let affine_transform t_img
    ?(tx=0.0) ?(ty=0.0)
    ?(sx=1.0) ?(sy=1.0)
    ?(rx=0.0) ?(ry=0.0)
    () =
  if sx = 0.0 then invalid_arg "affine_transform: sx = 0.0 would produce a 0 width image";
  if sy = 0.0 then invalid_arg "affine_transform: sy = 0.0 would produce a 0 height image";
  affine_transform t_img
      ~sx ~rx ~ry ~sy ~tx ~ty



external adaptive_threshold: image_handle -> width:int -> height:int -> offset:int -> unit  = "imper_adaptivethresholdimage"

external crop :   image_handle -> x:int -> y:int -> width:int -> height:int -> unit  = "imper_cropimage"
external chop :   image_handle -> x:int -> y:int -> width:int -> height:int -> unit  = "imper_chopimage"
external splice : image_handle -> x:int -> y:int -> width:int -> height:int -> unit  = "imper_spliceimage"


external colorize: image_handle -> string -> int -> int -> int -> int -> unit
                  = "imper_colorizeimage_bytecode"
                    "imper_colorizeimage_native"

external acquire_pixel : image_handle -> int -> int -> int * int * int * int  = "imper_acquireonepixel"



external composite_image: image_handle -> image_handle -> clip:bool -> x:int -> y:int -> compose:composite_operator -> unit
   = "imper_compositeimage_bytecode"
     "imper_compositeimage_native"

let composite_image t_img u_img ~compose ?(x=0) ?(y=0) ?(clip=false) () = composite_image t_img u_img ~clip ~x ~y ~compose




external texture_image: image_handle -> image_handle -> unit = "imper_textureimage"




external add_noise :  image_handle -> noise_type -> unit  = "imper_addnoiseimage"


external resize:  image_handle -> width:int -> height:int -> filter:resize_filter -> blur:float -> unit
    = "imper_resizeimage"

external sample :    image_handle -> width:int -> height:int -> unit  = "imper_sampleimage"
external scale :     image_handle -> width:int -> height:int -> unit  = "imper_scaleimage"
external thumbnail : image_handle -> width:int -> height:int -> unit  = "imper_thumbnailimage"



external set_image_colors:  image_handle -> int -> unit  = "imper_setimagecolors"
external set_compression_quality:  image_handle -> int -> unit  = "imper_setcompressionquality"


external set_image_type : image_handle -> image_type:image_type -> unit  = "imper_setimagetype"



external strip_image : image_handle -> unit  = "imper_stripimage"



external level : image_handle -> string -> unit = "imper_levelimage"


external ordered_dither : image_handle -> unit  = "imper_orderedditherimage"

external compress_colormap : image_handle -> unit  = "imper_compressimagecolormap"

external posterize : image_handle -> levels:int -> dither:magick_boolean  -> unit  = "imper_posterizeimage"

external map_image : image_handle -> map_image:image_handle -> dither:magick_boolean -> unit  = "imper_mapimage"


external is_palette    : image_handle -> bool  = "imper_ispaletteimage"
external is_taint      : image_handle -> bool  = "imper_istaintimage"
external is_equal : image_handle -> image_handle -> bool * float * float * float  = "imper_isimagesequal"




(*  DRAW  *)


type line_cap =
 | UndefinedCap
 | ButtCap
 | RoundCap
 | SquareCap

type line_join =
 | UndefinedJoin
 | MiterJoin
 | RoundJoin
 | BevelJoin


type color = int * int * int * int


let channels_of_color (red, green, blue, opacity : color) =
  (red, green, blue, opacity)



external acquire_pixel_opacity : image_handle -> int -> int -> int * int * int * int
    = "imper_acquireonepixel_opacity"




let color_of_rgbo_tuple (r,g,b,o) =
  (r,g,b,o : color)

let rgbo_tuple_of_color (r,g,b,o : color) =
  (r,g,b,o)

(* {{{ op *)

let max_color_map = get_max_colormap() ;;

let add_colors
      (r1, g1, b1, a1 : color)
      (r2, g2, b2, a2 : color) =
  let r = min (r1 + r2) max_color_map
  and g = min (g1 + g2) max_color_map
  and b = min (b1 + b2) max_color_map
  and a = min (a1 + a2) max_color_map in
  (r, g, b, a : color)

let sub_colors
      (r1, g1, b1, a1 : color)
      (r2, g2, b2, a2 : color) =
  let r = max (r1 - r2) 0
  and g = max (g1 - g2) 0
  and b = max (b1 - b2) 0
  and a = max (a1 - a2) 0 in
  (r, g, b, a : color)

let mul_colors
      (r1,g1,b1,a1 : color)
      (r2,g2,b2,a2 : color) =
  let r = min (r1 * r2) max_color_map
  and g = min (g1 * g2) max_color_map
  and b = min (b1 * b2) max_color_map
  and a = min (a1 * a2) max_color_map in
  (r, g, b, a : color)

let dump_color (r,g,b,a : color) =
  let (r,g,b,a) =
    if max_color_map = 65535
    then (r/257,g/257,b/257,a/257)
    else (r,g,b,a)
  in
  Printf.printf "rgba(%d,%d,%d,%d)\n" r g b a

let div_colors
      (r1,g1,b1,a1 : color)
      (r2,g2,b2,a2 : color) =
  let r = r1 / r2
  and g = g1 / g2
  and b = b1 / b2
  and a = a1 / a2 in
  (r, g, b, a : color)

(* }}} *)
(* {{{ string_of_color *)

let rgb_string_of_color (r,g,b,o : color) =
  let (r,g,b) =
    if max_color_map = 65535
    then (r/257, g/257, b/257)
    else
      if max_color_map = 255
      then (r,g,b)
      else
        failwith ("unimplemented colormap: " ^ string_of_int max_color_map)
  in
  Printf.sprintf "rgba(%d,%d,%d)" r g b


let rgba_string_of_color (r,g,b,o : color) =
  let (r,g,b,o) =
    if max_color_map = 65535
    then (r/257, g/257, b/257, o/257)
    else
      if max_color_map = 255
      then (r,g,b,o)
      else
        failwith ("unimplemented colormap: " ^ string_of_int max_color_map)
  in
  let a = 255 - o in
  Printf.sprintf "rgba(%d,%d,%d,%d)" r g b a


let hexa_string_of_color (r,g,b,o : color) =
  let (r,g,b,o) =
    if max_color_map = 65535
    then (r/257, g/257, b/257, o/257)
    else
      if max_color_map = 255
      then (r,g,b,o)
      else
        failwith ("unimplemented colormap: " ^ string_of_int max_color_map)
  in
  let a = 255 - o in
  Printf.sprintf "#%02X%02X%02X%02X" r g b a

(* }}} *)

(* {{{ color_of_hex *)

let color_of_hex str_color =

  (* check if the string is empty *)
  let str_len = String.length str_color in
  if str_len = 0 then
    invalid_arg "empty string";

  (* remove the strating char '#' *)
  let str_color =
    if str_color.[0] = '#'
    then String.sub str_color 1 (str_len - 1)
    else str_color
  in
  let str_len = String.length str_color in
  if str_len = 0 then
    invalid_arg "no data given for the color";

  (* check what is the maximum value for the color of a pixel *)
  let cast_for =
    let max_color_map = get_max_colormap() in
    match max_color_map with
    | 255
    | 65535 -> max_color_map
    | _ ->
        invalid_arg
          (Printf.sprintf
             "« %d »: unimplemented color_map \
             (implemented ones are 255 and 65535) \
             recompile ImageMagick and ./configure --with-quantum-depth 16 \
             (for exemple)"
             max_color_map)
  in

  (* convert a char to a string *)
  let string_of_char my_char =
    (String.make 1 ' ')
  in

  (* cast and check the values of the color for IM *)
  let mk_channel_value ~value ~cast_from =
    let value =
      match cast_from, cast_for with
      | 255, 255 -> value
      | 255, 65535 -> value * 257
      | 65535, 255 -> value / 257
      | 65535, 65535 -> value
      (* {{{ for exhaustive pattern-matching *)
      | 255, _
      | 655535, _ ->
          invalid_arg
            "the cast_from argument should be either 255 or 655535"
      | _, 255
      | _, 655535 ->
          invalid_arg
            "the get_max_colormap() function should return either 255 or 65535"
      | _, _ ->
          invalid_arg
            "the cast_from argument should be either 255 or 655535 \
             and the get_max_colormap() function should return either 255 or 65535"
      (* }}} *)
    in
    if value > cast_for then
      invalid_arg
        ("beyond the maximum value for a color channel: " ^ (string_of_int cast_for));
    if value < 0 then
      invalid_arg "the minimum value for a color channel is 0";
    value
  in

  (* convert an hexadecimal value in a string to an int *)
  let int_of_hexa_string elem =
    let value =
      try int_of_string ("0x" ^ elem)
      with _ ->
        invalid_arg ("give characters from [0-9a-fA-F] in " ^ str_color);
    in
    value
  in

  (* the value of a channel can be given with 1, 2 or 4 hexa characters *)
  let chan_of_1char elem =
    let value = int_of_hexa_string (elem ^ elem) in
    mk_channel_value ~value ~cast_from:255
  in
  let chan_of_2char elem =
    let value = int_of_hexa_string elem in
    mk_channel_value ~value ~cast_from:255
  in
  let chan_of_4char elem =
    let value = int_of_hexa_string elem in
    mk_channel_value ~value ~cast_from:65535
  in

  (* separate the values of each channel of the given color,
     which depends of the number of characters given *)
  match str_len with
  | 1 ->
      (chan_of_1char (string_of_char  str_color.[0])),
      (chan_of_1char (string_of_char  str_color.[0])),
      (chan_of_1char (string_of_char  str_color.[0])),
      0
  | 2 ->
      (chan_of_1char (string_of_char  str_color.[0])),
      (chan_of_1char (string_of_char  str_color.[0])),
      (chan_of_1char (string_of_char  str_color.[0])),
      cast_for -
      (chan_of_1char (string_of_char  str_color.[1]))
  | 3 ->
      (chan_of_1char (string_of_char  str_color.[0])),
      (chan_of_1char (string_of_char  str_color.[1])),
      (chan_of_1char (string_of_char  str_color.[2])),
      0
  | 4 ->
      (chan_of_1char (string_of_char  str_color.[0])),
      (chan_of_1char (string_of_char  str_color.[1])),
      (chan_of_1char (string_of_char  str_color.[2])),
      cast_for -
      (chan_of_1char (string_of_char  str_color.[3]))
  | 6 ->
      (chan_of_2char (String.sub str_color 0 2)),
      (chan_of_2char (String.sub str_color 2 2)),
      (chan_of_2char (String.sub str_color 4 2)),
      0
  | 8 ->
      (chan_of_2char (String.sub str_color 0 2)),
      (chan_of_2char (String.sub str_color 2 2)),
      (chan_of_2char (String.sub str_color 4 2)),
      cast_for -
      (chan_of_2char (String.sub str_color 6 2))
  | 12 ->
      (chan_of_4char (String.sub str_color 0 4)),
      (chan_of_4char (String.sub str_color 4 4)),
      (chan_of_4char (String.sub str_color 8 4)),
      0
  | 16 ->
      (chan_of_4char (String.sub str_color  0 4)),
      (chan_of_4char (String.sub str_color  4 4)),
      (chan_of_4char (String.sub str_color  8 4)),
      cast_for -
      (chan_of_4char (String.sub str_color 12 4))
  | _ ->
    invalid_arg "wrong number of characters (allowed are: 1|2|3|4|6|8|12|16)"

(* }}} *)

let black = (0, 0, 0, 0 : color)
let transparent = (0, 0, 0, max_color_map : color)

(* TODO: test the affine_matrix parameter *)
(* {{{ affine_matrix *)

type affine_matrix = {
  sx : float;
  rx : float;
  ry : float;
  sy : float;
  tx : float;
  ty : float;
}

let identity_matrix = {
  sx = 1.0;
  rx = 0.0;
  ry = 0.0;
  sy = 1.0;
  tx = 0.0;
  ty = 0.0;
}

let tuple_of_matrix ~affine_matrix =
  ( affine_matrix.sx,
    affine_matrix.rx,
    affine_matrix.ry,
    affine_matrix.sy,
    affine_matrix.tx,
    affine_matrix.ty )
;;

(* }}} *)

(* {{{ draw_point *)

external set_pixel : image_handle ->
            x:int -> y:int ->
            red:int -> green:int -> blue:int -> opacity:int -> unit
    = "imper_draw_point_bytecode"
      "imper_draw_point_native"


external draw_point : image_handle ->
            x:int -> y:int ->
            red:int -> green:int -> blue:int -> opacity:int -> unit
    = "imper_draw_point_bytecode"
      "imper_draw_point_native"

let draw_point t_img ~x ~y  ~color =
    let (red, green, blue, opacity) = channels_of_color color in
    draw_point  t_img  ~x ~y
            ~red ~green ~blue ~opacity

(* }}} *)
(* {{{ draw_line *)

external draw_line : image_handle ->
            x0:int -> y0:int -> x1:int -> y1:int ->
            fill_red:int -> fill_green:int -> fill_blue:int -> fill_alpha:int ->
            stroke_red:int -> stroke_green:int -> stroke_blue:int -> stroke_alpha:int ->
            stroke_antialias:magick_boolean ->
            stroke_width:float -> line_cap:line_cap -> unit
    = "imper_draw_line_bytecode"
      "imper_draw_line_native"

let draw_line t_img
        ~x0 ~y0  ~x1 ~y1
        ?(fill_color=transparent)
        ?(stroke_color=black)
        ?(stroke_antialias=MagickTrue)
        ?(stroke_width=1.0) ?(line_cap=ButtCap) () =
    let (fill_red, fill_green, fill_blue, fill_alpha) = channels_of_color fill_color
    and (stroke_red, stroke_green, stroke_blue, stroke_alpha) = channels_of_color stroke_color in
    draw_line t_img
            ~x0 ~y0 ~x1 ~y1
            ~fill_red ~fill_green ~fill_blue ~fill_alpha
            ~stroke_red ~stroke_green ~stroke_blue ~stroke_alpha
            ~stroke_antialias ~stroke_width ~line_cap

(* }}} *)
(* {{{ draw_circle *)

external draw_circle : image_handle ->
            x0:int -> y0:int -> x1:int -> y1:int ->
            fill_red:int -> fill_green:int -> fill_blue:int -> fill_alpha:int ->
            stroke_red:int -> stroke_green:int -> stroke_blue:int -> stroke_alpha:int ->
            stroke_antialias:magick_boolean -> stroke_width:float ->
            sx:float -> rx:float -> ry:float -> sy:float -> tx:float -> ty:float -> unit
    = "imper_draw_circle_bytecode"
      "imper_draw_circle_native"

let draw_circle t_img
        ~x0 ~y0  ~x1 ~y1
        ?(fill_color=black)
        ?(stroke_color=transparent)
        ?(stroke_width=1.0)
        ?(stroke_antialias=MagickTrue)
        ?(affine_matrix=identity_matrix)
        () =
    let (fill_red, fill_green, fill_blue, fill_alpha) = channels_of_color fill_color
    and (stroke_red, stroke_green, stroke_blue, stroke_alpha) = channels_of_color stroke_color
    and (sx, rx, ry, sy, tx, ty) = tuple_of_matrix ~affine_matrix
    in
    draw_circle t_img
            ~x0 ~y0  ~x1 ~y1
            ~fill_red ~fill_green ~fill_blue ~fill_alpha
            ~stroke_red ~stroke_green ~stroke_blue ~stroke_alpha
            ~stroke_antialias ~stroke_width
            ~sx ~rx ~ry ~sy ~tx ~ty

(* }}} *)
(* {{{ draw_rectangle *)

external draw_rectangle : image_handle ->
            x0:int -> y0:int -> x1:int -> y1:int ->
            fill_red:int -> fill_green:int -> fill_blue:int -> fill_alpha:int ->
            stroke_red:int -> stroke_green:int -> stroke_blue:int -> stroke_alpha:int ->
            stroke_antialias:magick_boolean ->
            stroke_width:float -> line_join:line_join ->
            sx:float -> rx:float -> ry:float -> sy:float -> tx:float -> ty:float -> unit
    = "imper_draw_rectangle_bytecode"
      "imper_draw_rectangle_native"

let draw_rectangle
        t_img  ~x0 ~y0  ~x1 ~y1
        ?(fill_color=black)
        ?(stroke_color=transparent)
        ?(stroke_width=1.0)
        ?(stroke_antialias=MagickTrue)
        ?(line_join=MiterJoin)
        ?(affine_matrix=identity_matrix)
        () =
    (* TODO: check if the affine_matrix is the identity and if so the
       default for antialias should be False, otherwise True. *)
    let (fill_red, fill_green, fill_blue, fill_alpha) = channels_of_color fill_color
    and (stroke_red, stroke_green, stroke_blue, stroke_alpha) = channels_of_color stroke_color
    and (sx, rx, ry, sy, tx, ty) = tuple_of_matrix ~affine_matrix
    in
    draw_rectangle t_img
            ~x0 ~y0  ~x1 ~y1
            ~fill_red ~fill_green ~fill_blue ~fill_alpha
            ~stroke_red ~stroke_green ~stroke_blue ~stroke_alpha
            ~stroke_antialias
            ~stroke_width ~line_join
            ~sx ~rx ~ry ~sy ~tx ~ty

(* }}} *)
(* {{{ draw_round_rectangle *)

external draw_round_rectangle : image_handle ->
            x0:int -> y0:int -> x1:int -> y1:int -> wc:int -> hc:int ->
            fill_red:int -> fill_green:int -> fill_blue:int -> fill_alpha:int ->
            stroke_red:int -> stroke_green:int -> stroke_blue:int -> stroke_alpha:int ->
            stroke_antialias:magick_boolean ->
            stroke_width:float ->
            sx:float -> rx:float -> ry:float -> sy:float -> tx:float -> ty:float -> unit
    = "imper_draw_roundrectangle_bytecode"
      "imper_draw_roundrectangle_native"

let draw_round_rectangle
        t_img  ~x0 ~y0  ~x1 ~y1  ~wc ~hc
        ?(fill_color=black)
        ?(stroke_color=transparent)
        ?(stroke_antialias=MagickTrue)
        ?(stroke_width=1.0)
        ?(affine_matrix=identity_matrix)
        () =
    let (fill_red, fill_green, fill_blue, fill_alpha) = channels_of_color fill_color
    and (stroke_red, stroke_green, stroke_blue, stroke_alpha) = channels_of_color stroke_color
    and (sx, rx, ry, sy, tx, ty) = tuple_of_matrix ~affine_matrix
    in
    draw_round_rectangle t_img
            ~x0 ~y0  ~x1 ~y1  ~wc ~hc
            ~fill_red ~fill_green ~fill_blue ~fill_alpha
            ~stroke_red ~stroke_green ~stroke_blue ~stroke_alpha
            ~stroke_antialias ~stroke_width
            ~sx ~rx ~ry ~sy ~tx ~ty

(* }}} *)
(* {{{ draw_arc *)

external draw_arc : image_handle ->
            x0:int -> y0:int -> x1:int -> y1:int -> a0:int -> a1:int ->
            fill_red:int -> fill_green:int -> fill_blue:int -> fill_alpha:int ->
            stroke_red:int -> stroke_green:int -> stroke_blue:int -> stroke_alpha:int ->
            stroke_antialias:magick_boolean ->
            stroke_width:float -> line_cap:line_cap ->
            sx:float -> rx:float -> ry:float -> sy:float -> tx:float -> ty:float -> unit
    = "imper_draw_arc_bytecode"
      "imper_draw_arc_native"

let draw_arc t_img
        ~x0 ~y0 ~x1 ~y1 ~a0 ~a1
        ?(fill_color=transparent)
        ?(stroke_color=black)
        ?(stroke_antialias=MagickTrue)
        ?(stroke_width=1.0)
        ?(line_cap=ButtCap)
        ?(affine_matrix=identity_matrix)
        () =
    let (fill_red, fill_green, fill_blue, fill_alpha) = channels_of_color fill_color
    and (stroke_red, stroke_green, stroke_blue, stroke_alpha) = channels_of_color stroke_color
    and (sx, rx, ry, sy, tx, ty) = tuple_of_matrix ~affine_matrix
    in
    draw_arc t_img
            ~x0 ~y0 ~x1 ~y1 ~a0 ~a1
            ~fill_red ~fill_green ~fill_blue ~fill_alpha
            ~stroke_red ~stroke_green ~stroke_blue ~stroke_alpha
            ~stroke_antialias ~stroke_width ~line_cap
            ~sx ~rx ~ry ~sy ~tx ~ty

(* }}} *)
(* {{{ draw_ellipse *)

external draw_ellipse : image_handle ->
            cx:int -> cy:int -> rx:int -> ry:int -> a0:int -> a1:int ->
            fill_red:int -> fill_green:int -> fill_blue:int -> fill_alpha:int ->
            stroke_red:int -> stroke_green:int -> stroke_blue:int -> stroke_alpha:int ->
            stroke_antialias:magick_boolean -> stroke_width:float ->
            sx:float -> rx:float -> ry:float -> sy:float -> tx:float -> ty:float -> unit
    = "imper_draw_ellipse_bytecode"
      "imper_draw_ellipse_native"

let draw_ellipse t_img
        ~cx ~cy ~rx ~ry
        ?(a0=0) ?(a1=360)
        ?(fill_color=black)
        ?(stroke_color=transparent)
        ?(stroke_antialias=MagickTrue)
        ?(stroke_width=1.0)
        ?(affine_matrix=identity_matrix)
        () =
    let (fill_red, fill_green, fill_blue, fill_alpha) = channels_of_color fill_color
    and (stroke_red, stroke_green, stroke_blue, stroke_alpha) = channels_of_color stroke_color
    and (sx, rx_, ry_, sy, tx, ty) = tuple_of_matrix ~affine_matrix
    in
    draw_ellipse t_img
            ~cx ~cy ~rx ~ry ~a0 ~a1
            ~fill_red ~fill_green ~fill_blue ~fill_alpha
            ~stroke_red ~stroke_green ~stroke_blue ~stroke_alpha
            ~stroke_antialias ~stroke_width
            ~sx ~rx:rx_ ~ry:ry_ ~sy ~tx ~ty

(* }}} *)

(* {{{ draw_polyline *)

external draw_polyline : image_handle ->
            coords:(int * int) array -> array_length:int ->
            fill_red:int -> fill_green:int -> fill_blue:int -> fill_alpha:int ->
            stroke_red:int -> stroke_green:int -> stroke_blue:int -> stroke_alpha:int ->
            stroke_antialias:magick_boolean ->
            stroke_width:float -> line_join:line_join -> line_cap:line_cap ->
            sx:float -> rx:float -> ry:float -> sy:float -> tx:float -> ty:float -> unit
    = "imper_draw_polyline_bytecode"
      "imper_draw_polyline_native"

let draw_polyline t_img
        ~coords
        ?(fill_color=transparent)
        ?(stroke_color=black)
        ?(stroke_antialias=MagickTrue)
        ?(stroke_width=1.0)
        ?(line_join=MiterJoin)
        ?(line_cap=ButtCap)
        ?(affine_matrix=identity_matrix)
        () =
    let (fill_red, fill_green, fill_blue, fill_alpha) = channels_of_color fill_color
    and (stroke_red, stroke_green, stroke_blue, stroke_alpha) = channels_of_color stroke_color
    and (sx, rx, ry, sy, tx, ty) = tuple_of_matrix ~affine_matrix
    and array_length = Array.length coords
    in
    draw_polyline t_img
            ~coords ~array_length
            ~fill_red ~fill_green ~fill_blue ~fill_alpha
            ~stroke_red ~stroke_green ~stroke_blue ~stroke_alpha
            ~stroke_antialias ~stroke_width ~line_join ~line_cap
            ~sx ~rx ~ry ~sy ~tx ~ty

(* }}} *)
(* {{{ draw_polygon *)

external draw_polygon : image_handle ->
            coords:(int * int) array -> array_length:int ->
            fill_red:int -> fill_green:int -> fill_blue:int -> fill_alpha:int ->
            stroke_red:int -> stroke_green:int -> stroke_blue:int -> stroke_alpha:int ->
            stroke_antialias:magick_boolean ->
            stroke_width:float -> line_join:line_join ->
            sx:float -> rx:float -> ry:float -> sy:float -> tx:float -> ty:float -> unit
    = "imper_draw_polygon_bytecode"
      "imper_draw_polygon_native"

let draw_polygon t_img
        ~coords
        ?(fill_color=black)
        ?(stroke_color=transparent)
        ?(stroke_antialias=MagickTrue)
        ?(stroke_width=1.0)
        ?(line_join=MiterJoin)
        ?(affine_matrix=identity_matrix)
        () =
    let (fill_red, fill_green, fill_blue, fill_alpha) = channels_of_color fill_color
    and (stroke_red, stroke_green, stroke_blue, stroke_alpha) = channels_of_color stroke_color
    and (sx, rx, ry, sy, tx, ty) = tuple_of_matrix ~affine_matrix
    and array_length = Array.length coords
    in
    draw_polygon t_img
            ~coords ~array_length
            ~fill_red ~fill_green ~fill_blue ~fill_alpha
            ~stroke_red ~stroke_green ~stroke_blue ~stroke_alpha
            ~stroke_antialias ~stroke_width ~line_join
            ~sx ~rx ~ry ~sy ~tx ~ty

(* }}} *)
(* {{{ draw_bezier *)

external draw_bezier : image_handle ->
            coords:(int * int) array -> array_length:int ->
            fill_red:int -> fill_green:int -> fill_blue:int -> fill_alpha:int ->
            stroke_red:int -> stroke_green:int -> stroke_blue:int -> stroke_alpha:int ->
            stroke_antialias:magick_boolean ->
            stroke_width:float -> line_cap:line_cap ->
            sx:float -> rx:float -> ry:float -> sy:float -> tx:float -> ty:float -> unit
    = "imper_draw_bezier_bytecode"
      "imper_draw_bezier_native"

let draw_bezier t_img
        ~coords
        ?(fill_color=transparent)
        ?(stroke_color=black)
        ?(stroke_antialias=MagickTrue)
        ?(stroke_width=1.0)
        ?(line_cap=ButtCap)
        ?(affine_matrix=identity_matrix)
        () =
    let (fill_red, fill_green, fill_blue, fill_alpha) = channels_of_color fill_color
    and (stroke_red, stroke_green, stroke_blue, stroke_alpha) = channels_of_color stroke_color
    and (sx, rx, ry, sy, tx, ty) = tuple_of_matrix ~affine_matrix
    and array_length = Array.length coords
    in
    draw_bezier t_img
            ~coords ~array_length
            ~fill_red ~fill_green ~fill_blue ~fill_alpha
            ~stroke_red ~stroke_green ~stroke_blue ~stroke_alpha
            ~stroke_antialias ~stroke_width ~line_cap
            ~sx ~rx ~ry ~sy ~tx ~ty

(* }}} *)

(* {{{ draw_path *)

external draw_path : image_handle ->
            path:string ->
            fill_red:int -> fill_green:int -> fill_blue:int -> fill_alpha:int ->
            stroke_red:int -> stroke_green:int -> stroke_blue:int -> stroke_alpha:int ->
            stroke_antialias:magick_boolean ->
            stroke_width:float -> line_join:line_join -> line_cap:line_cap ->
            sx:float -> rx:float -> ry:float -> sy:float -> tx:float -> ty:float -> unit
    = "imper_draw_path_bytecode"
      "imper_draw_path_native"


let draw_path t_img
        ~path
        ?(fill_color=transparent)
        ?(stroke_color=black)
        ?(stroke_antialias=MagickTrue)
        ?(stroke_width=1.0)
        ?(line_join=MiterJoin)
        ?(line_cap=ButtCap)
        ?(affine_matrix=identity_matrix)
        () =
    let (fill_red, fill_green, fill_blue, fill_alpha) = channels_of_color fill_color
    and (stroke_red, stroke_green, stroke_blue, stroke_alpha) = channels_of_color stroke_color
    and (sx, rx, ry, sy, tx, ty) = tuple_of_matrix ~affine_matrix
    in
    draw_path t_img
            ~path
            ~fill_red ~fill_green ~fill_blue ~fill_alpha
            ~stroke_red ~stroke_green ~stroke_blue ~stroke_alpha
            ~stroke_antialias ~stroke_width ~line_join ~line_cap
            ~sx ~rx ~ry ~sy ~tx ~ty

(* }}} *)

(* {{{ types for draw_text *)

type style_type =
 | Undefined_Style
 | Normal_Style
 | Italic
 | Oblique
 | Any_Style

type decoration_type =
 | Undefined_Decoration
 | No_Decoration
 | Underline
 | Overline
 | LineThrough

type stretch_type =
 | Undefined_Stretch
 | Normal_Stretch
 | UltraCondensed
 | ExtraCondensed
 | Condensed
 | SemiCondensed
 | SemiExpanded
 | Expanded
 | ExtraExpanded
 | UltraExpanded
 | Any_Stretch

(* }}} *)

(* {{{ draw_text *)

external draw_text : image_handle ->
            text:string -> font:string -> x:int -> y:int -> point_size:float ->
            density_x:int -> density_y:int ->
            style:style_type -> weight:int -> decoration:decoration_type -> stretch:stretch_type ->
            fill_red:int -> fill_green:int -> fill_blue:int -> fill_alpha:int ->
            stroke_red:int -> stroke_green:int -> stroke_blue:int -> stroke_alpha:int ->
            stroke_width:float ->
            stroke_antialias:magick_boolean ->
            text_antialias:magick_boolean ->
            encoding:string ->
            sx:float -> rx:float -> ry:float -> sy:float -> tx:float -> ty:float -> unit
    = "imper_draw_text_bytecode"
      "imper_draw_text_native"

let draw_text t_img
        ~text ?(font="")
        ~x ~y ~point_size
        ?(density_x=72)
        ?(density_y=72)
        ?(style=Normal_Style) ?(weight=1)
        ?(fill_color=black)
        ?(stroke_color=transparent)
        ?(decoration=No_Decoration)
        ?(stretch=Normal_Stretch)
        ?(stroke_width=1.0)
        ?(stroke_antialias=MagickTrue) (* TODO: no stroke antialias if stroke is transparent *)
        ?(text_antialias=MagickTrue)
        ?(encoding="")
        ?(affine_matrix=identity_matrix)
        () =
    let (fill_red, fill_green, fill_blue, fill_alpha) = channels_of_color  fill_color
    and (stroke_red, stroke_green, stroke_blue, stroke_alpha) = channels_of_color  stroke_color
    and (sx, rx, ry, sy, tx, ty) = tuple_of_matrix ~affine_matrix
    in
    draw_text t_img
            ~text ~font ~x ~y ~point_size
            ~density_x ~density_y
            ~style ~weight ~decoration ~stretch
            ~fill_red ~fill_green ~fill_blue ~fill_alpha
            ~stroke_red ~stroke_green ~stroke_blue ~stroke_alpha
            ~stroke_width
            ~stroke_antialias
            ~text_antialias
            ~encoding
            ~sx ~rx ~ry ~sy ~tx ~ty

(* }}} *)
(* {{{ get_metrics *)

type metrics_infos = {
  ascent  : float;
  descent : float;
  text_width  : float;
  text_height : float;
  max_advance : float;
  underline_position  : float;
  underline_thickness : float;
  pixels_per_em_x : float;
  pixels_per_em_y : float;
  bounds_x1 : float;
  bounds_y1 : float;
  bounds_x2 : float;
  bounds_y2 : float;
}

external get_metrics : image_handle ->
            text:string -> font:string -> x:int -> y:int -> point_size:float ->
            density_x:int -> density_y:int ->
            style:style_type -> weight:int -> decoration:decoration_type -> stretch:stretch_type ->
            stroke_width:float ->
            sx:float -> rx:float -> ry:float -> sy:float -> tx:float -> ty:float ->
            float * float * float * float * float * float * float *
            float * float * float * float * float * float
    = "imper_get_metrics_bytecode"
      "imper_get_metrics_native"

let get_metrics t_img
        ~text ?(font="") ~x ~y ~point_size
        ?(density_x=72)
        ?(density_y=72)
        ?(style=Normal_Style) ?(weight=1)
        ?(decoration=No_Decoration)
        ?(stretch=Normal_Stretch)
        ?(stroke_width=1.0)
        (*
        ?(affine_matrix=identity_matrix)
        *)
        () =
    (* The transformation matrix doesn't affect the results,
       but perhaps this will change in the futur ? *)
    let (sx, rx, ry, sy, tx, ty) = tuple_of_matrix ~affine_matrix:identity_matrix in
    (*
    let (sx, rx, ry, sy, tx, ty) = tuple_of_matrix ~affine_matrix in
    *)
    let ( ascent, descent,
          width, height,
          max_advance,
          underline_position,
          underline_thickness,
          pixels_per_em_x,
          pixels_per_em_y,
          bounds_x1, bounds_y1,
          bounds_x2, bounds_y2 )
      = get_metrics t_img
              ~text ~font ~x ~y ~point_size
              ~density_x ~density_y
              ~style ~weight ~decoration ~stretch
              ~stroke_width
              ~sx ~rx ~ry ~sy ~tx ~ty
    in
    {
      ascent  = ascent;
      descent = descent;
      text_width  = width;
      text_height = height;
      max_advance = max_advance;
      underline_position  = underline_position;
      underline_thickness = underline_thickness;
      pixels_per_em_x = pixels_per_em_x;
      pixels_per_em_y = pixels_per_em_y;
      bounds_x1 = bounds_x1;
      bounds_y1 = bounds_y1;
      bounds_x2 = bounds_x2;
      bounds_y2 = bounds_y2;
    }



let transform_metrics ~metrics ~affine_matrix =
    let m = metrics
    and (sx, rx, ry, sy, tx, ty) = tuple_of_matrix ~affine_matrix
    in
    let width  = m.text_width  *. sx
    and height = m.text_height *. sy
    and pixels_per_em_x = m.pixels_per_em_x *. sx
    and pixels_per_em_y = m.pixels_per_em_y *. sy
    and bounds_x1 = m.bounds_x1 *. sx
    and bounds_x2 = m.bounds_x2 *. sx
    and bounds_y1 = m.bounds_y1 *. sy
    and bounds_y2 = m.bounds_y2 *. sy
    and underline_position  = m.underline_position  *. sy
    and underline_thickness = m.underline_thickness *. sy
    and ascent  = m.ascent  *. sy
    and descent = m.descent *. sy
    and max_advance = m.max_advance *. sx
    in
    {
      ascent  = ascent;
      descent = descent;
      text_width  = width;
      text_height = height;
      max_advance = max_advance;
      underline_position  = underline_position;
      underline_thickness = underline_thickness;
      pixels_per_em_x = pixels_per_em_x;
      pixels_per_em_y = pixels_per_em_y;
      bounds_x1 = bounds_x1;
      bounds_y1 = bounds_y1;
      bounds_x2 = bounds_x2;
      bounds_y2 = bounds_y2;
    }


(* }}} *)


external draw_text_devel : image_handle -> text:string -> unit  =  "imper_draw_text_new1"

(* {{{ draw_mvg *)

external draw_mvg: image_handle -> mvg:string -> unit = "imper_draw_mvg"

(* }}} *)


(* @TODO: Make these functions work
external set_image_pixel :  image_handle -> int -> int -> unit  = "imper_setimagepixel"
external load_image : x:int -> y:int -> color:int -> image_handle  = "imper_loadimage"
*)


external get_raw  : image_handle -> (int * int * int * int) array array  = "imper_get_raw"
external get_raw' : image_handle -> (int * int * int * int) array array  = "imper_get_raw2"

external get_raw_opacity : image_handle -> (int * int * int * int) array array  = "imper_get_raw_opacity"

external get_raw_without_alpha : image_handle -> (int * int * int) array array = "imper_get_raw_without_alpha"


external get_raw_gl_indexed : image_handle -> (int * int * int * int) array = "imper_get_raw_gl_indexed"
external get_raw_gl_indexed_without_alpha : image_handle -> (int * int * int) array
                = "imper_get_raw_gl_indexed_without_alpha"


(* @TODO: send the array to C rather than unefficient loops on set_pixel calls *)
(*
let set_raw ~raw =
  let width  = Array.length raw
  and height = Array.length raw.(0)
  in
  let t_img = get_canvas ~width ~height ~color:"#000000"
  in
  for x = 0 to width - 1 do
    let raw_x = raw.(x) in
    for y = 0 to height - 1 do
      let (red, green, blue, alpha) = raw_x.(y) in
      set_pixel t_img ~x ~y ~red ~green ~blue ~opacity;
    done
  done;
  t_img
;;
*)
let set_raw ~raw =
  let width  = Array.length raw
  and height = Array.length raw.(0)
  in
  let t_img = get_canvas ~width ~height ~color:"#000000"
  in
  for x = 0 to width - 1 do
    for y = 0 to height - 1 do
      let (red, green, blue, opacity) = raw.(x).(y) in
      set_pixel t_img ~x ~y ~red ~green ~blue ~opacity;
    done
  done;
  t_img
;;


external set_raw_c :  raw:(int * int * int * int) array array -> width:int -> height:int -> image_handle
   = "imper_set_raw_c"

let set_raw_c ~raw =
  let width  = Array.length raw
  and height = Array.length raw.(0)
  in
  set_raw_c ~raw ~width ~height;
;;







(* images lists *)

type image_list_handle


external new_image_list : unit -> image_list_handle  = "imper_new_image_list"

external no_op : image_handle -> unit = "imper_no_op" (* TEMP *)


external display_images : image_list_handle -> unit  =  "im_displayimages"

external append_image_to_list : image_list_handle -> image_handle -> delay:int -> unit  = "imper_appendimagetolist"
let append_image_to_list  t_img_list t_img ?(delay=50) () =
    append_image_to_list  t_img_list t_img  ~delay

external image_list_length : image_list_handle -> int  = "imper_getimagelistlength"


external coalesce_images :    image_list_handle -> unit  = "imper_coalesceimages"
external flatten_images :     image_list_handle -> unit  = "imper_flattenimages"


external animate_images :  image_list_handle -> unit  = "imper_animateimages"


external write_images : image_list_handle -> string -> unit  = "im_writeimage"

external get_last_image_in_list :  image_list_handle -> image_handle  = "imper_getlastimageinlist"
external get_first_image_in_list : image_list_handle -> image_handle  = "imper_getfirstimageinlist"


external has_link :  image_handle -> bool  = "imper_has_link"


type stack =
  | Left_to_right
  | Top_to_bottom

let stack_dir_of_string ~stack =
  match String.lowercase_ascii stack with
  | "left to right"
  | "left-to-right"
  | "left_to_right" -> Left_to_right
  | "top to bottom"
  | "top-to-bottom"
  | "top_to_bottom" -> Top_to_bottom
  | _ -> failwith "unrecognized stack direction"

(*
external append_images : image_list_handle -> stack:stack -> image_handle = "imper_appendimages"
*)
external append_images : image_list_handle -> stack:stack -> image_handle -> unit = "imper_appendimages"
let append_images img_list ~stack =
  let _img = get_canvas ~width:2  ~height:2 ~color:"#0000" in
  append_images img_list ~stack _img;
  _img
;;

end;; (* of module Imper }}} *)


(* {{{ Functional module *)

module Fun = struct


let create_image ~width ~height ~pseudo_format () = create_image ~width ~height ~pseudo_format
let get_canvas ~width ~height ~color () = get_canvas ~width ~height ~color
let read_image ~filename () = read_image ~filename


(* {{{ functions with a functionnal forme in the MagickCore *)

external blur : image_handle -> radius:float -> sigma:float -> image_handle = "fun_blurimage"
let blur ?(radius=0.0) ~sigma () img = blur img ~radius ~sigma

external charcoal : image_handle -> radius:float -> sigma:float -> image_handle = "fun_charcoalimage"
let charcoal ?(radius=0.0) ~sigma () img = charcoal img ~radius ~sigma

external edge : image_handle -> radius:float -> image_handle  = "fun_edgeimage"
let edge ~radius () img = edge img ~radius

external emboss : image_handle -> radius:float -> sigma:float -> image_handle = "fun_embossimage"
let emboss ?(radius=0.0) ~sigma () img = emboss img ~radius ~sigma

external gaussian_blur : image_handle -> radius:float -> sigma:float -> image_handle = "fun_gaussianblurimage"
let gaussian_blur ?(radius=0.0) ~sigma () img = gaussian_blur img ~radius ~sigma

external implode : image_handle -> amount:float -> image_handle = "fun_implodeimage"
let implode ~amount () img = implode img ~amount

external motion_blur : image_handle -> radius:float -> sigma:float -> angle:float -> image_handle = "fun_motionblurimage"
let motion_blur ?(radius=0.0) ~sigma ~angle () img = motion_blur img ~radius ~sigma ~angle

external oilpaint : image_handle -> radius:float -> image_handle = "fun_oilpaintimage"
let oilpaint ~radius () img = oilpaint img ~radius

external roll : image_handle -> x:int -> y:int -> image_handle = "fun_rollimage"
let roll ~x ~y () img = roll img ~x ~y

external shade : image_handle -> gray:magick_boolean -> azimuth:float -> elevation:float -> image_handle = "fun_shadeimage"
let shade ?(gray=MagickTrue) ~azimuth ~elevation () img = shade img ~gray ~azimuth ~elevation

external sharpen : image_handle -> radius:float -> sigma:float -> image_handle = "fun_sharpenimage"
let sharpen ?(radius=0.0) ~sigma () img = sharpen img ~radius ~sigma

external spread : image_handle -> radius:float -> image_handle = "fun_spreadimage"
let spread ~radius () img = spread img ~radius

external swirl : image_handle -> degrees:float -> image_handle = "fun_swirlimage"
let swirl ~degrees () img = swirl img ~degrees

external unsharpmask : image_handle -> radius:float -> sigma:float -> amount:float -> threshold:float -> image_handle
    = "fun_unsharpmaskimage"
let unsharpmask ~radius ~sigma ~amount ~threshold () img = unsharpmask img ~radius ~sigma ~amount ~threshold

external wave : image_handle -> amplitude:float -> wave_length:float -> image_handle = "fun_waveimage"
let wave ~amplitude ~wave_length () img = wave img ~amplitude ~wave_length

external rotate : image_handle -> degrees:float -> image_handle = "fun_rotateimage"
let rotate ~degrees () img = rotate img ~degrees

external shear : image_handle -> x:float -> y:float -> image_handle = "fun_shearimage"
let shear ~x ~y () img = shear img ~x ~y

external sample : image_handle -> width:int -> height:int -> image_handle = "fun_sampleimage"
let sample ~width ~height () img = sample img ~width ~height

external scale : image_handle -> width:int -> height:int -> image_handle = "fun_scaleimage"
let scale ~width ~height () img = scale img ~width ~height

external thumbnail : image_handle -> width:int -> height:int -> image_handle = "fun_thumbnailimage"
let thumbnail ~width ~height () img = thumbnail img ~width ~height

external adaptive_threshold : image_handle -> width:int -> height:int -> offset:int -> image_handle
    = "fun_adaptivethresholdimage"
let adaptive_threshold ~width ~height ~offset () img = adaptive_threshold img ~width ~height ~offset

external add_noise : image_handle -> noise_type:noise_type -> image_handle = "fun_addnoiseimage"
let add_noise ~noise_type () img = add_noise img ~noise_type

external resize : image_handle -> width:int -> height:int -> filter:resize_filter -> blur:float -> image_handle
    = "fun_resizeimage"
let resize ~width ~height ~filter ~blur () img = resize img ~width ~height ~filter ~blur

external enhance : image_handle -> image_handle = "fun_enhanceimage"
let enhance () img = enhance img

external despeckle : image_handle -> image_handle = "fun_despeckleimage"
let despeckle () img = despeckle img

external minify : image_handle -> image_handle ="fun_minifyimage"
let minify () img = minify img

external magnify : image_handle -> image_handle = "fun_magnifyimage"
let magnify () img = magnify img

external flip : image_handle -> image_handle = "fun_flipimage"
let flip () img = flip img

external flop : image_handle -> image_handle = "fun_flopimage"
let flop () img = flop img

external splice : image_handle -> x:int -> y:int -> width:int -> height:int -> image_handle = "fun_spliceimage"
let splice ~x ~y ~width ~height () img = splice img ~x ~y ~width ~height


external crop : image_handle -> x:int -> y:int -> width:int -> height:int -> image_handle = "fun_cropimage"
let crop ~x ~y ~width ~height () img = crop img ~x ~y ~width ~height



external affine_transform : image_handle ->
  sx:float ->
  rx:float ->
  ry:float ->
  sy:float ->
  tx:float ->
  ty:float ->
  image_handle  = "fun_affinetransformimage_bytecode"
                  "fun_affinetransformimage_native"

let affine_transform
    ?(tx=0.0) ?(ty=0.0)
    ?(sx=1.0) ?(sy=1.0)
    ?(rx=0.0) ?(ry=0.0)
    () img =
  if sx = 0.0 then invalid_arg "affine_transform: sx = 0.0 would produce a 0 width image";
  if sy = 0.0 then invalid_arg "affine_transform: sy = 0.0 would produce a 0 height image";
  affine_transform img
      ~sx ~rx ~ry ~sy ~tx ~ty

(* }}} *)

(* {{{ functions with an imperative forme in the MagickCore *)

external negate : image_handle -> grayscale:magick_boolean -> image_handle = "fun_negateimage"
let negate ?(grayscale=MagickFalse) () img = negate img ~grayscale


external contrast : image_handle -> sharpen:magick_boolean -> image_handle = "fun_contrastimage"
let contrast ~sharpen () img = contrast img ~sharpen

external equalize : image_handle -> image_handle = "fun_equalizeimage"
let equalize () img = equalize img

external normalize : image_handle -> image_handle = "fun_normalizeimage"
let normalize () img = normalize img

external black_threshold : image_handle -> threshold:string -> image_handle = "fun_blackthresholdimage"
let black_threshold ~threshold () img = black_threshold img ~threshold

external white_threshold : image_handle -> threshold:string -> image_handle = "fun_whitethresholdimage"
let white_threshold ~threshold () img = white_threshold img ~threshold

external cyclecolormap : image_handle -> displace:int -> image_handle = "fun_cyclecolormapimage"
let cyclecolormap ~displace () img = cyclecolormap img ~displace

external solarize : image_handle -> threshold:float -> image_handle = "fun_solarizeimage"
let solarize ~threshold () img = solarize img ~threshold

external strip : image_handle -> image_handle = "fun_stripimage"
let strip () img = strip img

external level : image_handle -> levels:string -> image_handle = "fun_levelimage"
let level ~levels () img = level img ~levels

external ordered_dither : image_handle -> image_handle = "fun_orderedditherimage"
let ordered_dither () = ordered_dither ;;



(* TODO: ask which is the good traduction
 *
 *  below, behind, underneath, beneath
 *  above, on_top
 *)
let composite_image ~compose ?(x=0) ?(y=0) () ~img_below ~img_above =
  let img_under = clone_image  img_below in
  Imper.composite_image img_under img_above ~compose ~x ~y ();
  img_under
;;


let texture_image ~img ~tex_img =
  let new_img = clone_image img in
  Imper.texture_image new_img tex_img;
  new_img
;;




external modulate' : image_handle -> factors:string -> image_handle = "fun_modulateimage"

let modulate ?(brightness=100) ?(saturation=100) ?(hue=100) () img =
  let br = string_of_int  brightness
  and sa = string_of_int  saturation
  and hu = string_of_int  hue
  in
  modulate' img ~factors:(br ^","^ sa ^","^ hu)

let modulate' ~factors () img = modulate' img ~factors



let view () img = display img; img


(* }}} *)


end;; (* of module Functional }}} *)


(* {{{ get_magick_* *)

external get_magick_copyright     : unit -> string  = "imper_getmagickcopyright"
external get_magick_home_url      : unit -> string  = "imper_getmagickhomeurl"
external get_magick_release_date  : unit -> string  = "imper_getmagickreleasedate"
external get_magick_version       : unit -> int * string  = "imper_getmagickversion"
external get_magick_quantum_depth : unit -> int * string  = "imper_getmagickquantumdepth"
external get_magick_quantum_range : unit -> int * string  = "imper_getmagickquantumrange"
(* external get_magick_name       : unit -> string  = "imper_getmagickname" *)

external get_binding_version : unit -> string  = "imper_getbindingversion"

(* }}} *)


(* {{{ BigArray *)

type shared_data =
  | UI8  of (int, Bigarray.int8_unsigned_elt,  Bigarray.c_layout) Bigarray.Array3.t
  | UI16 of (int, Bigarray.int16_unsigned_elt, Bigarray.c_layout) Bigarray.Array3.t
  | UI32 of (int, Bigarray.int32_elt, Bigarray.c_layout) Bigarray.Array3.t
  | UI64 of (int, Bigarray.int64_elt, Bigarray.c_layout) Bigarray.Array3.t


external inspect_big_array: ('a, 'b, 'c) Bigarray.Array2.t -> unit = "ml_big_array_test"

let select () =
  let qb = sizeof_quantum_bit() in
  qb
;;

let big_array2_dump arr =
  for i = 0 to pred(Bigarray.Array2.dim1 arr) do
    for j = 0 to pred(Bigarray.Array2.dim2 arr) do
      Printf.printf "  %d,%d:%3d" i j arr.{i,j};
    done;
    Printf.printf "\n";
  done;
  flush stdout;
;;


external image_of_bigarray: ('a, 'b, 'c) Bigarray.Array3.t -> image_handle = "constituteimage_from_big_array_char"


(* }}} *)


(* vim: sw=2 ts=2 sts=2 et fdm=marker
 *)
