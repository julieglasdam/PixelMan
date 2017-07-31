//
//  main.h
//  PixelMan02
//
//  Created by Julie Glasdam on 30/06/2017.
//  Copyright © 2017 Julie Glasdam. All rights reserved.
//


#define main_h

#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>

/*
 #include <SDL.h>
 #include <SDL_ttf.h>
 #include <SDL_image.h>
 #include <SDL_mixer.h>
 */

#define STATUS_STATE_MENU 0
#define STATUS_STATE_LIVES 1
#define STATUS_STATE_GAME 2
#define STATUS_STATE_GAMEOVER 3
#define STATUS_STATE_WIN 4
#define STATUS_STATE_DESC02 5
#define STATUS_STATE_LEVEL02 6
#define STATUS_STATE_DESC03 7
#define STATUS_STATE_LEVEL03 8
#define STATUS_STATE_DESC04 9
#define STATUS_STATE_LEVEL04 10
#define STATUS_STATE_CREDITSACTIVE 11
#define STATUS_STATE_EXITACTIVE 12
#define STATUS_STATE_CREDITS 13
#define STATUS_STATE_WIN_NO 14
#define STATUS_STATE_GAMEOVER_NO 15

#define NUM_COINS01Lvl 63
#define NUM_COINS02Lvl 49
#define NUM_COINS03Lvl 48
#define NUM_COINS04Lvl 40

#define NUM_PATH 70

#define NUM_LEDGE01Lvl 52
#define NUM_LEDGE02Lvl 22
#define NUM_LEDGE03Lvl 29
#define NUM_LEDGE04Lvl 33

#define NUM_ENEMIES01Lvl 16
#define NUM_ENEMIES02Lvl 11
#define NUM_ENEMIES03Lvl 21
#define NUM_ENEMIES04Lvl 14

#define NUM_GREYPILLARS 6
#define NUM_HIGHLEDGE 3
#define NUM_TILEPATTERN 10
#define NUM_TORCH 20

#define NUM_SHADOWPILLAR 17

#define NUM_CLOUDSFRONT 20
#define NUM_CLOUDSBACK 20
#define NUM_PIGEONS 10

#define NUM_PICKUPHEARTS01Lvl 3
#define NUM_PICKUPHEARTS02Lvl 3
#define NUM_PICKUPHEARTS03Lvl 3
#define NUM_PICKUPHEARTS04Lvl 3

#define DELAY_SCROLL 80
#define DELAY_ENTER 800

#define SCREEN_WIDTH 940
#define SCREEN_HEIGHT 680


typedef struct {
    float x, y;
    float dx, dy;
    short lives;
    short coins;
    char *name;
    int onLedge, isDead;
    int collide;
    int w, h;
    int animFrame, facingLeft, slowingDown, isImmortal, hasWon;
} Man;


typedef struct {
    int x, y, w, h;
} Menu;


typedef struct {
    int x, y, w, h;
} LvlNumber;


typedef struct {
    int x, y, w, h;
} LvlTitle;


typedef struct {
    int x, y, w, h;
    int startPos, endPos;
    float dx, dy;
    int facingLeft, animFrame;
    
} Enemy;


typedef struct {
    int x, y, w, h;
} Ledge;


typedef struct {
    int x, y, w, h;
} Grass;


typedef struct {
    int x, y, w, h;
} Flag;


typedef struct {
    int x, y, w, h;
    int animFrame;
} Heart;


typedef struct {
    int x, y, w, h;
} Coins;


typedef struct {
    int x, y, w, h;
} Coin;

typedef struct {
    int x, y, w, h;
} Buttons;


typedef struct {
    int x, y, w, h;
} Sky;


typedef struct {
    double x, y, w, h;
    double startPos, endPos;
    double dx, dy;
} Clouds;


typedef struct {
    int x, y, w, h;
} Statue;


typedef struct {
    int x, y, w, h;
    int startPos, endPos;
    float dx, dy;
    int facingLeft, animFrame;
} Pigeons;


typedef struct {
    int x, y, w, h;
} GreyPillars;


typedef struct {
    int x, y, w, h;
} HighLedge;

typedef struct {
    int x, y, w, h;
} Tilepattern;

typedef struct {
    int x, y, w, h;
    int animFrame;
} Torch;

typedef struct {
    int x, y, w, h;
} ShadowPillar;

typedef struct {
    int x, y, w, h;
} PickupHeart;

