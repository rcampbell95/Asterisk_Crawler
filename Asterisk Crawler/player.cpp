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

Player::Player()
{
  set_attack(PLAYER_BASE_STAT + rand_num(3));
  set_defense(PLAYER_BASE_STAT + rand_num(4));
  set_speed(PLAYER_BASE_SPEED);
  int ex_health = rand_num(4);
  set_current_health(PLAYER_BASE_STAT + ex_health);
  set_total_health(PLAYER_BASE_STAT + ex_health);
  set_current_exp(0);
  set_total_exp(INITIAL_TOTAL_EXP);
  set_position(0);
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
