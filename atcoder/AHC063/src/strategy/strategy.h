#pragma once
#include<iostream>
#include<vector>
#include<random>

#include"../common.h"
#include"../state.h"
#include"../logger.h"
#include"../timer.h"

class Strategy{
  public:
    Strategy(const std::vector<Color>& ideal);
    virtual ~Strategy();

    virtual std::vector<char> solve(State& state,Logger& logger);

  protected:
    struct Candidate{
      State state;
      std::vector<char> operations;
    };
    Candidate createInitialCandidate(const State& state) const;
    Candidate createNextCandidate(const Candidate& current,Direction dir) const;
    Candidate createNextCandidateRandomly(const Candidate& current);

    int countTotFood(const Candidate& cand);
    std::vector<Color> ideal_;
    int score(const State& state,size_t operation_count) const;

    std::mt19937 rng_;

};
