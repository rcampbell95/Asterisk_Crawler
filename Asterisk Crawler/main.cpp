#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <time.h>
#include <algorithm>
#include "AC_Objects.cpp"

using namespace std;

int main()
{
    int num = 25;
    vector<int> event_positions(num);
    // Will be Part of create gameboard function //
    Gameboard Board;
    ///cout << Board.get_board()[0] << Board.get_board()[1];
    ///cout << Board.get_layout();
    game_start(Board, event_positions);
    //for(int count = 0;count < )
    //int board_size = 5;
    //string board_pattern = "|*|*|*|*|*|";
    //vector<string> gameboard(board_size,board_pattern);
    //for(int count = 0;count < gameboard.size();count++)
    //{
    //    if(count == 0)
    //        gameboard[0][1] = '@';
    //    cout << gameboard[count] << endl;
    //}
    return 0;
}
