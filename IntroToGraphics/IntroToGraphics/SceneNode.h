#pragma once

// Base abstract class for scene graph nodes. Derived classes implement Update and Draw.
class SceneNode
{
public:
    SceneNode() : next(nullptr) {}
    virtual ~SceneNode() = default;

    // Update node state (called by SceneGraph). deltaTime is in seconds (or caller's units).
    virtual void Update(float deltaTime) = 0;

    // Draw node (called by SceneGraph)
    virtual void Draw() = 0;

    SceneNode* next; // linked list pointer used by SceneGraph
};