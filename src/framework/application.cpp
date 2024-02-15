#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h" 
#include "texture.h"
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
    
    mesh1_lee.LoadOBJ("meshes/lee.obj");
    textureLee = new Image();
    textureLee->LoadTGA("textures/lee_color_specular.tga",true);
    //textureLee->FlipY(); 
    // 
    //  VEMOS QUE NUESTRO PROBLEMA NO ESTA RELACIONADO CON LA TEXTURA SINO CON LA MATRIZ. CUANDO HACEMOS EL FLIP SE VE LA CARA INVERTIDA CORRECTAMENTE, ES DECIR QUE LA TEXTURA FUNCIONA BIEN.
    // 
    entity1.texture = textureLee;
    
    camera = Camera();
    
    

    //modelMatrix4.RotateLocal(1*(PI/10.0f),rotation_axis);
    
    //predeterminem a camara en perspectiva
    camera.LookAt(eye, center, up);
    camera.SetPerspective(fov, framebuffer.width / (float)framebuffer.height, near_plane, far_plane);

    zBuffer=FloatImage(this->window_width, this->window_height);
    
    

}

// Render one frame
void Application::Render(void) 
{
    zBuffer.Fill(INT_MAX);
    framebuffer.Fill(Color::BLACK);
    entity1.Render(&framebuffer, &camara, Color::CYAN, &zBuffer);
    //entity7.Render(&framebuffer, &camara, Color::GREEN);
    //entity8.Render(&framebuffer, &camara, Color::BLUE);
    //entity9.Render(&framebuffer, &camara, Color::PURPLE);

    
    framebuffer.Render();//enviem el framebuffer a la pantalla
    
}

// Called after render
void Application::Update(float seconds_elapsed)
{
    
    //animen les entities
    
    if (multiples==true){
        
        /*
        entity7.Update(seconds_elapsed);
        
        
        entity8.Update(seconds_elapsed);
        
        
        entity9.Update(seconds_elapsed);*/
        
        
        
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

    case SDLK_c: {
        if (entity1.entityInitialized == false) {//comprovem que no estigui la entity ja inicialitzada
            entity1 = Entity(mesh1_lee);
            entity1.modelMatrix.Escalar(2.5, 2.5, 2.5);
            entity1.modelMatrix.Translate(0, -0.3, 0);
            entity1.entityInitialized = true;
        }
        else {
            entity1.drawInterpolatedColors = !entity1.drawInterpolatedColors;//canviem el bolea per fer laltre operació
        }
        entity1.tecla_z = false;
        entity1.tecla_c = true;
        entity1.tecla_t = false;
        break;
    }

    case SDLK_z: {
        if (entity1.entityInitialized == false) {//comprovem que no estigui la entity ja inicialitzada
            entity1 = Entity(mesh1_lee);
            entity1.modelMatrix.Escalar(2.5, 2.5, 2.5);
            entity1.modelMatrix.Translate(0, -0.3, 0);
            entity1.entityInitialized = true;
        }
        else {
            entity1.rasterize_with_Zbuffer = !entity1.rasterize_with_Zbuffer;//canviem el bolea per fer laltre operació
        }
        entity1.tecla_c = false;
        entity1.tecla_z = true;
        entity1.tecla_t = false;
        break;
    }

    case SDLK_t: {
        if (entity1.entityInitialized == false) {//comprovem que no estigui la entity ja inicialitzada
            //modelMatrix_txt = Matrix44();
            //modelMatrix_txt.SetIdentity();
            entity1 = Entity(mesh1_lee,modelMatrix_txt,textureLee);
            
            entity1.modelMatrix.Escalar(2.5, 2.5, 2.5);
            entity1.modelMatrix.Translate(0, -0.3, 0);
            //entity1.setTexture(textureLee);
            entity1.entityInitialized = true;
        }
        else {
            entity1.mesh_texture = !entity1.mesh_texture;
        }

        entity1.tecla_c = false;
        entity1.tecla_z = false;
        entity1.tecla_t = true;
        break;
    }

    }
}



//TODA ESTA PARTE NO FUNCIONA CORRECTAMENTE, NO HEMOS LOGRADO LOCALIZAR LOS FALLOS EN EL CODIGO

void Application::OnMouseButtonDown(SDL_MouseButtonEvent event)
{ /*//MIRAR CUANDO SE PRESIONA EL BOTON
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

    */
}


void Application::OnMouseButtonUp(SDL_MouseButtonEvent event) {
    //MIRAR CUANDO SE DEJA DE PULSAR EL BOTON

    /*if (event.button == SDL_BUTTON_LEFT) {
        leftMouse = false; //boton izq ya no esta presionado
    }

    if (event.button == SDL_BUTTON_RIGHT) {
        rightMouse = false;
    }*/
}

//PARA CUANDO EL RATON ESTA EN MOVIMIENTO
void Application::OnMouseMove(SDL_MouseButtonEvent event) {

    
    if (event.button == SDL_BUTTON_LEFT) {
        camera.Orbit(-mouse_delta.x * 0.01, Vector3::UP);
        camera.Orbit(-mouse_delta.y * 0.01, Vector3::RIGHT);
    }

}



void Application::OnWheel(SDL_MouseWheelEvent event)
{
    float dy = event.preciseY;
    camera.Zoom(dy < 0 ? 1.1 : 0.9);

}

void Application::OnFileChanged(const char* filename) {
    Shader::ReloadSingleShader(filename);
}

    
    
