//
//  main.c
//  PixelMan02
//
//  Created by Julie Glasdam on 30/06/2017.
//  Copyright © 2017 Julie Glasdam. All rights reserved.
//


#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "main.h"
#include "status.h"
#define GRAVITY 0.60f


// Turn of music for testing. 0 = music, 1 = music disabled
int mute = 0;
SDL_Color white = {255, 255, 255, 0};
SDL_Color black = {0, 0, 0, 0};

void defineObjects(GameState *game){
    game->flags.x = 10000;
    game->flags.y = 450;
    game->flags.w = 120;
    game->flags.h = 160;
    
    game->heart.x = 20;
    game->heart.y = 16;
    game->heart.w = 121;
    game->heart.h = 40;
    game->heart.animFrame = 5;
    
    game->coin.x = 175;
    game->coin.y = 23;
    game->coin.w = 30;
    game->coin.h = 30;
    
    game->play.x = 405;
    game->play.y = 300;
    game->play.w = 124;
    game->play.h = 130;
    
    game->credits.x = 405;
    game->credits.y = 300;
    game->credits.w = 124;
    game->credits.h = 130;
    
    game->exit.x = 405;
    game->exit.y = 300;
    game->exit.w = 124;
    game->exit.h = 130;
    
    game->yes.x = 370;
    game->yes.y = 400;
    game->yes.w = 226;
    game->yes.h = 62;
    
    game->no.x = 370;
    game->no.y = 400;
    game->no.w = 226;
    game->no.h = 62;
    
    game->man.w = 40;
    game->man.h = 50;
    
    game->statue.x = 6150;
    game->statue.y = 100;
    game->statue.w = 181;
    game->statue.h = 454;
    
    for (int i = 0; i < NUM_TILEPATTERN; i++) {
        game->tilepattern[i].x = i*1700;
        game->tilepattern[i].y = 0;
        game->tilepattern[i].w = 1700;
        game->tilepattern[i].h = 680;
    }
    
    for (int i = 0; i < NUM_PICKUPHEARTS01Lvl; i++) {
        game->pickupheartLvl01[i].w = 40; game->pickupheartLvl01[i].h = 40;
    }
    game->pickupheartLvl01[0].x = 3500; game->pickupheartLvl01[0].y = 470;
    game->pickupheartLvl01[1].x = 6460; game->pickupheartLvl01[1].y = 210;
    game->pickupheartLvl01[2].x = 8610; game->pickupheartLvl01[2].y = 360;
    
    for (int i = 0; i < NUM_PICKUPHEARTS02Lvl; i++) {
        game->pickupheartLvl02[i].w = 40; game->pickupheartLvl02[i].h = 40;
    }
    game->pickupheartLvl02[0].x = 2035; game->pickupheartLvl02[0].y = 200;
    game->pickupheartLvl02[1].x = 6960; game->pickupheartLvl02[1].y = 360;
    game->pickupheartLvl02[2].x = 8200; game->pickupheartLvl02[2].y = 410;
    
    for (int i = 0; i < NUM_PICKUPHEARTS03Lvl; i++) {
        game->pickupheartLvl03[i].w = 40; game->pickupheartLvl03[i].h = 40;
    }
    game->pickupheartLvl03[0].x = 2227; game->pickupheartLvl03[0].y = 360;
    game->pickupheartLvl03[1].x = 6836; game->pickupheartLvl03[1].y = 560;
    game->pickupheartLvl03[2].x = 8317; game->pickupheartLvl03[2].y = 360;
    
    for (int i = 0; i < NUM_PICKUPHEARTS04Lvl; i++) {
        game->pickupheartLvl04[i].w = 40; game->pickupheartLvl04[i].h = 40;
    }
    game->pickupheartLvl04[0].x = 3425; game->pickupheartLvl04[0].y = 130;
    game->pickupheartLvl04[1].x = 5986; game->pickupheartLvl04[1].y = 310;
    game->pickupheartLvl04[2].x = 8307; game->pickupheartLvl04[2].y = 510;
    
    // Clouds back - Level 04
    for (int i = 0; i < NUM_CLOUDSBACK; i++) {
        game->cloudsBack[i].w = 940; game->cloudsBack[i].h = 680; game->cloudsBack[i].x = 680*i; game->cloudsBack[i].y = 0;
    }
    
    // Clouds front - Level 04
    for (int i = 0; i < NUM_CLOUDSFRONT; i++) {
        game->cloudsFront[i].w = 940; game->cloudsFront[i].h = 680; game->cloudsFront[i].x = 680*i; game->cloudsFront[i].y = 150;
    }
    
    // Torches
    for (int i = 0; i < NUM_TORCH; i++) {
        game->torches[i].w = 90; game->torches[i].h = 96; game->torches[i].x = i*600; game->torches[i].y = 150; game->torches[i].animFrame = 0;
    }
    
    /// Enemies
    // Level 01
    for(int i = 0; i < NUM_ENEMIES01Lvl; i++){
        game->enemiesLvl01[i].w = 40; game->enemiesLvl01[i].h = 50; game->enemiesLvl01[i].animFrame = 0; game->enemiesLvl01[i].dx = 0;
    }
    game->enemiesLvl01[0].x = 610; game->enemiesLvl01[0].y = 250; game->enemiesLvl01[0].startPos = 610; game->enemiesLvl01[0].endPos = 100+(int)game->enemiesLvl01[0].x;
    game->enemiesLvl01[1].x = 1140; game->enemiesLvl01[1].y = 150; game->enemiesLvl01[1].startPos = 1140; game->enemiesLvl01[1].endPos = 140+(int)game->enemiesLvl01[1].x;
    game->enemiesLvl01[2].x = 1400; game->enemiesLvl01[2].y = 550; game->enemiesLvl01[2].startPos = 1400; game->enemiesLvl01[2].endPos = 100+(int)game->enemiesLvl01[2].x;
    game->enemiesLvl01[3].x = 1200; game->enemiesLvl01[3].y = 550; game->enemiesLvl01[3].startPos = 1200; game->enemiesLvl01[3].endPos = 130+(int)game->enemiesLvl01[3].x;
    game->enemiesLvl01[4].x = 2020; game->enemiesLvl01[4].y = 250; game->enemiesLvl01[4].startPos = 2020; game->enemiesLvl01[4].endPos = 170+(int)game->enemiesLvl01[4].x;
    game->enemiesLvl01[5].x = 2530; game->enemiesLvl01[5].y = 550; game->enemiesLvl01[5].startPos = 2530; game->enemiesLvl01[5].endPos = 500+(int)game->enemiesLvl01[5].x;
    game->enemiesLvl01[6].x = 3510; game->enemiesLvl01[6].y = 350; game->enemiesLvl01[6].startPos = 3510; game->enemiesLvl01[6].endPos = 100+(int)game->enemiesLvl01[6].x;
    game->enemiesLvl01[7].x = 4430; game->enemiesLvl01[7].y = 200; game->enemiesLvl01[7].startPos = 4430; game->enemiesLvl01[7].endPos = 170+(int)game->enemiesLvl01[7].x;
    game->enemiesLvl01[8].x = 4730; game->enemiesLvl01[8].y = 550; game->enemiesLvl01[8].startPos = 4730; game->enemiesLvl01[8].endPos = 410+(int)game->enemiesLvl01[8].x;
    game->enemiesLvl01[9].x = 5120; game->enemiesLvl01[9].y = 350; game->enemiesLvl01[9].startPos = 5120; game->enemiesLvl01[9].endPos = 170+(int)game->enemiesLvl01[9].x;
    game->enemiesLvl01[10].x = 7100; game->enemiesLvl01[10].y = 550; game->enemiesLvl01[10].startPos = 7100; game->enemiesLvl01[10].endPos = 810+(int)game->enemiesLvl01[10].x;
    game->enemiesLvl01[11].x = 8310; game->enemiesLvl01[11].y = 350; game->enemiesLvl01[11].startPos = 8310; game->enemiesLvl01[11].endPos = 140+(int)game->enemiesLvl01[11].x;
    game->enemiesLvl01[12].x = 8930; game->enemiesLvl01[12].y = 200; game->enemiesLvl01[12].startPos = 8930; game->enemiesLvl01[12].endPos = 100+(int)game->enemiesLvl01[12].x;
    game->enemiesLvl01[13].x = 9300; game->enemiesLvl01[13].y = 250; game->enemiesLvl01[13].startPos = 9300; game->enemiesLvl01[13].endPos = 170+(int)game->enemiesLvl01[13].x;
    game->enemiesLvl01[14].x = 9640; game->enemiesLvl01[14].y = 550; game->enemiesLvl01[14].startPos = 9640; game->enemiesLvl01[14].endPos = 140+(int)game->enemiesLvl01[14].x;
    game->enemiesLvl01[15].x = 1640; game->enemiesLvl01[15].y = 550; game->enemiesLvl01[15].startPos = 1640; game->enemiesLvl01[15].endPos = 140+(int)game->enemiesLvl01[15].x;
    
    
    // Enemies level 02
    for(int i = 0; i < NUM_ENEMIES02Lvl; i++) {
        game->enemiesLvl02[i].w = 40; game->enemiesLvl02[i].h = 50; game->enemiesLvl02[i].animFrame = 0; game->enemiesLvl02[i].dx = 0;
    }
    game->enemiesLvl02[0].x = 510; game->enemiesLvl02[0].y = 300; game->enemiesLvl02[0].startPos = 510; game->enemiesLvl02[0].endPos = 200+(int)game->enemiesLvl02[0].x;
    game->enemiesLvl02[1].x = 1130; game->enemiesLvl02[1].y = 190; game->enemiesLvl02[1].startPos = 1130; game->enemiesLvl02[1].endPos = 170+(int)game->enemiesLvl02[1].x;
    game->enemiesLvl02[2].x = 1430; game->enemiesLvl02[2].y = 550; game->enemiesLvl02[2].startPos = 1430; game->enemiesLvl02[2].endPos = 150+(int)game->enemiesLvl02[2].x;
    game->enemiesLvl02[3].x = 2510; game->enemiesLvl02[3].y = 230; game->enemiesLvl02[3].startPos = 2510; game->enemiesLvl02[3].endPos = 170+(int)game->enemiesLvl02[3].x;
    game->enemiesLvl02[4].x = 3220; game->enemiesLvl02[4].y = 400; game->enemiesLvl02[4].startPos = 3220; game->enemiesLvl02[4].endPos = 200+(int)game->enemiesLvl02[4].x;
    game->enemiesLvl02[5].x = 4200; game->enemiesLvl02[5].y = 350; game->enemiesLvl02[5].startPos = 4200; game->enemiesLvl02[5].endPos = 120+(int)game->enemiesLvl02[5].x;
    game->enemiesLvl02[6].x = 4570; game->enemiesLvl02[6].y = 550; game->enemiesLvl02[6].startPos = 4570; game->enemiesLvl02[6].endPos = 140+(int)game->enemiesLvl02[6].x;
    game->enemiesLvl02[7].x = 6010; game->enemiesLvl02[7].y = 150; game->enemiesLvl02[7].startPos = 6010; game->enemiesLvl02[7].endPos = 400+(int)game->enemiesLvl02[7].x;
    game->enemiesLvl02[8].x = 6340; game->enemiesLvl02[8].y = 150; game->enemiesLvl02[8].startPos = 6340; game->enemiesLvl02[8].endPos = 200+(int)game->enemiesLvl02[8].x;
    game->enemiesLvl02[9].x = 7070; game->enemiesLvl02[9].y = 550; game->enemiesLvl02[9].startPos = 7070; game->enemiesLvl02[9].endPos = 170+(int)game->enemiesLvl02[9].x;
    game->enemiesLvl02[10].x = 9260; game->enemiesLvl02[10].y = 550; game->enemiesLvl02[10].startPos = 9260; game->enemiesLvl02[10].endPos = 180+(int)game->enemiesLvl02[10].x;
    
    
    // Enemies level 03
    for(int i = 0; i < NUM_ENEMIES03Lvl; i++) {
        game->enemiesLvl03[i].w = 40; game->enemiesLvl03[i].h = 50; game->enemiesLvl03[i].animFrame = 0; game->enemiesLvl03[i].dx = 0;
    }
    game->enemiesLvl03[0].x = 610; game->enemiesLvl03[0].y = 400; game->enemiesLvl03[0].startPos = 610; game->enemiesLvl03[0].endPos = 180+(int)game->enemiesLvl03[0].x;
    game->enemiesLvl03[1].x = 1660; game->enemiesLvl03[1].y = 170; game->enemiesLvl03[1].startPos = 1660; game->enemiesLvl03[1].endPos = 190+(int)game->enemiesLvl03[1].x;
    game->enemiesLvl03[2].x = 3410; game->enemiesLvl03[2].y = 250; game->enemiesLvl03[2].startPos = 3410; game->enemiesLvl03[2].endPos = 120+(int)game->enemiesLvl03[2].x;
    game->enemiesLvl03[3].x = 4020; game->enemiesLvl03[3].y = 400; game->enemiesLvl03[3].startPos = 4020; game->enemiesLvl03[3].endPos = 170+(int)game->enemiesLvl03[3].x;
    game->enemiesLvl03[4].x = 5010; game->enemiesLvl03[4].y = 350; game->enemiesLvl03[4].startPos = 5010; game->enemiesLvl03[4].endPos = 180+(int)game->enemiesLvl03[4].x;
    game->enemiesLvl03[5].x = 6110; game->enemiesLvl03[5].y = 250; game->enemiesLvl03[5].startPos = 6110; game->enemiesLvl03[5].endPos = 160+(int)game->enemiesLvl03[5].x;
    game->enemiesLvl03[6].x = 7310; game->enemiesLvl03[6].y = 400; game->enemiesLvl03[6].startPos = 7310; game->enemiesLvl03[6].endPos = 150+(int)game->enemiesLvl03[6].x;
    game->enemiesLvl03[7].x = 8410; game->enemiesLvl03[7].y = 290; game->enemiesLvl03[7].startPos = 8410; game->enemiesLvl03[7].endPos = 170+(int)game->enemiesLvl03[7].x;
    game->enemiesLvl03[8].x = 9420; game->enemiesLvl03[8].y = 350; game->enemiesLvl03[8].startPos = 9420; game->enemiesLvl03[8].endPos = 180+(int)game->enemiesLvl03[8].x;
    
    game->enemiesLvl03[9].x = 900; game->enemiesLvl03[9].y = 550; game->enemiesLvl03[9].startPos = 900; game->enemiesLvl03[9].endPos = 250+(int)game->enemiesLvl03[9].x;
    game->enemiesLvl03[10].x = 2000; game->enemiesLvl03[10].y = 550; game->enemiesLvl03[10].startPos = 2000; game->enemiesLvl03[10].endPos = 200+(int)game->enemiesLvl03[10].x;
    game->enemiesLvl03[11].x = 2100; game->enemiesLvl03[11].y = 550; game->enemiesLvl03[11].startPos = 2100; game->enemiesLvl03[11].endPos = 250+(int)game->enemiesLvl03[11].x;
    game->enemiesLvl03[12].x = 2150; game->enemiesLvl03[12].y = 550; game->enemiesLvl03[12].startPos = 2150; game->enemiesLvl03[12].endPos = 350+(int)game->enemiesLvl03[12].x;
    game->enemiesLvl03[13].x = 3200; game->enemiesLvl03[13].y = 550; game->enemiesLvl03[13].startPos = 3200; game->enemiesLvl03[13].endPos = 200+(int)game->enemiesLvl03[13].x;
    game->enemiesLvl03[14].x = 3300; game->enemiesLvl03[14].y = 550; game->enemiesLvl03[14].startPos = 3300; game->enemiesLvl03[14].endPos = 260+(int)game->enemiesLvl03[14].x;
    game->enemiesLvl03[15].x = 4000; game->enemiesLvl03[15].y = 550; game->enemiesLvl03[15].startPos = 4000; game->enemiesLvl03[15].endPos = 320+(int)game->enemiesLvl03[15].x;
    game->enemiesLvl03[16].x = 4200; game->enemiesLvl03[16].y = 550; game->enemiesLvl03[16].startPos = 4200; game->enemiesLvl03[16].endPos = 250+(int)game->enemiesLvl03[16].x;
    game->enemiesLvl03[17].x = 6600; game->enemiesLvl03[17].y = 550; game->enemiesLvl03[17].startPos = 6600; game->enemiesLvl03[17].endPos = 280+(int)game->enemiesLvl03[17].x;
    game->enemiesLvl03[18].x = 7000; game->enemiesLvl03[18].y = 550; game->enemiesLvl03[18].startPos = 7000; game->enemiesLvl03[18].endPos = 310+(int)game->enemiesLvl03[18].x;
    game->enemiesLvl03[19].x = 8700; game->enemiesLvl03[19].y = 550; game->enemiesLvl03[19].startPos = 8700; game->enemiesLvl03[19].endPos = 260+(int)game->enemiesLvl03[19].x;
    game->enemiesLvl03[20].x = 8900; game->enemiesLvl03[20].y = 550; game->enemiesLvl03[20].startPos = 8900; game->enemiesLvl03[20].endPos = 300+(int)game->enemiesLvl03[20].x;
    
    
    
    // Enemies level 04
    for(int i = 0; i < NUM_ENEMIES04Lvl; i++) {
        game->enemiesLvl04[i].w = 40; game->enemiesLvl04[i].h = 50; game->enemiesLvl04[i].animFrame = 0; game->enemiesLvl04[i].dx = 0;
    }
    game->enemiesLvl04[0].x = 410; game->enemiesLvl04[0].y = 300; game->enemiesLvl04[0].startPos = 410; game->enemiesLvl04[0].endPos = 150+(int)game->enemiesLvl04[0].x;
    game->enemiesLvl04[1].x = 1110; game->enemiesLvl04[1].y = 150; game->enemiesLvl04[1].startPos = 1110; game->enemiesLvl04[1].endPos = 200+(int)game->enemiesLvl04[1].x;
    game->enemiesLvl04[2].x = 2120; game->enemiesLvl04[2].y = 270; game->enemiesLvl04[2].startPos = 2120; game->enemiesLvl04[2].endPos = 170+(int)game->enemiesLvl04[2].x;
    game->enemiesLvl04[3].x = 2510; game->enemiesLvl04[3].y = 200; game->enemiesLvl04[3].startPos = 2510; game->enemiesLvl04[3].endPos = 150+(int)game->enemiesLvl04[3].x;
    game->enemiesLvl04[4].x = 4310; game->enemiesLvl04[4].y = 350; game->enemiesLvl04[4].startPos = 4310; game->enemiesLvl04[4].endPos = 200+(int)game->enemiesLvl04[4].x;
    game->enemiesLvl04[5].x = 5410; game->enemiesLvl04[5].y = 330; game->enemiesLvl04[5].startPos = 5410; game->enemiesLvl04[5].endPos = 210+(int)game->enemiesLvl04[5].x;
    game->enemiesLvl04[6].x = 6410; game->enemiesLvl04[6].y = 400; game->enemiesLvl04[6].startPos = 6410; game->enemiesLvl04[6].endPos = 200+(int)game->enemiesLvl04[6].x;
    game->enemiesLvl04[7].x = 7310; game->enemiesLvl04[7].y = 300; game->enemiesLvl04[7].startPos = 7310; game->enemiesLvl04[7].endPos = 160+(int)game->enemiesLvl04[7].x;
    game->enemiesLvl04[8].x = 5870; game->enemiesLvl04[8].y = 500; game->enemiesLvl04[8].startPos = 5870; game->enemiesLvl04[8].endPos = 300+(int)game->enemiesLvl04[8].x;
    game->enemiesLvl04[9].x = 6000; game->enemiesLvl04[9].y = 500; game->enemiesLvl04[9].startPos = 6000; game->enemiesLvl04[9].endPos = 160+(int)game->enemiesLvl04[9].x;
    game->enemiesLvl04[10].x = 6300; game->enemiesLvl04[10].y = 500; game->enemiesLvl04[10].startPos = 6300; game->enemiesLvl04[10].endPos = 260+(int)game->enemiesLvl04[10].x;
    game->enemiesLvl04[11].x = 6100; game->enemiesLvl04[11].y = 500; game->enemiesLvl04[11].startPos = 6100; game->enemiesLvl04[11].endPos = 100+(int)game->enemiesLvl04[11].x;
    game->enemiesLvl04[12].x = 7760; game->enemiesLvl04[12].y = 250; game->enemiesLvl04[12].startPos = 7760; game->enemiesLvl04[12].endPos = 120+(int)game->enemiesLvl04[12].x;
    game->enemiesLvl04[13].x = 8755; game->enemiesLvl04[13].y = 500; game->enemiesLvl04[13].startPos = 8755; game->enemiesLvl04[13].endPos = 150+(int)game->enemiesLvl04[13].x;
    
    /// Ledges
    // Level 01
    for(int i = 0; i < NUM_LEDGE01Lvl; i++) {
        game->ledges[i].w = 300; game->ledges[i].h = 120;
    }
    // In the water
    game->ledges[0].x = 100; game->ledges[0].y = 630;
    game->ledges[1].x = 250; game->ledges[1].y = 660; game->ledges[1].w = 200; game->ledges[1].h = 100;
    game->ledges[2].x = 7000; game->ledges[2].y = 640;
    game->ledges[3].x = 8000; game->ledges[3].y = 630; game->ledges[3].w = 100; game->ledges[3].h = 120;
    game->ledges[4].x = 8100; game->ledges[4].y = 620;
    game->ledges[5].x = 13000; game->ledges[5].y = 650;
    game->ledges[6].x = 14500; game->ledges[6].y = 620;
    
    // In the air
    game->ledges[7].x = 200; game->ledges[7].y = 450;
    game->ledges[8].x = 450; game->ledges[8].y = 500; game->ledges[8].w = 130; game->ledges[8].h = 90;
    game->ledges[9].x = 600; game->ledges[9].y = 300;
    game->ledges[10].x = 1100; game->ledges[10].y = 200; game->ledges[10].w = 400; game->ledges[10].h = 300;
    game->ledges[11].x = 700; game->ledges[11].y = 400;
    game->ledges[12].x = 400; game->ledges[12].y = 200; game->ledges[12].w = 200; game->ledges[12].h = 80;
    game->ledges[13].x = 950; game->ledges[13].y = 420;
    game->ledges[14].x = 1050; game->ledges[14].y = 300; game->ledges[14].w = 100; game->ledges[14].h = 80;
    game->ledges[15].x = 1600; game->ledges[15].y = 150;
    game->ledges[16].x = 2000; game->ledges[16].y = 300; game->ledges[16].h = 140;
    game->ledges[17].x = 2150; game->ledges[17].y = 400;  game->ledges[17].w = 200; game->ledges[17].h = 80;
    game->ledges[18].x = 2400; game->ledges[18].y = 450;
    game->ledges[19].x = 2350; game->ledges[19].y = 500; game->ledges[19].w = 100; game->ledges[19].h = 80;
    game->ledges[20].x = 2800; game->ledges[20].y = 330;
    game->ledges[21].x = 3000; game->ledges[21].y = 230;
    game->ledges[22].x = 3500; game->ledges[22].y = 400;
    game->ledges[23].x = 3400; game->ledges[23].y = 450;
    game->ledges[24].x = 4000; game->ledges[24].y = 350; game->ledges[24].w = 320;
    game->ledges[25].x = 3850; game->ledges[25].y = 230; game->ledges[25].w = 150; game->ledges[25].h = 80;
    game->ledges[26].x = 3500; game->ledges[26].y = 510; game->ledges[26].w = 130; game->ledges[26].h = 80;
    game->ledges[27].x = 4400; game->ledges[27].y = 250;
    game->ledges[28].x = 4800; game->ledges[28].y = 200;
    game->ledges[29].x = 5100; game->ledges[29].y = 400;
    game->ledges[30].x = 5200; game->ledges[30].y = 480; game->ledges[30].w = 250; game->ledges[30].h = 100;
    game->ledges[31].x = 5800; game->ledges[31].y = 300; game->ledges[31].w = 100; game->ledges[31].h = 100;
    game->ledges[32].x = 5600; game->ledges[32].y = 420; game->ledges[32].w = 100; game->ledges[32].h = 100;
    game->ledges[33].x = 6000; game->ledges[33].y = 200; game->ledges[33].w = 100; game->ledges[33].h = 100;
    game->ledges[34].x = 6150; game->ledges[34].y = 200;
    game->ledges[35].x = 6300; game->ledges[35].y = 250; game->ledges[35].w = 250; game->ledges[35].h = 150;
    game->ledges[36].x = 6800; game->ledges[36].y = 240; game->ledges[36].w = 250; game->ledges[36].h = 250;
    game->ledges[37].x = 7400; game->ledges[37].y = 170;
    game->ledges[38].x = 7200; game->ledges[38].y = 300;
    game->ledges[41].x = 8100; game->ledges[41].y = 500; game->ledges[41].w = 250; game->ledges[41].h = 80;
    game->ledges[39].x = 8300; game->ledges[39].y = 400; game->ledges[39].w = 250;
    game->ledges[40].x = 7800; game->ledges[40].y = 300; game->ledges[40].w = 100; game->ledges[40].h = 100;
    game->ledges[43].x = 8700; game->ledges[43].y = 300;
    game->ledges[42].x = 8900; game->ledges[42].y = 250; game->ledges[42].w = 200; game->ledges[42].h = 200;
    game->ledges[44].x = 9300; game->ledges[44].y = 300;
    game->ledges[45].x = 9500; game->ledges[45].y = 400; game->ledges[45].w = 150; game->ledges[45].h = 80;
    game->ledges[46].x = 9700; game->ledges[46].y = 100; game->ledges[46].w = 100; game->ledges[46].h = 100;
    
    game->ledges[47].x = 8600; game->ledges[47].y = 400; game->ledges[47].w = 100; game->ledges[47].h = 100;
    game->ledges[48].x = 8100; game->ledges[48].y = 230; game->ledges[48].w = 120; game->ledges[48].h = 100;
    game->ledges[49].x = 40; game->ledges[49].y = 100; game->ledges[49].w = 100; game->ledges[49].h = 100;
    game->ledges[50].x = 4500; game->ledges[50].y = 350; game->ledges[50].w = 140; game->ledges[50].h = 100;
    game->ledges[51].x = 8200; game->ledges[51].y = 280; game->ledges[51].w = 100; game->ledges[51].h = 100;
    
    
    // Level 02
    for(int i = 0; i < NUM_LEDGE02Lvl; i++) {
        game->ledgesLvl02[i].w = 258; game->ledgesLvl02[i].h = 137;
    }
    game->ledgesLvl02[17].x = 200; game->ledgesLvl02[17].y = 550;
    game->ledgesLvl02[1].x = 500; game->ledgesLvl02[1].y = 350;
    game->ledgesLvl02[2].x = 650; game->ledgesLvl02[2].y = 450;
    game->ledgesLvl02[3].x = 800; game->ledgesLvl02[3].y = 280;
    game->ledgesLvl02[4].x = 1120; game->ledgesLvl02[4].y = 240;
    game->ledgesLvl02[5].x = 1480; game->ledgesLvl02[5].y = 240;
    game->ledgesLvl02[6].x = 1840; game->ledgesLvl02[6].y = 240;
    game->ledgesLvl02[7].x = 3200; game->ledgesLvl02[7].y = 450;
    game->ledgesLvl02[8].x = 3680; game->ledgesLvl02[8].y = 500;
    game->ledgesLvl02[9].x = 4200; game->ledgesLvl02[9].y = 400;
    game->ledgesLvl02[10].x = 4000; game->ledgesLvl02[10].y = 450;
    game->ledgesLvl02[11].x = 4600; game->ledgesLvl02[11].y = 360;
    game->ledgesLvl02[12].x = 5400; game->ledgesLvl02[12].y = 430;
    game->ledgesLvl02[13].x = 5580; game->ledgesLvl02[13].y = 550;
    game->ledgesLvl02[14].x = 5780; game->ledgesLvl02[14].y = 320;
    game->ledgesLvl02[15].x = 6780; game->ledgesLvl02[15].y = 400;
    game->ledgesLvl02[16].x = 7100; game->ledgesLvl02[16].y = 340;
    game->ledgesLvl02[0].x = 4250; game->ledgesLvl02[0].y = 250;
    game->ledgesLvl02[18].x = 8200; game->ledgesLvl02[18].y = 450;
    game->ledgesLvl02[19].x = 8700; game->ledgesLvl02[19].y = 550;
    game->ledgesLvl02[20].x = 9000; game->ledgesLvl02[20].y = 550;
    game->ledgesLvl02[21].x = 9300; game->ledgesLvl02[21].y = 500;
    
    
    for (int i = 0; i < NUM_GREYPILLARS; i++) {
        game->pillars[i].w = 206; game->pillars[i].h = 340; game->pillars[i].y = 280;
    }
    game->pillars[0].x = 2200;
    game->pillars[1].x = 2500;
    game->pillars[2].x = 2800; game->pillars[2].y = 400;
    game->pillars[3].x = 5000;
    game->pillars[4].x = 7500;
    game->pillars[5].x = 7800;
    
    
    for (int i = 0; i < NUM_HIGHLEDGE; i++) {
        game->highledge[i].w = 740; game->highledge[i].h = 414; game->highledge[i].y = 200;
    }
    game->highledge[0].x = 6000;
    game->highledge[1].x = 3500;
    game->highledge[2].x = 8200; game->highledge[2].y = 300;
    
    
    // Level 03
    for(int i = 0; i < NUM_LEDGE03Lvl; i++) {
        game->ledgesLvl03[i].w = 300; game->ledgesLvl03[i].h = 120;
    }
    game->ledgesLvl03[0].x = 400; game->ledgesLvl03[0].y = 550;
    game->ledgesLvl03[1].x = 600; game->ledgesLvl03[1].y = 450;
    game->ledgesLvl03[2].x = 800; game->ledgesLvl03[2].y = 350;
    game->ledgesLvl03[3].x = 1000; game->ledgesLvl03[3].y = 250;
    game->ledgesLvl03[4].x = 1400; game->ledgesLvl03[4].y = 250;
    game->ledgesLvl03[5].x = 1650; game->ledgesLvl03[5].y = 220;
    game->ledgesLvl03[6].x = 2000; game->ledgesLvl03[6].y = 230;
    game->ledgesLvl03[7].x = 2200; game->ledgesLvl03[7].y = 400;
    game->ledgesLvl03[8].x = 2750; game->ledgesLvl03[8].y = 350;
    game->ledgesLvl03[9].x = 3000; game->ledgesLvl03[9].y = 330;
    game->ledgesLvl03[10].x = 3400; game->ledgesLvl03[10].y = 300;
    game->ledgesLvl03[11].x = 3600; game->ledgesLvl03[11].y = 500;
    game->ledgesLvl03[12].x = 4000; game->ledgesLvl03[12].y = 450;
    game->ledgesLvl03[13].x = 4400; game->ledgesLvl03[13].y = 450;
    game->ledgesLvl03[14].x = 4800; game->ledgesLvl03[14].y = 450;
    game->ledgesLvl03[15].x = 5000; game->ledgesLvl03[15].y = 400;
    game->ledgesLvl03[16].x = 5500; game->ledgesLvl03[16].y = 400;
    game->ledgesLvl03[17].x = 5700; game->ledgesLvl03[17].y = 350;
    game->ledgesLvl03[18].x = 6100; game->ledgesLvl03[18].y = 300;
    game->ledgesLvl03[19].x = 6400; game->ledgesLvl03[19].y = 250;
    game->ledgesLvl03[20].x = 6900; game->ledgesLvl03[20].y = 500;
    game->ledgesLvl03[21].x = 7300; game->ledgesLvl03[21].y = 450;
    game->ledgesLvl03[22].x = 7700; game->ledgesLvl03[22].y = 400;
    game->ledgesLvl03[23].x = 8000; game->ledgesLvl03[23].y = 500;
    game->ledgesLvl03[24].x = 8200; game->ledgesLvl03[24].y = 400;
    game->ledgesLvl03[25].x = 8400; game->ledgesLvl03[25].y = 340;
    game->ledgesLvl03[26].x = 8800; game->ledgesLvl03[26].y = 300;
    game->ledgesLvl03[27].x = 9200; game->ledgesLvl03[27].y = 250;
    game->ledgesLvl03[28].x = 9400; game->ledgesLvl03[28].y = 400;
    
    for (int i = 0; i < NUM_SHADOWPILLAR; i++) {
        game->shadowPillar[i].w = 223; game->shadowPillar[i].h = 600; game->shadowPillar[i].y = 50;
    }
    game->shadowPillar[0].x = 1030;
    game->shadowPillar[1].x = 2117;
    game->shadowPillar[2].x = 3070;
    game->shadowPillar[3].x = 4370;
    game->shadowPillar[4].x = 6650;
    game->shadowPillar[5].x = 8860;
    
    
    // Level 04
    for(int i = 0; i < NUM_LEDGE04Lvl; i++){
        game->ledgesLvl04[i].w = 257; game->ledgesLvl04[i].h = 679;
    }
    game->ledgesLvl04[0].x = 200; game->ledgesLvl04[0].y = 450;
    game->ledgesLvl04[1].x = 400; game->ledgesLvl04[1].y = 350;
    game->ledgesLvl04[2].x = 840; game->ledgesLvl04[2].y = 240;
    game->ledgesLvl04[3].x = 750; game->ledgesLvl04[3].y = 350;
    game->ledgesLvl04[4].x = 1100; game->ledgesLvl04[4].y = 200;
    game->ledgesLvl04[5].x = 1600; game->ledgesLvl04[5].y = 440;
    game->ledgesLvl04[6].x = 1800; game->ledgesLvl04[6].y = 380;
    game->ledgesLvl04[7].x = 2100; game->ledgesLvl04[7].y = 320;
    game->ledgesLvl04[8].x = 2600; game->ledgesLvl04[8].y = 170;
    game->ledgesLvl04[9].x = 2500; game->ledgesLvl04[9].y = 250;
    game->ledgesLvl04[10].x = 2800; game->ledgesLvl04[10].y = 170;
    game->ledgesLvl04[11].x = 3000; game->ledgesLvl04[11].y = 170;
    game->ledgesLvl04[12].x = 3400; game->ledgesLvl04[12].y = 170;
    game->ledgesLvl04[13].x = 3600; game->ledgesLvl04[13].y = 170;
    game->ledgesLvl04[14].x = 4030; game->ledgesLvl04[14].y = 450;
    game->ledgesLvl04[15].x = 4300; game->ledgesLvl04[15].y = 400;
    game->ledgesLvl04[16].x = 4500; game->ledgesLvl04[16].y = 450;
    game->ledgesLvl04[17].x = 4700; game->ledgesLvl04[17].y = 450;
    game->ledgesLvl04[18].x = 5400; game->ledgesLvl04[18].y = 380;
    game->ledgesLvl04[19].x = 5100; game->ledgesLvl04[19].y = 320;
    game->ledgesLvl04[20].x = 5730; game->ledgesLvl04[20].y = 300;
    game->ledgesLvl04[21].x = 5800; game->ledgesLvl04[21].y = 350;
    game->ledgesLvl04[22].x = 6400; game->ledgesLvl04[22].y = 450;
    game->ledgesLvl04[23].x = 6700; game->ledgesLvl04[23].y = 380;
    game->ledgesLvl04[24].x = 7100; game->ledgesLvl04[24].y = 350;
    game->ledgesLvl04[25].x = 7300; game->ledgesLvl04[25].y = 350;
    game->ledgesLvl04[26].x = 7700; game->ledgesLvl04[26].y = 300;
    game->ledgesLvl04[27].x = 7900; game->ledgesLvl04[27].y = 300;
    game->ledgesLvl04[28].x = 8100; game->ledgesLvl04[28].y = 300;
    game->ledgesLvl04[29].x = 8400; game->ledgesLvl04[29].y = 430;
    game->ledgesLvl04[30].x = 8500; game->ledgesLvl04[30].y = 400;
    game->ledgesLvl04[31].x = 9000; game->ledgesLvl04[31].y = 450;
    game->ledgesLvl04[32].x = 9300; game->ledgesLvl04[32].y = 400;
    
    /// Coins
    // Level 01
    for(int i = 0; i < NUM_COINS01Lvl; i++) {
        game->coins[i].w = 25; game->coins[i].h = 25;
    }
    
    game->coins[0].x = 640; game->coins[0].y = 250;
    game->coins[1].x = 640+40;game->coins[1].y = 250;
    game->coins[2].x = 640+80; game->coins[2].y = 250;
    game->coins[3].x = 640+120; game->coins[3].y = 250;
    game->coins[4].x = 640+160;game->coins[4].y = 250;
    
    game->coins[5].x = 240; game->coins[5].y = 400;
    game->coins[6].x = 240+40;game->coins[6].y = 400;
    game->coins[7].x = 240+80; game->coins[7].y = 400;
    game->coins[8].x = 240+120; game->coins[8].y = 400;
    game->coins[9].x = 240+160;game->coins[9].y = 400;
    
    game->coins[10].x = 990; game->coins[10].y = 370;
    game->coins[11].x = 990+40;game->coins[11].y = 370;
    game->coins[12].x = 990+80; game->coins[12].y = 370;
    game->coins[13].x = 990+120; game->coins[13].y = 370;
    game->coins[14].x = 990+160;game->coins[14].y = 370;
    
    game->coins[15].x = 2440; game->coins[15].y = 400;
    game->coins[16].x = 2440+40; game->coins[16].y = 400;
    game->coins[17].x = 2440+80; game->coins[17].y = 400;
    game->coins[18].x = 2440+120; game->coins[18].y = 400;
    game->coins[19].x = 2440+160; game->coins[19].y = 400;
    
    game->coins[20].x = 3040; game->coins[20].y = 180;
    game->coins[21].x = 3040+40; game->coins[21].y = 180;
    game->coins[22].x = 3040+80; game->coins[22].y = 180;
    game->coins[23].x = 3040+120; game->coins[23].y = 180;
    game->coins[24].x = 3040+160; game->coins[24].y = 180;
    
    game->coins[25].x = 3440; game->coins[25].y = 400;
    game->coins[26].x = 3440+40; game->coins[26].y = 400;
    game->coins[27].x = 3440+80; game->coins[27].y = 400;
    game->coins[28].x = 3440+120; game->coins[28].y = 400;
    game->coins[29].x = 3440+160; game->coins[29].y = 400;
    
    game->coins[30].x = 4840; game->coins[30].y = 150;
    game->coins[31].x = 4840+40; game->coins[31].y = 150;
    game->coins[32].x = 4840+80; game->coins[32].y = 150;
    game->coins[33].x = 4840+120; game->coins[33].y = 150;
    game->coins[34].x = 4840+160; game->coins[34].y = 150;
    
    game->coins[35].x = 7240; game->coins[35].y = 250;
    game->coins[36].x = 7240+40; game->coins[36].y = 250;
    game->coins[37].x = 7240+80; game->coins[37].y = 250;
    game->coins[38].x = 7240+120; game->coins[38].y = 250;
    game->coins[39].x = 7240+160; game->coins[39].y = 250;
    
    game->coins[40].x = 9340; game->coins[40].y = 250;
    game->coins[41].x = 9340+40; game->coins[41].y = 250;
    game->coins[42].x = 9340+80; game->coins[42].y = 250;
    game->coins[43].x = 9340+120; game->coins[43].y = 250;
    game->coins[44].x = 9340+160; game->coins[44].y = 250;
    
    game->coins[45].x = 5820; game->coins[45].y = 250;
    game->coins[46].x = 5820+40; game->coins[46].y = 250;
    
    game->coins[47].x = 5620; game->coins[47].y = 370;
    game->coins[48].x = 5620+40; game->coins[48].y = 370;
    
    game->coins[49].x = 6020; game->coins[49].y = 150;
    game->coins[50].x = 6020+40; game->coins[50].y = 150;
    
    game->coins[51].x = 6820+40; game->coins[51].y = 190;
    game->coins[52].x = 6820+80; game->coins[52].y = 190;
    game->coins[53].x = 6820+120; game->coins[53].y = 190;
    game->coins[54].x = 6820+160; game->coins[54].y = 190;
    
    game->coins[55].x = 6820+40; game->coins[55].y = 190-50;
    game->coins[56].x = 6820+80; game->coins[56].y = 190-50;
    game->coins[57].x = 6820+120; game->coins[57].y = 190-50;
    game->coins[58].x = 6820+160; game->coins[58].y = 190-50;
    
    game->coins[59].x = 6820+40; game->coins[59].y = 190-100;
    game->coins[60].x = 6820+80; game->coins[60].y = 190-100;
    game->coins[61].x = 6820+120; game->coins[61].y = 190-100;
    game->coins[62].x = 6820+160; game->coins[62].y = 190-100;
    
    
    // Level 02
    for(int i = 0; i < NUM_COINS02Lvl; i++) {
        game->coinsLvl02[i].w = 25; game->coinsLvl02[i].h = 25;
    }
    game->coinsLvl02[0].x = 240+40; game->coinsLvl02[0].y = 500;
    game->coinsLvl02[1].x = 240+80; game->coinsLvl02[1].y = 500;
    game->coinsLvl02[2].x = 240+120; game->coinsLvl02[2].y = 500;
    game->coinsLvl02[3].x = 240+160; game->coinsLvl02[3].y = 500;
    
    game->coinsLvl02[4].x = 800+40; game->coinsLvl02[4].y = 230;
    game->coinsLvl02[5].x = 800+80; game->coinsLvl02[5].y = 230;
    game->coinsLvl02[6].x = 800+120; game->coinsLvl02[6].y = 230;
    game->coinsLvl02[7].x = 800+160; game->coinsLvl02[7].y = 230;
    
    game->coinsLvl02[8].x = 1480+40; game->coinsLvl02[8].y = 190;
    game->coinsLvl02[9].x = 1480+80; game->coinsLvl02[9].y = 190;
    game->coinsLvl02[10].x = 1480+120; game->coinsLvl02[10].y = 190;
    game->coinsLvl02[11].x = 1480+160; game->coinsLvl02[11].y = 190;
    
    game->coinsLvl02[12].x = 3570+40; game->coinsLvl02[12].y = 150;
    game->coinsLvl02[13].x = 3570+80; game->coinsLvl02[13].y = 150;
    game->coinsLvl02[14].x = 3570+120; game->coinsLvl02[14].y = 150;
    game->coinsLvl02[15].x = 3570+160; game->coinsLvl02[15].y = 150;
    game->coinsLvl02[16].x = 3570+200; game->coinsLvl02[16].y = 150;
    game->coinsLvl02[17].x = 3570+240; game->coinsLvl02[17].y = 150;
    game->coinsLvl02[18].x = 3570+280; game->coinsLvl02[18].y = 150;
    game->coinsLvl02[19].x = 3570+320; game->coinsLvl02[19].y = 150;
    game->coinsLvl02[20].x = 3570+360; game->coinsLvl02[20].y = 150;
    game->coinsLvl02[21].x = 3570+400; game->coinsLvl02[21].y = 150;
    game->coinsLvl02[22].x = 3570+440; game->coinsLvl02[22].y = 150;
    game->coinsLvl02[23].x = 3570+480; game->coinsLvl02[23].y = 150;
    
    game->coinsLvl02[24].x = 5000+40; game->coinsLvl02[24].y = 230;
    game->coinsLvl02[25].x = 5000+80; game->coinsLvl02[25].y = 230;
    game->coinsLvl02[26].x = 5000+120; game->coinsLvl02[26].y = 230;
    game->coinsLvl02[27].x = 5000+160; game->coinsLvl02[27].y = 230;
    
    game->coinsLvl02[28].x = 5780+40; game->coinsLvl02[28].y = 270;
    game->coinsLvl02[29].x = 5780+80; game->coinsLvl02[29].y = 270;
    game->coinsLvl02[30].x = 5780+120; game->coinsLvl02[30].y = 270;
    game->coinsLvl02[31].x = 5780+160; game->coinsLvl02[31].y = 270;
    
    game->coinsLvl02[32].x = 6780+40; game->coinsLvl02[32].y = 350;
    game->coinsLvl02[33].x = 6780+80; game->coinsLvl02[33].y = 350;
    game->coinsLvl02[34].x = 6780+120; game->coinsLvl02[34].y = 350;
    game->coinsLvl02[35].x = 6780+160; game->coinsLvl02[35].y = 350;
    
    game->coinsLvl02[36].x = 7800+40; game->coinsLvl02[36].y = 230;
    game->coinsLvl02[37].x = 7800+80; game->coinsLvl02[37].y = 230;
    game->coinsLvl02[38].x = 7800+120; game->coinsLvl02[38].y = 230;
    game->coinsLvl02[39].x = 7800+160; game->coinsLvl02[39].y = 230;
    
    game->coinsLvl02[40].x = 8700+40; game->coinsLvl02[40].y = 500;
    game->coinsLvl02[41].x = 8700+80; game->coinsLvl02[41].y = 500;
    game->coinsLvl02[42].x = 8700+120; game->coinsLvl02[42].y = 500;
    game->coinsLvl02[43].x = 8700+160; game->coinsLvl02[43].y = 500;
    game->coinsLvl02[44].x = 8700+200; game->coinsLvl02[44].y = 500;
    
    game->coinsLvl02[45].x = 9300+40; game->coinsLvl02[45].y = 450;
    game->coinsLvl02[46].x = 9300+80; game->coinsLvl02[46].y = 450;
    game->coinsLvl02[47].x = 9300+120; game->coinsLvl02[47].y = 450;
    game->coinsLvl02[48].x = 9300+160; game->coinsLvl02[48].y = 450;
    
    
    // Level 03
    for(int i = 0; i < NUM_COINS03Lvl; i++) {
        game->coinsLvl03[i].w = 25; game->coinsLvl03[i].h = 25;
    }
    game->coinsLvl03[0].x = 800+40; game->coinsLvl03[0].y = 300;
    game->coinsLvl03[1].x = 800+80; game->coinsLvl03[1].y = 300;
    game->coinsLvl03[2].x = 800+120; game->coinsLvl03[2].y = 300;
    game->coinsLvl03[3].x = 800+160; game->coinsLvl03[3].y = 300;
    
    game->coinsLvl03[4].x = 1000+40; game->coinsLvl03[4].y = 200;
    game->coinsLvl03[5].x = 1000+80; game->coinsLvl03[5].y = 200;
    game->coinsLvl03[6].x = 1000+120; game->coinsLvl03[6].y = 200;
    game->coinsLvl03[7].x = 1000+160; game->coinsLvl03[7].y = 200;
    
    game->coinsLvl03[8].x = 2000+40; game->coinsLvl03[8].y = 180;
    game->coinsLvl03[9].x = 2000+80; game->coinsLvl03[9].y = 180;
    game->coinsLvl03[10].x = 2000+120; game->coinsLvl03[10].y = 180;
    game->coinsLvl03[11].x = 2000+160; game->coinsLvl03[11].y = 180;
    
    game->coinsLvl03[12].x = 2200+40; game->coinsLvl03[12].y = 350;
    game->coinsLvl03[13].x = 2200+80; game->coinsLvl03[13].y = 350;
    game->coinsLvl03[14].x = 2200+120; game->coinsLvl03[14].y = 350;
    game->coinsLvl03[15].x = 2200+160; game->coinsLvl03[15].y = 350;
    
    game->coinsLvl03[16].x = 3600+40; game->coinsLvl03[16].y = 450;
    game->coinsLvl03[17].x = 3600+80; game->coinsLvl03[17].y = 450;
    game->coinsLvl03[18].x = 3600+120; game->coinsLvl03[18].y = 450;
    game->coinsLvl03[19].x = 3600+160; game->coinsLvl03[19].y = 450;
    
    game->coinsLvl03[20].x = 4400+40; game->coinsLvl03[20].y = 400;
    game->coinsLvl03[21].x = 4400+80; game->coinsLvl03[21].y = 400;
    game->coinsLvl03[22].x = 4400+120; game->coinsLvl03[22].y = 400;
    game->coinsLvl03[23].x = 4400+160; game->coinsLvl03[23].y = 400;
    
    game->coinsLvl03[24].x = 5700+40; game->coinsLvl03[24].y = 300;
    game->coinsLvl03[25].x = 5700+80; game->coinsLvl03[25].y = 300;
    game->coinsLvl03[26].x = 5700+120; game->coinsLvl03[26].y = 300;
    game->coinsLvl03[27].x = 5700+160; game->coinsLvl03[27].y = 300;
    
    game->coinsLvl03[28].x = 6400+40; game->coinsLvl03[28].y = 200;
    game->coinsLvl03[29].x = 6400+80; game->coinsLvl03[29].y = 200;
    game->coinsLvl03[30].x = 6400+120; game->coinsLvl03[30].y = 200;
    game->coinsLvl03[31].x = 6400+160; game->coinsLvl03[31].y = 200;
    
    game->coinsLvl03[32].x = 6900+40; game->coinsLvl03[32].y = 450;
    game->coinsLvl03[33].x = 6900+80; game->coinsLvl03[33].y = 450;
    game->coinsLvl03[34].x = 6900+120; game->coinsLvl03[34].y = 450;
    game->coinsLvl03[35].x = 6900+160; game->coinsLvl03[35].y = 450;
    
    game->coinsLvl03[36].x = 8200+40; game->coinsLvl03[36].y = 350;
    game->coinsLvl03[37].x = 8200+80; game->coinsLvl03[37].y = 350;
    game->coinsLvl03[38].x = 8200+120; game->coinsLvl03[38].y = 350;
    game->coinsLvl03[39].x = 8200+160; game->coinsLvl03[39].y = 350;
    
    game->coinsLvl03[40].x = 8800+40; game->coinsLvl03[40].y = 250;
    game->coinsLvl03[41].x = 8800+80; game->coinsLvl03[41].y = 250;
    game->coinsLvl03[42].x = 8800+120; game->coinsLvl03[42].y = 250;
    game->coinsLvl03[43].x = 8800+160; game->coinsLvl03[43].y = 250;
    
    game->coinsLvl03[44].x = 9200+40; game->coinsLvl03[44].y = 200;
    game->coinsLvl03[45].x = 9200+80; game->coinsLvl03[45].y = 200;
    game->coinsLvl03[46].x = 9200+120; game->coinsLvl03[46].y = 200;
    game->coinsLvl03[47].x = 9200+160; game->coinsLvl03[47].y = 200;
    
    
    // Coins level 04
    for(int i = 0; i < NUM_COINS04Lvl; i++){
        game->coinsLvl04[i].w = 25; game->coinsLvl04[i].h = 25;
    }
    game->coinsLvl04[0].x = 440; game->coinsLvl04[0].y = 300;
    game->coinsLvl04[1].x = 440+40; game->coinsLvl04[1].y = 300;
    game->coinsLvl04[2].x = 440+80; game->coinsLvl04[2].y = 300;
    game->coinsLvl04[3].x = 440+120; game->coinsLvl04[3].y = 300;
    game->coinsLvl04[4].x = 440+160; game->coinsLvl04[4].y = 300;
    
    game->coinsLvl04[5].x = 1140; game->coinsLvl04[5].y = 150;
    game->coinsLvl04[6].x = 1140+40; game->coinsLvl04[6].y = 150;
    game->coinsLvl04[7].x = 1140+80; game->coinsLvl04[7].y = 150;
    game->coinsLvl04[8].x = 1140+120; game->coinsLvl04[8].y = 150;
    game->coinsLvl04[9].x = 1140+160; game->coinsLvl04[9].y = 150;
    
    game->coinsLvl04[10].x = 2140; game->coinsLvl04[10].y = 270;
    game->coinsLvl04[11].x = 2140+40; game->coinsLvl04[11].y = 270;
    game->coinsLvl04[12].x = 2140+80; game->coinsLvl04[12].y = 270;
    game->coinsLvl04[13].x = 2140+120; game->coinsLvl04[13].y = 270;
    game->coinsLvl04[14].x = 2140+160; game->coinsLvl04[14].y = 270;
    
    game->coinsLvl04[15].x = 2640; game->coinsLvl04[15].y = 120;
    game->coinsLvl04[16].x = 2640+40; game->coinsLvl04[16].y = 120;
    game->coinsLvl04[17].x = 2640+80; game->coinsLvl04[17].y = 120;
    game->coinsLvl04[18].x = 2640+120; game->coinsLvl04[18].y = 120;
    game->coinsLvl04[19].x = 2640+160; game->coinsLvl04[19].y = 120;
    game->coinsLvl04[20].x = 2640+200; game->coinsLvl04[20].y = 120;
    game->coinsLvl04[21].x = 2640+240; game->coinsLvl04[21].y = 120;
    game->coinsLvl04[22].x = 2640+280; game->coinsLvl04[22].y = 120;
    game->coinsLvl04[23].x = 2640+320; game->coinsLvl04[23].y = 120;
    game->coinsLvl04[24].x = 2640+360; game->coinsLvl04[24].y = 120;
    game->coinsLvl04[25].x = 2640+400; game->coinsLvl04[25].y = 120;
    game->coinsLvl04[26].x = 2640+440; game->coinsLvl04[26].y = 120;
    game->coinsLvl04[27].x = 2640+480; game->coinsLvl04[27].y = 120;
    game->coinsLvl04[28].x = 2640+520; game->coinsLvl04[28].y = 120;
    game->coinsLvl04[29].x = 2640+560; game->coinsLvl04[29].y = 120;
    
    game->coinsLvl04[30].x = 5770; game->coinsLvl04[30].y = 250;
    game->coinsLvl04[31].x = 5770+40; game->coinsLvl04[31].y = 250;
    game->coinsLvl04[32].x = 5770+80; game->coinsLvl04[32].y = 250;
    game->coinsLvl04[33].x = 5770+120; game->coinsLvl04[33].y = 250;
    game->coinsLvl04[34].x = 5770+160; game->coinsLvl04[34].y = 250;
    
    game->coinsLvl04[35].x = 8540; game->coinsLvl04[35].y = 350;
    game->coinsLvl04[36].x = 8540+40; game->coinsLvl04[36].y = 350;
    game->coinsLvl04[37].x = 8540+80; game->coinsLvl04[37].y = 350;
    game->coinsLvl04[38].x = 8540+120; game->coinsLvl04[38].y = 350;
    game->coinsLvl04[39].x = 8540+160; game->coinsLvl04[39].y = 350;
    
    
    // Number of level at the top of the screen
    game->lvl01.x = 830; game->lvl01.y = 17; game->lvl01.w = 90; game->lvl01.h = 45; // Level 01
    game->lvl02.x = 830; game->lvl02.y = 17; game->lvl02.w = 90; game->lvl02.h = 45; // Level 02
    game->lvl03.x = 830; game->lvl03.y = 17; game->lvl03.w = 90; game->lvl03.h = 45; // Level 03
    game->lvl04.x = 830; game->lvl04.y = 17; game->lvl04.w = 90; game->lvl04.h = 45; // Level 04
    
    
    // Title of the level at the top of the screen
    game->lvl01t.x = 430; game->lvl01t.y = 22; game->lvl01t.w = 121; game->lvl01t.h = 39; // Level 01
    game->lvl02t.x = 430; game->lvl02t.y = 22; game->lvl02t.w = 131; game->lvl02t.h = 39; // Level 02
    game->lvl03t.x = 430; game->lvl03t.y = 22; game->lvl03t.w = 160; game->lvl03t.h = 39; // Level 03
    game->lvl04t.x = 430; game->lvl04t.y = 22; game->lvl04t.w = 131; game->lvl04t.h = 39; // Level 04
    
    
    /// Ground path
    // Level 01
    for(int i = 0; i < NUM_PATH; i++){
        game->grasses[i].w = 370; game->grasses[i].h = 120; game->grasses[i].x = i*356; game->grasses[i].y = 600;
    }
    
    // Level 02
    for(int i = 0; i < NUM_PATH; i++) {
        game->grassesLvl02[i].w = 370; game->grassesLvl02[i].h = 120; game->grassesLvl02[i].x = i*356; game->grassesLvl02[i].y = 600;
    }
    
    // Level 03
    for(int i = 0; i < NUM_PATH; i++) {
        game->grassesLvl03[i].w = 370; game->grassesLvl03[i].h = 120; game->grassesLvl03[i].x = i*356; game->grassesLvl03[i].y = 600;
    }
    
    // Level 04
    for(int i = 0; i < NUM_PATH; i++) {
        game->grassesLvl04[i].w = 155; game->grassesLvl04[i].h = 218; game->grassesLvl04[i].x = i*155; game->grassesLvl04[i].y = 550;
    }
    
    // Pigeons
    for (int i = 0; i < NUM_PIGEONS; i++) {
        game->pigeons[i].w = 30; game->pigeons[i].h = 26; game->pigeons[i].animFrame = 0;
    }
    game->pigeons[0].x = 600; game->pigeons[0].y = 525; game->pigeons[0].startPos = 600; game->pigeons[0].endPos = 150+(int)game->pigeons[0].x;
    game->pigeons[1].x = 760; game->pigeons[1].y = 325; game->pigeons[1].startPos = 760; game->pigeons[1].endPos = 220+(int)game->pigeons[1].x;
    game->pigeons[2].x = 2680; game->pigeons[2].y = 145; game->pigeons[2].startPos = 2680; game->pigeons[2].endPos = 180+(int)game->pigeons[2].x;
    game->pigeons[3].x = 2930; game->pigeons[3].y = 145; game->pigeons[3].startPos = 2930; game->pigeons[3].endPos = 200+(int)game->pigeons[3].x;
    game->pigeons[4].x = 4975; game->pigeons[4].y = 525; game->pigeons[4].startPos = 4975; game->pigeons[4].endPos = 190+(int)game->pigeons[4].x;
    game->pigeons[5].x = 5120; game->pigeons[5].y = 525; game->pigeons[5].startPos = 5120; game->pigeons[5].endPos = 220+(int)game->pigeons[5].x;
    game->pigeons[6].x = 5090; game->pigeons[6].y = 295; game->pigeons[6].startPos = 5090; game->pigeons[6].endPos = 200+(int)game->pigeons[6].x;
    game->pigeons[7].x = 6000; game->pigeons[7].y = 525; game->pigeons[7].startPos = 6000; game->pigeons[7].endPos = 190+(int)game->pigeons[7].x;
    game->pigeons[8].x = 6300; game->pigeons[8].y = 525; game->pigeons[8].startPos = 6300; game->pigeons[8].endPos = 210+(int)game->pigeons[8].x;
    game->pigeons[9].x = 6709; game->pigeons[9].y = 355; game->pigeons[9].startPos = 6709; game->pigeons[9].endPos = 180+(int)game->pigeons[9].x;
}

