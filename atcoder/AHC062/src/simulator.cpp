#include"simulator.h"

Simulator::Simulator(State state,Strategy& strategy,Logger& logger)
  :state_(std::move(state))
  ,strategy_(strategy)
  ,logger_(logger)
{

}

Simulator::~Simulator(){

}

std::vector<std::pair<char,char>> Simulator::simulate(){
  std::vector<std::pair<char,char>> result=strategy_.solve(state_,logger_);

  return result;
}
