/* {{{ COPYING 
 *
 * +-----------------------------------------------------------------+
 * | Copyright (C) 2004 2005 2006 Florent Monnier                    |
 * +-----------------------------------------------------------------+
 * | This binding aims to provide the ImageMagick methods to OCaml.  |
 * +-----------------------------------------------------------------+
 * | This software is provided 'as-is', without any express or       |
 * | implied warranty.  In no event will the authors be held liable  |
 * | for any damages arising from the use of this software.          |
 * |                                                                 |
 * | Permission is granted to anyone to use this software for any    |
 * | purpose, including commercial applications, and to alter it and |
 * | redistribute it freely.                                         |
 * +-----------------------------------------------------------------+
 * | Author: Florent Monnier <monnier.florent (at) gmail.com>        |
 * | Thanks to Matthieu Dubuget for his help with OCamlMakefile use. |
 * +-----------------------------------------------------------------+
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

#include <MagickCore/MagickCore.h>


#include "imagemagick.h"


/* }}} */

#define GetExceptionInfo(v)

/* {{{ MagickBoolean_val() 
 *
 * typedef enum
 * {
 *   MagickFalse = 0,
 *   MagickTrue = 1
 * } MagickBooleanType;
 *
static int
 */
int
MagickBoolean_val(value param)
{
#if CAML_FRAME
    CAMLparam1(param);
#endif

#if TYPE_CHECKING
    assert (Is_long(param));
#endif

    switch (Int_val(param))
      {
        case  0: return MagickFalse;
        case  1: return MagickTrue;
        default:
#if DEBUG
            fprintf(stderr, " Error in MagickBoolean_val()\n"); fflush(stderr);
            abort();
#else
            fprintf(stderr, "ImageMagick Warning: magick_boolean unrecognized, set to MagickFalse\n"); fflush(stderr);
            return MagickFalse;
#endif
      }
}

/* }}} */


/* {{{ imper_flipimage()
 *
 * Image *FlipImage(Image *image, ExceptionInfo *exception)
 */
CAMLprim value imper_flipimage(
        value image_bloc )
{
    CAMLparam1(image_bloc) ;

    Image
        *new_image ;

    ExceptionInfo
        *exception ;

    exception = AcquireExceptionInfo();

    new_image = FlipImage(
            (Image *) Field(image_bloc,1),
            exception) ;

    if (exception->severity != UndefinedException)
    {
        if ( new_image )
        {
            DestroyImage( new_image ) ;
        }

        caml_failwith( exception->reason ) ;
    }

    DestroyImage( (Image *) Field(image_bloc,1) ) ;
    Field(image_bloc,1) = (value) new_image ;

    DestroyExceptionInfo(exception) ;

    CAMLreturn (Val_unit) ;
}

/* }}} */
/* {{{ imper_flopimage()
 *
 * Image *FlopImage(Image *image, ExceptionInfo *exception)
 */
CAMLprim value imper_flopimage(
        value image_bloc )
{
    CAMLparam1(image_bloc) ;

    Image
        *new_image ;

    ExceptionInfo
        *exception ;

    exception = AcquireExceptionInfo();

    new_image = FlopImage(
            (Image *) Field(image_bloc,1),
            exception) ;

    if (exception->severity != UndefinedException)
    {
        if ( new_image )
        {
            DestroyImage( new_image ) ;
        }

        caml_failwith( exception->reason ) ;
    }

    DestroyImage( (Image *) Field(image_bloc,1) ) ;
    Field(image_bloc,1) = (value) new_image ;

    DestroyExceptionInfo(exception) ;

    CAMLreturn (Val_unit) ;
}

/* }}} */
/* {{{ imper_magnifyimage()
 *
 * Image *MagnifyImage(Image *image, ExceptionInfo *exception)
 */
CAMLprim value imper_magnifyimage(
        value image_bloc )
{
    CAMLparam1(image_bloc) ;

    Image
        *new_image ;

    ExceptionInfo
        *exception ;

    exception = AcquireExceptionInfo();

    new_image = MagnifyImage(
            (Image *) Field(image_bloc,1),
            exception) ;

    if (exception->severity != UndefinedException)
    {
        if ( new_image )
        {
            DestroyImage( new_image ) ;
        }

        caml_failwith( exception->reason ) ;
    }

    DestroyImage( (Image *) Field(image_bloc,1) ) ;
    Field(image_bloc,1) = (value) new_image ;

    DestroyExceptionInfo(exception) ;

    CAMLreturn (Val_unit) ;
}

/* }}} */
/* {{{ imper_minifyimage()
 *
 * Image *MinifyImage(Image *image, ExceptionInfo *exception)
 */
CAMLprim value imper_minifyimage(
        value image_bloc )
{
    CAMLparam1(image_bloc) ;

    Image
        *new_image ;

    ExceptionInfo
        *exception ;

    exception = AcquireExceptionInfo();

    new_image = MinifyImage(
            (Image *) Field(image_bloc,1),
            exception) ;

    if (exception->severity != UndefinedException)
    {
        if ( new_image )
        {
            DestroyImage( new_image ) ;
        }

        caml_failwith( exception->reason ) ;
    }

    DestroyImage( (Image *) Field(image_bloc,1) ) ;
    Field(image_bloc,1) = (value) new_image ;

    DestroyExceptionInfo(exception) ;

    CAMLreturn (Val_unit) ;
}

/* }}} */
/* {{{ imper_enhanceimage()
 *
 * Image *EnhanceImage(const Image *image, ExceptionInfo *exception)
 */
CAMLprim value imper_enhanceimage(
        value image_bloc )
{
    CAMLparam1(image_bloc) ;

    Image
        *new_image ;

    ExceptionInfo
        *exception ;

    exception = AcquireExceptionInfo();

    new_image = EnhanceImage(
            (Image *) Field(image_bloc,1),
            exception) ;

    if (exception->severity != UndefinedException)
    {
        if ( new_image )
        {
            DestroyImage( new_image ) ;
        }

        caml_failwith( exception->reason ) ;
    }

    DestroyImage( (Image *) Field(image_bloc,1) ) ;
    Field(image_bloc,1) = (value) new_image ;

    DestroyExceptionInfo(exception) ;

    CAMLreturn (Val_unit) ;
}

/* }}} */
/* {{{ imper_trimimage()
 *
 * Image *TrimImage(const Image *image, ExceptionInfo *exception)
 */
CAMLprim value imper_trimimage(
        value image_bloc )
{
    CAMLparam1(image_bloc) ;

    Image
        *new_image ;

    ExceptionInfo
        *exception ;

    exception = AcquireExceptionInfo();

    new_image = TrimImage(
            (Image *) Field(image_bloc,1),
            exception) ;

    if (exception->severity != UndefinedException)
    {
        if ( new_image )
        {
            DestroyImage( new_image ) ;
        }

        caml_failwith( exception->reason ) ;
    }

    DestroyImage( (Image *) Field(image_bloc,1) ) ;
    Field(image_bloc,1) = (value) new_image ;

    DestroyExceptionInfo(exception) ;

    CAMLreturn (Val_unit) ;
}

/* }}} */
/* {{{ imper_despeckle()
 *
 * Image *DespeckleImage(const Image *image, ExceptionInfo *exception)
 */
CAMLprim value imper_despeckle(
        value image_bloc )
{
    CAMLparam1(image_bloc) ;

    Image
        *new_image ;

    ExceptionInfo
        *exception ;

    exception = AcquireExceptionInfo();

    new_image = DespeckleImage(
            (Image *) Field(image_bloc,1),
            exception) ;

    if (exception->severity != UndefinedException)
    {
        if ( new_image )
        {
            DestroyImage( new_image ) ;
        }

        caml_failwith( exception->reason ) ;
    }

    DestroyImage( (Image *) Field(image_bloc,1) ) ;
    Field(image_bloc,1) = (value) new_image ;

    DestroyExceptionInfo(exception) ;

    CAMLreturn (Val_unit) ;
}

/* }}} */

/* {{{ imper_coalesceimages()
 *
 * Image *CoalesceImages(Image *image, ExceptionInfo *exception)
 */
