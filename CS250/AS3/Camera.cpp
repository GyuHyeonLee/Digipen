/*
Name : Gyuhyeon, Lee
Assignment Number : 3
Course name : CS250
Term : Spring 2018
*/
#include "Camera.h"

#define DEGREE_TO_RADIAN 0.0174533f

Camera::Camera(void)
{
	eye = Point(0.0f, 0.0f, 0.0f);
	
	right = Vector(1.0f, 0.0f, 0.0f);
	up = Vector(0.0f, 1.0f, 0.0f);
	back = Vector(0.0f, 0.0f, 1.0f);

	distance = near;

	float tangentResult = tanf(45.0f * DEGREE_TO_RADIAN);
	width = 2.0f * distance * tangentResult;
	height = width;
	
	near = 0.1f;
	far = 10.0f;
}

Camera::Camera(const Point& E, const Vector& look, const Vector& rel,
	float fov, float aspect, float _near, float _far)
{
	eye = E;

	distance = near;

	// n vector
	back = normalize(-1.0f * look);
	
	// u vector
	up = normalize(cross(look, rel));

	// v vector
	right = normalize(cross(back, up));

	width = 2.0f * distance * tanf(fov / 2.0f);
	height = width / aspect;

	near = _near;
	far = _far;
}

Point Camera::Eye(void) const
{
	return eye;
}

Vector Camera::Right(void) const
{
	return right;
}

Vector Camera::Up(void) const
{
	return up;
}

Vector Camera::Back(void) const
{
	return back;
}

Vector Camera::ViewportGeometry(void) const
{
	return Vector(width, height, distance);
}

float Camera::NearDistance(void) const
{
	return near;
}

float Camera::FarDistance(void) const
{
	return far;
}

Camera& Camera::Zoom(float factor)
{
	width *= factor;
	height *= factor;

	return *this;
}

Camera& Camera::Forward(float _distance)
{
	distance -= _distance;

	return *this;
}

// Rotate based on v(right)
Camera& Camera::Yaw(float angle)
{
	Affine rotateMatrix = rotate(angle, right);
	up = rotateMatrix * up;
	back = rotateMatrix * back;

	return *this;
}

Camera& Camera::Pitch(float angle)
{
	Affine rotateMatrix = rotate(angle, up);
	right = rotateMatrix * right;
	back = rotateMatrix * back;

	return *this;
}

Camera& Camera::Roll(float angle)
{
	Affine rotateMatrix = rotate(angle, back);
	right = rotateMatrix * right;
	up = rotateMatrix * up;

	return *this;
}