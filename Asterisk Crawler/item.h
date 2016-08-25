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
