/* NCurses Tetris
 * by Nodev
 *
 * Probably not the only game with this exact name.
 *
 * This software is released under the WTFPL v2.
 *
 * Requires NCurses.
 * Compile in C11 mode.
 * Written with 4-width tabs.
 * Written and tested on Linux. nanosleep() is the only thing I know to not be portable.
 */

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

//Everything should adjust automatically if these are changed except
//minimum screen size check. Top 2 rows are hidden.
#define fieldWidth 10
#define fieldHeight 22

//Global variables.
int
	//Coordinates of top left corner of play area, not including border.
	fieldTLCornerY, fieldTLCornerX,
	//Position of active tetrimino's 4x4 box's top left corner.
	activeTetY, activeTetX;;

//4 coordinate pairs of each of the tetriminos blocks, relative to the top
//left corner of a 4x4 box.
//[0], [1], are the y and x coordinates of the 1st square, and so on.
//[8] is the color pair.
int
	activeTet[9],
	nextTet[9];

//Play area. Format is field[y][x] for consistency with NCurses.
//field[0][0] is at the top left, y and x increase down and right.
//Top 2 rows are hidden.
int field[fieldHeight][fieldWidth];

//Function prototypes.
void blankField();
unsigned time_seed();
void newNextTet(int);
void rotateTet();
bool collides(int (*tet)[], int);
int difficulty(int);

