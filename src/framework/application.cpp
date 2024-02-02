#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h" 
//#include "../../build/particleSyst.h"
//#include <atlimage.h>

Application::Application(const char* caption, int width, int height)
{
	this->window = createWindow(caption, width, height);

	int w,h;
	SDL_GetWindowSize(window,&w,&h);

	this->mouse_state = 0;
	this->time = 0.f;
	this->window_width = w;
	this->window_height = h;
	this->keystate = SDL_GetKeyboardState(nullptr);

	this->framebuffer.Resize(w, h);
}

Application::~Application()
{

}

void Application::Init(void)
{
    
	std::cout << "Initiating app..." << std::endl;
    
    //predeterminem a camara en perspectiva
    camera.SetPerspective(fov, framebuffer.width / (float)framebuffer.height, near_plane, far_plane);
    camera.LookAt(eye, center, up);

    
    
    
    //ENTITIES
    /*
    mesh2_lee.LoadOBJ("meshes/lee.obj");
    entity2 .SetMesh(mesh2_lee);
    //entity2 = Entity(mesh2_lee);
    entity2.modelMatrix.Escalar(1.25, 1.25, 1.25);
    entity2.modelMatrix.Translate(0, -0.3, 0);
    


    mesh3_anna.LoadOBJ("meshes/anna.obj");
    entity3 = Entity(mesh3_anna);
    entity3.modelMatrix.Translate(-0.55, 0.35, 0);
    

    //mesh4_cleo.LoadOBJ("meshes/cleo.obj");
    //entity4 = Entity(mesh4_cleo);
    //entity4.modelMatrix.Translate(0.75, 0, 0);
    //entity4.modelMatrix.Escalar(1.4, 1.4, 1.4);
    //entity4.modelMatrix.Rotate(0.4, Vector3(-1, 1, 0));

    Mesh mesh4_cleo = Mesh();
    mesh4_cleo.LoadOBJ("meshes/cleo.obj");
    Entity entity4 = Entity(mesh4_cleo);
    entity4.modelMatrix.Escalar(1.4, 1.4, 1.4);
    entity4.modelMatrix.Translate(0, 0.1, 0);
    //entity4.modelMatrix.Rotate(0.4, Vector3(-1, 1, 0));
    entity4.Render(&framebuffer, &camera, Color::BLUE);

    mesh2_lee.LoadOBJ("meshes/lee.obj");
    entity2.SetMesh(mesh2_lee);
    entity2 = Entity(mesh2_lee);
    entity2.modelMatrix.Escalar(1.25, 1.25, 1.25);
    entity2.modelMatrix.Translate(0, -0.3, 0);
    
    */
    
    
    
    /*entity2.SetMesh(mesh2_anna);
    entity3.SetMesh(mesh3_leo);
    
    //cada entity tindra una transformacio diferent
    entity1.setRotate(true);
    entity1.setEscalate(false);
    entity1.setTranslate(false);

    entity2.setRotate(false);
    entity2.setEscalate(true);
    entity2.setTranslate(false);

    entity3.setRotate(false);
    entity3.setEscalate(false);
    entity3.setTranslate(true);*/
    
    


    

    /*editem les matrius model perque els objectes es trobin en posicions diferents
    modelMatrix1.SetIdentity();
    modelMatrix1.Translate(-0.5, 0, 0);
    modelMatrix2.SetIdentity();
    modelMatrix2.Translate(0.7, -0.4, 0);
    modelMatrix3.SetIdentity();
    modelMatrix3.Translate(0, 0.4, 0);
    
    //editem les matrius model perque els objectes siguin de mida diferent
    modelMatrix1._11=1.7;
    modelMatrix1._22=1.7;
    modelMatrix1._33=1.7;
    
    modelMatrix2._11=1.3;
    modelMatrix2._22=1.3;
    modelMatrix2._33=1.3;
    
    //aplico les matrius resultants a cada entitat
    //entity1.SetModelMatrix(modelMatrix1);
    //entity2.SetModelMatrix(modelMatrix2);
    //entity3.SetModelMatrix(modelMatrix3);

    
    

    */


}

// Render one frame
void Application::Render(void) 
{

    framebuffer.Render();//enviem el framebuffer a la pantalla
}

