///*******************///
///    Constants      ///
///*******************///

#define INITIAL_GAMEBOARD_LENGTH 5
#define INITIAL_GAMEBOARD_SIZE 25
#define INITIAL_TREASURES 5
#define INITIAL_SPACES 10
#define INITIAL_MONSTERS 8

///*******************///
///    Dependencies   ///
///*******************///

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <time.h>
#include <algorithm>
//#include <fstream>
#include <iomanip>
#include "AC_Functions.h"

using namespace std;

/// ************************** //
/// Gameboard Member Functions //
/// ************************** //

/// Gameboard Constructors //

Gameboard::Gameboard()
{
    num_treasures = INITIAL_TREASURES;
    num_spaces = INITIAL_SPACES;
    num_monsters = INITIAL_MONSTERS;
    board_layout = "|*";
    gameboard.resize(INITIAL_GAMEBOARD_SIZE);
    event_positions.resize(INITIAL_GAMEBOARD_SIZE);

    for(int count = 0;count < gameboard.size();count++)
    {
        gameboard[count] = board_layout;
    }

    ///gameboard[0][1] = '@';
    int ep_length = event_positions.size();
    event_positions[0] = INITIAL_GAMEBOARD_LENGTH;

    for(int count = 1;count < ep_length;count++)
    {
    	if(count < INITIAL_GAMEBOARD_SIZE - 14)
        {
            event_positions[count] = SPACE;
        }
        else if(count < INITIAL_GAMEBOARD_SIZE - 6)
        {
            event_positions[count] = MONSTER;
        }
        else if(count < INITIAL_GAMEBOARD_SIZE - 1)
        {
        	event_positions[count] = TREASURE;
        }
    }

    event_positions[ep_length-1] = EXIT;
}

Gameboard::Gameboard(int treasures, int spaces, int monsters, string layout, int gameboard_size)
{
    num_treasures = treasures;
    num_spaces = spaces;
    num_monsters = monsters;
    board_layout = layout;
    gameboard.resize(gameboard_size);
    // This would be used for a more dynamic gameboard and more levels.
    for(int count = 0;count < gameboard_size;count++)
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

vector<int> Gameboard::get_event_positions() const
{
    return event_positions;
}

void Gameboard::set_layout(string layout)
{
    board_layout = layout;
}

void Gameboard::set_event_positions(vector<int> positions)
{
    event_positions = positions;
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

/// *********************** //
/// Player Member Functions //
/// *********************** //

/// Player Constructors ///

Player::Player()
{
    set_attack(10 + rand_num(6));
    int ex_health = rand_num(5);
    set_current_health(10 + ex_health);
    set_total_health(10 + ex_health);
    set_defense(10 + rand_num(4));
    set_current_exp(0);
    set_total_exp(20);
    set_position(0);
}

/// Player Member Functions ///

string Player::get_name() const
{
    return name;
}

int Player::get_attack() const
{
    return attack;
}

int Player::get_defense() const
{
    return defense;
}

int Player::get_current_health() const
{
    return current_health;
}

int Player::get_total_health() const
{
    return total_health;
}

int Player::get_position() const
{
    return position;
}

int Player::get_current_exp() const
{
    return current_exp;
}

int Player::get_total_exp() const
{
    return total_exp;
}

void Player::set_name(string player_name)
{
    name = player_name;
}

void Player::set_attack(int player_attack)
{
    attack = player_attack;
}

void Player::set_defense(int player_defense)
{
    defense = player_defense;
}

void Player::set_current_health(int current_player_health)
{
    current_health = current_player_health;
}

void Player::set_total_health(int total_player_health)
{
    total_health = total_player_health;
}

void Player::set_current_exp(int current_player_exp)
{
    current_exp = current_player_exp;
}

void Player::set_total_exp(int total_player_exp)
{
    total_exp = total_player_exp;
}

void Player::set_position(int player_position)
{
    position = player_position;
}

/// ************************* //
/// Treasure Member Functions //
/// ************************* //

/// Treasure Constructors ///

Treasure::Treasure()
{
    total_health_raise = 0;
    health_raise = 0;
    attack_raise = 0;
    defense_raise = 0;
}

/// Treasure Member Functions ///

int Treasure::get_total_health_r()
{
    return(total_health_raise);
}

int Treasure::get_health_r()
{
    return(health_raise);
}

int Treasure::get_attack_r()
{
    return(attack_raise);
}

int Treasure::get_defense_r()
{
    return(defense_raise);
}

void Treasure::set_total_health_r(int raise)
{
    total_health_raise = raise;
}

void Treasure::set_health_r(int raise)
{
    health_raise = raise;
}

void Treasure::set_defense_r(int raise)
{
    defense_raise = raise;
}

void Treasure::set_attack_r(int raise)
{
    attack_raise = raise;
}

/// ************************ //
///   Function Declarations  //
/// ************************ //

/// void calc_board_perc(Gameboard& Board)
/// {
///    event_size = (Board.get_board).size() - 2;
///
/// }

void display_board(vector<string> vector_to_display,int player_position)
{
    int board_size = vector_to_display.size();
    vector<string> vec_board = vector_to_display;
    for(int count = 0;count < board_size;count++)
    {
        if(count == player_position)
        {
            vec_board[count][1] = '@';
        }
        cout << vec_board[count];
        if((count + 1) % INITIAL_GAMEBOARD_LENGTH == 0)
            cout << endl;
    }
}

void display_board(vector<int> vector_to_display)
{
    int board_size = vector_to_display.size();
    vector<int> vec_board = vector_to_display;
    for(int count = 0;count < board_size;count++)
    {
        cout << vec_board[count];
        if((count + 1) % INITIAL_GAMEBOARD_LENGTH == 0)
            cout << endl;
    }
}



int rand_num(int num)
{
    srand(time(NULL));
    return(rand() % num);
}

void initialize_vec(vector<int>& event_positions)
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
        else if(count < ep_length - 1)
        	event_positions[count] = TREASURE;
    }
}

