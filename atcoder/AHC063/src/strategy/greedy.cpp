#include"greedy.h"

Greedy::Greedy(const std::vector<Color>& ideal)
  :Strategy(ideal)
{

}

Greedy::~Greedy() = default;

std::vector<char> Greedy::solve(State& state,Logger& logger){
  std::vector<char> operation_row;
  Direction dir=Direction::UP;
  for(int i=0;i<MAX_SIMULATION;i++){
    bool found=false;
    for(Direction d:{
        Direction::UP,
        Direction::DOWN,
        Direction::LEFT,
        Direction::RIGHT
        }){
      if(state.snake().canMove(d)){
        dir=d;
        found=true;
        break;
      }
    }

    if(!found){
      logger.log("can not move!");
      break;
    }

    bool success=state.apply(dir);

    if(!success){
      logger.log("can not move!");
      break;
    }

    operation_row.emplace_back(OUTPUT_DIR[(int)dir]);

    logger.log(state,i+1);

    if(state.snake().size()==ideal_.size()){
      logger.log("score: "+std::to_string(score(state,operation_row.size())));
      return operation_row;
    }
    
  }

  logger.log("reach max simulation: "+std::to_string(score(state,operation_row.size())));
  return operation_row;
}
