/*
Name : Gyuhyeon, Lee
Assignment Number : 2
Course name : CS250
Term : Spring 2018
*/

#include "CubeMesh.h"
const Point CubeMesh::vertices[8] = 
{
	Point(1.0f, 1.0f, 1.0f),
	Point(-1.0f, 1.0f, 1.0f),
	Point(-1.0f, -1.0f, 1.0f),
	Point(1.0f, -1.0f, 1.0f),
	Point(1.0f, 1.0f, -1.0f),
	Point(-1.0f, 1.0f, -1.0f),
	Point(-1.0f, -1.0f, -1.0f),
	Point(1.0f, -1.0f, -1.0f),
};

const CubeMesh::Edge CubeMesh::edges[12] = 
{
	CubeMesh::Edge();
};

const CubeMesh::Face CubeMesh::faces[12] = 
{

};

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