// Shortcuts used in development
void shortcuts(GameState *game) {
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    
    // Skip to level
    if(state[SDL_SCANCODE_1]){
        game->statusState = STATUS_STATE_GAME;
    }
    if(state[SDL_SCANCODE_2]){
        game->statusState = STATUS_STATE_LEVEL02;
    }
    if(state[SDL_SCANCODE_3]){
        game->statusState = STATUS_STATE_LEVEL03;
    }
    if(state[SDL_SCANCODE_4]){
        game->man.y = 500;
        game->statusState = STATUS_STATE_LEVEL04;
    }
    
    // Go back to menu
    if(state[SDL_SCANCODE_BACKSPACE]){
        game->man.lives = 6;
        game->statusState = STATUS_STATE_MENU;
    }
    
    // Skip ahead in level
    if(state[SDL_SCANCODE_Z]) {
        game->man.x = 100;
    }
    if(state[SDL_SCANCODE_X]) {
        game->man.x = 4500;
    }
    if(state[SDL_SCANCODE_C]) {
        game->man.x = 9000;
    }
    
    // Fill up on hearts
    if(state[SDL_SCANCODE_H]) {
        if (game->man.lives < 6) {
            game->man.lives++;
        }
    }
    
}

// Print message to console, for tracking process
void printLog(char *message) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("[%d:%d:%d] %s\n", tm.tm_hour, tm.tm_min, tm.tm_sec, message);
}

