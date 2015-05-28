#ifndef PROTO_H
#define PROTO_H

///*******************///
///    Dependencies   ///
///*******************///

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

///**********************///
/// Forward Declarations ///
///**********************///

class Player;

/// ************************* //
///        Enumerations       //
/// ************************* //

enum TreasureType {ATTACK, DEFENSE, HEALTH, POTION};

enum EventTypes {WALL, SPACE, TREASURE, MONSTER, EXIT};

enum Enemy {BAT, ZOMBIE, SKELETON, GOBLIN};

enum GameState {EXITGAME, RESTART, CONTINUE};

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

void display_board(Gameboard&, int);

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

#endif
