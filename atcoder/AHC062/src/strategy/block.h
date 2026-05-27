#pragma once
#include"strategy.h"

class Block: public Strategy{
  public:
    Block();
    ~Block() override;

    struct Segment{
      int sum;
    };
    std::vector<Pos> solve(State& state,Logger& logger) override;
  private:
    int block_size_;

    std::vector<std::vector<Segment>> block;
};