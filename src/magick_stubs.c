/* {{{ COPYING 
 *
 * +---------------------------------------------------------------+
 * | Copyright (C) 2004, 2005, 2006, 2010  Florent Monnier         |
 * +---------------------------------------------------------------+
 * | This binding aims to provide the ImageMagick methods to OCaml |
 * +---------------------------------------------------------------+
 * | This software is provided 'as-is', without any express or     |
 * | implied warranty.  In no event will the authors be held       |
 * | liable for any damages arising from the use of this software. |
 * |                                                               |
 * | Permission is granted to anyone to use this software for any  |
 * | purpose, including commercial applications, and to alter it   |
 * | and redistribute it freely.                                   |
 * +---------------------------------------------------------------+
 * | Author: Florent Monnier <monnier.florent (at) gmail.com>      |
 * +---------------------------------------------------------------+
 *
 * }}} */

/* {{{ headers */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/fail.h>
#include <caml/callback.h>

#include <caml/custom.h>
#include <caml/printexc.h>

#include <caml/intext.h>
#include <caml/compatibility.h>
#include <caml/bigarray.h>

//define MAGICKCORE_EXCLUDE_DEPRECATED 1

#include <MagickCore/MagickCore.h>


#include "imagemagick_list.h"
#include "imagemagick.h"

#include <limits.h>

/* }}} */

#define GetExceptionInfo(e)
#define IsMagickInstantiated IsMagickCoreInstantiated

/* "ocaml.multimedia.2d_graphics.magick.imagemagick" */

/* {{{ alloc_image() */

Image *alloc_image(void)
{ 
    Image *img = malloc(sizeof(Image)) ;
    return img ;
}
/*
Image *alloc_image(void)
{ 
    Image *image ;
    ImageInfo *image_info ;

    image_info = CloneImageInfo((ImageInfo *) NULL) ;
    image = AllocateImage(image_info) ;
    DestroyImageInfo(image_info) ;
    return image ;
}
*/

/* }}} */
/* {{{ finalize_image() */

void
finalize_image(value image_bloc)
{
#if DEBUG
    Image *image;
    image = Field(image_bloc,1);
    if ( strlen(image->filename) ) {
        printf("ImageMagick: image finalisation « %s »\n", image->filename ); fflush(stdout);
    } else {
        printf("ImageMagick: image finalisation\n"); fflush(stdout);
    }
#endif

    if ( (Image *) Field(image_bloc,1) != (Image *) NULL ) {

        DestroyImage((Image *) Field(image_bloc,1));
#if DEBUG
    } else {
        printf("ImageMagick: attempt to finalize a null image\n"); fflush(stdout);
#endif
    }
}
/* Does not work very well:
 *
 * ImageMagick: image finalisation
 * ocamlrun: magick/image.c:1515: DestroyImage: Assertion `image->signature == 0xabacadabUL' failed.
 * Aborted
 *
 * @TODO find a guru to rewrite this part
 */

/* }}} */
/* {{{ finalize_images_list() */

void finalize_images_list(value image_bloc)
{
#if DEBUG
    Image *image;
    image = Field(image_bloc,1);
    if ( strlen(image->filename) ) {
        printf("ImageMagick: images_list finalisation « %s »\n", image->filename ); fflush(stdout);
    } else {
        printf("ImageMagick: images_list finalisation\n"); fflush(stdout);
    }
#endif

    if ( (Image *) Field(image_bloc,1) != (Image *) NULL ) {

        /* DestroyImage((Image *) Field(image_bloc,1)); */
        DestroyImageList((Image *) Field(image_bloc,1));
        /*
        Image *DestroyImageList(Image *image);
        */
#if DEBUG
    } else {
        printf("ImageMagick: attempt to finalize a null image\n"); fflush(stdout);
#endif
    }
}
/* Does not work very well:
 *
 * ImageMagick: image finalisation
 * ocamlrun: magick/image.c:1515: DestroyImage: Assertion `image->signature == 0xabacadabUL' failed.
 * Aborted
 *
 * @TODO find an ocaml-guru to rewrite this part
 */

/* }}} */

/* {{{ im_readimage() 
 *
 * Image *ReadImage(const ImageInfo *image_info, ExceptionInfo *exception)
 */

CAMLprim value
im_readimage(value input_image_name)
{
    CAMLparam1(input_image_name);

    CAMLlocal1(image_bloc);

    ExceptionInfo
        exception;

    ExceptionInfo
        *exc_info;

    ImageInfo
        *image_info;


    image_bloc = caml_alloc_final(2, (*finalize_image), sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    if (IsMagickInstantiated() == MagickFalse) {
        MagickCoreGenesis(getenv("PWD"), MagickTrue);
    }

    exc_info = AcquireExceptionInfo();

    image_info = CloneImageInfo((ImageInfo *) NULL);
    /* GetImageInfo(image_info) ; */
    (void) strcpy(image_info->filename, String_val(input_image_name));

    Field(image_bloc,1) = (value) ReadImage(image_info, exc_info);

    DestroyImageInfo(image_info);

#if 0
    if (exception.severity != UndefinedException) {
        if ( (Image *)Field(image_bloc,1) != (Image *) NULL) {
            DestroyImage((Image *) Field(image_bloc,1));  /* TODO: test me */
        }
        caml_failwith( exception.reason );
        /* @TODO  exception.description */
    }
#endif

    DestroyExceptionInfo(exc_info);

    if ((Image *) Field(image_bloc,1) == (Image *) NULL) {
        /* exit(1) ; */
        caml_failwith("read_image failed");
    }

    CAMLreturn( image_bloc );
}
/* }}} */
/* {{{ im_getimagecanvas() */
CAMLprim value
im_getimagecanvas(value width, value height, value color)
{
    CAMLparam3(width, height, color);

    CAMLlocal1(image_bloc);

    char
        str_buffer[ MaxTextExtent ];

    int str_len;

    ExceptionInfo
        exception;

    ExceptionInfo
        *exc_info;

    ImageInfo
        *image_info;

    if (IsMagickInstantiated() == MagickFalse) {
        MagickCoreGenesis(getenv("PWD"), MagickTrue);
    }

    image_info = CloneImageInfo((ImageInfo *) NULL);

    /*
    typedef struct _ImageInfo
    {
      ...
      char *size;
      char filename[MaxTextExtent];
      ...
    } ImageInfo
    */

    /* Give image size */
    str_len = snprintf( str_buffer, MaxTextExtent, "%ldx%ld", Long_val(width), Long_val(height) );
    (void) CloneString(&image_info->size, str_buffer);

    /* Give image color */
    str_len = snprintf( str_buffer, MaxTextExtent, "xc:%s", String_val(color) );
    strncpy( image_info->filename, str_buffer, str_len );


    image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    exc_info = AcquireExceptionInfo();

    Field(image_bloc,1) = (value) ReadImage(image_info, exc_info);

    DestroyImageInfo(image_info);

#if 0
    if (exception.severity != UndefinedException) {

        if ( (Image *)Field(image_bloc,1) != (Image *) NULL) {
            DestroyImage((Image *) Field(image_bloc,1));  /* TODO: test me */
        }

        caml_failwith( exception.reason );
    }
#endif

    DestroyExceptionInfo(exc_info);

    if ((Image *) Field(image_bloc,1) == (Image *) NULL) {
        /* exit(1) ; */
        caml_failwith("get_canvas failed");
    }

    CAMLreturn (image_bloc);
}
/* }}} */
/* {{{ im_create_image() */
CAMLprim value
im_create_image( value width, value height, value format )
{
    CAMLparam3( width, height, format );

    CAMLlocal1( image_bloc );

    char
        str_buffer[ MaxTextExtent ];

    int
        str_len;

    ExceptionInfo
        exception;

    ExceptionInfo
        *exc_info;

    ImageInfo
        *image_info;

    if (IsMagickInstantiated() == MagickFalse) {
        MagickCoreGenesis(getenv("PWD"), MagickTrue);
    }

    image_info = CloneImageInfo((ImageInfo *) NULL);

    /* Give image size */
    str_len = snprintf( str_buffer, MaxTextExtent, "%ldx%ld", Long_val(width), Long_val(height) );
    (void) CloneString(&image_info->size, str_buffer);

    /* Give image format */
    str_len = snprintf( str_buffer, MaxTextExtent, "%s", String_val(format) );
    strncpy( image_info->filename, str_buffer, str_len );


    image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    exc_info = AcquireExceptionInfo();

    Field(image_bloc,1) = (value) ReadImage(image_info, exc_info);

    DestroyImageInfo(image_info);

#if 0
    if (exception.severity != UndefinedException) {

        if ( (Image *)Field(image_bloc,1) != (Image *) NULL) {
            DestroyImage((Image *) Field(image_bloc,1));  /* TODO: test me */
        }

        caml_failwith( exception.reason );
    }
#endif

    DestroyExceptionInfo(exc_info);

    if ((Image *) Field(image_bloc,1) == (Image *) NULL) {
        /* exit(1) ; */
        caml_failwith("create_image failed");
    }

    CAMLreturn( image_bloc );
}
/* }}} */

#if 0
/* {{{ imper_constituteimage() 
 *
 * image = ConstituteImage(640, 480, "RGB", CharPixel, pixels, &exception);
 *
 * Image *ConstituteImage(
 *              const unsigned long columns,
 *              const unsigned long rows,
 *              const char *map,
 *              const StorageType storage,
 *              const void *pixels,
 *              ExceptionInfo *exception )
 */

CAMLprim value imper_constituteimage(value columns, value rows, value map)
{
    CAMLparam3(columns, rows, map);

    CAMLlocal1(image_bloc);

    ExceptionInfo
        exception;

    const void
        *pixels = malloc(sizeof(CharPixel) * Long_val(columns) * Long_val(rows));

    if (IsMagickInstantiated() == MagickFalse) {
        MagickCoreGenesis(getenv("PWD"), MagickTrue);
    }

    image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);
    Field(image_bloc,1) = (value) alloc_image();

    GetExceptionInfo(&exception);

#if DEBUG
    printf("before ConstituteImage call\n"); fflush(stdout);
#endif
    Field(image_bloc,1) = ConstituteImage(Long_val(columns), Long_val(rows),
            String_val(map), CharPixel, pixels,
            &exception );
#if DEBUG
    printf("after ConstituteImage call\n"); fflush(stdout);
#endif

    if (exception.severity != UndefinedException) {

        caml_failwith( exception.reason );
    }

    DestroyExceptionInfo(&exception);

    if ((Image *) Field(image_bloc,1) == (Image *) NULL) {
        exit(1);
    }

    CAMLreturn (image_bloc);
}
/* }}} */
/* {{{ imper_newmagickimage() 
 *
 * Image *NewMagickImage(const ImageInfo *image_info,
 *                       const unsigned long width, const unsigned long height,
 *                       const MagickPixelPacket *background)

typedef struct _MagickPixelPacket
{
  ColorspaceType
    colorspace;

  MagickBooleanType
    matte;

  double
    fuzz;

  unsigned long
    depth;

  MagickRealType
    red,
    green,
    blue,
    alpha,
    index;
} MagickPixelPacket;

 */
CAMLprim value
imper_newmagickimage_native( value width, value height,
            value background_red,
            value background_green,
            value background_blue,
            value background_alpha )
{
    CAMLparam5( width, height, background_red, background_green, background_blue );
    CAMLxparam1( background_alpha );

    CAMLlocal1(image_bloc);

    ImageInfo
        *image_info;

    MagickPixelPacket
        background;
    /*
    void GetMagickPixelPacket(const Image *image, MagickPixelPacket *pixel);
    */
    GetMagickPixelPacket( (Image *) NULL, &background);

    background.colorspace = (ColorspaceType) RGBColorspace;
    background.matte      = (MagickBooleanType) MagickTrue;
    background.fuzz       = (double) 0.2;
    background.depth      = (unsigned long) 16;

    background.red     = (MagickRealType) Int_val(background_red);
    background.green   = (MagickRealType) Int_val(background_green);
    background.blue    = (MagickRealType) Int_val(background_blue);
    background.alpha = (MagickRealType) Int_val(background_alpha);
    background.index   = (MagickRealType) 0;

    image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */
    Field(image_bloc,1) = (value) alloc_image();  /* alloc_image() */

    if (IsMagickInstantiated() == MagickFalse) {
        MagickCoreGenesis(getenv("PWD"), MagickTrue);
    }

    image_info = CloneImageInfo((ImageInfo *) NULL);
    /* GetImageInfo(image_info); */
    /* (void) strcpy(image_info->filename, String_val(input_image_name)); */

    Field(image_bloc,1) = (value) NewMagickImage(image_info,
                                                  Long_val(width), Long_val(height),
                                                  &background );

    DestroyImageInfo(image_info);

    if ((Image *) Field(image_bloc,1) == (Image *) NULL) {
        caml_failwith("newmagickimage failed");
    }

    CAMLreturn (image_bloc);
}

CAMLprim value
imper_newmagickimage_bytecode(value * argv, int argn)
{
      return imper_newmagickimage_native(
                argv[0], argv[1], argv[2],
                argv[3], argv[4], argv[5] );
}
/* }}} */
/* old: */
/* {{{ imper_newmagickimage() 
 *
 * Image *NewMagickImage(const ImageInfo *image_info,
 *                       const unsigned long width, const unsigned long height,
 *                       const MagickPixelPacket *background)

typedef struct _MagickPixelPacket
{
  ColorspaceType
    colorspace;

  MagickBooleanType
    matte;

  double
    fuzz;

  unsigned long
    depth;

  MagickRealType
    red,
    green,
    blue,
    alpha,
    index;
} MagickPixelPacket;

 */
CAMLprim value
imper_newmagickimage_native( value width, value height,
            value background_red,
            value background_green,
            value background_blue,
            value background_alpha )
{
    CAMLparam5( width, height, background_red, background_green, background_blue ) ;
    CAMLxparam1( background_alpha ) ;

    CAMLlocal1(image_bloc) ;
    /*
    value
        image_bloc ;
    */

    ImageInfo
        *image_info ;

    MagickPixelPacket
        *background ;

    MagickPixelPacket
        pixel ;

    PixelGetMagickColor(background, &pixel);
    /*
    background->colorspace = (ColorspaceType) RGBColorspace;

    background->matte   = (MagickBooleanType) MagickTrue;
    background->fuzz    = (double) 0.2;
    background->depth   = (unsigned long) 1;

    background->red     = (MagickRealType) Int_val(background_red);
    background->green   = (MagickRealType) Int_val(background_green);
    background->blue    = (MagickRealType) Int_val(background_blue);
    background->alpha = (MagickRealType) Int_val(background_alpha);
    background->index   = (MagickRealType) 1;
    */

    image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */
    Field(image_bloc,1) = (value) alloc_image();  /* alloc_image() */

    if (IsMagickInstantiated() == MagickFalse) {
        MagickCoreGenesis(getenv("PWD"), MagickTrue);
    }

    image_info = CloneImageInfo((ImageInfo *) NULL);
    /* GetImageInfo(image_info); */
    /* (void) strcpy(image_info->filename, String_val(input_image_name)); */

    Field(image_bloc,1) = (value) NewMagickImage(image_info,
                                                 Long_val(width), Long_val(height),
                                                 &pixel );

    DestroyImageInfo(image_info);

  

    if ((Image *) Field(image_bloc,1) == (Image *) NULL) {
        /* printf("newmagickimage failed\n") ; fflush(stdout) ; */
        caml_failwith("newmagickimage failed");
        /* exit(1) ; */
    }

    CAMLreturn (image_bloc) ;
}

CAMLprim value
imper_newmagickimage_bytecode(value * argv, int argn)
{
      return imper_newmagickimage_native(
                argv[0], argv[1], argv[2],
                argv[3], argv[4], argv[5] ) ;
}
/* }}} */
#endif

/* {{{ im_writeimage()
 *
 * MagickBooleanType WriteImage(const ImageInfo *image_info, Image *image);
 */

CAMLprim value
im_writeimage(value image_bloc, value output_image_name)
{
    CAMLparam2(image_bloc, output_image_name);

    Image
        *image;

    ImageInfo
        *image_info;

    MagickBooleanType
        ret;

    image = (Image *) Field(image_bloc,1);

    (void) strcpy(image->filename, String_val(output_image_name));
    image_info = CloneImageInfo((ImageInfo *) NULL);

    ExceptionInfo *excinfo = AcquireExceptionInfo();
    ret = WriteImage(image_info, image, excinfo);  /* WriteImage() */
    excinfo = DestroyExceptionInfo(excinfo);

    if (ret == MagickFalse) {
        caml_failwith("write_image failed");
    }
    DestroyImageInfo(image_info);

    CAMLreturn( Val_unit );
}
/* }}} */
/* {{{ im_displayimages() 
 *
 * MagickBooleanType DisplayImages(const ImageInfo *image_info, Image *images)
 */

CAMLprim value
im_displayimages(value image_bloc)
{
    CAMLparam1(image_bloc) ;

    Image
        *image ;

    ImageInfo
        *image_info ;

    ExceptionInfo
        excinfo ;

    ExceptionInfo
        *exc_info;

    MagickBooleanType
        ret ;

    image = (Image *) Field(image_bloc,1) ;

    exc_info = AcquireExceptionInfo();

    image_info = CloneImageInfo((ImageInfo *) NULL);

    ret = DisplayImages(image_info, image, exc_info) ;  /* DisplayImages() */

    DestroyImageInfo(image_info);
    DestroyExceptionInfo(exc_info);

    /* @TODO check this exception. */
    if (ret == MagickFalse) {
        /*
         * DisplayImages() displays an image sequence to any X window screen.
         * It returns a value other than 0 if successful.
         * Check the exception member of image to determine the reason for any failure.
         */

        /*
        caml_failwith( image_info.exception ) ;
        caml_failwith( image.exception ) ;
        */

        caml_failwith("display failed") ;
    }

    CAMLreturn (Val_unit) ;
}
/* }}} */
/* {{{ im_cloneimage() 
 *
 * Image *CloneImage(const Image *image, const unsigned long columns,
 *                      const unsigned long rows, const MagickBooleanType orphan,
 *                      ExceptionInfo *exception)
 */
CAMLprim value
im_cloneimage(value image_bloc)
{
    CAMLparam1(image_bloc);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo
        exception;

    ExceptionInfo
        *exc_info;

    exc_info = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    Field(new_image_bloc,1) = (value) CloneImage(
            (Image *) Field(image_bloc,1),
            0, 0, 1,
            exc_info );

#if 0
    if (exception.severity != UndefinedException)
    {
        if ( Field(new_image_bloc,1) )
        {
            DestroyImage( (Image *) Field(new_image_bloc,1) );
        }

        caml_failwith( exception.reason );
    }
#endif

    DestroyExceptionInfo(exc_info);

    CAMLreturn( new_image_bloc );
}

/* }}} */


/* {{{ @TODO: PlasmaImage()        |

PlasmaImage() initializes an image with plasma fractal values.
The image must be initialized with a base color and the random number generator seeded before this method is called.


image: The image.
segment: Define the region to apply plasma fractals values.
attenuate: Define the plasma attenuation factor.
depth: Limit the plasma recursion depth.

}}} */
/* {{{ imper_plasmaimage()
 *
 * MagickBooleanType PlasmaImage(Image *image, const SegmentInfo *segment,
 *             unsigned long attenuate, unsigned long depth )
 */
CAMLprim value
imper_plasmaimage_native(
        value image_bloc,
        value x1, value y1,
        value x2, value y2,
        value attenuate,
        value depth )
{
    CAMLparam5( image_bloc, x1, y1, x2, y2 );
    CAMLxparam2( attenuate, depth );

    MagickBooleanType
        ret;

    SegmentInfo
        segment_info;

    /*
    typedef struct _SegmentInfo
    {
      double
        x1,
        y1,
        x2,
        y2;
    } SegmentInfo;
    */
    segment_info.x1 = (double) Long_val(x1);
    segment_info.y1 = (double) Long_val(y1);
    segment_info.x2 = (double) Long_val(x2);
    segment_info.y2 = (double) Long_val(y2);


    ExceptionInfo *excinfo;

    excinfo = AcquireExceptionInfo();

    ret = PlasmaImage(
            (Image *) Field(image_bloc,1),
            &segment_info,
            (unsigned long) Long_val(attenuate),
            (unsigned long) Long_val(depth), excinfo );

    DestroyExceptionInfo(excinfo);

    if (ret == MagickFalse) {
        caml_failwith("get_plasma_image failed");
    }

    if ((Image *) Field(image_bloc,1) == (Image *) NULL) {
        /* exit(1) ; */
        caml_failwith("get_plasma_image failed");
    }

    CAMLreturn( Val_unit );
}

CAMLprim value
imper_plasmaimage_bytecode(value * argv, int argn)
{
      return imper_plasmaimage_native(
                argv[0], argv[1], argv[2], argv[3],
                argv[4], argv[5], argv[6] );
}
/* }}} */

/*
\define CONVALparam1(p)  CAMLparam1(p)
*/
#define CONVALparam1(p)  /*CAMLparam1(p)*/

/* {{{ CompositeOperator_val() */

