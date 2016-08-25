//MIT License
//
//Copyright (c) 2016 Roberto Campbell
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

///*******************///
///    Constants      ///
///*******************///

#define INITIAL_GAMEBOARD_LENGTH 5
#define INITIAL_GAMEBOARD_SIZE 25
#define INITIAL_TREASURES 5
#define INITIAL_SPACES 10
#define INITIAL_MONSTERS 8
#define INITIAL_TOTAL_EXP 10
#define PLAYER_BASE_STAT 10
#define PLAYER_BASE_SPEED 5
#define BASE_BUFF_RAISE 1
#define BASE_HEALTH_RAISE 5

///*******************///
///    Dependencies   ///
///*******************///

#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <cassert>

#include "unit.h"
#include "item.h"
#include "monster.h"
#include "proto.h"
#include "player.h"

using namespace std;

/// ************************ //
///   Function Declarations  //
/// ************************ //

void display_board(vector<int> current_floor, int width, int player_position)
{
  int floor_size = current_floor.size();
  /// There are three for loops to display three chunks of the
  /// current floor vector. This is to eliminate constant checking for minimap purposes
  /// but it does create code repitition.
  for(int i = 0;i < player_position - width;i++)
  {
    if(current_floor[i] == WALL)
    {
      cout << '#';
    }
    else
    {
      cout << ' ';
    }
    if((i + 1) % width == 0)
    {
      cout << endl;
    }
  }
  //---------//
  // Minimap //
  //---------//

  for(int j = player_position - width;j <= player_position + width;j++)
  {
    if(j == player_position)
    {
      cout << '@';
      continue;
    }
    if(j == player_position - width || j == player_position - 1 || j == player_position + 1 || j == player_position + width)
    {
      if(current_floor[j] == MONSTER)
      {
        cout << '*';
      }
      else if(current_floor[j] == TREASURE)
      {
        cout << '?';
      }
      else if(current_floor[j] == EXIT)
      {
        cout << '!';
      }
      else if(current_floor[j] == WALL)
      {
        cout << "#";
      }
      else cout << ' ';
      continue;
    }

    if(current_floor[j] == WALL)
    {
      cout << '#';
    }
    else
    {
      cout << ' ';
    }

    if((j + 1) % width == 0)
    {
      cout << endl;
    }
  }

  for(int k = player_position + width + 1;k < floor_size;k++)
  {
    if(current_floor[k] == WALL)
    {
      cout << '#';
    }
    else
    {
      cout << ' ';
    }
    if((k + 1) % width == 0)
    {
      cout << endl;
    }
  }
}

/*

void display_board(vector<string> vector_to_display,int player_position)
{
  int board_size = vector_to_display.size();
  vector<string> vec_board = vector_to_display;
  for(int count = 0; count < board_size;count++)
  {
    if(count == player_position)
    {
      vec_board[count][1] = '@';
    }
    cout << vec_board[count];
    if((count + 1) % INITIAL_GAMEBOARD_LENGTH == 0)
    {
      cout << '|';
      cout << endl;
    }
  }
}

*/

///

int rand_num(int num)
{
  srand(time(NULL));
  return(rand() % num);
}

