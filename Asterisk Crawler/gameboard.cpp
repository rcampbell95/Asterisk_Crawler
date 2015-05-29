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

Gameboard::Gameboard(vector<int>& dungeon)
{
  event_positions = dungeon;
  int spaces = count_spaces();
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
}

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

// Gameboard Member Functions //


vector<int> Gameboard::get_event_positions() const
{
  return event_positions;
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