void game_start(Gameboard& Board, Player& Adventurer)
{
    string player_name;
    /// Seed the random number generator for random_shuffle
    srand(time(0));
	cout << "...You find yourself surrounded by suffocating blackness, your breath quickly crystallizing in the icy air..." << endl
	     << "...Your memory is faint but you notice a glimmer of light in the distance and taking your sword, you set off..." << endl;
    cout << "Your name, brave adventurer? >> ";
    getline(cin,player_name);
    Adventurer.set_name(player_name);
    /// Initialize a integer vector that have the value of the event position vector, and will be sued to shuffle the event positions. The event positions vector
    /// will then be assigned the value of this temporary vector
    vector<int> positions = Board.get_event_positions();
	random_shuffle(positions.begin() + 1,positions.end() - 1);
	display_board(Board.get_board(),Adventurer.get_position());
	///display_board(positions);
	Board.set_event_positions(positions);
	display_stats(Adventurer);
}

void display_stats(Player& Adventurer)
{
    cout << Adventurer.get_name() << endl
         << "Health: " << setw(6) << Adventurer.get_current_health() << "/" << Adventurer.get_total_health() << endl
         << "Attack: " << setw(6) << Adventurer.get_attack() << endl
         << "Defense: " << setw(5) << Adventurer.get_defense() << endl
         << "Experience: " << Adventurer.get_current_exp() << "/" << Adventurer.get_total_exp();
}

void movement(Player& Adventurer)
{
    static int calls = 0;
    char player_move;
    cout << "\n>> ";
    if(calls > 0)
        cin.ignore();
    cin.get(player_move);
    /// Input validation for correct character.
    while(player_move != 'w' && player_move != 's' && player_move != 'a' && player_move != 'd')
    {
        cout << "\n>> ";
        cin.ignore();
        cin.get(player_move);
    }
    /// Input validation to make sure the player doesn't move off the gameboard.
    while(check_move(Adventurer.get_position(), player_move))
    {
        cout << "\n>> ";
        cin.ignore();
        cin.get(player_move);
    }
    if(player_move == 'w')
    {
        Adventurer.set_position(Adventurer.get_position()-5);
    }
    else if(player_move == 's')
    {
        Adventurer.set_position(Adventurer.get_position()+5);
    }
    else if(player_move == 'd')
    {
        Adventurer.set_position(Adventurer.get_position()+1);
    }
    else
    {
        Adventurer.set_position(Adventurer.get_position()-1);
    }
    /// Static variable for the if statement for the first cin.ignore().
    calls++;
}

bool check_move(int player_position, char player_move)
{
    return((player_position < 5 && player_move == 'w') || (player_position == 0 && player_move == 'a') ||
           (player_position > 19 && player_move == 's') || (player_position == 24 && player_move == 'd'));
}
