#include <cmath> // for fmodf
#include <cstddef>
#include <iostream>
#include "Planet.h"

// Planet constructor: initialize member state. Orbital/rotation angles are in degrees.
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

// Update orbital and rotational state. deltaTime should be > 0. Defensive early return on non-positive input.
void Planet::Update(float deltaTime)
{
    // Guard against negative or zero deltaTime gracefully (no-op if non-positive)
    if (deltaTime <= 0.0f)
        return;

    // Update rotations and keep angles bounded to [0, 360) to avoid floating-point growth.
    currentRotation = std::fmod(currentRotation + rotationSpeed * deltaTime, 360.0f);
    if (currentRotation < 0.0f) currentRotation += 360.0f;

    // Orbit speed is simplified (rotationSpeed / 10.0f). Keep angle normalized.
    orbitAngle = std::fmod(orbitAngle + (rotationSpeed / 10.0f) * deltaTime, 360.0f);
    if (orbitAngle < 0.0f) orbitAngle += 360.0f;

    // Update child nodes (e.g., moon)
    for (Planet* child : children)
    {
        if (child != nullptr)
            child->Update(deltaTime);
    }

    // Compute approximate world position from orbitAngle and distanceFromSun.
    worldX = cos(orbitAngle * 3.14159f / 180.0f) * distanceFromSun;
    worldY = 0.0f;
    worldZ = -sin(orbitAngle * 3.14159f / 180.0f) * distanceFromSun;
}

// Draw the planet using immediate mode (glBegin/glEnd) and apply hierarchical transforms.
// The worldX/Y/Z values are updated here as well to reflect the final transform.
void Planet::Draw()
{
    // Defensive checks: ensure mesh and vertex data are present before attempting to use them.
    if (mesh == nullptr || mesh->vertices == nullptr || mesh->numVertices <= 0)
    {
        return;
    }

    glPushMatrix();

    // Apply orbit rotation then translate outward by distanceFromSun.
    glRotatef(orbitAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(distanceFromSun, 0.0f, 0.0f);

    // Read modelview to compute approximate world coordinates for this planet (used for tracking)
    float matrix[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
    worldX = -(matrix[12] * matrix[0] + matrix[13] * matrix[1] + matrix[14] * matrix[2]);
    worldY = -(matrix[12] * matrix[4] + matrix[13] * matrix[5] + matrix[14] * matrix[6]);
    worldZ = -(matrix[12] * matrix[8] + matrix[13] * matrix[9] + matrix[14] * matrix[10]);

    // Tilt the orbit plane and apply a second orbit rotation to ensure tilt is respected.
    glRotatef(orbitInclination, 0.0f, 0.0f, 1.0f); // tilt the orbit plane
    glRotatef(orbitAngle, 0.0f, 1.0f, 0.0f);        // orbit around tilted axis
    glScalef(size, size, size);

    // Bind texture if available; otherwise render untextured.
    if (texture != nullptr && texture->id != 0)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture->id);
    }
    else
    {
        glDisable(GL_TEXTURE_2D);
    }

    // If this planet is the sun/light source, temporarily disable lighting so the sun appears bright.
    if (isLightSource) glDisable(GL_LIGHTING);

    // Draw the mesh using normals and texture coordinates if present.
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

    // If a texture was enabled earlier, disable it now to not affect subsequent drawing.
    if (texture != nullptr && texture->id != 0)
    {
        glDisable(GL_TEXTURE_2D);
    }

    // Draw rings if present
    if (hasRings)
    {
        DrawRings(ringInner, ringOuter);
    }

    // Draw children (e.g., moon) in local space
    for (Planet* child : children)
    {
        if (child != nullptr)
            child->Draw();
    }

    glPopMatrix();
}

// Draw a simple ring using a triangle strip. Visual only, not physically accurate.
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