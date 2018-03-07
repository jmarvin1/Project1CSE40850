#include <Arduboy2.h>
#include <ArduboyTones.h>

Arduboy2 ab;
ArduboyTones sound(ab.audio.enabled);

// background sprite
const unsigned char background[] PROGMEM = {
  0x00, 0x00, 0x6, 0x4, 0x00, 0x00, 0x00, 0x40, 0x60, 0x00, 0x2, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x38, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6, 0x6, 0x00, 0x00, 0x00, 0x00,
};

// player sprite
const unsigned char player [] PROGMEM = {
  0x00, 0x2, 0x26, 0xae, 0xfe, 0xfa, 0xf2, 0x72, 0x52, 0xd0, 0xd0, 0x90, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0xc9, 0xeb, 0xff, 0xbf, 0x9f, 0x9d, 0x94, 0x16, 0x17, 0x13, 0x3, 0x1, 0x1, 0x1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

// enemy sprite
const unsigned char enemy [] PROGMEM = {
  0x00, 0x2, 0x4, 0x88, 0x70, 0x8c, 0x70, 0xf8, 0x88, 0x88, 0x88, 0x00, 0x2, 0x1, 0x00, 0x00, 0x1, 0x00, 0x00, 0x00, 0x00, 0x00,
};

boolean start = false; // boolean to show title screen

int scroll = 0; // background scroll counter
int pad,oldpad,oldpad3; // pollFireButton buffer
int proj_count = 1; // next projectile counter
int enemy_count = 1; // next enemy counter
int enemy_timer = 10; // timer between enemy spawns

// player variables
int playerx = 5;
int playery = 10;
int firePressed = 0;

// projectile 1
int proj1_x = 0;
int proj1_y = 0;
int proj1_v = 0;

// projectile 2
int proj2_x = 0;
int proj2_y = 0;
int proj2_v = 0;

// projectile 3
int proj3_x = 0;
int proj3_y = 0;
int proj3_v = 0;

// enemy 1
int enemy1_x = 200;
int enemy1_y = 200;
int enemy1_v = 0;

// enemy 2
int enemy2_x = 200;
int enemy2_y = 200;
int enemy2_v = 0;

// enemy 3
int enemy3_x = 200;
int enemy3_y = 200;
int enemy3_v = 0;

// enemy 4
int enemy4_x = 200;
int enemy4_y = 200;
int enemy4_v = 0;

// enemy 5
int enemy5_x = 200;
int enemy5_y = 200;
int enemy5_v = 0;

uint16_t b_music[] = {
  NOTE_A5, 200, NOTE_F5, 200, NOTE_A5, 200, NOTE_F5, 200,
  NOTE_D5, 200, NOTE_AS4, 200, NOTE_C5, 200, NOTE_G4, 200,
  NOTE_A5, 200, NOTE_G5, 200, NOTE_A5, 200, NOTE_D5, 200, 
  NOTE_E5, 200, NOTE_G4, 200, NOTE_E4, 200, NOTE_A4, 200,
  NOTE_C5, 200, NOTE_G4, 200, NOTE_E4, 200, NOTE_G4, 200,
  NOTE_G5, 200, NOTE_C5, 200, NOTE_G4, 200, NOTE_C5, 200,
  NOTE_A5, 200, NOTE_F5, 200, NOTE_A5, 200, NOTE_F5, 200,
  NOTE_C5, 200, NOTE_A4, 200, NOTE_F4, 200, NOTE_C5, 200,
  NOTE_A5, 200, NOTE_F5, 200, NOTE_A5, 200, NOTE_F5, 200,
  NOTE_C5, 200, NOTE_A4, 200, NOTE_F4, 200, NOTE_A4, 200,
  NOTE_AS4, 200, NOTE_G4, 200, NOTE_AS4, 200, NOTE_F4, 200,
  NOTE_AS4, 200, NOTE_G4, 200, NOTE_C5, 200, NOTE_A4, 200,
  NOTE_F5, 200, NOTE_E5, 200, NOTE_F5, 200, NOTE_E5, 200,
  NOTE_AS4, 200, NOTE_A4, 200, NOTE_AS4, 200, NOTE_A4, 200,
  NOTE_AS5, 200, NOTE_A5, 200, NOTE_G5, 200, NOTE_AS5, 200,
  NOTE_D6, 200, NOTE_C6, 200, NOTE_AS5, 200, NOTE_A5, 200,
  NOTE_G5, 200, NOTE_AS5, 200, NOTE_F5, 200, NOTE_A5, 200,
  NOTE_G5, 200, NOTE_E5, 200, NOTE_C5, 200, NOTE_G5, 200,
  NOTE_A5, 200, NOTE_F5, 200, NOTE_A5, 200, NOTE_F5, 200,
  NOTE_A5, 200, NOTE_F5, 200, NOTE_A5, 200, NOTE_F5, 200,
  TONES_REPEAT
};

uint16_t g_music[] = {
  NOTE_A4, 100, NOTE_G4, 100, NOTE_A4, 100, NOTE_G4, 100,
  NOTE_B4, 100, NOTE_A4, 100, NOTE_G4, 100, NOTE_FS4, 100,
  NOTE_A4, 100, NOTE_G4, 100, NOTE_A4, 100, NOTE_G4, 100,
  NOTE_B4, 100, NOTE_A4, 100, NOTE_G4, 100, NOTE_FS4, 100,
  NOTE_A4, 100, NOTE_G4, 100, NOTE_A4, 100, NOTE_G4, 100,
  NOTE_B4, 100, NOTE_A4, 100, NOTE_G4, 100, NOTE_FS4, 100,
  NOTE_A4, 100, NOTE_G4, 100, NOTE_A4, 100, NOTE_G4, 100,
  NOTE_B4, 100, NOTE_A4, 100, NOTE_G4, 100, NOTE_FS4, 100,
  NOTE_D4, 100, NOTE_G4, 100, NOTE_A4, 100, NOTE_G4, 100,
  NOTE_B4, 100, NOTE_A4, 100, NOTE_G4, 100, NOTE_FS4, 100,
  NOTE_A4, 100, NOTE_G4, 100, NOTE_A4, 100, NOTE_G4, 100,
  NOTE_B4, 100, NOTE_A4, 100, NOTE_G4, 100, NOTE_FS4, 100,
  NOTE_E4, 100, NOTE_G4, 100, NOTE_A4, 100, NOTE_G4, 100,
  NOTE_B4, 100, NOTE_A4, 100, NOTE_G4, 100, NOTE_FS4, 100,
  NOTE_A4, 100, NOTE_G4, 100, NOTE_A4, 100, NOTE_G4, 100,
  NOTE_B4, 100, NOTE_A4, 100, NOTE_G4, 100, NOTE_FS4, 100,
  NOTE_A4, 100, NOTE_G4, 100, NOTE_A4, 100, NOTE_G4, 100,
  NOTE_B4, 100, NOTE_A4, 100, NOTE_G4, 100, NOTE_FS4, 100,
  NOTE_A4, 100, NOTE_G4, 100, NOTE_A4, 100, NOTE_G4, 100,
  NOTE_B4, 100, NOTE_A4, 100, NOTE_G4, 100, NOTE_FS4, 100,
  NOTE_D5, 100, NOTE_G4, 100, NOTE_A4, 100, NOTE_G4, 100,
  NOTE_B4, 100, NOTE_A4, 100, NOTE_G4, 100, NOTE_FS4, 100,
  NOTE_E5, 100, NOTE_G4, 100, NOTE_FS5, 100, NOTE_G4, 100,
  NOTE_B5, 100, NOTE_A4, 100, NOTE_FS5, 100, NOTE_FS4, 100,
  NOTE_CS5, 100, NOTE_G4, 100, NOTE_A4, 100, NOTE_G4, 100,
  NOTE_B4, 100, NOTE_A4, 100, NOTE_G4, 100, NOTE_FS4, 100,
  NOTE_D5, 100, NOTE_G4, 100, NOTE_E5, 100, NOTE_G4, 100,
  NOTE_D4, 100, NOTE_A4, 100, NOTE_CS5, 100, NOTE_FS4, 100,
  NOTE_D5, 100, NOTE_G4, 100, NOTE_E5, 100, NOTE_G4, 100,
  NOTE_FS5, 100, NOTE_A4, 100, NOTE_G5, 100, NOTE_FS4, 100,
  NOTE_A5, 100, NOTE_G4, 100, NOTE_G5, 100, NOTE_G4, 100,
  NOTE_FS5, 100, NOTE_A4, 100, NOTE_E5, 100, NOTE_FS4, 100,
  NOTE_A4, 100, NOTE_G4, 100, NOTE_A4, 100, NOTE_G4, 100,
  NOTE_B4, 100, NOTE_A4, 100, NOTE_G4, 100, NOTE_FS4, 100,
  NOTE_A4, 100, NOTE_G4, 100, NOTE_A4, 100, NOTE_G4, 100,
  NOTE_B4, 100, NOTE_A4, 100, NOTE_G4, 100, NOTE_FS4, 100,
  TONES_REPEAT
};

void setup() {
  // put your setup code here, to run once:
  ab.begin();
  ab.clear();
  ab.setFrameRate(60);
}

void loop() {
  // put your main code here, to run repeatedly:

  ab.audio.on();
  
  // Pause Renderer Between Frames
  if (!ab.nextFrame()) return;
  
  ab.clear();

  // Load Start Screen and Wait for Keypress
  while(!start)
  {
    // Title Screen Music
    if(!sound.playing()) sound.tonesInRAM(b_music);
    start = titleScreen();
/*    if (!start)
    {
      start = displayHighScores(EE_FILE);
    }*/
  
  }
  
  sound.volumeMode(VOLUME_ALWAYS_NORMAL);
  // Play Game Music
  if(!sound.playing()) sound.tonesInRAM(g_music);
  
  // Scroll Background
  scroll = (scroll+1)%16;

/* ========== Draw Sprites ========== */

  // Draw Background Tiles
  for (int bgx = 16-scroll; bgx<128; bgx += 16) {
    for (int bgy = 0; bgy < 64; bgy += 16) {
      ab.drawBitmap(bgx,bgy,background, 8, 8, WHITE);
    }
  }

  // Draw Player
  ab.fillRect(playerx,playery,17,17,BLACK);
  ab.drawBitmap(playerx,playery,player,17,17,WHITE);
  
  // Draw Projectiles
  if(proj1_v) ab.drawRect(proj1_x, proj1_y, 5, 2);
  if(proj2_v) ab.drawRect(proj2_x, proj2_y, 5, 2);
  if(proj3_v) ab.drawRect(proj3_x, proj3_y, 5, 2);

  // Draw Enemies
  if (enemy1_v) {
    ab.fillRect(enemy1_x, enemy1_y, 11, 11, BLACK);
    ab.drawBitmap(enemy1_x, enemy1_y, enemy, 11, 11, WHITE);
  }
  if (enemy2_v) {
    ab.fillRect(enemy2_x, enemy2_y, 11, 11, BLACK);
    ab.drawBitmap(enemy2_x, enemy2_y, enemy, 11, 11, WHITE);
  }
  if (enemy3_v) {
    ab.fillRect(enemy3_x, enemy3_y, 11, 11, BLACK);
    ab.drawBitmap(enemy3_x, enemy3_y, enemy, 11, 11, WHITE);
  }
  if (enemy4_v) {
    ab.fillRect(enemy4_x, enemy4_y, 11, 11, BLACK);
    ab.drawBitmap(enemy4_x, enemy4_y, enemy, 11, 11, WHITE);
  }
  if (enemy5_v) {
    ab.fillRect(enemy5_x, enemy5_y, 11, 11, BLACK);
    ab.drawBitmap(enemy5_x, enemy5_y, enemy, 11, 11, WHITE);
  }

  /* ========== Player Inputs ========== */
  
  // Move Player Sprite
  if (ab.pressed(LEFT_BUTTON)) playerx--;
  if (ab.pressed(RIGHT_BUTTON)) playerx++;
  if (ab.pressed(UP_BUTTON)) playery--;
  if (ab.pressed(DOWN_BUTTON)) playery++;

  // Fire Projectiles
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

/* ========== Move Other Sprites ========== */

  // Move Projectiles
  proj1_x += proj1_v;
  proj2_x += proj2_v;
  proj3_x += proj3_v;

  // Render New Enemies
  enemy_timer+= 1; // Increment Frame Counter Between Enemy Spawns
  if (enemy_timer == 30) {
    enemy_timer = 0;
    if (enemy_count == 1) {
      enemy_count += 1;
      enemy1_v = 1;
      enemy1_y = random(1,53);
      enemy1_x = 120;
    }
    else if (enemy_count == 2) {
      enemy_count += 1;
      enemy2_v = 1;
      enemy2_y = random(1,53);
      enemy2_x = 120;
    }
    else if (enemy_count == 3) {
      enemy_count += 1;
      enemy3_v = 1;
      enemy3_y = random(1,53);
      enemy3_x = 120;
    }
    else if (enemy_count == 4) {
      enemy_count += 1;
      enemy4_v = 1;
      enemy4_y = random(1,53);
      enemy4_x = 120;
    }
    else if (enemy_count == 1) {
      enemy_count += 1;
      enemy1_v = 1;
      enemy1_y = random(1,53);
      enemy1_x = 120;
    }
    else if (enemy_count == 5) {
      enemy_count = 1;
      enemy5_v = 1;
      enemy5_y = random(1,53);
      enemy5_x = 120;
    }
  }

  // Move Enemies
  enemy1_x -= enemy1_v;
  enemy2_x -= enemy2_v;
  enemy3_x -= enemy3_v;
  enemy4_x -= enemy4_v;
  enemy5_x -= enemy5_v;

/* ========== Collision Detection ========== */

  // Collision Detection With Edge of Screen
  if (playerx < 0) playerx=0;
  if (playerx > 111) playerx = 111;
  if (playery < 0) playery = 0;
  if (playery > 47) playery = 47;

  // Projectile Collision With Right Edge Screen
  if(proj1_x > 126) proj1_v = 0;
  if(proj2_x > 126) proj2_v = 0;
  if(proj3_x > 126) proj3_v = 0;

  // Enemy Collision With Left Edge of Screen
  if (enemy1_x < -10) {
    enemy1_x = 200;
    enemy1_y = 200;
    enemy1_v = 0; 
  }
  if (enemy2_x < -10) {
    enemy2_x = 200;
    enemy2_y = 200;
    enemy2_v = 0; 
  }
  if (enemy3_x < -10) {
    enemy3_x = 200;
    enemy3_y = 200;
    enemy3_v = 0; 
  }
  if (enemy4_x < -10) {
    enemy4_x = 200;
    enemy4_y = 200;
    enemy4_v = 0; 
  }
  if (enemy5_x < -10) {
    enemy5_x = 200;
    enemy5_y = 200;
    enemy5_v = 0; 
  }

  //player collisions with enemy
  if(enemy1_x < playerx + 17 && playerx < enemy1_x + 10)
  {
    if(enemy1_y < playery + 17 && playery < enemy1_y + 10)
    {
      //he ded  
    }
  }
  if(enemy2_x < playerx + 17 && playerx < enemy2_x + 10)
  {
    if(enemy2_y < playery + 17 && playery < enemy2_y + 10)
    {
      //he ded  
    }
  }
  if(enemy3_x < playerx + 17 && playerx < enemy3_x + 10)
  {
    if(enemy3_y < playery + 17 && playery < enemy3_y + 10)
    {
      //he ded  
    }
  }
  if(enemy4_x < playerx + 17 && playerx < enemy4_x + 10)
  {
    if(enemy4_y < playery + 17 && playery < enemy4_y + 10)
    {
      //he ded  
    }
  }
  if(enemy5_x < playerx + 17 && playerx < enemy5_x + 10)
  {
    if(enemy5_y < playery + 17 && playery < enemy5_y + 10)
    {
      //he ded  
    }
  }
  
/*-----------Projectile with enemy detection---------------*/
  if(enemy5_x < proj1_x + 5 && proj1_x < enemy5_x + 10)
  {
    if(enemy5_y < proj1_y + 2 && proj1_y < enemy5_y + 10)
    {
      //he ded  
    }
  }
 if(enemy4_x < proj1_x + 5 && proj1_x < enemy4_x + 10)
  {
    if(enemy4_y < proj1_y + 2 && proj1_y < enemy4_y + 10)
    {
      //he ded  
    }
  }
 if(enemy3_x < proj1_x + 5 && proj1_x < enemy3_x + 10)
  {
    if(enemy3_y < proj1_y + 2 && proj1_y < enemy3_y + 10)
    {
      //he ded  
    }
  }
 if(enemy2_x < proj1_x + 5 && proj1_x < enemy2_x + 10)
  {
    if(enemy2_y < proj1_y + 2 && proj1_y < enemy2_y + 10)
    {
      //he ded  
    }
  }
 if(enemy1_x < proj1_x + 5 && proj1_x < enemy1_x + 10)
  {
    if(enemy1_y < proj1_y + 2 && proj1_y < enemy1_y + 10)
    {
      //he ded  
    }
  }
 if(enemy5_x < proj2_x + 5 && proj2_x < enemy5_x + 10)
  {
    if(enemy5_y < proj2_y + 2 && proj2_y < enemy5_y + 10)
    {
      //he ded  
    }
  }
 if(enemy4_x < proj2_x + 5 && proj2_x < enemy4_x + 10)
  {
    if(enemy4_y < proj2_y + 2 && proj2_y < enemy4_y + 10)
    {
      //he ded  
    }
  }
 if(enemy3_x < proj2_x + 5 && proj2_x < enemy3_x + 10)
  {
    if(enemy3_y < proj2_y + 2 && proj2_y < enemy3_y + 10)
    {
      //he ded  
    }
  }
 if(enemy2_x < proj2_x + 5 && proj2_x < enemy2_x + 10)
  {
    if(enemy2_y < proj2_y + 2 && proj2_y < enemy2_y + 10)
    {
      //he ded  
    }
  }
 if(enemy1_x < proj2_x + 5 && proj2_x < enemy1_x + 10)
  {
    if(enemy1_y < proj2_y + 2 && proj2_y < enemy1_y + 10)
    {
      //he ded  
    }
  }
 if(enemy1_x < proj3_x + 5 && proj3_x < enemy1_x + 10)
  {
    if(enemy1_y < proj3_y + 2 && proj3_y < enemy1_y + 10)
    {
      //he ded  
    }
  }
 if(enemy2_x < proj3_x + 5 && proj3_x < enemy2_x + 10)
  {
    if(enemy2_y < proj3_y + 2 && proj3_y < enemy2_y + 10)
    {
      //he ded  
    }
  }
 if(enemy3_x < proj3_x + 5 && proj3_x < enemy3_x + 10)
  {
    if(enemy3_y < proj3_y + 2 && proj3_y < enemy3_y + 10)
    {
      //he ded  
    }
  }
 if(enemy4_x < proj3_x + 5 && proj3_x < enemy4_x + 10)
  {
    if(enemy4_y < proj3_y + 2 && proj3_y < enemy4_y + 10)
    {
      //he ded  
    }
  }
 if(enemy5_x < proj3_x + 5 && proj3_x < enemy5_x + 10)
  {
    if(enemy5_y < proj3_y + 2 && proj3_y < enemy5_y + 10)
    {
      //he ded  
    }
  }















  ab.display();

  // Clear Fire Button Buffer
  if(ab.notPressed(A_BUTTON) && ab.notPressed(B_BUTTON)) firePressed = 0;
}

boolean titleScreen()
{
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

  // Flash "Press FIRE" 5 times
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
      sound.noTone();
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
