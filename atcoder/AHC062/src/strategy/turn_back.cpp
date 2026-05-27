/*
(0,0)から出発して、(199,199)まで行き、同じようなパスをたどって帰ってくる
2行ずつ探索する
行きでは小さいスコアを取るマスを通る
(i,j) (i%2=0)からだと(i,j+1),(i+1,j)のスコアの小さい方を通る
帰りでは残っているマスを通る
*/
#include"turn_back.h"

TurnBack::TurnBack()
  :Strategy()
{

}

TurnBack::~TurnBack()=default;

std::vector<Pos> TurnBack::solve(State& state,Logger& logger){
  // @trace-pilot d6faf2958c2b47bf39f319dd534c576d17b29346 //////////////////////////////
//## `turn_back`でvertical(縦方向)の探索をCodexに作らせた
// @trace-pilot 21fbc68a09068f8675300a6509c8adee08226f48
  State horizontal_state=state;
  State vertical_state=state;

  std::vector<Pos> horizontal=solve_horizontal(horizontal_state,logger);
  std::vector<Pos> vertical=solve_vertical(vertical_state,logger);

  if(vertical_state.score()>horizontal_state.score()){
    state=vertical_state;
    return vertical;
  }

  state=horizontal_state;
  return horizontal;
}

std::vector<Pos> TurnBack::solve_vertical(State& state,Logger& logger){
  std::vector<Pos> res;
  res.emplace_back(state.pos());

  int left=state.kingdom()[1][0];
  int right=state.kingdom()[1][1];
  Pos next=left>right ? Pos(1,1) : Pos(1,0);
  Direction dir=get_direction(state.pos(),next);
  if(!state.apply(dir)){
    return res;
  }
  res.emplace_back(state.pos());
  for(int j=0;j<map_size;j+=2){
    while(true){
      Pos now=state.pos();
      int i=j%4==0 ? now.i+1 : now.i-1;
      assert(i>=1&&i<map_size-1);
      int left=state.kingdom()[i][j];
      int right=state.kingdom()[i][j+1];
      Pos next=left>right ? Pos(i,j+1) : Pos(i,j);

      if(i==map_size-2&&j%4==0){
        next=Pos(i,j+1);
      }
      if(i==1&&j%4!=0){
        next=Pos(i,j+1);
      }
      Direction dir=get_direction(now,next);
      if(!state.apply(dir)){
        return res;
      }
      res.emplace_back(state.pos());

      if(state.pos().i==map_size-2||state.pos().i==1){
        break;
      }
    }
    if(j+2>=map_size){
      break;
    }
    int i=j%4==0 ? map_size-2 : 1;
    Pos next=Pos(i,j+2);
    Direction dir=get_direction(state.pos(),next);
    if(!state.apply(dir)){
      return res;
    }
    res.emplace_back(state.pos());
  }

  if(state.pos()==Pos(1,map_size-1)){
    for(const Pos& next:{
      Pos(0,map_size-2),
      Pos(0,map_size-1),
      Pos(1,map_size-2)
    }){
      Direction dir=get_direction(state.pos(),next);
      if(!state.apply(dir)){
        return res;
      }
      res.emplace_back(state.pos());
    }
  }else if(state.pos()==Pos(map_size-2,map_size-1)){
    for(const Pos& next:{
      Pos(map_size-1,map_size-2),
      Pos(map_size-1,map_size-1),
      Pos(map_size-2,map_size-2)
    }){
      Direction dir=get_direction(state.pos(),next);
      if(!state.apply(dir)){
        return res;
      }
      res.emplace_back(state.pos());
    }
  }

  for(int j=map_size-2;j>=0;j-=2){
    while(true){
      Pos now=state.pos();
      int i=j%4==0 ? now.i-1 : now.i+1;
      assert(i>=0&&i<map_size);
      Pos next=state.kingdom()[i][j]!=-1 ? Pos(i,j) : Pos(i,j+1);
      if(i==0||i==map_size-1){
        next=Pos(i,j+1);
      }

      Direction dir=get_direction(now,next);
      if(!state.apply(dir)){
        return res;
      }
      res.emplace_back(state.pos());
      if(state.pos().i==0||state.pos().i==map_size-1){
        break;
      }
    }

    if(j==0){
      break;
    }
    while(true){
      if(!state.apply(Direction::LEFT)){
        return res;
      }
      res.emplace_back(state.pos());
      if(state.pos().j==j-2){
        break;
      }
    }
  }
  logger.log("score: "+std::to_string(state.score()));
  return res;
}

