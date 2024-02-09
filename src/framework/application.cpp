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
    


}

// Render one frame
void Application::Render(void) 
{
    framebuffer.Fill(Color::BLACK);
    entity7.Render(&framebuffer, &camara, Color::GREEN);
    entity8.Render(&framebuffer, &camara, Color::BLUE);
    entity9.Render(&framebuffer, &camara, Color::PURPLE);
    
    framebuffer.Render();//enviem el framebuffer a la pantalla
    
}

// Called after render
void Application::Update(float seconds_elapsed)
{
    
    //animen les entities
    
    if (multiples==true){
        
        
        entity7.Update(seconds_elapsed);
        
        
        entity8.Update(seconds_elapsed);
        
        
        entity9.Update(seconds_elapsed);
        
        
        
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
        multiples=false;
        framebuffer.Fill(Color::BLACK); //pantalla negra

        //fem load i renderitzem Lee
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
        multiples = true;

        // fem load i renderitzem Lee
        
        entity7 = Entity(mesh7_lee);
        entity7.modelMatrix.Escalar(1.25, 1.25, 1.25);
        entity7.modelMatrix.Translate(0, -0.3, 0);
        entity7.Render(&framebuffer, &camara, Color::GREEN);

        // fem load i renderitzem ANA, apliquem transformacions
    
        entity8 = Entity(mesh8_anna);
        entity8.modelMatrix.Escalar(1.00, 1.00, 1.00);
        entity8.modelMatrix.Translate(-0.5, -0.8, 0);
        entity8.modelMatrix.Rotate(0.4, Vector3(0.5, -0.5, 0));
        entity8.Render(&framebuffer, &camara, Color::BLUE);


        // fem load i renderitzem Leo, apliquem transformacions
        
        entity9 = Entity(mesh8_leo);
        entity9.modelMatrix.Escalar(1.0, 1.0, 1.0);
        entity9.modelMatrix.Translate(0.5, 0.0, 0.0);
        entity9.Render(&framebuffer, &camara, Color::PURPLE);


        break;
    }
              //TODA ESTA PARTE NO FUNCIONA CORRECTAMENTE, NO HEMOS LOGRADO LOCALIZAR LOS FALLOS EN EL CODIGO//
    case SDLK_o:
        framebuffer.Fill(Color::BLACK);
        //Orthographic projection
        camera.SetOrthographic(left, right, top, bottom, near_plane, far_plane);
        break;

    case SDLK_p:
        framebuffer.Fill(Color::BLACK);
        //Perspective Projection
        camera.SetPerspective(fov, framebuffer.width / (float)framebuffer.height, near_plane, far_plane);
        break;

    case SDLK_n:
        //incrementem valor de el near plane de camera
        camera.near_plane += 100.0f;
        camera.UpdateProjectionMatrix();
        break;

    case SDLK_f:
        camera.far_plane -= 100.f;
        camera.UpdateProjectionMatrix();
        break;

    case SDLK_PLUS:
        //TODA ESTA PARTE NO FUNCIONA CORRECTAMENTE, NO HEMOS LOGRADO LOCALIZAR LOS FALLOS EN EL CODIGO
        camera.fov += 2.0f;
        camera.UpdateProjectionMatrix();
        break;

    case SDLK_MINUS:
        //TODA ESTA PARTE NO FUNCIONA CORRECTAMENTE, NO HEMOS LOGRADO LOCALIZAR LOS FALLOS EN EL CODIGO
        camera.fov -= 2.0f;
        camera.UpdateProjectionMatrix();
        break;
    }
}



//TODA ESTA PARTE NO FUNCIONA CORRECTAMENTE, NO HEMOS LOGRADO LOCALIZAR LOS FALLOS EN EL CODIGO

void Application::OnMouseButtonDown(SDL_MouseButtonEvent event)
{ //MIRAR CUANDO SE PRESIONA EL BOTON
    if (event.button == SDL_BUTTON_LEFT) {
        leftMouse = true; //el boton que se ha picado es el izquierdo
        previ_MouseX = event.x; //guardar x del raton
        previ_MouseY = event.y; //guardar y del raton

    }
    if (event.button == SDL_BUTTON_RIGHT) { //lo mismo q en left
        rightMouse = true;
        previ_MouseX = event.x;
        previ_MouseY = event.y;
    }


}


void Application::OnMouseButtonUp(SDL_MouseButtonEvent event) {
    //MIRAR CUANDO SE DEJA DE PULSAR EL BOTON

    if (event.button == SDL_BUTTON_LEFT) {
        leftMouse = false; //boton izq ya no esta presionado
    }

    if (event.button == SDL_BUTTON_RIGHT) {
        rightMouse = false;
    }
}

//PARA CUANDO EL RATON ESTA EN MOVIMIENTO
void Application::OnMouseMove(SDL_MouseButtonEvent event) {
    //cambio de cordenadas del raton, posicion actual con anterior
    int deltaX = event.x - previ_MouseX;
    int deltaY = event.y - previ_MouseY;

    if (leftMouse) {

        //0.2 SENSIBILIDAD VALOR BIEN? MUY RAPIDO?

        float sensitivity = 0.02f;
        //rotar ejes X y Y
        camera.Rotate(deltaX * sensitivity, Vector3(0, 1, 0));
        camera.Rotate(deltaY * sensitivity, camera.GetLocalVector(Vector3(1, 0, 0)));
        //Actualizar posiciones
        previ_MouseX = event.x;
        previ_MouseY = event.y;

    }

    if (rightMouse) {
        float sensitivity = 0.02f;
        //mover de izq a derecha
        camera.Move(Vector3(-deltaX * sensitivity, 0, 0));

        //mover vertical
        camera.Move(Vector3(0, deltaY * sensitivity, 0));

        previ_MouseX = event.x;
        previ_MouseY = event.y;
    }
}



void Application::OnWheel(SDL_MouseWheelEvent event)
{
    //INTENTO, CREO QUE FALTAN COSAS

    float sensitivity = 0.1f; //sensibilidad para zoom de camera ¿VALOR CORRECTO?
    distance_camera -= event.y * sensitivity; //depende de rueda, variamos distancia

    //Para poner limites a la camera, QUE NO DE ERROR
    distance_camera = std::max(distance_camera, 1.0f);
    distance_camera = std::min(distance_camera, 1000.0f);

    float proporcion_window = static_cast<float>(window_width) / static_cast<float>(window_height);
    camera.SetPerspective(fov, proporcion_window, 0.01f, 1000.0f);//nueva prespectiva

    camera.UpdateViewMatrix();


}

void Application::OnFileChanged(const char* filename) {
    Shader::ReloadSingleShader(filename);
}

    
    
