#include<cassert>
#include"state.h"

State::State(Stage state,Snake snake)
  :stage_(std::move(state))
  ,snake_(std::move(snake))
{
  
}

State::~State(){

}

// O(K)
bool State::apply(Direction dir){
  const Pos next_head=snake_.head().pos+DIRS[(int)dir];

  // 境界判定
  if(!stage_.checkInStage(next_head)){
    return false;
  }

  // 移動可能判定
  // O(1)
  if(!snake_.canMove(dir)){
    return false;
  }

  // 食べる餌
  // O(1)
  Color food=stage_.removeFood(next_head);
  assert(food!=OUT_OF_BOUND);

  // snake移動
  // O(K)
  const Segment old_segment=snake_.move(dir);

  // 成長
  // O(1)
  if(food!=EMPTY){
    snake_.grow(old_segment.pos,food);
  }

  // 嚙みちぎり
  // O(K)
  const std::vector<Segment> dropped=snake_.bite();
  // O(1)
  stage_.addFoods(dropped);

  return true;
}
