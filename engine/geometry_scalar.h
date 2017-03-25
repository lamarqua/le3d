/**
	\file geometry_scalar.h
	\brief LightEngine 3D: Vertex / axis / plan structures
	\brief All platforms implementation (without SIMD support)
	\author Frederic Meslin (fred@fredslab.net)
	\twitter @marzacdev
	\website http://fredslab.net
	\copyright Frederic Meslin 2015 - 2017
	\version 1.0

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

#ifndef LE_GEOMETRY_SCALAR_H
#define LE_GEOMETRY_SCALAR_H

#include "global.h"

#include <math.h>

/*****************************************************************************/
struct Vertex
{
	float x, y, z, w;

	Vertex()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 1.0f;
	}

	Vertex(float px, float py, float pz)
	{
		x = px;
		y = py;
		z = pz;
		w = 1.0f;
	}

	static Vertex spherical(float azi, float inc, float dist)
	{
		Vertex r;
		r.x = cosf(azi) * cosf(inc) * dist;
		r.y = sinf(inc) * dist;
		r.z = -sinf(azi) * cosf(inc) * dist;
		return r;
	}

	Vertex operator + (Vertex v) const
	{
		Vertex r;
		r.x = x + v.x;
		r.y = y + v.y;
		r.z = z + v.z;
		return r;
	}

	Vertex operator += (Vertex v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	Vertex operator - (Vertex v) const
	{
		Vertex r;
		r.x = x - v.x;
		r.y = y - v.y;
		r.z = z - v.z;
		return r;
	}

	Vertex operator - () const
	{
		Vertex r;
		r.x = -x;
		r.y = -y;
		r.z = -z;
		return r;
	}

	Vertex operator -= (Vertex v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	Vertex operator * (Vertex v) const
	{
		Vertex r;
		r.x = x * v.x;
		r.y = y * v.y;
		r.z = z * v.z;
		return r;
	}

	Vertex operator / (Vertex v) const
	{
		Vertex r;
		r.x = x / v.x;
		r.y = y / v.y;
		r.z = z / v.z;
		return r;
	}

	Vertex operator * (float v) const
	{
		Vertex r;
		r.x = x * v;
		r.y = y * v;
		r.z = z * v;
		return r;
	}

	Vertex operator *= (Vertex v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}

	Vertex operator *= (float v)
	{
		x *= v;
		y *= v;
		z *= v;
		return *this;
	}

	bool operator == (Vertex v)
	{
		return x == v.x && y == v.y && z == v.z;
	}


	float dot(Vertex v) const
	{
		return x * v.x + y * v.y + z * v.z;
	}

	Vertex cross(Vertex v) const
	{
		Vertex c;
		c.x = y * v.z - v.y * z;
		c.y = -x * v.z + v.x * z;
		c.z = x * v.y - v.x * y;
		return c;
	}

	Vertex sign() const
	{
		Vertex c;
		c.x = copysignf(1.0f, x);
		c.y = copysignf(1.0f, y);
		c.z = copysignf(1.0f, z);
		c.w = copysignf(1.0f, w);
		return c;
	}

	Vertex round() const
	{
		Vertex c;
		c.x = floorf(x + 0.5f);
		c.y = floorf(y + 0.5f);
		c.z = floorf(z + 0.5f);
		c.w = floorf(w + 0.5f);
		return c;
	}

	Vertex floor() const
	{
		Vertex c;
		c.x = floorf(x);
		c.y = floorf(y);
		c.z = floorf(z);
		c.w = floorf(w);
		return c;
	}

	Vertex normalize()
	{
		float d = norm();
		if (d == 0.0f) {
			x = y = z = 0.0f;
			w = 1.0f;
		}else{
			d = 1.0f / d;
			x *= d;
			y *= d;
			z *= d;
			w *= d;
		}
		return *this;
	}

	float norm()
	{
		return sqrtf(dot(*this));
	}
};

/*****************************************************************************/
struct Axis
{
	Vertex origin;
	Vertex axis;
	float  norm;

	Axis()
	{
		origin.x = 0.0f;
		origin.y = 0.0f;
		origin.z = 0.0f;
		axis.x = 0.0f;
		axis.y = 0.0f;
		axis.z = 1.0f;
		norm = 1.0f;
	}

	Axis(Vertex v1, Vertex v2)
	{
		origin.x = v1.x;
		origin.y = v1.y;
		origin.z = v1.z;
		float dx = v2.x - v1.x;
		float dy = v2.y - v1.y;
		float dz = v2.z - v1.z;
		norm = sqrtf(dx * dx + dy * dy + dz * dz);
		axis.x = dx / norm;
		axis.y = dy / norm;
		axis.z = dz / norm;
	}
};

/*****************************************************************************/
struct Plan
{
	Axis xAxis;
	Axis yAxis;
	Axis zAxis;

	Plan()
	{
		xAxis.axis.x = 1.0f;
		xAxis.axis.y = 0.0f;
		xAxis.axis.z = 0.0f;

		yAxis.axis.x = 0.0f;
		yAxis.axis.y = 1.0f;
		yAxis.axis.z = 0.0f;

		zAxis.axis.x = 0.0f;
		zAxis.axis.y = 0.0f;
		zAxis.axis.z = 1.0f;
	}

	Plan(Vertex v1, Vertex v2, Vertex v3) :
		xAxis(Axis(v1, v2)), yAxis(Axis(v1, v3))
	{

		Vertex tv1, tv2;
		tv1.x = xAxis.axis.z * yAxis.axis.y;
		tv1.y = xAxis.axis.x * yAxis.axis.z;
		tv1.z = xAxis.axis.y * yAxis.axis.x;
		tv2.x = xAxis.axis.y * yAxis.axis.z;
		tv2.y = xAxis.axis.z * yAxis.axis.x;
		tv2.z = xAxis.axis.x * yAxis.axis.y;
		zAxis = Axis(tv1, tv2);
		zAxis.origin.x = v1.x;
		zAxis.origin.y = v1.y;
		zAxis.origin.z = v1.z;
	}
};

/*****************************************************************************/
struct Matrix
{
	float mat[4][4];

	Matrix()
	{
		identity();
	}

	void identity()
	{
		mat[0][0] = 1.0f;
		mat[0][1] = 0.0f;
		mat[0][2] = 0.0f;
		mat[0][3] = 0.0f;

		mat[1][0] = 0.0f;
		mat[1][1] = 1.0f;
		mat[1][2] = 0.0f;
		mat[1][3] = 0.0f;

		mat[2][0] = 0.0f;
		mat[2][1] = 0.0f;
		mat[2][2] = 1.0f;
		mat[2][3] = 0.0f;

		mat[3][0] = 0.0f;
		mat[3][1] = 0.0f;
		mat[3][2] = 0.0f;
		mat[3][3] = 1.0f;
	}

	void zero()
	{
		memset(mat, 0, sizeof(float) * 16);
	}

	void translate(float dx, float dy, float dz)
	{
		mat[0][3] += dx;
		mat[1][3] += dy;
		mat[2][3] += dz;
	}

	void scale(float sx, float sy, float sz)
	{
		Matrix m;
		m.mat[0][0] *= sx;
		m.mat[1][1] *= sy;
		m.mat[2][2] *= sz;
		*this = m * *this;
	}

	void rotate(float ax, float ay, float az)
	{
		rotateY(ay);
		rotateZ(az);
		rotateX(ax);
	}

	void rotateBackUp(Vertex back, Vertex up, float a)
	{
		back.normalize();
		up.normalize();
		Vertex right = up.cross(back);

		Matrix m1;
		m1.mat[0][0] = right.x;
		m1.mat[0][1] = right.y;
		m1.mat[0][2] = right.z;
		m1.mat[0][3] = right.w;
		
		m1.mat[1][0] = up.x;
		m1.mat[1][1] = up.y;
		m1.mat[1][2] = up.z;
		m1.mat[1][3] = up.w;
		
		m1.mat[2][0] = back.x;
		m1.mat[2][1] = back.y;
		m1.mat[2][2] = back.z;
		m1.mat[2][3] = back.w;
		
		Matrix m2;
		m2.rotateY(a);

		Matrix m3;
		m3.mat[0][0] = right.x;
		m3.mat[1][0] = right.y;
		m3.mat[2][0] = right.z;
		m3.mat[3][0] = 0.0f;
		
		m3.mat[0][1] = up.x;
		m3.mat[1][1] = up.y;
		m3.mat[2][1] = up.z;
		m3.mat[3][1] = 0.0f;
		
		m3.mat[0][2] = back.x;
		m3.mat[1][2] = back.y;
		m3.mat[2][2] = back.z;
		m3.mat[3][2] = 0.0f;
		
		m3.mat[0][3] = 0.0f;
		m3.mat[1][3] = 0.0f;
		m3.mat[2][3] = 0.0f;
		m3.mat[3][3] = 1.0f;

		*this = m3 * m2 * m1 * *this;
	}

	void rotateBackRight(Vertex back, Vertex right, float a)
	{
		back.normalize();
		right.normalize();
		Vertex up = back.cross(right);

		Matrix m1;
		m1.mat[0][0] = right.x;
		m1.mat[0][1] = right.y;
		m1.mat[0][2] = right.z;
		m1.mat[0][3] = right.w;
		
		m1.mat[1][0] = up.x;
		m1.mat[1][1] = up.y;
		m1.mat[1][2] = up.z;
		m1.mat[1][3] = up.w;
		
		m1.mat[2][0] = back.x;
		m1.mat[2][1] = back.y;
		m1.mat[2][2] = back.z;
		m1.mat[2][3] = back.w;
		
		Matrix m2;
		m2.rotateY(a);

		Matrix m3;
		m3.mat[0][0] = right.x;
		m3.mat[1][0] = right.y;
		m3.mat[2][0] = right.z;
		m3.mat[3][0] = 0.0f;
		
		m3.mat[0][1] = up.x;
		m3.mat[1][1] = up.y;
		m3.mat[2][1] = up.z;
		m3.mat[3][1] = 0.0f;
		
		m3.mat[0][2] = back.x;
		m3.mat[1][2] = back.y;
		m3.mat[2][2] = back.z;
		m3.mat[3][2] = 1.0f;
		
		m3.mat[3][3] = 0.0f;
		m3.mat[3][3] = 0.0f;
		m3.mat[3][3] = 0.0f;
		m3.mat[3][3] = 1.0f;

		*this = m3 * m2 * m1 * *this;
	}

	void alignBackUp(Vertex back, Vertex up)
	{
		back.normalize();
		up.normalize();
		Vertex right = up.cross(back);

		Matrix m;
		m.mat[0][0] = right.x;
		m.mat[1][0] = right.y;
		m.mat[2][0] = right.z;
		m.mat[3][0] = 0.0f;
		
		m.mat[0][1] = up.x;
		m.mat[1][1] = up.y;
		m.mat[2][1] = up.z;
		m.mat[3][1] = 0.0f;
		
		m.mat[0][2] = back.x;
		m.mat[1][2] = back.y;
		m.mat[2][2] = back.z;
		m.mat[3][2] = 0.0f;
		
		m.mat[0][3] = 0.0f;
		m.mat[1][3] = 0.0f;
		m.mat[2][3] = 0.0f;
		m.mat[3][3] = 1.0f;
		*this = m * *this;
	}

	void alignBackRight(Vertex back, Vertex right)
	{
		back.normalize();
		right.normalize();
		Vertex up = back.cross(right);

		Matrix m;
		m.mat[0][0] = right.x;
		m.mat[1][0] = right.y;
		m.mat[2][0] = right.z;
		m.mat[3][0] = 0.0f;
		
		m.mat[0][1] = up.x;
		m.mat[1][1] = up.y;
		m.mat[2][1] = up.z;
		m.mat[3][1] = 0.0f;
		
		m.mat[0][2] = back.x;
		m.mat[1][2] = back.y;
		m.mat[2][2] = back.z;
		m.mat[3][2] = 0.0f;

		m.mat[0][3] = 0.0f;
		m.mat[1][3] = 0.0f;
		m.mat[2][3] = 0.0f;
		m.mat[3][3] = 1.0f;
		
		*this = m * *this;
	}

	void rotateX(float a)
	{
		Matrix m;
		float c = cosf(a);
		float s = sinf(a);
		m.mat[1][1] = c;
		m.mat[1][2] = -s;
		m.mat[2][1] = s;
		m.mat[2][2] = c;
		*this = m * *this;
	}

	void rotateY(float a)
	{
		Matrix m;
		float c = cosf(a);
		float s = sinf(a);
		m.mat[0][0] = c;
		m.mat[0][2] = s;
		m.mat[2][0] = -s;
		m.mat[2][2] = c;
		*this = m * *this;
	}

	void rotateZ(float a)
	{
		Matrix m;
		float c = cosf(a);
		float s = sinf(a);
		m.mat[0][0] = c;
		m.mat[0][1] = -s;
		m.mat[1][0] = s;
		m.mat[1][1] = c;
		*this = m * *this;
	}

	Matrix inverse3x3()
	{
		float d = mat[0][0]*(mat[1][1]*mat[2][2]-mat[2][1]*mat[1][2])
				- mat[0][1]*(mat[1][0]*mat[2][2]-mat[1][2]*mat[2][0])
                + mat[0][2]*(mat[1][0]*mat[2][1]-mat[1][1]*mat[2][0]);

		Matrix m;
		if (d == 0.0f) {m.zero(); return m;}
		d = 1.0f / d;

		m.mat[0][0] =  (mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2]) * d;
		m.mat[0][1] = -(mat[0][1] * mat[2][2] - mat[2][1] * mat[0][2]) * d;
		m.mat[0][2] =  (mat[0][1] * mat[1][2] - mat[1][1] * mat[0][2]) * d;

		m.mat[1][0] = -(mat[1][0] * mat[2][2] - mat[2][0] * mat[1][2]) * d;
		m.mat[1][1] =  (mat[0][0] * mat[2][2] - mat[2][0] * mat[0][2]) * d;
		m.mat[1][2] = -(mat[0][0] * mat[1][2] - mat[1][0] * mat[0][2]) * d;

		m.mat[2][0] =  (mat[1][0] * mat[2][1] - mat[2][0] * mat[1][1]) * d;
		m.mat[2][1] = -(mat[0][0] * mat[2][1] - mat[2][0] * mat[0][1]) * d;
		m.mat[2][2] =  (mat[0][0] * mat[1][1] - mat[1][0] * mat[0][1]) * d;

		return m;
	}

	Vertex operator * (Vertex v) const
	{
		float x = v.x * mat[0][0] + v.y * mat[0][1] + v.z * mat[0][2] + mat[0][3];
		float y = v.x * mat[1][0] + v.y * mat[1][1] + v.z * mat[1][2] + mat[1][3];
		float z = v.x * mat[2][0] + v.y * mat[2][1] + v.z * mat[2][2] + mat[2][3];
		return Vertex(x, y, z);
	}

	Matrix operator + (Matrix m) const
	{
		Matrix r;
		for (int i = 0; i < 4; i++) {
			r.mat[i][0] = mat[i][0] + m.mat[i][0];
			r.mat[i][1] = mat[i][1] + m.mat[i][1];
			r.mat[i][2] = mat[i][2] + m.mat[i][2];
			r.mat[i][3] = mat[i][3] + m.mat[i][3];
		}
		return r;
	}

	Matrix operator * (Matrix m) const
	{
		Matrix r;
		for (int i = 0; i < 4; i++) {
			r.mat[i][0] = mat[i][0] * m.mat[0][0] + mat[i][1] * m.mat[1][0] + mat[i][2] * m.mat[2][0] + mat[i][3] * m.mat[3][0];
			r.mat[i][1] = mat[i][0] * m.mat[0][1] + mat[i][1] * m.mat[1][1] + mat[i][2] * m.mat[2][1] + mat[i][3] * m.mat[3][1];
			r.mat[i][2] = mat[i][0] * m.mat[0][2] + mat[i][1] * m.mat[1][2] + mat[i][2] * m.mat[2][2] + mat[i][3] * m.mat[3][2];
			r.mat[i][3] = mat[i][0] * m.mat[0][3] + mat[i][1] * m.mat[1][3] + mat[i][2] * m.mat[2][3] + mat[i][3] * m.mat[3][3];
		}
		return r;
	}
};

/*****************************************************************************/
namespace Geo{
	const Vertex up    = Vertex(0.0f, 1.0f, 0.0f);
	const Vertex down  = Vertex(0.0f, -1.0f, 0.0f);
	const Vertex front = Vertex(0.0f, 0.0f, -1.0f);
	const Vertex back  = Vertex(0.0f, 0.0f, 1.0f);
	const Vertex left  = Vertex(-1.0f, 0.0f, 0.0f);
	const Vertex right = Vertex(1.0f, 0.0f, 0.0f);
	const Vertex zero  = Vertex(0.0f, 0.0f, 0.0f);
}

#endif	//LE_GEOMETRY_SCALAR_H