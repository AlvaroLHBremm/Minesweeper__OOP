#include <iostream>
#include <windows.h>
#include "Class.h"
using namespace std;

int main(void)
{
	 HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	 //clock_t Clock_Cycles = clock();
	 Minesweeper Game;
	 int Game_Time = time(0);
	 Game.Load_Matriz();

	 int Line,Colum;

	 Game.Plot_Matriz(Game_Time);
	 while(true)
	 {
		 cin >> Line >> Colum;
		 if(Line <= 0 or Line > SIZE_LINE or Colum <= 0 or Colum > SIZE_COLUM)
			 continue;
		 else
		 {
			 Line = Line - 1;
			 Colum = Colum - 1;
			 break;
		 }
	 }
	 Game.Load_Bombs( Line , Colum );
	 Game.Bomb_Check( Line , Colum );
	 Game.Plot_Matriz(Game_Time);

	 while(true)
	 {
		 cin >> Line >> Colum;

		 if(Line <= 0 or Line > SIZE_LINE or Colum <= 0 or Colum > SIZE_COLUM)
			 continue;

		 Line = Line - 1;
		 Colum = Colum - 1;

		 if(Game.Bomb_Check( Line , Colum ) == true)
		 {
			 Game.Plot_Bombs();
			 Game.Plot_Matriz( Game_Time);
			 SetConsoleTextAttribute(hConsole, 136);
			 cout << " ";
     		 SetConsoleTextAttribute(hConsole, 244);
			 cout << " !!! YOU LOST !!!        ";
			 SetConsoleTextAttribute(hConsole, 136);
			 cout << " ";
			 SetConsoleTextAttribute(hConsole, 15);
			 cin >> Line;
			 return 0;
		 }
		 if(Game.ClearMap_Check() == true)
		 {
			 Game.Plot_Matriz( Game_Time);
			 SetConsoleTextAttribute(hConsole, 136);
			 cout << " ";
			 SetConsoleTextAttribute(hConsole, 250);
			 cout << " !!! YOU WIN !!!         ";
			 SetConsoleTextAttribute(hConsole, 136);
			 cout << " ";
			 SetConsoleTextAttribute(hConsole, 115);
			 cin >> Line;
			 return 0;
		 }
		 Game.Plot_Matriz(Game_Time);
//		 Clock_Cycles = clock() - Clock_Cycles;
//		 cout << "Clock cycles: " << Clock_Cycles << endl;
	 }
	return 0;
}
