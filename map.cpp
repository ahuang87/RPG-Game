#include "map.h"

#include "globals.h"
#include "graphics.h"

/**
 * The Map structure. This holds a HashTable for all the MapItems, along with
 * values for the width and height of the Map.
 */
struct Map {
    HashTable* items;
    int w, h;
};

#define NUM_MAPS 2
static Map maps[NUM_MAPS];
static int active_map;

/**
 * The first step in HashTable access for the map is turning the two-dimensional
 * key information (x, y) into a one-dimensional unsigned integer.
 * This function should uniquely map (x,y) onto the space of unsigned integers.
 */
static unsigned XY_KEY(int X, int Y)
{
    unsigned int key = map_width()*Y + X;
    return key;
    // TODO: Fix me!
}

/**
 * This is the hash function actually passed into createHashTable. It takes an
 * unsigned key (the output of XY_KEY) and turns it into a hash value (some
 * small non-negative integer).
 */
unsigned map_hash(unsigned key)
{
    return key%100;

}

void maps_init()
{
    maps[0].items = createHashTable(map_hash,100);
    maps[0].w=100;
    maps[0].h=50;

    // TODO: Implement!
    // Initialize hash table
    // Set width & height
}

Map* get_active_map()
{
    return &maps[active_map];
}

Map* set_active_map(int m)
{
    active_map = m;
    return &maps[active_map];
}

void print_map()
{
    char lookup[] = {'W', 'D', 'P', 'A', 'K', 'C', 'N',' ','S'};
    Map* map = get_active_map();
    for(int j = 0; j < map->h; j++) {
        for (int i = 0; i < map->w; i++) {
            MapItem* item = (MapItem*)getItem(map->items, XY_KEY(i, j));
            if (item) pc.printf("%c", lookup[item->type]);
            else pc.printf(" ");
        }
        pc.printf("\r\n");
    }
}

int map_width()
{
    // FIX THIS
    return get_active_map()->w;
}

int map_height()
{
    // FIX THIS
    return get_active_map()->h;
}

int map_area()
{
    return (get_active_map()->w)*(get_active_map()->h);
}
//dont know what to do with this one
MapItem* get_current(int x, int y)
{
    return get_here(x,y);
}

MapItem* get_north(int x, int y)
{

    unsigned int key = XY_KEY(x,y-1);
    return (MapItem*)getItem(get_active_map()->items,key);
}
MapItem* get_north_east(int x, int y)
{

    unsigned int key = XY_KEY(x+1,y-1);
    return (MapItem*)getItem(get_active_map()->items,key);
}
MapItem* get_north_west(int x, int y)
{

    unsigned int key = XY_KEY(x-1,y-1);
    return (MapItem*)getItem(get_active_map()->items,key);
}

MapItem* get_south(int x, int y)
{
    unsigned int key = XY_KEY(x,y+1);
    return (MapItem*)getItem(get_active_map()->items,key);
}
MapItem* get_south_east(int x, int y)
{
    unsigned int key = XY_KEY(x+1,y+1);
    return (MapItem*)getItem(get_active_map()->items,key);
}
MapItem* get_south_west(int x, int y)
{
    unsigned int key = XY_KEY(x-1,y+1);
    return (MapItem*)getItem(get_active_map()->items,key);
}
MapItem* get_east(int x, int y)
{
    unsigned int key = XY_KEY(x+1,y);
    return (MapItem*)getItem(get_active_map()->items,key);
}

MapItem* get_west(int x, int y)
{
    unsigned int key = XY_KEY(x-1,y);
    return (MapItem*)getItem(get_active_map()->items,key);
}

MapItem* get_here(int x, int y)
{
    // FIX THIS
    unsigned int key = XY_KEY(x,y);
    return (MapItem*)getItem(get_active_map()->items,key);
}

void map_erase(int x, int y)
{
    unsigned int key = XY_KEY(x,y);
    if(get_here(x,y)!=NULL)
        deleteItem(get_active_map()->items,key);
}

void add_wall(int x, int y, int dir, int len)
{
    for(int i = 0; i < len; i++) {
        MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
        w1->type = WALL;
        w1->draw = draw_wall;
        w1->walkable = false;
        w1->data = NULL;
        unsigned key = (dir == HORIZONTAL) ? XY_KEY(x+i, y) : XY_KEY(x, y+i);
        void* val = insertItem(get_active_map()->items, key, w1);
        if (val) free(val); // If something is already there, free it
    }
}

void add_plant(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = PLANT;
    w1->draw = draw_plant;
    w1->walkable = true;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}


void add_character(int x, int y, Character * player_data)
{
    MapItem* player  = (MapItem*)malloc(sizeof(MapItem));
    player->type = CHARACTERSPRITE;
    player->draw = player_data -> draw;
    player->walkable = true;
    player->data = player_data;
    player->data->x = x;
    player->data->y = y;
    player->data->px = x;
    player->data->py = y;
    player->data->Tx =(player->data->x )-(player->data->minrange)/2;
    player->data->Rx =(player->data->x )+(player->data->minrange)/2;
    player->data->Ty =(player->data->y)-(player->data->maxrange)/2;
    player->data->Ry =(player->data->y)+(player->data->maxrange)/2;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), player);
    if (val) free(val); // If something is already there, free it
}