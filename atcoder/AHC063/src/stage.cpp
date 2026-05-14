#include"stage.h"

Stage::Stage(int n,std::vector<std::vector<int>> f)
  :size_(n)
  ,food_(n,std::vector<Color>(n,EMPTY))
{
  for(int i=0;i<size_;i++){
    for(int j=0;j<size_;j++){
      food_[i][j]=static_cast<Color>(f[i][j]);
    }
  }
}

Stage::~Stage(){

}

bool Stage::checkInStage(Pos pos) const{
  return 0<=pos.i && pos.i<size_ &&
    0<=pos.j && pos.j<size_;
}

Color Stage::removeFood(Pos pos){
  if(!checkInStage(pos)){
    return OUT_OF_BOUND;
  }

  Color c=food_[pos.i][pos.j];
  food_[pos.i][pos.j]=EMPTY;

  return c;
}

bool Stage::addFood(Segment food){
  if(!checkInStage(food.pos)){
    return false;
  }

  food_[food.pos.i][food.pos.j]=food.color;
  return true;
}

bool Stage::addFoods(const std::vector<Segment>& foods){
  for(const auto& food: foods){
    if(!checkInStage(food.pos)){
      return false;
    }
    food_[food.pos.i][food.pos.j]=food.color;
  }

  return true;
}
