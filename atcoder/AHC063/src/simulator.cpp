#include "simulator.h"

Simulator::Simulator(State state, Strategy& strategy, Logger& logger)
  :state_(std::move(state))
  ,strategy_(strategy)
  ,logger_(logger)
{

}

Simulator::~Simulator(){

}


std::vector<char> Simulator::simulate(){
  logger_.log(state_,0);
  std::vector<char> result = strategy_.solve(state_, logger_);

  return result;
}

