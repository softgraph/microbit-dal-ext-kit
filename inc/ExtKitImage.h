/// Yotta module microbit-dal-ext-kit
/**	@package	microbit_dal_ext_kit
*/

/// Image utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_IMAGE_H
#define EXT_KIT_IMAGE_H

///	Define Literal MicroBitImage.
/**
	Example:
	@code
		EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(const, heart, 0,1,0,1,0, 1,1,1,1,1, 1,1,1,1,1, 0,1,1,1,0, 0,0,1,0,0)
	@endcode
	The example above defines a const MicroBitImage named 'heart' with 5 x 5 pixels.
	It is basically equivalent to the following code but the image is not malloc()ed and therefore does not consume any heap space.
	@code
		const MicroBitImage heart("0,1,0,1,0\n1,1,1,1,1\n1,1,1,1,1\n0,1,1,1,0\n0,0,1,0,0\n");
	@endcode
*/
#define EXT_KIT_DEFINE_LITERAL_MICROBIT_IMAGE_5_X_5(	\
		qualifier /* 'const' or 'static const' */,	\
		name,	\
		px00, px01, px02, px03, px04,	\
		px10, px11, px12, px13, px14,	\
		px20, px21, px22, px23, px24,	\
		px30, px31, px32, px33, px34,	\
		px40, px41, px42, px43, px44)	\
	qualifier uint8_t x__ ## name[]		\
		__attribute__ ((aligned (4))) = {	\
		0xff, 0xff, 5, 0, 5, 0,		\
		px00, px01, px02, px03, px04,	\
		px10, px11, px12, px13, px14,	\
		px20, px21, px22, px23, px24,	\
		px30, px31, px32, px33, px34,	\
		px40, px41, px42, px43, px44 };	\
	qualifier MicroBitImage name((ImageData*) x__ ## name);

#endif	// EXT_KIT_IMAGE_H
