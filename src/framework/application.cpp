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
    if (toolbar.LoadPNG("images/toolbar.png")==false){
        std::cout << "Image not found!" << std::endl;}
    //framebuffer.DrawImage(toolbar, 10, 10, true);
    
    
    if (bluecolor.LoadPNG("images/blue.png")==false){
        std::cout << "Image not found!" << std::endl;}
    //framebuffer.DrawImage(bluecolor, 275, 25, true);
    Button* bluebutton = new Button(&bluecolor, Vector2(275, 25));
    buttons.push_back(bluebutton);
 
    
    if (blackcolor.LoadPNG("images/black.png")==false){
        std::cout << "Image not found!" << std::endl;}
    //framebuffer.DrawImage(blackcolor, 125, 25, true);
    
    
    if (pinkcolor.LoadPNG("images/pink.png") == false) {
        std::cout << "Image not found!" << std::endl;}
    //framebuffer.DrawImage(pinkcolor, 375, 25, true);
    
    
    if (redcolor.LoadPNG("images/red.png") == false) {
        std::cout << "Image not found!" << std::endl;}
    //framebuffer.DrawImage(redcolor, 175, 25, true);
    
    
	if (circle.LoadPNG("images/circle.png") == false) {
		std::cout << "Image not found!" << std::endl;
	}
    //framebuffer.DrawImage(circle, 550, 25, true);
    Button* circlebutton = new Button(&circle, Vector2(550, 25));
    buttons.push_back(circlebutton);
    
    
	if (clear.LoadPNG("images/clear.png") == false) {
		std::cout << "Image not found!" << std::endl;
	}
    //framebuffer.DrawImage(clear, 25, 25, true);
    
    
	if (cyan.LoadPNG("images/cyan.png") == false) {
		std::cout << "Image not found!" << std::endl;
	}
    //framebuffer.DrawImage(cyan, 425, 25, true);
    
    
    if (eraser.LoadPNG("images/eraser.png") == false) {
        std::cout << "Eraser image not found!" << std::endl;
    }
    //framebuffer.DrawImage(eraser,625, 25, true);

    
    if (fruits.LoadPNG("images/fruits.png") == false) {
        std::cout << "Fruits image not found!" << std::endl;
    }
    
    //framebuffer.DrawImage(fruits, 725, 25, true);

    
    if (green.LoadPNG("images/green.png") == false) {
        std::cout << "Green image not found!" << std::endl;
    }
    
    //framebuffer.DrawImage(green, 225, 25, true);

   /* Image line;
    if (line.LoadPNG("images/line.png") == false) {
        std::cout << "Line image not found!" << std::endl;
    }
    framebuffer.DrawImage(line, 675, 25;

    // Load
    Image load;
    if (load.LoadPNG("images/load.png") == false) {
        std::cout << "Load image not found!" << std::endl;
    }
    framebuffer.DrawImage(load, , 25, true);

    // Rectangle
    Image rectangle;
    if (rectangle.LoadPNG("images/rectangle.png") == false) {
        std::cout << "Rectangle image not found!" << std::endl;
    }
    framebuffer.DrawImage(rectangle, , 25, true);

    Image save;
	if (save.LoadPNG("images/save.png") == false) {
		std::cout << "Image not found!" << std::endl;
	}
    framebuffer.DrawImage(save,, 25, true);
	}*/


}

// Render one frame
void Application::Render(void) 
{
    if (activeSyst) {
        particleSyst.Render(&framebuffer);
    }
    

	framebuffer.Render();//enviem el framebuffer a la pantalla
}

    //caldra fer modificacio del borde segons + o -
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
    switch (event.keysym.sym) {
        case SDLK_ESCAPE: exit(0); break; // ESC key, kill the app
            
        case SDLK_1:
            //framebuffer.DrawLineDDA(200, 200, 420, 500, Color::WHITE);
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
            framebuffer.Fill(Color::BLACK);
            framebuffer.DrawImage(toolbar, 10, 10, true);
            framebuffer.DrawImage(bluecolor, 275, 25, true);
            framebuffer.DrawImage(blackcolor, 125, 25, true);
            framebuffer.DrawImage(pinkcolor, 375, 25, true);
            framebuffer.DrawImage(redcolor, 175, 25, true);
            framebuffer.DrawImage(circle, 550, 25, true);
            framebuffer.DrawImage(clear, 25, 25, true);
            framebuffer.DrawImage(cyan, 425, 25, true);
            framebuffer.DrawImage(eraser,625, 25, true);
            framebuffer.DrawImage(fruits, 725, 25, true);
            framebuffer.DrawImage(green, 225, 25, true);
            break;
            
        case SDLK_6:
            activeSyst = true;
            particleSyst.Init(framebuffer.width, framebuffer.height);
            
            break;
        
        case SDLK_f:
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
            break;
            
    }
}
    
    
void Application::OnMouseButtonDown( SDL_MouseButtonEvent event )
{
        if (event.button == SDL_BUTTON_LEFT) {
            Vector2 mousePos = Vector2(static_cast<float>(event.x), static_cast<float>(event.y)-float(framebuffer.height));
            
            // Check if any button is clicked
            if (buttons[0]->IsMouseInside(mousePos)){
                this->drawingcolor=Color::BLUE;
                
            }
            /*if (lineButton.IsMouseInside(mousePos))
             {
             // Handle line button click
             //lineToolSelected = true;
             //rectangleToolSelected = false;
             //circleToolSelected = false;
             // ... Deselect other tools if needed
             }
             else if (rectangleButton.IsMouseInside(mousePos))
             {
             // Handle rectangle button click
             //lineToolSelected = false;
             rectangleToolSelected = true;
             //circleToolSelected = false;
             // ... Deselect other tools if needed
             }*/
            else if (buttons[1]->IsMouseInside(mousePos))
            {
                framebuffer.DrawCircle(this->startXcircle, this->startYcircle, this->radicircle, this->drawingcolor, this->borderWidth, this->isfilled, this->fillColor);
            }
            // ... Check other buttons
            
            // Check if the mouse is inside the drawing area
            //if (mousePos.x >= 0 && mousePos.x < window_width && mousePos.y >= 0 && mousePos.y < window_height)
            {
                // Handle drawing in the framebuffer based on the selected tool
                // ...
            }
        }
        
    }
    
    
    void Application::OnMouseButtonUp( SDL_MouseButtonEvent event )
    {
        if (event.button == SDL_BUTTON_LEFT) {
            // Reset tool states on mouse button release if needed
            lineToolSelected = false;
            rectangleToolSelected = false;
            circleToolSelected = false;
            // ... Reset other tool states if needed
        }
    }
    
    void Application::OnMouseMove(SDL_MouseButtonEvent event)
    {
        // Handle mouse movement
        // ...
        
        // Check if the left mouse button is pressed
        if (event.state & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            // Handle drawing while dragging the mouse
            if (lineToolSelected)
            {
                Color color(255, 255, 255);
                int startXline = 150;
                int startYline = 450;
                
                framebuffer.Fill(Color::BLACK);
                framebuffer.DrawLineDDA(startXline,startYline, startXline + 100 * std::cos(time), startYline + 100 * std::sin(time), color);
            }
            else if (rectangleToolSelected)
            {
                // Draw rectangles based on mouse movement
                // ...
            }
            else if (circleToolSelected)
            {
                // Draw circles based on mouse movement
                // ...
            }
            // ... Handle other tools
        }
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
