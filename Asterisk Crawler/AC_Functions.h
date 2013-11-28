#ifndef AC_FUNCTIONS_H_INCLUDED
#define AC_FUNCTIONS_H_INCLUDED

///*******************///
///    Constants      ///
///*******************///

#define GAMEBOARD_LENGTH 5

///*******************///
///   Dependencies    ///
///*******************///

#include <string>
#include <vector>

using namespace std;

/// ************************* //
///    Class Declarations     //
/// ************************* //

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

class Treasure
{
private:
    int total_health_raise;
    int health_raise;
    int attack_raise;
    int defense_raise;
public:
    Treasure();
    void set_total_health_r(int);
    void set_health_r(int);
    void set_attack_r(int);
    void set_defense_r(int);
    int get_total_health_r();
    int get_health_r();
    int get_attack_r();
    int get_defense_r();
};

/// ************************* //
///    Function Prototypes    //
/// ************************* //

int rand_num(int);

void initialize_vec(vector<int>&);

void game_start(Gameboard&,Player&);

void display_board(vector<string>,int);

void display_board(vector<int>);

void display_stats(Player&);

void movement(Player&);

bool check_move(int,char);

///void calc_board_perc(Gameboard&);

/// ************************* //
///        Enumerations       //
/// ************************* //

enum TreasureType {ATTACK, DEFENSE, HEALTH, POTION};

enum EventTypes {SPACE, TREASURE, MONSTER,EXIT};


#endif // AC_FUNCTIONS_H_INCLUDED