CAMLprim value imper_coalesceimages( value image_bloc )
{
    CAMLparam1(image_bloc);

    Image *new_image;

    ExceptionInfo *exception;


    exception = AcquireExceptionInfo();

    new_image = CoalesceImages(
            (Image *) Field(image_bloc,1),
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

    CAMLreturn (Val_unit);
}

/* }}} */
/* {{{ imper_flattenimages()
 *
 * Image *FlattenImages(Image *image, ExceptionInfo *exception)
 */
CAMLprim value imper_flattenimages( value image_bloc )
{
    CAMLparam1(image_bloc);

    Image *new_image;

    ExceptionInfo *exception;


    /* TODO update
    exception = AcquireExceptionInfo();
    */

    /* DEPR
    new_image = FlattenImages(
            (Image *) Field(image_bloc,1),
            exception );
    */

    new_image = MergeImageLayers(
                        (Image *) Field(image_bloc,1),
                        FlattenLayer,
                        exception );

    /* TODO
typedef enum
{
  UndefinedLayer,
  CoalesceLayer,
  CompareAnyLayer,
  CompareClearLayer,
  CompareOverlayLayer,
  DisposeLayer,
  OptimizeLayer,
  OptimizeImageLayer,
  OptimizePlusLayer,
  OptimizeTransLayer,
  RemoveDupsLayer,
  RemoveZeroLayer,
  CompositeLayer,
  MergeLayer,
  FlattenLayer,
  MosaicLayer,
  TrimBoundsLayer
} ImageLayerMethod;

    new_image = MergeImageLayers(
                        (Image *) Field(image_bloc,1),
                        const ImageLayerMethod,
                        exception );
    */

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

    CAMLreturn (Val_unit);
}

/* }}} */



/* {{{ imper_blurimage()
 *
 * Image *BlurImage(const Image *image, const double radius, const double sigma, ExceptionInfo *exception)
 */
CAMLprim value imper_blurimage(
        value image_bloc,
        value radius,
        value sigma )
{
    CAMLparam3(image_bloc, radius, sigma) ;

    Image
        *new_image ;

    ExceptionInfo
        *exception ;

    exception = AcquireExceptionInfo() ;

    new_image = BlurImage(
            (Image *) Field(image_bloc,1),
            Double_val(radius),
            Double_val(sigma),
            exception) ;

    if (exception->severity != UndefinedException)
    {
        if ( new_image )
        {
            DestroyImage( new_image ) ;
        }

        caml_failwith( exception->reason ) ;
    }

    DestroyImage( (Image *) Field(image_bloc,1) ) ;
    Field(image_bloc,1) = (value) new_image ;

    DestroyExceptionInfo(exception) ;

    CAMLreturn (Val_unit) ;
}

/* }}} */
/* {{{ imper_charcoalimage()
 *
 * Image *CharcoalImage(const Image *image, const double radius, const double sigma, ExceptionInfo *exception)
 */
CAMLprim value imper_charcoalimage(
        value image_bloc,
        value radius,
        value sigma )
{
    CAMLparam3(image_bloc, radius, sigma) ;

    Image
        *new_image ;

    ExceptionInfo
        *exception ;

    exception = AcquireExceptionInfo();

    new_image = CharcoalImage(
            (Image *) Field(image_bloc,1),
            Double_val(radius),
            Double_val(sigma),
            exception) ;

    if (exception->severity != UndefinedException)
    {
        if ( new_image )
        {
            DestroyImage( new_image ) ;
        }

        caml_failwith( exception->reason ) ;
    }

    DestroyImage( (Image *) Field(image_bloc,1) ) ;
    Field(image_bloc,1) = (value) new_image ;

    DestroyExceptionInfo(exception) ;

    CAMLreturn (Val_unit) ;
}

/* }}} */
/* {{{ imper_edgeimage()
 *
 * Image *EdgeImage(const Image *image, const double radius, ExceptionInfo *exception)
 */
CAMLprim value imper_edgeimage(
        value image_bloc,
        value radius )
{
    CAMLparam2(image_bloc, radius) ;

    Image
        *new_image ;

    ExceptionInfo
        *exception ;

    exception = AcquireExceptionInfo();

    new_image = EdgeImage(
            (Image *) Field(image_bloc,1),
            Double_val(radius),
            exception) ;

    if (exception->severity != UndefinedException)
    {
        if ( new_image )
        {
            DestroyImage( new_image ) ;
        }

        caml_failwith( exception->reason ) ;
    }

    DestroyImage( (Image *) Field(image_bloc,1) ) ;
    Field(image_bloc,1) = (value) new_image ;

    DestroyExceptionInfo(exception) ;

    CAMLreturn (Val_unit) ;
}

/* }}} */
/* {{{ imper_embossimage()
 *
 * Image *EmbossImage(const Image *image, const double radius, const double sigma, ExceptionInfo *exception)
 */
CAMLprim value imper_embossimage(
        value image_bloc,
        value radius,
        value sigma )
{
    CAMLparam3(image_bloc, radius, sigma) ;

    Image
        *new_image ;

    ExceptionInfo
        *exception ;

    exception = AcquireExceptionInfo();

    new_image = EmbossImage(
            (Image *) Field(image_bloc,1),
            Double_val(radius),
            Double_val(sigma),
            exception) ;

    if (exception->severity != UndefinedException)
    {
        if ( new_image )
        {
            DestroyImage( new_image ) ;
        }

        caml_failwith( exception->reason ) ;
    }

    DestroyImage( (Image *) Field(image_bloc,1) ) ;
    Field(image_bloc,1) = (value) new_image ;

    DestroyExceptionInfo(exception) ;

    CAMLreturn (Val_unit) ;
}

/* }}} */
/* {{{ imper_gaussianblurimage()
 *
 * Image *GaussianBlurImage(const Image *image, const double radius, const double sigma, ExceptionInfo *exception)
 */
CAMLprim value imper_gaussianblurimage(
        value image_bloc,
        value radius,
        value sigma )
{
    CAMLparam3(image_bloc, radius, sigma) ;

    Image
        *new_image ;

    ExceptionInfo
        *exception ;

    exception = AcquireExceptionInfo();

    new_image = GaussianBlurImage(
            (Image *) Field(image_bloc,1),
            Double_val(radius),
            Double_val(sigma),
            exception) ;

    if (exception->severity != UndefinedException)
    {
        if ( new_image )
        {
            DestroyImage( new_image ) ;
        }

        caml_failwith( exception->reason ) ;
    }

    DestroyImage( (Image *) Field(image_bloc,1) ) ;
    Field(image_bloc,1) = (value) new_image ;

    DestroyExceptionInfo(exception) ;

    CAMLreturn (Val_unit) ;
}

/* }}} */
/* {{{ imper_implodeimage()
 *
 * Image *ImplodeImage(const Image *image, const double amount, ExceptionInfo *exception)
 */
CAMLprim value imper_implodeimage(
        value image_bloc,
        value amount )
{
    CAMLparam2(image_bloc, amount) ;

    Image
        *new_image ;

    ExceptionInfo
        *exception ;

    exception = AcquireExceptionInfo();

    /* TODO update
    new_image = ImplodeImage(
            (Image *) Field(image_bloc,1),
            Double_val(amount),
            exception) ;
    */

    if (exception->severity != UndefinedException)
    {
        if ( new_image )
        {
            DestroyImage( new_image ) ;
        }

        caml_failwith( exception->reason ) ;
    }

    DestroyImage( (Image *) Field(image_bloc,1) ) ;
    Field(image_bloc,1) = (value) new_image ;

    DestroyExceptionInfo(exception) ;

    CAMLreturn (Val_unit) ;
}

/* }}} */
/* {{{ imper_motionblurimage()
 *
 * Image *MotionBlurImage(const Image *image, const double radius ,const double sigma, const double angle, ExceptionInfo *exception)
 */
CAMLprim value imper_motionblurimage(
        value image_bloc,
        value radius,
        value sigma,
        value angle )
{
    CAMLparam4(image_bloc, radius, sigma, angle) ;

    Image
        *new_image ;

    ExceptionInfo
        *exception ;

    exception = AcquireExceptionInfo();

    new_image = MotionBlurImage(
            (Image *) Field(image_bloc,1),
            Double_val(radius),
            Double_val(sigma),
            Double_val(angle),
            exception) ;

    if (exception->severity != UndefinedException)
    {
        if ( new_image )
        {
            DestroyImage( new_image ) ;
        }

        caml_failwith( exception->reason ) ;
    }

    DestroyImage( (Image *) Field(image_bloc,1) ) ;
    Field(image_bloc,1) = (value) new_image ;

    DestroyExceptionInfo(exception) ;

    CAMLreturn (Val_unit) ;
}

/* }}} */
/* {{{ imper_oilpaintimage()
 *
 * Image *OilPaintImage(const Image *image, const double radius, ExceptionInfo *exception)
 */
CAMLprim value imper_oilpaintimage(
        value image_bloc,
        value radius )
{
    CAMLparam2(image_bloc, radius) ;

    Image
        *new_image ;

    ExceptionInfo
        *exception ;

    exception = AcquireExceptionInfo();

    /* TODO update
    new_image = OilPaintImage(
            (Image *) Field(image_bloc,1),
            Double_val(radius),
            exception) ;
    */

    if (exception->severity != UndefinedException)
    {
        if ( new_image )
        {
            DestroyImage( new_image ) ;
        }

        caml_failwith( exception->reason ) ;
    }

    DestroyImage( (Image *) Field(image_bloc,1) ) ;
    Field(image_bloc,1) = (value) new_image ;

    DestroyExceptionInfo(exception) ;

    CAMLreturn (Val_unit) ;
}

/* }}} */
/* {{{ imper_rollimage()
 *
 * Image *RollImage(const Image *image, const long x_offset, const long y_offset, ExceptionInfo *exception)
 */
CAMLprim value imper_rollimage(
        value image_bloc,
        value x_offset,
        value y_offset )
{
    CAMLparam3(image_bloc, x_offset, y_offset) ;

    Image
        *new_image ;

    ExceptionInfo
        *exception ;

    exception = AcquireExceptionInfo() ;

    new_image = RollImage(
            (Image *) Field(image_bloc,1),
            Long_val(x_offset),
            Long_val(y_offset),
            exception) ;

    if (exception->severity != UndefinedException)
    {
        if ( new_image )
        {
            DestroyImage( new_image ) ;
        }

        caml_failwith( exception->reason ) ;
    }

    DestroyImage( (Image *) Field(image_bloc,1) ) ;
    Field(image_bloc,1) = (value) new_image ;

    DestroyExceptionInfo(exception) ;

    CAMLreturn (Val_unit) ;
}

/* }}} */
/* {{{ imper_shadeimage()
 *
 * Image *ShadeImage(const Image *image, const MagickBooleanType gray,
 *                         const double azimuth, const double elevation, ExceptionInfo *exception)
 */
CAMLprim value imper_shadeimage(
        value image_bloc,
        value color_shading,
        value azimuth,
        value elevation )
{
    CAMLparam4(image_bloc, color_shading, azimuth, elevation) ;

    Image
        *new_image ;

    ExceptionInfo
        *exception ;

    exception = AcquireExceptionInfo() ;

    new_image = ShadeImage(
            (Image *) Field(image_bloc,1),
            MagickBoolean_val(color_shading),
            Double_val(azimuth),
            Double_val(elevation),
            exception ) ;

    if (exception->severity != UndefinedException)
    {
        if ( new_image )
        {
            DestroyImage( new_image ) ;
        }

        caml_failwith( exception->reason ) ;
    }

    DestroyImage( (Image *) Field(image_bloc,1) ) ;
    Field(image_bloc,1) = (value) new_image ;

    DestroyExceptionInfo(exception) ;

    CAMLreturn (Val_unit) ;
}

/* }}} */
/* {{{ imper_sharpenimage()
 *
 * Image *SharpenImage(Image *image, const double radius, const double sigma, ExceptionInfo *exception)
 */
CAMLprim value imper_sharpenimage(
        value image_bloc,
        value radius,
        value sigma )
{
    CAMLparam3(image_bloc, radius, sigma) ;

    Image
        *new_image ;

    ExceptionInfo
        *exception ;

    exception = AcquireExceptionInfo();

    new_image = SharpenImage(
            (Image *) Field(image_bloc,1),
            Double_val(radius),
            Double_val(sigma),
            exception) ;

    if (exception->severity != UndefinedException)
    {
        if ( new_image )
        {
            DestroyImage( new_image ) ;
        }

        caml_failwith( exception->reason ) ;
    }

    DestroyImage( (Image *) Field(image_bloc,1) ) ;
    Field(image_bloc,1) = (value) new_image ;

    DestroyExceptionInfo(exception) ;

    CAMLreturn (Val_unit) ;
}

/* }}} */
/* {{{ imper_spreadimage()
 *
 * Image *SpreadImage(const Image *image, const double radius, ExceptionInfo *exception)
 */
CAMLprim value imper_spreadimage(
        value image_bloc,
        value radius )
{
    CAMLparam2(image_bloc, radius) ;

    Image
        *new_image ;

    ExceptionInfo
        *exception ;

    exception = AcquireExceptionInfo();

    /* TODO update
    new_image = SpreadImage(
            (Image *) Field(image_bloc,1),
            Double_val(radius),
            exception) ;
    */

    if (exception->severity != UndefinedException)
    {
        if ( new_image )
        {
            DestroyImage( new_image ) ;
        }

        caml_failwith( exception->reason ) ;
    }

    DestroyImage( (Image *) Field(image_bloc,1) ) ;
    Field(image_bloc,1) = (value) new_image ;

    DestroyExceptionInfo(exception) ;

    CAMLreturn (Val_unit) ;
}

/* }}} */
/* {{{ imper_swirlimage()
 *
 * Image *SwirlImage(const Image *image, double degrees, ExceptionInfo *exception)
 */
CAMLprim value imper_swirlimage(
        value image_bloc,
        value degrees )
{
    CAMLparam2(image_bloc, degrees) ;

    Image
        *new_image ;

    ExceptionInfo
        *exception ;

    exception = AcquireExceptionInfo();

    /* TODO update
    new_image = SwirlImage(
            (Image *) Field(image_bloc,1),
            Double_val(degrees),
            exception) ;
    */

    if (exception->severity != UndefinedException)
    {
        if ( new_image )
        {
            DestroyImage( new_image ) ;
        }

        caml_failwith( exception->reason ) ;
    }

    DestroyImage( (Image *) Field(image_bloc,1) ) ;
    Field(image_bloc,1) = (value) new_image ;

    DestroyExceptionInfo(exception) ;

    CAMLreturn (Val_unit) ;
}

/* }}} */
/* {{{ imper_unsharpmaskimage()
 *
 * Image *UnsharpMaskImage(const Image *image, const double radius, const double sigma, const double amount, const double threshold, ExceptionInfo *exception)
 */
CAMLprim value imper_unsharpmaskimage(
        value image_bloc,
        value radius,
        value sigma,
        value amount,
        value threshold )
{
    CAMLparam5(image_bloc, radius, sigma, amount, threshold) ;

    Image
        *new_image ;

    ExceptionInfo
        *exception ;

    exception = AcquireExceptionInfo();

    new_image = UnsharpMaskImage(
            (Image *) Field(image_bloc,1),
            Double_val(radius),
            Double_val(sigma),
            Double_val(amount),
            Double_val(threshold),
            exception) ;

    if (exception->severity != UndefinedException)
    {
        if ( new_image )
        {
            DestroyImage( new_image ) ;
        }

        caml_failwith( exception->reason ) ;
    }

    DestroyImage( (Image *) Field(image_bloc,1) ) ;
    Field(image_bloc,1) = (value) new_image ;

    DestroyExceptionInfo(exception) ;

    CAMLreturn (Val_unit) ;
}

/* }}} */
/* {{{ imper_waveimage()
 *
 * Image *WaveImage(const Image *image, const double amplitude, const double wave_length, ExceptionInfo *exception)
 */
CAMLprim value imper_waveimage(
        value image_bloc,
        value amplitude,
        value wave_length )
{
    CAMLparam3(image_bloc, amplitude, wave_length) ;

    Image
        *new_image ;

    ExceptionInfo
        *exception ;

    exception = AcquireExceptionInfo();

    /* TODO update
    new_image = WaveImage(
            (Image *) Field(image_bloc,1),
            Double_val(amplitude),
            Double_val(wave_length),
            exception) ;
    */

    if (exception->severity != UndefinedException)
    {
        if ( new_image )
        {
            DestroyImage( new_image ) ;
        }

        caml_failwith( exception->reason ) ;
    }

    DestroyImage( (Image *) Field(image_bloc,1) ) ;
    Field(image_bloc,1) = (value) new_image ;

    DestroyExceptionInfo(exception) ;

    CAMLreturn (Val_unit) ;
}

/* }}} */

/* {{{ imper_rotateimage()
 *
 * Image *RotateImage(const Image *image, const double degrees, ExceptionInfo *exception)
 */
CAMLprim value imper_rotateimage(
        value image_bloc,
        value degrees )
{
    CAMLparam2(image_bloc, degrees);

    Image
        *new_image;

    ExceptionInfo
        *exception;

    exception = AcquireExceptionInfo();

    new_image = RotateImage(
            (Image *) Field(image_bloc,1),
            Double_val(degrees),
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

    CAMLreturn (Val_unit);
}

/* }}} */
/* {{{ imper_shearimage()
 *
 * Image *ShearImage(const Image *image, const double x_shear, const double y_shear, ExceptionInfo *exception)
 */
CAMLprim value imper_shearimage(
        value image_bloc,
        value x_shear,
        value y_shear )
{
    CAMLparam3(image_bloc, x_shear, y_shear);

    Image
        *new_image;

    ExceptionInfo
        *exception;

    exception = AcquireExceptionInfo();

    new_image = ShearImage(
            (Image *) Field(image_bloc,1),
            Double_val(x_shear),
            Double_val(y_shear),
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

    CAMLreturn (Val_unit);
}

/* }}} */
/* {{{ imper_sampleimage()
 *
 * Image *SampleImage(const Image *image, const unsigned long columns, const unsigned long rows, ExceptionInfo *exception)
 */
CAMLprim value imper_sampleimage(
        value image_bloc,
        value columns,
        value rows )
{
    CAMLparam3(image_bloc, columns, rows);

    Image
        *new_image;

    ExceptionInfo
        *exception;

    exception = AcquireExceptionInfo();

    new_image = SampleImage(
            (Image *) Field(image_bloc,1),
            Long_val(columns),
            Long_val(rows),
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

    CAMLreturn (Val_unit);
}

/* }}} */
/* {{{ imper_scaleimage()
 *
 * Image *ScaleImage(const Image *image, const unsigned long columns, const unsigned long rows, ExceptionInfo *exception)
 */
CAMLprim value imper_scaleimage(
        value image_bloc,
        value columns,
        value rows )
{
    CAMLparam3(image_bloc, columns, rows);

    Image
        *new_image;

    ExceptionInfo
        *exception;

    exception = AcquireExceptionInfo();

    new_image = ScaleImage(
            (Image *) Field(image_bloc,1),
            Long_val(columns),
            Long_val(rows),
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

    CAMLreturn (Val_unit);
}

/* }}} */
/* {{{ imper_thumbnailimage()
 *
 * Image *ThumbnailImage(const Image *image,const unsigned long columns, const unsigned long rows,ExceptionInfo *exception)
 */
CAMLprim value imper_thumbnailimage(
        value image_bloc,
        value columns,
        value rows )
{
    CAMLparam3(image_bloc, columns, rows);

    Image
        *new_image;

    ExceptionInfo
        *exception;

    exception = AcquireExceptionInfo();

    new_image = ThumbnailImage(
            (Image *) Field(image_bloc,1),
            Long_val(columns),
            Long_val(rows),
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

    CAMLreturn (Val_unit);
}

/* }}} */

/* {{{ imper_adaptivethresholdimage()
 *
 * Image *AdaptiveThresholdImage(const Image *image,
 *              const unsigned long width, const unsigned long height,
 *              const long offset, ExceptionInfo *exception)
 */
CAMLprim value imper_adaptivethresholdimage(
        value image_bloc,
        value width,
        value height,
        value offset )
{
    CAMLparam4(image_bloc, width, height, offset);

    Image
        *new_image;

    ExceptionInfo
        *exception;

    exception = AcquireExceptionInfo();

    new_image = AdaptiveThresholdImage(
            (Image *) Field(image_bloc,1),
            Long_val(width),
            Long_val(height),
            Long_val(offset),
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

    CAMLreturn (Val_unit);
}

/* }}} */


/* {{{ imper_cropimage()
 *
 * Image *CropImage(const Image *image, const RectangleInfo *geometry, ExceptionInfo *exception)
 */
CAMLprim value imper_cropimage(
        value image_bloc,
        value x,
        value y,
        value width,
        value height )
{
    CAMLparam5(image_bloc, x, y, width, height) ;

    Image
        *new_image ;

    ExceptionInfo
        *exception ;

    RectangleInfo 
        geometry ;

    exception = AcquireExceptionInfo() ;

    geometry.x  = Long_val(x) ;
    geometry.y  = Long_val(y) ;
    geometry.width  = Long_val(width) ;
    geometry.height = Long_val(height) ;

    new_image = CropImage(
            (Image *) Field(image_bloc,1),
            &geometry,
            exception) ;

    if (exception->severity != UndefinedException)
    {
        if ( new_image )
        {
            DestroyImage( new_image ) ;
        }

        caml_failwith( exception->reason ) ;
    }

    DestroyImage( (Image *) Field(image_bloc,1) ) ;
    Field(image_bloc,1) = (value) new_image ;

    DestroyExceptionInfo(exception) ;

    CAMLreturn (Val_unit) ;
}

/* }}} */
/* {{{ imper_chopimage()
 *
 * Image *ChopImage(const Image *image, const RectangleInfo *chop_info, ExceptionInfo *exception)
 */
CAMLprim value imper_chopimage(
        value image_bloc,
        value x,
        value y,
        value width,
        value height )
{
    CAMLparam5(image_bloc, x, y, width, height) ;

    Image
        *new_image ;

    ExceptionInfo
        *exception ;

    RectangleInfo 
        chop_info ;

    exception = AcquireExceptionInfo();

    chop_info.x  = Long_val(x) ;
    chop_info.y  = Long_val(y) ;
    chop_info.width  = Long_val(width) ;
    chop_info.height = Long_val(height) ;

    new_image = ChopImage(
            (Image *) Field(image_bloc,1),
            &chop_info,
            exception) ;

    if (exception->severity != UndefinedException)
    {
        if ( new_image )
        {
            DestroyImage( new_image ) ;
        }

        caml_failwith( exception->reason ) ;
    }

    DestroyImage( (Image *) Field(image_bloc,1) ) ;
    Field(image_bloc,1) = (value) new_image ;

    DestroyExceptionInfo(exception) ;

    CAMLreturn (Val_unit) ;
}

/* }}} */

/* {{{ imper_spliceimage()
 *
 * Image *SpliceImage(const Image *image, const RectangleInfo *chop_info, ExceptionInfo *exception)
 */
CAMLprim value imper_spliceimage(
        value image_bloc,
        value x,
        value y,
        value width,
        value height )
{
    CAMLparam5(image_bloc, x, y, width, height) ;

    Image
        *new_image ;

    ExceptionInfo
        *exception ;

    RectangleInfo 
        chop_info ;

    exception = AcquireExceptionInfo();

    chop_info.x  = Long_val(x) ;
    chop_info.y  = Long_val(y) ;
    chop_info.width  = Long_val(width) ;
    chop_info.height = Long_val(height) ;

    new_image = SpliceImage(
            (Image *) Field(image_bloc,1),
            &chop_info,
            exception) ;

    if (exception->severity != UndefinedException)
    {
        if ( new_image )
        {
            DestroyImage( new_image ) ;
        }

        caml_failwith( exception->reason ) ;
    }

    DestroyImage( (Image *) Field(image_bloc,1) ) ;
    Field(image_bloc,1) = (value) new_image ;

    DestroyExceptionInfo(exception) ;

    CAMLreturn (Val_unit) ;
}

/* }}} */



/* {{{ ChannelType_val() */

static int
ChannelType_val( value param )
{
#if CAML_FRAME
    CAMLparam1 (param);
#endif

#if TYPE_CHECKING
    assert (Is_long (param));
#endif

#if DEBUG
    printf(" ChannelType_val(%d)\n", Int_val(param)); fflush(stdout);
#endif

    switch (Int_val (param))
      {
        case  0: return UndefinedChannel;
        case  1: return RedChannel;
        case  2: return GrayChannel;
        case  3: return CyanChannel;
        case  4: return GreenChannel;
        case  5: return MagentaChannel;
        case  6: return BlueChannel;
        case  7: return YellowChannel;
        case  8: return AlphaChannel;
        case  9: return OpacityChannel;
        case 10: return BlackChannel;
        case 11: return IndexChannel;
        case 12: return AllChannels;
        case 13: return DefaultChannels;
        default:
#if DEBUG
            fprintf(stderr, " Error in ChannelType_val()\n"); fflush(stderr);
            abort();
#else
            fprintf(stderr, "OCaml-ImageMagick Warning: channel_type unrecognized, set to DefaultChannels\n"); fflush(stderr);
            return DefaultChannels;
#endif
      }
}

/* }}} */


/* {{{ imper_negateimage() 
 *
 * MagickBooleanType NegateImage(Image *, const MagickBooleanType)
 */
CAMLprim value imper_negateimage(
            value image_bloc,
            value grayscale )
{
    CAMLparam2(image_bloc, grayscale) ;

    ExceptionInfo
        *exc_info;

    MagickBooleanType
        ret ;

    exc_info = AcquireExceptionInfo();

    ret = NegateImage(
                (Image *) Field(image_bloc,1),
                MagickBoolean_val(grayscale), exc_info ) ;

    DestroyExceptionInfo(exc_info);

    if (ret == MagickFalse) {
        caml_failwith("negate failed") ;
    }

    CAMLreturn (Val_unit) ;
}

/* }}} */
/* {{{ imper_contrastimage() 
 *
 * MagickBooleanType ContrastImage(Image *image, const MagickBooleanType sharpen)
 */
CAMLprim value imper_contrastimage(
            value image_bloc,
            value sharpen )
{
    CAMLparam2(image_bloc, sharpen) ;

    MagickBooleanType
        ret ;

    /*
     *  0 increases the contrast
     *  otherwise reduced it
     */

    /* TODO update
    ret = ContrastImage(
                (Image *) Field(image_bloc,1),
                MagickBoolean_val(sharpen) ) ;
    */
    /*
     *  MagickFalse increases the contrast,
     *  otherwise reduced it
     */

    if (ret == MagickFalse) {
        caml_failwith("contrast failed") ;
    }

    CAMLreturn (Val_unit) ;
}

/* }}} */
/* {{{ imper_equalizeimage() 
 *
 * MagickBooleanType EqualizeImage(Image *image)
 */
CAMLprim value imper_equalizeimage( value image_bloc )
{
    CAMLparam1(image_bloc) ;

    MagickBooleanType
        ret ;

    /* TODO update
    ret = EqualizeImage(
                (Image *) Field(image_bloc,1) ) ;
    */

    if (ret == MagickFalse) {
        caml_failwith("equalize failed") ;
    }

    CAMLreturn (Val_unit) ;
}

/* }}} */
/* {{{ imper_normalizeimage() 
 *
 * MagickBooleanType NormalizeImage(Image *image)
 */
CAMLprim value imper_normalizeimage( value image_bloc )
{
    CAMLparam1(image_bloc) ;

    MagickBooleanType
        ret ;

    /* TODO update
    ret = NormalizeImage(
                (Image *) Field(image_bloc,1) ) ;
    */

    if (ret == MagickFalse) {
        caml_failwith("normalize failed") ;
    }

    CAMLreturn (Val_unit) ;
}

/* }}} */
/* {{{ imper_blackthresholdimage() 
 *
 * MagickBooleanType BlackThresholdImage(Image *image, const char *threshold)
 */
CAMLprim value imper_blackthresholdimage( value image_bloc, value threshold )
{
    CAMLparam2(image_bloc, threshold) ;

    MagickBooleanType
        ret ;

    /* TODO update
    ret = BlackThresholdImage(
                (Image *) Field(image_bloc,1),
                String_val(threshold) ) ;
    */

    if (ret == MagickFalse) {
        caml_failwith("black_threshold failed") ;
    }

    CAMLreturn (Val_unit) ;
}

/* }}} */
/* {{{ imper_whitethresholdimage() 
 *
 * MagickBooleanType WhiteThresholdImage(Image *image, const char *threshold)
 */
CAMLprim value imper_whitethresholdimage( value image_bloc, value threshold )
{
    CAMLparam2(image_bloc, threshold) ;

    MagickBooleanType
        ret ;

    /* TODO update
    ret = WhiteThresholdImage(
                (Image *) Field(image_bloc,1),
                String_val(threshold) ) ;
    */

    if (ret == MagickFalse) {
        caml_failwith("white_threshold failed") ;
    }

    CAMLreturn (Val_unit) ;
}

/* }}} */
/* {{{ imper_cyclecolormapimage() 
 *
 * MagickBooleanType CycleColormapImage(Image *image, const long displace)
 */
CAMLprim value imper_cyclecolormapimage(
            value image_bloc,
            value displace )
{
    CAMLparam2(image_bloc, displace) ;

    MagickBooleanType
        ret ;

    /* TODO update
    ret = CycleColormapImage(
                (Image *) Field(image_bloc,1),
                Long_val(displace) ) ;
    */

    if (ret == MagickFalse) {
        caml_failwith("cyclecolormap failed") ;
    }

    CAMLreturn (Val_unit) ;
}

/* }}} */
/* {{{ imper_modulateimage() 
 *
 * MagickBooleanType ModulateImage(Image *image, const char *modulate)
 */
CAMLprim value imper_modulateimage(
            value image_bloc,
            value modulate )
{
    CAMLparam2(image_bloc, modulate) ;

    MagickBooleanType
        ret ;

    /* TODO update
    ret = ModulateImage(
                (Image *) Field(image_bloc,1),
                String_val(modulate) ) ;
    */

    if (ret == MagickFalse) {
        caml_failwith("modulate failed") ;
    }

    CAMLreturn (Val_unit) ;
}

/* }}} */
/* {{{ imper_solarizeimage() 
 *
 * MagickBooleanType SolarizeImage(Image *image, const double threshold)
 */
CAMLprim value imper_solarizeimage(
            value image_bloc,
            value threshold )
{
    CAMLparam2(image_bloc, threshold) ;

    MagickBooleanType
        ret ;

    /* TODO update
    ret = SolarizeImage(
                (Image *) Field(image_bloc,1),
                Double_val(threshold) ) ;
    */

    if (ret == MagickFalse) {
        caml_failwith("solarize failed") ;
    }

    CAMLreturn (Val_unit) ;
}

/* }}} */

/* {{{ imper_stripimage() 
 *
 * MagickBooleanType StripImage(Image *image)
 */
CAMLprim value imper_stripimage(
            value image_bloc )
{
    CAMLparam1(image_bloc) ;

    MagickBooleanType
        ret ;

    /* TODO update
    ret = StripImage(
                (Image *) Field(image_bloc,1) ) ;
    */

    if (ret == MagickFalse) {
        caml_failwith("strip failed") ;
    }

    CAMLreturn (Val_unit) ;
}

/* }}} */


/* {{{ imper_levelimage() 
 *
 * MagickBooleanType
 *    LevelImage(Image *image, const char *levels)
 *
 * MagickBooleanType
 *    LevelImage(Image *, const double, const double, const double, ExceptionInfo *)
 */
CAMLprim value imper_levelimage( value image_bloc, value levels )
{
    CAMLparam2(image_bloc, levels) ;

    MagickBooleanType
        ret ;

    /* TODO update
    ret = LevelImage(
                (Image *) Field(image_bloc,1),
                String_val(levels) ) ;
    */

    if (ret == MagickFalse) {
        caml_failwith("level failed") ;
    }

    CAMLreturn (Val_unit) ;
}

/* }}} */




/* {{{ NoiseType_val() */

static int
NoiseType_val( value param )
{
#if CAML_FRAME
    CAMLparam1 (param);
#endif

#if TYPE_CHECKING
    assert (Is_long (param));
#endif

    switch (Int_val (param))
      {
        case 0: return UndefinedNoise;
        case 1: return UniformNoise;
        case 2: return GaussianNoise;
        case 3: return MultiplicativeGaussianNoise;
        case 4: return ImpulseNoise;
        case 5: return LaplacianNoise;
        case 6: return PoissonNoise;
        default:
#if DEBUG
            fprintf(stderr, " Error in NoiseType_val()\n"); fflush(stderr);
            abort();
#else
            fprintf(stderr, "ImageMagick Warning: noise_type unrecognized, set to Undefined\n"); fflush(stderr);
            return UndefinedNoise;
#endif
      }
}

/* }}} */
/* {{{ imper_addnoiseimage()
 *
 * Image *AddNoiseImage(const Image *image, const NoiseType noise_type, ExceptionInfo *exception)
 */
CAMLprim value imper_addnoiseimage(
        value image_bloc,
        value noise_type )
{
    CAMLparam2(image_bloc, noise_type);

    Image
        *new_image;

    ExceptionInfo
        *exception;

    exception = AcquireExceptionInfo();

    /* TODO update
    new_image = AddNoiseImage(
            (Image *) Field(image_bloc,1),
            NoiseType_val(noise_type),
            exception );
    */

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

    CAMLreturn (Val_unit);
}

/* }}} */


/* {{{ FilterType_val() */

static FilterType
FilterType_val( value param )
{
#if CAML_FRAME
    CAMLparam1 (param);
#endif

#if TYPE_CHECKING
    assert (Is_long (param));
#endif

    switch (Int_val (param))
      {
        case  0: return UndefinedFilter;
        case  1: return PointFilter;
        case  2: return BoxFilter;
        case  3: return TriangleFilter;
        case  4: return HermiteFilter;
        case  5: return HanningFilter;
        case  6: return HammingFilter;
        case  7: return BlackmanFilter;
        case  8: return GaussianFilter;
        case  9: return QuadraticFilter;
        case 10: return CubicFilter;
        case 11: return CatromFilter;
        case 12: return MitchellFilter;
        case 13: return LanczosFilter;
        case 14: return BesselFilter;
        case 15: return SincFilter;

 /* TODO update
  UndefinedFilter;
  PointFilter;
  BoxFilter;
  TriangleFilter;
  HermiteFilter;
  HannFilter;
  HammingFilter;
  BlackmanFilter;
  GaussianFilter;
  QuadraticFilter;
  CubicFilter;
  CatromFilter;
  MitchellFilter;
  JincFilter;
  SincFilter;
  SincFastFilter;
  KaiserFilter;
  WelchFilter;
  ParzenFilter;
  BohmanFilter;
  BartlettFilter;
  LagrangeFilter;
  LanczosFilter;
  LanczosSharpFilter;
  Lanczos2Filter;
  Lanczos2SharpFilter;
  RobidouxFilter;
  RobidouxSharpFilter;
  CosineFilter;
  SplineFilter;
  LanczosRadiusFilter;
  CubicSplineFilter;
  */
        default:
#if DEBUG
            fprintf(stderr, " Error in FilterType_val()\n"); fflush(stderr);
            abort();
#else
            fprintf(stderr, "ImageMagick Warning: filter_type unrecognized, set to Undefined\n"); fflush(stderr);
            return UndefinedFilter;
#endif
      }
}

/* }}} */
/* {{{ imper_resizeimage()
 *
 * Image *ResizeImage(Image *image, const unsigned long columns, const unsigned long rows,
 *                  const FilterTypes filter, const double blur, ExceptionInfo *exception)
 */
CAMLprim value imper_resizeimage(
        value image_bloc,
        value columns,
        value rows,
        value filter,
        value blur )
{
    CAMLparam5(image_bloc, columns, rows, filter, blur);

    Image
        *new_image;

    ExceptionInfo
        *exception;

    exception = AcquireExceptionInfo();

    /* TODO update
    new_image = ResizeImage(
            (Image *) Field(image_bloc,1),
            Long_val(columns),
            Long_val(rows),
            FilterType_val(filter),
            Double_val(blur),
            exception );
    */

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

    CAMLreturn (Val_unit);
}

/* }}} */



/* @TODO:
QuantizeInfo *CloneQuantizeInfo(const QuantizeInfo *quantize_info)
QuantizeInfo *DestroyQuantizeInfo(QuantizeInfo *quantize_info)
MagickBooleanType GetImageQuantizeError(Image *image)
GetQuantizeInfo(QuantizeInfo *quantize_info)
MagickBooleanType QuantizeImage(const QuantizeInfo *quantize_info, Image *image)
MagickBooleanType QuantizeImages(const QuantizeInfo *quantize_info, Image *images)
*/


/* {{{ imper_orderedditherimage() 
 *
 * MagickBooleanType OrderedDitherImage(Image *image)
 */
CAMLprim value
imper_orderedditherimage( value image_bloc )
{
    CAMLparam1(image_bloc) ;

    MagickBooleanType
        ret ;

    /* TODO update
    ret = OrderedDitherImage(
                (Image *) Field(image_bloc,1) ) ;
    */

    if (ret == MagickFalse) {
        caml_failwith("ordered_dither failed") ;
    }

    CAMLreturn (Val_unit) ;
}

/* }}} */

/* {{{ imper_compressimagecolormap() 
 *
 * void CompressImageColormap(Image *image)
 */
CAMLprim value
imper_compressimagecolormap( value image_bloc )
{
    CAMLparam1(image_bloc) ;

    /* TODO update
    CompressImageColormap(
                (Image *) Field(image_bloc,1) ) ;
    */

    CAMLreturn (Val_unit) ;
}

/* }}} */
/* {{{ imper_posterizeimage() 
 *
 * MagickBooleanType PosterizeImage(Image *image, const unsigned long levels, const MagickBooleanType dither)
 */
CAMLprim value
imper_posterizeimage(value image_bloc, value levels, value dither)
{
    CAMLparam3(image_bloc, levels, dither);

    MagickBooleanType
        ret;

    /* TODO update
    ret = PosterizeImage(
                (Image *) Field(image_bloc,1),
                Long_val(levels),
                MagickBoolean_val(dither)
                );
    */

    if (ret == MagickFalse) {
        caml_failwith("posterize failed");
    }

    CAMLreturn (Val_unit);
}

/* }}} */

/* @TODO:
MagickBooleanType MapImages(Image *images,Image *map_image, const MagickBooleanType dither)
*/

/* {{{ imper_mapimage() 
 *
 * MagickBooleanType MapImage(Image *image,const Image *map_image, const MagickBooleanType dither)
 */
CAMLprim value
imper_mapimage(value image_bloc, value map_image_bloc, value dither)
{
    CAMLparam3(image_bloc, map_image_bloc, dither);

    MagickBooleanType
        ret;

    /* DEPR
    ret = MapImage(
                (Image *) Field(image_bloc,1),
                (Image *) Field(map_image_bloc,1),
                MagickBoolean_val(dither)
                );
    */

    QuantizeInfo quantize_info;
    GetQuantizeInfo( &quantize_info );
    /* TODO update
    quantize_info.dither = MagickBoolean_val(dither);
    RemapImage( &quantize_info,
                (Image *) Field(image_bloc,1),
                (Image *) Field(map_image_bloc,1)
                );
    */

    if (ret == MagickFalse) {
        caml_failwith("map_image failed");
    }

    CAMLreturn (Val_unit);
}

/* }}} */



void finalize_image(value);

/* {{{ fun_blurimage()
 *
 * Image *BlurImage(const Image *image, const double radius, const double sigma, ExceptionInfo *exception)
 */
CAMLprim value
fun_blurimage(
        value image_bloc,
        value radius,
        value sigma )
{
    CAMLparam3(image_bloc, radius, sigma);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo
        *exception;

    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    Field(new_image_bloc,1) = (value)
        BlurImage(
            (Image *) Field(image_bloc,1),
            Double_val(radius),
            Double_val(sigma),
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

/* }}} */
/* {{{ fun_charcoalimage()
 *
 * Image *CharcoalImage(const Image *image, const double radius, const double sigma, ExceptionInfo *exception)
 */
CAMLprim value
fun_charcoalimage(
        value image_bloc,
        value radius,
        value sigma )
{
    CAMLparam3(image_bloc, radius, sigma);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo
        *exception;

    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    Field(new_image_bloc,1) = (value)
        CharcoalImage(
            (Image *) Field(image_bloc,1),
            Double_val(radius),
            Double_val(sigma),
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

/* }}} */
/* {{{ fun_edgeimage()
 *
 * Image *EdgeImage(const Image *image, const double radius, ExceptionInfo *exception)
 */
CAMLprim value
fun_edgeimage(
        value image_bloc,
        value radius )
{
    CAMLparam2(image_bloc, radius);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo
        *exception;

    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    Field(new_image_bloc,1) = (value)
        EdgeImage(
            (Image *) Field(image_bloc,1),
            Double_val(radius),
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

/* }}} */
/* {{{ fun_embossimage()
 *
 * Image *EmbossImage(const Image *image, const double radius, const double sigma, ExceptionInfo *exception)
 */
CAMLprim value
fun_embossimage(
        value image_bloc,
        value radius,
        value sigma )
{
    CAMLparam3(image_bloc, radius, sigma);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo
        *exception;

    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    Field(new_image_bloc,1) = (value)
        EmbossImage(
            (Image *) Field(image_bloc,1),
            Double_val(radius),
            Double_val(sigma),
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

/* }}} */
/* {{{ fun_gaussianblurimage()
 *
 * Image *GaussianBlurImage(const Image *image, const double radius, const double sigma, ExceptionInfo *exception)
 */
CAMLprim value
fun_gaussianblurimage(
        value image_bloc,
        value radius,
        value sigma )
{
    CAMLparam3(image_bloc, radius, sigma);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo
        *exception;

    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    Field(new_image_bloc,1) = (value)
        GaussianBlurImage(
            (Image *) Field(image_bloc,1),
            Double_val(radius),
            Double_val(sigma),
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

/* }}} */
/* {{{ fun_implodeimage()
 *
 * Image *ImplodeImage(const Image *image, const double amount, ExceptionInfo *exception)
 */
CAMLprim value
fun_implodeimage(
        value image_bloc,
        value amount )
{
    CAMLparam2(image_bloc, amount);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo
        *exception;

    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    /* TODO update
    Field(new_image_bloc,1) = (value)
        ImplodeImage(
            (Image *) Field(image_bloc,1),
            Double_val(amount),
            exception );
    */


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

/* }}} */
/* {{{ fun_motionblurimage()
 *
 * Image *MotionBlurImage(const Image *image, const double radius ,const double sigma, const double angle, ExceptionInfo *exception)
 */
CAMLprim value
fun_motionblurimage(
        value image_bloc,
        value radius,
        value sigma,
        value angle )
{
    CAMLparam4(image_bloc, radius, sigma, angle);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo
        *exception;

    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    Field(new_image_bloc,1) = (value)
        MotionBlurImage(
            (Image *) Field(image_bloc,1),
            Double_val(radius),
            Double_val(sigma),
            Double_val(angle),
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

/* }}} */
/* {{{ fun_oilpaintimage()
 *
 * Image *OilPaintImage(const Image *image, const double radius, ExceptionInfo *exception)
 */
CAMLprim value
fun_oilpaintimage(
        value image_bloc,
        value radius )
{
    CAMLparam2(image_bloc, radius);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo
        *exception;

    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    /* TODO update
    Field(new_image_bloc,1) = (value)
        OilPaintImage(
            (Image *) Field(image_bloc,1),
            Double_val(radius),
            exception );
    */


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

/* }}} */
/* {{{ fun_rollimage()
 *
 * Image *RollImage(const Image *image, const long x_offset, const long y_offset, ExceptionInfo *exception)
 */
CAMLprim value
fun_rollimage(
        value image_bloc,
        value x_offset,
        value y_offset )
{
    CAMLparam3(image_bloc, x_offset, y_offset);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo
        *exception;

    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    Field(new_image_bloc,1) = (value)
        RollImage(
            (Image *) Field(image_bloc,1),
            Long_val(x_offset),
            Long_val(y_offset),
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

/* }}} */
/* {{{ fun_shadeimage()
 *
 * Image *ShadeImage(const Image *image, const unsigned int color_shading, double azimuth, double elevation, ExceptionInfo *exception)
 */
CAMLprim value
fun_shadeimage(
        value image_bloc,
        value color_shading,
        value azimuth,
        value elevation )
{
    CAMLparam4(image_bloc, color_shading, azimuth, elevation);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo
        *exception;

    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    Field(new_image_bloc,1) = (value)
        ShadeImage(
            (Image *) Field(image_bloc,1),
            Int_val(color_shading),
            Double_val(azimuth),
            Double_val(elevation),
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

/* }}} */
/* {{{ fun_sharpenimage()
 *
 * Image *SharpenImage(Image *image, const double radius, const double sigma, ExceptionInfo *exception)
 */
CAMLprim value
fun_sharpenimage(
        value image_bloc,
        value radius,
        value sigma )
{
    CAMLparam3(image_bloc, radius, sigma);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo
        *exception;

    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    Field(new_image_bloc,1) = (value)
        SharpenImage(
            (Image *) Field(image_bloc,1),
            Double_val(radius),
            Double_val(sigma),
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

/* }}} */
/* {{{ fun_spreadimage()
 *
 * Image *SpreadImage(const Image *image, const double radius, ExceptionInfo *exception)
 */
CAMLprim value
fun_spreadimage(
        value image_bloc,
        value radius )
{
    CAMLparam2(image_bloc, radius);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo
        *exception;

    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    /* TODO update
    Field(new_image_bloc,1) = (value)
        SpreadImage(
            (Image *) Field(image_bloc,1),
            Double_val(radius),
            exception );
    */


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

/* }}} */
/* {{{ fun_swirlimage()
 *
 * Image *SwirlImage(const Image *image, double degrees, ExceptionInfo *exception)
 */
CAMLprim value
fun_swirlimage(
        value image_bloc,
        value degrees )
{
    CAMLparam2(image_bloc, degrees);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo
        *exception;

    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    /* TODO update
    Field(new_image_bloc,1) = (value)
        SwirlImage(
            (Image *) Field(image_bloc,1),
            Double_val(degrees),
            exception );
    */


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

/* }}} */
/* {{{ fun_unsharpmaskimage()
 *
 * Image *UnsharpMaskImage(const Image *image, const double radius, const double sigma, const double amount, const double threshold, ExceptionInfo *exception)
 */
CAMLprim value
fun_unsharpmaskimage(
        value image_bloc,
        value radius,
        value sigma,
        value amount,
        value threshold )
{
    CAMLparam5(image_bloc, radius, sigma, amount, threshold);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo
        *exception;

    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    Field(new_image_bloc,1) = (value)
        UnsharpMaskImage(
            (Image *) Field(image_bloc,1),
            Double_val(radius),
            Double_val(sigma),
            Double_val(amount),
            Double_val(threshold),
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

/* }}} */
/* {{{ fun_waveimage()
 *
 * Image *WaveImage(const Image *image, const double amplitude, const double wave_length, ExceptionInfo *exception)
 */
CAMLprim value
fun_waveimage(
        value image_bloc,
        value amplitude,
        value wave_length )
{
    CAMLparam3(image_bloc, amplitude, wave_length);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo
        *exception;

    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    /* TODO update
    Field(new_image_bloc,1) = (value)
        WaveImage(
            (Image *) Field(image_bloc,1),
            Double_val(amplitude),
            Double_val(wave_length),
            exception );
    */


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

/* }}} */
/* {{{ fun_rotateimage()
 *
 * Image *RotateImage(const Image *image, const double degrees, ExceptionInfo *exception)
 */
CAMLprim value
fun_rotateimage(
        value image_bloc,
        value degrees )
{
    CAMLparam2(image_bloc, degrees);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo
        *exception;

    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    Field(new_image_bloc,1) = (value)
        RotateImage(
            (Image *) Field(image_bloc,1),
            Double_val(degrees),
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

/* }}} */
/* {{{ fun_shearimage()
 *
 * Image *ShearImage(const Image *image, const double x_shear, const double y_shear, ExceptionInfo *exception)
 */
CAMLprim value
fun_shearimage(
        value image_bloc,
        value x_shear,
        value y_shear )
{
    CAMLparam3(image_bloc, x_shear, y_shear);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo
        *exception;

    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    Field(new_image_bloc,1) = (value)
        ShearImage(
            (Image *) Field(image_bloc,1),
            Double_val(x_shear),
            Double_val(y_shear),
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

/* }}} */
/* {{{ fun_sampleimage()
 *
 * Image *SampleImage(const Image *image, const unsigned long columns, const unsigned long rows, ExceptionInfo *exception)
 */
CAMLprim value
fun_sampleimage(
        value image_bloc,
        value columns,
        value rows )
{
    CAMLparam3(image_bloc, columns, rows);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo
        *exception;

    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    Field(new_image_bloc,1) = (value)
        SampleImage(
            (Image *) Field(image_bloc,1),
            Long_val(columns),
            Long_val(rows),
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

/* }}} */
/* {{{ fun_scaleimage()
 *
 * Image *ScaleImage(const Image *image, const unsigned long columns, const unsigned long rows, ExceptionInfo *exception)
 */
CAMLprim value
fun_scaleimage(
        value image_bloc,
        value columns,
        value rows )
{
    CAMLparam3(image_bloc, columns, rows);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo
        *exception;

    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    Field(new_image_bloc,1) = (value)
        ScaleImage(
            (Image *) Field(image_bloc,1),
            Long_val(columns),
            Long_val(rows),
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

/* }}} */
/* {{{ fun_thumbnailimage()
 *
 * Image *ThumbnailImage(const Image *image,const unsigned long columns, const unsigned long rows,ExceptionInfo *exception)
 */
CAMLprim value
fun_thumbnailimage(
        value image_bloc,
        value columns,
        value rows )
{
    CAMLparam3(image_bloc, columns, rows);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo
        *exception;

    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    Field(new_image_bloc,1) = (value)
        ThumbnailImage(
            (Image *) Field(image_bloc,1),
            Long_val(columns),
            Long_val(rows),
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

/* }}} */
/* {{{ fun_adaptivethresholdimage()
 *
 * Image *AdaptiveThresholdImage(const Image *image, const unsigned long width, const unsigned long height, const long offset, ExceptionInfo *exception)
 */
CAMLprim value
fun_adaptivethresholdimage(
        value image_bloc,
        value width,
        value height,
        value offset )
{
    CAMLparam4(image_bloc, width, height, offset);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo
        *exception;

    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    Field(new_image_bloc,1) = (value)
        AdaptiveThresholdImage(
            (Image *) Field(image_bloc,1),
            Long_val(width),
            Long_val(height),
            Long_val(offset),
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

/* }}} */
/* {{{ fun_addnoiseimage()
 *
 * Image *AddNoiseImage(const Image *image, const NoiseType noise_type, ExceptionInfo *exception)
 */
CAMLprim value
fun_addnoiseimage(
        value image_bloc,
        value noise_type )
{
    CAMLparam2(image_bloc, noise_type);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo
        *exception;

    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    /* TODO update
    Field(new_image_bloc,1) = (value)
        AddNoiseImage(
            (Image *) Field(image_bloc,1),
            NoiseType_val(noise_type),
            exception );
    */


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

/* }}} */
/* {{{ fun_resizeimage()
 *
 * Image *ResizeImage(Image *image, const unsigned long columns, const unsigned long rows, const FilterTypes filter, const double blur, ExceptionInfo *exception)
 */
CAMLprim value
fun_resizeimage(
        value image_bloc,
        value columns,
        value rows,
        value filter,
        value blur )
{
    CAMLparam5(image_bloc, columns, rows, filter, blur);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo
        *exception;

    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    /* TODO update
    Field(new_image_bloc,1) = (value)
        ResizeImage(
            (Image *) Field(image_bloc,1),
            Long_val(columns),
            Long_val(rows),
            FilterType_val(filter),
            Double_val(blur),
            exception );
    */


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

/* }}} */

/* {{{ fun_enhanceimage()
 *
 * Image *EnhanceImage(const Image *image, ExceptionInfo *exception)
 */
CAMLprim value
fun_enhanceimage(
        value image_bloc )
{
    CAMLparam1(image_bloc);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo
        *exception;

    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    Field(new_image_bloc,1) = (value)
        EnhanceImage(
            (Image *) Field(image_bloc,1),
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

/* }}} */
/* {{{ fun_despeckleimage()
 *
 * Image *DespeckleImage(const Image *image, ExceptionInfo *exception)
 */
CAMLprim value
fun_despeckleimage(
        value image_bloc )
{
    CAMLparam1(image_bloc);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo
        *exception;

    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    Field(new_image_bloc,1) = (value)
        DespeckleImage(
            (Image *) Field(image_bloc,1),
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

/* }}} */
/* {{{ fun_cropimage()
 *
 * Image *CropImage(const Image *image, const RectangleInfo *geometry, ExceptionInfo *exception)
 */
CAMLprim value
fun_cropimage(
        value image_bloc,
        value x,
        value y,
        value width,
        value height )
{
    CAMLparam5(image_bloc, x, y, width, height);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo
        *exception;

    RectangleInfo 
        geometry;

    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    geometry.x  = Long_val(x);
    geometry.y  = Long_val(y);
    geometry.width  = Long_val(width);
    geometry.height = Long_val(height);

    Field(new_image_bloc,1) = (value)
        CropImage(
            (Image *) Field(image_bloc,1),
            &geometry,
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

/* }}} */
/* {{{ fun_minifyimage()
 *
 * Image *MinifyImage(Image *image, ExceptionInfo *exception)
 */
CAMLprim value
fun_minifyimage(
        value image_bloc )
{
    CAMLparam1(image_bloc);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo
        *exception;

    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    Field(new_image_bloc,1) = (value)
        MinifyImage(
            (Image *) Field(image_bloc,1),
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

/* }}} */
/* {{{ fun_magnifyimage()
 *
 * Image *MagnifyImage(Image *image, ExceptionInfo *exception)
 */
CAMLprim value
fun_magnifyimage(
        value image_bloc )
{
    CAMLparam1(image_bloc);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo
        *exception;

    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    Field(new_image_bloc,1) = (value)
        MagnifyImage(
            (Image *) Field(image_bloc,1),
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

/* }}} */
/* {{{ fun_flipimage()
 *
 * Image *FlipImage(Image *image, ExceptionInfo *exception)
 */
CAMLprim value
fun_flipimage(
        value image_bloc )
{
    CAMLparam1(image_bloc);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo
        *exception;

    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    Field(new_image_bloc,1) = (value)
        FlipImage(
            (Image *) Field(image_bloc,1),
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

/* }}} */
/* {{{ fun_flopimage()
 *
 * Image *FlopImage(Image *image, ExceptionInfo *exception)
 */
CAMLprim value
fun_flopimage(
        value image_bloc )
{
    CAMLparam1(image_bloc);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo
        *exception;

    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    Field(new_image_bloc,1) = (value)
        FlopImage(
            (Image *) Field(image_bloc,1),
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

/* }}} */

/* {{{ fun_spliceimage()
 *
 * Image *SpliceImage(const Image *image, const RectangleInfo *chop_info, ExceptionInfo *exception)
 */
CAMLprim value
fun_spliceimage(
        value image_bloc,
        value x,
        value y,
        value width,
        value height )
{
    CAMLparam5(image_bloc, x, y, width, height);
    CAMLlocal1(new_image_bloc);

    RectangleInfo 
        chop_info;

    ExceptionInfo
        *exception;

    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    chop_info.x = Long_val(x);
    chop_info.y = Long_val(y);
    chop_info.width  = Long_val(width);
    chop_info.height = Long_val(height);

    Field(new_image_bloc,1) = (value)
        SpliceImage(
            (Image *) Field(image_bloc,1),
            &chop_info,
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

/* }}} */

/* {{{ fun_orderedditherimage() 
 *
 * MagickBooleanType OrderedDitherImage(Image *image)
 */
CAMLprim value
fun_orderedditherimage( value image_bloc )
{
    CAMLparam1(image_bloc);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo *exception;
    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    Field(new_image_bloc,1) = (value) CloneImage(
            (Image *) Field(image_bloc,1),
            0, 0, 1,
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


    MagickBooleanType status;
    /* TODO update
    status = OrderedDitherImage(
                (Image *) Field(new_image_bloc,1) );
    */

    if (status == MagickFalse) {
        if ( Field(new_image_bloc,1) ) {
            DestroyImage( (Image *) Field(new_image_bloc,1) );
        }
        caml_failwith("ordered_dither failed");
    }

    CAMLreturn( new_image_bloc );
}
/* }}} */

/* {{{ fun_negateimage() 
 *
 * MagickBooleanType NegateImage(Image *, const MagickBooleanType)
 */
CAMLprim value
fun_negateimage(
            value image_bloc,
            value grayscale )
{
    CAMLparam2(image_bloc, grayscale);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo *exception;
    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    Field(new_image_bloc,1) = (value) CloneImage(
            (Image *) Field(image_bloc,1),
            0, 0, 1,
            exception );

    if (exception->severity != UndefinedException)
    {
        if ( Field(new_image_bloc,1) )
        {
            DestroyImage( (Image *) Field(new_image_bloc,1) );
        }
        caml_failwith( exception->reason );
    }


    MagickBooleanType status;

    status = NegateImage(
                (Image *) Field(new_image_bloc,1),
                MagickBoolean_val(grayscale), exception );

    DestroyExceptionInfo(exception);

    if (status == MagickFalse) {
        if ( Field(new_image_bloc,1) ) {
            DestroyImage( (Image *) Field(new_image_bloc,1) );
        }
        caml_failwith("negate failed");
    }

    CAMLreturn( new_image_bloc );
}
/* }}} */
/* {{{ fun_contrastimage() 
 *
 * MagickBooleanType ContrastImage(Image *image, const MagickBooleanType sharpen)
 */
CAMLprim value
fun_contrastimage(
            value image_bloc,
            value sharpen )
{
    CAMLparam2(image_bloc, sharpen);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo *exception;
    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    Field(new_image_bloc,1) = (value) CloneImage(
            (Image *) Field(image_bloc,1),
            0, 0, 1, exception );

    if (exception->severity != UndefinedException) {
        if ( Field(new_image_bloc,1) ) {
            DestroyImage( (Image *) Field(new_image_bloc,1) );
        }
        caml_failwith( exception->reason );
    }

    MagickBooleanType status;

    status = ContrastImage(
                (Image *) Field(new_image_bloc,1),
                MagickBoolean_val(sharpen), exception );

    DestroyExceptionInfo(exception);

    if (status == MagickFalse) {
        if ( Field(new_image_bloc,1) ) {
            DestroyImage( (Image *) Field(new_image_bloc,1) );
        }
        caml_failwith("Magick.Fun.contrast failed");
    }

    CAMLreturn( new_image_bloc );
}
/* }}} */
/* {{{ fun_equalizeimage() 
 *
 * MagickBooleanType EqualizeImage(Image *image)
 */
CAMLprim value
fun_equalizeimage(
            value image_bloc )
{
    CAMLparam1(image_bloc);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo *exception;
    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    Field(new_image_bloc,1) = (value) CloneImage(
            (Image *) Field(image_bloc,1),
            0, 0, 1, exception );

    if (exception->severity != UndefinedException) {
        if ( Field(new_image_bloc,1) ) {
            DestroyImage( (Image *) Field(new_image_bloc,1) );
        }
        caml_failwith( exception->reason );
    }
    DestroyExceptionInfo(exception);


    MagickBooleanType status;
    /* TODO update
    status = EqualizeImage(
                (Image *) Field(new_image_bloc,1)
                );
    */

    if (status == MagickFalse) {
        if ( Field(new_image_bloc,1) ) {
            DestroyImage( (Image *) Field(new_image_bloc,1) );
        }
        caml_failwith("Magick.Fun.equalize failed");
    }

    CAMLreturn( new_image_bloc );
}
/* }}} */
/* {{{ fun_normalizeimage() 
 *
 * MagickBooleanType NormalizeImage(Image *image)
 */
CAMLprim value
fun_normalizeimage(
            value image_bloc )
{
    CAMLparam1(image_bloc);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo *exception;
    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    Field(new_image_bloc,1) = (value) CloneImage(
            (Image *) Field(image_bloc,1),
            0, 0, 1, exception );

    if (exception->severity != UndefinedException) {
        if ( Field(new_image_bloc,1) ) {
            DestroyImage( (Image *) Field(new_image_bloc,1) );
        }
        caml_failwith( exception->reason );
    }
    DestroyExceptionInfo(exception);


    MagickBooleanType status;
    /* TODO update
    status = NormalizeImage(
                (Image *) Field(new_image_bloc,1)
                );
    */

    if (status == MagickFalse) {
        if ( Field(new_image_bloc,1) ) {
            DestroyImage( (Image *) Field(new_image_bloc,1) );
        }
        caml_failwith("Magick.Fun.normalize failed");
    }

    CAMLreturn( new_image_bloc );
}
/* }}} */
/* {{{ fun_blackthresholdimage() 
 *
 * MagickBooleanType BlackThresholdImage(Image *image, const char *threshold)
 */
CAMLprim value
fun_blackthresholdimage(
            value image_bloc,
            value threshold )
{
    CAMLparam2(image_bloc, threshold);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo *exception;
    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    Field(new_image_bloc,1) = (value) CloneImage(
            (Image *) Field(image_bloc,1),
            0, 0, 1, exception );

    if (exception->severity != UndefinedException) {
        if ( Field(new_image_bloc,1) ) {
            DestroyImage( (Image *) Field(new_image_bloc,1) );
        }
        caml_failwith( exception->reason );
    }
    DestroyExceptionInfo(exception);


    MagickBooleanType status;
    /* TODO update
    status = BlackThresholdImage(
                (Image *) Field(new_image_bloc,1),
                String_val(threshold) );
    */

    if (status == MagickFalse) {
        if ( Field(new_image_bloc,1) ) {
            DestroyImage( (Image *) Field(new_image_bloc,1) );
        }
        caml_failwith("Magick.Fun.black_threshold failed");
    }

    CAMLreturn( new_image_bloc );
}
/* }}} */
/* {{{ fun_whitethresholdimage() 
 *
 * MagickBooleanType WhiteThresholdImage(Image *image, const char *threshold)
 */
CAMLprim value
fun_whitethresholdimage(
            value image_bloc,
            value threshold )
{
    CAMLparam2(image_bloc, threshold);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo *exception;
    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    Field(new_image_bloc,1) = (value) CloneImage(
            (Image *) Field(image_bloc,1),
            0, 0, 1, exception );

    if (exception->severity != UndefinedException) {
        if ( Field(new_image_bloc,1) ) {
            DestroyImage( (Image *) Field(new_image_bloc,1) );
        }
        caml_failwith( exception->reason );
    }
    DestroyExceptionInfo(exception);


    MagickBooleanType status;
    /* TODO update
    status = WhiteThresholdImage(
                (Image *) Field(new_image_bloc,1),
                String_val(threshold) );
    */

    if (status == MagickFalse) {
        if ( Field(new_image_bloc,1) ) {
            DestroyImage( (Image *) Field(new_image_bloc,1) );
        }
        caml_failwith("Magick.Fun.white_threshold failed");
    }

    CAMLreturn( new_image_bloc );
}
/* }}} */
/* {{{ fun_cyclecolormapimage() 
 *
 * MagickBooleanType CycleColormapImage(Image *image, const long displace)
 */
CAMLprim value
fun_cyclecolormapimage(
            value image_bloc,
            value displace )
{
    CAMLparam2(image_bloc, displace);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo *exception;
    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    Field(new_image_bloc,1) = (value) CloneImage(
            (Image *) Field(image_bloc,1),
            0, 0, 1, exception );

    if (exception->severity != UndefinedException) {
        if ( Field(new_image_bloc,1) ) {
            DestroyImage( (Image *) Field(new_image_bloc,1) );
        }
        caml_failwith( exception->reason );
    }
    DestroyExceptionInfo(exception);


    MagickBooleanType status;
    /* TODO update
    status = CycleColormapImage(
                (Image *) Field(new_image_bloc,1),
                Long_val(displace) );
    */

    if (status == MagickFalse) {
        if ( Field(new_image_bloc,1) ) {
            DestroyImage( (Image *) Field(new_image_bloc,1) );
        }
        caml_failwith("Magick.Fun.cyclecolormap failed");
    }

    CAMLreturn( new_image_bloc );
}
/* }}} */
/* {{{ fun_modulateimage() 
 *
 * MagickBooleanType ModulateImage(Image *image, const char *modulate)
 */
CAMLprim value
fun_modulateimage(
            value image_bloc,
            value modulate )
{
    CAMLparam2(image_bloc, modulate);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo *exception;
    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    Field(new_image_bloc,1) = (value) CloneImage(
            (Image *) Field(image_bloc,1),
            0, 0, 1, exception );

    if (exception->severity != UndefinedException) {
        if ( Field(new_image_bloc,1) ) {
            DestroyImage( (Image *) Field(new_image_bloc,1) );
        }
        caml_failwith( exception->reason );
    }
    DestroyExceptionInfo(exception);


    MagickBooleanType status;
    /* TODO update
    status = ModulateImage(
                (Image *) Field(new_image_bloc,1),
                String_val(modulate) );
    */

    if (status == MagickFalse) {
        if ( Field(new_image_bloc,1) ) {
            DestroyImage( (Image *) Field(new_image_bloc,1) );
        }
        caml_failwith("Magick.Fun.modulate failed");
    }

    CAMLreturn( new_image_bloc );
}
/* }}} */
/* {{{ fun_solarizeimage() 
 *
 * MagickBooleanType SolarizeImage(Image *image, const double threshold)
 */
CAMLprim value
fun_solarizeimage(
            value image_bloc,
            value threshold )
{
    CAMLparam2(image_bloc, threshold);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo *exception;
    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    Field(new_image_bloc,1) = (value) CloneImage(
            (Image *) Field(image_bloc,1),
            0, 0, 1, exception );

    if (exception->severity != UndefinedException) {
        if ( Field(new_image_bloc,1) ) {
            DestroyImage( (Image *) Field(new_image_bloc,1) );
        }
        caml_failwith( exception->reason );
    }
    DestroyExceptionInfo(exception);


    MagickBooleanType status;
    /* TODO update
    status = SolarizeImage(
                (Image *) Field(new_image_bloc,1),
                Double_val(threshold) );
    */

    if (status == MagickFalse) {
        if ( Field(new_image_bloc,1) ) {
            DestroyImage( (Image *) Field(new_image_bloc,1) );
        }
        caml_failwith("Magick.Fun.solarize failed");
    }

    CAMLreturn( new_image_bloc );
}
/* }}} */
/* {{{ fun_stripimage() 
 *
 * MagickBooleanType StripImage(Image *image)
 */
CAMLprim value
fun_stripimage(
            value image_bloc )
{
    CAMLparam1(image_bloc);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo *exception;
    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    Field(new_image_bloc,1) = (value) CloneImage(
            (Image *) Field(image_bloc,1),
            0, 0, 1, exception );

    if (exception->severity != UndefinedException) {
        if ( Field(new_image_bloc,1) ) {
            DestroyImage( (Image *) Field(new_image_bloc,1) );
        }
        caml_failwith( exception->reason );
    }
    DestroyExceptionInfo(exception);


    MagickBooleanType status;
    /* TODO update
    status = StripImage(
                (Image *) Field(new_image_bloc,1)
                );
    */

    if (status == MagickFalse) {
        if ( Field(new_image_bloc,1) ) {
            DestroyImage( (Image *) Field(new_image_bloc,1) );
        }
        caml_failwith("Magick.Fun.strip failed");
    }

    CAMLreturn( new_image_bloc );
}
/* }}} */
/* {{{ fun_levelimage() 
 *
 * MagickBooleanType LevelImage(Image *image, const char *levels)
 */
CAMLprim value
fun_levelimage(
            value image_bloc,
            value levels )
{
    CAMLparam2(image_bloc, levels);
    CAMLlocal1(new_image_bloc);

    ExceptionInfo *exception;
    exception = AcquireExceptionInfo();

    new_image_bloc = caml_alloc_final(2, finalize_image, sizeof(Image), MAX_AMOUNT);  /* finalize_image() */

    Field(new_image_bloc,1) = (value) CloneImage(
            (Image *) Field(image_bloc,1),
            0, 0, 1, exception );

    if (exception->severity != UndefinedException) {
        if ( Field(new_image_bloc,1) ) {
            DestroyImage( (Image *) Field(new_image_bloc,1) );
        }
        caml_failwith( exception->reason );
    }
    DestroyExceptionInfo(exception);


    MagickBooleanType status;
    /* TODO update
    status = LevelImage(
                (Image *) Field(new_image_bloc,1),
                String_val(levels) );
    */

    if (status == MagickFalse) {
        if ( Field(new_image_bloc,1) ) {
            DestroyImage( (Image *) Field(new_image_bloc,1) );
        }
        caml_failwith("Magick.Fun.level failed");
    }

    CAMLreturn( new_image_bloc );
}
/* }}} */

/* vim: sw=4 ts=4 sts=4 et fdm=marker
 */
