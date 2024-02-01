#pragma once
#include "mesh.h"
#include "framework.h"
#include "image.h"
#include "camera.h"

class Entity
{
private:
	

public:
    Mesh mesh;
    Matrix44 modelMatrix;
    bool rotar;
    bool escalar;
    bool translate;
    
    
    
	Entity();
	Entity(const Mesh& mesh, const Matrix44& modelMatrix);
	Entity(const Mesh& mesh);

	void SetMesh(const Mesh& mesh);
	void SetModelMatrix(const Matrix44& modelMatrix);

	const Mesh& GetMesh() const;
	const Matrix44& GetModelMatrix() const;

    void Render(Image* framebuffer, Camera* camera, const Color& c);
    void Update(float seconds_elapsed);
    
    void setRotate(bool rotate);
    void setTranslate(bool translate);
    void setEscalate(bool escalate);

};


