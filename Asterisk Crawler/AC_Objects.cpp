#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <time.h>
#include <algorithm>
///#include <fstream>
#include <iomanip>


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
    vector<int> event_positions;
public:
    Gameboard(int, int, int, string,int);
    Gameboard();
    int p_spaces() const;
    int n_monsters() const;
    int p_treasures() const;
    string get_layout() const;
    vector<string> get_board() const;
    vector<int> get_event_positions() const;
    void set_layout(string);
    void set_p_treasures(int);
    void set_p_spaces(int);
    void set_n_monsters(int);
    void set_event_positions(vector<int>);
    /// You can make the gameboard a constant for now and later implement the function correctly.
    ///void create_gameboard(Gameboard&);
};

class Player
{
		private:
		    string name;
            int attack;
            int defense;
            int current_health;
            int total_health;
            int position;
            int score;
            int current_exp;
            int total_exp;
        public:
            Player();
            string get_name() const;
            int get_defense() const;
            int get_attack() const;
            int get_current_health() const;
            int get_total_health() const;
            int get_position() const;
            int get_current_exp() const;
            int get_total_exp() const;
            void set_name(string);
            void set_current_health(int);
            void set_total_health(int);
            void set_attack(int);
            void set_defense(int);
            void set_position(int);
            void set_current_exp(int);
            void set_total_exp(int);
};

/// ************************* //
///    Function Prototypes    //
/// ************************* //

int rand_num(int);

void initialize_vec(vector<int>&);

void game_start(Gameboard&,Player&);

void display_board(vector<string>);

void display_board(vector<int>);

void display_stats(Player&);

int movement();

///void calc_board_perc(Gameboard&);

/// ************************* //
///        Enumerations       //
/// ************************* //

enum TreasureType {ATTACK, DEFENSE, HEALTH, POTION};

enum EventTypes {SPACE, TREASURE, MONSTER,EXIT};


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
    event_positions.resize(25);
    for(int count = 0;count < gameboard.size();count++)
    {
        gameboard[count] = board_layout;
    }
    gameboard[0][1] = '@';
    int ep_length = event_positions.size();
    event_positions[0] = 5;
    for(int count = 1;count < ep_length;count++)
    {
    	if(count < 11)
        	event_positions[count] = SPACE;
        else if(count < 19)
        	event_positions[count] = MONSTER;
        else if(count < 24)
        	event_positions[count] = TREASURE;
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
    set_attack(10 + rand_num(4));
    int ex_health = rand_num(5);
    set_current_health(10 + ex_health);
    set_total_health(10 + ex_health);
    set_defense(10 + rand_num(6));
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

/// ************************ //
///   Function Declarations  //
/// ************************ //

/// void calc_board_perc(Gameboard& Board)
/// {
///    event_size = (Board.get_board).size() - 2;
///
/// }

void display_board(vector<string> vector_to_display)
{
    int board_size = vector_to_display.size();
    vector<string> vec_board = vector_to_display;
    for(int count = 0;count < board_size;count++)
    {
        cout << vec_board[count];
        if((count + 1) % 5 == 0)
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
        if((count + 1) % 5 == 0)
            cout << endl;
    }
}


int rand_num(int num)
{
    srand(time(0));
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
    cin >> player_name;
    Adventurer.set_name(player_name);
    /// Initialize a integer vector that have the value of the event position vector, and will be sued to shuffle the event positions. The event positions vector
    /// will then be assigned the value of this temporary vector
    vector<int> positions = Board.get_event_positions();
	random_shuffle(positions.begin() + 1,positions.end() - 1);
	display_board(Board.get_board());
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
