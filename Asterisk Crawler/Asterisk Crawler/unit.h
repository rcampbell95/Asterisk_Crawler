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
