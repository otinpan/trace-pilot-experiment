#pragma once
#include<iostream>
#include<vector>
#include<random>
#include<cassert>

#include"../common.h"
#include"../state.h"
#include"../logger.h"
#include"../timer.h"

class Strategy{
  public:
    Strategy();
    virtual ~Strategy();

    virtual std::vector<Pos> solve(State& state,Logger& logger);

  protected:
    // posから[left,right) [top,bottom)の区間でdirの方向に進んだ時のスコアを求める
    long long score_straight(
      const State& state,
      Pos left_top,
      Pos right_bottom,
      Logger& logger,
      Pos& pos,
      Direction dir,
      int& turn
    );
    std::mt19937 rng_;
};
