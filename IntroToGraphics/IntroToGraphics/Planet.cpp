#include <cmath> // for fmodf
#include <cstddef>
#include <iostream>
#include "Planet.h"

Planet::Planet(float radius, float distanceFromSun, float rotationSpeed, Mesh* mesh, Texture* texture, float startAngle, bool hasRings, float ringInner, float ringOuter, float orbitInclination)
	: size(radius),
	  radius(radius),
	  distanceFromSun(distanceFromSun),
	  rotationSpeed(rotationSpeed),
	  currentRotation(0.0f),
	  orbitAngle(startAngle),
	  mesh(mesh),
	  texture(texture),
	  hasRings(hasRings),
	  ringInner(ringInner),
	  ringOuter(ringOuter),
	  orbitInclination(orbitInclination)
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

    for (Planet* child : children)
    {
        if (child != nullptr)
            child->Update(deltaTime);
    }
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
    glRotatef(orbitInclination, 0.0f, 0.0f, 1.0f); // tilt the orbit plane
    glRotatef(orbitAngle, 0.0f, 1.0f, 0.0f);        // orbit around tilted axis
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

    if (isLightSource) glDisable(GL_LIGHTING);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < mesh->numVertices; ++i)
    {
        const auto& v = mesh->vertices[i];
        glNormal3f(v.nx, v.ny, v.nz);
        glTexCoord2f(v.u, v.v);
        glVertex3f(v.x, v.y, v.z);
    }
    glEnd();
    if (isLightSource) glEnable(GL_LIGHTING);

    if (texture != nullptr && texture->id != 0)
    {
        glDisable(GL_TEXTURE_2D);
    }

    if (hasRings)
    {
        DrawRings(ringInner, ringOuter);
    }

    for (Planet* child : children)
    {
        if (child != nullptr)
            child->Draw();
    }

    glPopMatrix();
}

void Planet::DrawRings(float innerRadius, float outerRadius)
{
    glDisable(GL_TEXTURE_2D);
    glColor3f(0.8f, 0.7f, 0.5f); // golden beige colour
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= 360; i += 5)
    {
        float angle = i * 3.14159f / 180.0f;
        glVertex3f(cos(angle) * innerRadius, 0.0f, sin(angle) * innerRadius);
        glVertex3f(cos(angle) * outerRadius, 0.0f, sin(angle) * outerRadius);
    }
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f); // reset colour
    glEnable(GL_TEXTURE_2D);
}

void Planet::SetRings(float innerRadius, float outerRadius)
{
    hasRings = true;
    ringInner = innerRadius;
    ringOuter = outerRadius;
}