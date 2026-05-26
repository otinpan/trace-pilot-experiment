#include"greedy.h"

Greedy::Greedy(bool is_vertical)
  :Strategy()
  ,is_vertical_(is_vertical)
{

}

Greedy::~Greedy()=default;

std::vector<Pos> Greedy::solve(State& state,Logger& logger){
  if(is_vertical_)return solve_zigzag_vertical(state,logger);
  return solve_zigzag(state,logger); 
}

std::vector<Pos> Greedy::solve_zigzag(State& state,Logger& logger){
  std::vector<Pos> result;
  logger.log(state);
  result.emplace_back(state.pos());
// @trace-pilot 547bb264d1c531829a76e5a5410fa876c80ed7f4 //////////////////////////////////////////
//## `greedy.cpp`の`solve_zigzag`をCodexに修正してもらった
// @trace-pilot c2a83752008387aa17308faa32bb97be37271ea9
  for(int i=0;i<map_size;i++){
    Direction dir=i%2==0 ? Direction::RIGHT : Direction::LEFT;
    for(int j=0;j<map_size-1;j++){
      if(!state.apply(dir)){
        return result;
      }
      result.emplace_back(state.pos());
      logger.log(state);
    }

    if(i!=map_size-1){
      if(!state.apply(Direction::DOWN)){
        return result;
      }
      result.emplace_back(state.pos());
      logger.log(state);
    }
  }

  return result;
}

std::vector<Pos> Greedy::solve_zigzag_vertical(State& state,Logger& logger){
  std::vector<Pos> result;
  logger.log(state);
  result.emplace_back(state.pos());

  for(int j=0;j<map_size;j++){
    Direction dir=j%2==0 ? Direction::DOWN : Direction::UP;
    for(int i=0;i<map_size-1;i++){
      if(!state.apply(dir)){
        return result;
      }
      result.emplace_back(state.pos());
      logger.log(state);
    }

    if(j!=map_size-1){
      if(!state.apply(Direction::RIGHT)){
        return result;
      }
      result.emplace_back(state.pos());
      logger.log(state);
    }
  }

  return result;
}
