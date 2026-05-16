// @trace-pilot c1445e214f10d833b08b849b0b3a9f0b22cdc602
// 焼きなまし法
#pragma once
#include<random>

// @trace-pilot c041b61f1898609dde303ca4926e67b605ec94da
#include"../experiment_logger.h"
#include"strategy.h"

class SimulatedAnnealing: public Strategy{
  public:
    SimulatedAnnealing(
// @trace-pilot c041b61f1898609dde303ca4926e67b605ec94da
        const std::vector<Color>& ideal,
        ExperimentLogger& experiment_logger
    );
    ~SimulatedAnnealing() override;

    std::vector<char> solve(State& state,Logger& logger) override;

  private:
    std::vector<char> solveRandomly(State& state,Logger& logger);
    bool shouldAccept(int current_score,int new_score,double temperature);

// @trace-pilot c041b61f1898609dde303ca4926e67b605ec94da
    ExperimentLogger& experiment_logger_;
    std::mt19937 rng_;
    double start_temp_;
    double end_temp_;
};
