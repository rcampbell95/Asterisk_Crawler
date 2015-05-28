///
///
///
///
///

///*******************///
///    Constants      ///
///*******************///

#define INITIAL_GAMEBOARD_LENGTH 5
#define INITIAL_GAMEBOARD_SIZE 25
#define INITIAL_TREASURES 10
#define INITIAL_SPACES .73
#define INITIAL_MONSTERS .17

///*******************///
///    Dependencies   ///
///*******************///

#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <algorithm>
#include <iomanip>
#include <map>

using namespace std;

#include <cstdlib>

#include "gameboard.h"
#include "item.h"
#include "unit.h"
#include "monster.h"
#include "proto.h"
#include "player.h"

/// ************************** //
/// Gameboard Member Functions //
/// ************************** //

// Gameboard Constructors //

int Gameboard::count_spaces()
{
    int spaces = 0;
    for(int i = 0;i < event_positions.size();i++)
    {
        if(event_positions[i] == 1)
        {
            spaces++;
        }
    }
    return(spaces);
}

Gameboard::Gameboard(vector<int>& dungeon)
{
  int spaces = count_spaces(dungeon);
  spaces = spaces - 2; // To account for the exit and entrance

  num_treasures = spaces / INITIAL_TREASURES;
  num_spaces = spaces * INITIAL_SPACES;
  num_monsters = spaces * INITIAL_MONSTERS;

  for(int count = 0;count < spaces;count++)
  {
    if(count < num_treasures)
    {
      event_positions[count] = TREASURE;
    }
    else if(count < num_monsters)
    {
      event_positions[count] = MONSTER;
    }
  }

  dungeon[spaces-1] = EXIT;
  cpy_event_positions = event_positions;
  /*
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

  // Initializing the treasure type vector
  event_positions[ep_length-1] = EXIT;
  cpy_event_positions = event_positions;
  */
  ///
}

/*
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
*/

// Gameboard Member Functions //

string Gameboard::get_layout() const
{
  return board_layout;
}

vector<int> Gameboard::get_event_positions() const
{
  return event_positions;
}

void Gameboard::set_layout(string layout)
{
  board_layout = layout;
}

void Gameboard::set_event_positions(vector<int> &positions)
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
  random_shuffle(positions.begin(),positions.end());  /// change random shuffle
  event_positions = positions;
}

/// edit
/*
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

void Gameboard::set_event_positions(vector<int> &positions)
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
*/
///

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
