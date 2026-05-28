#pragma once
#include"strategy.h"

class BlockSearch: public Strategy{
  public:
    BlockSearch();
    ~BlockSearch() override;

    std::vector<Pos> solve(State& state,Logger& logger) override;
  private:
    // ある頂点から任意の頂点までの最適経路
    struct BestBlockPaths{
      std::vector<std::vector<Direction>> paths;
      std::vector<long long> scores;
    };

    // block_size_ x block_sizeの領域
    // block[i][j].best_paths[0]なら(i,j)から左上までのベストなパス
    struct Block{
      int sum;
      // (i,j)からの各頂点へのベストな道のり
      std::vector<std::vector<BestBlockPaths>> best_paths;
    };

    void create_blocks(const State& state,Logger& logger);
    long long solve_block_score(
      const State& state,
      Logger& logger,
      Pos left_top
    );

    // 各マスから各マスまでのベストなパスを求める
    std::vector<std::vector<BestBlockPaths>> solve_best_paths_each(
      const State& state,
      Logger& logger,
      Pos left_top
    );

    // 各マスから任意のマスへの最適経路を求める
    BestBlockPaths solve_best_paths_from_start(
      const std::vector<std::vector<int>>& g,
      Pos start
    );

    std::vector<Pos> solve_block_path();
    
    std::vector<Pos> solve_best_path(
      State& state,
      Logger& logger,
      const std::vector<Pos>& block_path
    );

    Pos select_best_square(
      Pos rel_pos,
      Pos block_pos,
      Direction dir
    );
    int block_size_;
    std::vector<std::vector<Block>> blocks_;
};
