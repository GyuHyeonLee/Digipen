#include "Affine.h"

Hcoord::Hcoord(float X = 0, float Y = 0, float Z = 0, float W = 0)
{
	x = X;
	y = Y;
	z = Z;
	w = W;
}

Point::Point(float X = 0, float Y = 0, float Z = 0)
{
	x = X;
	y = Y;
	z = Z;
	w = 1.0f;
}

Vector::Vector(float X = 0, float Y = 0, float Z = 0)
{
	x = X;
	y = Y;
	z = Z;
	w = 0.0f;
}

Affine::Affine(void)
{
	row[0] = Hcoord(0.0f, 0.0f, 0.0f, 0.0f);
	row[1] = Hcoord(0.0f, 0.0f, 0.0f, 0.0f);
	row[2] = Hcoord(0.0f, 0.0f, 0.0f, 0.0f);
	row[3] = Hcoord(0.0f, 0.0f, 0.0f, 0.0f);
}

Affine::Affine(const Vector& Lx, const Vector& Ly, const Vector& Lz, const Point& D)
{
	row[0] = Hcoord(Lx.x, Ly.x, Lz.x, D.x)
	row[1] = Hcoord(Lx.y, Ly.y, Lz.y, D.y);
	row[2] = Hcoord(Lx.z, Ly.z, Lz.z, D.z);
	row[3] = Hcoord(0.0f, 0.0f, 0.0f, 1.0f);
}

Hcoord operator+(const Hcoord& u, const Hcoord& v)
{
	Hcoord result;

	result.w = u.w + v.w;
	result.x = (u.x + v.x) / result.w;
	result.y = (u.y + v.y) / result.w;
	result.z = (u.z + v.z) / result.w;
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

	result.x *= -1;
	result.y *= -1;
	result.z *= -1;
	result.w *= -1;

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

	result.x = v.x * A[1].x + v.y * A[1].y + v.z * A[1].z + v.w + A[1].w;
	result.y = v.x * A[2].x + v.y * A[2].y + v.z * A[2].z + v.w + A[2].w;
	result.z = v.x * A[3].x + v.y * A[3].y + v.z * A[3].z + v.w + A[3].w;
	result.w = v.x * A[4].x + v.y * A[4].y + v.z * A[4].z + v.w + A[4].w;

	return result;
}

Matrix operator*(const Matrix& A, const Matrix& B)
{
	Matrix result;

	result[0] = Hcoord(A[0].x*B[0].x + A[0].y*B[1].x + A[0].z*B[2].x + A[0].w*B[3].x,
						A[0].x*B[0].y + A[0].y*B[1].y + A[0].z*B[2].y + A[0].w*B[3].y,
						A[0].x*B[0].z + A[0].y*B[1].z + A[0].z*B[2].z + A[0].w*B[3].z,
						A[0].x*B[0].w + A[0].y*B[1].w + A[0].z*B[2].w + A[0].w*B[3].w);

	result[1] = Hcoord(A[1].x*B[0].x + A[1].y*B[1].x + A[1].z*B[3].x + A[1].w*B[3].x,
						A[1].x*B[0].y + A[1].y*B[1].y + A[1].z*B[3].y + A[1].w*B[3].y,
						A[1].x*B[0].z + A[1].y*B[1].z + A[1].z*B[3].z + A[1].w*B[3].z,
						A[1].x*B[0].w + A[1].y*B[1].w + A[1].z*B[3].w + A[1].w*B[3].w);

	result[2] = Hcoord(A[2].x*B[0].x + A[2].y*B[1].x + A[2].z*B[2].x + A[2].w*B[3].x,
						A[2].x*B[0].y + A[2].y*B[1].y + A[2].z*B[2].y + A[2].w*B[3].y,
						A[2].x*B[0].z + A[2].y*B[1].z + A[2].z*B[2].z + A[2].w*B[3].z,
						A[2].x*B[0].w + A[2].y*B[1].w + A[2].z*B[2].w + A[2].w*B[3].w);

	result[3] = Hcoord(A[3].x*B[0].x + A[3].y*B[1].x + A[3].z*B[2].x + A[3].w*B[3].x,
						A[3].x*B[0].y + A[3].y*B[1].y + A[3].z*B[2].y + A[3].w*B[3].y,
						A[3].x*B[0].z + A[3].y*B[1].z + A[3].z*B[2].z + A[3].w*B[3].z,
						A[3].x*B[0].w + A[3].y*B[1].w + A[3].z*B[2].w + A[3].w*B[3].w);

	return result;
}

float dot(const Vector& u, const Vector& v)
{
	float result;

	result = u.x*v.x + u.y*v.y + u.z*v.z;

	return result;
}

float abs(const Vector& v)
{
	float result;

	result = sqrt(dot(v, v));

	return result;
}

Vector normalize(const Vector& v)
{
	float length = sqrt(abs(v));
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

Matrix Tensor(const Vector &u, const Vector &v)
{
	Matrix result;

	result[0] = Hcoord(u.x*v.x, u.x*v.y, u.x*v.z, 0.0f);
	result[1] = Hcoord(u.y*v.x, u.y*v.y, u.y*v.z, 0.0f);
	result[2] = Hcoord(u.z*v.x, u.z*v.y, u.z*v.z, 0.0f);
	result[3] = Hcoord(0.0f, 0.0f, 0.0f, 0.0f);

	return result;
}
Affine rotate(float t, const Vector& v)
{
	float cost = cos(t);
	float sint = sin(t);
	Vector nv = normalize(v);

	Affine result;
	result[0] = Hcoord(cost + (1-cost)*nv.x*nv.x + sint,
						(1 - cost)*nv.x*nv.y - sint*nv.z,
						(1-cost)*nv.x*nv.z + sint*nv.y,
						0.0f);
	result[1] = Hcoord((1-cost)*nv.x*nv.y + sint*nv.z,
						cost + (1-cost)*nv.y*nv.y,
						(1-cost)*nv.x*nv.z - sint*nv.x,
						0.0f);
	result[2] = Hcoord((1-cost)*nv.x*nv.z - sint*nv.y,
						(1-cost)*nv.y*nv.z + sint*nv.x,
						cost + (1-cost)*nv.z*nv.z,
						0.0f);
	result[3] = Hcoord(0.0f, 0.0f, 0.0f, 1.0f);

	return result;
}

Affine translate(const Vector& v)
{
	Affine result;

	result[0] = Hcoord(1.0f, 0.0f, 0.0f, v.x);
	result[1] = Hcoord(0.0f, 1.0f, 0.0f, v.y);
	result[2] = Hcoord(0.0f, 0.0f, 1.0f, v.z);
	result[3] = Hcoord(0.0f, 0.0f, 0.0f, 1.0f);

	return result;
}

Affine scale(float r)
{
	Affine result;

	result[0] = Hcoord(r, 0.0f, 0.0f, 0.0f);
	result[1] = Hcoord(0.0f, r, 0.0f, 0.0f);
	result[2] = Hcoord(0.0f, 0.0f, r, 0.0f);
	result[3] = Hcoord(0.0f, 0.0f, 0.0f, 1.0f);

	return result;
}

Affine scale(float rx, float ry, float rz)
{
	Affine result;

	result[0] = Hcoord(rx, 0.0f, 0.0f, 0.0f);
	result[1] = Hcoord(0.0f, ry, 0.0f, 0.0f);
	result[2] = Hcoord(0.0f, 0.0f, rz, 0.0f);
	result[3] = Hcoord(0.0f, 0.0f, 0.0f, 1.0f);

	return result;
}

Affine inverse(const Affine& A)
{

}