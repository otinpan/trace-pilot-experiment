#include"strategy.h"

Strategy::Strategy(const std::vector<Color>& ideal)
  :ideal_(ideal)
  ,rng_(0)
{

}

Strategy::~Strategy() = default;

Strategy::Candidate Strategy::createInitialCandidate(const State& state) const{
  return Strategy::Candidate{state,{}};
}

Strategy::Candidate Strategy::createNextCandidate(
    const Strategy::Candidate& current,
    Direction dir
) const{
  Strategy::Candidate next=current;
  next.state.apply(dir);
  next.operations.emplace_back(OUTPUT_DIR[(int)dir]);
  return next;
}

Strategy::Candidate Strategy::createNextCandidateRandomly(
  const Candidate& current
){
  Direction dir;
  while(true){
    dir=static_cast<Direction>(rng_()%4);
    if(current.state.snake().canMove(dir)){
      break;
    }
  }

  return createNextCandidate(current,dir);
}



std::vector<char> Strategy::solve(State& state,Logger& logger){
  (void)state;
  (void)logger;
  return {};
}

int Strategy::score(const State& state,size_t operation_count) const{
  int error_count=0;

  const int m=ideal_.size();
  const int k=state.snake().size();

  for(int i=0;i<k;i++){
    if(state.snake().body()[i].color!=ideal_[i]){
      error_count++;
    }
  }
  return static_cast<int>(operation_count)+10000*(error_count+2*(m-k));
}