static int
CompositeOperator_val( value param )
{
    CONVALparam1 (param);

#if TYPE_CHECKING
    assert (Is_long (param));
#endif

    switch (Int_val (param))
      {
        /* {{{ cases */
        case  0: return UndefinedCompositeOp;
        case  1: return NoCompositeOp;
        case  2: return AlphaCompositeOp;
        case  3: return AtopCompositeOp;
        case  4: return BlendCompositeOp;
        case  5: return BlurCompositeOp;
        case  6: return BumpmapCompositeOp;
        case  7: return ChangeMaskCompositeOp;
        case  8: return ClearCompositeOp;
        case  9: return ColorBurnCompositeOp;
        case 10: return ColorDodgeCompositeOp;
        case 11: return ColorizeCompositeOp;
        case 12: return CopyBlackCompositeOp;
        case 13: return CopyBlueCompositeOp;
        case 14: return CopyCompositeOp;
        case 15: return CopyCyanCompositeOp;
        case 16: return CopyGreenCompositeOp;
        case 17: return CopyMagentaCompositeOp;
        case 18: return CopyAlphaCompositeOp;
        case 19: return CopyRedCompositeOp;
        case 20: return CopyYellowCompositeOp;
        case 21: return DarkenCompositeOp;
        case 22: return DarkenIntensityCompositeOp;
        case 23: return DifferenceCompositeOp;
        case 24: return DisplaceCompositeOp;
        case 25: return DissolveCompositeOp;
        case 26: return DistortCompositeOp;
        case 27: return DivideDstCompositeOp;
        case 28: return DivideSrcCompositeOp;
        case 29: return DstAtopCompositeOp;
        case 30: return DstCompositeOp;
        case 31: return DstInCompositeOp;
        case 32: return DstOutCompositeOp;
        case 33: return DstOverCompositeOp;
        case 34: return ExclusionCompositeOp;
        case 35: return HardLightCompositeOp;
        case 36: return HardMixCompositeOp;
        case 37: return HueCompositeOp;
        case 38: return InCompositeOp;
        case 39: return IntensityCompositeOp;
        case 40: return LightenCompositeOp;
        case 41: return LightenIntensityCompositeOp;
        case 42: return LinearBurnCompositeOp;
        case 43: return LinearDodgeCompositeOp;
        case 44: return LinearLightCompositeOp;
        case 45: return LuminizeCompositeOp;
        case 46: return MathematicsCompositeOp;
        case 47: return MinusDstCompositeOp;
        case 48: return MinusSrcCompositeOp;
        case 49: return ModulateCompositeOp;
        case 50: return ModulusAddCompositeOp;
        case 51: return ModulusSubtractCompositeOp;
        case 52: return MultiplyCompositeOp;
        case 53: return OutCompositeOp;
        case 54: return OverCompositeOp;
        case 55: return OverlayCompositeOp;
        case 56: return PegtopLightCompositeOp;
        case 57: return PinLightCompositeOp;
        case 58: return PlusCompositeOp;
        case 59: return ReplaceCompositeOp;
        case 60: return SaturateCompositeOp;
        case 61: return ScreenCompositeOp;
        case 62: return SoftLightCompositeOp;
        case 63: return SrcAtopCompositeOp;
        case 64: return SrcCompositeOp;
        case 65: return SrcInCompositeOp;
        case 66: return SrcOutCompositeOp;
        case 67: return SrcOverCompositeOp;
        case 68: return ThresholdCompositeOp;
        case 69: return VividLightCompositeOp;
        case 70: return XorCompositeOp;
        case 71: return StereoCompositeOp;
        /* }}} */
        default:
#if DEBUG
            fprintf(stderr, "CompositeOperator_val() failed\n"); fflush(stderr);
#endif
            abort();
      }
}

/* }}} */
/* {{{ imper_compositeimage() 
 *
 * MagickBooleanType CompositeImage(Image *image, const Image *composite_image,
 *                         const CompositeOperator,
 *                         const MagickBooleanType clip,
 *                         const ssize_t x_offset, const ssize_t y_offset,
 *                         ExceptionInfo *)
 */
CAMLprim value imper_compositeimage_native(
        value image_bloc,
        value composite_image_bloc,
        value ml_clip,
        value x_offset,
        value y_offset,
        value composite_operator )
{
    CAMLparam5(image_bloc, composite_image_bloc, x_offset, y_offset, composite_operator) ;

    MagickBooleanType
        ret ;

    MagickBooleanType clip;
    clip = MagickBoolean_val( ml_clip );

    ExceptionInfo *excinfo;

    excinfo = AcquireExceptionInfo();

    ret = CompositeImage(
                (Image *) Field(image_bloc,1),
                (Image *) Field(composite_image_bloc,1),
                CompositeOperator_val(composite_operator),
                clip,
                Long_val(x_offset),
                Long_val(y_offset),
                excinfo ) ;

    DestroyExceptionInfo(excinfo);

    /* @TODO check this exception. */
    if (ret == MagickFalse) {
        caml_failwith("composite_image failed");
    }

    CAMLreturn( Val_unit );
}

CAMLprim value
imper_compositeimage_bytecode(value * argv, int argn)
{
      return imper_compositeimage_native(
                argv[0], argv[1], argv[2],
                argv[3], argv[4], argv[5] );
}

/* }}} */

/* {{{ @TODO: for ChopImage()        |
 * raise invalid_argument rather than produce a failure
 * if the geometry is out of the dimention of the image.
 */
#if CHECK_VALS
    if () /* invalid_argument(""); */
#endif
/* }}} */

/* {{{ imper_textureimage() 
 *
 * MagickBooleanType TextureImage(Image *image, const Image *texture, ExceptionInfo *exc);
 *
 */
CAMLprim value imper_textureimage(
        value image_bloc,
        value texture_image_bloc )
{
    CAMLparam2(image_bloc, texture_image_bloc);

    MagickBooleanType
        ret;

    ExceptionInfo *excinfo;

    excinfo = AcquireExceptionInfo();

    ret = TextureImage(
                (Image *) Field(image_bloc,1),
                (Image *) Field(texture_image_bloc,1), excinfo );

    DestroyExceptionInfo(excinfo);

    /* @TODO check this exception. */
    if (ret == MagickFalse) {
        caml_failwith("texture_image failed");
    }

    CAMLreturn( Val_unit );
}

/* }}} */


/* {{{ imper_colorizeimage() 
 *
 * Image *ColorizeImage(const Image *, const char *, const PixelInfo *,ExceptionInfo *),
 */

CAMLprim value
imper_colorizeimage_native(
            value image_bloc,
            value alpha,
            value target_red,
            value target_green,
            value target_blue,
            value target_alpha )
{
    CAMLparam5( image_bloc, alpha, target_red, target_green, target_blue );
    CAMLxparam1( target_alpha );

    Image
        *new_image;

    ExceptionInfo
        *exception;

    PixelInfo
        target;

    exception = AcquireExceptionInfo();

    target.red     = (Quantum) Long_val(target_red);
    target.green   = (Quantum) Long_val(target_green);
    target.blue    = (Quantum) Long_val(target_blue);
    target.alpha   = (Quantum) Long_val(target_alpha);

    /* QueryColorDatabase( color, target, &handle->exception ); */

    new_image = ColorizeImage(
                    (Image *) Field(image_bloc,1),
                    String_val(alpha),
                    &target,
                    exception );

    if (exception->severity != UndefinedException)
    {
        if ( new_image )
        {
            DestroyImage( new_image );
        }

        caml_failwith( exception->reason );
    }

    DestroyImage( (Image *) Field(image_bloc,1) );
    Field(image_bloc,1) = (value) new_image;

    DestroyExceptionInfo(exception);

    CAMLreturn( Val_unit );
}

CAMLprim value
imper_colorizeimage_bytecode(value * argv, int argn)
{
      return imper_colorizeimage_native(
                argv[0], argv[1], argv[2],
                argv[3], argv[4], argv[5] );
}

/* }}} */


/* {{{ imper_acquireonepixel() 
 *
 * PixelPacket AcquireOnePixel(const Image image,
 *                   const long x, const long y,
 *                   ExceptionInfo exception)
 */

CAMLprim value
imper_acquireonepixel(
            value image_bloc,
            value x,
            value y )
{
    CAMLparam3( image_bloc, x, y );

    CAMLlocal1( tuple_color );

    ExceptionInfo
        *exception;

    PixelPacket
        pixel;

    exception = AcquireExceptionInfo();

    /* DEPR
    pixel = AcquireOnePixel(
                    (Image *) Field(image_bloc,1),
                    Long_val(x),
                    Long_val(y),
                    &exception );
    */

    GetOneVirtualPixel(
                    (Image *) Field(image_bloc,1),
                    Long_val(x),
                    Long_val(y),
                    &pixel,
                    exception );

    if (exception->severity != UndefinedException)
    {
        caml_failwith( exception->reason );
    }

    DestroyExceptionInfo(exception);

    value pixel_red   = Val_int( (int) pixel.red );
    value pixel_green = Val_int( (int) pixel.green );
    value pixel_blue  = Val_int( (int) pixel.blue );
    value pixel_alpha = Val_int( (int) (MaxMap - pixel.alpha) );

    tuple_color = caml_alloc_tuple(4) ;

    Store_field(tuple_color, 0, pixel_red );
    Store_field(tuple_color, 1, pixel_green );
    Store_field(tuple_color, 2, pixel_blue );
    Store_field(tuple_color, 3, pixel_alpha );

    CAMLreturn( tuple_color );
}

/* }}} */
/* {{{ imper_acquireonepixel_alpha() 
 *
 * PixelPacket AcquireOnePixel(const Image image,
 *                   const long x, const long y,
 *                   ExceptionInfo exception)
 */

CAMLprim value
imper_acquireonepixel_alpha(
            value image_bloc,
            value x,
            value y )
{
    CAMLparam3( image_bloc, x, y );

    CAMLlocal1( tuple_color );

    ExceptionInfo
        *exception;

    PixelPacket
        pixel;

    exception = AcquireExceptionInfo();

    /* DEPR
    pixel = AcquireOnePixel(
                    (Image *) Field(image_bloc,1),
                    Long_val(x),
                    Long_val(y),
                    exception );
    */

    GetOneVirtualPixel(
                    (Image *) Field(image_bloc,1),
                    Long_val(x),
                    Long_val(y),
                    &pixel,
                    exception );

    if (exception->severity != UndefinedException)
    {
        caml_failwith( exception->reason );
    }

    DestroyExceptionInfo(exception);

    value pixel_red     = Val_int( (int) pixel.red );
    value pixel_green   = Val_int( (int) pixel.green );
    value pixel_blue    = Val_int( (int) pixel.blue );
    value pixel_alpha = Val_int( (int) pixel.alpha );

    tuple_color = caml_alloc_tuple(4);

    Store_field(tuple_color, 0, pixel_red );
    Store_field(tuple_color, 1, pixel_green );
    Store_field(tuple_color, 2, pixel_blue );
    Store_field(tuple_color, 3, pixel_alpha );

    CAMLreturn( tuple_color );
}

/* }}} */


/* {{{ @TODO:  
 * Perhaps the _image structures in ping functions should be freed at the end?
 * }}} */
/* {{{ imper_ping_image_infos() 
 *
 * Image *PingImage(const ImageInfo *image_info, ExceptionInfo *exception)
 */

CAMLprim value
imper_ping_image_infos(value input_image_name)
{
    CAMLparam1( input_image_name );
    CAMLlocal2( pong_tuple, mimetype );

    Image *_image;

    ExceptionInfo
        *exception;

    ImageInfo
        *image_info;

    char*
        mime_type;

    if (IsMagickInstantiated() == MagickFalse) {
        MagickCoreGenesis(getenv("PWD"), MagickTrue);
    }

    exception = AcquireExceptionInfo();

    image_info = CloneImageInfo((ImageInfo *) NULL);
    (void) strcpy(image_info->filename, String_val(input_image_name));

    _image = PingImage(image_info, exception);
    DestroyImageInfo(image_info);

    if (exception->severity != UndefinedException) {
        caml_failwith( exception->reason );
    }

    DestroyExceptionInfo(exception);

    if (!_image) {
        caml_failwith("ping_image_infos failed");
    }

    mime_type = MagickToMime(_image->magick);

    value width    = Val_long(_image->columns);
    value height   = Val_long(_image->rows);
    value depth    = Val_long(_image->depth);
    value colors   = Val_long(_image->colors);
    value quality  = Val_long(_image->quality);
          mimetype = caml_copy_string( mime_type );

    /* TODO
     * BUG XXX FIXME
     * Perhaps the _image structure should be freed at this point?
     */

    pong_tuple = caml_alloc_tuple(6);

    Store_field(pong_tuple, 0, width );
    Store_field(pong_tuple, 1, height );
    Store_field(pong_tuple, 2, depth );
    Store_field(pong_tuple, 3, colors );
    Store_field(pong_tuple, 4, quality );
    Store_field(pong_tuple, 5, mimetype );

    CAMLreturn( pong_tuple );
}
/* }}} */
/* {{{ imper_ping_image() 
 *
 * Image *PingImage(const ImageInfo *image_info, ExceptionInfo *exception)
 */

CAMLprim value
imper_ping_image(value input_image_name)
{
    CAMLparam1(input_image_name);

    Image *_image;

    ExceptionInfo
        *exception;

    ImageInfo
        *image_info;

    if (IsMagickInstantiated() == MagickFalse) {
        MagickCoreGenesis(getenv("PWD"), MagickTrue);
    }

    exception = AcquireExceptionInfo();

    image_info = CloneImageInfo((ImageInfo *) NULL);
    (void) strcpy(image_info->filename, String_val(input_image_name));

    _image = PingImage(image_info, exception);
    DestroyImageInfo(image_info);

    if (exception->severity != UndefinedException) {

        CAMLreturn( Val_false );
    }

    DestroyExceptionInfo(exception);

    if (!_image) {
        CAMLreturn( Val_false );
    }

    /* TODO
     * BUG XXX FIXME
     * Perhaps the _image structure should be freed at this point?
     */

    CAMLreturn( Val_true );
}
/* }}} */


/* {{{ @NOTICE:  
   the getnumbercolors and getimagehistogram have been swapped
   between the libMagick and the OCaml-binding, because
   getnumbercolors returns an image histogram, and
   getimagehistogram only returns the number of colors. }}} */
/* {{{ imper_getnumbercolors() 
 *
 * unsigned long GetNumberColors(const Image *image, FILE *file, ExceptionInfo *exception)
 */
CAMLprim value
imper_getnumbercolors(value image_bloc, value hist_file)
{
    CAMLparam2(image_bloc, hist_file);

    FILE* fp;

    unsigned long
        unique_colors;    /* the number of unique colors */

    ExceptionInfo *exception;

    fp = fopen( String_val(hist_file), "w" );
    if ( !fp ) {
        caml_failwith("could not write to histogram file");
    }

    exception = AcquireExceptionInfo();

    unique_colors = GetNumberColors(
                        (Image *) Field(image_bloc,1),
                        fp,
                        exception );
    fclose( fp );

    if (exception->severity != UndefinedException)
    {
        caml_failwith( exception->reason );
    }

    DestroyExceptionInfo(exception);

    CAMLreturn( Val_long(unique_colors) );
}
/* }}} */
/* {{{ imper_getimagehistogram() 
 *
 * PixelInfo *GetImageHistogram(const Image *, size_t *, ExceptionInfo *);
 */
CAMLprim value
imper_getimagehistogram(value image_bloc)
{
    CAMLparam1(image_bloc);

    PixelInfo * pixel_info;  /* TODO */

    size_t number_colors;    /* the number of unique colors */

    ExceptionInfo *exception;

    exception = AcquireExceptionInfo();

    pixel_info = GetImageHistogram(
                        (Image *) Field(image_bloc,1),
                        &number_colors,
                        exception );

    if (exception->severity != UndefinedException)
    {
        caml_failwith( exception->reason );
    }

    DestroyExceptionInfo(exception);

    CAMLreturn( Val_long(number_colors) );
}
/* }}} */


/* {{{ imper_getmaxcolormap() 
 *
 * magick-type.h
 * #define MaxMap  N
 */
CAMLprim value
imper_getmaxcolormap( value unit )
{
    CAMLparam1(unit);

    CAMLreturn( Val_long( MaxMap ));
}
/* }}} */


/* {{{ ImageType_val() */

static int
ImageType_val( value param )
{
    CONVALparam1 (param);

#if TYPE_CHECKING
    assert(Is_long(param));
#endif

    switch (Int_val(param))
      {
        case 0:  return UndefinedType;
        case 1:  return BilevelType;
        case 2:  return GrayscaleType;
        case 3:  return GrayscaleAlphaType;
        case 4:  return PaletteType;
        case 5:  return PaletteAlphaType;
        case 6:  return TrueColorType;
        case 7:  return TrueColorAlphaType;
        case 8:  return ColorSeparationType;
        case 9:  return ColorSeparationAlphaType;
        case 10: return OptimizeType;
        default:
#if DEBUG
            fprintf(stderr, "ImageType_val() failed\n"); fflush(stderr);
#endif
            abort();
      }
}

/* }}} */

/* {{{ Val_ImageType() 
 *
 * ImageType GetImageType(const Image *image, ExceptionInfo *exception)
 */
int
Val_ImageType(ImageType image_type)
{
/*
typedef enum
{
    UndefinedType,
    BilevelType,
    GrayscaleType,
    GrayscaleAlphaType,
    PaletteType,
    PaletteAlphaType,
    TrueColorType,
    TrueColorAlphaType,
    ColorSeparationType,
    ColorSeparationAlphaType,
    OptimizeType
} ImageType;
*/
    switch (image_type)
    {
        case UndefinedType:            return 0;
        case BilevelType:              return 1;
        case GrayscaleType:            return 2;
        case GrayscaleAlphaType:       return 3;
        case PaletteType:              return 4;
        case PaletteAlphaType:         return 5;
        case TrueColorType:            return 6;
        case TrueColorAlphaType:       return 7;
        case ColorSeparationType:      return 8;
        case ColorSeparationAlphaType: return 9;
        case OptimizeType:             return 10;
        default:           return 11;  /* Error */
    }
}

/* }}} */

/* {{{ imper_getimagetype() 
 *
 * ImageType GetImageType(const Image *image, ExceptionInfo *exception)
 */
CAMLprim value
imper_getimagetype(value image_bloc)
{
    CAMLparam1(image_bloc);

    ImageType image_type;
    int image_type_code;

    image_type = GetImageType(
                        (Image *) Field(image_bloc,1) );

    image_type_code = Val_ImageType(image_type);

    if ( image_type_code == 11 ) {
        caml_failwith("get_image_type failed: the ImageType structure of the MagickCore has been upgraded");
    }

    CAMLreturn( Val_int(image_type_code) );
}
/* }}} */
/* {{{ imper_setimagetype() 
 *
 * MagickBooleanType SetImageType(Image *image, const ImageType image_type)
 */

CAMLprim value
imper_setimagetype(value image_bloc, value image_type)
{
    CAMLparam2(image_bloc, image_type);

    MagickBooleanType
        ret;

    ExceptionInfo *excinfo;

    excinfo = AcquireExceptionInfo();

    ret = SetImageType(
                    (Image *) Field(image_bloc,1),
                    ImageType_val(image_type),
                    excinfo ) ;

    DestroyExceptionInfo(excinfo);

    if (ret == MagickFalse) {
        caml_failwith("set_image_type failed");
    }

    CAMLreturn( Val_unit );
}
/* }}} */


/* {{{ _Val_AffineMatrix() 

typedef struct _AffineMatrix
{
  double
      sx,
      rx,
      ry,
      sy,
      tx,
      ty;
} AffineMatrix;

 */
void
_Val_AffineMatrix(
        AffineMatrix *affine_matrix,
        double sx,
        double rx,
        double ry,
        double sy,
        double tx,
        double ty )
{
    affine_matrix->sx = sx;
    affine_matrix->rx = rx;
    affine_matrix->ry = ry;
    affine_matrix->sy = sy;
    affine_matrix->tx = tx;
    affine_matrix->ty = ty;
}

void
Inspect_AffineMatrix( AffineMatrix *affine_matrix )
{
    printf(" AffineMatrix\n"
           " sx:%g\n"
           " rx:%g\n"
           " ry:%g\n"
           " sy:%g\n"
           " tx:%g\n"
           " ty:%g\n",
        affine_matrix->sx,
        affine_matrix->rx,
        affine_matrix->ry,
        affine_matrix->sy,
        affine_matrix->tx,
        affine_matrix->ty );
}
/* }}} */
/* {{{ imper_affinetransformimage() 
 *
 * Image *AffineTransformImage(const Image *image, AffineMatrix *affine, ExceptionInfo *exception)
 */
CAMLprim value
imper_affinetransformimage_native(
            value image_bloc,
            value sx,
            value rx,
            value ry,
            value sy,
            value tx,
            value ty )
{
    CAMLparam5( image_bloc, sx, rx, ry, sy );
    CAMLxparam2( tx, ty );

    ExceptionInfo
        *exception;

    AffineMatrix
        affine_matrix;

    Image
        *new_image;

    exception = AcquireExceptionInfo();


    _Val_AffineMatrix( &affine_matrix,
            Double_val(sx),
            Double_val(rx),
            Double_val(ry),
            Double_val(sy),
            Double_val(tx),
            Double_val(ty) );

    /*
    Inspect_AffineMatrix( &affine_matrix );
    */

    new_image = AffineTransformImage(
                    (Image *) Field(image_bloc,1),
                    &affine_matrix,
                    exception );


    if (exception->severity != UndefinedException)
    {
        if ( new_image )
        {
            DestroyImage( new_image );
        }

        caml_failwith( exception->reason );
    }

    DestroyExceptionInfo(exception);

    DestroyImage( (Image *) Field(image_bloc,1) );
    Field(image_bloc,1) = (value) new_image;

    CAMLreturn( Val_unit );
}


CAMLprim value
imper_affinetransformimage_bytecode(value * argv, int argn)
{
      return imper_affinetransformimage_native(
                argv[0], argv[1], argv[2], argv[3],
                argv[4], argv[5], argv[6] );
}

/* }}} */
/* {{{ fun_affinetransformimage() 
 *
 * Image *AffineTransformImage(const Image *image, AffineMatrix *affine, ExceptionInfo *exception)
 */
CAMLprim value
fun_affinetransformimage_native(
            value image_bloc,
            value sx,
            value rx,
            value ry,
            value sy,
            value tx,
            value ty )
{
    CAMLparam5( image_bloc, sx, rx, ry, sy );
    CAMLxparam2( tx, ty );
    CAMLlocal1(new_image_bloc);

    ExceptionInfo
        *exception;

    AffineMatrix
        affine_matrix;

    exception = AcquireExceptionInfo();


    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    _Val_AffineMatrix( &affine_matrix,
            Double_val(sx),
            Double_val(rx),
            Double_val(ry),
            Double_val(sy),
            Double_val(tx),
            Double_val(ty) );

    /*
    Inspect_AffineMatrix( &affine_matrix );
    */

    Field(new_image_bloc,1) =
        (value) AffineTransformImage(
                    (Image *) Field(image_bloc,1),
                    &affine_matrix,
                    exception );


    if (exception->severity != UndefinedException)
    {
        if ( Field(new_image_bloc,1) )
        {
            DestroyImage( (Image *) Field(new_image_bloc,1) );
        }

        caml_failwith( exception->reason );
    }

    DestroyExceptionInfo(exception);

    CAMLreturn( new_image_bloc );
}


CAMLprim value
fun_affinetransformimage_bytecode(value * argv, int argn)
{
      return fun_affinetransformimage_native(
                argv[0], argv[1], argv[2], argv[3],
                argv[4], argv[5], argv[6] );
}

/* }}} */


/* {{{ ====  GET INFOS  ==== */

/* {{{ imper_getimagewidth() 
 *
 * image->columns
 */
CAMLprim value
imper_getimagewidth( value image_bloc )
{
    CAMLparam1(image_bloc);

    CAMLreturn( Val_long(
                    ((Image *) Field(image_bloc,1))->columns
                ) );
}

/* }}} */
/* {{{ imper_getimageheight() 
 *
 * image->rows
 */
CAMLprim value
imper_getimageheight( value image_bloc )
{
    CAMLparam1(image_bloc);

    CAMLreturn( Val_long(
                    ((Image *) Field(image_bloc,1))->rows
                ) );
}

/* }}} */
/* {{{ imper_getimagedepth() 
 *
 * image->depth
 */
