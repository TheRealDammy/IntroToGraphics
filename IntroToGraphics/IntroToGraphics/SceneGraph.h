#pragma once
#include "SceneNode.h"

class SceneGraph
{
public:
    SceneGraph() : root(nullptr) {}

    void Add(SceneNode* node)
    {
        node->next = root;
        root = node;
    }

    void UpdateAll(float deltaTime)
    {
        SceneNode* current = root;
        while (current != nullptr)
        {
            current->Update(deltaTime);
            current = current->next;
        }
    }

    void DrawAll()
    {
        SceneNode* current = root;
        while (current != nullptr)
        {
            current->Draw();
            current = current->next;
        }
    }

private:
    SceneNode* root;
};