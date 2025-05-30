#include "Class.h"

void Minesweeper::Load_Matriz(void)
{
    for(int line = 0; line < SIZE_LINE; line++)
    {
        for(int colum = 0; colum < SIZE_COLUM; colum++)
        {
            Matriz[line][colum] = tile;
        }
    }
    cout << "Field size :: Colum: " << SIZE_COLUM << endl;
    cout << "Field size :: Lines: " << SIZE_LINE << endl;
    cout << "Field size :: Bombs: " << MINES << endl;
    cout << "Field size :: Tiles: " << total_tiles << endl;
}
void Minesweeper::Load_Bombs( int Line , int Colum )
{
	for(int line = 0; line < SIZE_LINE; line++)
	{
		for(int colum = 0; colum < SIZE_COLUM; colum++)
		{
			Bomb_Matriz[line][colum] = tile;
		}
	}
	srand(time(0));
	for(int i = 0; i < MINES; i++)
	{
		mine_xpos[i] = rand() % SIZE_COLUM;
		mine_ypos[i] = rand() % SIZE_LINE;
		if(mine_ypos[i] == Line and mine_xpos[i] == Colum) //
		{
			while(true)
			{
				mine_xpos[i] = rand() % SIZE_COLUM;
				mine_ypos[i] = rand() % SIZE_LINE;
				if(mine_ypos[i] != Line or mine_xpos[i] != Colum)
				{
					Bomb_Matriz[mine_ypos[i]][mine_xpos[i]] = Mine;
					break;
				}

			}
		}
		if(Bomb_Matriz[mine_ypos[i]][mine_xpos[i]] == Mine)
		{
			while(true)
			{
				mine_xpos[i] = rand() % SIZE_COLUM;
				mine_ypos[i] = rand() % SIZE_LINE;
				if(Bomb_Matriz[mine_ypos[i]][mine_xpos[i]] != Mine)
				{
					Bomb_Matriz[mine_ypos[i]][mine_xpos[i]] = Mine;
					break;
				}
			}
		}
		Bomb_Matriz[mine_ypos[i]][mine_xpos[i]] = Mine;
	}
}
void Minesweeper::Plot_Bombs(void)
{
	for(int i = 0; i < MINES; i++)
	{
		Matriz[mine_ypos[i]][mine_xpos[i]] = Mine;
	}
}
void Minesweeper::Plot_Matriz(int Game_Time)
{
	Game_Time = time(0) - Game_Time;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 136);

    cout << "+=====";
    for(int i = 0; i < SIZE_COLUM * 2; i++)
    {
    	cout << '=';
    }
    cout << '+' << endl;

    for(int line = 0; line < SIZE_LINE; line++)
    {
    	SetConsoleTextAttribute(hConsole, 136);
    	if((line + 1) >= 10)
    	{
    		cout <<  "|";
    		SetConsoleTextAttribute(hConsole, 112);
    		cout << ' ' << line + 1;
    		SetConsoleTextAttribute(hConsole, 136);
    		cout << '|';
    	}
    	else
    	{
    		cout <<  "|";
    		SetConsoleTextAttribute(hConsole, 112);
    		cout << ' ' << line + 1 << ' ';
    		SetConsoleTextAttribute(hConsole, 136);
    		cout << '|';
    	}
        for(int colum = 0; colum < SIZE_COLUM; colum++)
        {
        	switch(Matriz[line][colum])
        	{
        	case 46: // '.'
        		SetConsoleTextAttribute(hConsole, 119);
        		cout << Matriz[line][colum] << open_tile;
        		break;
        	case 32:// ' '
        		SetConsoleTextAttribute(hConsole, 240);
        		cout << Matriz[line][colum] << open_tile;
        		break;
        	case 49: // '1'
        		SetConsoleTextAttribute(hConsole, 241);
        		cout << Matriz[line][colum] << open_tile;
        		break;
        	case 50: // '2'
        		SetConsoleTextAttribute(hConsole, 242);
        		cout << Matriz[line][colum] << open_tile;
        		break;
        	case 51: // '3'
        		SetConsoleTextAttribute(hConsole, 244);
        		cout << Matriz[line][colum] << open_tile;
        		break;
        	case 52: // '4'
        		SetConsoleTextAttribute(hConsole, 243);
        		cout << Matriz[line][colum] << open_tile;
        		break;
        	case 53: // '5'
        		SetConsoleTextAttribute(hConsole, 252);
        		cout << Matriz[line][colum] << open_tile;
        		break;
        	case 54: // '6'
        		SetConsoleTextAttribute(hConsole, 250);
        		cout << Matriz[line][colum] << open_tile;
        		break;
        	case 55: // '7'
        		SetConsoleTextAttribute(hConsole, 240);
        		cout << Matriz[line][colum] << open_tile;
        		break;
        	case 56: // '8'
        		SetConsoleTextAttribute(hConsole, 247);
        		cout << Matriz[line][colum] << open_tile;
        		break;
        	case 88: // 'X'
        		SetConsoleTextAttribute(hConsole, 116);
        		cout << Matriz[line][colum] << open_tile;
        		break;
        	}
        }
    	SetConsoleTextAttribute(hConsole, 136);
        cout << "| " << endl;
        SetConsoleTextAttribute(hConsole, 15);
    }
	SetConsoleTextAttribute(hConsole, 136);
    cout << "+=====";
    for(int i = 0; i < SIZE_COLUM * 2; i++)
    {
    	cout << '=';
    }
    cout << '+' << endl;

    SetConsoleTextAttribute(hConsole, 15);
    //cout << "Total tiles: " << total_tiles << " | Tile counter: "<< tile_counter << endl;
    //cout << "| Time:  " << Game_Time << "|>: " << endl;
	SetConsoleTextAttribute(hConsole, 15);
}
bool Minesweeper::Bomb_Check( int Line , int Colum )
{
	if(Line < 0 or Colum < 0 or Line > SIZE_LINE or Colum > SIZE_COLUM or Bomb_Matriz[Line][Colum] == open_tile) // Checa se a coordenada é valida. Provavelmente irrelevante em conjunto com os IF's abaixo.
		return false;

	if(Bomb_Matriz[Line][Colum] == Mine) //Call Bomb_Plot Method to end the game
	{
		alive[0] = dead[0];
		alive[1] = dead[1];
		return true;
	}
	else// Checa se há bombas ao redor do ponto clicado.
	{
		int bomb = 0;

		if(Colum + 1 < SIZE_COLUM and  Colum + 1 >= 0)
			if(Bomb_Matriz[Line][Colum + 1]     == Mine)
				++bomb;
		if(Colum - 1 < SIZE_COLUM and  Colum - 1 >= 0)
			if(Bomb_Matriz[Line][Colum - 1]     == Mine)
				++bomb;
		if(Line + 1 < SIZE_LINE and  Line + 1 >= 0)
			if(Bomb_Matriz[Line + 1][Colum]     == Mine)
				++bomb;
		if(Line - 1 < SIZE_LINE and  Line - 1 >= 0)
			if(Bomb_Matriz[Line - 1][Colum]     == Mine)
				++bomb;
		if((Line + 1 < SIZE_LINE and  Line + 1 >= 0) and (Colum + 1 < SIZE_COLUM and  Colum + 1 >= 0))
			if(Bomb_Matriz[Line + 1][Colum + 1] == Mine)
				++bomb;
		if((Line + 1 < SIZE_LINE and  Line + 1 >= 0) and (Colum - 1 < SIZE_COLUM and  Colum - 1 >= 0))
			if(Bomb_Matriz[Line + 1][Colum - 1] == Mine)
				++bomb;
		if((Line - 1 < SIZE_LINE and  Line - 1 >= 0) and (Colum + 1 < SIZE_COLUM and  Colum + 1 >= 0))
			if(Bomb_Matriz[Line - 1][Colum + 1] == Mine)
				++bomb;
		if((Line - 1 < SIZE_LINE and  Line - 1 >= 0) and (Colum - 1 < SIZE_COLUM and  Colum - 1 >= 0))
			if(Bomb_Matriz[Line - 1][Colum - 1] == Mine)
				++bomb;

		if(bomb > 0) // Se houver bombas ao redor, sobrescreve o ponto com o numero correspondente de bombas.
		{
			Matriz[Line][Colum] = '0' + bomb; // Soma a quantidade de bombas com o char '0' da tabela ASCII (46)
		}
		else // Abre o campo ao redor do ponto inicial. E para cada quadrado checado chama recursivamente a si mesmo caso a coordenada nao tenha sido checado.
		{
			if(Matriz[Line][Colum] == tile)
			{
				Matriz[Line][Colum] = open_tile;
			}
			if((Colum + 1 < SIZE_COLUM) and  (Matriz[Line][Colum + 1] == tile))
			{
				Matriz[Line][Colum + 1] = open_tile;
				Bomb_Check( Line , Colum + 1);
			}
			if((Line + 1 < SIZE_LINE) and (Matriz[Line + 1][Colum] == tile))
			{
				Matriz[Line + 1][Colum] = open_tile;
				Bomb_Check( Line + 1 , Colum);
			}
			if((Colum - 1 >= 0) and (Matriz[Line][Colum - 1] == tile))
			{
				Matriz[Line][Colum - 1] = open_tile;
				Bomb_Check( Line , Colum - 1);
			}
			if((Line - 1 >= 0) and (Matriz[Line - 1][Colum] == tile))
			{
				Matriz[Line - 1][Colum] = open_tile;
				Bomb_Check( Line - 1 , Colum);
			}
			if(((Line + 1 < SIZE_LINE) and (Colum + 1 < SIZE_COLUM)) and (Matriz[Line + 1][Colum + 1] == tile))
			{
				Matriz[Line + 1][Colum + 1] = open_tile;
				Bomb_Check( Line + 1 , Colum + 1);
			}
			if(((Line - 1 >= 0) and (Colum + 1 < SIZE_COLUM)) and (Matriz[Line - 1][Colum + 1] == tile))
			{
				Matriz[Line - 1][Colum + 1] = open_tile;
				Bomb_Check( Line - 1 , Colum + 1);
			}
			if(((Line + 1 < SIZE_LINE) and (Colum - 1 >= 0)) and (Matriz[Line + 1][Colum - 1] == tile))
			{
				Matriz[Line + 1][Colum - 1] = open_tile;
				Bomb_Check( Line + 1 , Colum - 1);
			}
			if(((Line - 1 >= 0) and (Colum - 1 >= 0)) and (Matriz[Line - 1][Colum - 1] == tile))
			{
				Matriz[Line - 1][Colum - 1] = open_tile;
				Bomb_Check( Line - 1 , Colum - 1);
			}
		}
	}
	return false;
}
bool Minesweeper::ClearMap_Check(void)
{
	tile_counter = 0;
    for(int line = 0; line < SIZE_LINE; line++)
    {
        for(int colum = 0; colum < SIZE_COLUM; colum++)
        {
        	if(Matriz[line][colum] != tile)
        		tile_counter += 1;

        }
    }
    //cout << "Total tiles: " << total_tiles << " | Tile counter: "<< tile_counter << endl;
	if((total_tiles - tile_counter) == 0 )
		return true;
	else
		return false;
}