// Define attributes before each level, to initialize game
void defineAttributes(GameState *game) {
    game->man.x = 100;
    game->man.y = 552;
    game->man.dx = 0;
    game->man.dy = 0;
    game->man.onLedge = 0;
    game->man.animFrame = 0;
    game->man.facingLeft = 1;
    game->man.slowingDown = 0;
    game->man.lives = 6;
    game->man.coins = 0;
    game->man.isDead = 0;
    game->man.hasWon = 0;
    game->man.isImmortal = 0;
    game->time = 0;
    game->scrollX = 0;
    game->deathCountdown = -1;
    game->immortalCountdown = 0;
    game->winCountdown = 0;
}

void resetByWinning(GameState *game, float y) {
    game->winCountdown = 0;
    game->man.hasWon = 0;
    game->time = 0;
    game->man.x = 100;
    game->man.y = y;
    game->man.dx = 0;
    game->man.dy = 0;
    game->man.onLedge = 0;
    game->level = 6;
}


void resetByLosing(GameState *game) {
    game->statusState = STATUS_STATE_GAMEOVER;
    game->time = 0;
    game->level = 5;
    game->man.lives = 6;
    game->man.coins = 0;
}


/* Draw basic stuff in each level like coin counter, heart container, level text
 * Parameters: game, renderer, text color
 */
