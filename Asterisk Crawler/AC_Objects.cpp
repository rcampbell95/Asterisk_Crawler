#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <time.h>
#include <algorithm>

using namespace std;

//********************//
// Class Declarations //
//********************//

class Gameboard
{
private:
    int num_treasures;
    int num_spaces;
    int num_monsters;
    string board_layout;
    vector<string> gameboard(5);
public:
    Gameboard(int, int, int, string);
    Gameboard();
    int p_spaces() const;
    int n_monsters() const;
    int p_treasures() const;
    string get_layout() const;
    string get_board() const;
    void set_layout(string);
    void set_p_treasures(int);
    void set_p_spaces(int);
    void set_n_monsters(int);
    void create_gameboard(Gameboard&);
};

// ************************* //
//    Function Prototypes    //
// ************************* //

void game_start(Gameboard);

int rand_num(int);

vector<int> initialize_vec(vector<int>);

void game_start(Gameboard&);

void calc_board_perc(Gameboard&);

// ************************** //
// Gameboard Member Functions //
// ************************** //

// Gameboard Constructors //

Gameboard::Gameboard()
{
    num_treasures = 5;
    num_spaces = 10;
    num_monsters = 8;
    board_layout = "|*";
}

Gameboard::Gameboard(int treasures, int spaces, int monsters, string layout)
{
    num_treasures = treasures;
    num_spaces = spaces;
    num_monsters = monsters;
    board_layout = layout;
}

// Gameboard Member Functions //

int Gameboard::p_spaces() const
{
    return percent_spaces;
}

int Gameboard::n_monsters() const
{
    return num_monsters;
}

int Gameboard::p_treasures() const
{
    return percent_treasures;
}

void Gameboard::set_p_treasures(int num)
{
    percent_treasures = num;
}

void Gameboard::set_p_spaces(int num)
{
    percent_spaces = num;
}

string Gameboard::get_layout() const
{
    return board_layout;
}

string Gameboard::get_board() const
{
    return gameboard;
}

void Gameboard::set_layout(string layout)
{
    board_layout = layout;
}

void Gameboard::create_gameboard(Gameboard &Board)
{
    int g_size = (Board.gameboard).size();
    string row = "";
    for(int count = 0;count < g_size;count++)
    {
    	row += Board.board_layout;
    	if(((count + 1) % 5) == 0)
    	{
    		(Board.gameboard).push_back(row);
    	}
    }
}

// ************************ //
//   Function Declarations  //
// ************************ //

// void calc_board_perc(Gameboard& Board)
// {
//    event_size = (Board.get_board).size() - 2;
//    
// }

int rand_num(int num)
{
    srand(time(0));
    return(rand() % num);
}

vector<int> initialize_vec(vector<int> event_positions)
{
    int ep_length = event_positions.size();
    for(int count = 0;count < ep_length;count++)
    {
        event_positions[count] = count;
    }
    return event_positions;
}

void game_start(Gameboard& Board)
{
	cout << "...You find yourself surrounded by suffocating blackness, your breath quickly crystallizing in the icy air..." << endl
	     << "...Your memory is faint but you notice a glimmer of light in the distance and taking your sword, you set off..." << endl;
}