std::vector<Pos> TurnBack::solve_horizontal(State& state,Logger& logger){
  std::vector<Pos> res;
  res.emplace_back(state.pos());

  int up=state.kingdom()[0][1];
  int down=state.kingdom()[1][1];
  Pos next=up>down ? Pos(1,1) : Pos(0,1);
  Direction dir=get_direction(state.pos(),next);
// @trace-pilot 5604e62321fc0b2c541d210fe6e249bbb803c1c6
  if(!state.apply(dir)){
    return res;
  }
  res.emplace_back(state.pos());
  for(int i=0;i<map_size;i+=2){
    while(true){
      Pos now=state.pos();
      int j=i%4==0 ? now.j+1 : now.j-1;
      assert(j>=1&&j<map_size-1);
      int up=state.kingdom()[i][j];
      int down=state.kingdom()[i+1][j];
      Pos next=up>down ? Pos(i+1,j) : Pos(i,j);

// @trace-pilot 5604e62321fc0b2c541d210fe6e249bbb803c1c6
      if(j==map_size-2&&i%4==0){
        next=Pos(i+1,j);
      }
// @trace-pilot 5604e62321fc0b2c541d210fe6e249bbb803c1c6
      if(j==1&&i%4!=0){
        next=Pos(i+1,j);
      }
      Direction dir=get_direction(now,next);
// @trace-pilot 5604e62321fc0b2c541d210fe6e249bbb803c1c6
      if(!state.apply(dir)){
        return res;
      }
      res.emplace_back(state.pos());

      if(state.pos().j==map_size-2||state.pos().j==1){
        break;
      }
    }
// @trace-pilot 5604e62321fc0b2c541d210fe6e249bbb803c1c6
    if(i+2>=map_size){
      break;
    }
    int j=i%4==0 ? map_size-2 : 1;
    Pos next=Pos(i+2,j);
    Direction dir=get_direction(state.pos(),next);
// @trace-pilot 5604e62321fc0b2c541d210fe6e249bbb803c1c6
    if(!state.apply(dir)){
      return res;
    }
    res.emplace_back(state.pos());
  }

// @trace-pilot 6292e70ebdc98b67b2f5e04ebcfe01b2e7d7e79c //////////////////////////
// ## `turn_back`で未訪問のマスがあったため、Codexに修正させた
// @trace-pilot 463788e8703320cd86f6dcbf38868cdad42b2456
  if(state.pos()==Pos(map_size-1,1)){
    for(const Pos& next:{
      Pos(map_size-2,0),
      Pos(map_size-1,0),
      Pos(map_size-2,1)
    }){
      Direction dir=get_direction(state.pos(),next);
      if(!state.apply(dir)){
        return res;
      }
      res.emplace_back(state.pos());
    }
  }else if(state.pos()==Pos(map_size-1,map_size-2)){
    for(const Pos& next:{
      Pos(map_size-2,map_size-1),
      Pos(map_size-1,map_size-1),
      Pos(map_size-2,map_size-2)
    }){
      Direction dir=get_direction(state.pos(),next);
      if(!state.apply(dir)){
        return res;
      }
      res.emplace_back(state.pos());
    }
  }
  
  for(int i=map_size-2;i>=0;i-=2){
    while(true){
      Pos now=state.pos();
      int j=i%4==0 ? now.j-1 : now.j+1;
      assert(j>=0&&j<map_size);
      Pos next=state.kingdom()[i][j]!=-1 ? Pos(i,j) : Pos(i+1,j);
      if(j==0||j==map_size-1){
        next=Pos(i+1,j);
      }

      Direction dir=get_direction(now,next);
// @trace-pilot 5604e62321fc0b2c541d210fe6e249bbb803c1c6
      if(!state.apply(dir)){
        return res;
      }
      res.emplace_back(state.pos());
      if(state.pos().j==0||state.pos().j==map_size-1){
        break;
      }
    }

// @trace-pilot 5604e62321fc0b2c541d210fe6e249bbb803c1c6
    if(i==0){
      break;
    }
    while(true){
// @trace-pilot 5604e62321fc0b2c541d210fe6e249bbb803c1c6
      if(!state.apply(Direction::UP)){
        return res;
      }
      res.emplace_back(state.pos());
      if(state.pos().i==i-2){
        break;
      }
    }
  }
  logger.log("score: "+std::to_string(state.score()));
  return res;
}
