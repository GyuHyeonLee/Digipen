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
	Point(1.0f, 1.0f, -1.0f),
	Point(1.0f, -1.0f, 1.0f),
	Point(1.0f, -1.0f, -1.0f),
	Point(-1.0f, 1.0f, 1.0f),
	Point(-1.0f, 1.0f, -1.0f),
	Point(-1.0f, -1.0f, 1.0f),
	Point(-1.0f, -1.0f, -1.0f),
};

const CubeMesh::Face CubeMesh::faces[12] =
{
	CubeMesh::Face(0, 4, 6),
	CubeMesh::Face(0, 6, 2),
	CubeMesh::Face(1, 7, 5),
	CubeMesh::Face(1, 3, 7),
	CubeMesh::Face(4, 5, 7),
	CubeMesh::Face(4, 7, 6),
	CubeMesh::Face(0, 3, 1),
	CubeMesh::Face(0, 2, 3),
	CubeMesh::Face(1, 5, 4),
	CubeMesh::Face(1, 4, 0),
	CubeMesh::Face(2, 6, 3),
	CubeMesh::Face(6, 7, 3),
};

const CubeMesh::Edge CubeMesh::edges[12] = 
{
	CubeMesh::Edge(0, 1),
	CubeMesh::Edge(1, 5),
	CubeMesh::Edge(5, 4),
	CubeMesh::Edge(4, 0),
	CubeMesh::Edge(0, 2),
	CubeMesh::Edge(1, 3),
	CubeMesh::Edge(5, 7),
	CubeMesh::Edge(4, 6),
	CubeMesh::Edge(2, 3),
	CubeMesh::Edge(3, 7),
	CubeMesh::Edge(7, 6),
	CubeMesh::Edge(6, 2),
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
	return Vector(0.0f, 0.0f, 0.0f);
}

Point CubeMesh::Center(void)
{
	return Point(0.0f, 0.0f, 0.0f);
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