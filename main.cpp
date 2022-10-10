// Project includes
#include "globals.h"
#include "hardware.h"
#include "map.h"
#include "graphics.h"
#include "speech.h"

#include <math.h>
#include<stdio.h>
char team1[] = "team 1 turn end";
char team1s[] = "team 2's turn now";
char team2[] = "team 2 turn ended";
char team2s[] ="team 1's turn now";
char attack[] = "Has Been Stabbed";


struct {
    int x,y;    // Current locations
    int px, py;
    int Tx,Rx,Ty,Ry;
    int Selection;
    Character* selected;
    Character* attacked;
} Camera;
struct {
    int currentTeam;
    int Team1Count;
    int Team2Count;
} Teams;
static Character character[10];

void int_charecters(Character* ch)
{
    // int j = 0;
    srand(time(0));
    for(int i = 0 ; i<8; i++) {
        int ra = rand();
        // Current locations
        ch[i].x=ra%90 + 10;
        ch[i].y=ra%30+20;
        ch[i].px=ch[i].x;
        ch[i].py=ch[i].y;

        ch[i].maxrange = (ra%4 + 2)*2 +1;
        ch[i].minrange = (ra%4 + 2)*2 +1;
        ch[i].Ty = ch[i].y - (ch[i].maxrange/2);
        ch[i].Tx = ch[i].x - (ch[i].minrange/2);
        ch[i].Rx = ch[i].x + (ch[i].minrange/2);
        ch[i].Ry = ch[i].y + (ch[i].maxrange/2);

        ch[i].turns =1;
        ch[i].alive=1;
        ch[i].team= i%2;
        pc.printf("%d", ch[i].team);
    }
    ch[0].name = "Team 1";
    ch[1].name = "Team 2";
    ch[2].name = "Team 1";
    ch[3].name = "Team 2";
    ch[4].name = "Team 1";
    ch[5].name = "Team 2";


    //health status
    ch[0].healthmarker = 1;
    ch[1].healthmarker = 1;
    ch[2].healthmarker = 1;
    ch[3].healthmarker = 1;
    ch[4].healthmarker = 1;
    ch[5].healthmarker = 1;

    //attack info
    ch[0].attackPoint =  22;
    ch[1].attackPoint =  19;
    ch[2].attackPoint =  20;
    ch[3].attackPoint =  24;
    ch[4].attackPoint =  15;
    ch[5].attackPoint =  25;

    //defence info
    ch[0].defencePoint = 5;
    ch[1].defencePoint = 3;
    ch[2].defencePoint = 4;
    ch[3].defencePoint = 6;
    ch[4].defencePoint = 0;
    ch[5].defencePoint = 6;


    ch[0].draw = draw_team1;
    ch[1].draw = draw_team2;
    ch[2].draw = draw_team1s;
    ch[3].draw = draw_team2s;
    ch[4].draw = draw_team1ss;
    ch[5].draw = draw_team2ss;

}
/**
 * Given the game inputs, determine what kind of update needs to happen.
 * Possbile return values are defined below.
 */
#define NO_ACTION 0
#define ACTION_BUTTON 1
#define BACK_BUTTON 2
#define GO_LEFT 3
#define GO_RIGHT 4
#define GO_UP 5
#define GO_DOWN 6

int get_action(GameInputs inputs)
{
    if(inputs.ay > 0) {
        if(inputs.ay > 0.3) {
            return GO_UP;
        }
    } else {
        if(inputs.ay < 0) {
            if(inputs.ay < -0.3) {
                return GO_DOWN;
            }
        }
    }
    if(inputs.ax > 0) {
        if(inputs.ax > 0.3) {
            return GO_RIGHT;
        }
    } else {
        if(inputs.ax < 0) {
            if(inputs.ax < -0.3) {
                return GO_LEFT;
            }
        }
    }
    if(inputs.b1)
        return  ACTION_BUTTON;
    if(inputs.b2)
        return BACK_BUTTON;
    return NO_ACTION;
}

