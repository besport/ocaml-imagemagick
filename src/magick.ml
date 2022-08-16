(* GraphicsMagick bindings for OCaml
 * Copyright (C) 2022  Florent Monnier
 *
 * Permission is granted to anyone to use this software for any
 * purpose, including commercial applications, and to modify it
 * and redistribute it freely.
 *)

(* GraphicsMagick API documentation:
 * http://www.graphicsmagick.org/api/api.html
 *)

external initialize: unit -> unit = "caml_InitializeMagick"
external destroy: unit -> unit = "caml_DestroyMagick"

type image
type images

external read_image: filename:string -> image = "caml_ReadImage"
external write_image: image -> filename:string -> unit = "caml_WriteImage"

external blob_to_image: blob:string -> image = "caml_BlobToImage"

external get_canvas: width:int -> height:int -> color:string -> image = "caml_CanvasImage"

external clone: image -> image = "caml_CloneImage"

external image_width: image -> int = "caml_ImageWidth"
external image_height: image -> int = "caml_ImageHeight"

external display: image -> unit = "caml_DisplayImages"

external destroy_image: image -> unit = "caml_DestroyImage"


(* effects *)

external blur: image -> radius:float -> sigma:float -> image = "caml_BlurImage"
external motion_blur: image -> radius:float -> sigma:float -> angle:float -> image = "caml_MotionBlurImage"
external emboss: image -> radius:float -> sigma:float -> image = "caml_EmbossImage"
external sharpen: image -> radius:float -> sigma:float -> image = "caml_SharpenImage"
external edge: image -> radius:float -> image = "caml_EdgeImage"
external enhance: image -> image = "caml_EnhanceImage"
external shade: image -> gray:int -> azimuth:float -> elevation:float -> image = "caml_ShadeImage"

let blur image ?(radius = 0.0) ~sigma () =
  blur image ~radius ~sigma;
;;


(* fx *)

external charcoal: image -> radius:float -> sigma:float -> image = "caml_CharcoalImage"
external implode: image -> amount:float -> image = "caml_ImplodeImage"

external morph: images -> frames:int -> images = "caml_MorphImages"

external oil_paint: image -> radius:float -> image = "caml_OilPaintImage"
external swirl: image -> degrees :float -> image = "caml_SwirlImage"

external wave: image -> amplitude:float -> length:float -> image = "caml_WaveImage"


(* enhance *)

external contrast: image -> sharpen:int -> unit = "caml_ContrastImage"
external equalize: image -> unit = "caml_EqualizeImage"
external gamma: image -> level:string -> unit = "caml_GammaImage"
external level: image -> level:string -> unit = "caml_LevelImage"

module Channel = struct
type channel_type =
  | Undefined
  | Red
  | Cyan
  | Green
  | Magenta
  | Blue
  | Yellow
  | Opacity
  | Black
  | Matte
  | All
  | Gray
end

external level_channel: image ->  
    channel:Channel.channel_type ->
    black_point:float -> mid_point:float -> white_point:float -> unit
  = "caml_LevelImageChannel"

external modulate: image -> string -> unit = "caml_ModulateImage"
external negate: image -> int -> unit = "caml_NegateImage"
external normalize: image -> unit = "caml_NormalizeImage"


(* transform *)

external flip: image -> image = "caml_FlipImage"
external flop: image -> image = "caml_FlopImage"

type rectangle_info = {
  x: int;
  y: int;
  width: int;
  height: int;
}

external crop: image -> rectangle_info -> image = "caml_CropImage"
external shave: image -> rectangle_info -> image = "caml_ShaveImage"

let shave img (width, height) =
  (* x and y are not used *)
  shave img { x=0; y=0; width; height };
;;

external roll: image -> x_offset:int -> y_offset:int -> image
  = "caml_RollImage"


(* resize *)

external sample: image -> width:int -> height:int -> image = "caml_SampleImage"
external scale: image -> width:int -> height:int -> image = "caml_ScaleImage"
external thumbnail: image -> width:int -> height:int -> image = "caml_ThumbnailImage"

external magnify: image -> image = "caml_MagnifyImage"
external minify: image -> image = "caml_MinifyImage"


module Filter = struct
type filter_type =
  | Undefined
  | DefaultResize
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
end

external resize: image -> width:int -> height:int -> filter:Filter.filter_type -> blur:float -> image = "caml_ResizeImage"

let resize image ~width ~height ?(filter = Filter.DefaultResize) ?(blur=1.0) () =
  resize image ~width ~height ~filter ~blur;
;;


(* composite *)

module CompositeOp = struct
type composite_operator =
  | Undefined
  | Over
  | In
  | Out
  | Atop
  | Xor
  | Plus
  | Minus
  | Add
  | Subtract
  | Difference
  | Multiply
  | Bumpmap
  | Copy
  | CopyRed
  | CopyGreen
  | CopyBlue
  | CopyOpacity
  | Clear
  | Dissolve
  | Displace
  | Modulate
  | Threshold
  | No
  | Darken
  | Lighten
  | Hue
  | Saturate
  | Colorize
  | Luminize
  | Screen
  | Overlay
  | CopyCyan
  | CopyMagenta
  | CopyYellow
  | CopyBlack
  | Divide
  | HardLight
  | Exclusion
  | ColorDodge
  | ColorBurn
  | SoftLight
  | LinearBurn
  | LinearDodge
  | LinearLight
  | VividLight
  | PinLight
  | HardMix