void drawBasics(GameState *game, SDL_Renderer *renderer, SDL_Color inputColor){
    SDL_Color color = inputColor;
    
    // Coin counter
    char str2[128] = "";
    sprintf(str2, "x %d", (int)game->man.coins);
    SDL_Surface *tmp2 = TTF_RenderText_Blended(game->font2, str2, color);
    game->labelW = tmp2->w;
    game->labelH = tmp2->h;
    game->label = SDL_CreateTextureFromSurface(game->renderer, tmp2);
    SDL_FreeSurface(tmp2);
    
    //Draw coin
    SDL_Rect coinRect = { game->coin.x, game->coin.y, game->coin.w, game->coin.h };
    SDL_RenderCopy(renderer, game->textureCoin, NULL, &coinRect);
    
    
    //set the drawing color to white
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    
    SDL_Rect text2Rect = { 220, 40-game->labelH/2, game->labelW, game->labelH };
    SDL_RenderCopy(renderer, game->label, NULL, &text2Rect);
    
    // Draw fire
    if(game->man.isDead){
        game->time++;
        SDL_Rect rect = { game->scrollX+game->man.x-24+38/2+10, game->man.y-24-13/2, 38, 83};
        SDL_RenderCopyEx(renderer, game->textureFire, NULL, &rect, 0, NULL, (game->time%20 < 10));
    }
}


// Error message in log if a sprite is not found
void errorMsgLoadTextures(char *message, SDL_Surface *surface) {
    if (surface == NULL) {
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        printf("[%d:%d:%d] Cannot find %s.png\n", tm.tm_hour, tm.tm_min, tm.tm_sec, message);
    }
}