int main() {

	int
		control,
		maxRows, maxCols,
		linesCleared,
		moveCounter;		//Counts the number of frames since the last forced move
							//of the active tetrimino.
	bool
		gameOver;

	//Time per frame in nanoseconds.
	//60 fps.
	struct timespec frameDelay;
	frameDelay.tv_sec = 0;
	frameDelay.tv_nsec = 16667*1000;

	//Initialize random number generator.
	srand(time_seed());

	//NCurses initialization.
	initscr();				//Starts screen mode.
	cbreak();				//Sets input mode.
	noecho();				//Prevents echoing of input at cursor position.
	nodelay(stdscr, TRUE);	//Makes getch() a non-halting function.
	curs_set(0);			//Makes cursor invisible.

	//Tetrimino colors.
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_RED);
	init_pair(2, COLOR_BLACK, COLOR_GREEN);
	init_pair(3, COLOR_BLACK, COLOR_YELLOW);
	init_pair(4, COLOR_BLACK, COLOR_BLUE);
	init_pair(5, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(6, COLOR_BLACK, COLOR_CYAN);
	init_pair(7, COLOR_BLACK, COLOR_WHITE);

	//Finds out how large the terminal is.
	getmaxyx(stdscr, maxRows, maxCols);

	//Verify there is enough screen space.
	//This is the only code that uses stdio.h.
	//Adjust this if you change field size.
	if((maxRows < 25) | (maxCols < 35)) {
		endwin();
		printf("Minimum terminal size is 35x25.\n");
		return -1;
	}

	//Calculate top left corner of play area border.
	//All other positions are derived from these values, fieldWidth, fieldHeight.
	fieldTLCornerX = maxCols/2 - fieldWidth/2;
	fieldTLCornerY = maxRows/2 - (fieldHeight-2)/2;

	//Initialize static display elements.
	//move(int y, int x) moves the cursor to the given position.
	//printw(char string[]) prints the given string at current position.
	//mwprintw(int y, int x, char string[]) combines move() and printw().
	//Modifications to the screen stored as a buffer until refresh()
	//or getch() is called.

	//Title.
	mvprintw(fieldTLCornerY/2, maxCols/2 - 7, "NCurses Tetris");

	//Field border.
	for(int y=2; y<fieldHeight+2; y++) {
		if(y==2 | y==fieldHeight+1) {
			move(fieldTLCornerY-1+y, fieldTLCornerX-1);
			for(int x=0; x<fieldWidth+2; x++) {
				printw("#");
			}
		} else {
			move(fieldTLCornerY-1+y, fieldTLCornerX-1);
			printw("#");
			for(int x=0; x<fieldWidth; x++) {
				printw(" ");
			}
			printw("#");
		}
	}

	//Lines Cleared to the left, Next and controls to the right.
	mvprintw(fieldTLCornerY+2, fieldTLCornerX-10, "Lines");
	mvprintw(fieldTLCornerY+3, fieldTLCornerX-10, "Cleared:");
	mvprintw(fieldTLCornerY+2, fieldTLCornerX+fieldWidth+3, "Next:");
	mvprintw(fieldTLCornerY+8, fieldTLCornerX+fieldWidth+3, "A Left");
	mvprintw(fieldTLCornerY+9, fieldTLCornerX+fieldWidth+3, "D Right");
	mvprintw(fieldTLCornerY+10, fieldTLCornerX+fieldWidth+3, "S Down");
	mvprintw(fieldTLCornerY+11, fieldTLCornerX+fieldWidth+3, "W Rotate");
	mvprintw(fieldTLCornerY+12, fieldTLCornerX+fieldWidth+3, "SPACE Drop");
	mvprintw(fieldTLCornerY+13, fieldTLCornerX+fieldWidth+3, "N New Game");
	mvprintw(fieldTLCornerY+14, fieldTLCornerX+fieldWidth+3, "O Exit");

	refresh();

	//Outer game loop.
	while(TRUE) {

		//Outer loop getch() is at the end to prevent having to press 'n' twice when
		//starting a new game from within the inner loop.

		//New game.
		if(control == 'n' | control == 'N') {

			//Initialize new game.
			blankField();
			linesCleared = 0;
			gameOver = FALSE;
			moveCounter = 0;

			//Creates the first 2 tetriminos.
			newNextTet(rand()%7);
			memcpy(&activeTet, &nextTet, sizeof(activeTet));
			newNextTet(rand()%7);

			//The starting coordinates of the top left square of the active tetriminos 4x4
			//box. The box itself does not collide.
			activeTetY = 0;
			activeTetX = fieldWidth/2;

			//Inner game loop.
			while(TRUE){

				//Read
				control = getch();

				//Eval

				//Controls

				/*For more quickly testing difficulty speeds.
				if(control == 'e') {
					linesCleared++;
				}
				*/

				//Second parameter of collides() determines direction to check for collision.
				//1 left, 2 right, 3 down.
				//Left and right.
				if((control == 'a' | control == 'A') && !collides(&activeTet, 1)) {
					activeTetX--;
				} else if((control == 'd' | control == 'D') && !collides(&activeTet, 2)) {
					activeTetX++;
				//Down. Does not itself trigger a forced move.
				} else if(control == 's' | control == 'S') {
					if(!collides(&activeTet, 3)) {
						activeTetY++;
					}
				//Drop. Moves the active tetrimino down until it collides and triggers a forced move
				//on this frame by setting the moveCounter, thus causing the tetrimino to 'stick' immediately.
				} else if(control == ' ') {
					while(!collides(&activeTet, 3)) {
						activeTetY++;
					}
					moveCounter = 60;
				//Rotation.
				} else if(control == 'w' | control == 'W') {
					rotateTet();
				//Exit or New Game. Breaks to the outer loop.
				} else if(control == 'o' | control == 'O' | control == 'n' | control == 'N') {
					break;
				}

				/*Forced move.
				When the moveCounter reaches the number of frames per forced move, as determined
					by linesCleared, the moveCounter is reset to 0.
				If the active tetrimino collides downward, check if it is still at its starting
					position. If so, game over. Otherwise, change the values of field[][] at the
					active tetrimino's block's positions to the active tetrimino's color, copy
					nextTet to activeTet, move the active tetrimino back to the starting position,
					and create a new nextTet.
				If the active tetrimino does not collide downward, move it down by 1.
				*/
				moveCounter++;
				if(moveCounter >= 60 - difficulty(linesCleared)) {
					moveCounter = 0;
					if(collides(&activeTet, 3)) {
						if(activeTetY == 0) {
							gameOver = TRUE;
						} else {
							field[activeTetY+activeTet[0]][activeTetX+activeTet[1]] = activeTet[8];
							field[activeTetY+activeTet[2]][activeTetX+activeTet[3]] = activeTet[8];
							field[activeTetY+activeTet[4]][activeTetX+activeTet[5]] = activeTet[8];
							field[activeTetY+activeTet[6]][activeTetX+activeTet[7]] = activeTet[8];

							memcpy(&activeTet, &nextTet, sizeof(nextTet));
							activeTetY = 0;
							activeTetX = fieldWidth/2;
							newNextTet(rand()%7);
						}
					} else {
						activeTetY++;
					}
				}

				/*Check for filled lines and clear them.
				Scans the top visible row starting on the left. As soon as a non-empty block is found,
				moves to the next row. If it reaches the last column and finds it non-empty, then the
				row must be filled. The row above that is then copied to the current row, and so on
				upward to the top the field, which has the effect of removing the filled row.
				The checks then continue downward from that row, until the bottom of the field is reached.
				*/
				for(int y=2; y<fieldHeight; y++) {
					for(int x=0; x<fieldWidth; x++) {
						if(field[y][x] == 0) {
							break;
						} else if(x == fieldWidth-1) {
							linesCleared++;
							for(int row=y; row>0; row--) {
								for(int col=0; col<fieldWidth; col++) {
									field[row][col] = field[row-1][col];
								}
							}
						}
					}
				}

				//Print

				//Render the field.
				//Renders over the entire field every frame, so no clearing is needed for this
				//or for the active tetrimino.
				//Renders empty space as a white '.' on black background. Renders filled space
				//with an X with the fore and background colors for that space's value.
				for(int y=2; y<fieldHeight; y++) {
					for(int x=0; x<fieldWidth; x++) {
						if(field[y][x]==0) {
							mvprintw(fieldTLCornerY+y, fieldTLCornerX+x, ".");
						} else {
							attron(COLOR_PAIR(field[y][x]));
							mvprintw(fieldTLCornerY+y, fieldTLCornerX+x, "X");
							attroff(COLOR_PAIR(field[y][x]));
						}
					}
				}

				//Render the active tetrimino.
				//Doesn't render a square if it is in the 2 hidden rows. Position checks could
				//be replaced by just drawing hidden squares anyway and re-rendering the top of
				//the field border and the empty row above it.
				attron(COLOR_PAIR(activeTet[8]));
				if(activeTetY+activeTet[0] > 1)
					mvprintw(fieldTLCornerY+activeTetY+activeTet[0], fieldTLCornerX+activeTetX+activeTet[1], "X");
				if(activeTetY+activeTet[2] > 1)
					mvprintw(fieldTLCornerY+activeTetY+activeTet[2], fieldTLCornerX+activeTetX+activeTet[3], "X");
				if(activeTetY+activeTet[4] > 1)
					mvprintw(fieldTLCornerY+activeTetY+activeTet[4], fieldTLCornerX+activeTetX+activeTet[5], "X");
				if(activeTetY+activeTet[6] > 1)
					mvprintw(fieldTLCornerY+activeTetY+activeTet[6], fieldTLCornerX+activeTetX+activeTet[7], "X");
				attroff(COLOR_PAIR(activeTet[8]));

				//Erase and render the next tetrimino.
				//The next box is outside the field so it has to be erased.
				mvprintw(fieldTLCornerY+4, fieldTLCornerX+fieldWidth+3, "    ");
				mvprintw(fieldTLCornerY+5, fieldTLCornerX+fieldWidth+3, "    ");
				mvprintw(fieldTLCornerY+6, fieldTLCornerX+fieldWidth+3, "    ");
				mvprintw(fieldTLCornerY+7, fieldTLCornerX+fieldWidth+3, "    ");

				attron(COLOR_PAIR(nextTet[8]));
				mvprintw(fieldTLCornerY+4+nextTet[0], fieldTLCornerX+fieldWidth+3+nextTet[1], "X");
				mvprintw(fieldTLCornerY+4+nextTet[2], fieldTLCornerX+fieldWidth+3+nextTet[3], "X");
				mvprintw(fieldTLCornerY+4+nextTet[4], fieldTLCornerX+fieldWidth+3+nextTet[5], "X");
				mvprintw(fieldTLCornerY+4+nextTet[6], fieldTLCornerX+fieldWidth+3+nextTet[7], "X");
				attroff(COLOR_PAIR(nextTet[8]));

				//Erase and render linesCleared display. Will not completely erase if more than 99999
				//lines have been cleared, however, this is unlikely.
				mvprintw(fieldTLCornerY+4, fieldTLCornerX-10, "     ");
				mvprintw(fieldTLCornerY+4, fieldTLCornerX-10, "%i", linesCleared);

				//Prints game over and breaks to the outer loop. Because the outer loop contains no
				//rendering unless a new game is started, the displayed play area will remain as-is
				//until a new game is started.
				if (gameOver) {
					mvprintw(fieldTLCornerY + fieldHeight/2, fieldTLCornerX + fieldWidth/2 - 4, "GAMEOVER");
					refresh();
					break;
				}

				refresh();

				//This line comprises almost all execution time.
				nanosleep(&frameDelay, NULL);
			}

		}

		//If 'o' was pressed on the inner loop, control will still be 'o' now, so this will
		//break from the outer loop and exit the game. If 'n' was pressed, it is necessary to continue
		//or else control will be cleared by the outer loop getch() and the player will have to
		//press 'n' a second time.
		if(control == 'o' | control == 'O') {
			break;
		} else if(control == 'n' | control == 'N') {
			continue;
		}

		//Outer loop frame delay.
		nanosleep(&frameDelay, NULL);

		control = getch();

	}

	//Ends screen mode and exits.
	endwin();
	return 0;
}

