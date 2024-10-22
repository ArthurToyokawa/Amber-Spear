#pragma once

#include <systems/soundSystem.hpp>
#include <systems/pointCounter.hpp>
#include <systems/physicsSystem.hpp>
#include <gameObject/gameObjectGenerator.hpp>
#include <systems/stageSystem.hpp>
#include "world.hpp"

inline SoundSystem gSoundSystem;
inline PointCounter gPointCounter;
inline PhysicsSystem gPhysicsSystem;
inline GameObjectGenerator *gGameObjectGenerator;
inline StageSystem gStageSystem;
inline World gWorld;

void initializeGlobals();
