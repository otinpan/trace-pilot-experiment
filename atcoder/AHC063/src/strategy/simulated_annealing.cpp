// @trace-pilot e9e65d11e7593de7a47e0920c692b051eb3f1dc2
#include"simulated_annealing.h"
#include<algorithm>
#include<cmath>
#include<cassert>

// @trace-pilot c041b61f1898609dde303ca4926e67b605ec94da
SimulatedAnnealing::SimulatedAnnealing(
    const std::vector<Color>& ideal,
    ExperimentLogger& experiment_logger
)
  :Strategy(ideal)
  // @trace-pilot c041b61f1898609dde303ca4926e67b605ec94da
  ,experiment_logger_(experiment_logger)
  ,rng_(0)
  // @trace-pilot d2354c8817ce16b96762184960760fb0ccfe23b4
  //40000	10	92129	1.95002	2129	29	0
  // in/0000.txtでスコアが高いものを選んだ
  ,start_temp_(40000.0)
  ,end_temp_(10.0)
{

}

SimulatedAnnealing::~SimulatedAnnealing()=default;


bool SimulatedAnnealing::shouldAccept(
    int current_score,
    int new_score,
    double temperature
){
  if(new_score<=current_score){
    return true;
  }

  const double safe_temperature=std::max(1e-6,temperature);
  const double probability=std::exp(
      static_cast<double>(current_score-new_score)/safe_temperature
  );
  return std::generate_canonical<double,10>(rng_)<probability;
}

std::vector<char> SimulatedAnnealing::solve(State& state,Logger& logger){
  return solveRandomly(state,logger);
}

std::vector<char> SimulatedAnnealing::solveRandomly(State& state,Logger& logger){
  Timer timer;
  logger.log("start: time = "+std::to_string(timer.elapsed()));

  Candidate current=createInitialCandidate(state);
  Candidate best=current;
  int current_score=score(current.state,current.operations.size());
  int best_score=current_score;

  int initial_counter=countTotFood(current);
  logger.log("initial_counter: "+std::to_string(initial_counter));
  int accepted_step=0;
  while(timer.elapsed()<TIME_LIMIT){
    Candidate next=createNextCandidateRandomly(current);
    const int next_score=score(next.state,next.operations.size());

    const double progress=timer.elapsed()/TIME_LIMIT;
    const double temperature=
      start_temp_+(end_temp_-start_temp_)*progress;

    if(!shouldAccept(current_score,next_score,temperature)){
      continue;
    }

    accepted_step++;
    current=std::move(next);
    current_score=next_score;
    int counter=countTotFood(current);
    logger.log("time: "+std::to_string(timer.elapsed()));
    logger.log("score: "+std::to_string(best_score));
    logger.log("m: "+std::to_string(ideal_.size())+", t: "+std::to_string(current.state.snake().size()));
    logger.log(current.state,accepted_step);
    logger.log("current_counter: "+std::to_string(counter));

    assert(counter==initial_counter);

    if(current_score<best_score){
      best=current;
      best_score=current_score;
    }
  }

  state=best.state;
  logger.log("final score: "+std::to_string(best_score));
// @trace-pilot c041b61f1898609dde303ca4926e67b605ec94da
  experiment_logger_.logSaResult(
      start_temp_,
      end_temp_,
      best_score,
      timer.elapsed(),
      static_cast<int>(best.operations.size()),
      static_cast<int>(best.state.snake().size()),
      0
  );
  return best.operations;
}
