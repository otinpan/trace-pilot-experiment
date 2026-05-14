#include<cassert>
#include"snake.h"

Snake::Snake(int stage_size)
  :stage_size_(stage_size)
{
  for(int i=0;i<5;i++){
    body_.emplace_back(Segment(Pos(4-i,0),static_cast<Color>(1)));
  }
}

Snake::~Snake(){

}


Segment Snake::move(Direction dir){
  const Pos head_pos=head().pos+DIRS[(int)dir];
  assert(head_pos.i>=0 && head_pos.i<stage_size_ &&
      head_pos.j>=0 && head_pos.j<stage_size_);

  const Segment old_tail=tail();

  // 位置更新
  for(size_t i=body_.size()-1;i>0;i--){
    body_[i].pos=body_[i-1].pos;
  }

  body_[0].pos=head_pos;
  return old_tail;
}


void Snake::grow(Pos old_pos,Color food){
  if(food==EMPTY||food==OUT_OF_BOUND){
    return;
  }
  body_.emplace_back(Segment(old_pos,food));
}


bool Snake::canMove(Direction dir){
  // 境界チェック
  const Pos head_pos=body_[0].pos+DIRS[(int)dir];
  if(head_pos.i<0 || head_pos.i>=stage_size_ ||
      head_pos.j<0 || head_pos.j>=stage_size_){
    return false;
  }

  // u-turnチェック
  if(body_.size()<2){
    return true;
  }

  return head_pos!=body_[1].pos;
}

std::vector<Segment> Snake::bite(){
  int iter=-1;
  // 二分探索の方がよさそう
  for(int i=1;i<body_.size()-1;i++){
    if(head().pos==body_[i].pos){
      iter=i;
      break;
    }
  }

  if(iter==-1){
    return {};
  }

  // 餌追加
  std::vector<Segment> dropped;
  for(int i=iter;i<body_.size();i++){
    dropped.emplace_back(body_[i]);
  }

  // 削除
  body_.erase(body_.begin()+iter+1,body_.end());
  return dropped;
}