CAMLprim value
imper_getimagedepth( value image_bloc )
{
    CAMLparam1(image_bloc);

    CAMLreturn( Val_long(
                    ((Image *) Field(image_bloc,1))->depth
                ) );
}

/* }}} */
/* {{{ imper_getimagecolors() 
 *
 * image->colors
 */
CAMLprim value
imper_getimagecolors( value image_bloc )
{
    CAMLparam1(image_bloc);

    CAMLreturn( Val_long(
                    ((Image *) Field(image_bloc,1))->colors
                ) );
}

/* }}} */
/* {{{ imper_getimagecolorspace() 
 *
 * image->colorspace
 */
CAMLprim value
imper_getimagecolorspace( value image_bloc )
{
    CAMLparam1(image_bloc);

    CAMLreturn( Val_long(
                    ((Image *) Field(image_bloc,1))->colorspace
                ) );
}

/* }}} */
/* {{{ imper_getimagequality() 
 *
 * image->quality
 */
CAMLprim value
imper_getimagequality( value image_bloc )
{
    CAMLparam1(image_bloc);

    CAMLreturn( Val_long(
                    ((Image *) Field(image_bloc,1))->quality
                ) );
}

/* }}} */

/* {{{ imper_setimagecolors() 
 *
 * image->colors
 */
CAMLprim value
imper_setimagecolors( value image_bloc, value colors )
{
    CAMLparam2(image_bloc, colors);

    /* @TODO test this function */

    ((Image *) Field(image_bloc,1))->colors = Long_val(colors);

    CAMLreturn( Val_unit );
}

/* }}} */
/* {{{ imper_setcompressionquality() 
 *
 * image->quality
 */
CAMLprim value
imper_setcompressionquality( value image_bloc, value compression_quality )
{
    CAMLparam2(image_bloc, compression_quality);

    /* @TODO check this function */

    ((Image *) Field(image_bloc,1))->quality = Long_val(compression_quality);

    CAMLreturn( Val_unit );
}

/* }}} */

/* {{{ imper_getimagemimetype() 
 *
 */
CAMLprim value
imper_getimagemimetype( value image_bloc )
{
    CAMLparam1(image_bloc);

    char*
        mime_type;

    mime_type = MagickToMime(
                        ((Image *) Field(image_bloc,1))->magick
                    );

    CAMLreturn( caml_copy_string( mime_type ) );
}

/* }}} */
/* {{{ imper_getimagesize() 
 *
 * image->columns
 * image->rows
 */
CAMLprim value
imper_getimagesize( value image_bloc )
{
    CAMLparam1(image_bloc);

    unsigned long
        width, height;

    char*
        size;

    int ret;

    if ( (size = malloc(256)) == NULL ) {
        caml_failwith("get_image_size failed") ;
    }

    width  = ((Image *) Field(image_bloc,1))->columns;
    height = ((Image *) Field(image_bloc,1))->rows;

    ret = snprintf(size, 256, "width='%lu' height='%lu'", width, height);

    CAMLreturn( caml_copy_string( size ) );
}

/* }}} */

/* }}} */

/* {{{ ====  TESTS  ==== */

/* {{{ imper_ispaletteimage() 
 *
 * MagickBooleanType IsPaletteImage(const Image *image, ExceptionInfo *exception)
 */
CAMLprim value
imper_ispaletteimage(value image_bloc)
{
    CAMLparam1(image_bloc);

    MagickBooleanType
        ret;

    ret = IsPaletteImage( (Image *) Field(image_bloc,1) );

    if ( ret == MagickTrue )
    {
        CAMLreturn( Val_true );
    } else {
        CAMLreturn( Val_false );
    }
}
/* }}} */
/* {{{ imper_istaintimage() 
 *
 * MagickBooleanType IsTaintImage(const Image *image)
 */
CAMLprim value
imper_istaintimage(value image_bloc)
{
    CAMLparam1(image_bloc);

    MagickBooleanType
        ret;

    ret = IsTaintImage( (Image *) Field(image_bloc,1) );

    if ( ret == MagickTrue )
    {
        CAMLreturn( Val_true );
    } else {
        CAMLreturn( Val_false );
    }
}
/* }}} */
/* {{{ imper_isimagesequal() 
 *
 * MagickBooleanType IsImagesEqual(Image *image, const Image *reconstruct_image)
 */
CAMLprim value
imper_isimagesequal(value image_bloc, value comp_image_bloc)
{
    CAMLparam2( image_bloc, comp_image_bloc );
    CAMLlocal4(
            tuple_errors,
            mean_error_per_pixel,
            normalized_mean_error,
            normalized_maximum_error );

    ExceptionInfo
        *excinfo;

    MagickBooleanType
        ret;

    excinfo = AcquireExceptionInfo();

    ret = IsImagesEqual(
            (Image *) Field(image_bloc,1),
            (Image *) Field(comp_image_bloc,1), excinfo);

    DestroyExceptionInfo(excinfo);

    tuple_errors = caml_alloc_tuple(4);

    if ( ret == MagickTrue ) {
        Store_field(tuple_errors, 0, Val_true );
    } else {
        Store_field(tuple_errors, 0, Val_false );
    }

    Image *image;
    image = (Image *) Field(image_bloc,1);

    /* OLD
    value mean_error_per_pixel     = caml_copy_double((double)image->error.mean_error_per_pixel);
    value normalized_mean_error    = caml_copy_double((double)image->error.normalized_mean_error);
    value normalized_maximum_error = caml_copy_double((double)image->error.normalized_maximum_error);
    */

    /*
    mean_error_per_pixel     = caml_copy_double((double)image->error.mean_error_per_pixel);
    normalized_mean_error    = caml_copy_double((double)image->error.normalized_mean_error);
    normalized_maximum_error = caml_copy_double((double)image->error.normalized_maximum_error);

    Store_field(tuple_errors, 1, mean_error_per_pixel );
    Store_field(tuple_errors, 2, normalized_mean_error );
    Store_field(tuple_errors, 3, normalized_maximum_error );
    */

    Store_field(tuple_errors, 1, caml_copy_double( image->error.mean_error_per_pixel ) );
    Store_field(tuple_errors, 2, caml_copy_double( image->error.normalized_mean_error ) );
    Store_field(tuple_errors, 3, caml_copy_double( image->error.normalized_maximum_error ) );

    CAMLreturn( tuple_errors );
}
/* }}} */

/* }}} */

/* {{{ ====  ABOUT IM  ==== */

/* {{{ imper_getmagickcopyright() 
 *
 * const char *GetMagickCopyright(void)
 */
CAMLprim value
imper_getmagickcopyright( value unit )
{
    CAMLparam1(unit);
    const char* copyright;

    copyright = GetMagickCopyright();

    CAMLreturn(caml_copy_string( copyright ));
}
/* }}} */
/* {{{ imper_getmagickhomeurl() 
 *
 * char *GetMagickHomeURL(void)
 */
CAMLprim value
imper_getmagickhomeurl( value unit )
{
    CAMLparam1(unit);

    CAMLreturn(caml_copy_string(
                GetMagickHomeURL()
                ));
}
/* }}} */
/* {{{ imper_getmagickquantumdepth() 
 *
 * const char *GetMagickQuantumDepth(unsigned long *depth)
 */
CAMLprim value
imper_getmagickquantumdepth( value unit )
{
    CAMLparam1(unit);
    CAMLlocal2( tuple_quantum_depth, str_quantum_depth );  /* bug-fixed. found in V0.19 by F.Le Fessant */

    const char* quantum_depth;
    unsigned long *depth;

    depth = (unsigned long *)NULL;

    quantum_depth = GetMagickQuantumDepth(depth);

    value int_quantum_depth = Val_int( (int) depth );
          str_quantum_depth = caml_copy_string( quantum_depth );

    tuple_quantum_depth = caml_alloc_tuple(2);

    Store_field(tuple_quantum_depth, 0, int_quantum_depth);
    Store_field(tuple_quantum_depth, 1, str_quantum_depth);

    CAMLreturn( tuple_quantum_depth );
}
/* }}} */
/* {{{ imper_getmagickquantumrange() 
 *
 * const char *GetMagickQuantumRange(unsigned long *range)
 */
CAMLprim value
imper_getmagickquantumrange( value unit )
{
    CAMLparam1(unit);
    CAMLlocal1( tuple_quantum_range );

    const char* quantum_range;
    unsigned long *range;

    range = (unsigned long *)NULL;

    quantum_range = GetMagickQuantumRange(range);

    value int_quantum_range = Val_int( (int) range );
    value str_quantum_range = caml_copy_string( quantum_range );

    tuple_quantum_range = caml_alloc_tuple(2);

    Store_field(tuple_quantum_range, 0, int_quantum_range);
    Store_field(tuple_quantum_range, 1, str_quantum_range);

    CAMLreturn( tuple_quantum_range );
}
/* }}} */
/* {{{ imper_getmagickreleasedate() 
 *
 * const char *GetMagickReleaseDate(void)
 */
CAMLprim value
imper_getmagickreleasedate( value unit )
{
    CAMLparam1(unit);

    CAMLreturn(caml_copy_string(
                GetMagickReleaseDate()
                ));
}
/* }}} */
/* {{{ imper_getmagickversion() 
 *
 * const char *GetMagickVersion(unsigned long *version)
 */
CAMLprim value
imper_getmagickversion( value unit )
{
    CAMLparam1(unit);
    CAMLlocal3( tuple_magick_version, int_version, str_version );

    const char* char_version;
    unsigned long version;

    char_version = GetMagickVersion(&version);

    int_version = Val_int( version );
    str_version = caml_copy_string( char_version );

    tuple_magick_version = caml_alloc_tuple(2);

    Store_field(tuple_magick_version, 0, int_version);
    Store_field(tuple_magick_version, 1, str_version);

    CAMLreturn( tuple_magick_version );
}
/* }}} */
/* {{{ imper_getbindingversion() 
 *
 * #define OCAML_IMAGEMAGICK_VERSION "X"
 */
CAMLprim value
imper_getbindingversion( value unit )
{
    CAMLparam1(unit);

    CAMLreturn(caml_copy_string(
                OCAML_IMAGEMAGICK_VERSION
                ));
}
/* }}} */

/* TODO: find why getmagickname  does not work */
#if 0
/* {{{ imper_getmagickname() 
 *
 * const char *GetMagickName(void)
 */
CAMLprim value
imper_getmagickname( value unit )
{
    CAMLparam1(unit);

    CAMLreturn(caml_copy_string(
                GetMagickName()
                ));
}
/* }}} */
#endif

/* }}} */

/* {{{ ====  DRAWINGS  ==== */

#define MAKE_DESTROY_DRAWINFO 1

/* TODO: test the affine_matrix parameter */

/* {{{ LineCap_val() */

static int
LineCap_val( value param )
{
    CONVALparam1 (param);

#if TYPE_CHECKING
    assert (Is_long (param));
#endif

    switch (Int_val (param))
      {
        case 0: return UndefinedCap;
        case 1: return ButtCap;
        case 2: return RoundCap;
        case 3: return SquareCap;
        default:
#if DEBUG
            fprintf(stderr, "LineCap_val() failed\n"); fflush(stderr);
#endif
            abort();
      }
}

/* }}} */
/* {{{ LineJoin_val() */

static int
LineJoin_val( value param )
{
    CONVALparam1 (param);

#if TYPE_CHECKING
    assert (Is_long (param));
#endif

    switch (Int_val (param))
      {
        case 0: return UndefinedJoin;
        case 1: return MiterJoin;
        case 2: return RoundJoin;
        case 3: return BevelJoin;
        default:
#if DEBUG
            fprintf(stderr, "LineJoin_val() failed\n"); fflush(stderr);
#endif
            abort();
      }
}

/* }}} */
/* {{{ fill_AffineMatrix() */

void
fill_AffineMatrix(
        AffineMatrix *affine,
        double sx,
        double rx,
        double ry,
        double sy,
        double tx,
        double ty )
{
/*  typedef struct _AffineMatrix
    {
      double
        sx, rx, ry, sy, tx, ty;

    } AffineMatrix;  */

    affine->sx = sx;
    affine->rx = rx;
    affine->ry = ry;
    affine->sy = sy;
    affine->tx = tx;
    affine->ty = ty;
}
/* }}} */

    /* {{{ DrawInfo struct 

    typedef struct _DrawInfo
    {
      char
        *primitive,
        *geometry;

      RectangleInfo
        viewbox;

      AffineMatrix
        affine;

      GravityType
        gravity;

      PixelPacket
        fill,
        stroke;

      double
        stroke_width;

      GradientInfo
        gradient;

      Image
        *fill_pattern,
        *tile,
        *stroke_pattern;

      MagickBooleanType
        stroke_antialias,
        text_antialias;

      FillRule
        fill_rule;

      LineCap
        linecap;

      LineJoin
        linejoin;

      unsigned long
        miterlimit;

      double
        dash_offset;

      DecorationType
        decorate;

      CompositeOperator
        compose;

      char
        *text;

      unsigned long
        face;

      char
        *font,
        *metrics,
        *family;

      StyleType
        style;

      StretchType
        stretch;

      unsigned long
        weight;

      char
        *encoding;

      double
        pointsize;

      char
        *density;

      AlignType
        align;

      PixelPacket
        undercolor,
        border_color;

      char
        *server_name;

      double
        *dash_pattern;

      char
        *clip_path;

      SegmentInfo
        bounds;

      ClipPathUnits
        clip_units;

      Quantum
        alpha;

      MagickBooleanType
        render;

      ElementReference
        element_reference;

      MagickBooleanType
        debug;

      unsigned long
        signature;

    } DrawInfo;

    \* }}} ======== */

/* {{{ imper_draw_point() 
 *
 * (DrawInfo *)->primitive = "point x,y"
 */

CAMLprim value
imper_draw_point_native(
        value image_bloc,
        value x, value y,
        value red,
        value green,
        value blue,
        value alpha )
{
    CAMLparam5( image_bloc, x, y, red, green );
    CAMLxparam2( blue, alpha );

    MagickBooleanType
        ret;

    ImageInfo
        *image_info;

    DrawInfo
        *draw_info;


    image_info = CloneImageInfo((ImageInfo *) NULL);

    draw_info = CloneDrawInfo( image_info, ( DrawInfo* )NULL );
    DestroyImageInfo(image_info);

    if ( !draw_info ) {
#if DEBUG
        fprintf(stderr, "CloneDrawInfo() failed\n"); fflush(stderr);
#endif
        caml_failwith("draw_point failed");
    }

    PixelInfo
        fill;

    fill.red     = (Quantum) Long_val(red);
    fill.green   = (Quantum) Long_val(green);
    fill.blue    = (Quantum) Long_val(blue);
    fill.alpha = (Quantum) Long_val(alpha);

    draw_info->fill = fill;


    char str_buffer[ MaxTextExtent ];
    int str_len;

    /* Feed the primitive "point X,Y" */
    str_len = snprintf( str_buffer, MaxTextExtent, "point %ld,%ld", Long_val(x), Long_val(y) );
    (void) CloneString(&draw_info->primitive, str_buffer);

    ExceptionInfo *excinfo = AcquireExceptionInfo();

    ret = DrawImage((Image *) Field(image_bloc,1), draw_info, excinfo);

    excinfo = DestroyExceptionInfo(excinfo);

    if (ret == MagickFalse) {
#if DEBUG
        fprintf(stderr, "DrawImage() failed\n"); fflush(stderr);
#endif
        caml_failwith("draw_point failed");
    }


    /* @FIXME: draw_info should be freed
     * but sometimes it produces a Segmentation fault
     */
#if MAKE_DESTROY_DRAWINFO
    DestroyDrawInfo(draw_info);
#endif


    CAMLreturn( Val_unit );
}

CAMLprim value
imper_draw_point_bytecode(value * argv, int argn)
{
      return imper_draw_point_native(
                argv[0], argv[1], argv[2],
                argv[3], argv[4], argv[5], argv[6] );
}
/* }}} */
/* {{{ imper_draw_line() 
 *
 * (DrawInfo *)->primitive = "line  x0,y0 x1,y1"
 */

CAMLprim value
imper_draw_line_native(
        value image_bloc,
        value x0, value y0,
        value x1, value y1,

        value fill_red,
        value fill_green,
        value fill_blue,
        value fill_alpha,

        value stroke_red,
        value stroke_green,
        value stroke_blue,
        value stroke_alpha,

        value stroke_antialias,

        value width,
        value line_cap )
{
    CAMLparam5( image_bloc, x0, y0, x1, y1 );
    CAMLxparam5( fill_red, fill_green, fill_blue, fill_alpha, stroke_red );
    CAMLxparam5( stroke_green, stroke_blue, stroke_alpha, stroke_antialias, width);
    CAMLxparam1( line_cap );

    MagickBooleanType
        ret;

    ImageInfo
        *image_info;

    DrawInfo
        *draw_info;


    image_info = CloneImageInfo((ImageInfo *) NULL);

    draw_info = CloneDrawInfo( image_info, ( DrawInfo* )NULL );
    DestroyImageInfo(image_info);

    if ( !draw_info ) {
#if DEBUG
        fprintf(stderr, "CloneDrawInfo() failed\n"); fflush(stderr);
#endif
        caml_failwith("draw_line failed");
    }

    PixelInfo
        fill;

    fill.red     = (Quantum) Long_val(fill_red);
    fill.green   = (Quantum) Long_val(fill_green);
    fill.blue    = (Quantum) Long_val(fill_blue);
    fill.alpha = (Quantum) Long_val(fill_alpha);

    draw_info->fill = fill;


    PixelInfo
        stroke;

    stroke.red     = (Quantum) Long_val(stroke_red);
    stroke.green   = (Quantum) Long_val(stroke_green);
    stroke.blue    = (Quantum) Long_val(stroke_blue);
    stroke.alpha = (Quantum) Long_val(stroke_alpha);

    /*
       typedef struct _DrawInfo
       {
         PixelPacket fill, stroke;
         double stroke_width;
         CompositeOperator compose;
         LineCap linecap;
         LineJoin linejoin;
         ...
       } DrawInfo;
    */
    draw_info->stroke = stroke;

    draw_info->stroke_width = Double_val(width);
    draw_info->stroke_antialias = MagickBoolean_val(stroke_antialias);

    draw_info->linecap = LineCap_val(line_cap);


    char str_buffer[ MaxTextExtent ];
    int str_len;

    /*
     * Feed the primitive "line  x0,y0 x1,y1"
     */
    str_len = snprintf( str_buffer, MaxTextExtent, "line %ld,%ld %ld,%ld",
            Long_val(x0), Long_val(y0), Long_val(x1), Long_val(y1) );

    (void) CloneString(&draw_info->primitive, str_buffer);

    ExceptionInfo *excinfo = AcquireExceptionInfo();
    ret = DrawImage((Image *) Field(image_bloc,1), draw_info, excinfo);
    excinfo = DestroyExceptionInfo(excinfo);

    if (ret == MagickFalse) {
#if DEBUG
        fprintf(stderr, "DrawImage() failed\n"); fflush(stderr);
#endif
        caml_failwith("draw_line failed");
    }


    /* @FIXME: draw_info should be freed
     * but sometimes it produces a Segmentation fault
     */
#if MAKE_DESTROY_DRAWINFO
    DestroyDrawInfo(draw_info);
#endif


    CAMLreturn( Val_unit );
}

CAMLprim value
imper_draw_line_bytecode(value * argv, int argn)
{
      return imper_draw_line_native(
                argv[0], argv[1], argv[2],  argv[3],  argv[4],  argv[5],  argv[6],  argv[7],
                argv[8], argv[9], argv[10], argv[11], argv[12], argv[13], argv[14], argv[15] );
}
/* }}} */
/* {{{ imper_draw_rectangle() 
 *
 * (DrawInfo *)->primitive = "rectangle  x0,y0 x1,y1"
 */

CAMLprim value
imper_draw_rectangle_native(
        value image_bloc,
        value x0, value y0,
        value x1, value y1,

        value fill_red,
        value fill_green,
        value fill_blue,
        value fill_alpha,

        value stroke_red,
        value stroke_green,
        value stroke_blue,
        value stroke_alpha,

        value stroke_antialias,
        value stroke_width,
        value line_join,

        value sx,
        value rx,
        value ry,
        value sy,
        value tx,
        value ty )
{
    CAMLparam5( image_bloc, x0, y0, x1, y1 );
    CAMLxparam5( fill_red, fill_green, fill_blue, fill_alpha, stroke_red );
    CAMLxparam5( stroke_green, stroke_blue, stroke_alpha, stroke_antialias, stroke_width );
    CAMLxparam5( line_join, sx, rx, ry, sy );
    CAMLxparam2( tx, ty );

    MagickBooleanType
        ret;

    ImageInfo
        *image_info;

    DrawInfo
        *draw_info;


    image_info = CloneImageInfo((ImageInfo *) NULL);

    draw_info = CloneDrawInfo( image_info, ( DrawInfo* )NULL );
    DestroyImageInfo(image_info);

    if ( !draw_info ) {
#if DEBUG
        fprintf(stderr, "CloneDrawInfo() failed\n"); fflush(stderr);
#endif
        caml_failwith("draw_rectangle failed");
    }

    PixelInfo
        fill;

    fill.red     = (Quantum) Long_val(fill_red);
    fill.green   = (Quantum) Long_val(fill_green);
    fill.blue    = (Quantum) Long_val(fill_blue);
    fill.alpha = (Quantum) Long_val(fill_alpha);

    draw_info->fill = fill;


    PixelInfo
        stroke;

    stroke.red     = (Quantum) Long_val(stroke_red);
    stroke.green   = (Quantum) Long_val(stroke_green);
    stroke.blue    = (Quantum) Long_val(stroke_blue);
    stroke.alpha = (Quantum) Long_val(stroke_alpha);

    /*
       typedef struct _DrawInfo
       {
         PixelPacket fill, stroke;
         double stroke_width;
         CompositeOperator compose;
         LineCap linecap;
         LineJoin linejoin;
         AffineMatrix affine;
         ...
       } DrawInfo;
    */
    draw_info->stroke = stroke;
    draw_info->stroke_width = Double_val(stroke_width);
    draw_info->stroke_antialias = MagickBoolean_val(stroke_antialias);

    draw_info->linejoin = LineJoin_val(line_join);

    /* TODO
    printf("  %d\n", draw_info->compose);
    draw_info->compose = CompositeOperator_val(composite_operator);
    printf("  %d\n", draw_info->compose);
    */

    AffineMatrix affine;
    fill_AffineMatrix( &affine,
            Double_val(sx),
            Double_val(rx),
            Double_val(ry),
            Double_val(sy),
            Double_val(tx),
            Double_val(ty) );
    draw_info->affine = affine;

    char str_buffer[ MaxTextExtent ];
    int str_len;

    /* 
     * Feed the primitive "rectangle x0,y0 x1,y1"
     */
    str_len = snprintf( str_buffer, MaxTextExtent, "rectangle %ld,%ld %ld,%ld",
            Long_val(x0), Long_val(y0), Long_val(x1), Long_val(y1) );

    (void) CloneString(&draw_info->primitive, str_buffer);

    ExceptionInfo *excinfo = AcquireExceptionInfo();
    ret = DrawImage((Image *) Field(image_bloc,1), draw_info, excinfo);
    excinfo = DestroyExceptionInfo(excinfo);

    if (ret == MagickFalse) {
#if DEBUG
        fprintf(stderr, "DrawImage() failed\n"); fflush(stderr);
#endif
        caml_failwith("draw_rectangle failed");
    }


    /* @FIXME: draw_info should be freed
     * but sometimes it produces a Segmentation fault
     */
#if MAKE_DESTROY_DRAWINFO
    DestroyDrawInfo(draw_info);
#endif


    CAMLreturn( Val_unit );
}

