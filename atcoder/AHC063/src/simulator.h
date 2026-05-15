#pragma once
#include<iostream>
#include<vector>

#include"common.h"
#include"logger.h"
#include"state.h"

class Simulator{
  public:
    Simulator(State state,Logger& logger,const std::vector<Color> d);
    ~Simulator();

    // 次のステップの方向決定
    Direction decide();

    // 答えを求める
    void solve();

    // score計算
    int score();

    const std::vector<char>& operation_row() const{return operation_row_;}
  private:
    State state_;
    Logger& logger_;
    std::vector<char> operation_row_;
    std::vector<Color> ideal_snake_;
};
