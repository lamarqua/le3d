/**
	\file simd.h
	\brief LightEngine 3D: SIMD constants / types and intrinsic definitions
	\brief INTEL based platforms
	\author Frederic Meslin (fred@fredslab.net)
	\twitter @marzacdev
	\website http://fredslab.net
	\copyright Frederic Meslin 2015 - 2017
	\version 1.3

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

#ifndef LE_SIMD_H
#define LE_SIMD_H

	#include "xmmintrin.h"
	#include "emmintrin.h"
	#include "smmintrin.h"

	typedef float V4SF __attribute__ ((vector_size (16)));
	typedef union {V4SF v; float f[4];} v4sf;

	typedef int32_t V2SI __attribute__ ((vector_size (8)));
	typedef union {V2SI v; int32_t i[2];} v2si;

	typedef int32_t V4SI __attribute__ ((vector_size (16)));
	typedef union {V4SI v; int32_t i[4];} v4si;

#endif