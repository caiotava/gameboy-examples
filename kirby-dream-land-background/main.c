#include<gb/gb.h>
#include<stdio.h>
#include "bgTiles.h"
#include "bgMaps.h"

void initBackground();

void main()
{
	disable_interrupts();
	DISPLAY_OFF;

	initBackground();

	SPRITES_8x8;
	SHOW_BKG;
	SHOW_SPRITES;
	DISPLAY_ON;
	enable_interrupts();
}

void initBackground()
{
	int count;

	set_bkg_data(0, 31, bgTiles);

	for(count = 0; count < 18; count++ ) {
		set_bkg_tiles(count, count, 1, 1, bgMapEmpty);
	}

	set_bkg_tiles(0, 0, 20, 14, bgMapSky);
	set_bkg_tiles(0, 14, 20, 4, bgMapGround);
}
