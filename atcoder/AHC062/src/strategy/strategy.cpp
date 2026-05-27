#include"strategy.h"

Strategy::Strategy()
  :rng_(0)
{

}

Strategy::~Strategy()=default;


std::vector<Pos> Strategy::solve(State& state,Logger& logger){
  (void)state;
  (void)logger;
  return{};
} 


long long Strategy::score_straight(
  const State& state,
  Pos left_top,
  Pos right_bottom,
  Logger& logger,
  Pos& pos,
  Direction dir,
  int& turn
){
  long long score=0;
  while(true){
    Pos next=pos+DIRS[static_cast<int>(dir)];
    if(!next.is_on_block(left_top,right_bottom)){
      break;
    }
    pos=next;
    turn++;
    score+=(long long)turn*state.kingdom()[pos.i][pos.j];
  }
// @trace-pilot 459aadc7d949bf4c6b61391b35a1fa84905c19a6
  return score;
}
