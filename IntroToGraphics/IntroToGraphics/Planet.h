#pragma once
#include "SceneNode.h"
#include "Structures.h"
#include <vector>

// Planet is a SceneNode representing a spherical body. It supports:
// - orbiting around origin using orbitAngle/distanceFromSun
// - rotation (currentRotation) for self-spin
// - optional rings and children (hierarchical transforms)
// - simple textured triangle rendering using a Mesh.
class Planet : public SceneNode
{
public:
	// Parameters:
	// radius: visual scale
	// distanceFromSun: radius of orbit
	// rotationSpeed: used both for spin and to drive orbit speed (simplified)
	// mesh, texture: rendering assets
	// startAngle: initial orbit angle in degrees
	// hasRings: whether to render rings
	// ringInner/ringOuter: ring dimensions (if hasRings)
	// orbitInclination: tilt of orbit plane
	Planet(float radius, float distanceFromSun, float rotationSpeed, Mesh* mesh, Texture* texture, float startAngle = 0.0f, bool hasRings = false, float ringInner = 0.0f, float ringOuter = 0.0f, float orbitInclination = 0.0f);
	~Planet() override = default;
	void Update(float deltaTime) override;
	void Draw() override;
	void DrawRings(float innerRadius, float outerRadius);
	void SetRings(float innerRadius, float outerRadius);
	void AddChild(Planet* child) { children.push_back(child); }

public:
	bool isLightSource;
	// World coordinates updated during Draw/Update to support camera tracking
	float worldX, worldY, worldZ;

private:
	float size;
	float radius;
	float distanceFromSun;
	float rotationSpeed;
	float currentRotation;
	float orbitAngle;
	float orbitInclination;
	Mesh* mesh;
	Texture* texture;	
	bool hasRings;
	float ringInner;
	float ringOuter;
	std::vector<Planet*> children;
};