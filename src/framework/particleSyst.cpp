#include "utils.h"
#include "image.h"
#include "particleSyst.h"
#include "texture.h"




void particleSyst::Init(int width, int height) {
	for (int i = 0; i < MAX_PARTICLES; i++) {
		particles[i].position = Vector2(static_cast<float>(rand() % width), static_cast<float>(rand() % height));//W=780 I H=580, posicion inicial random
		particles[i].velocity = Vector2(static_cast<float>((rand() % 200 - 100) / 100.0f), static_cast<float>((rand() % 200 - 100) / 100.0f))*20;//velocitat i direccio d'entre -1 i 1, velocidad aleatoria en direciones random
		//particles[i].velocity.normalize(); // Make sure the velocity vector has length 1
		particles[i].color = Color(rand()%255, rand() % 255, rand() % 255);
		particles[i].acceleration = 0.0f; //acceleration constante, empezamos sin.
		particles[i].ttl = 1.0f; //tiempo vida inicial
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
			Vector2 displacement = particles[i].velocity * dt; // almacena el desplazamiento de la posición,  equacion: P0 = P + V*t
			particles[i].position = particles[i].position + displacement;
			particles[i].ttl -= dt;
		}
	}
}

