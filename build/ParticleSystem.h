#pragma once
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <framework/image.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define PARTICLESYSTEM_H

struct Particle {
    Vector2 position;
    Vector2 velocity; // Normalized speed and direction of the particle
    Color color;
    float acceleration;
    float ttl; // Time left until the particle expires
    bool inactive; // Particle is not used/expired, so it can be recreated
};

class ParticleSystem{
    static const int MAX_PARTICLES = 1000;
    //wo
    Particle particles[MAX_PARTICLES];

public:
    ParticleSystem();
    void Init();
    void Render(Image* framebuffer);
    void Update(float dt);
};

