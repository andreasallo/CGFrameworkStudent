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
    
    
    camera.SetPerspective(fov, framebuffer.width / (float)framebuffer.height, pla_aprop, pla_lluny);
    //camera.SetOrthographic(-1, -1, 1, 1, -1, 1);
    
    camera.LookAt(eye, center, Vector3(0, -1, 0));
    
    
    
    
    
    
    
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
    /*entity2.Update(seconds_elapsed);
     
     entity3.Update(seconds_elapsed);
     
     entity4.Update(seconds_elapsed);
     
     }
     if (mult==true){
     entity2.Update(seconds_elapsed);
     entity3.Update(seconds_elapsed);*/
}

//keyboard press event 
void Application::OnKeyPressed( SDL_KeyboardEvent event )
{
    // KEY CODES: https://wiki.libsdl.org/SDL2/SDL_Keycode
    
    //crido funcio segons la tecla apretada
    switch (event.keysym.sym) {
        case SDLK_ESCAPE: exit(0); break; // ESC key, kill the app
    }
    if (event.keysym.sym == SDLK_1) {
        framebuffer.Fill(Color::BLACK);
        Mesh mesh1_lee = Mesh();
        mesh1_lee.LoadOBJ("meshes/lee.obj");
        Entity entity1 = Entity(mesh1_lee);
        entity1.modelMatrix.Escalar(1.25, 1.25, 1.25);
        entity1.modelMatrix.Translate(0, -0.3, 0);
        entity1.Render(&framebuffer, &camara, Color::CYAN);
                
                //entity1.setRotate(false);
                //individual=true;
                //multiples=false;
            }
            
    if (event.keysym.sym == SDLK_2) {
        framebuffer.Fill(Color::BLACK);
        
        
        mesh2_lee.LoadOBJ("meshes/lee.obj");
        entity2 = Entity(mesh2_lee);
        entity2.modelMatrix.Escalar(1.25, 1.25, 1.25);
        entity2.modelMatrix.Translate(0, -0.3, 0);
        entity2.Render(&framebuffer, &camera, Color::YELLOW);
        
        
        mesh3_anna.LoadOBJ("meshes/anna.obj");
        entity3 = Entity(mesh3_anna);
        entity3.modelMatrix.Translate(-0.55, 0.35, 0);
        entity3.Render(&framebuffer, &camera, Color::CYAN);
        
        mesh4_cleo.LoadOBJ("meshes/cleo.obj");
        entity4 = Entity(mesh4_cleo);
        entity4.modelMatrix.Translate(0.75, 0, 0);
        entity4.modelMatrix.Escalar(1.4,1.4,1.4);
        entity4.modelMatrix.Rotate(0.4, Vector3(-1,1,0));
        entity4.Render(&framebuffer, &camera, Color::BLUE);
        
        
        
        
        
        
        
        
        //entity2.Render(&framebuffer, &camera, Color::YELLOW);
         //entity3.Render(&framebuffer, &camera, Color::GREEN);
         //entity4.Render(&framebuffer, &camera, Color::BLUE);
         
         individual=false;
         multiples=true;
    }
            
    /*if (event.keysym.sym == SDLK_o) {
        framebuffer.Fill(Color::BLACK);
        camera.SetOrthographic(left, right, top, bottom, pla_aprop, pla_lluny);
    }
            
    if (event.keysym.sym == SDLK_p) {
        framebuffer.Fill(Color::BLACK);
        camera.SetPerspective(fov, framebuffer.width / (float)framebuffer.height, pla_aprop, pla_lluny);}

        /*case SDLK_n:
            camera_n = camera.near_plane;


        case SDLK_f:
            camera_n = camera.far_plane;

      
            
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
            */
            
    }

    
    
void Application::OnMouseButtonDown( SDL_MouseButtonEvent event )
{
    if (event.button == SDL_BUTTON_LEFT) {
        /*Vector2 mousePos = Vector2(static_cast<float>(event.x), static_cast<float>(event.y)-float(framebuffer.height));
        
        //comprovo si s'ha apretat algun botó
        if (buttons[0]->IsMouseInside(mousePos)){
            this->drawingcolor=Color::BLUE;
        }
        
        else if (buttons[4]->IsMouseInside(mousePos))
        {
            this->mousePos=mousePos;//guardo on s'ha clicat*/
        }
    }

//comprovem com el programa no respon de manera corresponent a les apretades de botó del ratolí
//caldria millorar aquesta implementació
    
void Application::OnMouseButtonUp( SDL_MouseButtonEvent event )
    {
        if (event.button == SDL_BUTTON_LEFT) {
            /*dibuixo les figures corresponents al botó apretat
            if (buttons[4]->IsMouseInside(mousePos)){
                framebuffer.DrawCircle(this->startXcircle, this->startYcircle, radicircle, this->drawingcolor, this->borderWidth, this->isfilled, this->fillColor);*/
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
