#include "sobre_engine.h"

void swap_two_tiles(tiles* tile1, tiles* tile2)
{
	int temp_var;

	// swap tiles
	temp_var = tile1->rect.x;
	tile1->rect.x = tile2->rect.x;
	tile2->rect.x = temp_var;

	temp_var = tile1->rect.y;
	tile1->rect.y = tile2->rect.y;
	tile2->rect.y = temp_var;
}
