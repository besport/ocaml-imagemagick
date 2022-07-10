/* {{{ COPYING 
 *
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
 * |
 * +-----------------------------------------------------------------+
 * | Author: Florent Monnier                                         |
 * | Contact::email: 'fmonnie'+'r@linux-nantes.org'                  |
 * | Thanks to Matthieu Dubuget for his help with OCamlMakefile use. |
 * +-----------------------------------------------------------------+
 *
 * }}} */

int MagickBoolean_val(value);

CAMLprim value imper_flipimage(value);
CAMLprim value imper_flopimage(value);
CAMLprim value imper_magnifyimage(value);
CAMLprim value imper_minifyimage(value);
CAMLprim value imper_enhanceimage(value);
CAMLprim value imper_trimimage(value);
CAMLprim value imper_despeckle(value);

CAMLprim value imper_deconstructimages(value);
CAMLprim value imper_coalesceimages(value);
CAMLprim value imper_flattenimages(value);


CAMLprim value imper_negateimage(value, value);
CAMLprim value imper_contrastimage(value, value);
CAMLprim value imper_equalizeimage(value);
CAMLprim value imper_normalizeimage(value);
CAMLprim value imper_blackthresholdimage(value, value);
CAMLprim value imper_cyclecolormapimage(value, value);
CAMLprim value imper_modulateimage(value, value);
CAMLprim value imper_solarizeimage(value, value);
CAMLprim value imper_stripimage(value);



CAMLprim value imper_blurimage(value, value, value);
CAMLprim value imper_charcoalimage(value, value, value);
CAMLprim value imper_edgeimage(value, value);
CAMLprim value imper_embossimage(value, value, value);
CAMLprim value imper_gaussianblurimage(value, value, value);
CAMLprim value imper_implodeimage(value, value);
CAMLprim value imper_medianfilterimage(value, value);
CAMLprim value imper_motionblurimage(value, value, value, value);
CAMLprim value imper_oilpaintimage(value, value);
CAMLprim value imper_reducenoiseimage(value, value);
CAMLprim value imper_rollimage(value, value, value);
CAMLprim value imper_shadeimage(value, value, value, value);
CAMLprim value imper_sharpenimage(value, value, value);
CAMLprim value imper_spreadimage(value, value);
CAMLprim value imper_swirlimage(value, value);
CAMLprim value imper_unsharpmaskimage(value, value, value, value, value);
CAMLprim value imper_waveimage(value, value, value);

CAMLprim value imper_rotateimage(value, value);
CAMLprim value imper_shearimage(value, value, value);
CAMLprim value imper_sampleimage(value, value, value);
CAMLprim value imper_scaleimage(value, value, value);
CAMLprim value imper_thumbnailimage(value, value, value);

CAMLprim value imper_adaptivethresholdimage(value, value, value, value);

CAMLprim value imper_cropimage(value, value, value, value, value);
CAMLprim value imper_chopimage(value, value, value, value, value);

CAMLprim value imper_blurimagechannel(value, value, value, value);
CAMLprim value imper_gaussianblurimagechannel(value, value, value, value);
CAMLprim value imper_bilevelimagechannel(value, value, value);
CAMLprim value imper_sharpenimagechannel(value, value, value, value);


CAMLprim value imper_addnoiseimage(value, value);


CAMLprim value imper_resizeimage(value, value, value, value, value);

CAMLprim value imper_orderedditherimage(value);
CAMLprim value imper_compressimagecolormap(value);
CAMLprim value imper_posterizeimage(value, value, value);
CAMLprim value imper_mapimage(value, value, value);




CAMLprim value fun_blurimage(value, value, value);
CAMLprim value fun_charcoalimage(value, value, value);
CAMLprim value fun_edgeimage(value, value);
CAMLprim value fun_embossimage(value, value, value);
CAMLprim value fun_gaussianblurimage(value, value, value);
CAMLprim value fun_implodeimage(value, value);
CAMLprim value fun_medianfilterimage(value, value);
CAMLprim value fun_motionblurimage(value, value, value, value);
CAMLprim value fun_oilpaintimage(value, value);
CAMLprim value fun_reducenoiseimage(value, value);
CAMLprim value fun_rollimage(value, value, value);
CAMLprim value fun_shadeimage(value, value, value, value);
CAMLprim value fun_sharpenimage(value, value, value);
CAMLprim value fun_spreadimage(value, value);
CAMLprim value fun_swirlimage(value, value);
CAMLprim value fun_unsharpmaskimage(value, value, value, value, value);
CAMLprim value fun_waveimage(value, value, value);
CAMLprim value fun_rotateimage(value, value);
CAMLprim value fun_shearimage(value, value, value);
CAMLprim value fun_sampleimage(value, value, value);
CAMLprim value fun_scaleimage(value, value, value);
CAMLprim value fun_thumbnailimage(value, value, value);
CAMLprim value fun_adaptivethresholdimage(value, value, value, value);
CAMLprim value fun_blurimagechannel(value, value, value, value);
CAMLprim value fun_gaussianblurimagechannel(value, value, value, value);
CAMLprim value fun_addnoiseimage(value, value);
CAMLprim value fun_resizeimage(value, value, value, value, value);




/* vim: fdm=marker
 */
