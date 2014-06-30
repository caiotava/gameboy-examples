#include<gb/gb.h>
#include<stdio.h>
#include<rand.h>

// bank 0
void verticalSyncHandler();

// bank 2
void updateGraphics();
void doGameplay();
void updateJoypad();
void updateBadGuy();
void collisionDetection();

// bank 3
void drawTitleScreen();
void loadGameTiles();

fixed seed;

void main()
{
	ENABLE_RAM_MBC1;

	seed.b.l = DIV_REG;

	SWITCH_ROM_MBC1(3);

	drawTitleScreen();

	seed.b.h = DIV_REG;

	initrand(seed.w);

	loadGameTiles();

	disable_interrupts();

	SWITCH_ROM_MBC1(0);

	add_VBL(verticalSyncHandler);

	SWITCH_ROM_MBC1(2);

	doGameplay();

	reset();

	puts("reset");
}

void verticalSyncHandler()
{
	SWITCH_ROM_MBC1(2);

	updateGraphics();
}
