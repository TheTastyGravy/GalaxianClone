#pragma once
#include <vector>
#include "raymath.h"

// All possible tags an object can have
enum class Tag
{
	Player
};


// Abstract object class that all game objects should inherit from
class GameObject
{
	// GameObjectPool needs access to the objects tags
	friend class GameObjectPool;

private:
	// All the tags this object has. This should only be accessed by GameObjectPool
	std::vector<Tag> tags;

protected:
	Vector2 position;
	float rotation;

public:
	GameObject(Vector2 position = { 0, 0 }, float rotation = 0);
	virtual ~GameObject();

	virtual void update(float deltaTime) = 0;
	virtual void draw() = 0;


	void setPos(Vector2 pos) { position = pos; }
	Vector2 getPos() const { return position; }

	void setRot(float rot) { rotation = rot; }
	float getRot() const { return rotation; }


	// Add 'tag' to the object
	void addTag(Tag tag);
	// Remove 'tag' from the object, if it has it
	void removeTag(Tag tag);
};