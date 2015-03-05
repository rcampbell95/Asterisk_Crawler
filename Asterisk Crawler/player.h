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
  Player();
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
