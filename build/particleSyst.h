#pragma once
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

class particleSyst
{
	static const int MAX_PARTICLES = 200;

	struct Particle {
        Vector2 position;
        Vector2 velocity; // Normalized speed and direction of the particle
        Color color;
        float acceleration;
        float ttl; // Time left until the particle expires
        bool inactive; // Particle is not used/expired, so it can be recreated
	};

  
    Particle particles[MAX_PARTICLES];

    public:
        void Init(int widht, int height);
        void Render(Image* framebuffer);
        void Update(float dt);
};