//Hashes system time for the creation of a seed
//in a way that is allegedly portable.
unsigned time_seed() {
	time_t now = time(0);
	unsigned char *p = (unsigned char *)&now;
	unsigned seed = 0;

	for(size_t i=0; i<sizeof now; i++) {
		seed = seed*(UCHAR_MAX + 2U) + p[i];
	}
	return seed;
}

//Sets all field values to 0.
void blankField() {
	for(int y=0; y<fieldHeight; y++) {
		for(int x=0; x<fieldWidth; x++) {
			field[y][x] = 0;
		}
	}
}

//Sets the next tetrimino to the given shape.
//	0	1	2	3	4	5	6
//	I	O	T	J	L	S	Z
//Do not use zero as a color, as that represents an empty
//space in field[][].
void newNextTet(int shape) {
	switch(shape) {
		case 0:
			nextTet[0]=0;	nextTet[1]=1;
			nextTet[2]=1;	nextTet[3]=1;
			nextTet[4]=2;	nextTet[5]=1;
			nextTet[6]=3;	nextTet[7]=1;
			nextTet[8]=1;
			break;
		case 1:
			nextTet[0]=1;	nextTet[1]=1;
			nextTet[2]=1;	nextTet[3]=2;
			nextTet[4]=2;	nextTet[5]=1;
			nextTet[6]=2;	nextTet[7]=2;
			nextTet[8]=2;
			break;
		case 2:
			nextTet[0]=1;	nextTet[1]=0;
			nextTet[2]=1;	nextTet[3]=1;
			nextTet[4]=1;	nextTet[5]=2;
			nextTet[6]=2;	nextTet[7]=1;
			nextTet[8]=3;
			break;
		case 3:
			nextTet[0]=0;	nextTet[1]=2;
			nextTet[2]=1;	nextTet[3]=2;
			nextTet[4]=2;	nextTet[5]=2;
			nextTet[6]=2;	nextTet[7]=1;
			nextTet[8]=4;
			break;
		case 4:
			nextTet[0]=0;	nextTet[1]=1;
			nextTet[2]=1;	nextTet[3]=1;
			nextTet[4]=2;	nextTet[5]=1;
			nextTet[6]=2;	nextTet[7]=2;
			nextTet[8]=5;
			break;
		case 5:
			nextTet[0]=2;	nextTet[1]=1;
			nextTet[2]=2;	nextTet[3]=2;
			nextTet[4]=1;	nextTet[5]=2;
			nextTet[6]=1;	nextTet[7]=3;
			nextTet[8]=6;
			break;
		case 6:
			nextTet[0]=1;	nextTet[1]=0;
			nextTet[2]=1;	nextTet[3]=1;
			nextTet[4]=2;	nextTet[5]=1;
			nextTet[6]=2;	nextTet[7]=2;
			nextTet[8]=7;
			break;
	}
}

