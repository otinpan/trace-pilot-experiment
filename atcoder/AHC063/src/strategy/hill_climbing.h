// @trace-pilot 9d41e4e8a2a8ae4ab0d58ac9cdc0b46700451b83
// 山登り法
#pragma once
#include<random>

#include"strategy.h"


class HillClimbing: public Strategy{
  public:
    HillClimbing(const std::vector<Color>& ideal);
    ~HillClimbing() override;

    std::vector<char> solve(State& state,Logger& logger) override;
  private:
    std::vector<char> solveRandomly(State& state,Logger& logger);
    std::vector<char> solveSearch(State& state,Logger& logger);

    bool shouldAccept(int current_score,int new_score,double progress);

};
