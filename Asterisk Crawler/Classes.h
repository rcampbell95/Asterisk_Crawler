#ifndef CLASSES_H
#define CLASSES_H

///*******************///
///    Constants      ///
///*******************///

#define GAMEBOARD_LENGTH 5

///*******************///
///   Dependencies    ///
///*******************///

#include <string>
#include <vector>
#include <utility>

using namespace std;

/// ************************* //
///        Enumerations       //
/// ************************* //

enum TreasureType {ATTACK, DEFENSE, HEALTH, POTION};

enum EventTypes {SPACE, TREASURE, MONSTER,EXIT};

enum Enemy {BAT, ZOMBIE, SKELETON, GOBLIN};

enum GameState {EXITGAME, RESTART, CONTINUE};

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
  // no longer necessary
  // vector<string> gameboard;
  // Could the type of this vector cause any problems? Someting to check into.
  vector<pair<int, string> > event_positions;
  // vector<int> event_positions;
  vector<pair<int, string> > cpy_event_positions;
public:
  Gameboard(int, int, int, string,int);
  Gameboard();
  int p_spaces() const {return num_spaces;}
  int n_monsters() const {return num_monsters;}
  int p_treasures() const {return num_treasures;}
  string get_layout() const;
  /// vector<pair<int, string>> get_board() const;
  ///  vector<string> get_board() const;
  vector<pair<int, string> > get_event_positions() const;
  // vector<int> get_event_positions() const;
  vector<int> get_cpy_event_positions() const;
  void set_layout(string);
  void set_p_treasures(int num) {num_treasures = num;}
  void set_p_spaces(int num) {num_spaces = num;}
  void set_n_monsters(int);
  void set_event_positions(vector<pair<int, string> >&); 
  ///void set_event_positions(vector<int>&);
  void set_cpy_event_positions(vector<pair<int, string> >); 
  ///void set_cpy_event_position(vector<int>&); 
  void remove_event_position(int);
  void new_level_gameboard();
  // You can make the gameboard a constant for now and later implement the function correctly.
  //void create_gameboard(Gameboard&);
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
  void set_total_health_r(int raise) {total_health_raise = raise;}
  void set_health_r(int raise)       {health_raise = raise;}
  void set_attack_r(int raise)       {attack_raise = raise;}
  void set_defense_r(int raise)      {defense_raise = raise;}
  int get_total_health_r() const {return total_health_raise;}
  int get_health_r() const       {return health_raise;}
  int get_attack_r() const       {return attack_raise;}
  int get_defense_r() const      {return defense_raise;}
};

class Player
{
private:
  string name;
  int attack;
  int defense;
  int speed;
  int current_health;
  int total_health;
  int position;
  int score;
  int current_exp;
  int total_exp;
  int level;
  int floor;
public:
  Player();
  string get_name() const        {return name;}
  int get_defense() const        {return defense;}
  int get_attack() const         {return attack;}
  int get_speed() const          {return speed;}
  int get_current_health() const {return current_health;}
  int get_total_health() const   {return total_health;}
  int get_position() const       {return position;}
  int get_current_exp() const    {return current_exp;}
  int get_total_exp() const      {return total_exp;}
  int get_level() const          {return level;}
  int get_floor() const          {return floor;}
  void set_name(string player_name)                  {name = player_name;}
  void set_current_health(int current_player_health) {current_health = current_player_health;}
  void set_total_health(int total_player_health)     {total_health = total_player_health;}
  void set_attack(int player_attack)                 {attack = player_attack;}
  void set_defense(int player_defense)               {defense = player_defense;}
  void set_speed(int player_speed)                   {speed = player_speed;}
  void set_position(int player_position)             {position = player_position;}
  void set_current_exp(int current_player_exp)       {current_exp = current_player_exp;}
  void set_total_exp(int total_player_exp)           {total_exp = total_player_exp;}
  void set_level(int new_level)                      {level = new_level;}
  void set_floor(int new_floor)                      {floor = new_floor;}
  void stat_raise(Treasure&,TreasureType);
};

class Monster
{
private:
  int attack;
  int defense;
  int speed;
  int current_health;
  int total_health;
  int exp_raise;
  int score_raise;
public:
  Monster();
  int get_attack() const         {return attack;}
  int get_defense() const        {return defense;}
  int get_speed() const          {return speed;}
  int get_current_health() const {return current_health;}
  int get_total_health() const   {return total_health;}
  int get_exp_raise() const      {return exp_raise;}
  int get_score_raise() const    {return score_raise;}
  void set_attack(int new_attack)                  {attack = new_attack;}
  void set_defense(int new_defense)                {defense = new_defense;}
  void set_speed(int new_speed)                    {speed = new_speed;}
  void set_current_health(int new_current_health)  {current_health = new_current_health;}
  void set_total_health(int new_total_health)      {total_health = new_total_health;}
  void set_exp_raise(int new_exp_raise)            {exp_raise = new_exp_raise;}
  void set_score_raise(int new_score_raise)        {score_raise = new_score_raise;}
};

/// ************************ //
///       Structures         //
///************************* //

struct HighScoreEntry
{
  string name;
  int level,
    floor,
    total_health,
    attack,
    defense,
    current_exp,
    total_exp;
  HighScoreEntry *next;
};

/// ************************* //
///    Function Prototypes    //
/// ************************* //

int rand_num(int);

/// edit maybe?

void initialize_vec(vector<int>&);

void game_start(Player&);

/// edit

void display_board(vector<pair<int, string> >, int);

// void display_board(vector<string>,int);

void display_board(vector<int>);

///

void display_stats(Player&);

void display_stats(Monster&);

void movement(Player&);

bool check_move(int,char);

TreasureType initialize_treasure(Treasure&);

Enemy initialize_monster(Monster&, int);

bool combat(Monster&, Player&,Enemy, int);

int damage_done(int, int);

void level_up(Player&);

HighScoreEntry* create_linked_list(ifstream&,HighScoreEntry*&);

HighScoreEntry* insert_node(HighScoreEntry * &head, HighScoreEntry*);

void tail_deletion(HighScoreEntry*&);

bool check_if_high_score(HighScoreEntry*);

void create_high_score_entry(HighScoreEntry * &head, Player&);

void create_high_score_entry(HighScoreEntry * &head, Player&, ifstream&);

void display_list(HighScoreEntry*);

void initialilze_newnode(Player&, HighScoreEntry*&);

GameState play_again(GameState);

void delete_linked_list(HighScoreEntry *&);

void reset_player(Player&);

void check_file(ifstream&);

void check_file(ofstream&);

///void calc_board_perc(Gameboard&);

#endif // CLASSES_H
