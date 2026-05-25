#include"strategy.h"

Strategy::Strategy()
  :rng_(0)
{

}

Strategy::~Strategy()=default;


std::vector<std::pair<char,char>> Strategy::solve(State& state,Logger& logger){
  (void)state;
  (void)logger;
  return{};
} 

int Strategy::score(const State& state) const{
  return 0;
}
