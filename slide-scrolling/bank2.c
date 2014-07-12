#include<gb/gb.h>
#include<rand.h>

const UBYTE badGuyAI[] = {
        32,  32,  33,  34,  35,  35,  36,  37,
        38,  38,  39,  40,  41,  41,  42,  43,
        44,  44,  45,  46,  46,  47,  48,  48,
        49,  50,  50,  51,  51,  52,  53,  53,
        54,  54,  55,  55,  56,  56,  57,  57,
        58,  58,  58,  59,  59,  60,  60,  60,
        61,  61,  61,  61,  62,  62,  62,  62,
        62,  63,  63,  63,  63,  63,  63,  63,
        63,  63,  63,  63,  63,  63,  63,  63,
        62,  62,  62,  62,  62,  61,  61,  61,
        61,  60,  60,  60,  59,  59,  59,  58,
        58,  57,  57,  56,  56,  55,  55,  54,
        54,  53,  53,  52,  52,  51,  50,  50,
        49,  49,  48,  47,  47,  46,  45,  44,
        44,  43,  42,  42,  41,  40,  39,  39,
        38,  37,  36,  36,  35,  34,  33,  33,
        32,  31,  30,  29,  29,  28,  27,  26,
        26,  25,  24,  23,  23,  22,  21,  20,
        20,  19,  18,  18,  17,  16,  16,  15,
        14,  14,  13,  12,  12,  11,  11,  10,
        9,  9,  8,  8,  7,  7,  6,  6,
        6,  5,  5,  4,  4,  4,  3,  3,
        3,  2,  2,  2,  1,  1,  1,  1,
        1,  1,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,
        1,  1,  1,  1,  1,  1,  2,  2,
        2,  3,  3,  3,  4,  4,  4,  5,
        5,  5,  6,  6,  7,  7,  8,  8,
        9,  9,  10,  11,  11,  12,  12,  13,
        14,  14,  15,  16,  16,  17,  18,  18,
        19,  20,  20,  21,  22,  23,  23,  24,
        25,  26,  26,  27,  28,  29,  29,  30,
};

UBYTE playing, joy;
UBYTE playerX, playerY;
UBYTE badGuyX, badGuyY, badGuyZ, badGuyOffset;
UBYTE playerShotX, playerShotY, playerShotZ;

void updateGraphics()
{
	disable_interrupts();

	scroll_bkg(1, 0);

	move_sprite(0, playerX, playerY);

	move_sprite(1, badGuyX, badGuyY);

	move_sprite(2, playerShotX, playerShotY);

	enable_interrupts();
}

void updateJoypad()
{
	joy = joypad();

	if (joy & J_LEFT) {
		if (playerX > 0) {
			playerX--;
		}
	}

	if (joy & J_RIGHT) {
		if (playerX < 152) {
			playerX++;
		}
	}

	if (joy & J_UP) {
		if (playerY > 0) {
			playerY--;
		}
	}

	if (joy & J_DOWN) {
		if (playerY <136) {
			playerY++;
		}
	}

	if (joy & J_A) {
		if (playerShotZ == 0) {
			playerShotZ = 1;
			playerShotX = playerX;
			playerShotY = playerY;
		}

		if (playerShotZ == 1) {
			playerShotX = playerShotX + 2;

			if (playerShotX > 240) {
				playerShotX = 250;
				playerShotY = 250;
				playerShotZ = 0;
			}
		}
	}
}

void updateBadGuy()
{
	badGuyX = badGuyX -1;

	if (badGuyX > 240) {
		badGuyOffset = rand();

		while (badGuyOffset > 134) {
			badGuyOffset = rand();
		}

		badGuyX = 239;
	}

	badGuyY = badGuyOffset + badGuyAI[badGuyZ];

	badGuyZ++;
}

void collisionDetection()
{
	if (playerShotY > badGuyY - 4) {
		if (playerShotY < badGuyY + 4) {
			if (playerShotX > badGuyX - 4) {
				if (playerShotX < badGuyX + 4) {
					playerShotZ = 0;
					playerShotX = 250;
					playerShotY = 250;
					badGuyX = 255;
				}
			}
		}
	}

	if (playerY > badGuyY - 4) {
		if (playerY < badGuyY + 4) {
			if (playerX > badGuyX - 4) {
				if (playerX < badGuyX + 4) {
					playing = 0;
				}
			}
		}
	}
}

void doGameplay()
{
	playing = 1;
	playerX = 10;
	playerY = 10;
	badGuyX = 230;
	badGuyY = 230;

	while( playing == 1 ) {
		updateJoypad();
		updateBadGuy();
		collisionDetection();
		delay(10);
		wait_vbl_done();
	}
}
