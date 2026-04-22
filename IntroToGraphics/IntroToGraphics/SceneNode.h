#pragma once

class SceneNode
{
	public:
	SceneNode() = default;
	virtual ~SceneNode() = default;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;
};