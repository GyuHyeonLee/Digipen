/*
Name : Gyuhyeon, Lee
Assignment Number : 3
Course name : CS250
Term : Spring 2018
*/
#include "FrustumMesh.h"

const FrustumMesh::Face FrustumMesh::faces[12] =
{
	FrustumMesh::Face(1, 2, 4),
	FrustumMesh::Face(2, 3, 4),

	FrustumMesh::Face(4, 3, 8),
	FrustumMesh::Face(3, 7, 8),
	
	FrustumMesh::Face(3, 2, 7),
	FrustumMesh::Face(2, 6, 7),
	
	FrustumMesh::Face(2, 5, 6),
	FrustumMesh::Face(2, 1, 5),
	
	FrustumMesh::Face(1, 4, 5),
	FrustumMesh::Face(4, 8, 5),
	
	FrustumMesh::Face(6, 5, 7),
	FrustumMesh::Face(5, 8, 7),
};

const FrustumMesh::Edge FrustumMesh::edges[16] =
{
	FrustumMesh::Edge(0, 1),
	FrustumMesh::Edge(0, 2),
	FrustumMesh::Edge(0, 3),
	FrustumMesh::Edge(0, 4),

	FrustumMesh::Edge(1, 2),
	FrustumMesh::Edge(2, 3),
	FrustumMesh::Edge(3, 4),
	FrustumMesh::Edge(4, 1),

	FrustumMesh::Edge(4, 8),
	FrustumMesh::Edge(3, 7),
	FrustumMesh::Edge(2, 6),
	FrustumMesh::Edge(1, 5),

	FrustumMesh::Edge(5, 8),
	FrustumMesh::Edge(8, 7),
	FrustumMesh::Edge(7, 6),
	FrustumMesh::Edge(6, 5),
};

FrustumMesh::FrustumMesh(float fov, float aspect, 
						float near, float far)
{
	dimensions = Vector(0.0f, 0.0f, 0.f);
	float tangentResult = tanf(fov / 2.0f);
	float widthNear = 2.0f * near * tangentResult;
	float heightNear = widthNear / aspect;
	float halfWidthNear = widthNear / 2.0f;
	float halfHeightNear = heightNear / 2.0f;

	float widthFar = 2.0f * far * tangentResult;
	float heightFar = widthFar / aspect;
	float halfWidthFar = widthFar / 2.0f;
	float halfHeightFar = heightFar / 2.0f;

	vertices[0] = Point(0.0f, 0.0f, 0.0f);

	vertices[1] = Point(-halfWidthNear, halfHeightNear, -near);
	vertices[2] = Point(halfWidthNear, halfHeightNear, -near);
	vertices[3] = Point(halfWidthNear, -halfHeightNear, -near);
	vertices[4] = Point(-halfWidthNear, -halfHeightNear, -near);

	vertices[5] = Point(-halfWidthFar, halfHeightFar, -far);
	vertices[6] = Point(halfWidthFar, halfHeightFar, -far);
	vertices[7] = Point(halfWidthFar, -halfHeightFar, -far);
	vertices[8] = Point(-halfWidthFar, -halfHeightFar, -far);
}
int FrustumMesh::VertexCount(void)
{
	// By deviding the entire size of array by a single element
	// we can get the count
	return (sizeof(vertices) / sizeof(vertices[0]));
}
Point FrustumMesh::GetVertex(int i)
{
	return vertices[i];
}
Vector FrustumMesh::Dimensions(void)
{
	return dimensions;
}
Point FrustumMesh::Center(void)
{
	return center;
}
int FrustumMesh::FaceCount(void)
{
	return (sizeof(faces) / sizeof(faces[0]));
}
Mesh::Face FrustumMesh::GetFace(int i)
{
	return faces[i];
}
int FrustumMesh::EdgeCount(void)
{
	return (sizeof(edges) / sizeof(edges[0]));
}
Mesh::Edge FrustumMesh::GetEdge(int i)
{
	return edges[i];
}