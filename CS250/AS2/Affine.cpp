/*
Name : Gyuhyeon, Lee
Assignment Number : 1
Course name : CS250
Term : Spring 2018
*/

#include "Affine.h"

Hcoord::Hcoord(float X, float Y, float Z, float W)
	:x(X), y(Y), z(Z), w(W)
{
	// To elminate -0.0f, check near and then put it!
	if (near(x, 0.0f))
	{
		x = 0.0f;
	}
	if (near(y, 0.0f))
	{
		y = 0.0f;
	}
	if (near(z, 0.0f))
	{
		z = 0.0f;
	}
	if (near(w, 0.0f))
	{
		w = 0.0f;
	}
}

Point::Point(float X, float Y, float Z)
	:Hcoord(X, Y, Z, 1.0f)
{
}

Vector::Vector(float X, float Y, float Z)
	:Hcoord(X, Y, Z, 0.0f)
{
}

Affine::Affine(void)
{
	row[0] = Hcoord(0.0f, 0.0f, 0.0f, 0.0f);
	row[1] = Hcoord(0.0f, 0.0f, 0.0f, 0.0f);
	row[2] = Hcoord(0.0f, 0.0f, 0.0f, 0.0f);
	row[3] = Hcoord(0.0f, 0.0f, 0.0f, 1.0f);
}

Affine::Affine(const Vector& Lx, const Vector& Ly, const Vector& Lz, const Point& D)
{
	row[0] = Hcoord(Lx.x, Ly.x, Lz.x, D.x);
	row[1] = Hcoord(Lx.y, Ly.y, Lz.y, D.y);
	row[2] = Hcoord(Lx.z, Ly.z, Lz.z, D.z);
	row[3] = Hcoord(Lx.w, Ly.w, Lz.w, D.w);
}

Hcoord operator+(const Hcoord& u, const Hcoord& v)
{
	Hcoord result;

	result.x = u.x + v.x;
	result.y = u.y + v.y;
	result.z = u.z + v.z;
	result.w = u.w + v.w;

	return result;
}

Hcoord operator-(const Hcoord& u, const Hcoord& v)
{
	Hcoord result;

	result.x = u.x - v.x;
	result.y = u.y - v.y;
	result.z = u.z - v.z;
	result.w = u.w - v.w;

	return result;
}

Hcoord operator-(const Hcoord& v)
{
	Hcoord result = v;

	result.x *= -1.0f;
	result.y *= -1.0f;
	result.z *= -1.0f;
	result.w *= -1.0f;

	return result;
}

Hcoord operator*(float r, const Hcoord& v)
{
	Hcoord result = v;

	result.x *= r;
	result.y *= r;
	result.z *= r;
	result.w *= r;

	return result;
}

Hcoord operator*(const Matrix& A, const Hcoord& v)
{
	Hcoord result;

	result.x = A.row[0].x*v.x + A.row[0].y*v.y + A.row[0].z*v.z + A.row[0].w*v.w;
	result.y = A.row[1].x*v.x + A.row[1].y*v.y + A.row[1].z*v.z + A.row[1].w*v.w;
	result.z = A.row[2].x*v.x + A.row[2].y*v.y + A.row[2].z*v.z + A.row[2].w*v.w;
	result.w = A.row[3].x*v.x + A.row[3].y*v.y + A.row[3].z*v.z + A.row[3].w*v.w;

	return result;
}

Matrix operator*(const Matrix& A, const Matrix& B)
{
	Matrix result;

	result.row[0] = Hcoord(A.row[0].x*B.row[0].x + A.row[0].y*B.row[1].x + A.row[0].z*B.row[2].x + A.row[0].w*B.row[3].x,
							A.row[0].x*B.row[0].y + A.row[0].y*B.row[1].y + A.row[0].z*B.row[2].y + A.row[0].w*B.row[3].y,
							A.row[0].x*B.row[0].z + A.row[0].y*B.row[1].z + A.row[0].z*B.row[2].z + A.row[0].w*B.row[3].z,
							A.row[0].x*B.row[0].w + A.row[0].y*B.row[1].w + A.row[0].z*B.row[2].w + A.row[0].w*B.row[3].w);

	result.row[1] = Hcoord(A.row[1].x*B.row[0].x + A.row[1].y*B.row[1].x + A.row[1].z*B.row[2].x + A.row[1].w*B.row[3].x,
							A.row[1].x*B.row[0].y + A.row[1].y*B.row[1].y + A.row[1].z*B.row[2].y + A.row[1].w*B.row[3].y,
							A.row[1].x*B.row[0].z + A.row[1].y*B.row[1].z + A.row[1].z*B.row[2].z + A.row[1].w*B.row[3].z,
							A.row[1].x*B.row[0].w + A.row[1].y*B.row[1].w + A.row[1].z*B.row[2].w + A.row[1].w*B.row[3].w);

	result.row[2] = Hcoord(A.row[2].x*B.row[0].x + A.row[2].y*B.row[1].x + A.row[2].z*B.row[2].x + A.row[2].w*B.row[3].x,
							A.row[2].x*B.row[0].y + A.row[2].y*B.row[1].y + A.row[2].z*B.row[2].y + A.row[2].w*B.row[3].y,
							A.row[2].x*B.row[0].z + A.row[2].y*B.row[1].z + A.row[2].z*B.row[2].z + A.row[2].w*B.row[3].z,
							A.row[2].x*B.row[0].w + A.row[2].y*B.row[1].w + A.row[2].z*B.row[2].w + A.row[2].w*B.row[3].w);

	result.row[3] = Hcoord(A.row[3].x*B.row[0].x + A.row[3].y*B.row[1].x + A.row[3].z*B.row[2].x + A.row[3].w*B.row[3].x,
							A.row[3].x*B.row[0].y + A.row[3].y*B.row[1].y + A.row[3].z*B.row[2].y + A.row[3].w*B.row[3].y,
							A.row[3].x*B.row[0].z + A.row[3].y*B.row[1].z + A.row[3].z*B.row[2].z + A.row[3].w*B.row[3].z,
							A.row[3].x*B.row[0].w + A.row[3].y*B.row[1].w + A.row[3].z*B.row[2].w + A.row[3].w*B.row[3].w);

	return result;
}

