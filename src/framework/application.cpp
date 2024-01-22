#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h" 

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
	if (framebuffer.LoadPNG("images/black.png") == false) {
		std::cout << "Image not found!" << std::endl;
	}

	/*if (framebuffer.LoadPNG("images/blue.png") == false) {
		std::cout << "Image not found!" << std::endl; 
	}
	if (framebuffer.LoadPNG("images/circle.png") == false) {
		std::cout << "Image not found!" << std::endl;
	}
	if (framebuffer.LoadPNG("images/clear.png") == false) {
		std::cout << "Image not found!" << std::endl;
	}
	if (framebuffer.LoadPNG("images/cyan.png") == false) {
		std::cout << "Image not found!" << std::endl;
	}
	if (framebuffer.LoadPNG("images/eraser.png") == false) {
		std::cout << "Image not found!" << std::endl;
	}
	if (framebuffer.LoadPNG("images/fruits.png") == false) {
		std::cout << "Image not found!" << std::endl;

	}
	if (framebuffer.LoadPNG("images/green.png") == false) {
		std::cout << "Image not found!" << std::endl;
	}
	if (framebuffer.LoadPNG("images/line.png") == false) {
		std::cout << "Image not found!" << std::endl;
	}
	if (framebuffer.LoadPNG("images/load.png") == false) {
		std::cout << "Image not found!" << std::endl;
	}
	if (framebuffer.LoadPNG("images/pink.png") == false) {
		std::cout << "Image not found!" << std::endl;
	}
	if (framebuffer.LoadPNG("images/rectangle.png") == false) {
		std::cout << "Image not found!" << std::endl;
	}
	if (framebuffer.LoadPNG("images/red.png") == false) {
		std::cout << "Image not found!" << std::endl;

	}
	if (framebuffer.LoadPNG("images/save.png") == false) {
		std::cout << "Image not found!" << std::endl;
	}
	if (framebuffer.LoadPNG("images/toolbar.png") == false) {
		std::cout << "Image not found!" << std::endl;
	}*/


}

// Render one frame
void Application::Render(void) //EL  NOSTRE CODI DEL MAIN
{
	//DRAWING LINES

	Color color(255, 255, 255);
    int startXline = 150;
    int startYline = 450;

	framebuffer.Fill(Color::BLACK);
	framebuffer.DrawLineDDA(startXline,startYline, startXline + 100 * std::cos(time), startYline + 100 * std::sin(time), color);

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
	
	//DRAWING TRIANGLE
	Vector2 p0(600, 100);
	Vector2 p1(750, 350);
	Vector2 p2(500, 450);
	bool isTriangleFilled = true;
	Color fillColor_tri = Color::CYAN;
	framebuffer.DrawTriangle(p0, p1, p2, fillColor_rect, isTriangleFilled, fillColor_tri);


	framebuffer.Render();//enviem el framebuffer a la pantalla
}

    //caldra fer modificacio del borde segons + o -
// Called after render
void Application::Update(float seconds_elapsed)
{
    
}

//keyboard press event 
void Application::OnKeyPressed( SDL_KeyboardEvent event )
{
	// KEY CODES: https://wiki.libsdl.org/SDL2/SDL_Keycode
	switch(event.keysym.sym) {
		case SDLK_ESCAPE: exit(0); break; // ESC key, kill the app
	}
}

void Application::OnMouseButtonDown( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) {

	}
}

void Application::OnMouseButtonUp( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) {

	}
}

void Application::OnMouseMove(SDL_MouseButtonEvent event)
{
	
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