int go_up()
{

    Camera.py = Camera.y;
    if(Camera.Selection == 0)
        if(get_north(Camera.x,Camera.y) -> walkable == NULL ) {
            return Camera.py;
        } else {
            Camera.y = Camera.y - 1;
            return Camera.y;
        } else if(get_north(Camera.x,Camera.y) -> walkable == NULL||(Camera.y<Camera.Ty) ) {
        return Camera.py;
    } else {
        Camera.y = Camera.y - 1;
        return Camera.y;
    }
}

int go_down()
{
    Camera.py = Camera.y;
    if(Camera.Selection==0)
        if(get_south(Camera.x,Camera.y) -> walkable == NULL) {
            return Camera.py;
        } else {
            Camera.y = Camera.y + 1;
            return Camera.y;
        } else if(get_south(Camera.x,Camera.y) -> walkable == NULL||(Camera.y>Camera.Ry) ) {
        return Camera.py;
    } else {
        Camera.y = Camera.y + 1;
        return Camera.y;
    }
}

int go_left()
{
    Camera.px = Camera.x;
    if(Camera.Selection == 0)
        if(get_west(Camera.x,Camera.y) -> walkable == NULL ) {
            return Camera.px;
        } else {
            Camera.x = Camera.x - 1;
            return Camera.x;
        } else if(get_west(Camera.x,Camera.y) -> walkable == NULL||(Camera.x<Camera.Tx) ) {
        return Camera.px;
    } else {
        Camera.x = Camera.x - 1;
        return Camera.x;
    }
}

int go_right()
{
    Camera.px = Camera.x;
    if(Camera.Selection ==0)
        if(get_east(Camera.x,Camera.y) -> walkable == NULL) {
            return Camera.px;
        } else {
            Camera.x = Camera.x + 1;
            return Camera.x;
        } else if(get_east(Camera.x,Camera.y) -> walkable == NULL||(Camera.x>Camera.Rx) ) {
        return Camera.px;
    } else {
        Camera.x = Camera.x + 1;
        return Camera.x;
    }
}
bool Locator()
{

    if (get_east(Camera.selected -> x,Camera.selected -> y) -> type == CHARACTERSPRITE) {
        Camera.attacked = get_east(Camera.selected -> x,Camera.selected -> y) ->data;
        return true;
    }
    if( get_west(Camera.selected -> x,Camera.selected -> y) -> type == CHARACTERSPRITE) {
        Camera.attacked = get_west(Camera.selected -> x,Camera.selected -> y) ->data;
        return true;
    }
    if(get_north(Camera.selected -> x,Camera.selected -> y) -> type == CHARACTERSPRITE) {
        Camera.attacked = get_north(Camera.selected -> x,Camera.selected -> y) ->data;
        return true;
    }
    if(get_south(Camera.selected -> x,Camera.selected -> y) ->type == CHARACTERSPRITE) {
        Camera.attacked = get_south(Camera.selected -> x,Camera.selected -> y) ->data;
        return true;
    }
    if(get_south_east(Camera.selected -> x,Camera.selected -> y) ->type == CHARACTERSPRITE) {
        Camera.attacked = get_south_east(Camera.selected -> x,Camera.selected -> y) ->data;
        return true;
    }
    if(get_south_west(Camera.selected -> x,Camera.selected -> y) ->type == CHARACTERSPRITE) {
        Camera.attacked = get_south_west(Camera.selected -> x,Camera.selected -> y) ->data;
        return true;
    }
    if(get_north_east(Camera.selected -> x,Camera.selected -> y) -> type == CHARACTERSPRITE) {
        Camera.attacked = get_north_east(Camera.selected -> x,Camera.selected -> y) ->data;
        return true;
    }
    if(get_north_west(Camera.selected -> x,Camera.selected -> y) -> type == CHARACTERSPRITE) {
        Camera.attacked = get_north_west(Camera.selected -> x,Camera.selected -> y) ->data;
        return true;
    }

    return false;

}

/**
 * Update the game state based on the user action. For example, if the user
 * requests GO_UP, then this function should determine if that is possible by
 * consulting the map, and update the Camera position accordingly.
 *
 * Return values are defined below. FULL_DRAW indicates that for this frame,
 * draw_game should not optimize drawing and should draw every tile, even if
 * the Camera has not moved.
 */
