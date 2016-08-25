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

#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <fstream>

using namespace std;

#include "unit.h"
#include "gameboard.h"
#include "item.h"
#include "monster.h"
#include "proto.h"
#include "player.h"

#include "DungeonGenerator.h"

#include <time.h>
#include <assert.h>

int main()
{
  /// Object Declarations ///
  DungeonGenerator LevelGenerator(0,45,35);
  LevelGenerator.generate_dungeon(3, 15, 5);
  vector<int> new_dungeon = LevelGenerator.get_dungeon();

  Player Adventurer(new_dungeon.size());
  Gameboard Board;
  Board.set_height(LevelGenerator.get_height());
  Board.set_width(LevelGenerator.get_width());
  Board.set_seed(LevelGenerator.get_mapSeed());
  Treasure Buff;
  Monster Mob;
  /// Treasure variable to hold the type of treasure ///
  TreasureType temp_treasure;
  Enemy enemy_type;
  bool player_alive = true;
  GameState game_continue = EXITGAME;
  GameState previous_game_continue;
  ifstream input_file;
  input_file.open("highscores.txt");
  HighScoreEntry * head = NULL;

  game_start(Adventurer);
  Board.new_level_gameboard(new_dungeon);
  Adventurer.set_position(find_position(Adventurer, Board.get_event_positions()));

  do
  {
  while(player_alive)
  {
    display_board(Board.get_event_positions(),Board.get_width(),Adventurer.get_position());
    display_stats(Adventurer);
    movement(Adventurer, Board.get_width(), Board.get_event_positions()); /// Won't work. Need to pass vector to index possible places
    int player_position = Adventurer.get_position();
    if(Board.get_event_positions()[player_position] == TREASURE)
    {
      temp_treasure = initialize_treasure(Buff);
      Adventurer.stat_raise(Buff,temp_treasure);
      Board.remove_event_position(player_position);
    }
    else if(Board.get_event_positions()[player_position] == MONSTER)
    {
      enemy_type = initialize_monster(Mob, Adventurer.get_floor());
      player_alive = combat(Mob, Adventurer, enemy_type, Adventurer.get_floor());
      if(player_alive == false)
      {
        break;
      }
      Board.remove_event_position(player_position);
      if(Adventurer.get_current_exp() >= Adventurer.get_total_exp())
      {
        level_up(Adventurer);
      }
    }

    else if(Board.get_event_positions()[player_position] == EXIT)
    {
      Adventurer.set_floor(Adventurer.get_floor() + 1);
      Board.new_level_gameboard(new_dungeon);
      /// You may want to make this part of some game_end function, like highscore, saving, other stuff.
      cout << '\n' << "The exit! Steeling yourself, you ascend the stairs..." << '\n';
    }
  }

    /// Game Continue or Restart ///
    game_continue = play_again(game_continue);
    previous_game_continue = game_continue;
    if(game_continue == CONTINUE)
    {
      Adventurer.set_current_health(Adventurer.get_total_health());
      player_alive = true;
    }
    else if(game_continue == RESTART)
    {
      reset_player(Adventurer);
      player_alive = true;
    }
  }while(game_continue);

  /// Highscore Creation and Display ///
  check_file(input_file);
  head = create_linked_list(input_file,head);
  if(previous_game_continue != CONTINUE)
  {
    create_high_score_entry(head,Adventurer,input_file);
    display_list(head);
  }
  delete_linked_list(head);
  input_file.close();
  /// ----------------------------- ///
  cin.get();
}