//Tests for collision and rotates the active tetrimino clockwise.
void rotateTet() {
	//This array will hold the provisional position of the rotated tetrimino.
	int tempTet[9];

	/* Copies activeTet[] to tempTet[] via a tau/4 matrix transform. Because
	 * the top left	is the squares' 0, 0, they are also translated to the right
	 * by 4 to return them back to the square. However, because the same 0 column
	 * is both the originals left column and the rotated tetrimino's right column,
	 * it actually needs to be translated by 3.
	 */
	tempTet[0] = activeTet[1];
	tempTet[1] = -activeTet[0] + 3;
	tempTet[2] = activeTet[3];
	tempTet[3] = -activeTet[2] + 3;
	tempTet[4] = activeTet[5];
	tempTet[5] = -activeTet[4] + 3;
	tempTet[6] = activeTet[7];
	tempTet[7] = -activeTet[6] + 3;

	//The color does not need to be rotated.
	tempTet[8] = activeTet[8];

	/* If the provisional positions would collide, the function ends and tempTet is
	 * discarded. Otherwise, tempTet is copied to activeTet. This function makes no
	 * effort whatsoever to try and shift or wiggle tempTet around to see if there's
	 * a nearby position where it would fit, so attempting to rotate next to pieces or
	 * field edges will often simply fail.
	*/
	if(!collides(&tempTet, 0)) {
		memcpy(&activeTet, &tempTet, sizeof(activeTet));
	}
}

