//
//  status.h
//  PixelMan02
//
//  Created by Julie Glasdam on 30/06/2017.
//  Copyright © 2017 Julie Glasdam. All rights reserved.
//

#define status_h

#include <stdio.h>

// Start menu
//void init_start_menu(GameState *game);
void draw_start_menu(GameState *game);

void draw_credits(GameState *game);

void draw_exit(GameState *game);

// Credits menu
void draw_credits_menu(GameState *game);

// Level 01 text description
void init_status_lives(GameState *game);
void draw_status_lives(GameState *game);

// Level 02 text description
void init_descScreen_02(GameState *game);
void draw_descScreen_02(GameState *game);

// Level 03 text description
void init_descScreen_03(GameState *game);
void draw_descScreen_03(GameState *game);


// Level 04 text description
void init_descScreen_04(GameState *game);
void draw_descScreen_04(GameState *game);

// Game over
void draw_game_over(GameState *game);
void draw_game_over_no(GameState *game);

// Win game
void draw_game_win(GameState *game);
void draw_game_win_no(GameState *game);

