#include"simulator.h"

Simulator::Simulator(State state,Logger& logger,const std::vector<Color> d)
  :state_(std::move(state))
  ,logger_(logger)
  ,ideal_snake_(d)
{

}

Simulator::~Simulator(){

}

Direction Simulator::decide(){
  for(Direction dir:{
      Direction::UP,
      Direction::DOWN,
      Direction::LEFT,
      Direction::RIGHT
  }){
    
    if(state_.snake().canMove(dir)){
      return dir;
    }
  }

  return Direction::UP;
}

void Simulator::solve(){
  const int MAX_SIMULATION=100000;
  
  logger_.log(state_,0);

  for(int i=0;i<MAX_SIMULATION;i++){
    Direction dir=decide();

    bool success=state_.apply(dir);

    if(!success){
      logger_.log("can not move!");
      break;
    }

    operation_row_.emplace_back(OUTPUT_DIR[(int)dir]);

    logger_.log(state_,i+1);

    if(state_.snake().size()==ideal_snake_.size()){
      logger_.log("score: "+std::to_string(score()));
      return;
    }
  }

  logger_.log("max simulation: "+std::to_string(score()));
}

int Simulator::score(){
  int error_count=0;

  const int m=ideal_snake_.size();
  const int k=state_.snake().size();

  for(int i=0;i<k;i++){
    if(state_.snake().body()[i].color!=ideal_snake_[i]){
      error_count++;
    }
  }
  return operation_row_.size()+10000*(error_count+2*(m-k));
}