void reinitTurns()
{
    for(int i = 0 ; i<8; i++) {

        character[i].turns =1;

    }
}
#define NO_RESULT 0
#define GAME_OVER 1
#define FULL_DRAW 2
static int turnToggle = 0;

#define MODE_FREE_ROAM 1
#define MODE_SELECTED 2
int update_game(int action)
{
    // Save Camera previous location before updating
    Camera.px = Camera.x;
    Camera.py = Camera.y;

    // map m1;
    // Do different things based on the action
    // You can define smaller functions that get called for each case
    switch(action) {
        case ACTION_BUTTON:

            if(Camera.Selection == 0) {
                if(get_here(Camera.x,Camera.y)->type==CHARACTERSPRITE && get_here(Camera.x,Camera.y)->data->team == turnToggle && get_here(Camera.x,Camera.y)->data->turns==1) {
                    Camera.Selection = 1;
                    MapItem * select = get_here(Camera.x,Camera.y);
                    Camera.selected = select->data;
                    Camera.Tx = select->data->Tx;
                    Camera.Ty = select->data->Ty;
                    Camera.Rx = select->data->Rx;
                    Camera.Ry = select->data->Ry;
                    return FULL_DRAW;
                }
            } else {
                map_erase(Camera.selected->px,Camera.selected->py);
                Camera.selected->px = Camera.x;
                Camera.selected->py = Camera.y;
                Camera.selected->Tx = (Camera.x) - (Camera.selected -> minrange)/2;
                Camera.selected->Rx = (Camera.x) + (Camera.selected -> minrange)/2;
                Camera.selected->Ty = (Camera.y) - (Camera.selected -> maxrange)/2;
                Camera.selected->Ry = (Camera.y) + (Camera.selected -> maxrange)/2;
                add_character(Camera.x,Camera.y,Camera.selected);
                Camera.selected ->turns = 0;

                if(Locator()) {
                    if(Camera.attacked -> team != Camera.selected -> team) {
                        Camera.attacked->healthmarker = Camera.attacked->healthmarker -(Camera.selected->attackPoint-Camera.attacked->defencePoint);
                        speech(Camera.attacked -> name,attack);
                        pc.printf("attacked charaters's health = %d \n",Camera.attacked->healthmarker);
                        if(Camera.attacked->healthmarker <= 0) {

                            Camera.attacked->alive = 0;
                            map_erase(Camera.attacked->x,Camera.attacked->y);
                            if(Camera.attacked->team == 0)
                                Teams.Team1Count--;
                            else
                                Teams.Team2Count--;
                        }


                        if(Camera.attacked->alive) {

                            Camera.selected->healthmarker = Camera.selected->healthmarker -(Camera.attacked->attackPoint-Camera.selected->defencePoint);
                            speech(Camera.selected -> name,attack);
                            pc.printf("selected charaters's health = %d \n",Camera.selected->healthmarker);
                        }

                        if(Camera.selected->healthmarker <= 0) {
                            Camera.selected->alive = 0;
                            map_erase(Camera.selected->x,Camera.selected->y);
                            if(Camera.selected->team == 0)
                                Teams.Team1Count--;
                            else
                                Teams.Team2Count--;
                        }
                    }
                }
            }

            Camera.Selection = 0;
            print_map();
            return FULL_DRAW;

        case BACK_BUTTON:
            if(Camera.Selection == 1) {

                Camera.Selection = 0;
                print_map();

                return FULL_DRAW;
            } else {

                if(turnToggle)
                    speech(team2, team2s);
                else
                    speech(team1, team1s);
                turnToggle = !turnToggle;
                reinitTurns();
                return FULL_DRAW;
            }
        case GO_UP:
            if(go_up()) {
                return FULL_DRAW;
            }
            break;
        case GO_LEFT:
            if(go_left()) {
                return FULL_DRAW;
            }
            break;
        case GO_DOWN:
            if(go_down()) {
                return FULL_DRAW;
            }
            break;
        case GO_RIGHT:
            if(go_right()) {
                return FULL_DRAW;
            }
            break;
        default:
            break;
    }
    return NO_RESULT;
}

