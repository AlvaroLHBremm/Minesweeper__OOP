#ifndef CLASS_H_
#define CLASS_H_

using namespace std;
#include <time.h>
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <time.h>
#include <cmath>
#define SIZE_LINE 10
#define SIZE_COLUM 10
#define MINES 10 //(SIZE_COLUM + SIZE_LINE)*1.5

class Minesweeper
{
private:

	int Max_Bombs = 0;
	int ypos[10],xpos[10];
	int mines = 20;
	int total_tiles = (SIZE_LINE * SIZE_COLUM) - MINES;
	int tile_counter = 0;
	int mine_ypos[MINES], mine_xpos[MINES];

	char Matriz[SIZE_LINE][SIZE_COLUM];
	char Bomb_Matriz[SIZE_LINE][SIZE_COLUM];
	char alive[2] = {':','D'};
	char dead[2] = {'X','P'};
	char Mine = 'X';
	const char tile = '.';
	const char open_tile = ' ';

public:

	void Load_Matriz(void);
	void Load_Bombs( int Line , int Colum );
	void Plot_Bombs(void);
	void Plot_Matriz(int Game_Time);
	bool Bomb_Check( int X , int Y );
	bool ClearMap_Check(void);
};

#endif /* CLASS_H_ */
