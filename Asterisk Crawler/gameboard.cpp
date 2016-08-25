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

Gameboard::Gameboard()
{
  width = 10;
  height = 10;
  level_seed = 0;
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

void Gameboard::new_level_gameboard(vector<int>& dungeon)
{
  event_positions = dungeon;
  int spaces = count_spaces();
  events.resize(spaces);

  num_treasures = spaces / INITIAL_TREASURES;
  num_spaces = spaces * INITIAL_SPACES;
  num_monsters = spaces * INITIAL_MONSTERS;

  for(int count = 0;count < spaces;count++)
  {
    if(count < num_treasures)
    {
      events[count] = TREASURE;
    }
    else if(count < num_monsters + num_treasures)
    {
      events[count] = MONSTER;
    }
    else
    {
      events[count] = SPACE;
    }
  }

  events[spaces-1] = EXIT;

  vector<int> positions = events;
  random_shuffle(positions.begin(),positions.end());  /// change random shuffle
  int pos = 0;
  for(int i = 0; i < event_positions.size();i++)
  {
    if(event_positions[i] == SPACE)
    {
      event_positions[i] = positions[pos++];
    }
  }
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