typedef struct {
    float scrollX;
    Man man;
    
    // Level number
    LvlNumber lvl01;
    LvlNumber lvl02;
    LvlNumber lvl03;
    LvlNumber lvl04;
    
    // Level title
    LvlTitle lvl01t;
    LvlTitle lvl02t;
    LvlTitle lvl03t;
    LvlTitle lvl04t;
    
    // Menu screen
    Menu titlescreen;
    Menu creditsMenu;
    Menu wonScreen;
    Menu gameOver;
    Menu shadowBackground;
    
    // Buttons
    Buttons play;
    Buttons credits;
    Buttons exit;
    Buttons yes;
    Buttons no;
    
    //Enemies
    Enemy enemiesLvl01[NUM_ENEMIES01Lvl];
    Enemy enemiesLvl02[NUM_ENEMIES02Lvl];
    Enemy enemiesLvl03[NUM_ENEMIES03Lvl];
    Enemy enemiesLvl04[NUM_ENEMIES04Lvl];
    
    
    // Ledges
    Ledge ledges[NUM_LEDGE01Lvl];
    Ledge ledgesLvl02[NUM_LEDGE02Lvl];
    Ledge ledgesLvl03[NUM_LEDGE03Lvl];
    Ledge ledgesLvl04[NUM_LEDGE04Lvl];
    
    // Grey pillars
    GreyPillars pillars[NUM_GREYPILLARS];
    
    // High Ledge
    HighLedge highledge[NUM_HIGHLEDGE];
    
    // Grass
    Grass grasses[NUM_PATH];
    Grass grassesLvl02[NUM_PATH];
    Grass grassesLvl03[NUM_PATH];
    Grass grassesLvl04[NUM_PATH];
    
    
    Coins coins[NUM_COINS01Lvl];
    Coins coinsLvl02[NUM_COINS02Lvl];
    Coins coinsLvl03[NUM_COINS03Lvl];
    Coins coinsLvl04[NUM_COINS04Lvl];
    
    Heart heart;
    Coin coin;
    Flag flags;
    Sky starsky;
    
    Clouds cloudsFront[NUM_CLOUDSFRONT];
    Clouds cloudsBack[NUM_CLOUDSBACK];
    
    Pigeons pigeons[NUM_PIGEONS];
    
    Statue statue;
    
    Tilepattern tilepattern[NUM_TILEPATTERN];
    
    Torch torches[NUM_TORCH];
    
    ShadowPillar shadowPillar[NUM_SHADOWPILLAR];
    
    PickupHeart pickupheartLvl01[NUM_PICKUPHEARTS01Lvl];
    PickupHeart pickupheartLvl02[NUM_PICKUPHEARTS02Lvl];
    PickupHeart pickupheartLvl03[NUM_PICKUPHEARTS03Lvl];
    PickupHeart pickupheartLvl04[NUM_PICKUPHEARTS04Lvl];
    
    // Textures
    SDL_Texture *manFrames[3];
    SDL_Texture *enemyFrames[2];
    SDL_Texture *enemyFramesHelmet[2];
    SDL_Texture *enemyFrames02[2];
    SDL_Texture *enemyFramesShadow[2];
    SDL_Texture *enemyFrames04[2];
    SDL_Texture *manFramesHelmet[3];
    SDL_Texture *pigeonFrames[2];
    SDL_Texture *torchFrames[2];
    SDL_Texture *textureLedgeLvl01;
    SDL_Texture *textureLedgeLvl02;
    SDL_Texture *textureLedgeLvl03;
    SDL_Texture *textureLedgeLvl04;
    SDL_Texture *texturePathLvl01;
    SDL_Texture *texturePathLvl02;
    SDL_Texture *texturePathLvl03;
    SDL_Texture *texturePathLvl04;
    SDL_Texture *textureCoins;
    SDL_Texture *textureLvl01;
    SDL_Texture *textureLvl02;
    SDL_Texture *textureLvl03;
    SDL_Texture *textureLvl04;
    SDL_Texture *textureLvl01t;
    SDL_Texture *textureLvl02t;
    SDL_Texture *textureLvl03t;
    SDL_Texture *textureLvl04t;
    SDL_Texture *textureFire;
    SDL_Texture *textureHeartBlackFrames[6];
    SDL_Texture *textureHeartWhiteFrames[6];
    SDL_Texture *textureFlag;
    SDL_Texture *textureCoin;
    SDL_Texture *textureTitlescreen;
    SDL_Texture *texturePlay;
    SDL_Texture *textureCredits;
    SDL_Texture *textureExit;
    SDL_Texture *textureCreditsMenu;
    SDL_Texture *textureWon;
    SDL_Texture *textureYes;
    SDL_Texture *textureNo;
    SDL_Texture *textureGameOver;
    SDL_Texture *textureStars;
    SDL_Texture *textureCloudsFront;
    SDL_Texture *textureCloudsBack;
    SDL_Texture *textureStatue;
    SDL_Texture *textureGreyPillar;
    SDL_Texture *textureHighLedge;
    SDL_Texture *textureTilepattern;
    SDL_Texture *textureShadowBackground;
    SDL_Texture *textureShadowPillar;
    SDL_Texture *texturePickupheart;
    SDL_Texture *label;
    int labelW, labelH;
    
    //Fonts
    TTF_Font *font;
    TTF_Font *font2;
    
    // Sounds
    Mix_Chunk *coinSound, *hurt, *heartSound, *winLevel, *gameover_sound;
    Mix_Music *bg01, *bg02, *bg03, *bg04, *bg05, *bg06, *bg07;
    
    //time
    int time, deathCountdown, immortalCountdown, winCountdown;
    int statusState;
    int level;
    
    SDL_Renderer *renderer;
} GameState;



