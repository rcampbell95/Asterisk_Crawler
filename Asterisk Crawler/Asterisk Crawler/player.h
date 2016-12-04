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

#ifndef PLAYER_H
#define PLAYER_H

///*******************///
///    Dependencies   ///
///*******************///

class Player: public Unit
{
private:
  int position;
  int score;
  int current_exp;
  int total_exp;
  int level;
  int floor;
public:
  Player(int floor_size);
  int get_position() const       {return position;}
  int get_current_exp() const    {return current_exp;}
  int get_total_exp() const      {return total_exp;}
  int get_level() const          {return level;}
  int get_floor() const          {return floor;}
  void set_position(int player_position)             {position = player_position;}
  void set_current_exp(int current_player_exp)       {current_exp = current_player_exp;}
  void set_total_exp(int total_player_exp)           {total_exp = total_player_exp;}
  void set_level(int new_level)                      {level = new_level;}
  void set_floor(int new_floor)                      {floor = new_floor;}
  void stat_raise(Treasure&, TreasureType);

};

#endif
