external sizeof_quantum : unit -> int = "im_sizeof_quantum"
external sizeof_quantum_bit : unit -> int = "im_sizeof_quantum_bit"
type image_handle
external read_image : filename:string -> image_handle = "im_readimage"
external get_canvas : width:int -> height:int -> color:string -> image_handle
  = "im_getimagecanvas"
external create_image :
  width:int -> height:int -> pseudo_format:string -> image_handle
  = "im_create_image"
external clone_image : image_handle -> image_handle = "im_cloneimage"
external write_image : image_handle -> filename:string -> unit
  = "im_writeimage"
external display : image_handle -> unit = "im_displayimages"
external image_to_stdout : image_handle -> unit = "imper_imagetoblob_stdout"
external blob_of_image : image_handle -> int list = "imper_imagetoblob_bytes"
val dump_to_stdout : image_handle -> unit
external get_image_width : image_handle -> int = "imper_getimagewidth"
external get_image_height : image_handle -> int = "imper_getimageheight"
external get_image_depth : image_handle -> int = "imper_getimagedepth"
external get_image_quality : image_handle -> int = "imper_getimagequality"
external get_image_mimetype : image_handle -> string
  = "imper_getimagemimetype"
external get_image_size : image_handle -> string = "imper_getimagesize"
external get_image_colors : image_handle -> int = "imper_getimagecolors"
external get_image_colorspace : image_handle -> int
  = "imper_getimagecolorspace"
external ping_image_infos : string -> int * int * int * int * int * string
  = "imper_ping_image_infos"
external ping_image : string -> bool = "imper_ping_image"
external get_number_colors : image_handle -> int = "imper_getimagehistogram"
external get_image_histogram : image_handle -> histogram_file:string -> int
  = "imper_getnumbercolors"
external get_max_colormap : unit -> int = "imper_getmaxcolormap"
type image_type =
    Undefined_image_type
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
external get_image_type : image_handle -> image_type = "imper_getimagetype"
val string_of_image_type : image_type -> string
type magick_boolean = MagickFalse | MagickTrue
val magick_boolean_of_string : string -> magick_boolean
type noise_type =
    UndefinedNoise
  | UniformNoise
  | GaussianNoise
  | MultiplicativeGaussianNoise
  | ImpulseNoise
  | LaplacianNoise
  | PoissonNoise
type resize_filter =
    Undefined_resize_filter
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
val resize_filter_of_string : string -> resize_filter
val resize_filter_of_string' : string -> resize_filter
val string_of_resize_filter : resize_filter -> string
type channel_type =
    Undefined_Channel
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
val channel_type_of_string : string -> channel_type
val channel_type_of_string' : string -> channel_type
val string_of_channel_type : channel_type -> string
type composite_operator =
    Undefined_composite_operator
  | No_composite_operator
  | Add
  | Atop
  | Blend
  | Bumpmap
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
  | CopyOpacity
  | CopyRed
  | CopyYellow
  | Darken
  | DstAtop
  | Dst
  | DstIn
  | DstOut
  | DstOver
  | Difference
  | Displace
  | Dissolve
  | Exclusion
  | HardLight
  | Hue
  | In
  | Lighten
  | Luminize
  | Minus
  | Modulate
  | Multiply
  | Out
  | Over
  | Overlay
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
  | Subtract
  | Threshold
  | Xor
