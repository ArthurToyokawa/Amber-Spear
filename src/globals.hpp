#pragma once

#include <systems/soundSystem.hpp>
#include <systems/pointCounter.hpp>
#include <systems/physicsSystem.hpp>
#include <systems/gameStateSystem.hpp>
#include <gameObject/gameObjectGenerator.hpp>
#include <systems/stageSystem.hpp>
#include "world.hpp"
#include <menu/menuWorld.hpp>
#include <menu/menuItemGenerator.hpp>
#include <menu/menuManager.hpp>
#include <scoreboard/fileManager.hpp>

inline GameStateSystem gGameStateSystem;
inline SoundSystem gSoundSystem;
inline PhysicsSystem gPhysicsSystem;
inline StageSystem gStageSystem;
inline PointCounter gPointCounter;
inline FileManager gFileManager;

inline GameObjectGenerator *gGameObjectGenerator;
inline World gWorld;
inline MenuWorld gMenuWorld;
inline MenuItemGenerator gMenuItemGenerator;
inline MenuManager gMenuManager;

void initializeGlobals();
