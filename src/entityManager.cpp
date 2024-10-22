
#include "entityManager.hpp"
#include "common.hpp"
#include <gameObject/gameObject.hpp>

// TODO SEPARAR ESSE TRATAMENTO EM PLAYER
void EntityManager::handleKeys(std::list<SDL_Keycode> keys)
{
  // TODO essas var só é necessario em player
  int playerXAcc = 0;
  int playerYAcc = 0;
  bool createFireball = false;
  for (auto key : keys)
  {
    switch (key)
    {
    case SDLK_w:
      playerYAcc -= PLAYER_ACCELERATION;
      break;
    case SDLK_s:
      playerYAcc += PLAYER_ACCELERATION;
      break;
    case SDLK_a:
      playerXAcc -= PLAYER_ACCELERATION;
      break;
    case SDLK_d:
      playerXAcc += PLAYER_ACCELERATION;
      break;
    case SDLK_t:
    {
      // creating fireball
      if (fbCooldown == 0)
      {
        gSoundSystem.playSound(0);
        createFireball = true;
      }
      break;
    }
    case SDLK_y:
    {
      std::cout << "Cant add Aura" << std::endl;
      if (massAuraCooldown == 0)
      {
        std::cout << "Adding Aura" << std::endl;
        massAuraCooldown = 250;
        auraSystem->addMassAura(gWorld.getPlayer());
        break;
      }
    }
    default:
      break;
    }
  }
  // se ele estiver andando em apenas uma direcao aumenta sua velocidade
  if (playerXAcc == 0)
  {
    playerYAcc += playerYAcc * 0.5;
  }
  if (playerYAcc == 0)
  {
    playerXAcc += playerXAcc * 0.5;
  }
  // logica para setar a animacao TODO VER SE DA PRA MELHORAR ISSO
  // std::cout << "start player anims" << std::endl;
  if (playerXAcc == 0 && playerYAcc == 0) // player parado
  {
    gWorld.getPlayer()->getSprite()->switchToDefaultAnimation();
  }
  else if (playerXAcc == 0) // player se movendo em y
  {
    if (playerYAcc > 0)
    {
      gWorld.getPlayer()->getSprite()->switchAnimation(4); // animDown = 4;
    }
    else
    {
      gWorld.getPlayer()->getSprite()->switchAnimation(3); // animUp = 3;
    }
  }
  else if (playerYAcc == 0) // player de movendo em X
  {
    if (playerXAcc > 0)
    {
      gWorld.getPlayer()->getSprite()->switchAnimation(2); // animRight = 2;
    }
    else
    {
      gWorld.getPlayer()->getSprite()->switchAnimation(1); // animLeft = 1;
    }
  }
  gWorld.getPlayer()->getPhysics()->setAcceleration(playerXAcc, playerYAcc);
  // criando entidades baseado nos clicks do jogador
  if (createFireball)
  {
    gWorld.getPlayer()->getSprite()->switchAnimation(5); // animCasting = 5;
    std::cout << "CREATING FB POS: " << gWorld.getPlayer()->getPosition().x << " " << gWorld.getPlayer()->getPosition().y << " " << playerXAcc << " " << playerYAcc << std::endl;
    GameObject *fb = gGameObjectGenerator->makeFireball(gWorld.getPlayer()->getPosition().x, gWorld.getPlayer()->getPosition().y, playerXAcc, playerYAcc);
    gWorld.getSpells().push_back(fb);
    fbCooldown = 10;
  }
  if (gWorld.hasPlayer2())
  {
    handleKeysP2(keys);
  }
}
// TODO SEPARAR ESSE TRATAMENTO EM PLAYER
void EntityManager::handleKeysP2(std::list<SDL_Keycode> keys)
{
  int playerXAcc = 0;
  int playerYAcc = 0;
  bool createFireball = false;
  for (auto key : keys)
  {
    switch (key)
    {
    case SDLK_UP:
      playerYAcc -= PLAYER_ACCELERATION;
      break;
    case SDLK_DOWN:
      playerYAcc += PLAYER_ACCELERATION;
      break;
    case SDLK_LEFT:
      playerXAcc -= PLAYER_ACCELERATION;
      break;
    case SDLK_RIGHT:
      playerXAcc += PLAYER_ACCELERATION;
      break;
    case SDLK_KP_1:
    {
      // creating fireball
      if (fbCooldown2 == 0)
      {
        gSoundSystem.playSound(0);
        createFireball = true;
      }
      break;
    }
    case SDLK_KP_2:
    {
      if (massAuraCooldown2 == 0)
      {
        std::cout << "Adding Aura" << std::endl;
        massAuraCooldown2 = 250;
        auraSystem->addMassAura(gWorld.getPlayer2());
        break;
      }
    }
    default:
      break;
    }
  }
  // se ele estiver andando em apenas uma direcao aumenta sua velocidade
  if (playerXAcc == 0)
  {
    playerYAcc += playerYAcc * 0.5;
  }
  if (playerYAcc == 0)
  {
    playerXAcc += playerXAcc * 0.5;
  }
  // logica para setar a animacao TODO VER SE DA PRA MELHORAR ISSO
  // std::cout << "start player anims" << std::endl;
  if (playerXAcc == 0 && playerYAcc == 0) // player parado
  {
    gWorld.getPlayer2()->getSprite()->switchToDefaultAnimation();
  }
  else if (playerXAcc == 0) // player se movendo em y
  {
    if (playerYAcc > 0)
    {
      gWorld.getPlayer2()->getSprite()->switchAnimation(4); // animDown = 4;
    }
    else
    {
      gWorld.getPlayer2()->getSprite()->switchAnimation(3); // animUp = 3;
    }
  }
  else if (playerYAcc == 0) // player de movendo em X
  {
    if (playerXAcc > 0)
    {
      gWorld.getPlayer2()->getSprite()->switchAnimation(2); // animRight = 2;
    }
    else
    {
      gWorld.getPlayer2()->getSprite()->switchAnimation(1); // animLeft = 1;
    }
  }
  gWorld.getPlayer2()->getPhysics()->setAcceleration(playerXAcc, playerYAcc);
  // criando entidades baseado nos clicks do jogador
  if (createFireball)
  {
    gWorld.getPlayer2()->getSprite()->switchAnimation(5); // animCasting = 5;
    std::cout << "CREATING FB POS: " << gWorld.getPlayer2()->getPosition().x << " " << gWorld.getPlayer2()->getPosition().y << " " << playerXAcc << " " << playerYAcc << std::endl;
    GameObject *fb = gGameObjectGenerator->makeFireball(gWorld.getPlayer2()->getPosition().x, gWorld.getPlayer2()->getPosition().y, playerXAcc, playerYAcc);
    gWorld.getSpells().push_back(fb);
    fbCooldown2 = 10;
  }
}

