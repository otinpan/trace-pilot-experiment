#pragma once
#include"strategy.h"

class Surround: public Strategy{
  public:
    Surround();
    ~Surround() override;

    std::vector<Pos> solve(State& state,Logger& logger) override;
  private:

// @trace-pilot 74ef05a827d5e6f9b0326ebce6ff9aaee0217f3e ////////////////////////
// ## `surround`の`solve`をCodexに実装してもらった
// @trace-pilot 1eadc07aa10d0526a249473eac1c1a4fd6cd7882
    struct SearchResult{
      long long score;
      Direction first_dir;
      bool found;
    };

    int depth_=2;
    SearchResult dfs(
      State& state,
      Logger& logger,
      Pos from,
      Pos left_top,
      Pos right_bottom,
      Direction pre_dir,
      int turn,
      int n_depth
    );

};
