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

using namespace std;

#include <cstdlib>

#include "AC_Functions.h"

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
  /// Initializing the treasure type vector
  event_positions[ep_length-1] = EXIT;
  cpy_event_positions = event_positions;
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

void Gameboard::remove_event_position(int player_position)
{
	event_positions[player_position] = SPACE;
}

void Gameboard::new_level_gameboard()
{
  event_positions = cpy_event_positions;
  vector<int> positions = event_positions;
  random_shuffle(positions.begin(),positions.end());
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
  set_attack(PLAYER_BASE_STAT + rand_num(3));
  set_defense(PLAYER_BASE_STAT + rand_num(4));
  int ex_health = rand_num(4);
  set_current_health(PLAYER_BASE_STAT + ex_health);
  set_total_health(PLAYER_BASE_STAT + ex_health);
  set_current_exp(0);
  set_total_exp(INITIAL_TOTAL_EXP);
  set_position(0);
  level = 1;
  floor = 1;
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

int Player::get_level() const
{
  return level;
}

int Player::get_floor() const
{
  return floor;
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

void Player::set_level(int new_level)
{
  level = new_level;
}

void Player::set_floor(int new_floor)
{
  floor = new_floor;
}

void Player::stat_raise(Treasure& Buff,TreasureType type_stat_raise)
{
  if(type_stat_raise == ATTACK)
  {
    attack += Buff.get_attack_r();
    cout << "Treasure chest found! Attack is increased by " << Buff.get_attack_r() << '\n';
  }
  else if(type_stat_raise == DEFENSE)
  {
    defense += Buff.get_defense_r();
    cout << "Treasure chest found! Defense is increased by " << Buff.get_defense_r() << '\n';
  }
  else if(type_stat_raise == HEALTH)
  {
    total_health += Buff.get_total_health_r();
    current_health += Buff.get_total_health_r();
    cout << "Treasure chest found! Total health is increased by " << Buff.get_total_health_r() << '\n';
  }
  else if(type_stat_raise == POTION)
  {
    if((current_health + Buff.get_health_r()) < total_health)
    {
      current_health += Buff.get_health_r();
      cout << "Potion found! Health is increased by " << Buff.get_health_r() << '\n';
    }
    else if(current_health == total_health)
    {
      /// Health can't be raised if the two healths are equal, so the health raise is set to 0
      Buff.set_health_r(0);
      cout << "Potion found! But health is already full... " << '\n';
    }
    else
    {
      Buff.set_health_r(total_health - current_health);
      current_health = total_health;
      cout << "Potion found! Health is increased by " << Buff.get_health_r() << '\n';
    }
  }
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

int Treasure::get_total_health_r() const
{
  return(total_health_raise);
}

int Treasure::get_health_r() const
{
  return(health_raise);
}

int Treasure::get_attack_r() const
{
  return(attack_raise);
}

int Treasure::get_defense_r() const
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

/// ************************* //
/// Monster Member Functions  //
/// ************************* //

/// Monster Constructors ///

Monster::Monster()
{
  attack = 0;
  defense = 0;
  current_health = 0;
  total_health = 0;
  score_raise = 0;
  exp_raise = 0;
}

int Monster::get_attack() const
{
  return attack;
}

int Monster::get_defense() const
{
  return defense;
}

int Monster::get_current_health() const
{
  return current_health;
}

int Monster::get_total_health() const
{
  return total_health;
}

int Monster::get_exp_raise() const
{
  return exp_raise;
}

int Monster::get_score_raise() const
{
  return score_raise;
}

void Monster::set_attack(int new_attack)
{
  attack = new_attack;
}

void Monster::set_defense(int new_defense)
{
  defense = new_defense;
}

void Monster::set_current_health(int new_current_health)
{
  current_health = new_current_health;
}

void Monster::set_total_health(int new_total_health)
{
  total_health = new_total_health;
}

void Monster::set_exp_raise(int new_exp_raise)
{
  exp_raise = new_exp_raise;
}

void Monster::set_score_raise(int new_score_raise)
{
  score_raise = new_score_raise;
}

/// Treasure Member Functions ///



/// ************************ //
///   Function Declarations  //
/// ************************ //

/// void calc_board_perc(Gameboard& Board)
/// {
///  event_size = (Board.get_board).size() - 2;
///
/// }

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
/// I don't use this function, instead I execute this code in th gameboard constructor.
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
  /*
  vector<int> positions = Board.get_event_positions();
  random_shuffle(positions.begin() + 1,positions.end());
  display_board(Board.get_board(),Adventurer.get_position());
  Board.set_event_positions(positions);
  display_stats(Adventurer);
  */
}

void display_stats(Player& Adventurer)
{
  cout << Adventurer.get_name() << endl
     << "Floor: " << setw(7) << Adventurer.get_floor() << endl
     << "Level: " << setw(7) << Adventurer.get_level() << endl
     << "Health: " << setw(6) << Adventurer.get_current_health() << "/" << Adventurer.get_total_health() << endl
     << "Attack: " << setw(6) << Adventurer.get_attack() << endl
     << "Defense: " << setw(5) << Adventurer.get_defense() << endl
     << "Experience: " << Adventurer.get_current_exp() << "/" << Adventurer.get_total_exp();
}

void display_stats(Monster& Mob, Enemy monster_type)
{
  /// Add another message for all these,
  /// In other words, fix up the
  /// presentation of the combat
  if(monster_type == BAT)
  {
    cout << "Bat";
  }
  else if(monster_type == GOBLIN)
  {
    cout << "Goblin";
  }
  else if(monster_type == SKELETON)
  {
    cout << "Skeleton";
  }
  else
  {
    cout << "Zombie";
  }
  cout << endl;
  cout << "Health: " << setw(6) << Mob.get_current_health() << "/" << Mob.get_total_health() << endl
     << "Attack: " << setw(6) << Mob.get_attack() << endl
     << "Defense: " << setw(5) << Mob.get_defense() << endl;
}


void movement(Player& Adventurer)
{
  char player_move;
  cout << "\n>> ";
  cin.get(player_move);
  /// Input validation for correct character.
  while((player_move != 'w' && player_move != 's' && player_move != 'a' && player_move != 'd') || check_move(Adventurer.get_position(), player_move))
  {
    cout << "\n>> ";
    //cin.ignore();
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
  cin.ignore();
}

bool check_move(int player_position, char player_move)
{
  return((player_position < 5 && player_move == 'w') || (player_position == 0 && player_move == 'a') ||
       (player_position > 19 && player_move == 's') || (player_position == 24 && player_move == 'd'));
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
    enemy_base_exp;
  if(enemy_type == BAT)
  {
    const int BAT_BASE_DEFENSE = 3,
          BAT_BASE_ATTACK = 3,
          BAT_BASE_HEALTH = 5,
          BAT_BASE_EXP = 2;
    enemy_base_attack = BAT_BASE_ATTACK;
    enemy_base_defense = BAT_BASE_DEFENSE;
    enemy_base_health = BAT_BASE_HEALTH;
    enemy_base_exp = BAT_BASE_EXP;
    cout << "A bat appeared from the darkness!" << endl;
  }
  else if(enemy_type == GOBLIN)
  {
    const int GOBLIN_BASE_DEFENSE = 3,
          GOBLIN_BASE_ATTACK = 5,
          GOBLIN_BASE_HEALTH = 6,
          GOBLIN_BASE_EXP = 4;
    enemy_base_attack = GOBLIN_BASE_ATTACK;
    enemy_base_defense = GOBLIN_BASE_DEFENSE;
    enemy_base_health = GOBLIN_BASE_HEALTH;
    enemy_base_exp = GOBLIN_BASE_EXP;
    cout << "A goblin appeared from the darkness!" << endl;
  }
  else if(enemy_type == SKELETON)
  {
    const int SKELETON_BASE_DEFENSE = 5,
          SKELETON_BASE_ATTACK = 3,
          SKELETON_BASE_HEALTH = 5,
          SKELETON_BASE_EXP = 3;
    enemy_base_attack = SKELETON_BASE_ATTACK;
    enemy_base_defense = SKELETON_BASE_DEFENSE;
    enemy_base_health = SKELETON_BASE_HEALTH;
    enemy_base_exp = SKELETON_BASE_EXP;
    cout << "A skeleton appeared from the darkness!" << endl;
  }
  else
  {
    const int ZOMBIE_BASE_DEFENSE = 6,
          ZOMBIE_BASE_ATTACK = 4,
          ZOMBIE_BASE_HEALTH = 7,
          ZOMBIE_BASE_EXP = 4;
    enemy_base_attack = ZOMBIE_BASE_ATTACK;
    enemy_base_defense = ZOMBIE_BASE_DEFENSE;
    enemy_base_health = ZOMBIE_BASE_HEALTH;
    enemy_base_exp = ZOMBIE_BASE_EXP;
    cout << "A zombie appeared from the darkness!" << endl;
  }
  Mob.set_attack(enemy_base_attack+ rand_num(floor));
  Mob.set_defense(enemy_base_defense + rand_num(floor));
  int ex_health = rand_num(floor);
  Mob.set_current_health(enemy_base_health + ex_health);
  Mob.set_total_health(enemy_base_health + ex_health);
  Mob.set_exp_raise(enemy_base_exp + floor/3);
  return enemy_type;
}

/// This returns a bool because either the player
/// dies or the enemy does
bool combat(Monster& Mob, Player& Adventurer,Enemy enemy_type, int floor)
{
  int damage;
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
    display_stats(Mob,enemy_type);
    cout << "----------" << '\n';
    display_stats(Adventurer);
    cout << '\n' << "----------" << '\n';
    cin.get();

    damage = damage_done(Mob.get_attack(), Adventurer.get_defense());
    if(enemy_type == BAT)
    {
      cout << "The bat did " << damage << " damage!" << endl;
    }
    else if(enemy_type == GOBLIN)
    {
      cout << "The goblin did " << damage << " damage!" << endl;
    }
    else if(enemy_type == SKELETON)
    {
      cout << "The skeleton did " << damage << " damage!" << endl;
    }
    else
    {
      cout << "The zombie did " << damage << " damage!" << endl;
    }
    Adventurer.set_current_health(Adventurer.get_current_health() - damage);

    damage = damage_done(Adventurer.get_attack(), Mob.get_defense());
    if(enemy_type == BAT)
    {
      cout << "The bat sustained " << damage << " damage!" << endl;
    }
    else if(enemy_type == GOBLIN)
    {
      cout << "The goblin sustained " << damage << " damage!" << endl;
    }
    else if(enemy_type == SKELETON)
    {
      cout << "The skeleton sustained " << damage << " damage!" << endl;
    }
    else
    {
      cout << "The zombie sustained " << damage << " damage!" << endl;
    }
    Mob.set_current_health(Mob.get_current_health() - damage);
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
  cout << "Level up!" << '\n';
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

void reset_player(Player & Adventurer)
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

void check_file(ifstream &input_file)
{
  if(input_file.fail())
  {
  cout << "Error opening file";
  }
}

void check_file(ofstream &input_file)
{
  if(input_file.fail())
  {
  cout << "Error opening file";
  }
}