void EntityManager::update(float time)
{

  // update de auras e fisica
  // TODO se for um weakPointer pode ter um array separado disso e matamos o updatePhysics e updateAuras
  gWorld.getPlayer()->updateAuras(time);
  gWorld.getPlayer()->updatePhysics(time);
  if (gWorld.hasPlayer2())
  {
    gWorld.getPlayer2()->updateAuras(time);
    gWorld.getPlayer2()->updatePhysics(time);
  }
  for (auto it = gWorld.getObjects().begin(); it != gWorld.getObjects().end();)
  {
    auto &obj = *it;
    obj->updateAuras(time);
    obj->updatePhysics(time);
    ++it;
  }
  for (auto it = gWorld.getSpells().begin(); it != gWorld.getSpells().end();)
  {
    auto &fb = *it;
    fb->updatePhysics(time);
    ++it;
  }

  // checa e resolve colisoes
  gPhysicsSystem.handleCollisions();
  // remove objetos marcados para remoção (dead)
  removeDeadObjects();

  // transforma a pos de fisica em uma pos em px
  gWorld.getPlayer()->updateSprite();
  if (gWorld.hasPlayer2())
  {
    gWorld.getPlayer2()->updateSprite();
  }

  for (auto it = gWorld.getObjects().begin(); it != gWorld.getObjects().end();)
  {
    // TODO removendo objetos e spells fora da tela ATUALMENTE ISSO É INUTIL DPS TEM Q VER
    // AS PADREDES DA WINDOW SAO OBJETOS SE FOR DESCOMENTAR TEM QUE CRIAR UM ARRAY NOVO
    auto &obj = *it;
    // if (obj->getPosition().x > SCREEN_WIDTH || obj->getPosition().y > SCREEN_HEIGHT)
    // {
    //   delete obj;
    //   it = gWorld.getObjects().erase(it);
    // }
    // else
    // {
    obj->updateSprite();
    ++it;
    // }
  }
  for (auto it = gWorld.getSpells().begin(); it != gWorld.getSpells().end();)
  {
    auto &fb = *it;
    if (fb->getPosition().x > SCREEN_WIDTH || fb->getPosition().y > SCREEN_HEIGHT)
    {
      fb->kill();
      fb->removeChildren();
      delete fb;
      it = gWorld.getSpells().erase(it);
    }
    else
    {
      fb->updateSprite();
      ++it;
    }
  }
  if (fbCooldown != 0)
  {
    fbCooldown--;
  }
  if (massAuraCooldown != 0)
  {
    massAuraCooldown--;
  }
  if (gWorld.hasPlayer2())
  {
    if (fbCooldown2 != 0)
    {
      fbCooldown2--;
    }
    if (massAuraCooldown2 != 0)
    {
      massAuraCooldown2--;
    }
  }
}

void EntityManager::removeDeadObjects()
{
  for (auto it = gWorld.getSpells().begin(); it != gWorld.getSpells().end();)
  {
    auto &sp = *it;
    if (sp->isDead())
    {
      std::cout << "removing dead obj" << std::endl;
      sp->removeChildren();
      delete sp;
      it = gWorld.getSpells().erase(it);
    }
    else
    {
      ++it;
    }
  }
  for (auto it = gWorld.getObjects().begin(); it != gWorld.getObjects().end();)
  {
    auto &obj = *it;
    if (obj->isDead())
    {
      std::cout << "removing dead obj" << std::endl;
      obj->removeChildren();
      delete obj;
      it = gWorld.getObjects().erase(it);
    }
    else
    {
      ++it;
    }
  }
}