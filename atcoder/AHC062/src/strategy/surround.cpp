// @trace-pilot b6bef543946e6eb44b6ffb6145bb811e0c845f27
// Focused map
#include"surround.h"

// @trace-pilot 0232a54618a1e1d058f6147882aad590716ac605
std::pair<Pos,Pos> solve_next_block(
  const Direction& pre_dir,
  const Pos& pre_left_top,
  const Pos& pre_right_bottom
);

Direction solve_turn_direction(
  Pos& pos,
  const Pos& left_top,
  const Pos& right_bottom,
  const Direction pre_dir
);

// @trace-pilot 1eadc07aa10d0526a249473eac1c1a4fd6cd7882
Direction opposite_direction(Direction dir);

Surround::Surround()
  :Strategy()
  ,depth_(11)
{

}

Surround::~Surround()=default;

std::vector<Pos> Surround::solve(State& state,Logger& logger){
  std::vector<Pos> result;
  logger.log(state);
  result.emplace_back(state.pos());

  Pos left_top(0,0);
  Pos right_bottom(map_size,map_size);
  Direction pre_dir=Direction::UP;

  while(true){
    SearchResult search=dfs(
      state,
      logger,
      state.pos(),
      left_top,
      right_bottom,
      pre_dir,
      state.turn(),
      0
    );
    if(!search.found){
      break;
    }


    while(true){
      Pos next=state.pos()+DIRS[static_cast<int>(search.first_dir)];
      if(!next.is_on_block(left_top,right_bottom)){
        break;
      }
      if(!state.apply(search.first_dir)){
        return result;
      }
      result.emplace_back(state.pos());
    }

    bool can_turn=false;
    Direction turn_dir=Direction::UP;
    for(Direction dir:{
      Direction::UP,
      Direction::DOWN,
      Direction::RIGHT,
      Direction::LEFT
    }){
// @trace-pilot 1eadc07aa10d0526a249473eac1c1a4fd6cd7882
      if(dir==opposite_direction(search.first_dir))continue;

      Pos next=state.pos()+DIRS[static_cast<int>(dir)];
      if(next.is_on_block(left_top,right_bottom)){
        turn_dir=dir;
        can_turn=true;
        break;
      }
    }

    if(!can_turn){
      break;
    }

    if(!state.apply(turn_dir)){
      return result;
    }
    result.emplace_back(state.pos());
    logger.log(state);

    std::pair<Pos,Pos> next_block=solve_next_block(
      turn_dir,
      left_top,
      right_bottom
    );
    left_top=next_block.first;
    right_bottom=next_block.second;
    pre_dir=turn_dir;
  }

  return result;
}

Surround::SearchResult Surround::dfs(
  State& state,
  Logger& logger,
  Pos pos,
  Pos left_top,
  Pos right_bottom,
  Direction pre_dir,
  int turn,
  int n_depth
){
  //logger.log("pos: ("+std::to_string(pos.i)+","+std::to_string(pos.j)+")\n");
  //logger.log("dir: "+std::to_string(static_cast<int>(pre_dir)));
// @trace-pilot 0232a54618a1e1d058f6147882aad590716ac605
  (void)pre_dir;
  if(n_depth==depth_){
    return SearchResult{0,Direction::UP,false};
  }

  SearchResult best{0,Direction::UP,false};
  for(Direction dir:{
    Direction::UP,
    Direction::DOWN,
    Direction::RIGHT,
    Direction::LEFT
  }){
    Pos next=pos+DIRS[static_cast<int>(dir)];
    if(!next.is_on_block(left_top,right_bottom)){
      continue;
    }

    Pos n_pos=pos;
    int n_turn=turn;
    long long line_score=score_straight(
      state,
      left_top,
      right_bottom,
      logger,
      n_pos,
      dir,
      n_turn
    );

// @trace-pilot 0232a54618a1e1d058f6147882aad590716ac605
    bool can_turn=false;
    for(Direction next_dir:{
      Direction::UP,
      Direction::DOWN,
      Direction::RIGHT,
      Direction::LEFT
    }){
// @trace-pilot 1eadc07aa10d0526a249473eac1c1a4fd6cd7882
      if(next_dir==opposite_direction(dir))continue;

      Pos turn_next=n_pos+DIRS[static_cast<int>(next_dir)];
      if(turn_next.is_on_block(left_top,right_bottom)){
        can_turn=true;
        break;
      }
    }

    long long candidate=line_score;
    if(!can_turn){
      if(!best.found || candidate>best.score){
        best=SearchResult{candidate,dir,true};
      }
      continue;
    }

    // 曲がる
    Direction turn_dir=solve_turn_direction(
      n_pos,
      left_top,
      right_bottom,
      dir
    );
    
    // 曲がっただけscore
    n_turn++;
    line_score+=(long long)n_turn*state.kingdom()[n_pos.i][n_pos.j];

    
    // 次の区画を求める
    std::pair<Pos,Pos> next_block=solve_next_block(
      turn_dir,
      left_top,
      right_bottom
    );

// @trace-pilot 0232a54618a1e1d058f6147882aad590716ac605
    SearchResult child=dfs(
      state,
      logger,
      n_pos,
      next_block.first,
      next_block.second,
      turn_dir,
      n_turn,
      n_depth+1
    );

    candidate=line_score;
    if(child.found){
      candidate+=child.score;
    }

// @trace-pilot 0232a54618a1e1d058f6147882aad590716ac605
    if(!best.found || candidate>best.score){
      best=SearchResult{candidate,dir,true};
    }
  }

// @trace-pilot 0232a54618a1e1d058f6147882aad590716ac605
  return best;
}

std::pair<Pos,Pos> solve_next_block(
  const Direction& pre_dir,
  const Pos& pre_left_top,
  const Pos& pre_right_bottom
){
  switch(pre_dir){
    case Direction::UP:
      return std::make_pair(pre_left_top,pre_right_bottom+Pos(-1,0));
    case Direction::DOWN:
      return std::make_pair(pre_left_top+Pos(1,0),pre_right_bottom);
    case Direction::RIGHT:
      return std::make_pair(pre_left_top+Pos(0,1),pre_right_bottom);
    case Direction::LEFT:
      return std::make_pair(pre_left_top,pre_right_bottom+Pos(0,-1));
    default:
      assert(0);
// @trace-pilot 0232a54618a1e1d058f6147882aad590716ac605
      return std::make_pair(pre_left_top,pre_right_bottom);
  }
}

Direction solve_turn_direction(
  Pos& pos,
  const Pos& left_top,
  const Pos& right_bottom,
  const Direction pre_dir
){
  for(Direction dir:{
    Direction::UP,
    Direction::DOWN,
    Direction::RIGHT,
    Direction::LEFT
  }){
    Pos next=pos+DIRS[(int)dir];
    if(!next.is_on_block(left_top,right_bottom)){
      continue;
    }
// @trace-pilot 1eadc07aa10d0526a249473eac1c1a4fd6cd7882
    if(dir==opposite_direction(pre_dir)){
      continue;
    }
    pos=next;
    return dir;
  }

  assert(0);
// @trace-pilot 0232a54618a1e1d058f6147882aad590716ac605
  return Direction::UP;
}

// @trace-pilot 1eadc07aa10d0526a249473eac1c1a4fd6cd7882
Direction opposite_direction(Direction dir){
  switch(dir){
    case Direction::UP:
      return Direction::DOWN;
    case Direction::DOWN:
      return Direction::UP;
    case Direction::RIGHT:
      return Direction::LEFT;
    case Direction::LEFT:
      return Direction::RIGHT;
    default:
      assert(0);
      return Direction::UP;
  }
}