/**
 * Entry point for frame drawing. This should be called once per iteration of
 * the game loop. This draws all tiles on the screen, followed by the status
 * bars. Unless init is nonzero, this function will optimize drawing by only
 * drawing tiles that have changed from the previous frame.
 */
void draw_game(int init)
{
    // Draw game border first
    if(init) draw_border();

    // Iterate over all visible map tiles
    for (int i = -5; i <= 5; i++) { // Iterate over columns of tiles
        for (int j = -4; j <= 4; j++) { // Iterate over one column of tiles
            // Here, we have a given (i,j)

            // Compute the current map (x,y) of this tile
            int x = i + Camera.x;
            int y = j + Camera.y;

            // Compute the previous map (px, py) of this tile
            int px = i + Camera.px;
            int py = j + Camera.py;

            // Compute u,v coordinates for drawing
            int u = (i+5)*11 + 3;
            int v = (j+4)*11 + 15;

            // Figure out what to draw
            DrawFunc draw = NULL;
            if (i == 0 && j == 0) {
                // Decide what to draw at the 0 position
                draw = draw_selection;

            } else if (x >= 0 && y >= 0 && x < map_width() && y < map_height()) { // Current (i,j) in the map
                MapItem* curr_item = get_here(x, y);
                MapItem* prev_item = get_here(px, py);
                if (init || curr_item != prev_item) { // Only draw if they're different
                    if (curr_item) { // There's something here! Draw it
                        draw = curr_item->draw;
                    } else { // There used to be something, but now there isn't
                        draw = draw_nothing;
                    }
                }
            } else if (init) { // If doing a full draw, but we're out of bounds, draw the walls.
                draw = draw_wall;
            }
            // Actually draw the tile
            if (draw) draw(u, v);
        }
    }

}


/**
 * Initialize the main world map. Add walls around the edges, interior chambers,
 * and plants in the background so you can see motion.
 */
void init_main_map()
{

    Map* map = set_active_map(0);
    // "Random" plants
    for(int i = map_width() + 3; i < map_area(); i += 39) {
        add_plant(i % map_width(), i / map_width());
    }
    pc.printf("plants\r\n");
    int_charecters(character);
    pc.printf("Adding walls!\r\n");
    add_wall(0,              0,              HORIZONTAL, map_width());
    add_wall(0,              map_height()-1, HORIZONTAL, map_width());
    add_wall(0,              0,              VERTICAL,   map_height());
    add_wall(map_width()-1,  0,              VERTICAL,   map_height());
    add_character(5,5,&character[0]);
    add_character(7,5,&character[1]);

    add_character(5,8,&character[2]);
    add_character(7,8,&character[3]);

    add_character(5,10,&character[4]);
    add_character(7,10,&character[5]);
    pc.printf("Walls done!\r\n");
    print_map();

}

static int Game_status = 1;

int main()
{
    // First things first: initialize hardware
    char gameover[] = "The Game is";
    char gameover2[] = "Over!";

    while(1) {
        ASSERT_P(hardware_init() == ERROR_NONE, "Hardware init failed!");
        
        pc.printf("Program Starting");
        // Initialize the maps
        maps_init();

        init_main_map();
        Camera.x = Camera.px = 3;
        Camera.y = Camera.px = 3;
        Teams.currentTeam = turnToggle;

        Teams.Team1Count = 3;
        Teams.Team2Count = 3;

        // Initialize Characters


        // Initialize game state
        set_active_map(0);

        // Initial drawing
        draw_game(true);
        Game_status=1;
        // Main game loop

        while(Game_status) {
            // Timer to measure game update speed
            Timer t;
            t.start();

            // 1. Read inputs
            GameInputs in = read_inputs();
            // 2. Determine action (move, act, menu, etc.)
            int current_action  = get_action(in);
            // 3. Update game
            int current_update = update_game(current_action);
            // 3b. Check for game over
            // 4. Draw screen
            if(Teams.Team1Count&&Teams.Team2Count)
                draw_game(true);
            else {
                speech(gameover, gameover2);
            }
            // Compute update time
            t.stop();
            int dt = t.read_ms();
            if (dt < 100) wait_ms(100 - dt);
        }
    }
}
