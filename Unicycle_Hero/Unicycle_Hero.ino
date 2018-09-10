#include <Arduino.h>
#include <Arduboy2.h>
#include "Integers.h"
#include "Bitmaps.h"
Arduboy2 arduboy;

void DrawPlayer();
void Draw();
void Signals();
void setup();
void loop();
void DrawPlayer()
{
 if(player.left == true){ arduboy.drawBitmap(player.x,player.y,Player_L,16,16);}
 else if(player.right == true){ arduboy.drawBitmap(player.x,player.y,Player_R,16,16);}
 else{arduboy.drawBitmap(player.x,player.y,Player,16,16);}
   if(player.left == true){arduboy.setCursor(48,54);arduboy.print("Nice!");}
  else if(player.right == true){arduboy.setCursor(48,54);arduboy.print("Cool!");}
 if(Collide == true)
 {
  if(score > 20){score+=2;}
  else{score+=1;}
 }
}
void Draw()
{
  arduboy.drawRect(2,-1,18,68);
  arduboy.drawRect(2,34,18,16);
  arduboy.setCursor(21,0);
  if(score >= 20){arduboy.print("x2");}
} 
void Signals()
{
  for(i = 0;i < 1;++i)
  {
   if(object[i].randomize == true){object[i].y = 0;object[i].type = random(1,7);object[i].randomize = false;}
   if(object[i].type == 1){arduboy.drawBitmap(object[i].x,object[i].y,Up,16,16);}
   else if(object[i].type == 2){arduboy.drawBitmap(object[i].x,object[i].y,Down,16,16);}
   else if(object[i].type == 3){arduboy.drawBitmap(object[i].x,object[i].y,Left,16,16);}
   else if(object[i].type == 4){arduboy.drawBitmap(object[i].x,object[i].y,Right,16,16);}
   else if(object[i].type == 5){arduboy.drawBitmap(object[i].x,object[i].y,A_1,16,16);}
   else if(object[i].type == 6){arduboy.drawBitmap(object[i].x,object[i].y,B_1,16,16);}
     if(score >= 20 and object[i].y > 16){object[i].y+=2;}
     else{object[i].y++;}
   if(object[i].y > 80){player.dead = true;}
   Rect rectA{object[i].x,object[i].y,16,16};
   Rect rectB{2,34,18,16};
   if(arduboy.collide(rectA,rectB))
   {
    if(object[i].type == 1 and arduboy.pressed(UP_BUTTON)){Collide  = true;object[i].randomize = true;player.left = false;player.right = false;}
    else if(object[i].type == 2 and arduboy.pressed(DOWN_BUTTON)){Collide  = true;object[i].randomize = true;player.left = false;player.right = false;}
    else if(object[i].type == 3 and arduboy.pressed(LEFT_BUTTON)){Collide  = true;player.left = true;object[i].randomize = true;}
    else if(object[i].type == 4 and arduboy.pressed(RIGHT_BUTTON)){Collide  = true;player.right = true;object[i].randomize = true;}
    else if(object[i].type == 5 and arduboy.pressed(A_BUTTON)){Collide  = true;object[i].randomize = true;player.left = false;player.right = false;}
    else if(object[i].type == 6 and arduboy.pressed(B_BUTTON)){Collide  = true;object[i].randomize = true;player.left = false;player.right = false;}
    else if(arduboy.pressed(UP_BUTTON)){player.dead = true;}
    else if(arduboy.pressed(DOWN_BUTTON)){player.dead = true;}
    else if(arduboy.pressed(LEFT_BUTTON)){player.dead = true;}
    else if(arduboy.pressed(RIGHT_BUTTON)){player.dead = true;}
    else if(arduboy.pressed(A_BUTTON)){player.dead = true;}
    else if(arduboy.pressed(B_BUTTON)){player.dead = true;}
   }
    else{Collide = false;}
    if(player.dead == true){object[i].y = 0;}
        }
      }       
void setup()
{
  arduboy.begin();
  arduboy.setFrameRate(40);
  arduboy.initRandomSeed();
}

void loop()
{
  switch( gamestate ){
    case 0:
    arduboy.clear();
    arduboy.drawBitmap(0,0,Map,100,50);
    arduboy.pollButtons();
    if(arduboy.justPressed(A_BUTTON)){gamestate = 1;}
    arduboy.display();
    break;
    case 1:
  arduboy.clear();
  arduboy.pollButtons();
  if(!arduboy.nextFrame())
    return;
  DrawPlayer();
  Draw();
  Signals();
  if(player.dead == true){gamestate = 2;}
  arduboy.setCursor(0,0);
  arduboy.print(score);
  arduboy.display();
  break;
  case 2:
    if(player.dead == true)
  {
    arduboy.clear();
    arduboy.pollButtons();
    arduboy.setCursor(38,0);
    arduboy.print("Game Over\n Press B to continue");
    arduboy.setCursor(38,28);
    arduboy.print("Score: ");
    arduboy.print(score);
    arduboy.drawBitmap(player.x,player.y,Player_Dead,16,16);
    if(arduboy.justPressed(B_BUTTON)){player.dead = false;gamestate = 0;score = 0;player.left = false;player.right = false;}
    arduboy.display();
  }
}}


