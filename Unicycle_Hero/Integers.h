#pragma once

uint8_t i = 0;
bool Collide = false;
int gamestate = 0;
int score = 0;
class Player
{
  public:
  uint8_t x = 58;
  uint8_t y = 28;
  bool dead = false;
  bool left = false;
  bool right = false;
};
Player player;

struct Object
{
  public:
  int x = 3;
  int y = 0;
  bool randomize = true;
  int type = 0;
};
Object object[10];

