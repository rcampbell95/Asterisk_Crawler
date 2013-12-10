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
    int level = 1;
    game_start(Board, Adventurer);
    vector<int> event_position_cpy = Board.get_event_positions();
    while(event_position_cpy[Adventurer.get_position()] != EXIT || Adventurer.get_current_health() > 0)
    {
        movement(Adventurer);
        if(Board.get_event_positions()[Adventurer.get_position()] == TREASURE)
        {
            temp_treasure = initialize_treasure(Buff,Board.get_treasure_type());
            Adventurer.stat_raise(Buff,temp_treasure);
            Board.remove_event_position(Adventurer.get_position());
        }

        else if(Board.get_event_positions()[Adventurer.get_position()] == MONSTER)
        {
            initialize_monster(Mob, level);
        }

        display_board(Board.get_board(),Adventurer.get_position());
        display_stats(Adventurer);
    }
    level += 1;

    /// You may want to make this part of some game_end function, like highscore, saving, other stuff.
    cout << '\n' << "The exit! Steeling yourself, you ascend the stairs..." << '\n';
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
