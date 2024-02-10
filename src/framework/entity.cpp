#include "entity.h"


Entity::Entity() {
	modelMatrix.SetIdentity();
};//crea instancia de Entity, solo con matriz identidad
//útil cuando necesitas una entidad con una matriz de modelo predeterminada.

Entity::Entity(const Mesh& mesh, const Matrix44& modelMatrix) {
	this->mesh=mesh;
	this->modelMatrix=modelMatrix;
} //toma ya un mesh y una matriz y los asigna como variables de entity
//forma de crear una entidad con una malla específica y una matriz de modelo personalizada. 

Entity::Entity(const Mesh& mesh) : mesh(mesh) {
	modelMatrix.SetIdentity();
}//útil cuando solo tienes una malla y no necesitas especificar una matriz de modelo

void Entity::SetMesh(const Mesh& mesh) {
	this->mesh = mesh;
}//permite cambiar la malla(mesh)

void Entity::SetModelMatrix(const Matrix44& modelMatrix) {
	this->modelMatrix = modelMatrix;
}//permite establecer una nueva matriz


void Entity::setRotate(bool rotar){
    this->rotar=rotar;
}
void Entity::setTranslate(bool translate){
    this->translate=translate;
}
void Entity::setEscalate(bool escalate){
    this->escalar=escalate;
}


const Mesh& Entity::GetMesh() const {
	return mesh;
}

const Matrix44& Entity::GetModelMatrix() const {
	return modelMatrix;
}

void Entity::Render(Image* framebuffer, Camera* camera, const Color& c, FloatImage* zBuffer) {
    //get the vertices of the mesh
    const std::vector<Vector3>& meshVertices = mesh.GetVertices();
    
    //iterate vertices
    for (int i = 0; i < meshVertices.size(); i += 3) {
        
        //Vertex triangle actual
        Vector3 vertex_0 = meshVertices[i];
        Vector3 vertex_1 = meshVertices[i+1];
        Vector3 vertex_2 = meshVertices[i+2];
        
        //Transformar vertex a WORLDSPACE
        
        
        Vector4 v0 = Vector4(vertex_0.x, vertex_0.y, vertex_0.z, 1);
        Vector4 v1 = Vector4(vertex_1.x, vertex_1.y, vertex_1.z, 1);
        Vector4 v2 = Vector4(vertex_2.x, vertex_2.y, vertex_2.z, 1);
        
        //Fem la transformació a WS
        Vector4 world0 = modelMatrix*v0;
        Vector4 world1 = modelMatrix * v1;
        Vector4 world2 = modelMatrix * v2;
        
        //Agafem els vectors de la matriu en el WS
        Vector3 v0_ws = world0.GetVector3();
        Vector3 v1_ws = world1.GetVector3();
        Vector3 v2_ws = world2.GetVector3();
        
        //Passem el Clip Space
        bool negZ0, negZ1, negZ2; //booleans per mirar si estan dins o fora.
        
        // pantalla de menys 1 a 1
        Vector3 clipSpace0 = camera->ProjectVector(v0_ws, negZ0);
        Vector3 clipSpace1 = camera->ProjectVector(v1_ws, negZ1);
        Vector3 clipSpace2 = camera->ProjectVector(v2_ws, negZ2);
        
        
        //assegurar estar dins del frustrum
        if (negZ0 == false && negZ1 == false && negZ2 == false) {
            
            float sWidth = static_cast<float>(framebuffer->width);
            float sHeight = static_cast<float>(framebuffer->height);
            
            //Pasar del Clip Space al Screen Space
            Vector3 screenSpace0 = Vector3(static_cast<int>((clipSpace0.x + 1.0f) * 0.5f * framebuffer->width), static_cast<int>((clipSpace0.y + 1.0f) * 0.5f * framebuffer->height), clipSpace0.z);
            Vector3 screenSpace1 = Vector3(static_cast<int>((clipSpace1.x + 1.0f) * 0.5f * framebuffer->width), static_cast<int>((clipSpace1.y + 1.0f) * 0.5f * framebuffer->height), clipSpace1.z);
            Vector3 screenSpace2 = Vector3(static_cast<int>((clipSpace2.x + 1.0f) * 0.5f * framebuffer->width), static_cast<int>((clipSpace2.y + 1.0f) * 0.5f * framebuffer->height), clipSpace2.z);
            
            
            //Draw triangle
            Vector2 vec1= Vector2(screenSpace0.x, screenSpace0.y);
            Vector2 vec2= Vector2(screenSpace1.x, screenSpace1.y);
            Vector2 vec3= Vector2(screenSpace2.x, screenSpace2.y);
            
            if(tecla_c){
                if (drawInterpolatedColors){
                    framebuffer->DrawTriangleInterpolated(screenSpace0, screenSpace1,screenSpace2,Color::RED, Color::BLUE, Color::YELLOW, NULL);}
                else{ framebuffer->DrawTriangle(vec1, vec2, vec3, Color::PURPLE, true, Color::PURPLE);}
            }
            if(tecla_z){
                if(rasterize_with_Zbuffer){
                    framebuffer->DrawTriangleInterpolated(screenSpace0, screenSpace1,screenSpace2,Color::PURPLE, Color::BLUE, Color::RED, zBuffer);}
                else{framebuffer->DrawTriangleInterpolated(screenSpace0, screenSpace1,screenSpace2,Color::PURPLE, Color::BLUE, Color::RED, NULL);}
            }
            /*framebuffer->DrawLineDDA(screenSpace0.x, screenSpace0.y, screenSpace1.x, screenSpace1.y, c);
            framebuffer->DrawLineDDA(screenSpace1.x, screenSpace1.y, screenSpace2.x, screenSpace2.y, c);
            framebuffer->DrawLineDDA(screenSpace2.x, screenSpace2.y, screenSpace0.x, screenSpace0.y, c);*/
            
            
        }
    }
}
    
void Entity::Update(float seconds_elapsed){
    modelMatrix.RotateLocal(0.01 * (PI / 10.0f), Vector3(0.0f,1.0f,0.0f));

    //NO ENS FUNCIONEN LES ALTRES OPCIONS
/*
    if (escalar == true) {

        //escalar un 10%, potser molt poc?
        float num_scale = 1.0f + seconds_elapsed * 0.1f;
        for (int i = 0; i < 16; ++i) {
            modelMatrix.m[i] *= num_scale;
        }
    }
    if (translate == true) {
        //Translación en el eje y.
        float translation_vel = 0.3f;
        modelMatrix.TranslateLocal(0.0f, seconds_elapsed * translation_vel, 0.0f);
    }
    
}

		//rotate: eye(posicion de camara apunta a center). roto vector q va del eye al center
		//orbit: cambio el eye, roto el angulo de center . vector del center al eye.*/

}
