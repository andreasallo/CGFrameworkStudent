#include "utils.h"
#include "image.h"
#include "particleSyst.h"






void particleSyst::Init(int width, int height) {
	for (int i = 0; i < MAX_PARTICLES; i++) {
		particles[i].position = Vector2(static_cast<float>(rand() % width), static_cast<float>(rand() % height));//W=780 I H=580
		particles[i].velocity = Vector2(static_cast<float>((rand() % 200 - 100) / 100.0f), static_cast<float>((rand() % 200 - 100) / 100.0f));//velocitat i direccio d'entre -1 i 1
		particles[i].velocity.normalize(); // Make sure the velocity vector has length 1
		particles[i].color = Color(rand() % 256, rand() % 256, rand() % 256);//color alearori
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
			particles[i].position = particles[i].position + displacement;
			particles[i].ttl -= dt;

			// Verifica si la partícula ha salido de la pantalla y reiníciala si es necesario
				if (particles[i].position.y > 580) {
					particles[i].position.y = 0; // Reubicar en la parte superior
					particles[i].position.x = rand() % 780; // Posición aleatoria en x
					particles[i].ttl = 5.0f; // Reiniciar tiempo de vida
				}

			// También podrías ajustar la lógica para reiniciar si el tiempo de vida es menor o igual a cero
			if (particles[i].ttl <= 0.0f) {
				particles[i].inactive = true; // Desactiva la partícula si ha alcanzado su tiempo de vida
			}
		}
	}
}

