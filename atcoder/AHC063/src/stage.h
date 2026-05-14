#pragma once
#include<iostream>
#include<vector>
#include"common.h"
#include"optional"

class Stage{
  public:
    Stage(int n,std::vector<std::vector<int>> f);
    ~Stage();

    bool checkInStage(Pos pos) const;
    Color removeFood(Pos pos);
    bool addFood(Segment food);
    bool addFoods(const std::vector<Segment>& foods);

  private:
    int size_;
    std::vector<std::vector<Color>> food_;

};
