//
//  status.c
//  PixelMan
//
//  Created by Julie Glasdam on 30/06/2017.
//  Copyright © 2017 Julie Glasdam. All rights reserved.
//

#include <stdio.h>
#include "main.h"

// ---------- Start menu: play -----------
/*
void init_start_menu(GameState *game)
{
    //Create label textures for status screen
    SDL_Color white = { 255, 255, 255, 255 };
    SDL_Surface *tmp = TTF_RenderText_Blended(game->font, "Start menu", white);
    game->labelW = tmp->w;
    game->labelH = tmp->h;
    game->label = SDL_CreateTextureFromSurface(game->renderer, tmp);
    SDL_FreeSurface(tmp);
    
    
}*/

void draw_start_menu(GameState *game)
{
    SDL_Renderer *renderer = game->renderer;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    
    //Clear the screen
    SDL_RenderClear(renderer);
    
    //set the drawing color to white
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    
    //Draw menu
    SDL_Rect titleRect = { 00, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, game->textureTitlescreen, NULL, &titleRect);
    
    SDL_Rect playRect = { game->play.x, game->play.y, 124, 130 };
    SDL_RenderCopy(renderer, game->texturePlay, NULL, &playRect);
    
}





// ---------- Start menu: credits -----------

void draw_credits(GameState *game)
{
    SDL_Renderer *renderer = game->renderer;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    
    //Clear the screen
    SDL_RenderClear(renderer);
    
    //set the drawing color to white
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    
    //Draw menu
    SDL_Rect titleRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, game->textureTitlescreen, NULL, &titleRect);
    
    SDL_Rect creditsRect = { game->credits.x, game->credits.y, 124, 130 };
    SDL_RenderCopy(renderer, game->textureCredits, NULL, &creditsRect);
    
}






// ---------- Start menu: exit -----------

void draw_exit(GameState *game)
{
    SDL_Renderer *renderer = game->renderer;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    
    //Clear the screen
    SDL_RenderClear(renderer);
    
    //set the drawing color to white
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    
    //Draw menu
    SDL_Rect titleRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, game->textureTitlescreen, NULL, &titleRect);
    
    SDL_Rect exitRect = { game->exit.x, game->exit.y, 124, 130 };
    SDL_RenderCopy(renderer, game->textureExit, NULL, &exitRect);
    
}





// ---------- Credits menu ----------

void draw_credits_menu(GameState *game) {
    SDL_Renderer *renderer = game->renderer;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    
    //Clear the screen
    SDL_RenderClear(renderer);
    
    //set the drawing color to white
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    
    //Draw menu
    SDL_Rect titleRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, game->textureCreditsMenu, NULL, &titleRect);
    
    
    
}




// ---------- DescScreen 01 -----------

void init_status_lives(GameState *game)
// Define the labels
{
    //Create label textures for status screen
    SDL_Color white = { 255, 255, 255, 255 };
    
    SDL_Surface *tmp = TTF_RenderText_Blended(game->font, "Level 01", white);
    game->labelW = tmp->w;
    game->labelH = tmp->h;
    game->label = SDL_CreateTextureFromSurface(game->renderer, tmp);
    SDL_FreeSurface(tmp);
}

void draw_status_lives(GameState *game)
// The actual drawings of text/images
{
    SDL_Renderer *renderer = game->renderer;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    
    //Clear the screen
    SDL_RenderClear(renderer);
    
    //set the drawing color to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    SDL_Rect textRect = { 460-game->labelW/2, 240-game->labelH/2, game->labelW, game->labelH };
    SDL_RenderCopy(renderer, game->label, NULL, &textRect);
    
}



// ---------- Game Over -----------


void draw_game_over(GameState *game)
{
    SDL_Renderer *renderer = game->renderer;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    
    //Clear the screen
    SDL_RenderClear(renderer);
    
    //set the drawing color to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    
    //Draw menu
    SDL_Rect gameoverRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, game->textureGameOver, NULL, &gameoverRect);
    
    SDL_Rect yes2Rect = { game->yes.x, game->yes.y, 226, 62 };
    SDL_RenderCopy(renderer, game->textureYes, NULL, &yes2Rect);
}


void draw_game_over_no(GameState *game)
{
    SDL_Renderer *renderer = game->renderer;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    
    //Clear the screen
    SDL_RenderClear(renderer);
    
    //set the drawing color to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    
    //Draw menu
    SDL_Rect gameoverRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, game->textureGameOver, NULL, &gameoverRect);
    
    SDL_Rect no2Rect = { game->no.x, game->no.y, 226, 62 };
    SDL_RenderCopy(renderer, game->textureNo, NULL, &no2Rect);
}




// ---------- DescScreen 02 -------

