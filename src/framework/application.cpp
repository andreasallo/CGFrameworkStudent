#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h" 
#include "../../build/particleSyst.h"
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
    Image toolbar;
    if (toolbar.LoadPNG("images/toolbar.png")==false){
        std::cout << "Image not found!" << std::endl;}
    framebuffer.DrawImage(toolbar, 10, 10, true);
    
    
    
    Image bluecolor;
    if (bluecolor.LoadPNG("images/blue.png")==false){
        std::cout << "Image not found!" << std::endl;}
    framebuffer.DrawImage(bluecolor, 275, 25, true);
    Button* bluebutton = new Button(bluecolor, Vector2(275, 25));
    buttons.push_back(bluebutton);
    
    Image blackcolor;
    if (blackcolor.LoadPNG("images/black.png")==false){
        std::cout << "Image not found!" << std::endl;}
    framebuffer.DrawImage(blackcolor, 125, 25, true);
    
    Image pinkcolor;
    if (pinkcolor.LoadPNG("images/pink.png") == false) {
        std::cout << "Image not found!" << std::endl;}
    framebuffer.DrawImage(pinkcolor, 375, 25, true);
    
    Image redcolor;
    if (redcolor.LoadPNG("images/red.png") == false) {
        std::cout << "Image not found!" << std::endl;}
    framebuffer.DrawImage(redcolor, 175, 25, true);
    
    Image circle;
	if (circle.LoadPNG("images/circle.png") == false) {
		std::cout << "Image not found!" << std::endl;
	}
    framebuffer.DrawImage(circle, 550, 25, true);
    Button* circlebutton = new Button(circle, Vector2(550, 25));
    buttons.push_back(circlebutton);
    
    Image clear;
	if (clear.LoadPNG("images/clear.png") == false) {
		std::cout << "Image not found!" << std::endl;
	}
    framebuffer.DrawImage(clear, 25, 25, true);
    
    Image cyan;
	if (cyan.LoadPNG("images/cyan.png") == false) {
		std::cout << "Image not found!" << std::endl;
	}
    framebuffer.DrawImage(cyan, 425, 25, true);
    
    Image eraser;
    if (eraser.LoadPNG("images/eraser.png") == false) {
        std::cout << "Eraser image not found!" << std::endl;
    }
    framebuffer.DrawImage(eraser,625, 25, true);

    // Fruits
    Image fruits;
    if (fruits.LoadPNG("images/fruits.png") == false) {
        std::cout << "Fruits image not found!" << std::endl;
    }
    framebuffer.DrawImage(fruits, 725, 25, true);

    Image green;
    if (green.LoadPNG("images/green.png") == false) {
        std::cout << "Green image not found!" << std::endl;
    }
    framebuffer.DrawImage(green, 225, 25, true);

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
void Application::Render(void) //EL  NOSTRE CODI DEL MAIN
{

    /*
	//DRAWING LINES

	Color color(255, 255, 255);
    int startXline = 150;
    int startYline = 450;

	framebuffer.Fill(Color::BLACK);
	framebuffer.DrawLineDDA(200,200, 420, 500, Color::WHITE);

	//DRAWING RECTANGLE
	int height = 150;
	int width = 300;
	int startXrectangle = 100;
	int startYrectangle = 100;
	Color wh = Color::WHITE;
	bool isFilled = true;
	Color fillColor_rect = Color::RED;
	framebuffer.DrawRectangle(startXrectangle, startYrectangle, width, height, wh, borderWidth, isFilled, fillColor_rect);
    
    
    //DRAWING CIRCLE
    int radi = 120;
    int startXcircle = 600;
    int startYcircle = 150;
	Color fillColor_circle = Color::GREEN;
	Color yel = Color::YELLOW;
    framebuffer.DrawCircle(startXcircle, startYcircle, radi, yel, borderWidth, isFilled, fillColor_circle);
    framebuffer.DrawCircle(600, 150, 120, Color::YELLOW, borderWidth, true, Color::Green);
	
	//DRAWING TRIANGLE
	Vector2 p0(600, 100);
	Vector2 p1(750, 350);
	Vector2 p2(500, 450);
	bool isTriangleFilled = true;
	Color fillColor_tri = Color::CYAN;
	framebuffer.DrawTriangle(p0, p1, p2, fillColor_rect, isTriangleFilled, fillColor_tri);
    framebuffer.DrawTriangle((600, 100), (750, 350), (500, 450), Color::RED, true, Color::Cyan);

    
    */
    //drawing tool
    

	framebuffer.Render();//enviem el framebuffer a la pantalla
}

    //caldra fer modificacio del borde segons + o -
// Called after render
void Application::Update(float seconds_elapsed)
{
    const int screenWidth = 750;
    const int screenHeight = 550;

    particleSyst snow;
    snow.Init(screenWidth, screenHeight);

 
    /*//ANIMACION DE PARTICULAS
    // Mueve la posición de las partículas de nieve
    particle_system.Update(seconds_elapsed);

    // También podrías animar otros elementos o cambiar colores según sea necesario
    object_position.x += seconds_elapsed * 10;
    image_rotation_angle += seconds_elapsed;
    */
}

//keyboard press event 
void Application::OnKeyPressed( SDL_KeyboardEvent event )
{
    
	// KEY CODES: https://wiki.libsdl.org/SDL2/SDL_Keycode
    switch (event.keysym.sym) {
    case SDLK_ESCAPE: exit(0); break; // ESC key, kill the app

    case SDLK_1:
        framebuffer.DrawLineDDA(200, 200, 420, 500, Color::WHITE);
        break;

    case SDLK_2:
        framebuffer.DrawRectangle(100, 100, 300, 150, Color::RED, borderWidth, true, Color::WHITE);
        break;

    case SDLK_3:
        framebuffer.DrawCircle(600, 150, 120, Color::YELLOW, borderWidth, true, Color::GREEN);
        break;

    case SDLK_4:
        framebuffer.DrawTriangle((600, 100), (750, 350), (500, 450), Color::RED, true, Color::CYAN);
        break;

    case SDLK_5:
        break;

    case SDLK_6:
        break;

    case SDLK_f:
        break;

    case SDLK_PLUS:
        break;

    case SDLK_MINUS:
        break;
        
    }


void Application::OnMouseButtonDown( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) {
            Vector2 mousePos = Vector2(static_cast<float>(event.x), static_cast<float>(event.y));

            // Check if any button is clicked
        if (buttons[0]->IsMouseInside(mousePos)){
            this->colorselecionado=Color::BLUE;
            
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
