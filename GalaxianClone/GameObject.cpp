#include "GameObject.h"
#include "GameObjectPool.h"


GameObject::GameObject(Vector2 position, float rotation) :
	position(position),
	rotation(rotation)
{
	// Add this object to the pool
	GameObjectPool::addToPool(this);
}

GameObject::~GameObject()
{
	// Remove this object from the pool
	GameObjectPool::removeFromPool(this);
}


void GameObject::addTag(Tag tag)
{
	// Add the tag to the list
	tags.push_back(tag);
}

void GameObject::removeTag(Tag tag)
{
	// Find the tag and remove it
	for (int i = 0; i < tags.size(); i++)
	{
		if (tags[i] == tag)
			tags.erase(tags.begin() + i);
	}
}