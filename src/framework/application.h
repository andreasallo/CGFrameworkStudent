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
#include "texture.h"


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
    //LAB3
    FloatImage zBuffer;
    
    //LAB2

    Camera camera;
    Mesh mesh1_lee = Mesh();
    Mesh mesh2_lee = Mesh();
    Mesh mesh3_anna = Mesh();
    //Mesh mesh4_cleo = Mesh();

    //TEXTURE
    Image* textureLee;
    Matrix44 modelMatrix_txt;
    
    Entity entity1;
    Entity entity2;
    Entity entity3;
    //Entity entity4;
    //CODI FUNCIONA
    Mesh mesh7_lee = Mesh();
    Entity entity7;
    Mesh mesh8_anna = Mesh();
    Entity entity8 = Entity(mesh8_anna);
    Mesh mesh8_leo = Mesh();
    Entity entity9 = Entity(mesh8_leo);

    
    bool individual;
    bool multiples;
    float camera_n = 0.0f;
    float fov=PI/4;
    float near_plane =0.01;
    float far_plane =100.0;

    float left = -5;
    float right = 5;
    float top = 2;
    float bottom = -2;
        
    Vector3 eye = Vector3(0.0f, 0.5f, 2.0f);
    Vector3 center = Vector3(0.0f, 0.0f, 0.0f);
    Vector3 up = Vector3(0.0f, 1.0f, 0.0f);

    Camera camara = Camera();

    bool leftMouse=false;
    bool rightMouse = false;
    int previ_MouseY, previ_MouseX;
    float distance_camera;
    
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
