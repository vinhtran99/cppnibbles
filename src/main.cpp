// ConsoleApplication3.cpp : Defines the entry point for the console application.
// main game

#include "conx2.h"
#include "player.h"

int main() {
	hidcur();
	snake worm;
	// food (apple)
	COORD app;
	// apple count
	int appcnt = 0;
	// starting point of the snake: middle of the screen
	int midx = maxx / 2;
	int midy = maxy / 2;
	// to keep track the body of the snake (0: no snake; 1: snake occupied)
	int matrix[maxy][maxx];
	// initialized to 0s for zero obstacles. User can make a matrix herself to enjoy
	memset(matrix, 0, sizeof(matrix));
	init(&worm, midx, midy, matrix);
	// loop until the snake bites himself or something not eatable
	for ( ; ; ) {
		if (appcnt == 0) {
			do {
				app.X = rand() % maxx;
				app.Y = rand() % maxy;
			} while (matrix[app.Y][app.X] == 1);
			appcnt = 1;
			gotoxy(app.X, app.Y);
			printf("@");
		}
		if (worm.dir == 1 || worm.dir == 3) {
			Sleep(100);
		}
		else {
			Sleep(50);
		}
		// user control: using arrow keys: 1 is up, 2 is left, 3 is down, 4 is right
		if ( KeyPressed() ) {
			int key = getkey();
			switch (key) {
			case 75:
				if (worm.dir != 4)
					worm.dir = 2;
				break;
			case 77:
				if (worm.dir != 2)
					worm.dir = 4;
				break;
			case 72:
				if (worm.dir != 3)
					worm.dir = 1;
				break;
			case 80:
				if (worm.dir != 1)
					worm.dir = 3;
				break;
			}
		}
		COORD curxy, newxy;
		curxy = worm.head->pos;

		switch (worm.dir) {
		case 1:
			newxy.X = curxy.X;
			if (curxy.Y == 0) {
				// wrap around
				newxy.Y = maxy - 1;
			}
			else {
				newxy.Y = curxy.Y - 1;
			}
			break;
		case 2:
			if (curxy.X == 0) {
				newxy.X = maxx - 1;
			}
			else {
				newxy.X = curxy.X - 1;
			}
			newxy.Y = curxy.Y;
			break;
		case 3:
			newxy.X = curxy.X;
			if (curxy.Y == maxy - 1) {
				newxy.Y = 0;
			}
			else {
				newxy.Y = curxy.Y + 1;
			}
			break;
		case 4:
			if (curxy.X == maxx - 1) {
				newxy.X = 0;
			}
			else {
				newxy.X = curxy.X + 1;
			}
			newxy.Y = curxy.Y;
			break;
		}
		// the snake has eaten an apple?
		if (worm.head->pos.X == app.X && worm.head->pos.Y == app.Y) {
			appcnt = 0;
			worm.pts += 1;
		}
		// is he died yet?
		if ( die(matrix, newxy)  ) {
			break;
			system("cls");
		}
		else {
			move(matrix, &worm, newxy);
		}
	}
    return 0;
}