CAMLprim value
imper_draw_rectangle_bytecode(value * argv, int argn)
{
      return imper_draw_rectangle_native(
                argv[0],  argv[1],  argv[2],  argv[3],  argv[4],  argv[5],
                argv[6],  argv[7],  argv[8],  argv[9],  argv[10], argv[11],
                argv[12], argv[13], argv[14], argv[15], argv[16], argv[17],
                argv[18], argv[19], argv[20], argv[21] );
}
/* }}} */
/* {{{ imper_draw_roundrectangle() 
 *
 * (DrawInfo *)->primitive = "roundRectangle  x0,y0 x1,y1 wc,hc"
 */

CAMLprim value
imper_draw_roundrectangle_native(
        value image_bloc,
        value x0, value y0,
        value x1, value y1,
        value wc, value hc,

        value fill_red,
        value fill_green,
        value fill_blue,
        value fill_alpha,

        value stroke_red,
        value stroke_green,
        value stroke_blue,
        value stroke_alpha,

        value stroke_antialias,
        value stroke_width,

        value sx,
        value rx,
        value ry,
        value sy,
        value tx,
        value ty )
{
    CAMLparam5( image_bloc, x0, y0, x1, y1 );
    CAMLxparam5( wc, hc, fill_red, fill_green, fill_blue );
    CAMLxparam5( fill_alpha, stroke_red, stroke_green, stroke_blue, stroke_alpha );
    CAMLxparam5( stroke_antialias, stroke_width, sx, rx, ry );
    CAMLxparam3( sy, tx, ty );

    MagickBooleanType
        ret;

    ImageInfo
        *image_info;

    DrawInfo
        *draw_info;


    image_info = CloneImageInfo((ImageInfo *) NULL);

    draw_info = CloneDrawInfo( image_info, ( DrawInfo* )NULL );
    DestroyImageInfo(image_info);

    if ( !draw_info ) {
#if DEBUG
        fprintf(stderr, "CloneDrawInfo() failed\n"); fflush(stderr);
#endif
        caml_failwith("draw_round_rectangle failed");
    }

    PixelInfo
        fill;

    fill.red     = (Quantum) Long_val(fill_red);
    fill.green   = (Quantum) Long_val(fill_green);
    fill.blue    = (Quantum) Long_val(fill_blue);
    fill.alpha = (Quantum) Long_val(fill_alpha);

    draw_info->fill = fill;


    PixelInfo
        stroke;

    stroke.red     = (Quantum) Long_val(stroke_red);
    stroke.green   = (Quantum) Long_val(stroke_green);
    stroke.blue    = (Quantum) Long_val(stroke_blue);
    stroke.alpha = (Quantum) Long_val(stroke_alpha);

    /*
       typedef struct _DrawInfo
       {
         PixelPacket fill, stroke;
         double stroke_width;
         CompositeOperator compose;
         LineCap linecap;
         LineJoin linejoin;
         ...
       } DrawInfo;
    */
    draw_info->stroke = stroke;
    draw_info->stroke_width = Double_val(stroke_width);
    draw_info->stroke_antialias = MagickBoolean_val(stroke_antialias);

    AffineMatrix affine;
    fill_AffineMatrix( &affine,
            Double_val(sx),
            Double_val(rx),
            Double_val(ry),
            Double_val(sy),
            Double_val(tx),
            Double_val(ty) );
    draw_info->affine = affine;


    char str_buffer[ MaxTextExtent ];
    int str_len;

    /* 
     * Feed the primitive  "roundRectangle x0,y0 x1,y1 wc,hc"
     */
    str_len = snprintf( str_buffer, MaxTextExtent, "roundRectangle %ld,%ld %ld,%ld %ld,%ld",
            Long_val(x0), Long_val(y0), Long_val(x1), Long_val(y1), Long_val(wc), Long_val(hc) );

    (void) CloneString(&draw_info->primitive, str_buffer);

    ExceptionInfo *excinfo = AcquireExceptionInfo();
    ret = DrawImage((Image *) Field(image_bloc,1), draw_info, excinfo);
    excinfo = DestroyExceptionInfo(excinfo);

    if (ret == MagickFalse) {
#if DEBUG
        fprintf(stderr, "DrawImage() failed\n"); fflush(stderr);
#endif
        caml_failwith("draw_round_rectangle failed");
    }


    /* @FIXME: draw_info should be freed
     * but sometimes it produces a Segmentation fault
     */
#if MAKE_DESTROY_DRAWINFO
    DestroyDrawInfo(draw_info);
#endif


    CAMLreturn( Val_unit );
}

CAMLprim value
imper_draw_roundrectangle_bytecode(value * argv, int argn)
{
      return imper_draw_roundrectangle_native(
                argv[0],  argv[1],  argv[2],  argv[3],  argv[4],  argv[5],
                argv[6],  argv[7],  argv[8],  argv[9],  argv[10], argv[11],
                argv[12], argv[13], argv[14], argv[15], argv[16], argv[17],
                argv[18], argv[19], argv[20], argv[21], argv[22] );
}
/* }}} */
/* {{{ imper_draw_arc() 
 *
 * (DrawInfo *)->primitive = "arc  x0,y0 x1,y1 a0,a1"
 */

CAMLprim value
imper_draw_arc_native(
        value image_bloc,
        value x0, value y0,
        value x1, value y1,
        value a0, value a1,

        value fill_red,
        value fill_green,
        value fill_blue,
        value fill_alpha,

        value stroke_red,
        value stroke_green,
        value stroke_blue,
        value stroke_alpha,

        value stroke_antialias,
        value stroke_width,
        value line_cap,

        value sx,
        value rx,
        value ry,
        value sy,
        value tx,
        value ty )
{
    CAMLparam5( image_bloc, x0, y0, x1, y1 );
    CAMLxparam5( a0, a1, fill_red, fill_green, fill_blue );
    CAMLxparam5( fill_alpha, stroke_red, stroke_green, stroke_blue, stroke_alpha );
    CAMLxparam5( stroke_antialias, stroke_width, line_cap, sx, rx );
    CAMLxparam4( ry, sy, tx, ty );

    MagickBooleanType
        ret;

    ImageInfo
        *image_info;

    DrawInfo
        *draw_info;


    image_info = CloneImageInfo((ImageInfo *) NULL);

    draw_info = CloneDrawInfo( image_info, ( DrawInfo* )NULL );
    DestroyImageInfo(image_info);

    if ( !draw_info ) {
#if DEBUG
        fprintf(stderr, "CloneDrawInfo() failed\n"); fflush(stderr);
#endif
        caml_failwith("draw_arc failed");
    }

    PixelInfo
        fill;

    fill.red     = (Quantum) Long_val(fill_red);
    fill.green   = (Quantum) Long_val(fill_green);
    fill.blue    = (Quantum) Long_val(fill_blue);
    fill.alpha = (Quantum) Long_val(fill_alpha);

    draw_info->fill = fill;


    PixelInfo
        stroke;

    stroke.red     = (Quantum) Long_val(stroke_red);
    stroke.green   = (Quantum) Long_val(stroke_green);
    stroke.blue    = (Quantum) Long_val(stroke_blue);
    stroke.alpha = (Quantum) Long_val(stroke_alpha);

    /*
       typedef struct _DrawInfo
       {
         PixelPacket fill, stroke;
         double stroke_width;
         CompositeOperator compose;
         LineCap linecap;
         LineJoin linejoin;
         ...
       } DrawInfo;
    */
    draw_info->stroke = stroke;
    draw_info->stroke_width = Double_val(stroke_width);
    draw_info->stroke_antialias = MagickBoolean_val(stroke_antialias);

    draw_info->linecap = LineCap_val(line_cap);


    AffineMatrix affine;
    fill_AffineMatrix( &affine,
            Double_val(sx),
            Double_val(rx),
            Double_val(ry),
            Double_val(sy),
            Double_val(tx),
            Double_val(ty) );
    draw_info->affine = affine;


    char str_buffer[ MaxTextExtent ];
    int str_len;

    /* 
     * Feed the primitive  "arc  x0,y0 x1,y1 a0,a1"
     */
    str_len = snprintf( str_buffer, MaxTextExtent, "arc %ld,%ld %ld,%ld %ld,%ld",
            Long_val(x0), Long_val(y0), Long_val(x1), Long_val(y1), Long_val(a0), Long_val(a1) );

    (void) CloneString(&draw_info->primitive, str_buffer);

    ExceptionInfo *excinfo = AcquireExceptionInfo();
    ret = DrawImage((Image *) Field(image_bloc,1), draw_info, excinfo);
    excinfo = DestroyExceptionInfo(excinfo);

    if (ret == MagickFalse) {
#if DEBUG
        fprintf(stderr, "DrawImage() failed\n"); fflush(stderr);
#endif
        caml_failwith("draw_arc failed");
    }


    /* @FIXME: draw_info should be freed
     * but sometimes it produces a Segmentation fault
     */
#if MAKE_DESTROY_DRAWINFO
    DestroyDrawInfo(draw_info);
#endif


    CAMLreturn( Val_unit );
}

CAMLprim value
imper_draw_arc_bytecode(value * argv, int argn)
{
      return imper_draw_arc_native(
                argv[0],  argv[1],  argv[2],  argv[3],  argv[4],  argv[5],
                argv[6],  argv[7],  argv[8],  argv[9],  argv[10], argv[11],
                argv[12], argv[13], argv[14], argv[15], argv[16], argv[17],
                argv[18], argv[19], argv[20], argv[21], argv[22], argv[23] );
}
/* }}} */
/* {{{ imper_draw_circle() 
 *
 * (DrawInfo *)->primitive = "circle x0,y0 x1,y1"
 */

CAMLprim value
imper_draw_circle_native(
        value image_bloc,
        value x0, value y0,
        value x1, value y1,

        value fill_red,
        value fill_green,
        value fill_blue,
        value fill_alpha,

        value stroke_red,
        value stroke_green,
        value stroke_blue,
        value stroke_alpha,

        value stroke_antialias,
        value stroke_width,

        value sx,
        value rx,
        value ry,
        value sy,
        value tx,
        value ty )
{
    CAMLparam5( image_bloc, x0, y0, x1, y1 );
    CAMLxparam5( fill_red, fill_green, fill_blue, fill_alpha, stroke_red );
    CAMLxparam5( stroke_green, stroke_blue, stroke_alpha, stroke_antialias, stroke_width );
    CAMLxparam5( sx, rx, ry, sy, tx );
    CAMLxparam1( ty );

    MagickBooleanType
        ret;

    ImageInfo
        *image_info;

    DrawInfo
        *draw_info;


    image_info = CloneImageInfo((ImageInfo *) NULL);

    draw_info = CloneDrawInfo( image_info, ( DrawInfo* )NULL );
    DestroyImageInfo(image_info);

    if ( !draw_info ) {
#if DEBUG
        fprintf(stderr, "CloneDrawInfo() failed\n"); fflush(stderr);
#endif
        caml_failwith("draw_circle failed");
    }

    PixelInfo
        fill;

    fill.red     = (Quantum) Long_val(fill_red);
    fill.green   = (Quantum) Long_val(fill_green);
    fill.blue    = (Quantum) Long_val(fill_blue);
    fill.alpha = (Quantum) Long_val(fill_alpha);

    draw_info->fill = fill;


    PixelInfo
        stroke;

    stroke.red     = (Quantum) Long_val(stroke_red);
    stroke.green   = (Quantum) Long_val(stroke_green);
    stroke.blue    = (Quantum) Long_val(stroke_blue);
    stroke.alpha = (Quantum) Long_val(stroke_alpha);

    /*
       typedef struct _DrawInfo
       {
         PixelPacket fill, stroke;
         double stroke_width;
         CompositeOperator compose;
         LineCap linecap;
         LineJoin linejoin;
         ...
       } DrawInfo;
    */
    draw_info->stroke = stroke;
    draw_info->stroke_width = Double_val(stroke_width);
    draw_info->stroke_antialias = MagickBoolean_val(stroke_antialias);


    AffineMatrix affine;
    fill_AffineMatrix( &affine,
            Double_val(sx),
            Double_val(rx),
            Double_val(ry),
            Double_val(sy),
            Double_val(tx),
            Double_val(ty) );
    draw_info->affine = affine;


    char str_buffer[ MaxTextExtent ];
    int str_len;

    /*
     * Feed the primitive "circle x0,y0 x1,y1"
     */
    str_len = snprintf( str_buffer, MaxTextExtent, "circle %ld,%ld %ld,%ld",
            Long_val(x0), Long_val(y0), Long_val(x1), Long_val(y1) );

    (void) CloneString(&draw_info->primitive, str_buffer);

    ExceptionInfo *excinfo = AcquireExceptionInfo();
    ret = DrawImage((Image *) Field(image_bloc,1), draw_info, excinfo);
    excinfo = DestroyExceptionInfo(excinfo);

    if (ret == MagickFalse) {
#if DEBUG
        fprintf(stderr, "DrawImage() failed\n"); fflush(stderr);
#endif
        caml_failwith("draw_circle failed");
    }


    /* @FIXME: draw_info should be freed
     * but sometimes it produces a Segmentation fault
     */
#if MAKE_DESTROY_DRAWINFO
    DestroyDrawInfo(draw_info);
#endif


    CAMLreturn( Val_unit );
}

CAMLprim value
imper_draw_circle_bytecode(value * argv, int argn)
{
      return imper_draw_circle_native(
                argv[0],  argv[1],  argv[2],  argv[3],  argv[4],
                argv[5],  argv[6],  argv[7],  argv[8],  argv[9],
                argv[10], argv[11], argv[12], argv[13], argv[14],
                argv[15], argv[16], argv[17], argv[18], argv[19],
                argv[20] );
}
/* }}} */
/* {{{ imper_draw_ellipse() 
 *
 * (DrawInfo *)->primitive = "ellipse  x0,y0 rx,ry a0,a1"
 */

CAMLprim value
imper_draw_ellipse_native(
        value image_bloc,
        value x0, value y0,
        value x1, value y1,
        value a0, value a1,

        value fill_red,
        value fill_green,
        value fill_blue,
        value fill_alpha,

        value stroke_red,
        value stroke_green,
        value stroke_blue,
        value stroke_alpha,

        value stroke_antialias,
        value stroke_width,

        value sx,
        value rx,
        value ry,
        value sy,
        value tx,
        value ty )
{
    CAMLparam5( image_bloc, x0, y0, x1, y1 );
    CAMLxparam5( a0, a1, fill_red, fill_green, fill_blue );
    CAMLxparam5( fill_alpha, stroke_red, stroke_green, stroke_blue, stroke_alpha );
    CAMLxparam5( stroke_antialias, stroke_width, sx, rx, ry );
    CAMLxparam3( sy, tx, ty );

    MagickBooleanType
        ret;

    ImageInfo
        *image_info;

    DrawInfo
        *draw_info;


    image_info = CloneImageInfo((ImageInfo *) NULL);

    draw_info = CloneDrawInfo( image_info, ( DrawInfo* )NULL );
    DestroyImageInfo(image_info);

    if ( !draw_info ) {
#if DEBUG
        fprintf(stderr, "CloneDrawInfo() failed\n"); fflush(stderr);
#endif
        caml_failwith("draw_ellipse failed");
    }

    PixelInfo
        fill;

    fill.red     = (Quantum) Long_val(fill_red);
    fill.green   = (Quantum) Long_val(fill_green);
    fill.blue    = (Quantum) Long_val(fill_blue);
    fill.alpha = (Quantum) Long_val(fill_alpha);

    draw_info->fill = fill;


    PixelInfo
        stroke;

    stroke.red     = (Quantum) Long_val(stroke_red);
    stroke.green   = (Quantum) Long_val(stroke_green);
    stroke.blue    = (Quantum) Long_val(stroke_blue);
    stroke.alpha = (Quantum) Long_val(stroke_alpha);

    /*
       typedef struct _DrawInfo
       {
         PixelPacket fill, stroke;
         double stroke_width;
         CompositeOperator compose;
         LineCap linecap;
         LineJoin linejoin;
         ...
       } DrawInfo;
    */
    draw_info->stroke = stroke;
    draw_info->stroke_width = Double_val(stroke_width);
    draw_info->stroke_antialias = MagickBoolean_val(stroke_antialias);


    AffineMatrix affine;
    fill_AffineMatrix( &affine,
            Double_val(sx),
            Double_val(rx),
            Double_val(ry),
            Double_val(sy),
            Double_val(tx),
            Double_val(ty) );
    draw_info->affine = affine;


    char str_buffer[ MaxTextExtent ];
    int str_len;

    /* 
     * Feed the primitive  "ellipse  x0,y0 rx,ry a0,a1"
     */
    str_len = snprintf( str_buffer, MaxTextExtent, "ellipse %ld,%ld %ld,%ld %ld,%ld",
            Long_val(x0), Long_val(y0), Long_val(x1), Long_val(y1), Long_val(a0), Long_val(a1) );

    (void) CloneString(&draw_info->primitive, str_buffer);

    ExceptionInfo *excinfo = AcquireExceptionInfo();
    ret = DrawImage((Image *) Field(image_bloc,1), draw_info, excinfo);
    excinfo = DestroyExceptionInfo(excinfo);

    if (ret == MagickFalse) {
#if DEBUG
        fprintf(stderr, "DrawImage() failed\n"); fflush(stderr);
#endif
        caml_failwith("draw_ellipse failed");
    }


    /* @FIXME: draw_info should be freed
     * but sometimes it produces a Segmentation fault
     */
#if MAKE_DESTROY_DRAWINFO
    DestroyDrawInfo(draw_info);
#endif


    CAMLreturn( Val_unit );
}

CAMLprim value
imper_draw_ellipse_bytecode(value * argv, int argn)
{
      return imper_draw_ellipse_native(
                argv[0],  argv[1],  argv[2],  argv[3],  argv[4],  argv[5],
                argv[6],  argv[7],  argv[8],  argv[9],  argv[10], argv[11],
                argv[12], argv[13], argv[14], argv[15], argv[16], argv[17],
                argv[18], argv[19], argv[20], argv[21], argv[22] );
}
/* }}} */
/* {{{ imper_draw_polyline() 
 *
 * (DrawInfo *)->primitive = "polyline x0,y0  ...  xn,yn"
 */

CAMLprim value
imper_draw_polyline_native(
        value image_bloc,
        value array,
        value array_length,

        value fill_red,
        value fill_green,
        value fill_blue,
        value fill_alpha,

        value stroke_red,
        value stroke_green,
        value stroke_blue,
        value stroke_alpha,

        value stroke_antialias,
        value width,
        value line_join,
        value line_cap,

        value sx,
        value rx,
        value ry,
        value sy,
        value tx,
        value ty )
{
    CAMLparam5( image_bloc, array, array_length, fill_red, fill_green );
    CAMLxparam5( fill_blue, fill_alpha, stroke_red, stroke_green, stroke_blue );
    CAMLxparam5( stroke_alpha, stroke_antialias, width, line_join, line_cap );
    CAMLxparam5( sx, rx, ry, sy, tx );
    CAMLxparam1( ty );

    CAMLlocal1( coords );

    MagickBooleanType
        ret;

    ImageInfo
        *image_info;

    DrawInfo
        *draw_info;

    int i;
    int array_len = Int_val(array_length);


    image_info = CloneImageInfo((ImageInfo *) NULL);

    draw_info = CloneDrawInfo( image_info, ( DrawInfo* )NULL );
    DestroyImageInfo(image_info);

    if ( !draw_info ) {
#if DEBUG
        fprintf(stderr, "CloneDrawInfo() failed\n"); fflush(stderr);
#endif
        caml_failwith("draw_polyline failed");
    }

    PixelInfo
        fill;

    fill.red     = (Quantum) Long_val(fill_red);
    fill.green   = (Quantum) Long_val(fill_green);
    fill.blue    = (Quantum) Long_val(fill_blue);
    fill.alpha = (Quantum) Long_val(fill_alpha);

    draw_info->fill = fill;


    PixelInfo
        stroke;

    stroke.red     = (Quantum) Long_val(stroke_red);
    stroke.green   = (Quantum) Long_val(stroke_green);
    stroke.blue    = (Quantum) Long_val(stroke_blue);
    stroke.alpha = (Quantum) Long_val(stroke_alpha);

    /*
       typedef struct _DrawInfo
       {
         PixelPacket fill, stroke;
         double stroke_width;
         CompositeOperator compose;
         LineCap linecap;
         LineJoin linejoin;
         ...
       } DrawInfo;
    */
    draw_info->stroke = stroke;

    draw_info->stroke_width = Double_val(width);
    draw_info->stroke_antialias = MagickBoolean_val(stroke_antialias);

    draw_info->linecap  = LineCap_val(line_cap);
    draw_info->linejoin = LineJoin_val(line_join);


    AffineMatrix affine;
    fill_AffineMatrix( &affine,
            Double_val(sx),
            Double_val(rx),
            Double_val(ry),
            Double_val(sy),
            Double_val(tx),
            Double_val(ty) );
    draw_info->affine = affine;


    char str_buffer[ MaxTextExtent ];
    char str_buffer_tmp[ MaxTextExtent ];
    int str_len;

    /*
     * Feed the primitive "polyline  x0,y0  ...  xn,yn"
     */
    str_len = snprintf( str_buffer, MaxTextExtent, "polyline" );

    for (i=0; i < array_len; i++) {

        coords = Field(array, i);

        strcpy( str_buffer_tmp, str_buffer );

        str_len = snprintf( str_buffer, MaxTextExtent, "%s %ld,%ld",
                    str_buffer_tmp,
                    Long_val(Field(coords,0)),
                    Long_val(Field(coords,1)) );
    }

    (void) CloneString(&draw_info->primitive, str_buffer);

    ExceptionInfo *excinfo = AcquireExceptionInfo();
    ret = DrawImage((Image *) Field(image_bloc,1), draw_info, excinfo);
    excinfo = DestroyExceptionInfo(excinfo);

    if (ret == MagickFalse) {
#if DEBUG
        fprintf(stderr, "DrawImage() failed\n"); fflush(stderr);
#endif
        caml_failwith("draw_polyline failed");
    }


    /* @FIXME: draw_info should be freed
     * but sometimes it produces a Segmentation fault
     */
#if MAKE_DESTROY_DRAWINFO
    DestroyDrawInfo(draw_info);
#endif


    CAMLreturn( Val_unit );
}