// Called after render
void Application::Update(float seconds_elapsed)
{
    
    //animen les entities
    
    if (multiples==true){
        framebuffer.Fill(Color::BLACK);
        
        entity7.Update(seconds_elapsed);
        entity7.Render(&framebuffer, &camara, Color::GREEN);
        
        entity8.Update(seconds_elapsed);
        entity8.Render(&framebuffer, &camara, Color::BLUE);
        
        entity9.Update(seconds_elapsed);
        entity9.Render(&framebuffer, &camara, Color::PURPLE);
        
        
    }
}
    
    //keyboard press event
    void Application::OnKeyPressed(SDL_KeyboardEvent event)
    {
        // KEY CODES: https://wiki.libsdl.org/SDL2/SDL_Keycode
        
        //crido funcio segons la tecla apretada
        switch (event.keysym.sym) {
            case SDLK_ESCAPE:
                exit(0);
                break;
                
            case SDLK_1: {
                framebuffer.Fill(Color::BLACK);
                Mesh mesh1_lee = Mesh();
                mesh1_lee.LoadOBJ("meshes/lee.obj");
                entity1 = Entity(mesh1_lee);
                entity1.modelMatrix.Escalar(1.25, 1.25, 1.25);
                entity1.modelMatrix.Translate(0, -0.3, 0);
                entity1.Render(&framebuffer, &camara, Color::CYAN);
                break;
            }
                
            case SDLK_2: {
                framebuffer.Fill(Color::BLACK);
                multiples=true;
                
                mesh7_lee.LoadOBJ("meshes/lee.obj");
                entity7 = Entity(mesh7_lee);
                entity7.modelMatrix.Escalar(1.25, 1.25, 1.25);
                entity7.modelMatrix.Translate(0, -0.3, 0);
                entity7.Render(&framebuffer, &camara, Color::GREEN);
                
                mesh8_anna.LoadOBJ("meshes/anna.obj");
                entity8 = Entity(mesh8_anna);
                entity8.modelMatrix.Escalar(1.00, 1.00, 1.00);
                entity8.modelMatrix.Translate(-0.5, -0.8, 0);
                entity8.modelMatrix.Rotate(0.4, Vector3(0.5, -0.5, 0));
                entity8.Render(&framebuffer, &camara, Color::BLUE);
                
                mesh8_leo.LoadOBJ("meshes/cleo.obj");
                entity9 = Entity(mesh8_leo);
                entity9.modelMatrix.Escalar(1.0, 1.0, 1.0);
                entity9.modelMatrix.Translate(0.5, 0.0, 0.0);
                entity9.Render(&framebuffer, &camara, Color::PURPLE);
                
                
                break;
            }
                
            case SDLK_o:
                framebuffer.Fill(Color::BLACK);
                camera.SetOrthographic(left, right, top, bottom, near_plane, far_plane);
                break;
                
            case SDLK_p:
                framebuffer.Fill(Color::BLACK);
                camera.SetPerspective(fov, framebuffer.width / (float)framebuffer.height, near_plane, far_plane);
                break;
                
            case SDLK_n:
                camera.near_plane += 100.0f;
                camera.UpdateProjectionMatrix();
                break;
                
            case SDLK_f:
                camera.far_plane -= 100.f;
                camera.UpdateProjectionMatrix();
                break;
                
            case SDLK_PLUS:
                camera.fov += 2.0f;
                camera.UpdateProjectionMatrix();
                break;
                
            case SDLK_MINUS:
                camera.fov -= 2.0f;
                camera.UpdateProjectionMatrix();
                break;
        }
    }
    
    void Application::OnMouseButtonDown(SDL_MouseButtonEvent event)
    { //MIRAR CUANDO SE PRESIONA EL BOTON
        if (event.button == SDL_BUTTON_LEFT) {
            leftMouse = true; //el boton que se ha picado es el izquierdo
            previMouseX = event.x; //guardar x del raton
            previMouseY = event.y; //guardar y del raton
            
        }
        if (event.button == SDL_BUTTON_RIGHT) {
            rightMouse = true;
            previMouseX = event.x;
            previMouseY = event.y;
        }
        
        
    }

    
void Application::OnMouseButtonUp( SDL_MouseButtonEvent event ){
    //MIRAR CUANDO SE DEJA DE PULSAR EL BOTON

    if (event.button == SDL_BUTTON_LEFT) {
        leftMouse = false; //boton izq ya no esta presionado
    }

    if (event.button == SDL_BUTTON_RIGHT) {
        rightMouse = false;
    }
}

    
void Application::OnMouseMove(SDL_MouseButtonEvent event) {
    //cambio de cordenadas del raton
    int deltaX = event.x - previMouseX;
    int deltaY = event.y - previMouseY;

    if (leftMouse) {
        
        //0.2 SENSIBILIDAD VALOR BIEN? MUY RAPIDO?

        float sensitivity = 0.02f;
        //rotar ejes X y Y
        camera.Rotate(deltaX * sensitivity, Vector3(0, 1, 0));
        camera.Rotate(deltaY * sensitivity, camera.GetLocalVector(Vector3(1,0,0)));
        //Actualizar posiciones
        previMouseX = event.x;
        previMouseY = event.y;

    }

    if (rightMouse) {
        float sensitivity = 0.02f;
        //mover de izq a derecha
        camera.Move(Vector3(-deltaX * sensitivity, 0, 0));

        //mover vertical
        camera.Move(Vector3(0, deltaY * sensitivity, 0));

        previMouseX = event.x;
        previMouseY = event.y;    
    }  
}
       
    
    
void Application::OnWheel(SDL_MouseWheelEvent event)
{
    float sensitivity = 0.1f; //sensibilidad para zoom de camera ¿VALOR CORRECTO?
    cameraDistance-=event.y*sensitivity; //depende de rueda, variamos distancia

    cameraDistance = std::max(cameraDistance, 1.0f);
    cameraDistance = std::min(cameraDistance, 100.0f);

    float proporcion_window= static_cast<float>(window_width) / static_cast<float>(window_height);
    camera.SetPerspective(fov, proporcion_window, 0.01f, 1000.0f);//

    camera.UpdateViewMatrix();

      
}
    
void Application::OnFileChanged(const char* filename){
    Shader::ReloadSingleShader(filename);
}
