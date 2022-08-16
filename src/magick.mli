(** GraphicsMagick bindings for OCaml *)
(* Copyright (C) 2022  Florent Monnier
 *
 * Permission is granted to anyone to use this software for any
 * purpose, including commercial applications, and to modify it
 * and redistribute it freely.
 *)

(** {{:http://www.graphicsmagick.org/api/api.html}
     GraphicsMagick API documentation} *)

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


(** {3 Effects} *)

(** {{:http://www.graphicsmagick.org/api/effect.html}api doc} *)

val blur: image -> ?radius:float -> sigma:float -> unit -> image

external motion_blur: image -> radius:float -> sigma:float -> angle:float -> image
  = "caml_MotionBlurImage"

external emboss: image -> radius:float -> sigma:float -> image
  = "caml_EmbossImage"

external sharpen: image -> radius:float -> sigma:float -> image
  = "caml_SharpenImage"

external edge: image -> radius:float -> image = "caml_EdgeImage"

external enhance: image -> image = "caml_EnhanceImage"

external shade: image -> gray:int -> azimuth:float -> elevation:float -> image
  = "caml_ShadeImage"


(** {3 FX} *)

(** {{:http://www.graphicsmagick.org/api/fx.html}api doc} *)

external charcoal: image -> radius:float -> sigma:float -> image = "caml_CharcoalImage"
external implode: image -> amount:float -> image = "caml_ImplodeImage"

external morph: images -> frames:int -> images = "caml_MorphImages"

external oil_paint: image -> radius:float -> image = "caml_OilPaintImage"
external swirl: image -> degrees:float -> image = "caml_SwirlImage"

external wave: image -> amplitude:float -> length:float -> image = "caml_WaveImage"


(** {3 Enhance} *)

(** {{:http://www.graphicsmagick.org/api/enhance.html}api doc} *)

external contrast: image -> sharpen:int -> unit = "caml_ContrastImage"
external equalize: image -> unit = "caml_EqualizeImage"
external gamma: image -> level:string -> unit = "caml_GammaImage"
external level: image -> level:string -> unit = "caml_LevelImage"

module Channel: sig
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

external level_channel: image -> channel:Channel.channel_type ->
  black_point:float -> mid_point:float -> white_point:float -> unit
  = "caml_LevelImageChannel"

external modulate: image -> string -> unit = "caml_ModulateImage"

external negate: image -> int -> unit = "caml_NegateImage"

external normalize: image -> unit = "caml_NormalizeImage"


(** {3 Transform} *)

(** {{:http://www.graphicsmagick.org/api/transform.html}api doc} *)

external flip: image -> image = "caml_FlipImage"
external flop: image -> image = "caml_FlopImage"

type rectangle_info = { x: int; y: int; width: int; height: int; }

external crop: image -> rectangle_info -> image = "caml_CropImage"

val shave: image -> int * int -> image

external roll: image -> x_offset:int -> y_offset:int -> image
  = "caml_RollImage"


(** {3 Resize} *)

(** {{:http://www.graphicsmagick.org/api/resize.html}api doc} *)

external sample: image -> width:int -> height:int -> image
  = "caml_SampleImage"

external scale: image -> width:int -> height:int -> image
  = "caml_ScaleImage"

external thumbnail: image -> width:int -> height:int -> image
  = "caml_ThumbnailImage"

external magnify: image -> image = "caml_MagnifyImage"
external minify: image -> image = "caml_MinifyImage"


module Filter: sig
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

val resize: image -> width:int -> height:int ->
  ?filter:Filter.filter_type -> ?blur:float -> unit -> image


(** {3 Composite} *)

module CompositeOp: sig
  (** {4 Composite Operator} *)

  (** {{:http://www.graphicsmagick.org/api/types.html#compositeoperator}
       composite-operator api doc} *)
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

  val to_string: composite_operator -> string
  val of_string: string -> composite_operator
end

val composite: image -> compose:CompositeOp.composite_operator ->
  image -> ?x_offset:int -> ?y_offset:int -> unit -> unit
(** {{:http://www.graphicsmagick.org/api/composite.html}api doc} *)


module ImgList: sig
  (** {3 Image Lists} *)

  type img_list = images

  external new_image_list: unit -> img_list = "caml_NewImageList"
  external destroy_image_list: img_list -> unit = "caml_DestroyImageList"

  external append_image: img_list -> image -> img_list
    = "caml_AppendImageToList"

  external prepend_image: img_list -> image -> img_list
    = "caml_PrependImageToList"

  external get_first_image: img_list -> image = "caml_GetFirstImageInList"

  external get_image: img_list -> offset:int -> image
    = "caml_GetImageFromList"

  external length: img_list -> int = "caml_GetImageListLength"

  external get_index: img_list -> int = "caml_GetImageIndexInList"
end


(** {3 Draw} *)

module Draw: sig
  (** {3 Draw} *)

  (** {{:http://www.graphicsmagick.org/api/draw.html}api doc} *)

  type context

  external allocate_context: image -> context = "caml_DrawAllocateContext"

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


(** {3 describe} *)

external describe: image -> unit = "caml_DescribeImage"
(** {{:http://www.graphicsmagick.org/api/describe.html}api doc} *)

