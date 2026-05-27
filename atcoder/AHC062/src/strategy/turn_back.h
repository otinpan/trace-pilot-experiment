#pragma once
#include"strategy.h"

class TurnBack: public Strategy{
  public:
    TurnBack();
    ~TurnBack() override;

    std::vector<Pos> solve(State& state,Logger& logger) override;
  private:
    std::vector<Pos> solve_vertical(State& state,Logger& logger);
    std::vector<Pos> solve_horizontal(State& state,Logger& logger);
};