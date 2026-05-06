#pragma once
#include "SceneNode.h"

// Very small scene graph implemented as a linked list.
// Each SceneNode is expected to implement Update() and Draw().
// Add() inserts nodes at the head; order will be reverse of insertion.
class SceneGraph
{
public:
    SceneGraph() : root(nullptr) {}

    // Add node to graph; node becomes new head
    void Add(SceneNode* node)
    {
        node->next = root;
        root = node;
    }

    // Update all nodes in the list. deltaTime is seconds (or milliseconds as used by caller).
    void UpdateAll(float deltaTime)
    {
        SceneNode* current = root;
        while (current != nullptr)
        {
            current->Update(deltaTime);
            current = current->next;
        }
    }

    // Draw all nodes in the list. Render order is insertion-reverse.
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
    SceneNode* root; // head of singly-linked list
};