#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <algorithm>
#include "AC_Functions.h"

using namespace std;

int main()
{
    /// Object Declarations ///
    Player Adventurer;
    Gameboard Board;
    Treasure Buff;
    Monster Mob;
    /// Treasure variable to hold the type of treasure ///
    TreasureType temp_treasure;
    Enemy enemy_type;
    int floor = 1;
    bool player_alive = true;
    game_start(Board, Adventurer);
    Board.new_level_gameboard(floor,Adventurer.get_position());
    while(player_alive == true)
    {
        display_board(Board.get_board(),Adventurer.get_position());
        display_stats(Adventurer, floor);
        movement(Adventurer);
        int player_position = Adventurer.get_position();
        if(Board.get_event_positions()[player_position] == TREASURE)
        {
            temp_treasure = initialize_treasure(Buff);
            Adventurer.stat_raise(Buff,temp_treasure);
            Board.remove_event_position(player_position);
        }

        else if(Board.get_event_positions()[player_position] == MONSTER)
        {
            enemy_type = initialize_monster(Mob, floor);
            player_alive = combat(Mob, Adventurer, enemy_type, floor);
            if(player_alive == false)
            {
                break;
            }

            Board.remove_event_position(player_position);
            if(Adventurer.get_current_exp() > Adventurer.get_total_exp())
            {
                level_up(Adventurer);
            }
        }
        else if(Board.get_event_positions()[player_position] == EXIT)
        {
            floor += 1;
            Board.new_level_gameboard(floor,player_position);
            /// You may want to make this part of some game_end function, like highscore, saving, other stuff.
            cout << '\n' << "The exit! Steeling yourself, you ascend the stairs..." << '\n';
        }
    }
    ///for(int count = 0;count < )
    ///int board_size = 5;
    ///string board_pattern = "|*|*|*|*|*|";
    ///vector<string> gameboard(board_size,board_pattern);
    ///for(int count = 0;count < gameboard.size();count++)
    ///{
    ///    if(count == 0)
    ///        gameboard[0][1] = '@';
    ///    cout << gameboard[count] << endl;
    ///}
    return 0;
}
