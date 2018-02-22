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
  
  // Move Player Sprite
  if (ab.pressed(LEFT_BUTTON)) playerx--;
  if (ab.pressed(RIGHT_BUTTON)) playerx++;
  if (ab.pressed(UP_BUTTON)) playery--;
  if (ab.pressed(DOWN_BUTTON)) playery++;

  // Collision Detection With Edge of Screen
  if (playerx < 0) playerx=0;
  if (playerx > 111) playerx = 111;
  if (playery < 0) playery = 0;
  if (playery > 47) playery = 47;

  ab.display();
}
boolean titleScreen()
{
  //Clears the screen
  ab.clear();
  ab.setCursor(16,22);
  ab.setTextSize(2);
  ab.print("Galaga but not really");
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
