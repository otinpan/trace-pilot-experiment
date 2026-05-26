#include"state.h"
#include"cassert"

State::State(std::vector<std::vector<int>> kingdom)
  :kingdom_(kingdom)
  ,init_kingdom_(kingdom)
  ,pos_(Pos(0,0))
  ,path_({})
  ,visited_({})
  ,score_(0)
  ,turn_(0)
{

  pos_=Pos(0,0);
  visited_.emplace_back(pos_);
}

State::~State()=default;

// 1ターン進め、スコアを加算
bool State::apply(Direction dir){
  Pos next_pos=pos_+DIRS[static_cast<int>(dir)];
  if(!next_pos.is_on_map()){
    return false;
  }

  turn_++;
  kingdom_[pos_.i][pos_.j]=-1;
  pos_=next_pos;
  score_+=(long long)turn_*kingdom_[pos_.i][pos_.j];

  path_.emplace_back(dir);
  visited_.emplace_back(next_pos);
  return true;
}

// 1ターン戻し、スコアを戻す
void State::undo(){
  assert(path_.size()!=0);
  assert(visited_.size()!=0);

  Direction pre_dir=path_.back();
  Pos pre_pos=pos_-DIRS[static_cast<int>(pre_dir)];
  assert(pre_pos.is_on_map());

  kingdom_[pos_.i][pos_.j]=init_kingdom_[pos_.i][pos_.j];
  score_-=(long long)turn_*kingdom_[pos_.i][pos_.j];
  pos_=pre_pos;
  visited_.pop_back();
  path_.pop_back();
  turn_--;
  return;
}
