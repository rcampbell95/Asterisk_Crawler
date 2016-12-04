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

///
///
///
///
///

///*******************///
///    Dependencies   ///
///*******************///

#include <string>

#include "unit.h"
#include "item.h"
#include "monster.h"
#include "proto.h"
#include "player.h"

///*******************///
///    Constants      ///
///*******************///

#define INITIAL_TOTAL_EXP 10
#define PLAYER_BASE_STAT 10
#define PLAYER_BASE_SPEED 5

/// *********************** //
/// Player Member Functions //
/// *********************** //

/// Player Constructors ///

Player::Player(int floor_size)
{
  set_attack(PLAYER_BASE_STAT + rand_num(3));
  set_defense(PLAYER_BASE_STAT + rand_num(4));
  set_speed(PLAYER_BASE_SPEED);
  int ex_health = rand_num(4);
  set_current_health(PLAYER_BASE_STAT + ex_health);
  set_total_health(PLAYER_BASE_STAT + ex_health);
  set_current_exp(0);
  set_total_exp(INITIAL_TOTAL_EXP);
  position = 0;
  level = 1;
  floor = 1;
}

/// Player Member Functions ///

void Player::stat_raise(Treasure& Buff, TreasureType type_stat_raise)
{
  if(type_stat_raise == ATTACK)
  {
    attack += Buff.get_attack_r();
    cout << "Treasure chest found! Attack is increased by " << Buff.get_attack_r() << '\n';
  }
  else if(type_stat_raise == DEFENSE)
  {
    defense += Buff.get_defense_r();
    cout << "Treasure chest found! Defense is increased by " << Buff.get_defense_r() << '\n';
  }
  else if(type_stat_raise == HEALTH)
  {
    total_health += Buff.get_total_health_r();
    current_health += Buff.get_total_health_r();
    cout << "Treasure chest found! Total health is increased by " << Buff.get_total_health_r() << '\n';
  }
  else if(type_stat_raise == POTION)
  {
    if((current_health + Buff.get_health_r()) < total_health)
    {
      current_health += Buff.get_health_r();
      cout << "Potion found! Health is increased by " << Buff.get_health_r() << '\n';
    }
    else if(current_health == total_health)
    {
      /// Health can't be raised if the two healths are equal, so the health raise is set to 0
      Buff.set_health_r(0);
      cout << "Potion found! But health is already full... " << '\n';
    }
    else
    {
      Buff.set_health_r(total_health - current_health);
      current_health = total_health;
      cout << "Potion found! Health is increased by " << Buff.get_health_r() << '\n';
    }
  }
}
