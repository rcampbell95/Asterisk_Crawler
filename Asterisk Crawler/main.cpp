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
    int num = 23;
    vector<int> event_positions(23);
    // Will be Part of create gameboard function //
    Gameboard Board;
    random_shuffle(event_positions.begin(),event_positions.end());
    Board.create_gameboard(Board);
    cout << Board.get_board()[0];
    cout << Board.get_layout();
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