// Load textures, fonts and audio, assign them to objects, and initialize attributes
void loadGame(GameState *game){
    
    /// Load textures
    SDL_Surface *surface = NULL;
    
    
    // Enemies
    // surface = IMG_Load("img/enemy01.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/enemy01.png");
    errorMsgLoadTextures("lvl01/enemy01", surface);
    game->enemyFrames[0] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/enemy02.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/enemy02.png");
    errorMsgLoadTextures("lvl01/enemy02", surface);
    game->enemyFrames[1] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/lvl01/enemy01Helmet.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/lvl01/enemy01Helmet.png");
    errorMsgLoadTextures("enemy01Helmet", surface);
    game->enemyFramesHelmet[0] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/lvl01/enemy02Helmet.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/lvl01/enemy02Helmet.png");
    errorMsgLoadTextures("enemy02Helmet", surface);
    game->enemyFramesHelmet[1] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/lvl01/enemy03Helmet.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/lvl03/enemy01shadow.png");
    errorMsgLoadTextures("enemy01shadow", surface);
    game->enemyFramesShadow[0] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/lvl03/enemy01shadow.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/lvl03/enemy02shadow.png");
    errorMsgLoadTextures("enemy02shadow", surface);
    game->enemyFramesShadow[1] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/lvl03/lvl04/enemy01.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/lvl04/enemy01.png");
    errorMsgLoadTextures("lvl04/enemy01", surface);
    game->enemyFrames04[0] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/lvl04/lvl04/enemy02.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/lvl04/enemy02.png");
    errorMsgLoadTextures("lvl04/enemy02", surface);
    game->enemyFrames04[1] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/lvl02/enemy01.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/lvl02/enemy01.png");
    errorMsgLoadTextures("lvl02/enemy01", surface);
    game->enemyFrames02[0] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/lvl02/enemy02.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/lvl02/enemy02.png");
    errorMsgLoadTextures("lvl02/enemy02", surface);
    game->enemyFrames02[1] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // Player
    // surface = IMG_Load("img/player01.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/player01.png");
    errorMsgLoadTextures("player01", surface);
    game->manFrames[0] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/player02.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/player02.png");
    errorMsgLoadTextures("player02", surface);
    game->manFrames[1] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/playerJump.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/playerJump.png");
    errorMsgLoadTextures("playerJump", surface);
    game->manFrames[2] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // Torches
    // surface = IMG_Load("img/lvl02/torch01.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/lvl02/torch01.png");
    errorMsgLoadTextures("torch01", surface);
    game->torchFrames[0] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/lvl02/torch02.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/lvl02/torch02.png");
    errorMsgLoadTextures("torch02", surface);
    game->torchFrames[1] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/player01Helmet.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/player01Helmet.png");
    errorMsgLoadTextures("player01Helmet", surface);
    game->manFramesHelmet[0] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/player02Helmet.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/player02Helmet.png");
    errorMsgLoadTextures("player02Helmet", surface);
    game->manFramesHelmet[1] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/playerJumpHelmet.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/playerJumpHelmet.png");
    errorMsgLoadTextures("playerJumpHelmet", surface);
    game->manFramesHelmet[2] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // Pigeons
    // surface = IMG_Load("img/lvl04/pigeon1.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/lvl04/pigeon1.png");
    errorMsgLoadTextures("pigeon1", surface);
    game->pigeonFrames[0] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/lvl04/pigeon2.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/lvl04/pigeon2.png");
    errorMsgLoadTextures("pigeon2", surface);
    game->pigeonFrames[1] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    
    // Grass ledges
    // surface = IMG_Load("img/lvl01/ledge.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/lvl01/ledge.png");
    errorMsgLoadTextures("lvl01/ledge", surface);
    game->textureLedgeLvl01 = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/lvl02/ledge.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/lvl02/ledge.png");
    errorMsgLoadTextures("lvl02/ledge", surface);
    game->textureLedgeLvl02 = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/lvl03/ledge.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/lvl03/ledge.png");
    errorMsgLoadTextures("lvl03/ledge", surface);
    game->textureLedgeLvl03 = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/lvl04/ledge.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/lvl04/pillar.png");
    errorMsgLoadTextures("lvl04/pillar", surface);
    game->textureLedgeLvl04 = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    
    // Paths
    // surface = IMG_Load("img/lvl01/path.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/lvl01/path.png");
    errorMsgLoadTextures("lvl01/path", surface);
    game->texturePathLvl01 = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/lvl02/path.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/lvl02/path.png");
    errorMsgLoadTextures("lvl02/path", surface);
    game->texturePathLvl02 = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/lvl03/path.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/lvl03/path.png");
    errorMsgLoadTextures("lvl03/path", surface);
    game->texturePathLvl03 = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/lvl04/path.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/lvl04/path.png");
    errorMsgLoadTextures("lvl04/path", surface);
    game->texturePathLvl04 = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    
    // Coins
    // surface = IMG_Load("img/coinTemp.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/coinTemp.png");
    errorMsgLoadTextures("coinTemp", surface);
    game->textureCoins = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    
    // Flags
    // surface = IMG_Load("img/flag.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/flag.png");
    errorMsgLoadTextures("flag", surface);
    game->textureFlag = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    
    // Heart
    // surface = IMG_Load("img/heart/1livesLeftWhiteOutline.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/heart/1livesLeftWhiteOutline.png");
    errorMsgLoadTextures("1livesLeftWhiteOutline", surface);
    game->textureHeartWhiteFrames[0] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    //  surface = IMG_Load("img/heart/2livesLeftWhiteOutline.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/heart/2livesLeftWhiteOutline.png");
    errorMsgLoadTextures("2livesLeftWhiteOutline", surface);
    game->textureHeartWhiteFrames[1] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/heart/3livesLeftWhiteOutline.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/heart/3livesLeftWhiteOutline.png");
    errorMsgLoadTextures("3livesLeftWhiteOutline", surface);
    game->textureHeartWhiteFrames[2] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/heart/4livesLeftWhiteOutline.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/heart/4livesLeftWhiteOutline.png");
    errorMsgLoadTextures("4livesLeftWhiteOutline", surface);
    game->textureHeartWhiteFrames[3] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/heart/5livesLeftWhiteOutline.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/heart/5livesLeftWhiteOutline.png");
    errorMsgLoadTextures("5livesLeftWhiteOutline", surface);
    game->textureHeartWhiteFrames[4] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    //surface = IMG_Load("img/heart/6livesLeftWhiteOutline.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/heart/6livesLeftWhiteOutline.png");
    errorMsgLoadTextures("6livesLeftWhiteOutline", surface);
    game->textureHeartWhiteFrames[5] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    
    // surface = IMG_Load("img/heart/1livesLeftBlackOutline.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/heart/1livesLeftBlackOutline.png");
    errorMsgLoadTextures("1livesLeftBlackOutline", surface);
    game->textureHeartBlackFrames[0] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/heart/2livesLeftBlackOutline.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/heart/2livesLeftBlackOutline.png");
    errorMsgLoadTextures("2livesLeftBlackOutline", surface);
    game->textureHeartBlackFrames[1] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    //  surface = IMG_Load("img/heart/3livesLeftBlackOutline.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/heart/3livesLeftBlackOutline.png");
    errorMsgLoadTextures("3livesLeftBlackOutline", surface);
    game->textureHeartBlackFrames[2] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/heart/4livesLeftBlackOutline.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/heart/4livesLeftBlackOutline.png");
    errorMsgLoadTextures("4livesLeftBlackOutline", surface);
    game->textureHeartBlackFrames[3] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    //  surface = IMG_Load("img/heart/5livesLeftBlackOutline.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/heart/5livesLeftBlackOutline.png");
    errorMsgLoadTextures("5livesLeftBlackOutline", surface);
    game->textureHeartBlackFrames[4] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/heart/6livesLeftBlackOutline.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/heart/6livesLeftBlackOutline.png");
    errorMsgLoadTextures("6livesLeftBlackOutline", surface);
    game->textureHeartBlackFrames[5] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    
    // Fire
    // surface = IMG_Load("img/fire.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/fire.png");
    errorMsgLoadTextures("fire", surface);
    game->textureFire = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    
    // Coin count
    // surface = IMG_Load("img/coinTemp.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/coinTemp.png");
    errorMsgLoadTextures("coinTemp", surface);
    game->textureCoin = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // Level number text
    // surface = IMG_Load("img/lvl01/level01.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/lvl01/level01.png");
    errorMsgLoadTextures("lvl01/level01", surface);
    game->textureLvl01 = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/lvl02/level02.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/lvl02/level02.png");
    errorMsgLoadTextures("lvl02/level02", surface);
    game->textureLvl02 = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/lvl03/level03.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/lvl03/level03.png");
    errorMsgLoadTextures("lvl03/level03", surface);
    game->textureLvl03 = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/lvl04/level04.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/lvl04/level04.png");
    errorMsgLoadTextures("lvl04/level04", surface);
    game->textureLvl04 = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    
    
    // Level title text
    // surface = IMG_Load("img/lvl01/title01.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/lvl01/title01.png");
    errorMsgLoadTextures("lvl01/title01", surface);
    game->textureLvl01t = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/lvl02/title02.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/lvl02/title02.png");
    errorMsgLoadTextures("lvl02/title02", surface);
    game->textureLvl02t = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/lvl03/title03.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/lvl03/title03.png");
    errorMsgLoadTextures("lvl03/title03", surface);
    game->textureLvl03t = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/lvl04/title04.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/lvl04/title04.png");
    errorMsgLoadTextures("lvl04/title04", surface);
    game->textureLvl04t = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    
    // Start menu
    // surface = IMG_Load("img/start2.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/start2.png");
    errorMsgLoadTextures("start2", surface);
    game->textureTitlescreen = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/PlayIsMarked.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/PlayIsMarked.png");
    errorMsgLoadTextures("PlayIsMarked", surface);
    game->texturePlay = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/CreditIsMarked.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/CreditIsMarked.png");
    errorMsgLoadTextures("CreditIsMarked", surface);
    game->textureCredits = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/ExitIsMarked.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/ExitIsMarked.png");
    errorMsgLoadTextures("ExitIsMarked", surface);
    game->textureExit = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // Credits menu
    // surface = IMG_Load("img/credits.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/credits.png");
    errorMsgLoadTextures("credits", surface);
    game->textureCreditsMenu = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // Won screen
    // surface = IMG_Load("img/gamewon.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/gamewon.png");
    errorMsgLoadTextures("gamewon", surface);
    game->textureWon = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/yes.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/yes.png");
    errorMsgLoadTextures("yes", surface);
    game->textureYes = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/no.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/no.png");
    errorMsgLoadTextures("no", surface);
    game->textureNo = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // Game over
    // surface = IMG_Load("img/gameover.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/gameover.png");
    errorMsgLoadTextures("gameover", surface);
    game->textureGameOver = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // Shadow background
    // surface = IMG_Load("img/lvl03/background.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/lvl03/background.png");
    errorMsgLoadTextures("lvl03/background", surface);
    game->textureShadowBackground = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // Star sky level 01
    // surface = IMG_Load("img/lvl01/stars.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/lvl01/stars.png");
    errorMsgLoadTextures("lvl01/stars", surface);
    game->textureStars = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // Clouds level 04
    // surface = IMG_Load("img/lvl04/cloudsFront.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/lvl04/cloudsFront.png");
    errorMsgLoadTextures("lvl04/cloudsFront", surface);
    game->textureCloudsFront = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/lvl04/cloudsBack.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/lvl04/cloudsBack.png");
    errorMsgLoadTextures("lvl04/cloudsBack", surface);
    game->textureCloudsBack = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // Statue
    // surface = IMG_Load("img/lvl04/statue.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/lvl04/statue.png");
    errorMsgLoadTextures("lvl01/statue", surface);
    game->textureStatue = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // Grey Pillar
    // surface = IMG_Load("img/lvl02/pillar.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/lvl02/pillar.png");
    errorMsgLoadTextures("lvl02/pillar", surface);
    game->textureGreyPillar = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    //  surface = IMG_Load("img/lvl02/highLedge.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/lvl02/highLedge.png");
    errorMsgLoadTextures("lvl02/highLedge", surface);
    game->textureHighLedge = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/lvl02/tilepattern.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/lvl02/tilepattern.png");
    errorMsgLoadTextures("lvl02/tilepattern", surface);
    game->textureTilepattern = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/lvl03/pillar.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/lvl03/pillar.png");
    errorMsgLoadTextures("lvl03/pillar", surface);
    game->textureShadowPillar = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    // surface = IMG_Load("img/heart/heart.png");
    surface = IMG_Load("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/img/heart/heart.png");
    errorMsgLoadTextures("heart", surface);
    game->texturePickupheart = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    
    //Load fonts
    // game->font = TTF_OpenFont("PIXELADE.TTF", 48);
    game->font = TTF_OpenFont("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/PIXELADE.TTF", 48);
    // game->font = TTF_OpenFont("PIXELADE.TTF", 32);
    game->font2 = TTF_OpenFont("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/PIXELADE.ttf", 32);
    
    
    // Load music (WINDOWS)
    // game->bg01 = Mix_LoadMUS("audio/Take_the_Lead.mp3");
    // game->bg02 = Mix_LoadMUS("audio/Cool_Rock.mp3");
    // game->bg03 = Mix_LoadMUS("audio/Saved_By_The_Ringtone.mp3");
    // game->bg03 = Mix_LoadMUS("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/audio/Saved_By_The_Ringtone.mp3"); // Removed to avoid copyright issues
    // game->bg04 = Mix_LoadMUS("audio/The_Cannery.mp3");
    // game->bg05 = Mix_LoadMUS("audio/Kool_Kats.mp3");
    // game->bg06 = Mix_LoadMUS("audio/game_over.mp3");
    // game->bg07 = Mix_LoadMUS("audio/win_game.wav");
    
    // Load music (MAC)
    game->bg01 = Mix_LoadMUS("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/audio/Take_the_Lead.mp3");
    game->bg02 = Mix_LoadMUS("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/audio/Cool_Rock.mp3");
    game->bg03 = Mix_LoadMUS("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/audio/Cryptic_Sorrow.mp3");
    game->bg04 = Mix_LoadMUS("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/audio/The_Cannery.mp3");
    game->bg05 = Mix_LoadMUS("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/audio/Kool_Kats.mp3");
    game->bg06 = Mix_LoadMUS("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/audio/game_over.mp3");
    game->bg07 = Mix_LoadMUS("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/audio/win_game.wav");
    
    
    // Load sounds
    // game->coinSound = Mix_LoadWAV("audio/coin.wav");
    game->coinSound = Mix_LoadWAV("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/audio/coin.wav");
    if (game->coinSound != NULL) {
        Mix_VolumeChunk(game->coinSound, 128);
    }
    
    // game->hurt = Mix_LoadWAV("audio/hurt3.wav"); // Not currently used
    game->hurt = Mix_LoadWAV("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/audio/hurt3.wav"); // Not currently used
    if (game->hurt != NULL) {
        Mix_VolumeChunk(game->hurt, 128);
    }
    
    // game->heartSound = Mix_LoadWAV("audio/heart2.wav");
    game->heartSound = Mix_LoadWAV("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/audio/heart2.wav");
    if (game->heartSound != NULL) {
        Mix_VolumeChunk(game->heartSound, 64);
    }
    
    // game->winLevel = Mix_LoadWAV("audio/win_level_2.wav");
    game->winLevel = Mix_LoadWAV("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/audio/win_level_2.wav");
    if (game->winLevel != NULL) {
        Mix_VolumeChunk(game->winLevel, 64);
    }
    
    // game->gameover_sound = Mix_LoadWAV("audio/gameover_sound.wav");
    game->gameover_sound = Mix_LoadWAV("/Users/julieglasdam/Documents/xCode_projecter/PixelMan02/PixelMan02/audio/gameover_sound.wav");
    if (game->gameover_sound != NULL) {
        Mix_VolumeChunk(game->gameover_sound, 64);
    }
    
    // Initialize all attributes
    game->label = NULL;
    game->statusState = STATUS_STATE_MENU;
    game->level = 0;
    defineAttributes(game);
    defineObjects(game);
}



// Check if player collides with something
int collide2d(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2) {
    return (!((x1 > (x2+wt2)) || (x2 > (x1+wt1)) || (y1 > (y2+ht2)) || (y2 > (y1+ht1))));
}


// Collision detection for all ledges and paths (including extra pillars, high ledges etc)
void collisionDetectPlatforms(GameState *game, float x, float y, float w, float h) {
    float mw = (float) game->man.w;
    float mh = (float) game->man.h;
    float mx = (float) game->man.x;
    float my = (float) game->man.y;
    float bx = (float) x;
    float by = (float) y;
    float bw = (float) w;
    
    
    if(mx+mw > bx && mx<bx+bw){ // If mans x coordinate + mans height is more than the x position of the top of the ledge (remember to check if up key is pressed)
        if(my+mh > by && my < by && game->man.dy > 0) { // If mans y coordinate + man height is more than the top of the ledge and the mans y coordinate is less than the top of the ledge and the man is moving
            game->man.y = by-mh; // Mans y position is y coordinate of ledge - mans height
            my = by-mh; // Mans y position is top of ledge - mans height
            game->man.dy = 0; // Man is not moving
            game->man.onLedge = 1;
        }
    }
}


// Collision detection enemies
void collisionDetectEnemies(GameState *game, float mx, float my, float ex, float ey, float mw, float mh, float ew, float eh) {
    if(collide2d(mx, my, ex, ey, mw, mh, ew, eh)) {
        //  Mix_PlayChannel(-1, game->hurt, 0);
        if (game->man.lives == 1) { // If he is down to 1 life
            game->man.isDead = 1; // He is dead
        }
        else {
            game->man.lives--; // Loose a life
            game->man.isImmortal = 1; // Enters immortal phase
        }
    }
}



// Players animation frames when walking and gravity
void playerMovement(GameState *game) {
    // Add gravity
    game->man.dy += GRAVITY;
    
    // For every frame, one is added to the x/y positions
    game->man.x += game->man.dx;
    game->man.y += game->man.dy;
    
    // Flip animation frame, every 8th frame, if man is moving, and not in the air, and not slowing down
    if(game->man.dx != 0 && game->man.onLedge && !game->man.slowingDown){
        if(game->time % 8 == 0){
            if(game->man.animFrame == 0){
                game->man.animFrame = 1;
            }
            else{
                game->man.animFrame = 0;
            }
        }
    }
}



void scrolling(GameState *game) {
    // Making the game scroll. Set scrollX to minus to make it scroll forwards. Offset by half the screen (+320) to center the player
    game->scrollX = -game->man.x+320;
    
    // Make sure we cant see anything to the left at the beginning of the level
    if(game->scrollX > 0)
        game->scrollX = 0;
    
    // Making sure we cant see anything to the right in the end
    else if(game->scrollX < -9300)
        game->scrollX = -9300;
}


/* Define logic for all levels, like collision detection, movement, changing variables when collection coins, getting/losing a life*/
void defineLogicForLevel01(GameState *game) {
    if(!game->man.isDead && !game->man.hasWon){
        // Initialize basic functions of the game
        playerMovement(game);
        scrolling(game);
        shortcuts(game);
        game->time++;
        
        // How many lives does he have
        game->heart.animFrame = ((int)game->man.lives-1);
        
        
        // Collision detect ground
        for(int i = 0; i < NUM_PATH; i++) {
            collisionDetectPlatforms(game, (float)game->grasses[i].x, (float)game->grasses[i].y, (float)game->grasses[i].w, (float)game->grasses[i].h );
        }
        
        // Collision detect ledges
        for(int i = 0; i < NUM_LEDGE01Lvl; i++) {
            collisionDetectPlatforms(game, (float)game->ledges[i].x, (float)game->ledges[i].y, (float)game->ledges[i].w, (float)game->ledges[i].h );
        }
        
        // Collision detect enemies
        if (game->man.isImmortal == 0) { // If he is not in immortal phase
            for(int i = 0; i < NUM_ENEMIES01Lvl; i++) {
                collisionDetectEnemies(game, (float)game->man.x, (float)game->man.y, (float)game->enemiesLvl01[i].x, (float)game->enemiesLvl01[i].y, (float)game->man.w, (float)game->man.h, (float)game->enemiesLvl01[i].w, (float)game->enemiesLvl01[i].h);
            }
        }
        else if (game->man.isImmortal == 1) { // If he is in immortal phase
            if (game->immortalCountdown < 120) { // Wait a few seconds
                game->immortalCountdown++;
            }
            else {
                game->immortalCountdown = 0; // Reset countdown for next time
                game->man.isImmortal = 0; // Making him mortal again
            }
        }
        
        
        // Collision detect coins
        for(int i = 0; i < NUM_COINS01Lvl; i++) {
            if(collide2d(game->man.x, game->man.y, game->coins[i].x, game->coins[i].y, 48, 48, 48, 48)) {
                game->man.coins++;
                game->coins[i].x = -300;
                Mix_PlayChannel(-1, game->coinSound, 0);
            }
        }
        
        // Collision detect hearts
        for(int i = 0; i < NUM_PICKUPHEARTS01Lvl; i++) {
            if(collide2d(game->man.x, game->man.y, game->pickupheartLvl01[i].x, game->pickupheartLvl01[i].y, 48, 48, 48, 48)) {
                if (game->man.lives < 6) {
                    game->man.lives++;
                }
                Mix_PlayChannel(-1, game->heartSound, 0);
                game->pickupheartLvl01[i].x = -300;
            }
        }
        
        
        // Enemy movement
        for (int i = 0; i < NUM_ENEMIES01Lvl; i++) {
            
            game->enemiesLvl01[i].x += game->enemiesLvl01[i].dx;
            
            if ((int)game->enemiesLvl01[i].x == (int)game->enemiesLvl01[i].startPos) { // If he's at his starting position
                game->enemiesLvl01[i].dx += 0.01; // add to dx variable every frame
                game->enemiesLvl01[i].facingLeft = 1;
                game->enemiesLvl01[i].animFrame = 0; // Non-walking sprite
            }
            else if ((int)game->enemiesLvl01[i].x == (int)game->enemiesLvl01[i].endPos) { // If he's at his end position
                game->enemiesLvl01[i].dx -= 0.01; // subtract from dx variable
                game->enemiesLvl01[i].facingLeft = 0;
                game->enemiesLvl01[i].animFrame = 0; // Non-walking sprite
            }
            
            if ((int)game->enemiesLvl01[i].x > (1+(int)game->enemiesLvl01[i].startPos) && (int)game->enemiesLvl01[i].x < ((int)game->enemiesLvl01[i].endPos-1)) { // If he's between his start and end position, minus 1 pixel in each end (to get around the lack)
                if(game->time % 20 == 0){ // Every 20th frame flip the animation frame
                    if(game->enemiesLvl01[i].animFrame == 0){
                        game->enemiesLvl01[i].animFrame = 1;
                    }
                    else{
                        game->enemiesLvl01[i].animFrame = 0;
                    }
                }
            }
        }
        
        if(game->man.x > 10000){
            game->man.hasWon = 1;
        }
    }
    
    // If you complete the level
    if (game->man.hasWon) {
        Mix_HaltMusic();
        Mix_PlayChannel(-1, game->winLevel, 0);
        if (game->winCountdown < 120) {
            game->winCountdown++;
        }
        else {
            resetByWinning(game, 552); // second parameter is the players y coordinate
            init_descScreen_02(game);
            game->statusState = STATUS_STATE_DESC02;
        }
    }
    
    
    
    // If you die
    if (game->man.isDead) {
        Mix_HaltMusic();
        Mix_PlayChannel(-1, game->gameover_sound, 0);
        if(game->deathCountdown < 0){ // deathCountdown is minus one by default, so this is always true when initialized
            game->deathCountdown = 60; // Set timer to 60
        }
        if(game->deathCountdown >= 0){ // It is more, because we just set it to 60
            game->deathCountdown--; // Count down
            if(game->deathCountdown < 0){ // When it reaches 0
                game->man.lives--;
                resetByLosing(game); // Reset everything, and send player to the game over screen
            }
        }
    }
    
}