float dot(const Vector& u, const Vector& v)
{
	float result;

	result = u.x*v.x + u.y*v.y + u.z*v.z + u.w*v.w;

	return result;
}

float abs(const Vector& v)
{
	float result = sqrt(dot(v, v));

	return result;
}

Vector normalize(const Vector& v)
{
	float length = abs(v);
	Vector result = v;

	result.x /= length;
	result.y /= length;
	result.z /= length;

	return result;
}
Vector cross(const Vector& u, const Vector& v)
{
	Vector result;

	result.x = u.y*v.z - u.z*v.y;
	result.y = -u.x*v.z + u.z*v.x;
	result.z = u.x*v.y - u.y*v.x;
	result.w = 0.0f;

	return result;
}

Affine rotate(float t, const Vector& v)
{
	Affine result;
	
	float cost = cos(t);
	float sint = sin(t);
	float oneMcost = 1.0f - cost;
	Vector nv = normalize(v);
	
	result.row[0] = Hcoord(cost + oneMcost*nv.x*nv.x,
							oneMcost*nv.x*nv.y - sint*nv.z,
							oneMcost*nv.x*nv.z + sint*nv.y,
							0.0f);
	result.row[1] = Hcoord(oneMcost*nv.x*nv.y + sint*nv.z,
							cost + oneMcost*nv.y*nv.y,
							oneMcost*nv.y*nv.z - sint*nv.x,
							0.0f);
	result.row[2] = Hcoord(oneMcost*nv.x*nv.z - sint*nv.y,
							oneMcost*nv.y*nv.z + sint*nv.x,
							cost + oneMcost*nv.z*nv.z,
							0.0f);
	result.row[3] = Hcoord(0.0f, 0.0f, 0.0f, 1.0f);

	return result;
}
Affine translate(const Vector& v)
{
	Affine result;

	result.row[0] = Hcoord(1.0f, 0.0f, 0.0f, v.x);
	result.row[1] = Hcoord(0.0f, 1.0f, 0.0f, v.y);
	result.row[2] = Hcoord(0.0f, 0.0f, 1.0f, v.z);
	result.row[3] = Hcoord(0.0f, 0.0f, 0.0f, 1.0f);

	return result;
}

Affine scale(float r)
{
	Affine result;

	result.row[0] = Hcoord(r, 0.0f, 0.0f, 0.0f);
	result.row[1] = Hcoord(0.0f, r, 0.0f, 0.0f);
	result.row[2] = Hcoord(0.0f, 0.0f, r, 0.0f);
	result.row[3] = Hcoord(0.0f, 0.0f, 0.0f, 1.0f);

	return result;
}
Affine scale(float rx, float ry, float rz)
{
	Affine result;

	result.row[0] = Hcoord(rx, 0.0f, 0.0f, 0.0f);
	result.row[1] = Hcoord(0.0f, ry, 0.0f, 0.0f);
	result.row[2] = Hcoord(0.0f, 0.0f, rz, 0.0f);
	result.row[3] = Hcoord(0.0f, 0.0f, 0.0f, 1.0f);

	return result;
}
Affine inverse(const Affine& A)
{
	Affine result;

	float d = A.row[0].x*A.row[1].y*A.row[2].z + 
				A.row[0].y*A.row[1].z*A.row[2].x + 
				A.row[0].z*A.row[1].x*A.row[2].y - 
				A.row[2].x*A.row[1].y*A.row[0].z - 
				A.row[2].y*A.row[1].z*A.row[0].x - 
				A.row[2].z*A.row[1].x*A.row[0].y;

	float m00 = (A.row[1].y*A.row[2].z - A.row[2].y*A.row[1].z) / d;
	float m01 = (A.row[2].y*A.row[0].z - A.row[0].y*A.row[2].z) / d;
	float m02 = (A.row[0].y*A.row[1].z - A.row[0].z*A.row[1].y) / d;
	float m10 = (A.row[2].x*A.row[1].z - A.row[1].x*A.row[2].z) / d;
	float m11 = (A.row[0].x*A.row[2].z - A.row[0].z*A.row[2].x) / d;
	float m12 = (A.row[0].z*A.row[1].x - A.row[0].x*A.row[1].z) / d;
	float m20 = (A.row[1].x*A.row[2].y - A.row[2].x*A.row[1].y) / d;
	float m21 = (A.row[2].x*A.row[0].y - A.row[0].x*A.row[2].y) / d;
	float m22 = (A.row[0].x*A.row[1].y - A.row[0].y*A.row[1].x) / d;

	float b0 = A.row[0].w;
	float b1 = A.row[1].w;
	float b2 = A.row[2].w;

	result.row[0] = Hcoord(m00, m01, m02, -m00*b0 - m01*b1 - m02*b2);
	result.row[1] = Hcoord(m10, m11, m12, -m10*b0 - m11*b1 - m12*b2);
	result.row[2] = Hcoord(m20, m21, m22, -m20*b0 - m21*b1 - m22*b2);
	result.row[3] = Hcoord(0.0f, 0.0f, 0.0f, 1.0f);

	return result;
}