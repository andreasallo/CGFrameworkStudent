#pragma once
#include "mesh.h"
#include "image.h"

class Entity
{
private:
	Mesh mesh;
	Matrix44 modelMatrix;

public:
	Entity();
	Entity(const Mesh& mesh, const Matrix44& modelMatrix);
	Entity(const Mesh& mesh);

	void SetMesh(const Mesh& mesh);
	void SetModelMatrix(const Matrix44& modelMatrix);

	const Mesh& GetMesh() const;
	const Matrix44& GetModelMatrix() const;

	void Entity::Render(Image* framebuffer, Camera* camera, const Color& c);

};


