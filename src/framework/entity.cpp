#include "entity.h"
#include "framework.h"
#include "camera.h"

Entity::Entity() {
	modelMatrix.SetIdentity();
};//crea instancia de Entity, solo con matriz identidad
//útil cuando necesitas una entidad con una matriz de modelo predeterminada.

Entity::Entity(const Mesh& mesh, const Matrix44& modelMatrix) {
	this->mesh=mesh;
	this->modelMatrix=modelMatrix;
} //toma ya un mesh y una matriz y los asigna como variables de entity
//forma de crear una entidad con una malla específica y una matriz de modelo personalizada. /

Entity::Entity(const Mesh& mesh) : mesh(mesh) {
	modelMatrix.SetIdentity();
}//útil cuando solo tienes una malla y no necesitas especificar una matriz de modelo

void Entity::SetMesh(const Mesh& mesh) {
	this->mesh = mesh;
}//permite cambiar la malla(mesh)

void Entity::SetModelMatrix(const Matrix44& modelMatrix) {
	this->modelMatrix = modelMatrix;
}//permite establecer una nueva matriz

const Mesh& Entity::GetMesh() const {
	return mesh;
}

const Matrix44& Entity::GetModelMatrix() const {
	return modelMatrix;
}

void Entity::Render(Image* framebuffer, Camera* camera, const Color& c) {
	//get the vertices of the mesh
	const std::vector<Vector3>& meshVertices = mesh.GetVertices();

	//iterate vertices
	for (size_t i = 0; i < meshVertices.size(); i += 3) {
		//Vertex triangle actual
		Vector3 v0 = meshVertices[i];
		Vector3 v1 = meshVertices[i+1];
		Vector3 v2 = meshVertices[i+2];

		//Transformar vertex a WORLDSPACE
		
	}
}
