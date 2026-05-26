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
    std::mt19937 rng_;
    int score(const State& state) const;
};
