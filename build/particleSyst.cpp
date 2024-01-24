#include "particleSyst.h"
#include <framework/image.h>
#include <framework/framework.h>
#include <framework/application.h>
#include <framework/utils.h>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "GL/glew.h"
#include <cmath>




void particleSyst::Init(int width, int height) {
	for (int i = 0; i < MAX_PARTICLES; i++) {
		particles[i].position = Vector2(static_cast<float>(rand() % width), static_cast<float>(rand() % height));//W=780 I H=580
		particles[i].velocity = Vector2(static_cast<float>((rand() % 200 - 100) / 100.0f), static_cast<float>((rand() % 200 - 100) / 100.0f));//velocitat i direccio d'entre -1 i 1
		particles[i].velocity.normalize(); // Make sure the velocity vector has length 1
		particles[i].color = Color::WHITE;//color blanc per  la neu
		particles[i].acceleration = 0.1f; //acceleration constant
		particles[i].ttl = 5.0f;
		particles[i].inactive = false;
	}
}

void particleSyst::Render(Image* framebuffer) {
	for (int i = 0; i < MAX_PARTICLES; i++) {
		if (!particles[i].inactive) {
			framebuffer->SetPixelSafe(static_cast<int>(particles[i].position.x), static_cast<int>(particles[i].position.y), particles[i].color);
		}
	}
}


void particleSyst::Update(float dt) {
	for (int i = 0; i < MAX_PARTICLES; ++i) {
		if (!particles[i].inactive) {
			Vector2 displacement = particles[i].velocity * dt; // almacena el desplazamiento de la posición,  equacio: P0 = P + V*t
			particles[i].position = particles[i].position + displacement; //suma el desplazamiento al actual

			particles[i].ttl -= dt; //decreix el ttl

			if (particles[i].ttl <= 0.0f) { //fins q la particula mori
				particles[i].inactive = true;
			}

			/*if (particles[i].position.y > Image::height) { //farem efecte neu, cauen d'adalt i reapareixen.
				particles[i].position.y = 0; // Reubicar en la parte superior (nieve)
				particles[i].position.x = rand() % Image::width; // Posición aleatoria en x
				particles[i].ttl = 5.0f; // Reiniciar tiempo de vida
				particles[i].inactive = false; // Reactivar la partícula
			}*/
		}
	}
}