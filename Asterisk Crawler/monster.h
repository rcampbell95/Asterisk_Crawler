#ifndef MONSTER_H
#define MONSTER_H

///*******************///
///    Dependencies   ///
///*******************///

class Monster: public Unit
{
private:
  int exp_raise;
  int score_raise;
public:
  Monster();
  int get_exp_raise() const      {return exp_raise;}
  int get_score_raise() const    {return score_raise;}
  void set_exp_raise(int new_exp_raise)            {exp_raise = new_exp_raise;}
  void set_score_raise(int new_score_raise)        {score_raise = new_score_raise;}
};


#endif
