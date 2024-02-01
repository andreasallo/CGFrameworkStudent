/*  
	+ This class encapsulates the application, is in charge of creating the data, getting the user input, process the update and render.
*/

#pragma once

#include "main/includes.h"
#include "framework.h"
#include "image.h"
#include "particleSyst.h"
#include "entity.h"
#include "camera.h"


class Application
{
private:
    std::vector<Button*> buttons;
    
    Color colorselecionado;
    bool bluecolorbuttonSelected;
    bool lineToolSelected;
    bool rectangleToolSelected;
    bool circleToolSelected;

public:
    
    //LAB2
    Entity entity1;
    Entity entity2;
    Entity entity3;
    Camera camera;
    Matrix44 modelMatrix1;
    Matrix44 modelMatrix2;
    Matrix44 modelMatrix3;
    Matrix44 modelMatrix4;
    bool individual;
    bool multiples;
    float camera_n = 0.0f;
    
    //LAB1
    bool isfilled=false;
    int borderWidth=20;  // Variable miembro para almacenar el ancho del borde
    int radicircle = 120;
    int startXcircle = 600;
    int startYcircle = 150;
    Color fillColor= Color::GREEN;
    Color drawingcolor;
    bool drawingline;
    bool drawingrectangle;
    bool drawingcircle;
    bool drawingtriangle;
    bool filledrectangle;
    bool filledcircle;
    bool filledtriangle;
    Image toolbar;
    Image bluecolor;
    Image blackcolor;
    Image pinkcolor;
    Image redcolor;
    Image circle;
    Image clear;
    Image cyan;
    Image eraser;
    Image fruits;
    Image green;
    Image line;
    Image load;
    Image rectangle;
    Image save;
    Vector2 mousePos;
    
	// Window

	SDL_Window* window = nullptr;
	int window_width;
	int window_height;

	float time;

	//PARTICLES
	particleSyst particleSyst;
	bool activeSyst = true;


	// Input
	const Uint8* keystate;
	int mouse_state; // Tells which buttons are pressed
	Vector2 mouse_position; // Last mouse position
	Vector2 mouse_delta; // Mouse movement in the last frame

	void OnKeyPressed(SDL_KeyboardEvent event);
	void OnMouseButtonDown(SDL_MouseButtonEvent event);
	void OnMouseButtonUp(SDL_MouseButtonEvent event);
	void OnMouseMove(SDL_MouseButtonEvent event);
	void OnWheel(SDL_MouseWheelEvent event);
	void OnFileChanged(const char* filename);

	// CPU Global framebuffer
	Image framebuffer;

	// Constructor and main methods
	Application(const char* caption, int width, int height);
	~Application();

	void Init( void );
	void Render( void );
	void Update( float dt );

	// Other methods to control the app
	void SetWindowSize(int width, int height) {
		glViewport( 0,0, width, height );
		this->window_width = width;
		this->window_height = height;
	}

	Vector2 GetWindowSize()
	{
		int w,h;
		SDL_GetWindowSize(window,&w,&h);
		return Vector2(float(w), float(h));
	}
};
