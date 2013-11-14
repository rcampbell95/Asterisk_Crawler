#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <time.h>
#include <algorithm>
#include <fstream>

using namespace std;

///********************//
/// Class Declarations //
///********************//

class Gameboard
{
private:
    int num_treasures;
    int num_spaces;
    int num_monsters;
    string board_layout;
    vector<string> gameboard;
public:
    Gameboard(int, int, int, string);
    Gameboard();
    int p_spaces() const;
    int n_monsters() const;
    int p_treasures() const;
    string get_layout() const;
    vector<string> get_board() const;
    void set_layout(string);
    void set_p_treasures(int);
    void set_p_spaces(int);
    void set_n_monsters(int);
    /// You can make the gameboard a constant for now and later implement the function correctly.
    ///void create_gameboard(Gameboard&);
};

/// ************************* //
///    Function Prototypes    //
/// ************************* //

int rand_num(int);

vector<int> initialize_vec(vector<int>);

void game_start(Gameboard&,vector<int> event_positions);

void display_board(Gameboard);

///void calc_board_perc(Gameboard&);

/// ************************* //
///        Enumerations       //
/// ************************* //

enum TreasureType {ATTACK, DEFENSE, HEALTH, POTION};

enum EventTypes {MONSTER, TREASURE, SPACE};


/// ************************** //
/// Gameboard Member Functions //
/// ************************** //

/// Gameboard Constructors //

Gameboard::Gameboard()
{
    num_treasures = 5;
    num_spaces = 10;
    num_monsters = 8;
    board_layout = "|*";
    gameboard.resize(25);
    for(int count = 0;count < gameboard.size();count++)
    {
        gameboard[count] = board_layout;
    }
    gameboard[0][1] = '@';
}

Gameboard::Gameboard(int treasures, int spaces, int monsters, string layout, int gameboard_size)
{
    num_treasures = treasures;
    num_spaces = spaces;
    num_monsters = monsters;
    board_layout = layout;
    gameboard.resize(game_board_size);
    // This would be used for a more dynamic gameboard and more levels. 
    for(int count = 0;count < gameboard.size();count++)
    {
        gameboard[count] = board_layout;
    }
    gameboard[0][1] = '@';
}

/// Gameboard Member Functions //

int Gameboard::p_spaces() const
{
    return num_spaces;
}

int Gameboard::n_monsters() const
{
    return num_monsters;
}

int Gameboard::p_treasures() const
{
    return num_treasures;
}

void Gameboard::set_p_treasures(int num)
{
    num_treasures = num;
}

void Gameboard::set_p_spaces(int num)
{
    num_spaces = num;
}

string Gameboard::get_layout() const
{
    return board_layout;
}

vector<string> Gameboard::get_board() const
{
    return gameboard;
}

void Gameboard::set_layout(string layout)
{
    board_layout = layout;
}
/// For now, I won't implement this function. I'll just have the gameboard have a set size.
/*
void Gameboard::create_gameboard(Gameboard &Board)
{
    int g_size = (Board.gameboard).size() * 5;
    string row = "";
    for(int count = 0;count < g_size;count++)
    {
    	row = row + Board.board_layout;
    	if(((count + 1) % 5) == 0)
    	{
    	    cout << row << endl;
    	    /// There's a problem with this line of code, or at least I think the
    	    /// problem lies in this line. The vector of string doesn't get initialized
    	    /// correctly.
    		(Board.gameboard).push_back(row);
    		row = "";
    	}
    }
}
*/
/// ************************ //
///   Function Declarations  //
/// ************************ //

/// void calc_board_perc(Gameboard& Board)
/// {
///    event_size = (Board.get_board).size() - 2;
///
/// }

void display_board(Gameboard board)
{
    int board_size = board.get_board().size();
    vector<string> vec_board = board.get_board();
    for(int count = 0;count < board_size;count++)
    {
        cout << vec_board[count];
        if((count + 1) % 5 == 0)
            cout << endl;
    }
}

int rand_num(int num)
{
    srand(time(0));
    return(rand() % num);
}

vector<int> initialize_vec(vector<int> event_positions)
{
    int ep_length = event_positions.size();
    /// Would be simple to make thse harcoded numbers percents instead of harcoding them. I'll try this just to hurry the
    /// alpha version then see how I can optimize it.
    for(int count = 1;count < ep_length;count++)
    {
    	if(count < 11)
        	event_positions[count] = SPACE;
        else if(count < 19)
        	event_positions[count] = MONSTER;
        else if(count < 24)
        	event_positions[count] = TREASURE;
    }
    return event_positions;
}

void game_start(Gameboard& Board, int event_positions)
{
	cout << "...You find yourself surrounded by suffocating blackness, your breath quickly crystallizing in the icy air..." << endl
	     << "...Your memory is faint but you notice a glimmer of light in the distance and taking your sword, you set off..." << endl;
	random_shuffle(event_positions.begin(),event_positions.end());
	display_board(Board);
}