void defineLogicForLevel02(GameState *game) {
    if(!game->man.isDead && !game->man.hasWon){
        
        // Initialize basic functions of the game
        game->level = 2;
        playerMovement(game);
        scrolling(game);
        shortcuts(game);
        game->time++;
        
        // How many lives does he have
        game->heart.animFrame = ((int)game->man.lives-1);
        
        // Collision detection ground
        for(int i = 0; i < NUM_PATH; i++) {   // Ground
            collisionDetectPlatforms(game, (float)game->grassesLvl02[i].x, (float)game->grassesLvl02[i].y, (float)game->grassesLvl02[i].w, (float)game->grassesLvl02[i].h);
        }
        
        // Collision detection ledges
        for(int i = 0; i < NUM_LEDGE02Lvl; i++) {
            collisionDetectPlatforms(game, (float)game->ledgesLvl02[i].x, (float)game->ledgesLvl02[i].y, (float)game->ledgesLvl02[i].w, (float)game->ledgesLvl02[i].h);
        }
        
        // Collision detection grey pillars
        for(int i = 0; i < NUM_GREYPILLARS; i++) {
            collisionDetectPlatforms(game, (float)game->pillars[i].x, game->pillars[i].y, game->pillars[i].w, game->pillars[i].h);
        }
        
        for(int i = 0; i < NUM_HIGHLEDGE; i++) {
            collisionDetectPlatforms(game, (float)game->highledge[i].x, (float)game->highledge[i].y, (float)game->highledge[i].w, (float)game->highledge[i].h);
        }
        
        
        // Collision detect enemies
        if (game->man.isImmortal == 0) { // If he is not in immortal phase
            for(int i = 0; i < NUM_ENEMIES02Lvl; i++) {
                collisionDetectEnemies(game, (float)game->man.x, (float)game->man.y, (float)game->enemiesLvl02[i].x, (float)game->enemiesLvl02[i].y, (float)game->man.w, (float)game->man.h, (float)game->enemiesLvl02[i].w, (float)game->enemiesLvl02[i].h);
            }
        }
        else if (game->man.isImmortal == 1) { // If he is in immortal phase
            if (game->immortalCountdown < 120) { // Wait a few seconds
                game->immortalCountdown++;
            }
            else {
                game->immortalCountdown = 0; // Reset countdown for next time
                game->man.isImmortal = 0; // Making him mortal again
            }
        }
        
        
        
        
        for(int i = 0; i < NUM_COINS02Lvl; i++) { // Coins
            if(collide2d(game->man.x, game->man.y, game->coinsLvl02[i].x, game->coinsLvl02[i].y, 48, 48, 48, 48)) {
                Mix_PlayChannel(-1, game->coinSound, 0);
                game->man.coins++;
                game->coinsLvl02[i].x = -300;
            }
        }
        
        // Collision detect hearts
        for(int i = 0; i < NUM_PICKUPHEARTS02Lvl; i++) {
            if(collide2d(game->man.x, game->man.y, game->pickupheartLvl02[i].x, game->pickupheartLvl02[i].y, 48, 48, 48, 48)) {
                if (game->man.lives < 6) {
                    game->man.lives++;
                }
                Mix_PlayChannel(-1, game->heartSound, 0);
                game->pickupheartLvl02[i].x = -300;
            }
        }
        
        
        // Enemy movement
        for (int i = 0; i < NUM_ENEMIES02Lvl; i++) {
            game->enemiesLvl02[i].x += game->enemiesLvl02[i].dx;
            
            if ((int)game->enemiesLvl02[i].x == (int)game->enemiesLvl02[i].startPos) { // If he's at his starting position
                game->enemiesLvl02[i].dx += 0.01; // add to dx variable every frame
                game->enemiesLvl02[i].facingLeft = 1;
                game->enemiesLvl02[i].animFrame = 0; // Non-walking sprite
            }
            else if ((int)game->enemiesLvl02[i].x == (int)game->enemiesLvl02[i].endPos) { // If he's at his end position
                game->enemiesLvl02[i].dx -= 0.01; // subtract from dx variable
                game->enemiesLvl02[i].facingLeft = 0;
                game->enemiesLvl02[i].animFrame = 0; // Non-walking sprite
            }
            
            if ((int)game->enemiesLvl02[i].x > (1+(int)game->enemiesLvl02[i].startPos) && (int)game->enemiesLvl02[i].x < ((int)game->enemiesLvl02[i].endPos-1)) { // If he's between his start and end position, minus 1 pixel in each end (to get around the lack)
                if(game->time % 20 == 0){ // Every 20th frame flip the animation frame
                    if(game->enemiesLvl02[i].animFrame == 0){
                        game->enemiesLvl02[i].animFrame = 1;
                    }
                    else{
                        game->enemiesLvl02[i].animFrame = 0;
                    }
                }
            }
        }
        
        // Torches
        for (int i = 0; i < NUM_TORCH; i++) {
            if (i == 0 || i%2 == 0 ) {
                if(game->time % 40 == 0){ // Every 20th frame flip the animation frame
                    if(game->torches[i].animFrame == 0){
                        game->torches[i].animFrame = 1;
                    }
                    else{
                        game->torches[i].animFrame = 0;
                    }
                }
            }
            else {
                if(game->time % 30 == 0){ // Every 20th frame flip the animation frame
                    if(game->torches[i].animFrame == 0){
                        game->torches[i].animFrame = 1;
                    }
                    else{
                        game->torches[i].animFrame = 0;
                    }
                }
            }
        }
        
        if(game->man.x > 10000){
            game->man.hasWon = 1;
        }
    }
    
    // If you complete the level
    if (game->man.hasWon) {
        Mix_HaltMusic();
        Mix_PlayChannel(-1, game->winLevel, 0);
        if (game->winCountdown < 120) {
            game->winCountdown++;
        }
        else {
            resetByWinning(game, 552); // second parameter is the players y coordinate
            init_descScreen_03(game);
            game->statusState = STATUS_STATE_DESC03;
        }
    }
    
    // If you die
    if (game->man.isDead) {
        Mix_HaltMusic();
        Mix_PlayChannel(-1, game->gameover_sound, 0);
        if(game->deathCountdown < 0){ // deathCountdown is minus one by default, so this is always true when initialized
            game->deathCountdown = 60; // Set timer to 60
        }
        if(game->deathCountdown >= 0){ // It is more, because we just set it to 60
            game->deathCountdown--; // Count down
            if(game->deathCountdown < 0){ // When it reaches 0
                game->man.lives--;
                resetByLosing(game); // Reset everything, and send player to the game over screen
            }
        }
    }
}

void defineLogicForLevel03(GameState *game) {
    if(!game->man.isDead && !game->man.hasWon){
        
        // Initialize basic functions of the game
        game->level = 3;
        playerMovement(game);
        scrolling(game);
        shortcuts(game);
        game->time++;
        
        // How many lives does he have
        game->heart.animFrame = ((int)game->man.lives-1);
        
        // Collision detection ground
        for(int i = 0; i < NUM_PATH; i++) {
            collisionDetectPlatforms(game, (float)game->grassesLvl03[i].x, (float)game->grassesLvl03[i].y, (float)game->grassesLvl03[i].w, (float)game->grassesLvl03[i].h);
        }
        
        // Collision detecting ledges
        for(int i = 0; i < NUM_LEDGE03Lvl; i++) {
            collisionDetectPlatforms(game, (float)game->ledgesLvl03[i].x, game->ledgesLvl03[i].y, game->ledgesLvl03[i].w, game->ledgesLvl03[i].h);
        }
        
        
        // Collision detect enemies
        if (game->man.isImmortal == 0) { // If he is not in immortal phase
            for(int i = 0; i < NUM_ENEMIES03Lvl; i++) {
                collisionDetectEnemies(game, (float)game->man.x, (float)game->man.y, (float)game->enemiesLvl03[i].x, (float)game->enemiesLvl03[i].y, (float)game->man.w, (float)game->man.h, (float)game->enemiesLvl03[i].w, (float)game->enemiesLvl03[i].h);
            }
        }
        else if (game->man.isImmortal == 1) { // If he is in immortal phase
            if (game->immortalCountdown < 120) { // Wait a few seconds
                game->immortalCountdown++;
            }
            else {
                game->immortalCountdown = 0; // Reset countdown for next time
                game->man.isImmortal = 0; // Making him mortal again
            }
        }
        
        
        for(int i = 0; i < NUM_COINS03Lvl; i++) { // Coins
            if(collide2d(game->man.x, game->man.y, game->coinsLvl03[i].x, game->coinsLvl03[i].y, 48, 48, 48, 48)) {
                Mix_PlayChannel(-1, game->coinSound, 0);
                game->man.coins++;
                game->coinsLvl03[i].x = -300;
            }
        }
        
        // Collision detect hearts
        for(int i = 0; i < NUM_PICKUPHEARTS03Lvl; i++) {
            if(collide2d(game->man.x, game->man.y, game->pickupheartLvl03[i].x, game->pickupheartLvl03[i].y, 48, 48, 48, 48)) {
                if (game->man.lives < 6) {
                    game->man.lives++;
                }
                Mix_PlayChannel(-1, game->heartSound, 0);
                game->pickupheartLvl03[i].x = -300;
            }
        }
        
        
        // Enemy movement
        for (int i = 0; i < NUM_ENEMIES03Lvl; i++) {
            game->enemiesLvl03[i].x += game->enemiesLvl03[i].dx;
            
            if ((int)game->enemiesLvl03[i].x == (int)game->enemiesLvl03[i].startPos) { // If he's at his starting position
                game->enemiesLvl03[i].dx += 0.01; // add to dx variable every frame
                game->enemiesLvl03[i].facingLeft = 1;
                game->enemiesLvl03[i].animFrame = 0; // Non-walking sprite
            }
            else if ((int)game->enemiesLvl03[i].x == (int)game->enemiesLvl03[i].endPos) { // If he's at his end position
                game->enemiesLvl03[i].dx -= 0.01; // subtract from dx variable
                game->enemiesLvl03[i].facingLeft = 0;
                game->enemiesLvl03[i].animFrame = 0; // Non-walking sprite
            }
            
            if ((int)game->enemiesLvl03[i].x > (1+(int)game->enemiesLvl03[i].startPos) && (int)game->enemiesLvl03[i].x < ((int)game->enemiesLvl03[i].endPos-1)) { // If he's between his start and end position, minus 1 pixel in each end (to get around the lack)
                if(game->time % 20 == 0){ // Every 20th frame flip the animation frame
                    if(game->enemiesLvl03[i].animFrame == 0){
                        game->enemiesLvl03[i].animFrame = 1;
                    }
                    else{
                        game->enemiesLvl03[i].animFrame = 0;
                    }
                }
            }
        }
        
        if(game->man.x > 10000){ // If you win
            game->man.hasWon = 1;
        }
    }
    
    // If you complete the level
    if (game->man.hasWon) {
        Mix_HaltMusic();
        Mix_PlayChannel(-1, game->winLevel, 0);
        if (game->winCountdown < 120) {
            game->winCountdown++;
        }
        else {
            resetByWinning(game, 502); // second parameter is the players y coordinate
            init_descScreen_04(game);
            game->statusState = STATUS_STATE_DESC04;
        }
    }
    
    // If you die
    if (game->man.isDead) {
        Mix_HaltMusic();
        Mix_PlayChannel(-1, game->gameover_sound, 0);
        if(game->deathCountdown < 0){ // deathCountdown is minus one by default, so this is always true when initialized
            game->deathCountdown = 60; // Set timer to 60
        }
        if(game->deathCountdown >= 0){ // It is more, because we just set it to 60
            game->deathCountdown--; // Count down
            if(game->deathCountdown < 0){ // When it reaches 0
                game->man.lives--;
                resetByLosing(game); // Reset everything, and send player to the game over screen
            }
        }
    }
}

void defineLogicForLevel04(GameState *game) {
    if(!game->man.isDead && !game->man.hasWon){
        
        // Initialize basic functions of the game
        game->level = 4;
        playerMovement(game);
        scrolling(game);
        shortcuts(game);
        game->time++;
        
        // How many lives does he have
        game->heart.animFrame = ((int)game->man.lives-1);
        
        // Collision detecting ground
        for(int i = 0; i < NUM_PATH; i++) {
            collisionDetectPlatforms(game, (float)game->grassesLvl04[i].x, (float)game->grassesLvl04[i].y, (float)game->grassesLvl04[i].w, (float)game->grassesLvl04[i].h);
        }
        
        // Collision detection ledges
        for(int i = 0; i < NUM_LEDGE04Lvl; i++) {
            collisionDetectPlatforms(game, (float)game->ledgesLvl04[i].x, game->ledgesLvl04[i].y, game->ledgesLvl04[i].w, game->ledgesLvl04[i].h);
        }
        
        
        // Collision detect enemies
        if (game->man.isImmortal == 0) { // If he is not in immortal phase
            for(int i = 0; i < NUM_ENEMIES04Lvl; i++) {
                collisionDetectEnemies(game, (float)game->man.x, (float)game->man.y, (float)game->enemiesLvl04[i].x, (float)game->enemiesLvl04[i].y, (float)game->man.w, (float)game->man.h, (float)game->enemiesLvl04[i].w, (float)game->enemiesLvl04[i].h);
            }
        }
        else if (game->man.isImmortal == 1) { // If he is in immortal phase
            if (game->immortalCountdown < 120) { // Wait a few seconds
                game->immortalCountdown++;
            }
            else {
                game->immortalCountdown = 0; // Reset countdown for next time
                game->man.isImmortal = 0; // Making him mortal again
            }
        }
        
        
        
        for(int i = 0; i < NUM_COINS04Lvl; i++) { // Coins
            if(collide2d(game->man.x, game->man.y, game->coinsLvl04[i].x, game->coinsLvl04[i].y, 48, 48, 48, 48)) {
                Mix_PlayChannel(-1, game->coinSound, 0);
                game->man.coins++;
                game->coinsLvl04[i].x = -300;
            }
        }
        
        // Collision detect hearts
        for(int i = 0; i < NUM_PICKUPHEARTS04Lvl; i++) {
            if(collide2d(game->man.x, game->man.y, game->pickupheartLvl04[i].x, game->pickupheartLvl04[i].y, 48, 48, 48, 48)) {
                if (game->man.lives < 6) {
                    game->man.lives++;
                }
                Mix_PlayChannel(-1, game->heartSound, 0);
                game->pickupheartLvl04[i].x = -300;
            }
        }
        
        
        // Enemy movement
        for (int i = 0; i < NUM_ENEMIES04Lvl; i++) {
            game->enemiesLvl04[i].x += game->enemiesLvl04[i].dx;
            
            if ((int)game->enemiesLvl04[i].x == (int)game->enemiesLvl04[i].startPos) { // If he's at his starting position
                game->enemiesLvl04[i].dx += 0.01; // add to dx variable every frame
                game->enemiesLvl04[i].facingLeft = 1;
                game->enemiesLvl04[i].animFrame = 0; // Non-walking sprite
            }
            else if ((int)game->enemiesLvl04[i].x == (int)game->enemiesLvl04[i].endPos) { // If he's at his end position
                game->enemiesLvl04[i].dx -= 0.01; // subtract from dx variable
                game->enemiesLvl04[i].facingLeft = 0;
                game->enemiesLvl04[i].animFrame = 0; // Non-walking sprite
            }
            
            
            if ((int)game->enemiesLvl04[i].x > (1+(int)game->enemiesLvl04[i].startPos) && (int)game->enemiesLvl04[i].x < ((int)game->enemiesLvl04[i].endPos-1)) { // If he's between his start and end position, minus 1 pixel in each end (to get around the lack)
                
                
                if(game->time % 20 == 0){ // Every 20th frame flip the animation frame
                    if(game->enemiesLvl04[i].animFrame == 0){
                        game->enemiesLvl04[i].animFrame = 1;
                    }
                    else if(game->enemiesLvl04[i].animFrame == 1){
                        game->enemiesLvl04[i].animFrame = 0;
                    }
                    
                }
                
            }
        }
        
        
        
        // Pigeon movement
        for (int i = 0; i < NUM_PIGEONS; i++) {
            game->pigeons[i].x += game->pigeons[i].dx;
            
            if ((int)game->pigeons[i].x == (int)game->pigeons[i].startPos) { // If he's at his starting position
                game->pigeons[i].dx += 0.01; // add to dx variable every frame
                game->pigeons[i].facingLeft = 1;
                game->pigeons[i].animFrame = 0; // Non-walking sprite
            }
            else if ((int)game->pigeons[i].x == (int)game->pigeons[i].endPos) { // If he's at his end position
                game->pigeons[i].dx -= 0.01; // subtract from dx variable
                game->pigeons[i].facingLeft = 0;
                game->pigeons[i].animFrame = 0; // Non-walking sprite
            }
            
            
            if ((int)game->pigeons[i].x > (1+(int)game->pigeons[i].startPos) && (int)game->pigeons[i].x < ((int)game->pigeons[i].endPos-1)) { // If he's between his start and end position, minus 1 pixel in each end (to get around the lack)
                
                
                if(game->time % 20 == 0){ // Every 20th frame flip the animation frame
                    if(game->pigeons[i].animFrame == 0){
                        game->pigeons[i].animFrame = 1;
                    }
                    else if(game->pigeons[i].animFrame == 1){
                        game->pigeons[i].animFrame = 0;
                    }
                    
                }
                
            }
        }
        
        
        if(game->man.x > 10000){ // If you win
            game->man.hasWon = 1;
        }
    }
    
    // If you complete the level
    if (game->man.hasWon) {
        Mix_HaltMusic();
        Mix_PlayChannel(-1, game->winLevel, 0);
        if (game->winCountdown < 120) {
            game->winCountdown++;
        }
        else {
            resetByWinning(game, 552); // second parameter is the players y coordinate
            game->statusState = STATUS_STATE_WIN;
        }
    }
    
    // If you die
    if (game->man.isDead) {
        Mix_HaltMusic();
        Mix_PlayChannel(-1, game->gameover_sound, 0);
        if(game->deathCountdown < 0){ // deathCountdown is minus one by default, so this is always true when initialized
            game->deathCountdown = 60; // Set timer to 60
        }
        if(game->deathCountdown >= 0){ // It is more, because we just set it to 60
            game->deathCountdown--; // Count down
            if(game->deathCountdown < 0){ // When it reaches 0
                game->man.lives--;
                resetByLosing(game); // Reset everything, and send player to the game over screen
            }
        }
    }
}







