#pragma once

enum class TextureEnum
{
  amberSpear,
  berryBush,
  box,
  boxHeavy,
  darkBall,
  dirt,
  enemy1,
  enemy2,
  enemy3,
  error,
  fireball,
  grass,
  healthPotion,
  lava,
  manaPotion,
  mountain,
  player,
  player2,
  rock,
  roots,
  sand,
  snow,
  goatHead,
  COUNT
};
class TextureEnumUtils
{

public:
  const char *enumToString(TextureEnum e)
  {
    switch (e)
    {
      using enum TextureEnum;
    case amberSpear:
      return "amberSpear";
      break;
    case berryBush:
      return "berryBush";
      break;
    case box:
      return "box";
      break;
    case boxHeavy:
      return "boxHeavy";
      break;
    case darkBall:
      return "darkBall";
      break;
    case dirt:
      return "dirt";
      break;
    case enemy1:
      return "enemy1";
      break;
    case enemy2:
      return "enemy2";
      break;
    case enemy3:
      return "enemy3";
      break;
    case error:
      return "error";
      break;
    case fireball:
      return "fireball";
      break;
    case grass:
      return "grass";
      break;
    case healthPotion:
      return "healthPotion";
      break;
    case lava:
      return "lava";
      break;
    case manaPotion:
      return "manaPotion";
      break;
    case mountain:
      return "mountain";
      break;
    case player:
      return "player";
      break;
    case player2:
      return "player2";
      break;
    case rock:
      return "rock";
      break;
    case roots:
      return "roots";
      break;
    case sand:
      return "sand";
      break;
    case snow:
      return "snow";
      break;
    case goatHead:
      return "goatHead";
      break;
    case COUNT:
      return "error";
      break;
    default:
      return "error";
      break;
    }
  };

  const char *enumToFileLocation(TextureEnum e)
  {
    switch (e)
    {
      using enum TextureEnum;
    case amberSpear:
      return "assets/amberSpear.png";
      break;
    case berryBush:
      return "assets/berryBush.png";
      break;
    case box:
      return "assets/box.png";
      break;
    case boxHeavy:
      return "assets/boxHeavy.png";
      break;
    case darkBall:
      return "assets/darkBall.png";
      break;
    case dirt:
      return "assets/dirt.png";
      break;
    case enemy1:
      return "assets/enemy1.png";
      break;
    case enemy2:
      return "assets/enemy2.png";
      break;
    case enemy3:
      return "assets/enemy3.png";
      break;
    case error:
      return "assets/error.png";
      break;
    case fireball:
      return "assets/fireball.png";
      break;
    case grass:
      return "assets/grass.png";
      break;
    case healthPotion:
      return "assets/healthPotion.png";
      break;
    case lava:
      return "assets/lava.png";
      break;
    case manaPotion:
      return "assets/manaPotion.png";
      break;
    case mountain:
      return "assets/mountain.png";
      break;
    case player:
      return "assets/player.png";
      break;
    case player2:
      return "assets/player2.png";
      break;
    case rock:
      return "assets/rock.png";
      break;
    case roots:
      return "assets/roots.png";
      break;
    case sand:
      return "assets/sand.png";
      break;
    case snow:
      return "assets/snow.png";
      break;
    case goatHead:
      return "assets/goat16px.png";
      break;
    case COUNT:
      return "assets/error.png";
      break;
    default:
      return "assets/error.png";
      break;
    }
  };

  TextureEnum indexToEnum(int index)
  {
    return static_cast<TextureEnum>(index);
  };

  const char *indexToString(int index)
  {
    return enumToString(static_cast<TextureEnum>(index));
  };

  const char *indexToFileLocation(int index)
  {
    return enumToFileLocation(static_cast<TextureEnum>(index));
  };
};