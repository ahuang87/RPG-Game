#ifndef GRAPHICS_H
#define GRAPHICS_H

/**
 * Takes a string image and draws it to the screen. The string is 121 characters
 * long, and represents an 11x11 tile in row-major ordering (across, then down,
 * like a regular multi-dimensional array). The available colors are:
 *      R = Red
 *      Y = Yellow
 *      G = Green
 *      D = Brown ("dirt")
 *      5 = Light grey (50%)
 *      3 = Dark grey (30%)
 *      Any other character is black
 * More colors can be easily added by following the pattern already given.
 */
void draw_img(int u, int v, const char* img);

/**
 * DrawFunc functions. 
 * These can be used as the MapItem draw functions.
 */
void draw_nothing(int u, int v);
void draw_wall(int u, int v);
void draw_plant(int u, int v);


void draw_team1(int u, int v);
void draw_team2(int u, int v);

void draw_team1s(int u, int v);
void draw_team2s(int u, int v);

void draw_team1ss(int u, int v);
void draw_team2ss(int u, int v);



void draw_player1sprite(int u, int v);
void draw_player2sprite(int u, int v);
void draw_selection(int u, int v);


 
/**
 * Draw the border for the map.
 */
void draw_border();

#endif // GRAPHICS_H