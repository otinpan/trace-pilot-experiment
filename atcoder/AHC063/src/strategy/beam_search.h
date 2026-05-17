// @trace-pilot 1c2e4aaf1c379243a81a97cf98a4c30d71f4785c
// ビームサーチ

// @trace-pilot 5874311e961bcba1302d77e1148df8ff36fd84d3
/* 
beamwidthが小さい
軽い
高速
局所解に弱い

beamwidth が大きい
重い
未来を広く見られる
*/
#pragma once
#include<cassert>
#include<algorithm>

#include"strategy.h"
#include"../experiment_logger.h"

class BeamSearch: public Strategy{
  public:
    BeamSearch(const std::vector<Color>& ideal,ExperimentLogger& experiment_logger);
    ~BeamSearch() override;

    std::vector<char> solve(State& state,Logger& logger) override;

    void setBeamWidth(int width){beam_width_=width;}
    int getBeamWidth() const{return beam_width_;}
  private:
    ExperimentLogger& experiment_logger_;
    int beam_width_;
};
