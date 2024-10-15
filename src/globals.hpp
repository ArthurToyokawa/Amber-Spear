#pragma once

#include <systems/soundSystem.hpp>
#include <systems/pointCounter.hpp>
#include <systems/physicsSystem.hpp>
#include "world.hpp"

inline SoundSystem gSoundSystem;
inline PointCounter gPointCounter;
inline PhysicsSystem gPhysicsSystem;
inline World gWorld;

void initializeGlobals();
