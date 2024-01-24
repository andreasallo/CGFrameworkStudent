#include "atlimage.h"
#include "GL/glew.h"
#include "GL/glew.h"
#include "ParticleSystem.h"
#include <algorithm>
#include <cmath>
#include <cmath>
#include <cstdlib>
#include <cstdlib>
#include <ctime>
#include <framework/image.h>
#include <fstream>
#include <iostream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <string>
#include <string.h>

ParticleSystem::ParticleSystem() {
	Init();
}


void ParticleSystem::Init() {
	for (int i = 0; i < MAX_PARTICLES; i++) {
		particles[i].position = Vector2(static_cast<float>(rand() % Application::window_height), static_cast<float>(rand() % Image::height));//W=780 I H=580
		particles[i].velocity = Vector2(static_cast<float>((rand() % 200 - 100) / 100.0f), static_cast<float>((rand() % 200 - 100) / 100.0f));//velocitat i direccio d'entre -1 i 1
		particles[i].velocity.Normalize(); // Make sure the velocity vector has length 1
		particles[i].color = Color(rand() % 256, rand() % 256, rand() % 256);//color alearori
		particles[i].acceleration = 0.1f; //acceleration constant
		particles[i].ttl = 5.0f;
		particles[i].inactive = false;
	}
}

void ParticleSystem::Render(Image* framebuffer) {
	for (int i = 0; i < MAX_PARTICLES; i++) {
		if (!particles[i].inactive) {
			framebuffer->DrawPixel(static_cast<int>(particles[i].position.x), static_cast<int>(particles[i].position.y), particles[i].color);
		}
	}
}

	
void ParticleSystem :: Update(float dt) {
	for (int i = 0; i < MAX_PARTICLES; ++i) {
		if (!particles[i].inactive) {
			Vector2 displacement = particles[i].velocity * dt; // almacena el desplazamiento de la posición,  equacio: P0 = P + V*t
			particles[i].position = particles[i].position + displacement; //suma el desplazamiento al actual

			particles[i].ttl -= dt; //decreix el ttl

			if (particles[i].ttl <= 0.0f) { //fins q la particula mori
				particles[i].inactive = true;
			}

			if(particles[i].position.y > Image::height) {
				particles[i].position.y = 0; // Reubicar en la parte superior (nieve)
				particles[i].position.x = rand() % Image::width; // Posición aleatoria en x
				particles[i].ttl = 5.0f; // Reiniciar tiempo de vida
				particles[i].inactive = false; // Reactivar la partícula
		}
	}
}