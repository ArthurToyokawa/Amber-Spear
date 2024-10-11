#pragma once

#include "soundSystem.hpp"
#include "pointCounter.hpp"
#include "physicsSystem.hpp"
#include "world.hpp"

inline SoundSystem gSoundSystem;
inline PointCounter gPointCounter;
inline PhysicsSystem gPhysicsSystem;
inline World gWorld;

void initializeGlobals();
