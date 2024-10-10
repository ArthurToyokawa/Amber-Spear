#pragma once

#include "soundSystem.hpp"
#include "pointCounter.hpp"
#include "physicsSystem.hpp"

inline SoundSystem gSoundSystem;
inline PointCounter gPointCounter;
inline PhysicsSystem gPhysicsSystem;

void initializeGlobals();