val composite_operator_of_string : string -> composite_operator
val composite_operator_of_string' : string -> composite_operator
val string_of_composite_operator : composite_operator -> string
module Imper :
  sig
    external plasma_image :
      image_handle ->
      x1:int ->
      y1:int -> x2:int -> y2:int -> attenuate:int -> depth:int -> unit
      = "imper_plasmaimage_bytecode" "imper_plasmaimage_native"
    external flip : image_handle -> unit = "imper_flipimage"
    external flop : image_handle -> unit = "imper_flopimage"
    external magnify : image_handle -> unit = "imper_magnifyimage"
    external minify : image_handle -> unit = "imper_minifyimage"
    external enhance : image_handle -> unit = "imper_enhanceimage"
    external trim : image_handle -> unit = "imper_trimimage"
    external despeckle : image_handle -> unit = "imper_despeckle"
    val negate : image_handle -> ?grayscale:magick_boolean -> unit -> unit
    external contrast : image_handle -> sharpen:magick_boolean -> unit
      = "imper_contrastimage"
    external equalize : image_handle -> unit = "imper_equalizeimage"
    external normalize : image_handle -> unit = "imper_normalizeimage"
    external white_threshold : image_handle -> threshold:string -> unit
      = "imper_whitethresholdimage"
    external black_threshold : image_handle -> threshold:string -> unit
      = "imper_blackthresholdimage"
    external cyclecolormap : image_handle -> displace:int -> unit
      = "imper_cyclecolormapimage"
    external solarize : image_handle -> threshold:float -> unit
      = "imper_solarizeimage"
    external modulate' : image_handle -> factors:string -> unit
      = "imper_modulateimage"
    val modulate :
      image_handle ->
      ?brightness:int -> ?saturation:int -> ?hue:int -> unit -> unit
    val blur : image_handle -> ?radius:float -> sigma:float -> unit -> unit
    val gaussian_blur :
      image_handle -> ?radius:float -> sigma:float -> unit -> unit
    val motion_blur :
      image_handle ->
      ?radius:float -> sigma:float -> angle:float -> unit -> unit
    val charcoal :
      image_handle -> ?radius:float -> sigma:float -> unit -> unit
    external edge : image_handle -> radius:float -> unit = "imper_edgeimage"
    val emboss : image_handle -> ?radius:float -> sigma:float -> unit -> unit
    external implode : image_handle -> amount:float -> unit
      = "imper_implodeimage"
    external medianfilter : image_handle -> radius:float -> unit
      = "imper_medianfilterimage"
    external oilpaint : image_handle -> radius:float -> unit
      = "imper_oilpaintimage"
    external reduce_noise : image_handle -> radius:float -> unit
      = "imper_reducenoiseimage"
    external roll : image_handle -> x:int -> y:int -> unit
      = "imper_rollimage"
    val shade :
      image_handle ->
      ?gray:magick_boolean ->
      azimuth:float -> elevation:float -> unit -> unit
    external spread : image_handle -> radius:float -> unit
      = "imper_spreadimage"
    external swirl : image_handle -> degrees:float -> unit
      = "imper_swirlimage"
    val sharpen :
      image_handle -> ?radius:float -> sigma:float -> unit -> unit
    external unsharpmask :
      image_handle ->
      radius:float -> sigma:float -> amount:float -> threshold:float -> unit
      = "imper_unsharpmaskimage"
    external wave :
      image_handle -> amplitude:float -> wave_length:float -> unit
      = "imper_waveimage"
    external rotate : image_handle -> degrees:float -> unit
      = "imper_rotateimage"
    external shear : image_handle -> x:float -> y:float -> unit
      = "imper_shearimage"
    val affine_transform :
      image_handle ->
      ?tx:float ->
      ?ty:float ->
      ?sx:float -> ?sy:float -> ?rx:float -> ?ry:float -> unit -> unit
    external adaptive_threshold :
      image_handle -> width:int -> height:int -> offset:int -> unit
      = "imper_adaptivethresholdimage"
    external crop :
      image_handle -> x:int -> y:int -> width:int -> height:int -> unit
      = "imper_cropimage"
    external chop :
      image_handle -> x:int -> y:int -> width:int -> height:int -> unit
      = "imper_chopimage"
    external splice :
      image_handle -> x:int -> y:int -> width:int -> height:int -> unit
      = "imper_spliceimage"
    external colorize :
      image_handle -> string -> int -> int -> int -> int -> unit
      = "imper_colorizeimage_bytecode" "imper_colorizeimage_native"
    external acquire_pixel :
      image_handle -> int -> int -> int * int * int * int
      = "imper_acquireonepixel"
    val composite_image :
      image_handle ->
      image_handle ->
      compose:composite_operator -> ?x:int -> ?y:int -> unit -> unit
    external texture_image : image_handle -> image_handle -> unit
      = "imper_textureimage"
    external bilevel_channel :
      image_handle -> channel:channel_type -> float -> unit
      = "imper_bilevelimagechannel"
    val blur_channel :
      image_handle ->
      channel:channel_type -> ?radius:float -> sigma:float -> unit -> unit
    val gaussian_blur_channel :
      image_handle ->
      channel:channel_type -> ?radius:float -> sigma:float -> unit -> unit
    external radial_blur : image_handle -> angle:float -> unit
      = "imper_radialblurimage"
    external radial_blur_channel :
      image_handle -> channel:channel_type -> angle:float -> unit
      = "imper_radialblurimagechannel"
    val sharpen_image_channel :
      image_handle ->
      channel:channel_type -> ?radius:float -> sigma:float -> unit -> unit
    external add_noise : image_handle -> noise_type -> unit
      = "imper_addnoiseimage"
    external resize :
      image_handle ->
      width:int -> height:int -> filter:resize_filter -> blur:float -> unit
      = "imper_resizeimage"
    external sample : image_handle -> width:int -> height:int -> unit
      = "imper_sampleimage"
    external scale : image_handle -> width:int -> height:int -> unit
      = "imper_scaleimage"
    external thumbnail : image_handle -> width:int -> height:int -> unit
      = "imper_thumbnailimage"
    external set_image_colors : image_handle -> int -> unit
      = "imper_setimagecolors"
    external set_compression_quality : image_handle -> int -> unit
      = "imper_setcompressionquality"
    external set_image_type : image_handle -> image_type:image_type -> unit
      = "imper_setimagetype"
    external set_type : image_handle -> unit = "imper_setimagetype__"
    external strip_image : image_handle -> unit = "imper_stripimage"
    external level : image_handle -> string -> unit = "imper_levelimage"
    external level_channel :
      image_handle -> channel:channel_type -> float -> float -> float -> unit
      = "imper_levelimagechannel"
    external gamma_channel :
      image_handle -> channel:channel_type -> gamma:float -> unit
      = "imper_gammaimagechannel"
    external negate_channel :
      image_handle -> channel:channel_type -> magick_boolean -> unit
      = "imper_negateimagechannel"
    external ordered_dither : image_handle -> unit
      = "imper_orderedditherimage"
    external compress_colormap : image_handle -> unit
      = "imper_compressimagecolormap"
    external posterize :
      image_handle -> levels:int -> dither:magick_boolean -> unit
      = "imper_posterizeimage"
    external map_image :
      image_handle -> map_image:image_handle -> dither:magick_boolean -> unit
      = "imper_mapimage"
    external is_gray : image_handle -> bool = "imper_isgrayimage"
    external is_monochrome : image_handle -> bool = "imper_ismonochromeimage"
    external is_opaque : image_handle -> bool = "imper_isopaqueimage"
    external is_palette : image_handle -> bool = "imper_ispaletteimage"
    external is_taint : image_handle -> bool = "imper_istaintimage"
    external is_equal :
      image_handle -> image_handle -> bool * float * float * float
      = "imper_isimagesequal"
    type line_cap = UndefinedCap | ButtCap | RoundCap | SquareCap
    type line_join = UndefinedJoin | MiterJoin | RoundJoin | BevelJoin
    type color = int * int * int * int
    val channels_of_color : color -> int * int * int * int
    external acquire_pixel_opacity :
      image_handle -> int -> int -> int * int * int * int
      = "imper_acquireonepixel_opacity"
    external set_image_opacity : image_handle -> opacity:int -> unit
      = "imper_setimageopacity"
    external color_of_string : string -> color = "imper_querycolordatabase"
    val color_of_rgbo_tuple : int * int * int * int -> color
    val rgbo_tuple_of_color : color -> int * int * int * int
    val max_color_map : int
    val add_colors : color -> color -> color
    val sub_colors : color -> color -> color
    val mul_colors : color -> color -> color
    val dump_color : color -> unit
    val div_colors : color -> color -> color
    val rgb_string_of_color : color -> string
    val rgba_string_of_color : color -> string
    val hexa_string_of_color : color -> string
    val color_of_hex : string -> int * int * int * int
    val black : color
    val transparent : color
    type affine_matrix = {
      sx : float;
      rx : float;
      ry : float;
      sy : float;
      tx : float;
      ty : float;
    }
    val identity_matrix : affine_matrix
    val tuple_of_matrix :
      affine_matrix:affine_matrix ->
      float * float * float * float * float * float
    external set_pixel :
      image_handle ->
      x:int ->
      y:int -> red:int -> green:int -> blue:int -> opacity:int -> unit
      = "imper_draw_point_bytecode" "imper_draw_point_native"
    val draw_point : image_handle -> x:int -> y:int -> color:color -> unit
    val draw_line :
      image_handle ->
      x0:int ->
      y0:int ->
      x1:int ->
      y1:int ->
      ?fill_color:color ->
      ?stroke_color:color ->
      ?stroke_antialias:magick_boolean ->
      ?stroke_width:float -> ?line_cap:line_cap -> unit -> unit
    val draw_circle :
      image_handle ->
      x0:int ->
      y0:int ->
      x1:int ->
      y1:int ->
      ?fill_color:color ->
      ?stroke_color:color ->
      ?stroke_width:float ->
      ?stroke_antialias:magick_boolean ->
      ?affine_matrix:affine_matrix -> unit -> unit
    val draw_rectangle :
      image_handle ->
      x0:int ->
      y0:int ->
      x1:int ->
      y1:int ->
      ?fill_color:color ->
      ?stroke_color:color ->
      ?stroke_width:float ->
      ?stroke_antialias:magick_boolean ->
      ?line_join:line_join -> ?affine_matrix:affine_matrix -> unit -> unit
    val draw_round_rectangle :
      image_handle ->
      x0:int ->
      y0:int ->
      x1:int ->
      y1:int ->
      wc:int ->
      hc:int ->
      ?fill_color:color ->
      ?stroke_color:color ->
      ?stroke_antialias:magick_boolean ->
      ?stroke_width:float -> ?affine_matrix:affine_matrix -> unit -> unit
    val draw_arc :
      image_handle ->
      x0:int ->
      y0:int ->
      x1:int ->
      y1:int ->
      a0:int ->
      a1:int ->
      ?fill_color:color ->
      ?stroke_color:color ->
      ?stroke_antialias:magick_boolean ->
      ?stroke_width:float ->
      ?line_cap:line_cap -> ?affine_matrix:affine_matrix -> unit -> unit
    val draw_ellipse :
      image_handle ->
      cx:int ->
      cy:int ->
      rx:int ->
      ry:int ->
      ?a0:int ->
      ?a1:int ->
      ?fill_color:color ->
      ?stroke_color:color ->
      ?stroke_antialias:magick_boolean ->
      ?stroke_width:float -> ?affine_matrix:affine_matrix -> unit -> unit
    val draw_polyline :
      image_handle ->
      coords:(int * int) array ->
      ?fill_color:color ->
      ?stroke_color:color ->
      ?stroke_antialias:magick_boolean ->
      ?stroke_width:float ->
      ?line_join:line_join ->
      ?line_cap:line_cap -> ?affine_matrix:affine_matrix -> unit -> unit
    val draw_polygon :
      image_handle ->
      coords:(int * int) array ->
      ?fill_color:color ->
      ?stroke_color:color ->
      ?stroke_antialias:magick_boolean ->
      ?stroke_width:float ->
      ?line_join:line_join -> ?affine_matrix:affine_matrix -> unit -> unit
    val draw_bezier :
      image_handle ->
      coords:(int * int) array ->
      ?fill_color:color ->
      ?stroke_color:color ->
      ?stroke_antialias:magick_boolean ->
      ?stroke_width:float ->
      ?line_cap:line_cap -> ?affine_matrix:affine_matrix -> unit -> unit
    val draw_path :
      image_handle ->
      path:string ->
      ?fill_color:color ->
      ?stroke_color:color ->
      ?stroke_antialias:magick_boolean ->
      ?stroke_width:float ->
      ?line_join:line_join ->
      ?line_cap:line_cap -> ?affine_matrix:affine_matrix -> unit -> unit
    type style_type =
        Undefined_Style
      | Normal_Style
      | Italic
      | Oblique
      | Any_Style
    type decoration_type =
        Undefined_Decoration
      | No_Decoration
      | Underline
      | Overline
      | LineThrough
    type stretch_type =
        Undefined_Stretch
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
    val draw_text :
      image_handle ->
      text:string ->
      ?font:string ->
      x:int ->
      y:int ->
      point_size:float ->
      ?density_x:int ->
      ?density_y:int ->
      ?style:style_type ->
      ?weight:int ->
      ?fill_color:color ->
      ?stroke_color:color ->
      ?decoration:decoration_type ->
      ?stretch:stretch_type ->
      ?stroke_width:float ->
      ?stroke_antialias:magick_boolean ->
      ?text_antialias:magick_boolean ->
      ?encoding:string -> ?affine_matrix:affine_matrix -> unit -> unit
    type metrics_infos = {
      ascent : float;
      descent : float;
      text_width : float;
      text_height : float;
      max_advance : float;
      underline_position : float;
      underline_thickness : float;
      pixels_per_em_x : float;
      pixels_per_em_y : float;
      bounds_x1 : float;
      bounds_y1 : float;
      bounds_x2 : float;
      bounds_y2 : float;
    }
    val get_metrics :
      image_handle ->
      text:string ->
      ?font:string ->
      x:int ->
      y:int ->
      point_size:float ->
      ?density_x:int ->
      ?density_y:int ->
      ?style:style_type ->
      ?weight:int ->
      ?decoration:decoration_type ->
      ?stretch:stretch_type -> ?stroke_width:float -> unit -> metrics_infos
    val transform_metrics :
      metrics:metrics_infos -> affine_matrix:affine_matrix -> metrics_infos
    external draw_text_devel : image_handle -> text:string -> unit
      = "imper_draw_text_new1"
    external draw_mvg : image_handle -> mvg:string -> unit = "imper_draw_mvg"
    external get_raw : image_handle -> (int * int * int * int) array array
      = "imper_get_raw"
    external get_raw' : image_handle -> (int * int * int * int) array array
      = "imper_get_raw2"
    external get_raw_opacity :
      image_handle -> (int * int * int * int) array array
      = "imper_get_raw_opacity"
    external get_raw_without_alpha :
      image_handle -> (int * int * int) array array
      = "imper_get_raw_without_alpha"
    external get_raw_gl_indexed :
      image_handle -> (int * int * int * int) array
      = "imper_get_raw_gl_indexed"
    external get_raw_gl_indexed_without_alpha :
      image_handle -> (int * int * int) array
      = "imper_get_raw_gl_indexed_without_alpha"
    val set_raw : raw:(int * int * int * int) array array -> image_handle
    val set_raw_c : raw:(int * int * int * int) array array -> image_handle
    type image_list_handle
    external new_image_list : unit -> image_list_handle
      = "imper_new_image_list"
    external no_op : image_handle -> unit = "imper_no_op"
    external display_images : image_list_handle -> unit = "im_displayimages"
    val append_image_to_list :
      image_list_handle -> image_handle -> ?delay:int -> unit -> unit
    external image_list_length : image_list_handle -> int
      = "imper_getimagelistlength"
    external deconstruct_images : image_list_handle -> unit
      = "imper_deconstructimages"
    external coalesce_images : image_list_handle -> unit
      = "imper_coalesceimages"
    external flatten_images : image_list_handle -> unit
      = "imper_flattenimages"
    val average_images : image_list_handle -> image_handle
    external animate_images : image_list_handle -> unit
      = "imper_animateimages"
    external write_images : image_list_handle -> string -> unit
      = "im_writeimage"
    external get_last_image_in_list : image_list_handle -> image_handle
      = "imper_getlastimageinlist"
    external get_first_image_in_list : image_list_handle -> image_handle
      = "imper_getfirstimageinlist"
    external has_link : image_handle -> bool = "imper_has_link"
    type stack = Left_to_right | Top_to_bottom
    val stack_dir_of_string : stack:string -> stack
    val append_images : image_list_handle -> stack:stack -> image_handle
  end
