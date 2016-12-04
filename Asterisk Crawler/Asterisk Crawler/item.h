#ifndef ITEM_H
#define ITEM_H

class Treasure
{
private:
  int total_health_raise;
  int health_raise;
  int attack_raise;
  int defense_raise;
public:
  Treasure();
  void set_total_health_r(int raise) {total_health_raise = raise;}
  void set_health_r(int raise)       {health_raise = raise;}
  void set_attack_r(int raise)       {attack_raise = raise;}
  void set_defense_r(int raise)      {defense_raise = raise;}
  int get_total_health_r() const {return total_health_raise;}
  int get_health_r() const       {return health_raise;}
  int get_attack_r() const       {return attack_raise;}
  int get_defense_r() const      {return defense_raise;}
};

#endif