void init_descScreen_02(GameState *game){
    //Create label textures for status screen
    SDL_Color white = { 255, 255, 255, 255 };
    
    SDL_Surface *tmp = TTF_RenderText_Blended(game->font, "Level 02", white);
    game->labelW = tmp->w;
    game->labelH = tmp->h;
    game->label = SDL_CreateTextureFromSurface(game->renderer, tmp);
    SDL_FreeSurface(tmp);
    
}
void draw_descScreen_02(GameState *game) {
    SDL_Renderer *renderer = game->renderer;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    
    //Clear the screen
    SDL_RenderClear(renderer);
    
    //set the drawing color to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    SDL_Rect textRect = { 460-game->labelW/2, 240-game->labelH/2, game->labelW, game->labelH };
    SDL_RenderCopy(renderer, game->label, NULL, &textRect);
    
}




// ---------- DescScreen 03 -------

void init_descScreen_03(GameState *game){
    //Create label textures for status screen
    SDL_Color white = { 255, 255, 255, 255 };
    
    SDL_Surface *tmp = TTF_RenderText_Blended(game->font, "Level 03", white);
    game->labelW = tmp->w;
    game->labelH = tmp->h;
    game->label = SDL_CreateTextureFromSurface(game->renderer, tmp);
    SDL_FreeSurface(tmp);
    
}
void draw_descScreen_03(GameState *game) {
    SDL_Renderer *renderer = game->renderer;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    
    //Clear the screen
    SDL_RenderClear(renderer);
    
    //set the drawing color to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    SDL_Rect textRect = { 460-game->labelW/2, 240-game->labelH/2, game->labelW, game->labelH };
    SDL_RenderCopy(renderer, game->label, NULL, &textRect);
    
}


// ---------- DescScreen 04 -------

void init_descScreen_04(GameState *game){
    //Create label textures for status screen
    SDL_Color white = { 255, 255, 255, 255 };
    
    SDL_Surface *tmp = TTF_RenderText_Blended(game->font, "Level 04", white);
    game->labelW = tmp->w;
    game->labelH = tmp->h;
    game->label = SDL_CreateTextureFromSurface(game->renderer, tmp);
    SDL_FreeSurface(tmp);
    
}
void draw_descScreen_04(GameState *game) {
    SDL_Renderer *renderer = game->renderer;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    
    //Clear the screen
    SDL_RenderClear(renderer);
    
    //set the drawing color to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    SDL_Rect textRect = { 460-game->labelW/2, 240-game->labelH/2, game->labelW, game->labelH };
    SDL_RenderCopy(renderer, game->label, NULL, &textRect);
    
}





// ---------- Game Won -----------

void draw_game_win(GameState *game)
{
    SDL_Renderer *renderer = game->renderer;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    
    //Clear the screen
    SDL_RenderClear(renderer);
    
    //set the drawing color to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    //Draw menu
    SDL_Rect wonRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, game->textureWon, NULL, &wonRect);
    
    SDL_Rect yesRect = { game->yes.x, game->yes.y, 226, 62 };
    SDL_RenderCopy(renderer, game->textureYes, NULL, &yesRect);
    
    SDL_Color white = { 255, 255, 255, 255 };
    
    char str2[128] = "";
    
    sprintf(str2, "You collected %d coins", (int)game->man.coins);
    SDL_Surface *tmp2 = TTF_RenderText_Blended(game->font2, str2, white);
    game->labelW = tmp2->w;
    game->labelH = tmp2->h;
    game->label = SDL_CreateTextureFromSurface(game->renderer, tmp2);
    SDL_FreeSurface(tmp2);
    
    
    SDL_Rect text2Rect = { 370, 250-game->labelH/2, game->labelW, game->labelH };
    SDL_RenderCopy(renderer, game->label, NULL, &text2Rect);
}


void draw_game_win_no(GameState *game)
{
    SDL_Renderer *renderer = game->renderer;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    
    //Clear the screen
    SDL_RenderClear(renderer);
    
    //set the drawing color to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    //Draw menu
    SDL_Rect wonRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, game->textureWon, NULL, &wonRect);
    
    SDL_Rect noRect = { game->no.x, game->no.y, 226, 62 };
    SDL_RenderCopy(renderer, game->textureNo, NULL, &noRect);
    
    SDL_Color white = { 255, 255, 255, 255 };
    
    char str2[128] = "";
    
    sprintf(str2, "You collected %d coins", (int)game->man.coins);
    SDL_Surface *tmp2 = TTF_RenderText_Blended(game->font2, str2, white);
    game->labelW = tmp2->w;
    game->labelH = tmp2->h;
    game->label = SDL_CreateTextureFromSurface(game->renderer, tmp2);
    SDL_FreeSurface(tmp2);
    
    
    SDL_Rect text2Rect = { 370, 250-game->labelH/2, game->labelW, game->labelH };
    SDL_RenderCopy(renderer, game->label, NULL, &text2Rect);
    
}


