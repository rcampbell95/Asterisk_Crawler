#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <algorithm>
#include "AC_Functions.h"

using namespace std;

int main()
{
    /// Will be Part of create gameboard function //
    Player Adventurer;
    Gameboard Board;
    Treasure Buff;
    TreasureType temp_treasure;
    ///cout << Board.get_board()[0] << Board.get_board()[1];
    ///cout << Board.get_layout();
    game_start(Board, Adventurer);
    vector<int> event_positions = Board.get_event_positions();
    while(Adventurer.get_position() < 24)
    {
        movement(Adventurer);
        if(event_positions[Adventurer.get_position()] == TREASURE)
        {
            temp_treasure = initialize_treasure(Buff,Board.get_treasure_type());
            cout << '\n' << Buff.get_total_health_r() << " "
             << Buff.get_health_r() << " "
             << Buff.get_attack_r() << " "
             << Buff.get_defense_r() << '\n';
            Adventurer.stat_raise(Buff,temp_treasure);
        }
        display_board(Board.get_board(),Adventurer.get_position());
        display_stats(Adventurer);
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
