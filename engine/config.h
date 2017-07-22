/**
	\file config.h
	\brief LightEngine 3D: General engine configuration file
	\brief All platforms implementation
	\author Frederic Meslin (fred@fredslab.net)
	\twitter @marzacdev
	\website http://fredslab.net
	\copyright Frederic Meslin 2015 - 2017
	\version 1.1

	The MIT License (MIT)
	Copyright (c) 2017 Fr�d�ric Meslin

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#ifndef LE_CONFIG_H
#define LE_CONFIG_H

/** Engine configuration */
	#define LE_MAX_FILE_EXTENSION		8						/** Maximum file extension string length */
	#define LE_MAX_FILE_NAME			128						/** Maximum file name string length */
	#define LE_MAX_FILE_PATH			256						/** Maximum file path string length */

/** Data caches */
	#define LE_BMPCACHE_SLOTS			1024					/** Maximum number of bitmaps in cache */
	#define LE_MESHCACHE_SLOTS			1024					/** Maximum number of meshes in cache */

/** Bitmap management */
	#define LE_BMP_CHECKCOORDS 			1						/** Check coordinated on bitmap operations */

/** Wavefront object parser */
	#define LE_OBJ_MAX_NAME				256						/** Wavefront object maximum name string length */
	#define LE_OBJ_MAX_LINE				1024					/** Wavefront object maximum file line length */
	#define LE_OBJ_MAX_PATH				256						/** Wavefront object maximum path string length */

/** Renderer configuration */
	#define LE_RENDERER_FRONT			-0.5f					/** Front clipping plane */
	#define LE_RENDERER_BACK			-32768.0f				/** Back clipping plane */
	#define LE_RENDERER_FOV				65.0f					/** Default field of view */
	#define LE_RENDERER_3DFRUSTRUM		1						/** Use a 3D frustrum to clip triangles */
	#define LE_RENDERER_2DFRAME			0						/** Use a 2D frame to clip triangles */

	#define LE_RENDERER_ZTEX			1						/** Enable perspective correction on texture mapping */
	#define LE_RENDERER_INTRASTER		1						/** Enable fixed point or floating point rasterizing */

	#define LE_TRILIST_MAX				10000					/** Maximum number of triangles in display list */
	#define LE_VERLIST_MAX				(3 * LE_TRILIST_MAX)	/** Maximum number of vertexes in transformation buffer */

/** Performance optimizations */
	#define LE_USE_SIMD					1						/** Use SIMD (SSE / Neon) vectors */
	#define LE_USE_MMX					0						/** Use MMX acceleration for integer math */
	#define LE_FORCE_16B_ALIGN			1						/** Force 16bit alignment (needed by SSE) */

#endif