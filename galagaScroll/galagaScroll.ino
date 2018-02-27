#include <Arduboy2.h>

Arduboy2 ab;

const unsigned char background[] PROGMEM = {
  0x00, 0x00, 0x6, 0x4, 0x00, 0x00, 0x00, 0x40, 0x60, 0x00, 0x2, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x38, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6, 0x6, 0x00, 0x00, 0x00, 0x00,
};

const unsigned char player [] PROGMEM = {
  0x00, 0x2, 0x26, 0xae, 0xfe, 0xfa, 0xf2, 0x72, 0x52, 0xd0, 0xd0, 0x90, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0xc9, 0xeb, 0xff, 0xbf, 0x9f, 0x9d, 0x94, 0x16, 0x17, 0x13, 0x3, 0x1, 0x1, 0x1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
boolean start = false;
int playerx = 5;
int playery = 10;
int scroll = 0;
int pad;
int oldpad,oldpad3;

int firePressed = 0;

int proj1_x = 0;
int proj1_y = 0;
int proj1_v = 0;

int proj2_x = 0;
int proj2_y = 0;
int proj2_v = 0;

int proj3_x = 0;
int proj3_y = 0;
int proj3_v = 0;

int proj_count = 1;

void setup() {
  // put your setup code here, to run once:
  ab.begin();
  ab.clear();
  ab.setFrameRate(60);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Pause Renderer Between Frames
  if (!ab.nextFrame()) return;
  
  ab.clear();
  while(!start)
  {
    start =titleScreen();
/*    if (!start)
    {
      start = displayHighScores(EE_FILE);
    }*/
  
  }
  // Draw Sprites
  scroll = (scroll+1)%16;
  for (int bgx = 16-scroll; bgx<128; bgx += 16) {
    for (int bgy = 0; bgy < 64; bgy += 16) {
      ab.drawBitmap(bgx,bgy,background, 8, 8, WHITE);
    }
  }
  ab.fillRect(playerx,playery,17,17,BLACK);
  ab.drawBitmap(playerx,playery,player,17,17,WHITE);
  if(proj1_v) ab.drawRect(proj1_x, proj1_y, 5, 2);
  if(proj2_v) ab.drawRect(proj2_x, proj2_y, 5, 2);
  if(proj3_v) ab.drawRect(proj3_x, proj3_y, 5, 2);
  
  // Move Player Sprite
  if (ab.pressed(LEFT_BUTTON)) playerx--;
  if (ab.pressed(RIGHT_BUTTON)) playerx++;
  if (ab.pressed(UP_BUTTON)) playery--;
  if (ab.pressed(DOWN_BUTTON)) playery++;

  if((ab.pressed(A_BUTTON) || ab.pressed(B_BUTTON)) && !firePressed){
    firePressed = 1;
    if(proj_count == 1){
      proj1_v = 2;
      proj1_x = playerx + 8;
      proj1_y = playery + 8;
      proj_count += 1;
    }
    else if(proj_count == 2){
      proj2_v = 2;
      proj2_x = playerx + 8;
      proj2_y = playery + 8;
      proj_count += 1;
    }
    else if(proj_count == 3){
      proj3_v = 2;
      proj3_x = playerx + 8;
      proj3_y = playery + 8;
      proj_count = 1;
    }
  }

  if(proj1_v) proj1_x += proj1_v;
  if(proj2_v) proj2_x += proj2_v;
  if(proj3_v) proj3_x += proj3_v;

  // Collision Detection With Edge of Screen
  if (playerx < 0) playerx=0;
  if (playerx > 111) playerx = 111;
  if (playery < 0) playery = 0;
  if (playery > 47) playery = 47;

  if(proj1_x > 126) proj1_v = 0;
  if(proj2_x > 126) proj2_v = 0;
  if(proj3_x > 126) proj3_v = 0;

  ab.display();

  if(ab.notPressed(A_BUTTON) && ab.notPressed(B_BUTTON)) firePressed = 0;
}
boolean titleScreen()
{
  //Clears the screen
  ab.clear();
  ab.setCursor(16,22);
  ab.setTextSize(2);
  ab.print("GALAGA?");
  ab.setTextSize(1);
  ab.display();
  if (pollFireButton(25))
  {
    return true;
  }

  //Flash "Press FIRE" 5 times
  for(byte i = 0; i < 5; i++)
  {
    //Draws "Press FIRE"
    ab.setCursor(31, 53);
    ab.print("PRESS FIRE!");
    ab.display();

    if (pollFireButton(50))
    {
      return true;
    }

    //Removes "Press FIRE"
    ab.setCursor(31, 53);
    ab.print("           ");
    ab.display();

    if (pollFireButton(25))
    {
      return true;
    }
  }

  return false;
}

boolean pollFireButton(int n)
{
  for(int i = 0; i < n; i++)
  {
    delay(15);
    pad = ab.pressed(A_BUTTON) || ab.pressed(B_BUTTON);
    if(pad == true && oldpad == false)
    {
      oldpad3 = true; //Forces pad loop 3 to run once
      return true;
    }
    oldpad = pad;
  }
  return false;
}
