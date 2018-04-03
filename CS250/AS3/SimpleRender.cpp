/*
Name : Gyuhyeon, Lee
Assignment Number : 3
Course name : CS250
Term : Spring 2018
*/

#include "SimpleRender.h"

SimpleRender::SimpleRender(Render &r)
	: render(r)
{
	// Construct perspective projection matrix
	PersProj.row[0] = Hcoord( 1, 0, 0, 0 );
	PersProj.row[1] = Hcoord(0, 1, 0, 0);
	PersProj.row[2] = Hcoord(0, 0, 1.0f / 11.0f, -5.0f / 11.0f);
	PersProj.row[3] = Hcoord(0, 0, -2.0f / 11.0f, 10.0f / 11.0f);

}

SimpleRender::~SimpleRender(void)
{
}

void SimpleRender::DisplayEdges(Mesh& m, const Affine& A, const Vector& color)
{
	render.SetColor(color);
	int edgeCount = m.EdgeCount();

	Matrix result = PersProj * A;

	// Draw all edges
	for (int i = 0;
		i < edgeCount;
		++i)
	{
		Mesh::Edge targetEdge = m.GetEdge(i);

		Hcoord h1 = result * m.GetVertex(targetEdge.index1);
		Hcoord h2 = result * m.GetVertex(targetEdge.index2);

		render.DrawLine(h1, h2);
	}
}

void SimpleRender::DisplayFaces(Mesh& m, const Affine& A, const Vector& color)
{
	int faceCount = m.FaceCount();

	Matrix result = PersProj * A;

	// Draw all edges
	for (int i = 0;
		i < faceCount;
		++i)
	{
		Mesh::Face targetFace = m.GetFace(i);

		Hcoord h1 = A * m.GetVertex(targetFace.index1);
		Hcoord h2 = A * m.GetVertex(targetFace.index2);
		Hcoord h3 = A * m.GetVertex(targetFace.index3);

		Vector PE = Vector(0.0f - h1.x, 0.0f - h1.y, 5.0f - h1.z);
		Vector faceNormal = cross(h2 - h1, h3 - h1);
		float dotResult = dot(faceNormal, PE);

		if (dotResult > 0.0f)
		{
			Vector lightDirection(0, 0, 1.0f);
			float diffuse = abs(dot(lightDirection, faceNormal)) / 
							(abs(lightDirection) * abs(faceNormal));
			
			render.SetColor(diffuse * color);

			render.FillTriangle(PersProj * h1, PersProj * h2, PersProj * h3);
		}
	}
}