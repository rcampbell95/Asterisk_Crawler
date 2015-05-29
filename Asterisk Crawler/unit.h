#ifndef UNIT_H
#define UNIT_H

class Unit
{
protected:
  std::string name;
  int attack;
  int defense;
  int speed;
  int current_health;
  int total_health;
public:
  std::string get_name() const        {return name;}
  int get_attack() const         {return attack;}
  int get_defense() const        {return defense;}
  int get_speed() const          {return speed;}
  int get_current_health() const {return current_health;}
  int get_total_health() const   {return total_health;}
  void set_name(std::string unit_name)          {name = unit_name;}
  void set_current_health(int currentHealth) {current_health = currentHealth;}
  void set_total_health(int totalHealth)     {total_health = totalHealth;}
  void set_attack(int unitAttack)                 {attack = unitAttack;}
  void set_defense(int unitDefense)               {defense = unitDefense;}
  void set_speed(int unitSpeed)                   {speed = unitSpeed;}
};

#endif