/* The structure of the game. Create different states, and define the flow of the states, based on the players actions, and their progrees in the game*/
int process(GameState *game) {
    int done2 = 0;
    
    // Menu screen
    if(game->statusState == STATUS_STATE_MENU){ // Start game active
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        
        if(state[SDL_SCANCODE_SPACE]){ // Go to level 01 descriptive text
            game->statusState = STATUS_STATE_LIVES;
        }
        if(state[SDL_SCANCODE_DOWN]){ // Hover over credits button
            game->statusState = STATUS_STATE_CREDITSACTIVE;
            SDL_Delay(150);
        }
        
    }
    
    
    else if(game->statusState == STATUS_STATE_CREDITSACTIVE){ // Credits button active
        draw_credits(game);
        
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if(state[SDL_SCANCODE_UP]){ // Hover over start game button
            game->statusState = STATUS_STATE_MENU;
            SDL_Delay(80);
        }
        if(state[SDL_SCANCODE_DOWN]){ // Hover over exit button
            game->statusState = STATUS_STATE_EXITACTIVE;
            SDL_Delay(80);
        }
        if(state[SDL_SCANCODE_SPACE]){ // Go to credits screen
            game->statusState = STATUS_STATE_CREDITS;
        }
    }
    
    
    else if(game->statusState == STATUS_STATE_EXITACTIVE){  // Exit button active
        draw_exit(game);
        SDL_Delay(50);
        
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if(state[SDL_SCANCODE_UP]){ // Hover over credits button
            game->statusState = STATUS_STATE_CREDITSACTIVE;
            SDL_Delay(50);
        }
        if(state[SDL_SCANCODE_SPACE]){ // Exit program
            done2 = 1;
        }
    }
    
    
    /// Credits menu
    else if (game->statusState == STATUS_STATE_CREDITS){
        draw_credits_menu(game);
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if(state[SDL_SCANCODE_BACKSPACE]){ // Go back to the menu
            game->statusState = STATUS_STATE_CREDITSACTIVE; // credits button is active
        }
    }
    
    
    /// Win game
    else if (game->statusState == STATUS_STATE_WIN) { // Yes - replay game
        game->level = 5;
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if(state[SDL_SCANCODE_RIGHT]){ // Hover over no button to exit game
            game->statusState = STATUS_STATE_WIN_NO;
            SDL_Delay(DELAY_SCROLL);
        }
        if(state[SDL_SCANCODE_SPACE]){ // Choose yes to replay game
            game->level = 1;
            game->statusState = STATUS_STATE_GAME;
        }
    }
    
    else if (game->statusState == STATUS_STATE_WIN_NO) { // No - go to menu
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if(state[SDL_SCANCODE_LEFT]){ // Hover over yes button to replay game
            game->statusState = STATUS_STATE_WIN;
            SDL_Delay(DELAY_SCROLL);
        }
        if(state[SDL_SCANCODE_SPACE]){ // Choose yes to replay game
            game->statusState = STATUS_STATE_MENU;
            //init_start_menu(game);
            SDL_Delay(DELAY_ENTER);
        }
    }
    
    
    
    /// Game over screen
    else if(game->statusState == STATUS_STATE_GAMEOVER){ // Yes - replay game
        draw_game_over(game);
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        
        if(state[SDL_SCANCODE_RIGHT]){ // Hover the no button
            game->statusState = STATUS_STATE_GAMEOVER_NO;
        }
        if(state[SDL_SCANCODE_SPACE]){ // Choose yes, to replay game
            game->statusState = STATUS_STATE_GAME;
            Mix_HaltMusic();
            defineAttributes(game);
            game->level = 1;
        }
    }
    
    else if(game->statusState == STATUS_STATE_GAMEOVER_NO){
        draw_game_over_no(game);
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        
        if(state[SDL_SCANCODE_LEFT]){ // Hover the yes button
            game->statusState = STATUS_STATE_GAMEOVER;
        }
        if(state[SDL_SCANCODE_SPACE]){ // Choose no, to go to the start menu
            
            game->level = 0;
            game->statusState = STATUS_STATE_MENU;
            SDL_Delay(DELAY_ENTER);
            Mix_HaltMusic();
            defineAttributes(game);
            
        }
    }
    
    
    
    /// Descriptive text before Level 01
    else if(game->statusState == STATUS_STATE_LIVES){
        game->time++;
        Mix_HaltMusic();
        if(game->time > 100){
            Mix_HaltMusic();
            game->immortalCountdown = 0; // I don't know why countdowns have to be initialized here
            game->winCountdown = 0;
            game->statusState = STATUS_STATE_GAME;
            game->level = 1;
        }
    }
    
    /// Descriptive text before Level 02
    else if(game->statusState == STATUS_STATE_DESC02){
        Mix_HaltMusic();
        game->level = 2;
        game->time++;
        if(game->time > 100){
            game->statusState = STATUS_STATE_LEVEL02;
        }
    }
    
    /// Descriptive text before Level 03
    else if(game->statusState == STATUS_STATE_DESC03){
        Mix_HaltMusic();
        game->level = 3;
        game->time++;
        if(game->time > 100){
            game->statusState = STATUS_STATE_LEVEL03;
        }
    }
    
    /// Descriptive text before Level 04
    else if(game->statusState == STATUS_STATE_DESC04){
        Mix_HaltMusic();
        game->level = 4;
        game->time++;
        if(game->time > 100){
            game->statusState = STATUS_STATE_LEVEL04;
        }
    }
    
    // Game levels
    else if(game->statusState == STATUS_STATE_GAME){
        defineLogicForLevel01(game);
    }
    
    else if(game->statusState == STATUS_STATE_LEVEL02){
        defineLogicForLevel02(game);
    }
    
    else if(game->statusState == STATUS_STATE_LEVEL03){
        defineLogicForLevel03(game);
    }
    
    else if(game->statusState == STATUS_STATE_LEVEL04){
        defineLogicForLevel04(game);
    }
    return done2;
}

/* Handle the user interaction. Define what to do when buttons are pressed */
int processEvents(SDL_Window *window, GameState *game) {
    SDL_Event event;
    int done = 0;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_WINDOWEVENT_CLOSE: {
                if(window) {
                    SDL_DestroyWindow(window);
                    window = NULL;
                    done = 1;
                }
            }
                break;
            case SDL_KEYDOWN: { // Check if a key is pressed
                switch(event.key.keysym.sym) {
                    case SDLK_ESCAPE: // Quit program
                        done = 1;
                        break;
                    case SDLK_w: // Jump
                        if(game->man.onLedge) {
                            game->man.dy = -8;
                            game->man.onLedge = 0;
                        }
                        break;
                    case SDLK_UP: // Jump
                        if(game->man.onLedge) {
                            game->man.dy = -8;
                            game->man.onLedge = 0;
                        }
                        break;
                }
            }
                break;
            case SDL_QUIT: // Quit game
                done = 1;
                break;
        }
    }
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP]) {
        game->man.dy -= 0.3f;
        game->man.animFrame = 2;
    }
    if(state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT]) {
        game->man.dx -= 0.5;
        if(game->man.dx < -6) {
            game->man.dx = -6;
        }
        game->man.facingLeft = 0;
        game->man.slowingDown = 0;
    }
    else if(state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT]) {
        game->man.dx += 0.5;
        if(game->man.dx > 6) {
            game->man.dx = 6;
        }
        game->man.facingLeft = 1;
        game->man.slowingDown = 0;
    }
    else {
        game->man.animFrame = 0;
        game->man.dx *= 0.8f;
        game->man.slowingDown = 1;
        if(fabsf(game->man.dx) < 0.1f) {
            game->man.dx = 0;
        }
    }
    
    // Move to process???
    if (!Mix_PlayingMusic() && mute == 0) {
        if (game->level == 0) {
            Mix_PlayMusic(game->bg05, -1);
        }
        else if (game->level == 1) {
            Mix_PlayMusic(game->bg01, -1);
        }
        else if (game->level == 2) {
            Mix_PlayMusic(game->bg02, -1);
        }
        else if (game->level == 3) {
            Mix_PlayMusic(game->bg03, -1);
        }
        else if (game->level == 4) {
            Mix_PlayMusic(game->bg04, -1);
        }
        else if (game->level == 5) {
            Mix_PlayMusic(game->bg06, -1);
        }
        else if (game->level == 6) {
            Mix_PlayMusic(game->bg07, -1);
        }
    }
    return done;
}

// Draw the textures for the objects in the four levels
void drawLevel01(GameState *game, SDL_Renderer *renderer) {
    // Background color
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    
    // Clear the screen
    SDL_RenderClear(renderer);
    
    //Draw star sky
    SDL_Rect starRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, game->textureStars, NULL, &starRect);
    
    //Draw flag
    SDL_Rect flagRect = { game->scrollX+game->flags.x, game->flags.y, game->flags.w, game->flags.h };
    SDL_RenderCopy(renderer, game->textureFlag, NULL, &flagRect);
    
    // Draw path
    for(int i = 0; i < NUM_PATH; i++) {
        SDL_Rect grassRect = {game->scrollX+game->grasses[i].x, game->grasses[i].y, game->grasses[i].w, game->grasses[i].h };
        SDL_RenderCopy(renderer, game->texturePathLvl01, NULL, &grassRect);
    }
    
    // Draw ledges
    for(int i = 0; i < NUM_LEDGE01Lvl; i++) {
        SDL_Rect ledgeRect = {game->scrollX+game->ledges[i].x, game->ledges[i].y, game->ledges[i].w, game->ledges[i].h };
        SDL_RenderCopy(renderer, game->textureLedgeLvl01, NULL, &ledgeRect);
    }
    
    // Draw coins
    for(int i = 0; i < NUM_COINS01Lvl; i++) {
        SDL_Rect coinsRect = {game->scrollX+game->coins[i].x, game->coins[i].y, game->coins[i].w, game->coins[i].h };
        SDL_RenderCopy(renderer, game->textureCoins, NULL, &coinsRect);
    }
    
    // Draw hearts
    for(int i = 0; i < NUM_PICKUPHEARTS01Lvl; i++) {
        SDL_Rect heartsRect = {game->scrollX+game->pickupheartLvl01[i].x, game->pickupheartLvl01[i].y, game->pickupheartLvl01[i].w, game->pickupheartLvl01[i].h };
        SDL_RenderCopy(renderer, game->texturePickupheart, NULL, &heartsRect);
    }
    
    
    // Draw enemies
    for(int i = 0; i < NUM_ENEMIES01Lvl; i++) {
        SDL_Rect enemyRect = { game->scrollX+game->enemiesLvl01[i].x, game->enemiesLvl01[i].y, game->enemiesLvl01[i].w, game->enemiesLvl01[i].h};
        SDL_RenderCopyEx(renderer, game->enemyFrames[game->enemiesLvl01[i].animFrame], NULL, &enemyRect, 0, NULL, (game->enemiesLvl01[i].facingLeft == 0));
    }
    
    
    
    
    //Draw level number
    SDL_Rect text01Rect = {game->lvl01.x, game->lvl01.y, game->lvl01.w, game->lvl01.h };
    SDL_RenderCopy(renderer, game->textureLvl01, NULL, &text01Rect);
    
    //Draw level name
    SDL_Rect title01Rect = {game->lvl01t.x, game->lvl01t.y, game->lvl01t.w, game->lvl01t.h };
    SDL_RenderCopy(renderer, game->textureLvl01t, NULL, &title01Rect);
    
    
    //Draw player
    SDL_Rect rect = { game->scrollX+game->man.x, game->man.y, game->man.w, game->man.h};
    SDL_RenderCopyEx(renderer, game->manFramesHelmet[game->man.animFrame], NULL, &rect, 0, NULL, (game->man.facingLeft == 0));
    
    
    
    //Draw basics
    SDL_Rect heartRect = { game->heart.x, game->heart.y, game->heart.w, game->heart.h };
    SDL_RenderCopyEx(renderer, game->textureHeartWhiteFrames[game->heart.animFrame], NULL, &heartRect, 0, NULL, SDL_FLIP_NONE);
    drawBasics(game, renderer, white);
    
}

void drawLevel02(GameState *game, SDL_Renderer *renderer) {
    // Background color
    SDL_SetRenderDrawColor(renderer, 19, 28, 43, 255);
    
    // Clear the screen
    SDL_RenderClear(renderer);
    
    // Draw tile pattern
    for(int i = 0; i < NUM_TILEPATTERN; i++) {
        SDL_Rect patternRect = {game->scrollX+game->tilepattern[i].x, game->tilepattern[i].y, game->tilepattern[i].w, game->tilepattern[i].h };
        SDL_RenderCopy(renderer, game->textureTilepattern, NULL, &patternRect);
    }
    
    // Draw torches
    for(int i = 0; i < NUM_TORCH; i++) {
        SDL_Rect torchRect = { game->scrollX+game->torches[i].x, game->torches[i].y, game->torches[i].w, game->torches[i].h};
        SDL_RenderCopyEx(renderer, game->torchFrames[game->torches[i].animFrame], NULL, &torchRect, 0, NULL, SDL_FLIP_NONE);
    }
    
    //Draw flag
    SDL_Rect flagRect = { game->scrollX+game->flags.x, game->flags.y,  game->flags.w, game->flags.h };
    SDL_RenderCopy(renderer, game->textureFlag, NULL, &flagRect);
    
    
    // Draw high ledge
    for(int i = 0; i < NUM_HIGHLEDGE; i++) {
        SDL_Rect highledgeRect = {game->scrollX+game->highledge[i].x, game->highledge[i].y, game->highledge[i].w, game->highledge[i].h };
        SDL_RenderCopy(renderer, game->textureHighLedge, NULL, &highledgeRect);
    }
    
    // Draw ledges
    for(int i = 0; i < NUM_LEDGE02Lvl; i++) {
        SDL_Rect ledge02Rect = {game->scrollX+game->ledgesLvl02[i].x, game->ledgesLvl02[i].y, game->ledgesLvl02[i].w, game->ledgesLvl02[i].h };
        SDL_RenderCopy(renderer, game->textureLedgeLvl02, NULL, &ledge02Rect);
    }
    
    // Draw pillars
    for(int i = 0; i < NUM_GREYPILLARS; i++) {
        SDL_Rect pillarRect = {game->scrollX+game->pillars[i].x, game->pillars[i].y, game->pillars[i].w, game->pillars[i].h };
        SDL_RenderCopy(renderer, game->textureGreyPillar, NULL, &pillarRect);
    }
    
    
    // Path
    for(int i = 0; i < NUM_PATH; i++) {
        SDL_Rect grass02Rect = {game->scrollX+game->grassesLvl02[i].x, game->grassesLvl02[i].y, game->grassesLvl02[i].w, game->grassesLvl02[i].h };
        SDL_RenderCopy(renderer, game->texturePathLvl02, NULL, &grass02Rect);
    }
    
    // Draw coins
    for(int i = 0; i < NUM_COINS02Lvl; i++) {
        SDL_Rect coins2Rect = {game->scrollX+game->coinsLvl02[i].x, game->coinsLvl02[i].y , game->coinsLvl02[i].w, game->coinsLvl02[i].h };
        SDL_RenderCopy(renderer, game->textureCoins, NULL, &coins2Rect);
    }
    
    // Draw hearts
    for(int i = 0; i < NUM_PICKUPHEARTS02Lvl; i++) {
        SDL_Rect heartsRect = {game->scrollX+game->pickupheartLvl02[i].x, game->pickupheartLvl02[i].y, game->pickupheartLvl02[i].w, game->pickupheartLvl02[i].h };
        SDL_RenderCopy(renderer, game->texturePickupheart, NULL, &heartsRect);
    }
    
    // Draw enemies
    for(int i = 0; i < NUM_ENEMIES02Lvl; i++) {
        SDL_Rect enemyRect = { game->scrollX+game->enemiesLvl02[i].x, game->enemiesLvl02[i].y, game->enemiesLvl02[i].w, game->enemiesLvl02[i].h};
        SDL_RenderCopyEx(renderer, game->enemyFrames02[game->enemiesLvl02[i].animFrame], NULL, &enemyRect, 0, NULL, (game->enemiesLvl02[i].facingLeft == 0));
    }
    
    
    
    //Draw level text
    SDL_Rect text02Rect = {game->lvl02.x, game->lvl02.y, game->lvl02.w, game->lvl02.h };
    SDL_RenderCopy(renderer, game->textureLvl02, NULL, &text02Rect);
    
    //Draw level name
    SDL_Rect title02Rect = {game->lvl02t.x, game->lvl02t.y , game->lvl02t.w, game->lvl02t.h };
    SDL_RenderCopy(renderer, game->textureLvl02t, NULL, &title02Rect);
    
    //Draw player
    SDL_Rect rect = { game->scrollX+game->man.x, game->man.y, game->man.w, game->man.h};
    SDL_RenderCopyEx(renderer, game->manFrames[game->man.animFrame], NULL, &rect, 0, NULL, (game->man.facingLeft == 0));
    
    // Draws the hearts and coins collected
    SDL_Rect heartRect = { game->heart.x, game->heart.y, game->heart.w, game->heart.h };
    SDL_RenderCopyEx(renderer, game->textureHeartWhiteFrames[game->heart.animFrame], NULL, &heartRect, 0, NULL, SDL_FLIP_NONE);
    drawBasics(game, renderer, white);
}

