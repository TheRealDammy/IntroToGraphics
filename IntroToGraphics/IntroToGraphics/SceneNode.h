#pragma once

class SceneNode
{
public:
    SceneNode() : next(nullptr) {}
    virtual ~SceneNode() = default;
    virtual void Update(float deltaTime) = 0;
    virtual void Draw() = 0;

    SceneNode* next; // linked list pointer
};