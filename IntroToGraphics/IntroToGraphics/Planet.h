#pragma once
#include "SceneNode.h"
#include "Structures.h"
#include <vector>

class Planet : public SceneNode
{
public:
	Planet(float radius, float distanceFromSun, float rotationSpeed, Mesh* mesh, Texture* texture, float startAngle = 0.0f, bool hasRings = false, float ringInner = 0.0f, float ringOuter = 0.0f, float orbitInclination = 0.0f);
	~Planet() override = default;
	void Update(float deltaTime) override;
	void Draw() override;
	void DrawRings(float innerRadius, float outerRadius);
	void SetRings(float innerRadius, float outerRadius);
	void AddChild(Planet* child) { children.push_back(child); }

public:
	bool isLightSource;

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