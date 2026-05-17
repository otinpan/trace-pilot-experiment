#include"beam_search.h"

BeamSearch::BeamSearch(const std::vector<Color>& ideal,ExperimentLogger& experiment_logger)
  :Strategy(ideal)
  ,experiment_logger_(experiment_logger)
  ,beam_width_(10)
{

}


BeamSearch::~BeamSearch()=default;


std::vector<char> BeamSearch::solve(State& state,Logger& logger){
  Timer timer;
  std::vector<std::pair<int,Candidate>> beam;
  Candidate init_cand=createInitialCandidate(state);
  int init_score=score(state,init_cand.operations.size());
  beam.emplace_back(std::make_pair(init_score,init_cand));

  int step=0;
  std::vector<std::pair<int,Candidate>> next_cands;
  int init_counter=countTotFood(init_cand);
  while(timer.elapsed()<TIME_LIMIT){
    next_cands.clear();
    step++;
    for(const auto& b:beam){
      for(Direction dir:{
        Direction::UP,
        Direction::RIGHT,
        Direction::DOWN,
        Direction::LEFT
      }){
        if(!b.second.state.snake().canMove(dir)){
          continue;
        }
        Candidate next_cand=createNextCandidate(b.second,dir);
        int next_score=score(next_cand.state,next_cand.operations.size());
        next_cands.emplace_back(std::make_pair(next_score,next_cand));
      }
    }

    std::sort(next_cands.begin(),next_cands.end(),
        [](const auto& a,const auto& b){
        return a.first<b.first;
    });

    if(next_cands.size()>static_cast<size_t>(beam_width_)){
      next_cands.erase(next_cands.begin()+beam_width_,next_cands.end());
    }

    logger.log("next cands size: "+std::to_string(next_cands.size())+'\n');
    for(const auto& c:next_cands){
      int counter=countTotFood(c.second);
      logger.log("time: "+std::to_string(timer.elapsed()));
      logger.log("score: "+std::to_string(c.first));
      logger.log("m: "+std::to_string(ideal_.size())+", t: "+std::to_string(c.second.state.snake().size()));
      logger.log(c.second.state,step);
      logger.log("current_counter: "+std::to_string(counter));
      assert(init_counter==counter);
    }

    beam=next_cands;
  }

  Candidate& best=beam[0].second;
  int best_score=beam[0].first;

  logger.log("final score: "+std::to_string(best_score));
  experiment_logger_.logBeamResult(beam_width_,best_score);
  return best.operations;
}