//Collision check for the given tetrimino in the given direction.
//1 left, 2, right, 3 down. 0 checks for collision without movement.
bool collides(int (*tet)[], int dir) {
	//In place collision. Used for tempTet collision checks during rotation.
	if(dir==0) {
		if(
			activeTetX + (*tet)[1] < 0 |			//Left field edge.
			activeTetX + (*tet)[3] < 0 |
			activeTetX + (*tet)[5] < 0 |
			activeTetX + (*tet)[7] < 0
		) {
			return true;
		} else if(
			activeTetX + (*tet)[1] > fieldWidth-1 |	//Right field edge.
			activeTetX + (*tet)[3] > fieldWidth-1 |
			activeTetX + (*tet)[5] > fieldWidth-1 |
			activeTetX + (*tet)[7] > fieldWidth-1
		) {
			return true;
		} else if(
			activeTetY+(*tet)[0] > fieldHeight-1 |	//Bottom field edge.
			activeTetY+(*tet)[2] > fieldHeight-1 |
			activeTetY+(*tet)[4] > fieldHeight-1 |
			activeTetY+(*tet)[6] > fieldHeight-1
		) {
			return true;
		} else if(									//Filled squares.
			field[activeTetY+(*tet)[0]][activeTetX + (*tet)[1]] != 0 |
			field[activeTetY+(*tet)[2]][activeTetX + (*tet)[3]] != 0 |
			field[activeTetY+(*tet)[4]][activeTetX + (*tet)[5]] != 0 |
			field[activeTetY+(*tet)[6]][activeTetX + (*tet)[7]] != 0
		) {
			return true;
		} else {
			return false;
		}
	//Left.
	} else if(dir==1) {
		if(
			activeTetX + (*tet)[1] == 0 |	//Left field edge.
			activeTetX + (*tet)[3] == 0 |
			activeTetX + (*tet)[5] == 0 |
			activeTetX + (*tet)[7] == 0
		) {
			return true;
		} else if(							//Filled squares.
			field[activeTetY+(*tet)[0]][activeTetX + (*tet)[1]-1] != 0 |
			field[activeTetY+(*tet)[2]][activeTetX + (*tet)[3]-1] != 0 |
			field[activeTetY+(*tet)[4]][activeTetX + (*tet)[5]-1] != 0 |
			field[activeTetY+(*tet)[6]][activeTetX + (*tet)[7]-1] != 0
		) {
			return true;
		} else {
			return false;
		}
	//Right.
	} else if(dir==2) {
		if(
			activeTetX + (*tet)[1] == fieldWidth-1 |	//Right field edge.
			activeTetX + (*tet)[3] == fieldWidth-1 |
			activeTetX + (*tet)[5] == fieldWidth-1 |
			activeTetX + (*tet)[7] == fieldWidth-1
		) {
			return true;
		} else if(										//Filled squares.
			field[activeTetY+(*tet)[0]][activeTetX + (*tet)[1]+1] != 0 |
			field[activeTetY+(*tet)[2]][activeTetX + (*tet)[3]+1] != 0 |
			field[activeTetY+(*tet)[4]][activeTetX + (*tet)[5]+1] != 0 |
			field[activeTetY+(*tet)[6]][activeTetX + (*tet)[7]+1] != 0
		) {
			return true;
		} else {
			return false;
		}
	//Down.
	} else {
		if(
			activeTetY+(*tet)[0] == fieldHeight-1 |		//Bottom edge.
			activeTetY+(*tet)[2] == fieldHeight-1 |
			activeTetY+(*tet)[4] == fieldHeight-1 |
			activeTetY+(*tet)[6] == fieldHeight-1
		) {
			return true;
		} else if(										//Filled squares.
			field[activeTetY+(*tet)[0]+1][activeTetX + (*tet)[1]] != 0 |
			field[activeTetY+(*tet)[2]+1][activeTetX + (*tet)[3]] != 0 |
			field[activeTetY+(*tet)[4]+1][activeTetX + (*tet)[5]] != 0 |
			field[activeTetY+(*tet)[6]+1][activeTetX + (*tet)[7]] != 0
		) {
			return true;
		} else {
			return false;
		}
	}
}

//Determines the rate at which the forced move threshold decreases
//based on clearedLines. Increases tetrimino speed by about 33%
//for each 4 lines cleared, capped at about 4x original speed.
int difficulty(int lines) {
	if(lines < 4)
		return 0;
	else if(lines < 8)
		return 15;
	else if(lines <12)
		return 27;
	else if(lines <16)
		return 35;
	else if(lines <20)
		return 41;
	else
		return 46;
}