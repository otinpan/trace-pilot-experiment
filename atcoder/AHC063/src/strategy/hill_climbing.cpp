#include"hill_climbing.h"
#include<algorithm>
#include<cmath>
#include"../timer.h"

HillClimbing::HillClimbing(const std::vector<Color>& ideal)
  :Strategy(ideal)
{

}

HillClimbing::~HillClimbing()=default;


// @trace-pilot 38ca90aaeab836014da7331a89f6af01df39abd5
bool HillClimbing::shouldAccept(int current_score,int new_score,double progress){
  if(new_score<=current_score){
    return true;
  }

  const double temperature=std::max(1e-6,1.0-progress);
  const double acceptance_threshold=std::exp(
      static_cast<double>(current_score-new_score)/(15000.0*temperature)
  );
  return std::generate_canonical<double,10>(rng_)<acceptance_threshold;
}

std::vector<char> HillClimbing::solve(State& state,Logger& logger){
  return solveSearch(state,logger);
  //return solveRandomly(state,logger);
}

std::vector<char> HillClimbing::solveRandomly(State& state,Logger& logger){
  Timer timer;
  logger.log("start: time = "+std::to_string(timer.elapsed()));

  Candidate current=createInitialCandidate(state);
  Candidate best=current;
  int current_score=score(current.state,current.operations.size());
  int best_score=current_score;
  int accepted_step=0;


  while(timer.elapsed()<TIME_LIMIT){
    Candidate next=createNextCandidateRandomly(current);
    const int new_score=score(next.state,next.operations.size());
    const double progress=timer.elapsed()/TIME_LIMIT;
    if(!shouldAccept(current_score,new_score,progress)){
      continue;
    }

    accepted_step++;
    current=std::move(next);
    current_score=new_score;
    logger.log("time: "+std::to_string(timer.elapsed()));
    logger.log("score: "+std::to_string(best_score));
    logger.log(best.state,accepted_step);

    if(new_score<best_score){
      best=current;
      best_score=new_score;
    }
  }

  state=best.state;
  logger.log("final score: "+std::to_string(best_score));
  return best.operations;
}

// @trace-pilot ee154eb35ab515332034218ba9387f427f5cb110
std::vector<char> HillClimbing::solveSearch(State& state,Logger& logger){
  Timer timer;
  logger.log("start: time = "+std::to_string(timer.elapsed()));

  Candidate current=createInitialCandidate(state);
  Candidate best=current;
  int best_score=score(best.state,best.operations.size());

  while(timer.elapsed()<TIME_LIMIT){
    bool found=false;
    Candidate best_next=current;
    int best_next_score=0;

    for(Direction dir : {
        Direction::UP,
        Direction::DOWN,
        Direction::LEFT,
        Direction::RIGHT
    }){
      if(!current.state.snake().canMove(dir)){
        continue;
      }

      Candidate next=createNextCandidate(current,dir);
      const int next_score=score(next.state,next.operations.size());
      if(!found || next_score<best_next_score){
        found=true;
        best_next=std::move(next);
        best_next_score=next_score;
      }
    }

    if(!found){
      break;
    }

    current=std::move(best_next);
    if(best_next_score<best_score){
      best=current;
      best_score=best_next_score;
      logger.log("time: "+std::to_string(timer.elapsed()));
      logger.log("score: "+std::to_string(best_score));
      logger.log(best.state,best.operations.size());
    }
  }

  state=best.state;
  logger.log("final score: "+std::to_string(best_score));
  return best.operations;
}