CAMLprim value
imper_draw_polyline_bytecode(value * argv, int argn)
{
      return imper_draw_polyline_native(
                argv[0],  argv[1],  argv[2],  argv[3],  argv[4],  argv[5],
                argv[6],  argv[7],  argv[8],  argv[9],  argv[10], argv[11],
                argv[12], argv[13], argv[14], argv[15], argv[16], argv[17],
                argv[18], argv[19], argv[20] );
}
/* }}} */
/* {{{ imper_draw_polygon() 
 *
 * (DrawInfo *)->primitive = "polygon  x0,y0  ...  xn,yn"
 */

CAMLprim value
imper_draw_polygon_native(
        value image_bloc,
        value array,
        value array_length,

        value fill_red,
        value fill_green,
        value fill_blue,
        value fill_alpha,

        value stroke_red,
        value stroke_green,
        value stroke_blue,
        value stroke_alpha,

        value stroke_antialias,
        value width,
        value line_join,

        value sx,
        value rx,
        value ry,
        value sy,
        value tx,
        value ty )
{
    CAMLparam5( image_bloc, array, array_length, fill_red, fill_green );
    CAMLxparam5( fill_blue, fill_alpha, stroke_red, stroke_green, stroke_blue );
    CAMLxparam5( stroke_alpha, stroke_antialias, width, line_join, sx );
    CAMLxparam5( rx, ry, sy, tx, ty );

    MagickBooleanType
        ret;

    ImageInfo
        *image_info;

    DrawInfo
        *draw_info;

    int i;
    int array_len = Int_val(array_length);


    image_info = CloneImageInfo((ImageInfo *) NULL);

    draw_info = CloneDrawInfo( image_info, ( DrawInfo* )NULL );
    DestroyImageInfo(image_info);

    if ( !draw_info ) {
#if DEBUG
        fprintf(stderr, "CloneDrawInfo() failed\n"); fflush(stderr);
#endif
        caml_failwith("draw_polygon failed");
    }

    PixelInfo
        fill;

    fill.red     = (Quantum) Long_val(fill_red);
    fill.green   = (Quantum) Long_val(fill_green);
    fill.blue    = (Quantum) Long_val(fill_blue);
    fill.alpha = (Quantum) Long_val(fill_alpha);

    draw_info->fill = fill;


    PixelInfo
        stroke;

    stroke.red     = (Quantum) Long_val(stroke_red);
    stroke.green   = (Quantum) Long_val(stroke_green);
    stroke.blue    = (Quantum) Long_val(stroke_blue);
    stroke.alpha = (Quantum) Long_val(stroke_alpha);

    /*
       typedef struct _DrawInfo
       {
         PixelPacket fill, stroke;
         double stroke_width;
         CompositeOperator compose;
         LineCap linecap;
         LineJoin linejoin;
         ...
       } DrawInfo;
    */
    draw_info->stroke = stroke;

    draw_info->stroke_width = Double_val(width);
    draw_info->stroke_antialias = MagickBoolean_val(stroke_antialias);

    draw_info->linejoin = LineJoin_val(line_join);


    AffineMatrix affine;
    fill_AffineMatrix( &affine,
            Double_val(sx),
            Double_val(rx),
            Double_val(ry),
            Double_val(sy),
            Double_val(tx),
            Double_val(ty) );
    draw_info->affine = affine;


    char str_buffer[ MaxTextExtent ];
    char str_buffer_tmp[ MaxTextExtent ];
    int str_len;
    value coords;

    /*
     * Feed the primitive "polygon  x0,y0  ...  xn,yn"
     */
    str_len = snprintf( str_buffer, MaxTextExtent, "polygon" );

    for (i=0; i < array_len; i++) {

        coords = Field(array, i);

        strcpy( str_buffer_tmp, str_buffer );

        str_len = snprintf( str_buffer, MaxTextExtent, "%s %ld,%ld",
                    str_buffer_tmp,
                    Long_val(Field(coords,0)),
                    Long_val(Field(coords,1)) );
    }

    (void) CloneString(&draw_info->primitive, str_buffer);

    ExceptionInfo *excinfo = AcquireExceptionInfo();
    ret = DrawImage((Image *) Field(image_bloc,1), draw_info, excinfo);
    excinfo = DestroyExceptionInfo(excinfo);

    if (ret == MagickFalse) {
#if DEBUG
        fprintf(stderr, "DrawImage() failed\n"); fflush(stderr);
#endif
        caml_failwith("draw_polygon failed");
    }


    /* @FIXME: draw_info should be freed
     * but sometimes it produces a Segmentation fault
     */
#if MAKE_DESTROY_DRAWINFO
    DestroyDrawInfo(draw_info);
#endif


    CAMLreturn( Val_unit );
}

CAMLprim value
imper_draw_polygon_bytecode(value * argv, int argn)
{
      return imper_draw_polygon_native(
                argv[0],  argv[1],  argv[2],  argv[3],  argv[4],  argv[5],
                argv[6],  argv[7],  argv[8],  argv[9],  argv[10], argv[11],
                argv[12], argv[13], argv[14], argv[15], argv[16], argv[17],
                argv[18], argv[19] );
}
/* }}} */
/* {{{ imper_draw_bezier() 
 *
 * (DrawInfo *)->primitive = "Bezier  x0,y0  ...  xn,yn"
 */

CAMLprim value
imper_draw_bezier_native(
        value image_bloc,
        value array,
        value array_length,

        value fill_red,
        value fill_green,
        value fill_blue,
        value fill_alpha,

        value stroke_red,
        value stroke_green,
        value stroke_blue,
        value stroke_alpha,

        value stroke_antialias,
        value width,
        value line_cap,

        value sx,
        value rx,
        value ry,
        value sy,
        value tx,
        value ty )
{
    CAMLparam5( image_bloc, array, array_length, fill_red, fill_green );
    CAMLxparam5( fill_blue, fill_alpha, stroke_red, stroke_green, stroke_blue );
    CAMLxparam5( stroke_alpha, stroke_antialias, width, line_cap, sx );
    CAMLxparam5( rx, ry, sy, tx, ty );

    MagickBooleanType
        ret;

    ImageInfo
        *image_info;

    DrawInfo
        *draw_info;

    int i;
    int array_len = Int_val(array_length);


    image_info = CloneImageInfo((ImageInfo *) NULL);

    draw_info = CloneDrawInfo( image_info, ( DrawInfo* )NULL );
    DestroyImageInfo(image_info);

    if ( !draw_info ) {
#if DEBUG
        fprintf(stderr, "CloneDrawInfo() failed\n"); fflush(stderr);
#endif
        caml_failwith("draw_bezier failed");
    }

    PixelInfo
        fill;

    fill.red     = (Quantum) Long_val(fill_red);
    fill.green   = (Quantum) Long_val(fill_green);
    fill.blue    = (Quantum) Long_val(fill_blue);
    fill.alpha = (Quantum) Long_val(fill_alpha);

    draw_info->fill = fill;


    PixelInfo
        stroke;

    stroke.red     = (Quantum) Long_val(stroke_red);
    stroke.green   = (Quantum) Long_val(stroke_green);
    stroke.blue    = (Quantum) Long_val(stroke_blue);
    stroke.alpha = (Quantum) Long_val(stroke_alpha);

    /*
       typedef struct _DrawInfo
       {
         PixelPacket fill, stroke;
         double stroke_width;
         CompositeOperator compose;
         LineCap linecap;
         LineJoin linejoin;
         ...
       } DrawInfo;
    */
    draw_info->stroke = stroke;

    draw_info->stroke_width = Double_val(width);
    draw_info->stroke_antialias = MagickBoolean_val(stroke_antialias);

    draw_info->linecap  = LineCap_val(line_cap);


    AffineMatrix affine;
    fill_AffineMatrix( &affine,
            Double_val(sx),
            Double_val(rx),
            Double_val(ry),
            Double_val(sy),
            Double_val(tx),
            Double_val(ty) );
    draw_info->affine = affine;


    char str_buffer[ MaxTextExtent ];
    char str_buffer_tmp[ MaxTextExtent ];
    int str_len;
    value coords;

    /*
     * Feed the primitive "Bezier  x0,y0  ...  xn,yn"
     */
    str_len = snprintf( str_buffer, MaxTextExtent, "bezier" );

    for (i=0; i < array_len; i++) {

        coords = Field(array, i);

        strcpy( str_buffer_tmp, str_buffer );

        str_len = snprintf( str_buffer, MaxTextExtent, "%s %ld,%ld",
                    str_buffer_tmp,
                    Long_val(Field(coords,0)),
                    Long_val(Field(coords,1)) );
    }

    (void) CloneString(&draw_info->primitive, str_buffer);

    ExceptionInfo *excinfo = AcquireExceptionInfo();
    ret = DrawImage((Image *) Field(image_bloc,1), draw_info, excinfo);
    excinfo = DestroyExceptionInfo(excinfo);

    if (ret == MagickFalse) {
#if DEBUG
        fprintf(stderr, "DrawImage() failed\n"); fflush(stderr);
#endif
        caml_failwith("draw_bezier failed");
    }


    /* @FIXME: draw_info should be freed
     * but sometimes it produces a Segmentation fault
     */
#if MAKE_DESTROY_DRAWINFO
    DestroyDrawInfo(draw_info);
#endif


    CAMLreturn( Val_unit );
}

CAMLprim value
imper_draw_bezier_bytecode(value * argv, int argn)
{
      return imper_draw_bezier_native(
                argv[0],  argv[1],  argv[2],  argv[3],  argv[4],  argv[5],
                argv[6],  argv[7],  argv[8],  argv[9],  argv[10], argv[11],
                argv[12], argv[13], argv[14], argv[15], argv[16], argv[17],
                argv[18], argv[19] );
}
/* }}} */

/* {{{ imper_draw_path() 
 *
 * (DrawInfo *)->primitive
 *       path     path specification  (SVG string path)
 */

CAMLprim value
imper_draw_path_native(
        value image_bloc,
        value path,

        value fill_red,
        value fill_green,
        value fill_blue,
        value fill_alpha,

        value stroke_red,
        value stroke_green,
        value stroke_blue,
        value stroke_alpha,

        value stroke_antialias,
        value stroke_width,
        value line_join,
        value line_cap,

        value sx,
        value rx,
        value ry,
        value sy,
        value tx,
        value ty )
{
    CAMLparam5( image_bloc, path, fill_red, fill_green, fill_blue );
    CAMLxparam5( fill_alpha, stroke_red, stroke_green, stroke_blue, stroke_alpha );
    CAMLxparam5( stroke_antialias, stroke_width, line_join, line_cap, sx );
    CAMLxparam5( rx, ry, sy, tx, ty );

    MagickBooleanType
        ret;

    ImageInfo
        *image_info;

    DrawInfo
        *draw_info;


    image_info = CloneImageInfo((ImageInfo *) NULL);

    draw_info = CloneDrawInfo( image_info, ( DrawInfo* )NULL );
    DestroyImageInfo(image_info);

    if ( !draw_info ) {
#if DEBUG
        fprintf(stderr, "CloneDrawInfo() failed\n"); fflush(stderr);
#endif
        caml_failwith("draw_path failed");
    }


    PixelInfo
        fill;

    fill.red     = (Quantum) Long_val(fill_red);
    fill.green   = (Quantum) Long_val(fill_green);
    fill.blue    = (Quantum) Long_val(fill_blue);
    fill.alpha = (Quantum) Long_val(fill_alpha);

    draw_info->fill = fill;


    PixelInfo
        stroke;

    stroke.red     = (Quantum) Long_val(stroke_red);
    stroke.green   = (Quantum) Long_val(stroke_green);
    stroke.blue    = (Quantum) Long_val(stroke_blue);
    stroke.alpha = (Quantum) Long_val(stroke_alpha);

    draw_info->stroke = stroke;

    /*
       typedef struct _DrawInfo
       {
         PixelPacket fill, stroke;
         double stroke_width;
         CompositeOperator compose;
         LineCap linecap;
         LineJoin linejoin;
         ...
       } DrawInfo;
    */

    draw_info->stroke_width = Double_val(stroke_width);
    draw_info->stroke_antialias = MagickBoolean_val(stroke_antialias);

    draw_info->linecap  = LineCap_val(line_cap);
    draw_info->linejoin = LineJoin_val(line_join);


    AffineMatrix affine;
    fill_AffineMatrix( &affine,
            Double_val(sx),
            Double_val(rx),
            Double_val(ry),
            Double_val(sy),
            Double_val(tx),
            Double_val(ty) );
    draw_info->affine = affine;


    char str_buffer[ MaxTextExtent ];
    int str_len;

    /* Feed the primitive "path spec" */
    str_len = snprintf( str_buffer, MaxTextExtent, "path '%s'", String_val(path) );
    (void) CloneString(&draw_info->primitive, str_buffer);

    ExceptionInfo *excinfo = AcquireExceptionInfo();
    ret = DrawImage((Image *) Field(image_bloc,1), draw_info, excinfo);
    excinfo = DestroyExceptionInfo(excinfo);

    if (ret == MagickFalse) {
#if DEBUG
        fprintf(stderr, "DrawImage() failed\n"); fflush(stderr);
#endif
        caml_failwith("draw_path failed");
    }

    /* @FIXME: draw_info should be freed
     * but sometimes it produces a Segmentation fault
     */
#if MAKE_DESTROY_DRAWINFO
    DestroyDrawInfo(draw_info);
#endif

    CAMLreturn( Val_unit );
}

CAMLprim value
imper_draw_path_bytecode(value * argv, int argn)
{
      return imper_draw_path_native(
                argv[0],  argv[1],  argv[2],  argv[3],  argv[4],  argv[5],
                argv[6],  argv[7],  argv[8],  argv[9],  argv[10], argv[11],
                argv[12], argv[13], argv[14], argv[15], argv[16], argv[17],
                argv[18], argv[19] );
}
/* }}} */


/* {{{ StyleType_val() */

static int
StyleType_val( value param )
{
    CONVALparam1 (param);

#if TYPE_CHECKING
    assert( Is_long(param) );
#endif

    switch (Int_val (param))
      {
        case 0: return UndefinedStyle;
        case 1: return NormalStyle;
        case 2: return ItalicStyle;
        case 3: return ObliqueStyle;
        case 4: return AnyStyle;
        default:
#if DEBUG
            fprintf(stderr, "StyleType_val() failed\n"); fflush(stderr);
            abort();
#else
            return UndefinedStyle;
#endif
      }
}

/* }}} */
/* {{{ DecorationType_val() */

static int
DecorationType_val( value param )
{
    CONVALparam1 (param);

#if TYPE_CHECKING
    assert (Is_long (param));
#endif

    switch (Int_val (param))
      {
        case 0: return UndefinedDecoration;
        case 1: return NoDecoration;
        case 2: return UnderlineDecoration;
        case 3: return OverlineDecoration;
        case 4: return LineThroughDecoration;
        default:
#if DEBUG
            fprintf(stderr, "DecorationType_val() failed\n"); fflush(stderr);
            abort();
#else
            return UndefinedDecoration;
#endif
      }
}

/* }}} */


/* {{{ StretchType_val() */

static int
StretchType_val( value param )
{
    CONVALparam1 (param);

#if TYPE_CHECKING
    assert (Is_long (param));
#endif

    switch (Int_val (param))
      {
        case  0: return UndefinedStretch;
        case  1: return NormalStretch;
        case  2: return UltraCondensedStretch;
        case  3: return ExtraCondensedStretch;
        case  4: return CondensedStretch;
        case  5: return SemiCondensedStretch;
        case  6: return SemiExpandedStretch;
        case  7: return ExpandedStretch;
        case  8: return ExtraExpandedStretch;
        case  9: return UltraExpandedStretch;
        case 10: return AnyStretch;
        default:
#if DEBUG
            fprintf(stderr, "StretchType_val() failed\n"); fflush(stderr);
            abort();
#else
            return UndefinedStretch;
#endif
      }
}

/* }}} */

/* {{{ imper_draw_text() */

CAMLprim value
imper_draw_text_native(
        value image_bloc,
        value text,
        value font,

        value x,
        value y,
        value pointsize,
        value density_x,
        value density_y,
        value style,
        value weight,
        value decoration,
        value stretch,

        value fill_red,
        value fill_green,
        value fill_blue,
        value fill_alpha,

        value stroke_red,
        value stroke_green,
        value stroke_blue,
        value stroke_alpha,

        value stroke_width,
        value stroke_antialias,
        value text_antialias,
        value encoding,

        value sx,
        value rx,
        value ry,
        value sy,
        value tx,
        value ty )
{
    CAMLparam5( image_bloc, text, font, x, y );
    CAMLxparam5( pointsize, density_x, density_y, style, weight );
    CAMLxparam5( decoration, stretch, fill_red, fill_green, fill_blue );
    CAMLxparam5( fill_alpha, stroke_red, stroke_green, stroke_blue, stroke_alpha );
    CAMLxparam5( stroke_width, stroke_antialias, text_antialias, encoding, sx );
    CAMLxparam5( rx, ry, sy, tx, ty );

    MagickBooleanType
        ret;

    ImageInfo
        *image_info;

    DrawInfo
        *draw_info;

    char
        str_buffer[ MaxTextExtent ];

    int str_len;


    image_info = CloneImageInfo((ImageInfo *) NULL);

    draw_info = CloneDrawInfo( image_info, ( DrawInfo* )NULL );
    DestroyImageInfo(image_info);

    if ( !draw_info ) {
#if DEBUG
        fprintf(stderr, "CloneDrawInfo() failed\n"); fflush(stderr);
#endif
        caml_failwith("draw_text failed");
    }


    PixelInfo fill;

    fill.red     = (Quantum) Long_val(fill_red);
    fill.green   = (Quantum) Long_val(fill_green);
    fill.blue    = (Quantum) Long_val(fill_blue);
    fill.alpha = (Quantum) Long_val(fill_alpha);

    draw_info->fill = fill;


    PixelInfo stroke;

    stroke.red     = (Quantum) Long_val(stroke_red);
    stroke.green   = (Quantum) Long_val(stroke_green);
    stroke.blue    = (Quantum) Long_val(stroke_blue);
    stroke.alpha = (Quantum) Long_val(stroke_alpha);

    draw_info->stroke = stroke;

    /* typedef struct _DrawInfo
       {
          CompositeOperator compose;
          ...
       } DrawInfo; */

    draw_info->stroke_width = Double_val(stroke_width);

    draw_info->stroke_antialias = MagickBoolean_val(stroke_antialias);
    draw_info->text_antialias   = MagickBoolean_val(text_antialias);

    draw_info->pointsize = Double_val(pointsize);
    draw_info->style = StyleType_val(style);

    draw_info->weight = (unsigned long) Long_val(weight);


    draw_info->render = MagickTrue;  /* @TODO: find what is this ! */


    /* TODO */
#if 0
    draw_info->text         /* for the actual text to draw */
    draw_info->undercolor   /* to draw a box under the text */
    draw_info->family       /* to specify the font family to draw text with */
    draw_info->encoding     /* to set the font encoding */
    draw_info->metrics = "";
#endif

    /* {{{ DrawInfo 

    typedef struct _DrawInfo
    {
      char
        *primitive,
        *geometry;

      RectangleInfo
        viewbox;

      AffineMatrix
        affine;

      GravityType
        gravity;

      PixelPacket
        fill,
        stroke;

      double
        stroke_width;

      GradientInfo
        gradient;

      Image
        *fill_pattern,
        *tile,
        *stroke_pattern;

      MagickBooleanType
        stroke_antialias,
        text_antialias;

      FillRule
        fill_rule;

      LineCap
        linecap;

      LineJoin
        linejoin;

      unsigned long
        miterlimit;

      double
        dash_offset;

      DecorationType
        decorate;

      CompositeOperator
        compose;

      char
        *text;

      unsigned long
        face;

      char
        *font,
        *metrics,
        *family;

      StyleType
        style;

      StretchType
        stretch;

      unsigned long
        weight;

      char
        *encoding;

      double
        pointsize;

      char
        *density;

      AlignType
        align;

      PixelPacket
        undercolor,
        border_color;

      char
        *server_name;

      double
        *dash_pattern;

      char
        *clip_path;

      SegmentInfo
        bounds;

      ClipPathUnits
        clip_units;

      Quantum
        alpha;

      MagickBooleanType
        render;

      ElementReference
        element_reference;

      MagickBooleanType
        debug;

      unsigned long
        signature;
    } DrawInfo;

    \* }}} ======== */


    AffineMatrix affine;
    fill_AffineMatrix( &affine,
            Double_val(sx),
            Double_val(rx),
            Double_val(ry),
            Double_val(sy),
            Double_val(tx),
            Double_val(ty) );
    draw_info->affine = affine;


    if ( strlen(String_val(font)) ) {
        (void) CloneString(&draw_info->font, String_val(font) );
    }

    if ( strlen(String_val(encoding)) ) {
        (void) CloneString(&draw_info->encoding, String_val(encoding) );
    }

    /* set the font resolution (default: "72x72") */
    str_len = snprintf( str_buffer, MaxTextExtent, "%ldx%ld", Long_val(density_x), Long_val(density_y) );
    (void) CloneString(&draw_info->density, str_buffer);

    draw_info->decorate = DecorationType_val(decoration);


    /* TODO

      unsigned long
        face;
    */

    /* @TODO: I don't see any effect with any stretch. */
    draw_info->stretch = StretchType_val(stretch);
#if DEBUG
    printf(" Stretch = '%d'\n", draw_info->stretch); fflush(stdout);
#endif


    /* Feed the primitive "text spec" */
    str_len = snprintf( str_buffer, MaxTextExtent, "text %ld,%ld '%s'",
                              Long_val(x), Long_val(y), String_val(text) );
    (void) CloneString(&draw_info->primitive, str_buffer);


    ExceptionInfo *excinfo = AcquireExceptionInfo();
    ret = DrawImage((Image *) Field(image_bloc,1), draw_info, excinfo);
    excinfo = DestroyExceptionInfo(excinfo);

    if (ret == MagickFalse) {
#if DEBUG
        fprintf(stderr, "DrawImage() failed\n"); fflush(stderr);
#endif
        caml_failwith("draw_text failed");
    }


    /* @FIXME: draw_info should be freed
     * but sometimes it produces a Segmentation fault
     */
#if MAKE_DESTROY_DRAWINFO
    DestroyDrawInfo(draw_info);
#endif


    CAMLreturn( Val_unit );
}

