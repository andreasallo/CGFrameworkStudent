#pragma once
#include "mesh.h"
#include "framework.h"
#include "image.h"
#include "camera.h"
#include "texture.h"


class Entity
{
private:
	

public:
    Mesh mesh;
    Matrix44 modelMatrix;
    Image* texture;

    bool rotar;
    bool escalar;
    bool translate;
    bool entityInitialized=false;
    
    bool tecla_c;
    bool tecla_z;
    bool tecla_t;
    bool drawInterpolatedColors=false;
    bool rasterize_with_Zbuffer=false;
    bool mesh_texture = false;
    
    
    
	Entity();
	Entity(const Mesh& mesh, const Matrix44& modelMatrix);
	Entity(const Mesh& mesh);

	void SetMesh(const Mesh& mesh);
	void SetModelMatrix(const Matrix44& modelMatrix);

	const Mesh& GetMesh() const;
	const Matrix44& GetModelMatrix() const;

    void Render(Image* framebuffer, Camera* camera, const Color& c, FloatImage* zBuffer);
    void Update(float seconds_elapsed);
    
    void setRotate(bool rotate);
    void setTranslate(bool translate);
    void setEscalate(bool escalate);
    void setTexture(Image* textures);
    const Texture* Entity::GetTexture() const;

};