let to_string = function
  | Undefined   -> "Undefined"
  | Over        -> "Over"
  | In          -> "In"
  | Out         -> "Out"
  | Atop        -> "Atop"
  | Xor         -> "Xor"
  | Plus        -> "Plus"
  | Minus       -> "Minus"
  | Add         -> "Add"
  | Subtract    -> "Subtract"
  | Difference  -> "Difference"
  | Multiply    -> "Multiply"
  | Bumpmap     -> "Bumpmap"
  | Copy        -> "Copy"
  | CopyRed     -> "CopyRed"
  | CopyGreen   -> "CopyGreen"
  | CopyBlue    -> "CopyBlue"
  | CopyOpacity -> "CopyOpacity"
  | Clear       -> "Clear"
  | Dissolve    -> "Dissolve"
  | Displace    -> "Displace"
  | Modulate    -> "Modulate"
  | Threshold   -> "Threshold"
  | No          -> "No"
  | Darken      -> "Darken"
  | Lighten     -> "Lighten"
  | Hue         -> "Hue"
  | Saturate    -> "Saturate"
  | Colorize    -> "Colorize"
  | Luminize    -> "Luminize"
  | Screen      -> "Screen"
  | Overlay     -> "Overlay"
  | CopyCyan    -> "CopyCyan"
  | CopyMagenta -> "CopyMagenta"
  | CopyYellow  -> "CopyYellow"
  | CopyBlack   -> "CopyBlack"
  | Divide      -> "Divide"
  | HardLight   -> "HardLight"
  | Exclusion   -> "Exclusion"
  | ColorDodge  -> "ColorDodge"
  | ColorBurn   -> "ColorBurn"
  | SoftLight   -> "SoftLight"
  | LinearBurn  -> "LinearBurn"
  | LinearDodge -> "LinearDodge"
  | LinearLight -> "LinearLight"
  | VividLight  -> "VividLight"
  | PinLight    -> "PinLight"
  | HardMix     -> "HardMix"

let of_string = function
  | "Undefined"   -> Undefined
  | "Over"        -> Over
  | "In"          -> In
  | "Out"         -> Out
  | "Atop"        -> Atop
  | "Xor"         -> Xor
  | "Plus"        -> Plus
  | "Minus"       -> Minus
  | "Add"         -> Add
  | "Subtract"    -> Subtract
  | "Difference"  -> Difference
  | "Multiply"    -> Multiply
  | "Bumpmap"     -> Bumpmap
  | "Copy"        -> Copy
  | "CopyRed"     -> CopyRed
  | "CopyGreen"   -> CopyGreen
  | "CopyBlue"    -> CopyBlue
  | "CopyOpacity" -> CopyOpacity
  | "Clear"       -> Clear
  | "Dissolve"    -> Dissolve
  | "Displace"    -> Displace
  | "Modulate"    -> Modulate
  | "Threshold"   -> Threshold
  | "No"          -> No
  | "Darken"      -> Darken
  | "Lighten"     -> Lighten
  | "Hue"         -> Hue
  | "Saturate"    -> Saturate
  | "Colorize"    -> Colorize
  | "Luminize"    -> Luminize
  | "Screen"      -> Screen
  | "Overlay"     -> Overlay
  | "CopyCyan"    -> CopyCyan
  | "CopyMagenta" -> CopyMagenta
  | "CopyYellow"  -> CopyYellow
  | "CopyBlack"   -> CopyBlack
  | "Divide"      -> Divide
  | "HardLight"   -> HardLight
  | "Exclusion"   -> Exclusion
  | "ColorDodge"  -> ColorDodge
  | "ColorBurn"   -> ColorBurn
  | "SoftLight"   -> SoftLight
  | "LinearBurn"  -> LinearBurn
  | "LinearDodge" -> LinearDodge
  | "LinearLight" -> LinearLight
  | "VividLight"  -> VividLight
  | "PinLight"    -> PinLight
  | "HardMix"     -> HardMix
  | _ -> invalid_arg "Magick.CompositeOp.of_string"

end

external composite: image -> CompositeOp.composite_operator -> image -> x_offset:int -> y_offset:int -> unit = "caml_CompositeImage"

let composite image1 ~compose image2 ?(x_offset=0) ?(y_offset=0) () =
  composite image1 compose image2 ~x_offset ~y_offset;
;;


(* image list *)

module ImgList = struct

type img_list = images

external new_image_list: unit -> img_list = "caml_NewImageList"

external destroy_image_list: img_list -> unit = "caml_DestroyImageList"

external append_image: img_list -> image -> img_list = "caml_AppendImageToList"

external prepend_image: img_list -> image -> img_list = "caml_PrependImageToList"

external get_first_image: img_list -> image = "caml_GetFirstImageInList"

external get_image: img_list -> offset:int -> image = "caml_GetImageFromList"

external length: img_list -> int = "caml_GetImageListLength"

external get_index: img_list -> int = "caml_GetImageIndexInList"

end


(* draw *)

module Draw = struct

type context

external allocate_context: image -> context
  = "caml_DrawAllocateContext"

external stroke_color_string: context -> string -> unit
  = "caml_DrawSetStrokeColorString"

external fill_color_string: context -> string -> unit
  = "caml_DrawSetFillColorString"

external stroke_width: context -> float -> unit
  = "caml_DrawSetStrokeWidth"

external circle: context -> ox:float -> oy:float -> px:float -> py:float -> unit
  = "caml_DrawCircle"

external rectangle: context -> x1:float -> y1:float -> x2:float -> y2:float -> unit
  = "caml_DrawRectangle"

external arc: context -> p1:float * float -> p2:float * float -> rot:float * float -> unit
  = "caml_DrawArc"

external render: context -> unit
  = "caml_DrawRender"

end


(* describe *)

external describe: image -> unit = "caml_DescribeImage"


(* vim: sw=2 ts=2 sts=2 et
 *)
