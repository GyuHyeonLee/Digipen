/*
Name : Gyuhyeon, Lee
Assignment Number : 2
Course name : CS250
Term : Spring 2018
*/

#include "CubeMesh.h"

CubeMesh::CubeMesh()
{ 
	vertices[0] = Point();
	vertices[1] = Point();
	vertices[2] = Point();
	vertices[3] = Point();
	vertices[4] = Point();
	vertices[5] = Point();
	vertices[6] = Point();
	vertices[7] = Point();

	faces[0] = ;
	faces[1] = ;
	faces[2] = ;
	faces[3] = ;
	faces[4] = ;
	faces[5] = ;
	faces[6] = ;
	faces[7] = ;
	faces[8] = ;
	faces[9] = ;
	faces[10] = ;
	faces[11] = ;

	edges[0] = ;
	edges[1] = ;
	edges[2] = ;
	edges[3] = ;
	edges[4] = ;
	edges[5] = ;
	edges[6] = ;
	edges[7] = ;
	edges[8] = ;
	edges[9] = ;
	edges[10] = ;
	edges[11] = ;
}

int CubeMesh::VertexCount(void)
{
	// By deviding the entire size of array by a single element
	// we can get the count
	return (sizeof(vertices) / sizeof(vertices[0]));
}

Point CubeMesh::GetVertex(int i)
{
	return vertices[i];
}

Vector CubeMesh::Dimensions(void)
{
	return Vector(1.0f, 1.0f, 1.0f);
}

Point CubeMesh::Center(void)
{
	return Point(1.0f, 1.0f, 1.0f);
}

int CubeMesh::FaceCount(void)
{
	return (sizeof(faces) / sizeof(faces[0]));
}

CubeMesh::Face CubeMesh::GetFace(int i)
{
	return faces[i];
}

int CubeMesh::EdgeCount(void)
{
	return (sizeof(edges) / sizeof(edges[0]));
}

CubeMesh::Edge CubeMesh::GetEdge(int i)
{
	return edges[i];
}