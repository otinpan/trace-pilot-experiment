#include<cassert>
#include"state.h"

State::State(Stage state,Snake snake)
  :stage_(state)
  ,snake_(snake)
{
  
}

Stage::~Stage(){

}

bool State::apply(Direction dir){
  // 境界判定
  const Pos next_head=snake_.head().pos;
  if(stage_.checkInStage(next_head)){
    return false;
  }

  // 移動可能判定
  if(!snake_.canMove(dir)){
    return false;
  }

  // 食べる餌
  Color food=stage_.removeFood(next_head);
  assert(food!=OUT_OF_BOUND);

  // snake移動
  const Segment old_segment=snake_.move(dir);

  // 成長
  if(food!=EMPTY){
    snake_.grow(old_segment.pos,food);
  }

  // 嚙みちぎり判定
  const std::vector<Segment> dropped=snake_.bite();
  stage_.addFoods(dropped);

  return true;
}
