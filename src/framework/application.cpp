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
    


}

// Render one frame
void Application::Render(void) 
{
    

	framebuffer.Render();//enviem el framebuffer a la pantalla
}

// Called after render
void Application::Update(float seconds_elapsed)
{
    if (activeSyst) {
        particleSyst.Update(seconds_elapsed);
    }  
}

//keyboard press event 
void Application::OnKeyPressed( SDL_KeyboardEvent event )
{
    Vector2 a, b, c;
    a=Vector2{600, 100}, b=Vector2{750, 350}, c=Vector2{500, 450};
    // KEY CODES: https://wiki.libsdl.org/SDL2/SDL_Keycode
    
    //crido funcio segons la tecla apretada
    switch (event.keysym.sym) {
        case SDLK_ESCAPE: exit(0); break; // ESC key, kill the app
            
        case SDLK_1:
            framebuffer.DrawLineDDA(200, 200, 420, 500, Color::WHITE);
            drawingline=true;
            break;
            
        case SDLK_2:
            framebuffer.DrawRectangle(100, 100, 300, 150, Color::RED, borderWidth, false, Color::WHITE);
            drawingrectangle=true;
            break;
            
        case SDLK_3:
            framebuffer.DrawCircle(600, 150, 120, Color::YELLOW, borderWidth, false, Color::GREEN);
            drawingcircle=true;
            break;
            
        case SDLK_4:
            framebuffer.DrawTriangle(a, b, c, Color::RED, false, Color::CYAN);
            drawingtriangle=true;
            break;
            
        case SDLK_5:
            drawingline=false;
            framebuffer.DrawImage(toolbar, 10, 10, true);
            framebuffer.DrawImage(clear, 25, 25, true);
            framebuffer.DrawImage(blackcolor, 125, 25, true);
            framebuffer.DrawImage(redcolor, 175, 25, true);
            framebuffer.DrawImage(bluecolor, 275, 25, true);
            framebuffer.DrawImage(pinkcolor, 375, 25, true);
            framebuffer.DrawImage(cyan, 425, 25, true);
            framebuffer.DrawImage(rectangle,475, 25, true);
            framebuffer.DrawImage(circle, 575, 25, true);
            framebuffer.DrawImage(eraser,625, 25, true);
            framebuffer.DrawImage(line, 525, 25,true);
            framebuffer.DrawImage(load,675,25, true);
            framebuffer.DrawImage(save,725, 25, true);
            break;
            
        case SDLK_6:
            activeSyst = true;
            particleSyst.Init(framebuffer.width, framebuffer.height);
            
            break;
        
            
        case SDLK_f:
            //caldrà tenir en compte quines figures estan dibuixades per pantalla per saber quines s'han d'omplir
            if(drawingrectangle==true){
                framebuffer.DrawRectangle(100, 100, 300, 150, Color::RED, borderWidth, true, Color::WHITE);
                filledrectangle=true;}
            if(drawingcircle==true){
                framebuffer.DrawCircle(600, 150, 120, Color::YELLOW, borderWidth, true, Color::GREEN);
                filledcircle=true;}
            if(drawingtriangle==true){
             framebuffer.DrawTriangle(a, b, c, Color::RED, true, Color::CYAN);
                filledtriangle=true;}
            break;
            
        case SDLK_PLUS:
            //caldrà tenir en compte quines figures estan dibuixades per pantalla per saber en quines cal augmentar el marge
            borderWidth=borderWidth+10;
            if(drawingrectangle==true){
                if(filledrectangle==true){framebuffer.DrawRectangle(100, 100, 300, 150, Color::RED, borderWidth, true, Color::WHITE);}
                else{framebuffer.DrawRectangle(100, 100, 300, 150, Color::RED, borderWidth, false, Color::WHITE);}
            }
            if(drawingcircle==true){
                if(filledcircle==true){framebuffer.DrawCircle(600, 150, 120, Color::YELLOW, borderWidth, true, Color::GREEN);}
                else{framebuffer.DrawCircle(600, 150, 120, Color::YELLOW, borderWidth, false, Color::GREEN);}
            }
            if(drawingtriangle==true){
                if(filledtriangle==true){framebuffer.DrawTriangle(a, b, c, Color::RED, true, Color::CYAN);}
                else{framebuffer.DrawTriangle(a, b, c, Color::RED, false, Color::CYAN);}
            }
            break;
            
        case SDLK_MINUS:
            //caldrà tenir en compte quines figures estan dibuixades per pantalla per saber en quines cal disminuir el marge
            framebuffer.Fill(Color::BLACK);
            if(borderWidth>10){ borderWidth=borderWidth-10;}
            if(drawingrectangle==true){
                if(filledrectangle==true){framebuffer.DrawRectangle(100, 100, 300, 150, Color::RED, borderWidth, true, Color::WHITE);}
                else{framebuffer.DrawRectangle(100, 100, 300, 150, Color::RED, borderWidth, false, Color::WHITE);}
            }
            if(drawingcircle==true){
                if(filledcircle==true){framebuffer.DrawCircle(600, 150, 120, Color::YELLOW, borderWidth, true, Color::GREEN);}
                else{framebuffer.DrawCircle(600, 150, 120, Color::YELLOW, borderWidth, false, Color::GREEN);}
            }
            if(drawingtriangle==true){
                if(filledtriangle==true){framebuffer.DrawTriangle(a, b, c, Color::RED, true, Color::CYAN);}
                else{framebuffer.DrawTriangle(a, b, c, Color::RED, false, Color::CYAN);}
            }
            if(drawingline==true){
                framebuffer.DrawLineDDA(200, 200, 420, 500, Color::WHITE);
            }
            break;
            
    }
}
    
    
void Application::OnMouseButtonDown( SDL_MouseButtonEvent event )
{
    if (event.button == SDL_BUTTON_LEFT) {
        Vector2 mousePos = Vector2(static_cast<float>(event.x), static_cast<float>(event.y)-float(framebuffer.height));
        
        //comprovo si s'ha apretat algun botó
        if (buttons[0]->IsMouseInside(mousePos)){
            this->drawingcolor=Color::BLUE;
        }
        
        else if (buttons[4]->IsMouseInside(mousePos))
        {
            this->mousePos=mousePos;//guardo on s'ha clicat
        }
        
    }
}

//comprovem com el programa no respon de manera corresponent a les apretades de botó del ratolí
//caldria millorar aquesta implementació
    
void Application::OnMouseButtonUp( SDL_MouseButtonEvent event )
    {
        if (event.button == SDL_BUTTON_LEFT) {
            //dibuixo les figures corresponents al botó apretat
            if (buttons[4]->IsMouseInside(mousePos)){
                framebuffer.DrawCircle(this->startXcircle, this->startYcircle, radicircle, this->drawingcolor, this->borderWidth, this->isfilled, this->fillColor);
            }
        }
    }
    
    void Application::OnMouseMove(SDL_MouseButtonEvent event)
    {
        /*if (event.state & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            if (lineToolSelected)
            {
            // Dibuixem linia depenent del moviment
            // ...
            }
            else if (rectangleToolSelected)
            {
                // Dibuixem rectangle depenent del moviment
                // ...
            }
            else if (circleToolSelected)
            {
                
            }
        }*/
    }
    
    void Application::OnWheel(SDL_MouseWheelEvent event)
    {
        float dy = event.preciseY;
        
        // ...
    }
    
    void Application::OnFileChanged(const char* filename)
    {
        Shader::ReloadSingleShader(filename);
    }
