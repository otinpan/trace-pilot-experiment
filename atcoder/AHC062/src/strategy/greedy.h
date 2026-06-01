#pragma once
#include"strategy.h"

class Greedy: public Strategy{
  public:
// @trace-pilot 8df6e90bf6b89471b82eaeda517c4f1aa2bc3e1f
    Greedy(bool is_vertical=false);
    ~Greedy() override;

    std::vector<Pos> solve(State& state,Logger& logger) override;
  private:
    bool is_vertical_;
    std::vector<Pos> solve_zigzag(State& state,Logger& logger);
    std::vector<Pos> solve_zigzag_vertical(State& state,Logger& logger);
};