CAMLprim value
imper_draw_text_bytecode(value * argv, int argn)
{
      return imper_draw_text_native(
                argv[0],  argv[1],  argv[2],  argv[3],  argv[4],  argv[5],
                argv[6],  argv[7],  argv[8],  argv[9],  argv[10], argv[11],
                argv[12], argv[13], argv[14], argv[15], argv[16], argv[17],
                argv[18], argv[19], argv[20], argv[21], argv[22], argv[23],
                argv[24], argv[25], argv[26], argv[27], argv[28], argv[29] );
}
/* }}} */

/* {{{ imper_get_metrics() */

CAMLprim value
imper_get_metrics_native(
        value image_bloc,
        value text,
        value font,

        value x,
        value y,
        value pointsize,
        value density_x,
        value density_y,

        value style,
        value weight,
        value decoration,
        value stretch,

        value stroke_width,

        value sx,
        value rx,
        value ry,
        value sy,
        value tx,
        value ty )
{
    CAMLparam5( image_bloc, text, font, x, y );
    CAMLxparam5( pointsize, density_x, density_y, style, weight );
    CAMLxparam5( decoration, stretch, stroke_width, sx, rx );
    CAMLxparam4( ry, sy, tx, ty );

    CAMLlocal5(
        tuple_metrics,
        ascent, descent,
        width, height );
    CAMLlocal5(
        max_advance,
        underline_position,
        underline_thickness,
        x_, y_ );
    CAMLlocal4( x1, y1, x2, y2 );


    MagickBooleanType
        ret;

    ImageInfo
        *image_info;

    DrawInfo
        *draw_info;

    char
        str_buffer[ MaxTextExtent ];

    int str_len;


    image_info = CloneImageInfo((ImageInfo *) NULL);

    draw_info = CloneDrawInfo( image_info, ( DrawInfo* )NULL );
    DestroyImageInfo(image_info);

    if ( !draw_info ) {
#if DEBUG
        fprintf(stderr, "CloneDrawInfo() failed\n"); fflush(stderr);
#endif
        caml_failwith("draw_text failed");
    }

    /*
       typedef struct _DrawInfo
       {
         PixelPacket fill, stroke;
         double stroke_width;
         CompositeOperator compose;
         ...
       } DrawInfo;
    */

    draw_info->stroke_width = Double_val(stroke_width);
    draw_info->stroke_antialias = MagickTrue;

    draw_info->text_antialias = MagickTrue;
    draw_info->pointsize = Double_val(pointsize);
    draw_info->style = StyleType_val(style);

    draw_info->weight = (unsigned long) Long_val(weight);


    draw_info->render = MagickTrue;  /* @TODO: find what is this ! */


    if ( strlen(String_val(font)) ) {
        (void) CloneString(&draw_info->font, String_val(font) );
    }


    AffineMatrix affine;
    fill_AffineMatrix( &affine,
            Double_val(sx),
            Double_val(rx),
            Double_val(ry),
            Double_val(sy),
            Double_val(tx),
            Double_val(ty) );
    draw_info->affine = affine;


    /* @TODO:

    draw_info->metrics = "";
    draw_info->family = "";

      char
        *metrics,
        *family;
    */

    /* density example: "72x72" */
    str_len = snprintf( str_buffer, MaxTextExtent, "%ldx%ld", Long_val(density_x), Long_val(density_y) );
    (void) CloneString(&draw_info->density, str_buffer);

    draw_info->decorate = DecorationType_val(decoration);

    /* @TODO: I don't see any effect with any stretch. */
    draw_info->stretch = StretchType_val(stretch);
#if DEBUG
    printf(" stretch = '%d'\n", draw_info->stretch);
#endif

    /* TODO

      unsigned long
        face;
    */


    /* Feed the primitive "text spec" */
    str_len = snprintf( str_buffer, MaxTextExtent, "text %ld,%ld '%s'",
                              Long_val(x), Long_val(y), String_val(text) );
    (void) CloneString(&draw_info->primitive, str_buffer);


    TypeMetric metrics_infos;

    (void) CloneString(&draw_info->text, String_val(text) );

    ExceptionInfo *excinfo = AcquireExceptionInfo();
    ret = GetMultilineTypeMetrics((Image *) Field(image_bloc,1), draw_info, &metrics_infos, excinfo);
    excinfo = DestroyExceptionInfo(excinfo);

    if (ret == MagickFalse) {
#if DEBUG
        fprintf(stderr, "GetMultilineTypeMetrics() failed\n"); fflush(stderr);
#endif
        caml_failwith("get_text_metrics failed");
    }

    /* {{{ dev */

#if 0
#if DEBUG
    printf("\n\
    ascent  %f\n\
    descent %f\n\
    width   %f\n\
    height  %f\n\
    max_advance   %f\n\
    underline_position   %f\n\
    underline_thickness  %f\n\
\n",
        (double) metrics_infos->ascent,
        (double) metrics_infos->descent,
        (double) metrics_infos->width,
        (double) metrics_infos->height,
        (double) metrics_infos->max_advance,
        (double) metrics_infos->underline_position,
        (double) metrics_infos->underline_thickness );
#endif
#endif

/*
typedef struct _TypeMetric
{
  PointInfo
    pixels_per_em;

  double
    ascent,
    descent,
    width,
    height,
    max_advance,
    underline_position,
    underline_thickness;

  SegmentInfo
    bounds;
} TypeMetric;


typedef struct _PointInfo
{
  double
    x,
    y;
} PointInfo;


typedef struct _SegmentInfo
{
  double
    x1,
    y1,
    x2,
    y2;
} SegmentInfo;
*/

/* en:  ascent  descent   advance  thickness
   fr:  montée  descente  avancée  épaisseur

   example:
     ascent: 21.0
     descent: -6.0
     width: 267.0
     height: 28.0
     max_advance: 30.0
     underline_position: -1.953125
     underline_thickness: 0.937500
*/

    /* }}} */

    ascent              = caml_copy_double( (double) metrics_infos.ascent              );
    descent             = caml_copy_double( (double) metrics_infos.descent             );
    width               = caml_copy_double( (double) metrics_infos.width               );
    height              = caml_copy_double( (double) metrics_infos.height              );
    max_advance         = caml_copy_double( (double) metrics_infos.max_advance         );
    underline_position  = caml_copy_double( (double) metrics_infos.underline_position  );
    underline_thickness = caml_copy_double( (double) metrics_infos.underline_thickness );

    x_ = caml_copy_double( (double) metrics_infos.pixels_per_em.x );
    y_ = caml_copy_double( (double) metrics_infos.pixels_per_em.y );

    x1 = caml_copy_double( (double) metrics_infos.bounds.x1 );
    y1 = caml_copy_double( (double) metrics_infos.bounds.y1 );
    x2 = caml_copy_double( (double) metrics_infos.bounds.x2 );
    y2 = caml_copy_double( (double) metrics_infos.bounds.y2 );

    tuple_metrics = caml_alloc_tuple(13);

    Store_field(tuple_metrics, 0, ascent              );
    Store_field(tuple_metrics, 1, descent             );
    Store_field(tuple_metrics, 2, width               );
    Store_field(tuple_metrics, 3, height              );
    Store_field(tuple_metrics, 4, max_advance         );
    Store_field(tuple_metrics, 5, underline_position  );
    Store_field(tuple_metrics, 6, underline_thickness );

    Store_field(tuple_metrics,  7, x_ );
    Store_field(tuple_metrics,  8, y_ );
    Store_field(tuple_metrics,  9, x1 );
    Store_field(tuple_metrics, 10, y1 );
    Store_field(tuple_metrics, 11, x2 );
    Store_field(tuple_metrics, 12, y2 );


    /* @FIXME: draw_info should be freed
     * but sometimes it produces a Segmentation fault
     */
#if MAKE_DESTROY_DRAWINFO
    DestroyDrawInfo(draw_info);
#endif


    CAMLreturn( tuple_metrics );
}

CAMLprim value
imper_get_metrics_bytecode(value * argv, int argn)
{
      return imper_get_metrics_native(
                argv[0],  argv[1],  argv[2],  argv[3],  argv[4],  argv[5],
                argv[6],  argv[7],  argv[8],  argv[9],  argv[10], argv[11],
                argv[12], argv[13], argv[14], argv[15], argv[16], argv[17],
                argv[18] );
}
/* }}} */


/* {{{ imper_draw_text_new1()
 *
 *   draw_info->text for the actual text to draw
 *   draw_info->undercolor to draw a box under the text
 *   draw_info->affine to rotate, scale, translate the text
 *   draw_info->font to specify the font to draw text with
 *   draw_info->family to specify the font family to draw text with
 *   draw_info->density to set the font resolution (defaults to 72x72)
 *   draw_info->pointsize to set the font pointsize
 *   draw_info->encoding to set the font encoding
 *   draw_info->fill to set the text fill color
 *   draw_info->stroke to set the text stroke color
 *   draw_info->text_antialias to set text antialiasing
 */
CAMLprim value
imper_draw_text_new1(
        value image_bloc,
        value text )
{
    CAMLparam2(image_bloc, text);

    MagickBooleanType
        ret;

    DrawInfo
        *draw_info;

    ImageInfo
        *image_info;


    image_info = CloneImageInfo((ImageInfo *) NULL);
    draw_info = CloneDrawInfo( image_info, ( DrawInfo* )NULL );
    DestroyImageInfo(image_info);

    if ( !draw_info ) {
#if DEBUG
        fprintf(stderr, "CloneDrawInfo() failed\n"); fflush(stderr);
#endif
        caml_failwith("draw_text failed");
    }

#if 0

Typedef struct _DrawInfo
{
  char
    *primitive,
    *geometry;

  RectangleInfo
    viewbox;

  AffineMatrix
    affine;

  GravityType
    gravity;

  PixelPacket
    fill,
    stroke;

  double
    stroke_width;

  GradientInfo
    gradient;

  Image
    *fill_pattern,
    *tile,
    *stroke_pattern;

  MagickBooleanType
    stroke_antialias,
    text_antialias;

  FillRule
    fill_rule;

  LineCap
    linecap;

  LineJoin
    linejoin;

  unsigned long
    miterlimit;

  double
    dash_offset;

  DecorationType
    decorate;

  CompositeOperator
    compose;

  char
    *text;

  unsigned long
    face;

  char
    *font,
    *metrics,
    *family;

  StyleType
    style;

  StretchType
    stretch;

  unsigned long
    weight;

  char
    *encoding;

  double
    pointsize;

  char
    *density;

  AlignType
    align;

  PixelPacket
    undercolor,
    border_color;

  char
    *server_name;

  double
    *dash_pattern;

  char
    *clip_path;

  SegmentInfo
    bounds;

  ClipPathUnits
    clip_units;

  Quantum
    alpha;

  MagickBooleanType
    render;

  ElementReference
    element_reference;

  MagickBooleanType
    debug;

  unsigned long
    signature;
} DrawInfo;

    draw_info->text            /* for the actual text to draw */
    draw_info->undercolor      /* to draw a box under the text */
    draw_info->affine          /* to rotate, scale, translate the text */
    draw_info->font            /* to specify the font to draw text with */
    draw_info->family          /* to specify the font family to draw text with */
    draw_info->density         /* to set the font resolution (defaults to 72x72) */
    draw_info->pointsize       /* to set the font pointsize */
    draw_info->encoding        /* to set the font encoding */
    draw_info->fill            /* to set the text fill color */
    draw_info->stroke          /* to set the text stroke color */
    draw_info->text_antialias  /* to set text antialiasing */
#endif

    (void) CloneString(&draw_info->text, String_val(text) );
    (void) CloneString(&draw_info->geometry, "20x20");
    
    if (draw_info->font == (char *) NULL) {
        printf(" font uninitiatized\n"); fflush(stdout);
    } else {
        printf(" font set to: '%s'\n", draw_info->font ); fflush(stdout);
    }

    ExceptionInfo *excinfo = AcquireExceptionInfo();
    ret = DrawImage((Image *) Field(image_bloc,1), draw_info, excinfo);
    excinfo = DestroyExceptionInfo(excinfo);

    if (ret == MagickFalse) {
#if DEBUG
        fprintf(stderr, "DrawImage() failed\n"); fflush(stderr);
#endif
        caml_failwith("draw_text failed");
    }


    /* @FIXME: draw_info should be freed
     * but sometimes it produces a Segmentation fault
     */
#if MAKE_DESTROY_DRAWINFO
    DestroyDrawInfo(draw_info);
#endif


    CAMLreturn( Val_unit );
}

/* }}} */

    /* {{{ Primitives TODO 
     *
     * image    operator x0,y0 w,h filename
     * }}} */
    /* {{{ from the doc 
     *
     *  point          x,y
     *  line           x0,y0 x1,y1
     *  rectangle      x0,y0 x1,y1
     *  roundRectangle x0,y0 x1,y1 wc,hc
     *  arc            x0,y0 x1,y1 a0,a1
     *  ellipse        x0,y0 rx,ry a0,a1
     *  circle         x0,y0 x1,y1
     *  polyline       x0,y0  ...  xn,yn
     *  polygon        x0,y0  ...  xn,yn
     *  Bezier         x0,y0  ...  xn,yn
     *  path           path specification
     *  image          operator x0,y0 w,h filename
     *
     * }}} */
    /* {{{ from the sources 
     * affine d,d,d,d,d,d
     * arc
     * bezier
     * clip-path
     * clip-rule
     * clip-units
     * circle
     * color
     * decorate
     * ellipse
     * encoding
     * fill
     * fill-rule
     * fill-alpha
     * font
     * font-family
     * font-size
     * font-stretch
     * font-style
     * font-weight
     * gradient-units
     * gravity
     * image
     * line
     * matte
     * offset
     * alpha
     * path
     * point
     * polyline
     * polygon
     * pop
     *   clip-path
     *   defs
     *   gradient
     *   graphic-context
     *   pattern
     * push
     *   clip-path
     *   pop
     *   clip-path
     *   gradient
     *   radial
     *   pop
     *   gradient
     * pattern d,d,d,d
     * graphic-context
     * rectangle
     * rotate
     * roundRectangle
     * scale
     * skewX
     * skewY
     * stop-color
     * stroke
     * stroke-antialias
     * stroke-dasharray
     * stroke-dashoffset
     * stroke-linecap
     * stroke-linejoin
     * stroke-miterlimit
     * stroke-alpha
     * stroke-width
     * text
     * text-align
     * text-anchor
     * text-antialias
     * text-undercolor
     * translate d,d
     * viewbox d,d,d,d
     *
     * }}} */

/* {{{ imper_draw_mvg() 
 */

CAMLprim value
imper_draw_mvg(
        value image_bloc,
        value mvg )
{
    CAMLparam2( image_bloc, mvg );

    MagickBooleanType
        ret;

    DrawInfo
        *draw_info;

    {
        ImageInfo
            *image_info;

        image_info = CloneImageInfo((ImageInfo *) NULL);
        draw_info = CloneDrawInfo( image_info, ( DrawInfo* )NULL );
        DestroyImageInfo(image_info);
    }

    if ( !draw_info ) {
#if DEBUG
        fprintf(stderr, "CloneDrawInfo() failed\n"); fflush(stderr);
#endif
        caml_failwith("draw_mvg failed");
    }

    (void) CloneString(&draw_info->primitive, String_val(mvg) );

    ExceptionInfo *excinfo = AcquireExceptionInfo();
    ret = DrawImage((Image *) Field(image_bloc,1), draw_info, excinfo);
    excinfo = DestroyExceptionInfo(excinfo);

    if (ret == MagickFalse) {
#if DEBUG
        fprintf(stderr, "DrawImage() failed\n"); fflush(stderr);
#endif
        caml_failwith("draw_mvg failed");
    }

    /* @FIXME: draw_info should be freed
     * but sometimes it produces a Segmentation fault
     */
#if MAKE_DESTROY_DRAWINFO
    DestroyDrawInfo(draw_info);
#endif

    CAMLreturn( Val_unit );
}
/* }}} */

#if 0
/* {{{ imper_setimagepixel() 
 *
 * PixelPacket *SetImagePixels(Image *image, const long x, const long y,
 *                const unsigned long columns,
 *                const unsigned long rows)
 *
 * MagickBooleanType SyncImagePixels(Image *image)
 */

CAMLprim value
imper_setimagepixel(
            value image_bloc,
            value x,
            value y )
{
    CAMLparam3( image_bloc, x, y );

    PixelPacket
        *pixels;

    /*
    PixelPacket
        pixel;
    */

    MagickBooleanType
        ret;

    Image *img;

    pixels = GetImagePixels(
                    (Image *) Field(image_bloc,1),
                    Long_val(x),
                    Long_val(y),
                    1, 1);

    if (pixels == (PixelPacket *) NULL) {
        caml_failwith("setimagepixel failed") ;
    }

    /*
    printf("\tsizeof pixels = %d\n", sizeof(pixels));
    */

    printf("\tR G B = %d %d %d\n",
                    pixels[0].red,
                    pixels[0].green,
                    pixels[0].blue );

    pixels->red     = 0;
    pixels->green   = 0;
    pixels->blue    = 0;
    pixels->alpha = 0;

    img = ( (Image *) Field(image_bloc,1) ) ;

    printf("\tR G B = %d %d %d\n",
                    pixels[0].red,
                    pixels[0].green,
                    pixels[0].blue );

    /* ret = SyncImagePixels( (Image *) Field(image_bloc,1) ); */
    /* ret = SyncImage( (Image *) Field(image_bloc,1) ); */
    /* ret = SyncCache( (Image *) Field(image_bloc,1) ); */
    ret = SyncImagePixels( img );

    if (ret == MagickFalse) {
        caml_failwith("setimagepixel failed") ;
    }

    CAMLreturn( Val_unit );
}

/* }}} */
/* {{{ imper_loadimage()
 */