module Fun :
  sig
    val create_image :
      width:int -> height:int -> pseudo_format:string -> unit -> image_handle
    val get_canvas :
      width:int -> height:int -> color:string -> unit -> image_handle
    val read_image : filename:string -> unit -> image_handle
    val blur :
      ?radius:float -> sigma:float -> unit -> image_handle -> image_handle
    val radial_blur : angle:float -> unit -> image_handle -> image_handle
    val radial_blur_channel :
      channel:channel_type ->
      angle:float -> unit -> image_handle -> image_handle
    val charcoal :
      ?radius:float -> sigma:float -> unit -> image_handle -> image_handle
    val edge : radius:float -> unit -> image_handle -> image_handle
    val emboss :
      ?radius:float -> sigma:float -> unit -> image_handle -> image_handle
    val gaussian_blur :
      ?radius:float -> sigma:float -> unit -> image_handle -> image_handle
    val implode : amount:float -> unit -> image_handle -> image_handle
    val medianfilter : radius:float -> unit -> image_handle -> image_handle
    val motion_blur :
      ?radius:float ->
      sigma:float -> angle:float -> unit -> image_handle -> image_handle
    val oilpaint : radius:float -> unit -> image_handle -> image_handle
    val reduce_noise : radius:float -> unit -> image_handle -> image_handle
    val roll : x:int -> y:int -> unit -> image_handle -> image_handle
    val shade :
      ?gray:magick_boolean ->
      azimuth:float ->
      elevation:float -> unit -> image_handle -> image_handle
    val sharpen :
      ?radius:float -> sigma:float -> unit -> image_handle -> image_handle
    val spread : radius:float -> unit -> image_handle -> image_handle
    val swirl : degrees:float -> unit -> image_handle -> image_handle
    val unsharpmask :
      radius:float ->
      sigma:float ->
      amount:float -> threshold:float -> unit -> image_handle -> image_handle
    val wave :
      amplitude:float ->
      wave_length:float -> unit -> image_handle -> image_handle
    val rotate : degrees:float -> unit -> image_handle -> image_handle
    val shear : x:float -> y:float -> unit -> image_handle -> image_handle
    val sample :
      width:int -> height:int -> unit -> image_handle -> image_handle
    val scale :
      width:int -> height:int -> unit -> image_handle -> image_handle
    val thumbnail :
      width:int -> height:int -> unit -> image_handle -> image_handle
    val adaptive_threshold :
      width:int ->
      height:int -> offset:int -> unit -> image_handle -> image_handle
    val blur_channel :
      channel:channel_type ->
      ?radius:float -> sigma:float -> unit -> image_handle -> image_handle
    val gaussian_blur_channel :
      channel:channel_type ->
      ?radius:float -> sigma:float -> unit -> image_handle -> image_handle
    val add_noise :
      noise_type:noise_type -> unit -> image_handle -> image_handle
    val resize :
      width:int ->
      height:int ->
      filter:resize_filter ->
      blur:float -> unit -> image_handle -> image_handle
    val enhance : unit -> image_handle -> image_handle
    val despeckle : unit -> image_handle -> image_handle
    val minify : unit -> image_handle -> image_handle
    val magnify : unit -> image_handle -> image_handle
    val flip : unit -> image_handle -> image_handle
    val flop : unit -> image_handle -> image_handle
    val splice :
      x:int ->
      y:int ->
      width:int -> height:int -> unit -> image_handle -> image_handle
    val crop :
      x:int ->
      y:int ->
      width:int -> height:int -> unit -> image_handle -> image_handle
    val affine_transform :
      ?tx:float ->
      ?ty:float ->
      ?sx:float ->
      ?sy:float ->
      ?rx:float -> ?ry:float -> unit -> image_handle -> image_handle
    val negate :
      ?grayscale:magick_boolean -> unit -> image_handle -> image_handle
    val contrast :
      sharpen:magick_boolean -> unit -> image_handle -> image_handle
    val equalize : unit -> image_handle -> image_handle
    val normalize : unit -> image_handle -> image_handle
    val black_threshold :
      threshold:string -> unit -> image_handle -> image_handle
    val white_threshold :
      threshold:string -> unit -> image_handle -> image_handle
    val cyclecolormap : displace:int -> unit -> image_handle -> image_handle
    val solarize : threshold:float -> unit -> image_handle -> image_handle
    val strip : unit -> image_handle -> image_handle
    val gamma_channel :
      channel:channel_type ->
      gamma:float -> unit -> image_handle -> image_handle
    val level : levels:string -> unit -> image_handle -> image_handle
    val level_channel :
      channel:channel_type ->
      black_point:float ->
      white_point:float ->
      gamma:float -> unit -> image_handle -> image_handle
    val negate_channel :
      channel:channel_type ->
      grayscale:magick_boolean -> unit -> image_handle -> image_handle
    val ordered_dither : unit -> image_handle -> image_handle
    val composite_image :
      compose:composite_operator ->
      ?x:int ->
      ?y:int ->
      unit ->
      img_below:image_handle -> img_above:image_handle -> image_handle
    val texture_image :
      img:image_handle -> tex_img:image_handle -> image_handle
    val modulate :
      ?brightness:int ->
      ?saturation:int -> ?hue:int -> unit -> image_handle -> image_handle
    val modulate' : factors:string -> unit -> image_handle -> image_handle
    val view : unit -> image_handle -> image_handle
  end