/// I don't use this function, instead I execute this code in th gameboard constructor.
void initialize_vec(vector<int>& event_positions)
{
  int ep_length = event_positions.size();
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

void game_start(Player& Adventurer)
{
  string player_name;
  // Seed the random number generator for random_shuffle
  srand(time(0));
	cout << "...You find yourself surrounded by suffocating blackness, your breath quickly crystallizing in the icy air..." << endl
	   << "...Your memory is faint but you notice a glimmer of light in the distance and taking your sword, you set off..." << endl;
  cout << "Your name, brave adventurer? >> ";
  getline(cin,player_name);
  Adventurer.set_name(player_name);
}

void display_hp_bar(int current_health, int total_health)
{
  for(int count = 0;count < total_health;count++)
  {
    if(count < current_health)
    {
      cout << '*';
    }
    else
    {
      cout << '~';
    }
  }
}

void display_stats(Player& Adventurer)
{
  int current_health = Adventurer.get_current_health();
  int total_health = Adventurer.get_total_health();
  cout << Adventurer.get_name() << endl
    << "Floor: " << setw(7) << Adventurer.get_floor() << endl
    << "Level: " << setw(7) << Adventurer.get_level() << endl
    << "Health: " << setw(6) << current_health << "/" << total_health;
    cout << "   ";
    display_hp_bar(current_health, total_health);
    cout << endl;

    cout << "Attack: " << setw(6) << Adventurer.get_attack() << endl
    << "Defense: " << setw(5) << Adventurer.get_defense() << endl
    << "Speed: " << setw(7) << Adventurer.get_speed() << endl
    << "Experience: " << Adventurer.get_current_exp() << "/" << Adventurer.get_total_exp();
}

void display_stats(Monster& Mob)
{
  /// Add another message for all these,
  /// In other words, fix up the
  /// presentation of the combat
  cout << Mob.get_name();
  cout << endl;
  cout << "Health: " << setw(6) << Mob.get_current_health() << "/" << Mob.get_total_health();
  cout << "   ";
  display_hp_bar(Mob.get_current_health(), Mob.get_total_health());
  cout << endl;
  cout << "Attack: " << setw(6) << Mob.get_attack() << endl
    << "Defense: " << setw(5) << Mob.get_defense() << endl
    << "Speed: " << setw(7) << Mob.get_speed() << endl;
}

int find_position(Player& Adventurer, vector<int> event_positions)
{
  for(int i = 0; i < event_positions.size();i++)
  {
    if(event_positions[i] == SPACE)
    {
      return(i);
    }
  }
}

void movement(Player& Adventurer,int width, vector<int> event_positions)
{
  char player_move;
  cout << "\n>> ";
  cin.get(player_move);
  /// Input validation for correct character.
  while((player_move != 'w' && player_move != 's' && player_move != 'a' && player_move != 'd') || check_move(Adventurer.get_position(), width, player_move, event_positions))
  {
    cout << "\n>> ";
    cin.get(player_move);
  }
  if(player_move == 'w')
  {
    Adventurer.set_position(Adventurer.get_position()-width);
  }
  else if(player_move == 's')
  {
    Adventurer.set_position(Adventurer.get_position()+width);
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
  cin.ignore();
}

bool check_move(int player_position, int width, char player_move, vector<int>& event_positions)
{
  bool up_collide = event_positions[player_position - width] == WALL && player_move == 'w';
  if(up_collide) cout << "up_collide is true";
  bool left_collide = event_positions[player_position - 1] == WALL && player_move == 'a';
  if(left_collide) cout << "left_collide is true";
  bool down_collide = event_positions[player_position + width] == WALL && player_move == 's';
  if(down_collide) cout << "down_collide is true";
  bool right_collide = event_positions[player_position + 1] == WALL && player_move == 'd';
  if(right_collide) cout << "right_collide is true";
  return(up_collide || left_collide || down_collide || right_collide);
}

TreasureType initialize_treasure(Treasure& Buff)
{
  TreasureType buff_type = static_cast<TreasureType>(rand_num(4));

  if(buff_type == ATTACK)
  {
    /// Use a define statement for these constants. Call it base stat raise!
    Buff.set_attack_r(BASE_BUFF_RAISE + rand_num(2));
    return ATTACK;
  }
  else if(buff_type == DEFENSE)
  {
    Buff.set_defense_r(BASE_BUFF_RAISE+rand_num(2));
    return DEFENSE;
  }
  else if(buff_type == HEALTH)
  {
    Buff.set_total_health_r(BASE_BUFF_RAISE+rand_num(2));
    return HEALTH;
  }
  else
  {
    Buff.set_health_r(BASE_HEALTH_RAISE+rand_num(5));
    return POTION;
  }
}

Enemy initialize_monster(Monster& Mob, int floor)
{
  Enemy enemy_type = static_cast<Enemy>(rand_num(3));
  int enemy_base_defense,
    enemy_base_attack,
    enemy_base_health,
    enemy_base_exp,
    enemy_base_speed;
  std::string enemy_name;

  if(enemy_type == BAT)
  {
    const int BAT_BASE_DEFENSE = 3,
          BAT_BASE_ATTACK = 3,
          BAT_BASE_HEALTH = 5,
          BAT_BASE_EXP = 2,
          BAT_BASE_SPEED = 6;
    enemy_base_attack = BAT_BASE_ATTACK;
    enemy_base_defense = BAT_BASE_DEFENSE;
    enemy_base_health = BAT_BASE_HEALTH;
    enemy_base_exp = BAT_BASE_EXP;
    enemy_base_speed = BAT_BASE_SPEED;
    enemy_name = "Dildo Bat";
  }
  else if(enemy_type == GOBLIN)
  {
    const int GOBLIN_BASE_DEFENSE = 3,
          GOBLIN_BASE_ATTACK = 5,
          GOBLIN_BASE_HEALTH = 6,
          GOBLIN_BASE_EXP = 4,
          GOBLIN_BASE_SPEED = 4;
    enemy_base_attack = GOBLIN_BASE_ATTACK;
    enemy_base_defense = GOBLIN_BASE_DEFENSE;
    enemy_base_health = GOBLIN_BASE_HEALTH;
    enemy_base_exp = GOBLIN_BASE_EXP;
    enemy_base_speed = GOBLIN_BASE_SPEED;
    enemy_name = "Goblin";
  }
  else if(enemy_type == SKELETON)
  {
    const int SKELETON_BASE_DEFENSE = 5,
          SKELETON_BASE_ATTACK = 3,
          SKELETON_BASE_HEALTH = 5,
          SKELETON_BASE_EXP = 3,
          SKELETON_BASE_SPEED = 3;
    enemy_base_attack = SKELETON_BASE_ATTACK;
    enemy_base_defense = SKELETON_BASE_DEFENSE;
    enemy_base_health = SKELETON_BASE_HEALTH;
    enemy_base_exp = SKELETON_BASE_EXP;
    enemy_base_speed = SKELETON_BASE_SPEED;
    enemy_name = "Skeleton";
  }
  else
  {
    const int ZOMBIE_BASE_DEFENSE = 6,
          ZOMBIE_BASE_ATTACK = 4,
          ZOMBIE_BASE_HEALTH = 7,
          ZOMBIE_BASE_EXP = 4,
          ZOMBIE_BASE_SPEED = 2;
    enemy_base_attack = ZOMBIE_BASE_ATTACK;
    enemy_base_defense = ZOMBIE_BASE_DEFENSE;
    enemy_base_health = ZOMBIE_BASE_HEALTH;
    enemy_base_exp = ZOMBIE_BASE_EXP;
    enemy_base_speed = ZOMBIE_BASE_SPEED;
    enemy_name = "Zombie";
  }
  Mob.set_attack(enemy_base_attack+ rand_num(floor));
  Mob.set_defense(enemy_base_defense + rand_num(floor));
  Mob.set_speed(enemy_base_speed);
  int ex_health = rand_num(floor);
  Mob.set_current_health(enemy_base_health + ex_health);
  Mob.set_total_health(enemy_base_health + ex_health);
  Mob.set_exp_raise(enemy_base_exp + floor/3);
  Mob.set_name(enemy_name);
  cout << "A " << enemy_name << " appeared from the darkness!" << endl;
  return enemy_type;
}

/// This returns a bool because either the player
/// dies or the enemy does
bool combat(Monster& Mob, Player& Adventurer,Enemy enemy_type, int floor)
{
  int mob_damage, player_damage;
  string battle_message;
  if(Adventurer.get_current_health() <= 0)
  {
    cout << "You have been slain..." << '\n';
    return false;
  }
  else if(Mob.get_current_health() <= 0)
  {
    cout << "The monster has been slain!" << '\n';
    Adventurer.set_current_exp(Adventurer.get_current_exp() + Mob.get_exp_raise());
    return true;
  }
  else
  {
    cout << "----------" << '\n';
    display_stats(Mob);
    cout << "----------" << '\n';
    display_stats(Adventurer);
    cout << '\n' << "----------" << '\n';
    cin.get();

    player_damage = damage_done(Mob.get_attack(), Adventurer.get_defense());
    mob_damage = damage_done(Adventurer.get_attack(), Mob.get_defense());

    if((Adventurer.get_speed() <= Mob.get_speed()) || (Mob.get_current_health() - mob_damage) > 0)
    {
      cout << "The " << Mob.get_name() << " did " << player_damage << " damage!" << endl;
      Adventurer.set_current_health(Adventurer.get_current_health() - player_damage);
    }

    if((Mob.get_speed() <= Adventurer.get_speed()) || (Adventurer.get_current_health() > 0))
    {
      cout << "The " << Mob.get_name() << " sustained " << mob_damage << " damage!" << endl;
      Mob.set_current_health(Mob.get_current_health() - mob_damage);
    }
    cin.get();

    return combat(Mob,Adventurer,enemy_type,floor);
  }
}

int damage_done(int attack, int defense)
{
  return(((2 * attack)/defense + 1) + rand_num(2));
}

void level_up(Player& Adventurer)
{
  int prev_experience = Adventurer.get_total_exp();
  Adventurer.set_level(Adventurer.get_level() + 1);
  Adventurer.set_total_exp(Adventurer.get_total_exp() + Adventurer.get_total_exp() / 3);
  Adventurer.set_current_exp(Adventurer.get_current_exp() - prev_experience);
  Adventurer.set_current_health(Adventurer.get_current_health() + (Adventurer.get_total_health() - Adventurer.get_current_health())/2);
  Adventurer.set_attack(Adventurer.get_attack() + Adventurer.get_attack()/10);
  Adventurer.set_defense(Adventurer.get_defense() + Adventurer.get_defense()/10);

  cout << "**---------**" << endl;
  cout << "* Level up! *" << '\n';
  cout << "**---------**" << endl;
}

void check_file(ofstream &file_to_check)
{
  if(file_to_check.fail())
  {
  cout << "Error opening file";
  }
}

void check_file(ifstream &file_to_check)
{
  if(file_to_check.fail())
  {
  cout << "Error opening file";
  }
}


HighScoreEntry * create_linked_list(ifstream &input_file,HighScoreEntry * &head)
{
  string whitespace;
  HighScoreEntry * currentnode = NULL;
  if(input_file.fail())
  {
    cout << "\nError opening file!";
    return head = NULL;
  }
  if(head == NULL)
  {
    getline(input_file, whitespace);
  }
  if(!input_file.eof())
  {
    HighScoreEntry * newnode = new HighScoreEntry;
    currentnode = head;
    if(head == NULL)
    {
      head = newnode;
    }
    else
    {
      currentnode->next = newnode;
    }
    currentnode = newnode;
    currentnode->next = NULL;
    input_file >> currentnode->name >> currentnode->floor >> currentnode->level
           >> currentnode->total_health
           >> currentnode->attack >> currentnode->defense
           >> currentnode->current_exp >> currentnode->total_exp;
    create_linked_list(input_file,currentnode);
  }
  return head;
}

HighScoreEntry* insert_node(HighScoreEntry * &head, HighScoreEntry * newnode)
{
  HighScoreEntry * currentnode;
  HighScoreEntry * previousnode = NULL;
  if(head == NULL)
  {
    head = newnode;
    return head;
  }
  for(currentnode = head;currentnode != NULL;previousnode = currentnode, currentnode = currentnode->next)
  {
    if(newnode->floor >= currentnode->floor)
    {
      if(previousnode == NULL)
      {
        head = newnode;
        newnode->next = currentnode;
        return head;
      }
      else
      {
        newnode->next = currentnode;
        previousnode->next = newnode;
        return head;
      }
    }
  }
  previousnode->next = newnode;
  return head;
}

void tail_deletion(HighScoreEntry * &head)
{
  if(head->next == NULL)
  {
    delete head;
    head = NULL;
  }
  else
  {
    tail_deletion(head->next);
  }
}

void display_list(HighScoreEntry * head)
{
  static int num_player = 1;
  HighScoreEntry * currentnode = head;
  if(currentnode != NULL)
  {
    cout << num_player << ". ";
    cout << "Player Name: " << setw(11) << currentnode->name << '\n'
       << "Floor Reached: " << setw(9) << currentnode->floor << '\n'
       << "Level: " << setw(17) << currentnode->level << '\n'
       << "Total Health: " << setw(10) << currentnode->total_health << '\n'
       << "Attack: " << setw(16) << currentnode->attack << '\n'
       << "Defense: " << setw(15) << currentnode->defense << '\n'
       << "Current Experience: " << setw(4) << currentnode->current_exp << '\n'
       << "Experience to Level Up: " << currentnode->total_exp << '\n';
    cout << '\n';
    num_player++;
    display_list(currentnode->next);
  }
}


bool check_if_high_score(HighScoreEntry * head)
{
  HighScoreEntry * currentnode;
  int num_nodes = 0;
  for(currentnode = head;currentnode != NULL;currentnode = currentnode->next)
  {
    num_nodes++;
  }
  if(num_nodes >= 5)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void initialize_newnode(Player &Adventurer, HighScoreEntry * &newnode)
{
  newnode->attack = Adventurer.get_attack();
  newnode->current_exp = Adventurer.get_current_exp();
  newnode->defense = Adventurer.get_defense();
  newnode->floor = Adventurer.get_floor();
  newnode->level = Adventurer.get_level();
  newnode->name = Adventurer.get_name();
  newnode->total_exp = Adventurer.get_total_exp();
  newnode->total_health = Adventurer.get_total_health();
  newnode->next = NULL;
}

void create_high_score_entry(HighScoreEntry* &head,Player &Adventurer, ifstream &input_file)
{
  HighScoreEntry* currentnode = NULL;
  HighScoreEntry* newnode = new HighScoreEntry;
  initialize_newnode(Adventurer,newnode);
  head = insert_node(head,newnode);
  if(check_if_high_score(head))
  {
    tail_deletion(head);
  }
  cout <<  "--------------------Highscores--------------------" << '\n';
  input_file.close();
  ofstream output_file;
  output_file.open("highscores.txt",ios::trunc);
  check_file(output_file);
  for(currentnode = head;currentnode != NULL;currentnode = currentnode->next)
  {
    output_file << " " << '\n'
          << currentnode->name << '\n'
          << currentnode->floor << '\n'
          << currentnode->level << '\n'
          << currentnode->total_health << '\n'
          << currentnode->attack << '\n'
          << currentnode->defense << '\n'
          << currentnode->current_exp << '\n'
          << currentnode->total_exp;
  }
  output_file.close();
}

GameState play_again(GameState game_continue)
{
  char buffer[20];
  int player_choice;
  cout << "Your vision fading fast, you wonder if you can continue..." << '\n'
     << "Continue forward or will you try again? " << "1. Continue Forward 2. Try Again 3. Let Death Consume me"
     << '\n' << ">> ";
  cin >> buffer;
  player_choice = atoi(buffer);
  cin.ignore();
  while(player_choice != 1 and player_choice != 2 and player_choice != 3)
  {
    cout << '\n' << "You must decide soon!" << '\n';
    cin >> buffer;
    player_choice = atoi(buffer);
    cin.ignore();
  }
  switch(player_choice)
  {
  case 1:
    return CONTINUE;
    break;
  case 2:
    return RESTART;
    break;
  case 3:
    return EXITGAME;
    break;
  }
}

void delete_linked_list(HighScoreEntry * &head)
{
  HighScoreEntry * currentnode;
  HighScoreEntry * previousnode = NULL;
  for(currentnode = head;currentnode != NULL;previousnode = currentnode,currentnode = currentnode->next,delete previousnode)
  {
  ;
  }
}

void reset_player(Player &Adventurer)
{
  Adventurer.set_floor(1);
  Adventurer.set_level(1);
  Adventurer.set_attack(PLAYER_BASE_STAT + rand_num(3));
  Adventurer.set_defense(PLAYER_BASE_STAT + rand_num(4));
  int ex_health = rand_num(4);
  Adventurer.set_current_health(PLAYER_BASE_STAT + ex_health);
  Adventurer.set_total_health(PLAYER_BASE_STAT + ex_health);
  Adventurer.set_current_exp(0);
  Adventurer.set_total_exp(INITIAL_TOTAL_EXP);
}
