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

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

///*******************///
///    Constants      ///
///*******************///

#define GAMEBOARD_LENGTH 5

///*******************///
///   Dependencies    ///
///*******************///

#include <utility>

using namespace std;

/// ************************* //
///    Class Declarations     //
/// ************************* //

class Gameboard
{
private:
  int height;
  int width;
  int level_seed;
  int num_treasures;
  int num_spaces;
  int num_monsters;
  vector<int> event_positions;
  vector<int> events;
  int count_spaces();
public:
  Gameboard();

  int get_height() const {return height;}
  int get_width() const {return width;}
  int get_seed() const {return level_seed;}
  int p_spaces() const {return num_spaces;}
  int n_monsters() const {return num_monsters;}
  int p_treasures() const {return num_treasures;}
  vector<int> get_event_positions() const;
  vector<int> get_events() const;

  void set_height(int new_height) {height = new_height;}
  void set_width(int new_width) {width = new_width;}
  void set_seed(int new_seed) {level_seed = new_seed;}
  void set_p_treasures(int num) {num_treasures = num;}
  void set_p_spaces(int num) {num_spaces = num;}
  void set_n_monsters(int);
  void set_event_positions(vector<int>&);
  void set_events(vector<int>&);

  void remove_event_position(int);
  void new_level_gameboard(vector<int>&);
  // You can make the gameboard a constant for now and later implement the function correctly.
  //void create_gameboard(Gameboard&);
};

#endif