external get_magick_copyright : unit -> string = "imper_getmagickcopyright"
external get_magick_home_url : unit -> string = "imper_getmagickhomeurl"
external get_magick_release_date : unit -> string
  = "imper_getmagickreleasedate"
external get_magick_version : unit -> int * string = "imper_getmagickversion"
external get_magick_quantum_depth : unit -> int * string
  = "imper_getmagickquantumdepth"
external get_magick_quantum_range : unit -> int * string
  = "imper_getmagickquantumrange"
external get_binding_version : unit -> string = "imper_getbindingversion"
type shared_data =
    UI8 of
      (int, Bigarray.int8_unsigned_elt, Bigarray.c_layout) Bigarray.Array3.t
  | UI16 of
      (int, Bigarray.int16_unsigned_elt, Bigarray.c_layout) Bigarray.Array3.t
  | UI32 of (int, Bigarray.int32_elt, Bigarray.c_layout) Bigarray.Array3.t
  | UI64 of (int, Bigarray.int64_elt, Bigarray.c_layout) Bigarray.Array3.t
external inspect_big_array : ('a, 'b, 'c) Bigarray.Array2.t -> unit
  = "ml_big_array_test"
val select : unit -> int
val big_array2_dump : (int, 'a, 'b) Bigarray.Array2.t -> unit
external image_of_bigarray : ('a, 'b, 'c) Bigarray.Array3.t -> image_handle
  = "constituteimage_from_big_array_char"
type coords_2d = { x : int; y : int; }
type dimentions = { width : int; height : int; }
type bounding_box = { pos : coords_2d; dims : dimentions; }
type gradient_spreadMethod = Pad_spread | Repeat_spread | Reflect_spread
val _linear_gradient :
  width:int ->
  height:int ->
  a:coords_2d ->
  b:coords_2d ->
  ?spread_method:gradient_spreadMethod ->
  ?bounding_box:bounding_box -> unit -> image_handle
val linear_gradient :
  image_handle ->
  a:coords_2d ->
  b:coords_2d ->
  stop:(float * string) list ->
  ?matrix:(float * float * float) * (float * float * float) *
          (float * float * float) ->
  ?spread_method:gradient_spreadMethod ->
  ?bounding_box:bounding_box -> unit -> unit
