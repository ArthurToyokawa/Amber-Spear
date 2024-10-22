#include <gameObject/gameObject.hpp>

void World::clearSpells()
{
  for (auto spell : spells)
  {
    if (spell)
    {
      spell->removeChildren();
      delete spell;
    }
  }
  spells.clear();
}

void World::clearObjects()
{
  for (auto object : objects)
  {
    if (object)
    {
      object->removeChildren();
      delete object;
    }
  }
  objects.clear();
}

void World::clearMapObjects()
{
  for (auto mapObject : mapObjects)
  {
    if (mapObject)
    {
      mapObject->removeChildren();
      delete mapObject;
      mapObject = nullptr;
    }
  }
}

void World::clearPlayers()
{
  if (player)
  {
    player->removeChildren();
    delete player;
    player = nullptr;
  }
}