#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <time.h>
#include <algorithm>

using namespace std;

int rand_num(int);
// int linear_search(vector<int>, int);
vector initialize_vec(vector<int>);

int main()
{
    int num = 23;
    vector<int> event_positions(23);
    // Will be Part of create gameboard function //
    random_shuffle(event_positions.begin(),event_positions.end());
    cout << event_positions[0];
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

int rand_num(int num)
{
    srand(time(0));
    return(rand() % num);
}

/*int linear_search(vector<int> event_positions, int search_num)
{
    int ep_size = event_positions.size();
    for(int count = 0;count < ep_size;count++)
    {
        if(event_positions[count] == search_num)
        {
            return(1);
        }
    }
    return(0);
}
*/

vector initialize_vec(vector<int> event_positions)
{
    ep_length = event_positions.size();
    for(int count = 0;count < ep_length;count++)
    {
        event_positions[count] = count;
    }
    return event_positions;
}