CAMLprim value
imper_loadimage(
            value width,
            value height,
            value color )
{
    CAMLparam3( width, height, color );

    CAMLlocal1(image_bloc);

    long x = Long_val(width);
    long y = Long_val(height);

    ExceptionInfo
        exception;

    ImageInfo
        *image_info;

    image_info = CloneImageInfo((ImageInfo *) NULL);


#if DEBUG
    image_bloc = caml_alloc_final(3, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */
#else
    image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */
#endif

    Field(image_bloc,1) = (value) alloc_image();


#if DEBUG
    Field(image_bloc,2) = malloc(sizeof(char) * strlen("loaded image"));
    Field(image_bloc,2) = "loaded image";
#endif


    if (IsMagickInstantiated() == MagickFalse) {
        MagickCoreGenesis(getenv("PWD"), MagickTrue);
    }

    const unsigned int _color = Int_val(color);
    unsigned int *pixels;
    register unsigned int *p;
    StorageType storage = IntegerPixel;

    /*
    double *pixels;
    register double *p;
    StorageType storage = DoublePixel;
    */

    const char *map;
    map = "RGBA";

    long i;
    register long j;
    register short m;
    short map_len = strlen(map);

    pixels = malloc(x * y * sizeof(unsigned int) * map_len);
    p = pixels;

    printf("\t color = '%d'\n", _color); fflush(stdout);

    for (i=0; i < y; ++i)
        for (j=0; j < x; ++j)
            for (m=0; m < map_len; ++m)
            {
                *p = _color;
                p++;
            }

    printf("\t pixels [0] = '%d'\n", pixels[0]);
    printf("\t pixels [1] = '%d'\n", pixels[1]);
    printf("\t pixels [2] = '%d'\n", pixels[2]); fflush(stdout);

    /* Image *ConstituteImage(const unsigned long columns, const unsigned long rows,
     *                        const char *map, const StorageType storage,
     *                        const void *pixels, ExceptionInfo *exception )
     */
    GetExceptionInfo(&exception);
    /*
    Field(image_bloc,1) = (value) ConstituteImage(x, y, map, storage, pixels, &exception);
    */
    Field(image_bloc,1) = (value) ConstituteImage(x, y, "RGBA", IntegerPixel, pixels, &exception);
    DestroyImageInfo(image_info);

    if (exception.severity != UndefinedException) {
        caml_failwith( exception.reason );
        /* @TODO  exception.description */
    }

    DestroyExceptionInfo(&exception);

    if ((Image *) Field(image_bloc,1) == (Image *) NULL) {
        caml_failwith("load_image failed");
    }

    CAMLreturn( image_bloc );
}
/* }}} */
#endif

/* }}} */

/* {{{ ====  RAWS  ==== */

/* {{{ imper_get_raw() 
 *
 * const PixelPacket *AcquireImagePixels(const Image *image,
 *                   const long x, const long y,
 *                   const unsigned long columns, const unsigned long rows,
 *                   ExceptionInfo *exception)
 */

CAMLprim value
imper_get_raw( value image_bloc )
{
    CAMLparam1( image_bloc );
    CAMLlocal3( pixel_matrix, column_array, color_tuple );
    unsigned long x, y;
    unsigned long columns, rows;

    ExceptionInfo
        *exception;

    PixelPacket
        pixel;

    columns = ((Image *) Field(image_bloc,1))->columns;
    rows    = ((Image *) Field(image_bloc,1))->rows;

    exception = AcquireExceptionInfo();

    const PixelPacket * pixel_packet_array;

    /* DEPR
    pixel_packet_array =
            AcquireImagePixels(
                     (Image *) Field(image_bloc,1),
                     0, 0,
                     columns, rows,
                     exception );
    */

    pixel_packet_array =
            GetVirtualPixels(
                     (Image *) Field(image_bloc,1),
                     0, 0,
                     columns, rows,
                     exception );

    if (exception->severity != UndefinedException)
    {
        caml_failwith( exception->reason );
    }
    DestroyExceptionInfo(exception);

    /* alloc_array(f, a) allocates an array of values, calling function f
     * over each element of the input array a to transform it into a value.
     * The array a is an array of pointers terminated by the null pointer.
     * The function f receives each pointer as argument, and returns a value.
     * The zero-tagged block returned by alloc_array(f, a) is filled with the values
     * returned by the successive calls to f.
     * (This function must not be used to build an array of floating-point numbers.)
     */
    /*
    PixelPacket init_columns[columns];
    PixelPacket init_rows[rows];

    pixel_matrix = alloc_array(fill_raw, init_columns);
    column_array = alloc_array(fill_raw, init_rows);
    */

    pixel_matrix = caml_alloc_tuple(columns);

    for (x=0; x < columns; ++x) {

        column_array = caml_alloc_tuple(rows);

        for (y=0; y < rows; ++y) {

            pixel = pixel_packet_array[(columns * y) + x];

            color_tuple  = caml_alloc_tuple(4);

            Store_field(color_tuple, 0, Val_long( (long) pixel.red ));
            Store_field(color_tuple, 1, Val_long( (long) pixel.green ));
            Store_field(color_tuple, 2, Val_long( (long) pixel.blue ));
            Store_field(color_tuple, 3, Val_long( MaxMap -
                                                  (long) pixel.alpha ));

            Store_field(column_array, y, color_tuple);
        }
        Store_field(pixel_matrix, x, column_array);
    }

    CAMLreturn( pixel_matrix );
}

/* }}} */
/* {{{ imper_get_raw_alpha() 
 *
 * const PixelPacket *AcquireImagePixels(const Image *image,
 *                   const long x, const long y,
 *                   const unsigned long columns, const unsigned long rows,
 *                   ExceptionInfo *exception)
 */

CAMLprim value
imper_get_raw_alpha( value image_bloc )
{
    CAMLparam1( image_bloc );
    CAMLlocal3( pixel_matrix, column_array, color_tuple );
    unsigned long x, y;
    unsigned long columns, rows;

    ExceptionInfo
        *exception;

    PixelPacket
        pixel;

    columns = ((Image *) Field(image_bloc,1))->columns;
    rows    = ((Image *) Field(image_bloc,1))->rows;

    exception = AcquireExceptionInfo();

    const PixelPacket * pixel_packet_array;

    /* DEPR
    pixel_packet_array =
            AcquireImagePixels(
                     (Image *) Field(image_bloc,1),
                     0, 0,
                     columns, rows,
                     exception );
    */

    pixel_packet_array =
            GetVirtualPixels(
                     (Image *) Field(image_bloc,1),
                     0, 0,
                     columns, rows,
                     exception );

    if (exception->severity != UndefinedException)
    {
        caml_failwith( exception->reason );
    }
    DestroyExceptionInfo(exception);

    /* alloc_array(f, a) allocates an array of values, calling function f
     * over each element of the input array a to transform it into a value.
     * The array a is an array of pointers terminated by the null pointer.
     * The function f receives each pointer as argument, and returns a value.
     * The zero-tagged block returned by alloc_array(f, a) is filled with the values
     * returned by the successive calls to f.
     * (This function must not be used to build an array of floating-point numbers.)
     */
    /*
    PixelPacket init_columns[columns];
    PixelPacket init_rows[rows];

    pixel_matrix = alloc_array(fill_raw, init_columns);
    column_array = alloc_array(fill_raw, init_rows);
    */

    pixel_matrix = caml_alloc_tuple(columns);

    for (x=0; x < columns; ++x) {

        column_array = caml_alloc_tuple(rows);

        for (y=0; y < rows; ++y) {

            pixel = pixel_packet_array[(columns * y) + x];

            color_tuple  = caml_alloc_tuple(4);

            Store_field(color_tuple, 0, Val_long( (long) pixel.red ));
            Store_field(color_tuple, 1, Val_long( (long) pixel.green ));
            Store_field(color_tuple, 2, Val_long( (long) pixel.blue ));
            Store_field(color_tuple, 3, Val_long( (long) pixel.alpha ));

            Store_field(column_array, y, color_tuple);
        }
        Store_field(pixel_matrix, x, column_array);
    }

    CAMLreturn( pixel_matrix );
}

/* }}} */
/* {{{ imper_get_raw_without_alpha() 
 *
 * const PixelPacket *AcquireImagePixels(const Image *image,
 *                   const long x, const long y,
 *                   const unsigned long columns, const unsigned long rows,
 *                   ExceptionInfo *exception)
 */

CAMLprim value
imper_get_raw_without_alpha( value image_bloc )
{
    CAMLparam1( image_bloc );
    CAMLlocal3( pixel_matrix, column_array, color_tuple );
    unsigned long x, y;
    unsigned long columns, rows;

    ExceptionInfo
        *exception;

    PixelPacket
        pixel;

    columns = ((Image *) Field(image_bloc,1))->columns;
    rows    = ((Image *) Field(image_bloc,1))->rows;

    exception = AcquireExceptionInfo();

    const PixelPacket * pixel_packet_array;

    /* DEPR
    pixel_packet_array =
            AcquireImagePixels(
                     (Image *) Field(image_bloc,1),
                     0, 0,
                     columns, rows,
                     exception );
    */

    pixel_packet_array =
            GetVirtualPixels(
                     (Image *) Field(image_bloc,1),
                     0, 0,
                     columns, rows,
                     exception );

    if (exception->severity != UndefinedException)
    {
        caml_failwith( exception->reason );
    }
    DestroyExceptionInfo(exception);

    /* alloc_array(f, a) allocates an array of values, calling function f
     * over each element of the input array a to transform it into a value.
     * The array a is an array of pointers terminated by the null pointer.
     * The function f receives each pointer as argument, and returns a value.
     * The zero-tagged block returned by alloc_array(f, a) is filled with the values
     * returned by the successive calls to f.
     * (This function must not be used to build an array of floating-point numbers.)
     */
    /*
    PixelPacket init_columns[columns];
    PixelPacket init_rows[rows];

    pixel_matrix = alloc_array(fill_raw, init_columns);
    column_array = alloc_array(fill_raw, init_rows);
    */

    pixel_matrix = caml_alloc_tuple(columns);

    for (x=0; x < columns; ++x) {

        column_array = caml_alloc_tuple(rows);

        for (y=0; y < rows; ++y) {

            pixel = pixel_packet_array[(columns * y) + x];

            color_tuple  = caml_alloc_tuple(3);

            Store_field(color_tuple, 0, Val_long( (long) pixel.red ));
            Store_field(color_tuple, 1, Val_long( (long) pixel.green ));
            Store_field(color_tuple, 2, Val_long( (long) pixel.blue ));

            Store_field(column_array, y, color_tuple);
        }
        Store_field(pixel_matrix, x, column_array);
    }

    CAMLreturn( pixel_matrix );
}

/* }}} */
/* {{{ imper_get_raw2() 
 *
 * PixelPacket AcquireOnePixel(const Image image,
 *                   const long x, const long y,
 *                   ExceptionInfo exception)
 */

CAMLprim value
imper_get_raw2( value image_bloc )
{
    CAMLparam1( image_bloc );
    CAMLlocal3( pixel_matrix, column_array, color_tuple );
    unsigned long x, y;
    unsigned long width, height;

    ExceptionInfo
        *exception;

    PixelPacket
        pixel;

    width  = ((Image *) Field(image_bloc,1))->columns;
    height = ((Image *) Field(image_bloc,1))->rows;

    exception = AcquireExceptionInfo();

    /* alloc_array(f, a) allocates an array of values, calling function f
     * over each element of the input array a to transform it into a value.
     * The array a is an array of pointers terminated by the null pointer.
     * The function f receives each pointer as argument, and returns a value.
     * The zero-tagged block returned by alloc_array(f, a) is filled with the values
     * returned by the successive calls to f.
     * (This function must not be used to build an array of floating-point numbers.)
     */
    /*
    PixelPacket init_width[width];
    PixelPacket init_height[height];
    pixel_matrix = alloc_array(fill_raw, init_width);
    column_array = alloc_array(fill_raw, init_height);
    */

    pixel_matrix = caml_alloc_tuple(width);
    /*
    pixel_matrix = alloc(width, 0);
    */

    for (x=0; x < width; ++x) {

        column_array = caml_alloc_tuple(height);
        /*
        column_array = alloc(height,0);
        */

        for (y=0; y < height; ++y) {

            /* DEPR
            pixel = AcquireOnePixel(
                            (Image *) Field(image_bloc,1),
                            x, y, exception );
            */

            GetOneVirtualPixel(
                            (Image *) Field(image_bloc,1),
                            Long_val(x),
                            Long_val(y),
                            &pixel,
                            exception );

            if (exception->severity != UndefinedException)
            {
                caml_failwith( exception->reason );
            }

            color_tuple  = caml_alloc_tuple(4);

            Store_field(color_tuple, 0, Val_long( (long) pixel.red ));
            Store_field(color_tuple, 1, Val_long( (long) pixel.green ));
            Store_field(color_tuple, 2, Val_long( (long) pixel.blue ));
            Store_field(color_tuple, 3, Val_long( MaxMap -
                                                  (long) pixel.alpha ));

            Store_field(column_array, y, color_tuple);
        }
        Store_field(pixel_matrix, x, column_array);
    }
    DestroyExceptionInfo(exception);

    CAMLreturn( pixel_matrix );
}

/* }}} */


/* {{{ imper_get_raw_gl_indexed() 
 *
 * const PixelPacket *AcquireImagePixels(const Image *image,
 *                   const long x, const long y,
 *                   const unsigned long columns, const unsigned long rows,
 *                   ExceptionInfo *exception)
 */

CAMLprim value
imper_get_raw_gl_indexed( value image_bloc )
{
    CAMLparam1( image_bloc );
    CAMLlocal3( pixel_matrix, column_array, color_tuple );
    unsigned long x, y;
    unsigned long columns, rows;

    ExceptionInfo
        exception;

    PixelPacket
        pixel;

    columns = ((Image *) Field(image_bloc,1))->columns;
    rows    = ((Image *) Field(image_bloc,1))->rows;

    GetExceptionInfo(&exception);

    const PixelPacket * pixel_packet_array;

    /* DEPR
    pixel_packet_array =
            AcquireImagePixels(
                     (Image *) Field(image_bloc,1),
                     0, 0,
                     columns, rows,
                     &exception );
    */

    pixel_packet_array =
            GetVirtualPixels(
                     (Image *) Field(image_bloc,1),
                     0, 0,
                     columns, rows,
                     &exception );
   
    if (exception.severity != UndefinedException)
    {
        caml_failwith( exception.reason );
    }
    DestroyExceptionInfo(&exception);

    /* alloc_array(f, a) allocates an array of values, calling function f
     * over each element of the input array a to transform it into a value.
     * The array a is an array of pointers terminated by the null pointer.
     * The function f receives each pointer as argument, and returns a value.
     * The zero-tagged block returned by alloc_array(f, a) is filled with the values
     * returned by the successive calls to f.
     * (This function must not be used to build an array of floating-point numbers.)
     */
    /*
    PixelPacket init_columns[columns];
    PixelPacket init_rows[rows];

    pixel_matrix = alloc_array(fill_raw, init_columns);
    column_array = alloc_array(fill_raw, init_rows);
    */

    pixel_matrix = caml_alloc_tuple(columns * rows);

    for (x=0; x < columns; ++x) {

        for (y=0; y < rows; ++y) {

            pixel = pixel_packet_array[(columns * y) + x];

            color_tuple  = caml_alloc_tuple(4);

            Store_field(color_tuple, 0, Val_long( (long) pixel.red ));
            Store_field(color_tuple, 1, Val_long( (long) pixel.green ));
            Store_field(color_tuple, 2, Val_long( (long) pixel.blue ));
            Store_field(color_tuple, 3, Val_long( MaxMap -
                                                  (long) pixel.alpha ));

            Store_field(pixel_matrix, (x * rows) + y, color_tuple);
        }
    }

    CAMLreturn( pixel_matrix );
}

/* }}} */
/* {{{ imper_get_raw_gl_indexed_without_alpha() 
 *
 * const PixelPacket *AcquireImagePixels(const Image *image,
 *                   const long x, const long y,
 *                   const unsigned long columns, const unsigned long rows,
 *                   ExceptionInfo *exception)
 */

CAMLprim value
imper_get_raw_gl_indexed_without_alpha( value image_bloc )
{
    CAMLparam1( image_bloc );
    CAMLlocal3( pixel_matrix, column_array, color_tuple );
    unsigned long x, y;
    unsigned long columns, rows;

    ExceptionInfo
        exception;

    PixelPacket
        pixel;

    columns = ((Image *) Field(image_bloc,1))->columns;
    rows    = ((Image *) Field(image_bloc,1))->rows;

    GetExceptionInfo(&exception);

    const PixelPacket * pixel_packet_array;

    /* DEPR
    pixel_packet_array =
            AcquireImagePixels(
                     (Image *) Field(image_bloc,1),
                     0, 0,
                     columns, rows,
                     &exception );
    */

    pixel_packet_array =
            GetVirtualPixels(
                     (Image *) Field(image_bloc,1),
                     0, 0,
                     columns, rows,
                     &exception );

    if (exception.severity != UndefinedException)
    {
        caml_failwith( exception.reason );
    }
    DestroyExceptionInfo(&exception);

    /* alloc_array(f, a) allocates an array of values, calling function f
     * over each element of the input array a to transform it into a value.
     * The array a is an array of pointers terminated by the null pointer.
     * The function f receives each pointer as argument, and returns a value.
     * The zero-tagged block returned by alloc_array(f, a) is filled with the values
     * returned by the successive calls to f.
     * (This function must not be used to build an array of floating-point numbers.)
     */
    /*
    PixelPacket init_columns[columns];
    PixelPacket init_rows[rows];

    pixel_matrix = alloc_array(fill_raw, init_columns);
    column_array = alloc_array(fill_raw, init_rows);
    */

    pixel_matrix = caml_alloc_tuple(columns * rows);

    for (x=0; x < columns; ++x) {

        for (y=0; y < rows; ++y) {

            pixel = pixel_packet_array[(columns * y) + x];

            color_tuple  = caml_alloc_tuple(3);

            Store_field(color_tuple, 0, Val_long( (long) pixel.red ));
            Store_field(color_tuple, 1, Val_long( (long) pixel.green ));
            Store_field(color_tuple, 2, Val_long( (long) pixel.blue ));

            Store_field(pixel_matrix, (x * rows) + y, color_tuple);
        }
    }

    CAMLreturn( pixel_matrix );
}

/* }}} */


/* Does not work! */
/* {{{ set_pixel() 
 *
 * (DrawInfo *)->primitive = "point x,y"
 */
void
set_pixel(
        Image *image,
        unsigned long x,
        unsigned long y,
        PixelInfo pixel )
{
    MagickBooleanType
        ret;

    ImageInfo
        *image_info;

    DrawInfo
        *draw_info;

    image_info = CloneImageInfo((ImageInfo *) NULL);

    draw_info = CloneDrawInfo( image_info, ( DrawInfo* )NULL );
    DestroyImageInfo(image_info);

    if ( !draw_info ) {
#if DEBUG
        fprintf(stderr, "CloneDrawInfo() failed\n"); fflush(stderr);
#endif
        caml_failwith("set_raw failed");
    }

    draw_info->fill = pixel;

    char str_buffer[ MaxTextExtent ];
    int str_len;

    /* Feed the primitive "point X,Y" */
    str_len = snprintf( str_buffer, MaxTextExtent, "point %ld,%ld", Long_val(x), Long_val(y) );
    (void) CloneString(&draw_info->primitive, str_buffer);

    ExceptionInfo *excinfo = AcquireExceptionInfo();
    ret = DrawImage(image, draw_info, excinfo);
    excinfo = DestroyExceptionInfo(excinfo);

    if (ret == MagickFalse) {
#if DEBUG
        fprintf(stderr, "DrawImage() failed\n"); fflush(stderr);
#endif
        caml_failwith("set_raw failed");
    }

    /* @FIXME: draw_info should be freed
     * but this line produce a Segmentation fault
     * DestroyDrawInfo(draw_info);
     */
}
/* }}} */
/* {{{ imper_set_raw_c() 
 *
 * PixelPacket *SetImagePixels(Image *image, const long x, const long y,
 *                   const unsigned long columns, const unsigned long rows);
 */
CAMLprim value
imper_set_raw_c(
        value raw,
        value width,
        value height )
{
    CAMLparam3( raw, width, height );
    CAMLlocal3( column_array, color_tuple, image_bloc );

    const unsigned long columns = Long_val(width);
    const unsigned long rows    = Long_val(height);

    /* {{{ new_image */
    {
        char
            str_buffer[ MaxTextExtent ];

        int str_len;

        ExceptionInfo
            exception;

        ImageInfo
            *image_info;

        image_info = CloneImageInfo((ImageInfo *) NULL);

        /* image size */
        str_len = snprintf(str_buffer, MaxTextExtent, "%ldx%ld", columns, rows);
        (void) CloneString(&image_info->size, str_buffer);

        /* image color */
        strcpy( image_info->filename, "xc:#7F7F7F7F");

        image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

        Field(image_bloc,1) = (value) alloc_image();  /* alloc_image() */

        if (IsMagickInstantiated() == MagickFalse) {
            MagickCoreGenesis(getenv("PWD"), MagickTrue);
        }

        GetExceptionInfo(&exception);

        Field(image_bloc,1) = (value) ReadImage(image_info, &exception);
        DestroyImageInfo(image_info);

        if (exception.severity != UndefinedException) {

            caml_failwith( exception.reason );
        }

        DestroyExceptionInfo(&exception);

        if ((Image *) Field(image_bloc,1) == (Image *) NULL) {
            /* exit(1) ; */
            caml_failwith("set_raw failed");
        }
    }
    /* }}} */

    /*
    PixelPacket
        *pixel_array;

    pilxel_array = SetImagePixels(Field(image_bloc,1), 0, 0, columns, rows);

    if (pixel_array == (PixelPacket *)NULL) {
        caml_failwith("set_raw failed") ;
    }
    */

    unsigned long x, y;

    PixelInfo
        pixel;

    /*
    printf("  sizeof(pixel_array[0]) = %d\n", sizeof(pixel_array[0]));
    printf("  PixelPacket = %d\n", sizeof(PixelPacket));
    */

    for (x=0; x < columns; x++) {

        column_array = Field(raw, x);

        for (y=0; y < rows; y++) {

            color_tuple = Field(column_array, y);

            pixel.red     = Field(color_tuple, 0);
            pixel.green   = Field(color_tuple, 0);
            pixel.blue    = Field(color_tuple, 0);
            pixel.alpha = Field(color_tuple, 0);  /* o = max - a */

            /*
            printf("ImageMagick: recording pixel y=%d into array", y); fflush(stdout);
            pixel_array[x * columns + y] = pixel;
            printf(" OK\n"); fflush(stdout);
            */
            set_pixel( (Image *) Field(image_bloc,1), x, y, pixel);
        }
        printf("."); fflush(stdout);
    }
    printf("\n"); fflush(stdout);

#if 0
    /* {{{ SyncImagePixels() 
     *
     * MagickBooleanType SyncImagePixels(Image *image);
     */
    {
        MagickBooleanType
            ret;

        ret = SyncImagePixels(Field(image_bloc,1));

        if (ret == MagickFalse) {
#if DEBUG
            printf("ImageMagick: SyncImagePixels() failed\n"); fflush(stdout);
#endif
            caml_failwith("set_raw failed");
        }
    }
    /* }}} */
    printf("ImageMagick: After Sync!\n"); fflush(stdout);
#endif

    CAMLreturn( image_bloc );
}
/* }}} */

/* }}} */


/* {{{ @TODO: IMAGE LISTS   
 *
 * MagickBooleanType AnimateImages(const ImageInfo *, Image *);
 * Image *AppendImages(const Image *, const MagickBooleanType,ExceptionInfo *);
 * Image *AverageImages(const Image *, ExceptionInfo *);
 *
 * in <magick/list.h>
 *
 * }}} */
/* TODO: the images added in a list are not clones, these are pointers.
 * So if images are freed by the GC, there will be problems.
 * (A solution could be to add a field to the image_bloc which says if the image
 * is part of an image_list or not, and keep track of when the image or the list
 * have been reclaimed by the GC.)
 */
/* {{{ ====  IMAGE LISTS  ==== */

/* {{{ imper_new_image_list() 
 *
 * Image *NewImageList(void);
 */
CAMLprim value
imper_new_image_list(value unit)
{
    CAMLparam1(unit);

    CAMLlocal1(images_list_bloc);


    images_list_bloc = caml_alloc_final(2, finalize_images_list, sizeof(Image), MAX_AMOUNT); /* finalize_image() */

    if (IsMagickInstantiated() == MagickFalse) {
        MagickCoreGenesis(getenv("PWD"), MagickTrue);
    }

    Field(images_list_bloc,1) = (value) NewImageList();
    /*
    Field(images_list_bloc,1) = NewImageList();
    */


    if ((Image *) &Field(images_list_bloc,1) == (Image *) NULL) {
        /* exit(1) ; */
        caml_failwith("new_images_list failed");
    }

    CAMLreturn (images_list_bloc);
}
/* }}} */
/* {{{ imper_appendimagetolist() 
 *
 * AppendImageToList(Image *images, const Image *image);
 */
CAMLprim value
imper_appendimagetolist(
        value images_list_bloc,
        value image_bloc,
        value delay )
{
    CAMLparam3( images_list_bloc, image_bloc, delay );

    Image *img;

    img = (Image *) Field(image_bloc,1);
    img->delay = (unsigned long) Long_val(delay);


    AppendImageToList(
                (Image **) &Field(images_list_bloc,1),
                (Image *)  Field(image_bloc,1) );


    CAMLreturn( Val_unit );
}
/* }}} */
/* {{{ imper_getimagelistlength() 
 *
 * unsigned long GetImageListLength(const Image *images);
 */
CAMLprim value
imper_getimagelistlength(
        value images_list_bloc )
{
    CAMLparam1( images_list_bloc );

    CAMLreturn( Val_long(
            GetImageListLength( (Image *) Field(images_list_bloc,1) )
            ));
}
/* }}} */
/* {{{ imper_animateimages() 
 *
 * MagickBooleanType AnimateImages(const ImageInfo *image_info, Image *images);
 */
CAMLprim value
imper_animateimages(
        value images_list_bloc )
{
    CAMLparam1( images_list_bloc );

    ImageInfo
        *image_info;

    MagickBooleanType
        ret;

    image_info = CloneImageInfo((ImageInfo *) NULL);


    ExceptionInfo *excinfo = AcquireExceptionInfo();
    ret = AnimateImages(image_info, (Image *) Field(images_list_bloc,1), excinfo);
    excinfo = DestroyExceptionInfo(excinfo);


    if (ret == MagickFalse) {
        caml_failwith("animate_images failed");
    }
    DestroyImageInfo(image_info);

    CAMLreturn( Val_unit );
}
/* }}} */

/* {{{ imper_getlastimageinlist() 
 *
 * Image *GetLastImageInList(const Image *images);
 */
CAMLprim value
imper_getlastimageinlist(
        value images_list_bloc )
{
    CAMLparam1( images_list_bloc );

    CAMLlocal1( image_bloc );


    Field(image_bloc,1) = (value) GetLastImageInList( (Image *) &Field(images_list_bloc,1) );


    CAMLreturn( image_bloc );
}
/* }}} */
/* {{{ imper_getfirstimageinlist() 
 *
 * Image *GetFirstImageInList(const Image *images);
 */
CAMLprim value
imper_getfirstimageinlist(
        value images_list_bloc )
{
    CAMLparam1( images_list_bloc );

    CAMLlocal1( image_bloc );


    Field(image_bloc,1) = (value) GetFirstImageInList( (Image *) &Field(images_list_bloc,1) );


    CAMLreturn( image_bloc );
}
/* }}} */


/* TEMP */
/* Just a work-around to prevent an image in an image_list
   to be garbage collected */
/* {{{ imper_no_op() */
CAMLprim value
imper_no_op(value image_bloc)
{
    CAMLparam1( image_bloc );
    Image *image;

    image = (Image *) Field(image_bloc,1);

    CAMLreturn( Val_unit );
}
/* }}} */

/* {{{ imper_has_link() */

/* {{{ int has_link(Image *img) */

/* {{{ int has_link(Image *img) OLD */
#if 0
int has_link(Image *img)
{
/*  struct _Image
      *previous,
      *list,
      *next   */

    if ( img->previous == (Image *) NULL
      && img->next     == (Image *) NULL
      && img->list     == (Image *) NULL )
    {
        return 0;
    } else {
        return 1;
    }
}
#endif
/* }}} */

int has_link(Image *img)
{
/*  struct _Image
      *previous,
      *list,
      *next   */

    if ( img->previous != (Image *) NULL )
    {
        return 1;
    }

    if ( img->next != (Image *) NULL )
    {
        return 2;
    }

    if ( img->list != (Image *) NULL )
    {
        return 3;
    }

    return 0;
}
/* }}} */

CAMLprim value
imper_has_link( value image_bloc )
{
    CAMLparam1(image_bloc);
    Image *img;

    img = (Image *) Field(image_bloc,1);

    switch ( has_link(img) )
    {
        case 0:
#if DEBUG
            printf("ImageMagick.has_link: image doesn't have any link to other image\n"); fflush(stdout);
#endif
            CAMLreturn( Val_false );
            break;
        case 1:
#if DEBUG
            printf("ImageMagick.has_link: image has previous\n"); fflush(stdout);
#endif
            CAMLreturn( Val_true );
            break;
        case 2:
#if DEBUG
            printf("ImageMagick.has_link: image has next\n"); fflush(stdout);
#endif
            CAMLreturn( Val_true );
            break;
        case 3:
#if DEBUG
            printf("ImageMagick.has_link: image has list\n"); fflush(stdout);
#endif
            CAMLreturn( Val_true );
            break;
        default:
            caml_failwith("has_link failed");
    }
}
/* }}} */

#define CAML_ALLOC_WITH_0_SIZE 1

/* {{{ imper_appendimages()
 *
 * Image *AppendImages(const Image *image,const MagickBooleanType stack, ExceptionInfo *exception);
 */
CAMLprim value
__imper_appendimages(
        value image_list_bloc,
        value ml_stack )
{
    CAMLparam2(image_list_bloc, ml_stack );

    CAMLlocal1(image_bloc);

    Image *new_image;

    ExceptionInfo *exception;

    MagickBooleanType stack;
    stack = MagickBoolean_val( ml_stack );

    exception = AcquireExceptionInfo();

    image_bloc = caml_alloc_final(2, (*finalize_image), sizeof(Image), MAX_AMOUNT);  /* finalize_image() */
#if CAML_ALLOC_WITH_0_SIZE
#endif

    new_image = AppendImages(
            (Image *) Field(image_list_bloc,1),
            stack,
            exception );

    if (exception->severity != UndefinedException)
    {   if ( new_image )
        {
            DestroyImage( new_image );
        }
        caml_failwith( exception->reason );
    }

    Field(image_bloc,1) = (value) new_image;

    DestroyExceptionInfo(exception);

    CAMLreturn( Val_unit );
}

/* }}} */
/* {{{ imper_appendimages()
 *
 * Image *AppendImages(const Image *image,const MagickBooleanType stack, ExceptionInfo *exception);
 */
CAMLprim value
imper_appendimages(
        value image_list_bloc,
        value ml_stack,
        value image_bloc )
{
    CAMLparam3( image_list_bloc, ml_stack, image_bloc );

    Image *new_image;

    ExceptionInfo *exception;

    exception = AcquireExceptionInfo();

    MagickBooleanType stack;
    stack = MagickBoolean_val( ml_stack );

    new_image = AppendImages(
            (Image *) Field(image_list_bloc,1),
            stack,
            exception );

    if (exception->severity != UndefinedException)
    {
        if ( new_image )
        {
            DestroyImage( new_image );
        }

        caml_failwith( exception->reason );
    }

    DestroyImage( (Image *) Field(image_bloc,1) );
    Field(image_bloc,1) = (value) new_image;

    DestroyExceptionInfo(exception);

    CAMLreturn( Val_unit );
}

/* }}} */

/* }}} */


/* {{{ ====  BLOBS  ==== */

/*
 * extern MagickExport unsigned char
 *   *FileToBlob(const char *, const size_t,size_t *, ExceptionInfo *),
 *   *GetBlobStreamData(const Image *),
 *   *ImageToBlob(const ImageInfo *, Image *, size_t *, ExceptionInfo *),
 *   *ImagesToBlob(const ImageInfo *, Image *, size_t *, ExceptionInfo *);
 */

/* {{{ imper_imagetoblob_stdout() 
 *
 * unsigned char *ImageToBlob(const ImageInfo *image_info, Image *image,
 *                     size_t *length, ExceptionInfo *exception)
 */
CAMLprim value
imper_imagetoblob_stdout(value image_bloc)
{
    CAMLparam1( image_bloc );

    ImageInfo
        *image_info;

    ExceptionInfo
        exception;

    char*
        mime_type;

    unsigned char *blob_data;  /* the image BLOB data */
    size_t blob_size;          /* the size of the image BLOB */

    GetExceptionInfo(&exception);
    image_info = CloneImageInfo((ImageInfo *) NULL) ;

    blob_data = ImageToBlob(
                    image_info,
                    (Image *) Field(image_bloc,1),
                    &blob_size,
                    &exception );

    /*
    printf("%s", blob_data ); fflush(stdout);
    fputs(blob_data, stdout); fflush(stdout);
    */

    /*
    unsigned long i;
    for (i=0; i < blob_size; i++) {
        //(void) fputc(blob_data[i], stdout);
        (void) putc(blob_data[i], stdout);
    }
    fflush(stdout);
    */
    if (exception.severity != UndefinedException) {

        caml_failwith( exception.reason );
    }

    mime_type = MagickToMime(
                      ((Image *) Field(image_bloc,1))->magick );

    printf("Content-Type: %s\n"
           "Content-Length: %d\n"
           "\n", mime_type, blob_size);
    /*
    fwrite(blob_data, 1, blob_size, stdout);
    */
    fwrite(blob_data, blob_size, 1, stdout);

    DestroyImageInfo(image_info);
    DestroyExceptionInfo(&exception);

    CAMLreturn( Val_unit );
}
/* }}} */
/* {{{ imper_imagetoblob_bytes() 
 *
 * unsigned char *ImageToBlob(const ImageInfo *image_info, Image *image,
 *                     size_t *length, ExceptionInfo *exception)
 */
CAMLprim value
imper_imagetoblob_bytes(value image_bloc)
{
    CAMLparam1( image_bloc );
    CAMLlocal1( byte_array );

    ImageInfo
        *image_info;

    ExceptionInfo
        exception;

    unsigned char *blob_data;  /* the image BLOB data */
    size_t blob_size;         /* the size of the image BLOB */

    GetExceptionInfo(&exception);
    image_info = CloneImageInfo((ImageInfo *) NULL) ;

    blob_data = ImageToBlob(
                    image_info,
                    (Image *) Field(image_bloc,1),
                    &blob_size,
                    &exception );

    if (exception.severity != UndefinedException) {

        caml_failwith( exception.reason );
    }
    DestroyImageInfo(image_info);
    DestroyExceptionInfo(&exception);


    byte_array = caml_alloc_tuple(blob_size);

    unsigned long blob_len;

    puts(" A"); fflush(stdout);
    blob_len = blob_size;
    puts(" B"); fflush(stdout);
    printf(" blob-size = '%lu'\n", blob_len); fflush(stdout);
    puts(" C"); fflush(stdout);

    unsigned long i;
    for (i=0; i < blob_len; i++) {
        printf("."); fflush(stdout);
        Store_field(byte_array, i, Val_int((unsigned int) blob_data[i]));
    }
    puts("\n D"); fflush(stdout);

    CAMLreturn( byte_array );
}
/* }}} */

/* }}} */

/* {{{ ====  IMPORT  ==== */

/*
typedef struct _XImportInfo
{
  MagickBooleanType
    frame,
    borders,
    screen,
    descend,
    silent;
} XImportInfo;

extern MagickExport Image
  *XImportImage(const ImageInfo *,XImportInfo *);

extern MagickExport void
  XGetImportInfo(XImportInfo *);
 */

/* {{{ imper_importimage() 
 *
 * Image *XImportImage(const ImageInfo *, XImportInfo *);
 */
CAMLprim value
imper_importimage(value width, value height, value color)
{
    CAMLparam3(width, height, color);

    CAMLlocal1(image_bloc);

    char
        str_buffer[ MaxTextExtent ];

    int str_len;

    ExceptionInfo
        *exception;

    ImageInfo
        *image_info;


    image_info = CloneImageInfo((ImageInfo *) NULL);

    /* Give image size */
    str_len = snprintf( str_buffer, MaxTextExtent, "%ldx%ld", Long_val(width), Long_val(height) );
    (void) CloneString(&image_info->size, str_buffer);

    /* Give image color */
    str_len = snprintf( str_buffer, MaxTextExtent, "xc:%s", String_val(color) );
    strncpy( image_info->filename, str_buffer, str_len );


    image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    Field(image_bloc,1) = (value) alloc_image();  /* alloc_image() */


    if (IsMagickInstantiated() == MagickFalse) {
        MagickCoreGenesis(getenv("PWD"), MagickTrue);
    }

    exception = AcquireExceptionInfo();

    Field(image_bloc,1) = (value) ReadImage(image_info, exception);
    DestroyImageInfo(image_info);

    /****************/

    /* {  MagickBooleanType
            frame,
            borders,
            screen,
            descend,
            silent;
       }  XImportInfo;  */
    XImportInfo
        *import_info;
    import_info = (XImportInfo *)NULL;

    ExceptionInfo *excinfo = AcquireExceptionInfo();
    Field(image_bloc,1) = (value) XImportImage(image_info, import_info, excinfo);
    excinfo = DestroyExceptionInfo(excinfo);

    /****************/

    if (exception->severity != UndefinedException) {

        caml_failwith( exception->reason );
    }

    DestroyExceptionInfo(exception);

    if ((Image *) Field(image_bloc,1) == (Image *) NULL) {
        /* exit(1) ; */
        caml_failwith("import failed");
    }

    CAMLreturn (image_bloc);
}
/* }}} */

/* }}} */


/* {{{ ====  BIG-ARRAY  ==== */


/* {{{ im_sizeof_quantum() */

CAMLprim value
im_sizeof_quantum(value unit)
{
    CAMLparam0();
    CAMLreturn( Val_int(sizeof(Quantum)) );
}

CAMLprim value
im_sizeof_quantum_bit(value unit)
{
    CAMLparam0();
    CAMLreturn( Val_int(sizeof(Quantum) * CHAR_BIT) );
}

/* }}} */

/* {{{ inspect BigArray */

CAMLprim value
ml_big_array_test(value v)
{
    CAMLparam1( v );

    /* number of dimensions should be 2 */
    if (Caml_ba_array_val(v)->num_dims != 2) {
        caml_failwith("the Bigarray should have 2 dimensions");
    }

    /* kind of array elements */
    printf(" Bigarray kind: ");
    switch (Caml_ba_array_val(v)->flags & CAML_BA_KIND_MASK)
    /* {{{ cases: */
    {
        case CAML_BA_FLOAT32:    printf(" FLOAT32:    Single-precision floats \n"); break;
        case CAML_BA_FLOAT64:    printf(" FLOAT64:    Double-precision floats \n"); break;
        case CAML_BA_SINT8:      printf(" SINT8:      Signed 8-bit integers   \n"); break;
        case CAML_BA_UINT8:      printf(" UINT8:      Unsigned 8-bit integers \n"); break;
        case CAML_BA_SINT16:     printf(" SINT16:     Signed 16-bit integers  \n"); break;
        case CAML_BA_UINT16:     printf(" UINT16:     Unsigned 16-bit integers\n"); break;
        case CAML_BA_INT32:      printf(" INT32:      Signed 32-bit integers  \n"); break;
        case CAML_BA_INT64:      printf(" INT64:      Signed 64-bit integers  \n"); break;
        case CAML_BA_CAML_INT:   printf(" CAML_INT:   Caml-style integers (signed 31 or 63 bits)   \n"); break;
        case CAML_BA_NATIVE_INT: printf(" NATIVE_INT: Platform-native long integers (32 or 64 bits)\n"); break;
        case CAML_BA_COMPLEX32:  printf(" COMPLEX32:  Single-precision complex\n"); break;
        case CAML_BA_COMPLEX64:  printf(" COMPLEX64:  Double-precision complex\n"); break;
    }
    /* }}} */

    unsigned long X_ = (unsigned long) Caml_ba_array_val(v)->dim[0];
    unsigned long Y_ = (unsigned long) Caml_ba_array_val(v)->dim[1];
    Quantum *arr;
    arr = Caml_ba_data_val(v);

    printf("    sizeof array   %d bytes, %d bits\n",
                    sizeof(arr[0]),
                    sizeof(arr[0]) * CHAR_BIT);
    printf("    sizeof Quantum %d bytes, %d bits  (char %d bits)\n",
                    sizeof(Quantum),
                    sizeof(Quantum) * CHAR_BIT,  CHAR_BIT);

    unsigned long x, y;
    for (x=0; x < X_; x++) {
        for (y=0; y < Y_; y++) {
            if(x==1 && y==3) arr[y+x*Y_] = 6;
            printf("  %lu,%lu", x, y );
            printf(":%3d", (Quantum) arr[y+x*Y_] );
            //printf(":%d", *arr );
            //arr++;
        }
        printf("\n");
    }

    fflush(stdout);

    CAMLreturn( Val_unit );
}
/* }}} */

/* {{{ constituteimage_from_big_array_char() 
 *
 * image = ConstituteImage(640, 480, "RGB", CharPixel, pixels, exception);
 *
 * Image *ConstituteImage(
 *             const unsigned long columns,
 *             const unsigned long rows,
 *             const char *map,
 *             const StorageType storage,
 *             const void *pixels,
 *             ExceptionInfo *exception );
 */
CAMLprim value
constituteimage_from_big_array_char(value array)
{
    CAMLparam1( array );
    CAMLlocal1( image_bloc );
    ExceptionInfo *exception;

    if ( (Caml_ba_array_val(array)->flags & CAML_BA_KIND_MASK) != CAML_BA_UINT8) {
        caml_failwith("The bigarray should contain unsigned 8-bit integers");
    }
    if (Caml_ba_array_val(array)->num_dims != 3) {
        caml_failwith("the Bigarray should have 3 dimensions");
    }
    unsigned long width  = (unsigned long) Caml_ba_array_val(array)->dim[0];
    unsigned long height = (unsigned long) Caml_ba_array_val(array)->dim[1];
    /*
    unsigned short cells = (unsigned short)Caml_ba_array_val(array)->dim[2];
    */

    //unsigned char *data;
    void *data;
    data = Caml_ba_data_val(array);

    if (IsMagickInstantiated() == MagickFalse) {
        MagickCoreGenesis(getenv("PWD"), MagickTrue);
    }

    image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    /*
    unsigned char *pixels;
    pixels = malloc(width * height * sizeof(char) * cells);
    unsigned long x, y;
    unsigned short p;
    unsigned long long k=0;
    for (x=0; x < width; x++)
        for (y=0; y < height; y++)
            for (p=0; p < cells; p++) { pixels[k] = *data; data++; k++; }

    exception = AcquireExceptionInfo();
    Field(image_bloc,1) =
        (value) ConstituteImage(width, height, "RGB", CharPixel, pixels, exception);
    free(pixels);
    */

    char map[] = "RGB";

    /* TODO
    assert( strlen(map) == cells );
    */

    exception = AcquireExceptionInfo();
    Field(image_bloc,1) =
        (value) ConstituteImage(width, height, map, CharPixel, data, exception);


    if (exception->severity != UndefinedException) {
        if ( (Image *)Field(image_bloc,1) != (Image *) NULL) {
            DestroyImage((Image *) Field(image_bloc,1));
        }
        caml_failwith( exception->reason );
    }
    exception = DestroyExceptionInfo(exception);

    if ( (Image *)Field(image_bloc,1) == (Image *) NULL) {
        caml_failwith("image_of_bigarray failed");
    }

    CAMLreturn( image_bloc );
}
/* }}} */

/* }}} */


/* {{{ ====  TMP: LINEAR GRADIENT  ==== */

#include <math.h>
#include <assert.h>

/* {{{ Mathematic utilities */

/* returns the length of the vector */
long double
vector_length(
    long long x,
    long long y)
{
  return sqrt((x*x) + (y*y));
}

/* returns the scalar product of 2 vectors */
long long
scalar_product(
    long long a_x,
    long long a_y,
    long long b_x,
    long long b_y)
{
  return (a_x * b_x) + (a_y * b_y);
}

/* returns the cosinus of the angle between the 2 vectors 'ab' and 'cd' */
long double
get_cos(
    long long ab_x,
    long long ab_y,
    long long cd_x,
    long long cd_y)
{
  long long _scal = scalar_product(ab_x,ab_y, cd_x,cd_y);
  long double _len = vector_length(ab_x,ab_y) * vector_length(cd_x,cd_y);
  return (long double)_scal / _len;
}

/* returns the vector (a - b) */
void
vector_substract(
    long long *result_x,
    long long *result_y,

    unsigned long a_x,
    unsigned long a_y,
    unsigned long b_x,
    unsigned long b_y)
{
  *result_x = (long long)a_x - (long long)b_x;
  *result_y = (long long)a_y - (long long)b_y;
}

/* returns the vector (a + b) */
void
vector_add(
    long *result_x,
    long *result_y,

    unsigned long a_x,
    unsigned long a_y,
    unsigned long b_x,
    unsigned long b_y)
{
  *result_x = a_x + b_x;
  *result_y = a_y + b_y;
}

/* returns the coordinate of 'c'
   in the 1D (one dimention) system defined by the vector 'ab'. */
long double
get_y_of_A_B(
    unsigned long a_x, unsigned long a_y,
    unsigned long b_x, unsigned long b_y,
    unsigned long c_x, unsigned long c_y)
{
  long long ab_x, ab_y;
  vector_substract(&ab_x,&ab_y, b_x,b_y, a_x,a_y);

  long long ac_x, ac_y;
  vector_substract(&ac_x,&ac_y, c_x,c_y, a_x,a_y);

  return vector_length(ac_x,ac_y) * get_cos(ab_x,ab_y, ac_x,ac_y);
}

/* multiply a vector by 'k' */
void
vector_multiply(
    unsigned long *result_x,
    unsigned long *result_y,
    long double k,
    unsigned long x,
    unsigned long y)
{
  *result_x = (unsigned long)(k * (long double)x);
  *result_y = (unsigned long)(k * (long double)y);
}

void
test_math_utilities(void)
{

  /* {{{ scalar_product() */
  if (
      scalar_product(50, 40, 150, 110) == 11900 &&
      scalar_product(10, 208, 448, 32) == 11136 &&
      scalar_product(1541, 2, 7, 3129) == 17045 )
  {
    printf(" scalar_product() is OK!\n");
  } else {
    printf(" scalar_product() is WRONG!\n");
  }
  /* }}} */
  /* {{{ vector_length() */
  if (
      vector_length(12, 16) == 20.0 &&
      vector_length(18, 24) == 30.0 &&
      (int)(vector_length(48, 231)) == 235 )
  {
    printf(" vector_length() is OK!\n");
  } else {
    printf(" vector_length() is WRONG!\n");
  }
  /* }}} */
  /* {{{ get_cos() */
  if (
      get_cos(1,0, 0,1) == 0.0 &&
      get_cos(1,0, 1,0) == 1.0 &&
      ((int)(10000.0 * get_cos(5,2, 7,9))) == 8631
     )
  {
    printf(" get_cos() is OK!\n");
  } else {
    printf(" get_cos() is WRONG!\n");
  }
  /* }}} */

}
/* }}} */

/* {{{ _set_pixel() */

#define _set_pixel(image, x, y, px_color) \
          draw_info->fill = px_color; \
          str_len=snprintf(str_buffer,MaxTextExtent,"point %lu,%lu", x,y); \
          (void) CloneString(&draw_info->primitive, str_buffer); \
          ExceptionInfo *excinfo = AcquireExceptionInfo(); \
          ret=DrawImage(image, draw_info, excinfo); \
          excinfo = DestroyExceptionInfo(excinfo); \
          if(ret==MagickFalse) fprintf(stderr, "DrawImage() failed\n");

/* }}} */

/*  en: http://www.w3.org/TR/SVG/pservers.html#LinearGradients  */
/*  fr: http://www.yoyodesign.org/doc/w3c/svg1/pservers.html#LinearGradients  */

/* {{{ proto and type */

typedef enum
{
  Pad_SpreadMethod,
  Repeat_SpreadMethod,
  Reflect_SpreadMethod
} Gradient_SpreadMethod;

/* {{{ SpreadMethod_val() */

static int
SpreadMethod_val( value param )
{
    CONVALparam1( param );

#if TYPE_CHECKING
    assert(Is_long( param ));
#endif

    switch (Int_val( param ))
      {
        case 0: return Pad_SpreadMethod;
        case 1: return Repeat_SpreadMethod;
        case 2: return Reflect_SpreadMethod;
        default:
#if DEBUG
            fprintf(stderr, "Error: Gradient SpreadMethod unrecognized\n"); fflush(stderr);
            abort();
            /*
            return -1;
            caml_failwith("Gradient SpreadMethod unrecognized");
            // caml_failwith() does not work in sub-functions
            */
#else
            fprintf(stderr, "Warning: Gradient SpreadMethod unrecognized\n"); fflush(stderr);
            return Pad_SpreadMethod;
#endif
      }
}

/* }}} */

typedef enum
{
  Gradient_UserSpaceOnUse,
  /* If gradientUnits="userSpaceOnUse", x1, y1, x2, y2 represent values 
   * in the coordinate system that results from taking the current user 
   * coordinate system in place at the time when the gradient element is 
   * referenced (i.e., the user coordinate system for the element 
   * referencing the gradient element via a 'fill' or 'stroke' property) 
   * and then applying the transform specified by attribute gradientTransform.
   */
  Gradient_ObjectBoundingBox
  /*   gradientUnits="objectBoundingBox"
   * Indicates that the attributes which specify the gradient vector (x1, y1, x2, y2)
   * represent fractions or percentages of the bounding box of the element to which the gradient is applied.
   */
} Gradient_Units;

typedef struct _BoundingBox
{
  unsigned long
    x, y,
    width, height;
} BoundingBox;

/* }}} */

/* }}} */


/*  vim:cindent sw=4 ts=4 sts=4 et fdm=marker
 */
