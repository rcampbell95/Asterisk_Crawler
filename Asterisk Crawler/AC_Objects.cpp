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
    int percent_treasures;
    int percent_spaces;
    int num_monsters;
    string board_layout;
    vector<string> gameboard;
public:
    Gameboard(int, int, string);
    Gameboard();
    int p_spaces() const;
    int n_monsters() const;
    int p_treasures() const;
    string get_layout() const;
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
    percent_treasures = 0;
    percent_spaces = 0;
    num_monsters = 0;
    board_layout = "|*";
}

Gameboard::Gameboard(int treasures, int spaces, string layout)
{
    percent_treasures = treasures;
    percent_spaces = spaces;
    board_layout = layout;
}

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

void Gameboard::set_layout(string layout)
{
    board_layout = layout;
}

void Gameboard::create_gameboard(Gameboard& Board)
{
    calc_board_perc(Board);
}

// ************************ //
//   Function Declarations  //
// ************************ //

void calc_board_perc(Gameboard& Board)
{
    Board.set_layout("david");
}

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
    Board.set_p_treasures(3);
    Board.set_p_spaces(2);
	cout << "...You find yourself surrounded by suffocating blackness, your breath quickly crystallizing in the icy air..." << endl
	     << "...Your memory is faint but you notice a glimmer of light in the distance and taking your sword, you set off..." << endl;
}