void drawLevel03(GameState *game, SDL_Renderer *renderer) {
    // Background color
    SDL_SetRenderDrawColor(renderer, 128, 128, 255, 255);
    
    // Clear the screen
    SDL_RenderClear(renderer);
    
    //Draw background
    SDL_Rect backgroundRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, game->textureShadowBackground, NULL, &backgroundRect);
    
    
    //Draw flag
    SDL_Rect flagRect = { game->scrollX+game->flags.x, game->flags.y, game->flags.w, game->flags.h };
    SDL_RenderCopy(renderer, game->textureFlag, NULL, &flagRect);
    
    //Draw level text
    SDL_Rect text03Rect = {game->lvl03.x, game->lvl03.y, game->lvl03.w, game->lvl03.h };
    SDL_RenderCopy(renderer, game->textureLvl03, NULL, &text03Rect);
    
    //Draw level name
    SDL_Rect title03Rect = {game->lvl03t.x, game->lvl03t.y, game->lvl03t.w, game->lvl03t.h };
    SDL_RenderCopy(renderer, game->textureLvl03t, NULL, &title03Rect);
    
    // Pillars
    for(int i = 0; i < NUM_SHADOWPILLAR; i++) {
        SDL_Rect pillarRect = {game->scrollX+game->shadowPillar[i].x, game->shadowPillar[i].y, game->shadowPillar[i].w, game->shadowPillar[i].h };
        SDL_RenderCopy(renderer, game->textureShadowPillar, NULL, &pillarRect);
    }
    
    // Draw ledges
    for(int i = 0; i < NUM_LEDGE03Lvl; i++) {
        SDL_Rect ledge03Rect = {game->scrollX+game->ledgesLvl03[i].x, game->ledgesLvl03[i].y, game->ledgesLvl03[i].w, game->ledgesLvl03[i].h };
        SDL_RenderCopy(renderer, game->textureLedgeLvl03, NULL, &ledge03Rect);
    }
    
    
    // Draw coins
    for(int i = 0; i < NUM_COINS03Lvl; i++) {
        SDL_Rect coins03Rect = {game->scrollX+game->coinsLvl03[i].x, game->coinsLvl03[i].y, game->coinsLvl03[i].w, game->coinsLvl03[i].h };
        SDL_RenderCopy(renderer, game->textureCoins, NULL, &coins03Rect);
    }
    
    // Draw hearts
    for(int i = 0; i < NUM_PICKUPHEARTS03Lvl; i++) {
        SDL_Rect heartsRect = {game->scrollX+game->pickupheartLvl03[i].x, game->pickupheartLvl03[i].y, game->pickupheartLvl03[i].w, game->pickupheartLvl03[i].h };
        SDL_RenderCopy(renderer, game->texturePickupheart, NULL, &heartsRect);
    }
    
    // Draw enemies
    for(int i = 0; i < NUM_ENEMIES03Lvl; i++) {
        SDL_Rect enemyRect = { game->scrollX+game->enemiesLvl03[i].x, game->enemiesLvl03[i].y, game->enemiesLvl03[i].w, game->enemiesLvl03[i].h};
        SDL_RenderCopyEx(renderer, game->enemyFramesShadow[game->enemiesLvl03[i].animFrame], NULL, &enemyRect, 0, NULL, (game->enemiesLvl03[i].facingLeft == 0));
    }
    
    // Path
    for(int i = 0; i < NUM_PATH; i++) {
        SDL_Rect grass03Rect = {game->scrollX+game->grassesLvl03[i].x, game->grassesLvl03[i].y, game->grassesLvl03[i].w, game->grassesLvl03[i].h };
        SDL_RenderCopy(renderer, game->texturePathLvl03, NULL, &grass03Rect);
    }
    
    
    //Draw player
    SDL_Rect rect = { game->scrollX+game->man.x, game->man.y, game->man.w, game->man.h};
    SDL_RenderCopyEx(renderer, game->manFrames[game->man.animFrame], NULL, &rect, 0, NULL, (game->man.facingLeft == 0));
    
    
    // Draws the hearts and coins collected
    SDL_Rect heartRect = { game->heart.x, game->heart.y, game->heart.w, game->heart.h };
    SDL_RenderCopyEx(renderer, game->textureHeartBlackFrames[game->heart.animFrame], NULL, &heartRect, 0, NULL, SDL_FLIP_NONE);
    drawBasics(game, renderer, black);
}

void drawLevel04(GameState *game, SDL_Renderer *renderer) {
    // Background color
    SDL_SetRenderDrawColor(renderer, 0, 149, 181, 0);
    
    // Clear the screen
    SDL_RenderClear(renderer);
    
    
    //Draw level text
    SDL_Rect text04Rect = {game->lvl04.x, game->lvl04.y, game->lvl04.w, game->lvl04.h };
    SDL_RenderCopy(renderer, game->textureLvl04, NULL, &text04Rect);
    
    //Draw level name
    SDL_Rect title04Rect = {game->lvl04t.x, game->lvl04t.y, game->lvl04t.w, game->lvl04t.h };
    SDL_RenderCopy(renderer, game->textureLvl04t, NULL, &title04Rect);
    
    // Clouds back
    for (int i = 0; i < NUM_CLOUDSBACK; i++) {
        SDL_Rect cloudsB = {game->scrollX+game->cloudsBack[i].x, game->cloudsBack[i].y, game->cloudsBack[i].w, game->cloudsBack[i].h };
        SDL_RenderCopy(renderer, game->textureCloudsBack, NULL, &cloudsB);
    }
    
    
    //Draw flag
    SDL_Rect flagRect = { game->scrollX+game->flags.x, 400, game->flags.w, game->flags.h };
    SDL_RenderCopy(renderer, game->textureFlag, NULL, &flagRect);
    
    // Statue
    SDL_Rect statue = {game->scrollX+game->statue.x, game->statue.y, game->statue.w, game->statue.h };
    SDL_RenderCopy(renderer, game->textureStatue, NULL, &statue);
    
    
    // Draw coins
    for(int i = 0; i < NUM_COINS04Lvl; i++) {
        SDL_Rect coins4Rect = {game->scrollX+game->coinsLvl04[i].x, game->coinsLvl04[i].y, game->coinsLvl04[i].w, game->coinsLvl04[i].h };
        SDL_RenderCopy(renderer, game->textureCoins, NULL, &coins4Rect);
    }
    
    // Draw hearts
    for(int i = 0; i < NUM_PICKUPHEARTS04Lvl; i++) {
        SDL_Rect heartsRect = {game->scrollX+game->pickupheartLvl04[i].x, game->pickupheartLvl04[i].y, game->pickupheartLvl04[i].w, game->pickupheartLvl04[i].h };
        SDL_RenderCopy(renderer, game->texturePickupheart, NULL, &heartsRect);
    }
    
    
    // Draw ledges
    for(int i = 0; i < NUM_LEDGE04Lvl; i++) {
        SDL_Rect ledge04Rect = {game->scrollX+game->ledgesLvl04[i].x, game->ledgesLvl04[i].y, game->ledgesLvl04[i].w, game->ledgesLvl04[i].h };
        SDL_RenderCopy(renderer, game->textureLedgeLvl04, NULL, &ledge04Rect);
    }
    
    
    
    // Draw enemies
    for(int i = 0; i < NUM_ENEMIES04Lvl; i++) {
        SDL_Rect enemy04Rect = { game->scrollX+game->enemiesLvl04[i].x, game->enemiesLvl04[i].y, game->enemiesLvl04[i].w, game->enemiesLvl04[i].h };
        SDL_RenderCopyEx(renderer, game->enemyFrames04[game->enemiesLvl04[i].animFrame], NULL, &enemy04Rect, 0, NULL, (game->enemiesLvl04[i].facingLeft == 0)); // game->enemiesLvl04[i].animFrame
    }
    
    // Draw pigeons
    for(int i = 0; i < NUM_PIGEONS; i++) {
        SDL_Rect pigeonRect = { game->scrollX+game->pigeons[i].x, game->pigeons[i].y, game->pigeons[i].w, game->pigeons[i].h };
        SDL_RenderCopyEx(renderer, game->pigeonFrames[game->pigeons[i].animFrame], NULL, &pigeonRect, 0, NULL, (game->pigeons[i].facingLeft == 0)); // game->enemiesLvl04[i].animFrame
    }
    
    // Path
    for(int i = 0; i < NUM_PATH; i++) {
        SDL_Rect grass04Rect = {game->scrollX+game->grassesLvl04[i].x, game->grassesLvl04[i].y, game->grassesLvl04[i].w, game->grassesLvl04[i].h };
        SDL_RenderCopy(renderer, game->texturePathLvl04, NULL, &grass04Rect);
    }
    
    //Draw player
    SDL_Rect rect = { game->scrollX+game->man.x, game->man.y, game->man.w, game->man.h};
    SDL_RenderCopyEx(renderer, game->manFrames[game->man.animFrame], NULL, &rect, 0, NULL, (game->man.facingLeft == 0));
    
    
    // Clouds front
    for (int i = 0; i < NUM_CLOUDSFRONT; i++) {
        SDL_Rect cloudsF = {game->scrollX+game->cloudsFront[i].x, game->cloudsFront[i].y, game->cloudsFront[i].w, game->cloudsFront[i].h };
        SDL_RenderCopy(renderer, game->textureCloudsFront, NULL, &cloudsF);
    }
    
    // Draws the hearts and coins collected
    SDL_Rect heartRect = { game->heart.x, game->heart.y, game->heart.w, game->heart.h };
    SDL_RenderCopyEx(renderer, game->textureHeartBlackFrames[game->heart.animFrame], NULL, &heartRect, 0, NULL, SDL_FLIP_NONE);
    drawBasics(game, renderer, black);
}


/* The structure of the when to draw the textures */
void doRender(SDL_Renderer *renderer, GameState *game) {
    
    // Textures for different states, like menu, win/gameover screen are defined in "status.c"
    if(game->statusState == STATUS_STATE_MENU) {
        draw_start_menu(game);
    }
    
    else if(game->statusState == STATUS_STATE_GAMEOVER) {
        draw_game_over(game);
    }
    else if(game->statusState == STATUS_STATE_WIN) {
        draw_game_win(game);
    }
    else if (game->statusState == STATUS_STATE_WIN_NO) {
        draw_game_win_no(game);
    }
    else if(game->statusState == STATUS_STATE_CREDITS){
        draw_credits_menu(game);
    }
    else if(game->statusState == STATUS_STATE_CREDITSACTIVE) {
        draw_credits(game);
    }
    else if(game->statusState == STATUS_STATE_EXITACTIVE) {
        draw_exit(game);
    }
    
    else if(game->statusState == STATUS_STATE_LIVES) {
        init_status_lives(game);
        draw_status_lives(game);
    }
    
    else if (game->statusState == STATUS_STATE_DESC02) {
        draw_descScreen_02(game);
    }
    
    else if (game->statusState == STATUS_STATE_DESC03) {
        draw_descScreen_03(game);
    }
    
    else if (game->statusState == STATUS_STATE_DESC04) {
        draw_descScreen_04(game);
    }
    
    
    // Textures for the four levels are defined in "main.c"
    else if(game->statusState == STATUS_STATE_GAME) {
        drawLevel01(game, renderer);
    }
    
    else if (game->statusState == STATUS_STATE_LEVEL02) {
        drawLevel02(game, renderer);
    }
    
    else if (game->statusState == STATUS_STATE_LEVEL03) {
        drawLevel03(game, renderer);
    }
    
    else if (game->statusState == STATUS_STATE_LEVEL04) {
        drawLevel04(game, renderer);
    }
    
    //We are done drawing, show to the screen what we've drawn
    SDL_RenderPresent(renderer);
}




int main(int argc, char *argv[]) {
    printLog("Start game");                          // Start console log
    GameState gameState;                             // Create instance of gamestate for reference
    SDL_Window *window = NULL;                       // Declare a window
    SDL_Renderer *renderer  = NULL;                  // Declare a renderer
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);       // Initialize SDL
    TTF_Init();                                      // Initialize ttf
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,
                  MIX_DEFAULT_FORMAT,
                  MIX_DEFAULT_CHANNELS, 4096);       // Initialize mixer
    
    srand((int)time(NULL));
    
    
    //Create an application window with the following settings:
    window = SDL_CreateWindow("Pixel Man",                 // window title
                              SDL_WINDOWPOS_UNDEFINED,     // initial x position
                              SDL_WINDOWPOS_UNDEFINED,     // initial y position
                              SCREEN_WIDTH,                // width defined in main.h
                              SCREEN_HEIGHT,               // height defined in main.h
                              0                            // flags
                              );
    
    // Initialize a renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    gameState.renderer = renderer;
    
    
    // Load textures
    loadGame(&gameState);
    
    // Event loop, initializing attributes, defining logic and drawing adding textures
    int done = 0;
    int done2 = 0;
    
    while(!done && !done2) {
        done = processEvents(window, &gameState);
        done2 = process(&gameState);
        doRender(renderer, &gameState);
    }
    
    // Destroy textures
    SDL_DestroyTexture(gameState.pigeonFrames[0]);
    SDL_DestroyTexture(gameState.pigeonFrames[1]);
    SDL_DestroyTexture(gameState.manFrames[0]);
    SDL_DestroyTexture(gameState.manFrames[1]);
    SDL_DestroyTexture(gameState.manFrames[2]);
    SDL_DestroyTexture(gameState.enemyFrames[0]);
    SDL_DestroyTexture(gameState.enemyFrames[1]);
    SDL_DestroyTexture(gameState.enemyFramesHelmet[0]);
    SDL_DestroyTexture(gameState.enemyFramesHelmet[1]);
    SDL_DestroyTexture(gameState.enemyFrames02[0]);
    SDL_DestroyTexture(gameState.enemyFrames02[1]);
    SDL_DestroyTexture(gameState.enemyFramesShadow[0]);
    SDL_DestroyTexture(gameState.enemyFramesShadow[1]);
    SDL_DestroyTexture(gameState.enemyFrames04[0]);
    SDL_DestroyTexture(gameState.enemyFrames04[1]);
    SDL_DestroyTexture(gameState.manFramesHelmet[0]);
    SDL_DestroyTexture(gameState.manFramesHelmet[1]);
    SDL_DestroyTexture(gameState.manFramesHelmet[2]);
    SDL_DestroyTexture(gameState.torchFrames[0]);
    SDL_DestroyTexture(gameState.torchFrames[1]);
    SDL_DestroyTexture(gameState.textureLedgeLvl01);
    SDL_DestroyTexture(gameState.textureLedgeLvl02);
    SDL_DestroyTexture(gameState.textureLedgeLvl03);
    SDL_DestroyTexture(gameState.textureLedgeLvl04);
    SDL_DestroyTexture(gameState.texturePathLvl01);
    SDL_DestroyTexture(gameState.texturePathLvl02);
    SDL_DestroyTexture(gameState.texturePathLvl03);
    SDL_DestroyTexture(gameState.texturePathLvl04);
    SDL_DestroyTexture(gameState.textureFire);
    SDL_DestroyTexture(gameState.textureFlag);
    SDL_DestroyTexture(gameState.textureCoins);
    SDL_DestroyTexture(gameState.textureTitlescreen);
    SDL_DestroyTexture(gameState.textureLvl01);
    SDL_DestroyTexture(gameState.textureLvl02);
    SDL_DestroyTexture(gameState.textureLvl03);
    SDL_DestroyTexture(gameState.textureLvl04);
    SDL_DestroyTexture(gameState.textureLvl01t);
    SDL_DestroyTexture(gameState.textureLvl02t);
    SDL_DestroyTexture(gameState.textureLvl03t);
    SDL_DestroyTexture(gameState.textureLvl04t);
    SDL_DestroyTexture(gameState.textureCoin);
    SDL_DestroyTexture(gameState.texturePlay);
    SDL_DestroyTexture(gameState.textureCredits);
    SDL_DestroyTexture(gameState.textureExit);
    SDL_DestroyTexture(gameState.textureWon);
    SDL_DestroyTexture(gameState.textureYes);
    SDL_DestroyTexture(gameState.textureNo);
    SDL_DestroyTexture(gameState.textureGameOver);
    SDL_DestroyTexture(gameState.textureStars);
    SDL_DestroyTexture(gameState.textureCloudsFront);
    SDL_DestroyTexture(gameState.textureCloudsBack);
    SDL_DestroyTexture(gameState.textureGreyPillar);
    SDL_DestroyTexture(gameState.textureHighLedge);
    SDL_DestroyTexture(gameState.textureTilepattern);
    SDL_DestroyTexture(gameState.textureShadowBackground);
    SDL_DestroyTexture(gameState.textureShadowPillar);
    SDL_DestroyTexture(gameState.texturePickupheart);
    
    for (int i = 0; i < 6; i++) {
        SDL_DestroyTexture(gameState.textureHeartBlackFrames[i]);
        SDL_DestroyTexture(gameState.textureHeartWhiteFrames[i]);
    }
    
    // Destroy label
    if(gameState.label != NULL)
        SDL_DestroyTexture(gameState.label);
    
    // Free memory of sounds and music
    Mix_FreeChunk(gameState.coinSound);
    Mix_FreeChunk(gameState.hurt);
    Mix_FreeChunk(gameState.heartSound);
    Mix_FreeChunk(gameState.winLevel);
    Mix_FreeChunk(gameState.gameover_sound);
    Mix_FreeMusic(gameState.bg01);
    Mix_FreeMusic(gameState.bg02);
    Mix_FreeMusic(gameState.bg03);
    Mix_FreeMusic(gameState.bg04);
    Mix_FreeMusic(gameState.bg05);
    Mix_FreeMusic(gameState.bg06);
    Mix_FreeMusic(gameState.bg07);
    
    
    // Close and destroy everything
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
    return 0;
}
