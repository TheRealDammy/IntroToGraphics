#pragma once
#include "SceneNode.h"
#include "Structures.h"

class Planet : public SceneNode
{
public:
	Planet(float radius, float distanceFromSun, float rotationSpeed, Mesh* mesh, Texture* texture, float startAngle = 0.0f);
	~Planet() override = default;
	void Update(float deltaTime) override;
	void Draw() override;
	void SetTexture(Texture* texture);

private:
	float size;
	float radius;
	float distanceFromSun;
	float rotationSpeed;
	float currentRotation;
	float orbitAngle;
	Mesh* mesh;
	Texture* texture;
};