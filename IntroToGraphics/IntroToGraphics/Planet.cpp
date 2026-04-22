#include <cmath> // for fmodf
#include <cstddef>
#include <iostream>
#include "Planet.h"

Planet::Planet(float radius, float distanceFromSun, float rotationSpeed, Mesh* mesh, Texture* texture, float startAngle)
    : size(radius), radius(radius), distanceFromSun(distanceFromSun), rotationSpeed(rotationSpeed), mesh(mesh), texture(texture), currentRotation(0.0f), orbitAngle(startAngle)
{
}

void Planet::Update(float deltaTime)
{
    // Guard against negative or zero deltaTime gracefully (no-op if non-positive)
    if (deltaTime <= 0.0f)
        return;

    // Update rotations and keep angles bounded to [0, 360) to avoid floating-point growth.
    currentRotation = std::fmod(currentRotation + rotationSpeed * deltaTime, 360.0f);
    if (currentRotation < 0.0f) currentRotation += 360.0f;

    orbitAngle = std::fmod(orbitAngle + (rotationSpeed / 10.0f) * deltaTime, 360.0f);
    if (orbitAngle < 0.0f) orbitAngle += 360.0f;
}

void Planet::Draw()
{
    // Defensive checks: ensure mesh and vertex data are present before attempting to use them.
    if (mesh == nullptr || mesh->vertices == nullptr || mesh->numVertices <= 0)
    {
        return;
    }

    glPushMatrix();
    glRotatef(orbitAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(distanceFromSun, 0.0f, 0.0f);
    glRotatef(currentRotation, 0.0f, 1.0f, 0.0f);
    glScalef(size, size, size);

    // Only enable/bind texture when we have a valid texture id
    if (texture != nullptr && texture->id != 0)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture->id);
    }
    else
    {
        glDisable(GL_TEXTURE_2D);
    }

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < mesh->numVertices; ++i)
    {
        const auto& v = mesh->vertices[i];
        glNormal3f(v.nx, v.ny, v.nz);
        glTexCoord2f(v.u, v.v);
        glVertex3f(v.x, v.y, v.z);
    }
    glEnd();

    if (texture != nullptr && texture->id != 0)
    {
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();
}