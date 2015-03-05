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
  int num_treasures;
  int num_spaces;
  int num_monsters;
  string board_layout;
  // no longer necessary
  // vector<string> gameboard;
  // Could the type of this vector cause any problems? Someting to check into.
  vector<pair<int, string> > event_positions;
  // vector<int> event_positions;
  vector<pair<int, string> > cpy_event_positions;
public:
  Gameboard(int, int, int, string,int);
  Gameboard();
  int p_spaces() const {return num_spaces;}
  int n_monsters() const {return num_monsters;}
  int p_treasures() const {return num_treasures;}
  string get_layout() const;
  /// vector<pair<int, string>> get_board() const;
  ///  vector<string> get_board() const;
  vector<pair<int, string> > get_event_positions() const;
  // vector<int> get_event_positions() const;
  vector<int> get_cpy_event_positions() const;
  void set_layout(string);
  void set_p_treasures(int num) {num_treasures = num;}
  void set_p_spaces(int num) {num_spaces = num;}
  void set_n_monsters(int);
  void set_event_positions(vector<pair<int, string> >&);
  ///void set_event_positions(vector<int>&);
  void set_cpy_event_positions(vector<pair<int, string> >);
  ///void set_cpy_event_position(vector<int>&);
  void remove_event_position(int);
  void new_level_gameboard();
  // You can make the gameboard a constant for now and later implement the function correctly.
  //void create_gameboard(Gameboard&);
};

#endif
