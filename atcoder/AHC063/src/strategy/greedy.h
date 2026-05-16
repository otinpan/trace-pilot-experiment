#pragma once
#include<vector>

#include"../common.h"
#include"strategy.h"

class Greedy: public Strategy{
  public:
    Greedy(const std::vector<Color>& ideal);
    ~Greedy() override;

    std::vector<char> solve(State& state,Logger& logger) override;
};
