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
  const int initial_treasures = 10;
  const double initial_spaces = .73;
  const double initial_monsters = 1 - initial_spaces;

  event_positions = dungeon;
  int spaces = count_spaces();
  events.resize(spaces);

  num_treasures = spaces / initial_treasures;
  num_spaces = spaces * initial_spaces;
  num_monsters = spaces * initial_monsters;



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
