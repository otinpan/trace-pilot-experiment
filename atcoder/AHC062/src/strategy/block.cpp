// @trace-pilot 4704197afcd17be72efe1e08058ade1de435003a
// Focused map
#include"block.h"

BlockSearch::BlockSearch()
  :Strategy()
  ,block_size_(2)
{
  assert(map_size%block_size_==0);
  int bs=map_size/block_size_;
  assert(bs>=1);
  assert(bs==1||bs%2==0);
  blocks_.resize(bs);
  for(auto& b:blocks_){
    b.resize(bs);
  }

}

BlockSearch::~BlockSearch()=default;


void BlockSearch::create_blocks(const State& state,Logger& logger){
  for(int i=0;i<map_size;i+=block_size_){
    for(int j=0;j<map_size;j+=block_size_){
      Pos left_top=Pos(i,j);
      long long s=solve_block_score(state,logger,left_top);
      // block内の各頂点から各頂点までの最適経路
      auto best_paths=solve_best_paths_each(state,logger,left_top);
      int bi=i/block_size_;
      int bj=j/block_size_;
      blocks_[bi][bj].sum=s;
      blocks_[bi][bj].best_paths=best_paths;
    }
  }
}

// block内の総和を求める
long long BlockSearch::solve_block_score(
  const State& state,
  Logger& logger,
  Pos left_top
){
  long long result=0;
  for(int i=0;i<block_size_;i++){
    for(int j=0;j<block_size_;j++){
      result+=state.kingdom()[left_top.i+i][left_top.j+j];
    }
  }
  return result;
}

// ブロック内の各マスから最適経路を求める
auto BlockSearch::solve_best_paths_each(
  const State& state,
  Logger& logger,
  Pos left_top
) -> std::vector<std::vector<BestBlockPaths>>{
  std::vector<std::vector<BestBlockPaths>> result(
    block_size_,
    std::vector<BestBlockPaths>(block_size_)
  );

  std::vector<std::vector<int>> g(block_size_,std::vector<int>(block_size_));
  for(int i=0;i<block_size_;i++){
    for(int j=0;j<block_size_;j++){
      g[i][j]=state.kingdom()[left_top.i+i][left_top.j+j];
    }
  }

  for(int i=0;i<block_size_;i++){
    for(int j=0;j<block_size_;j++){
      // 外側意外のときはいらない
      if(i!=0 && i!=block_size_-1
        && j!=0 && j!=block_size_-1){
          continue;
        }
      BestBlockPaths best_paths_from_start=
        solve_best_paths_from_start(
        g,
        Pos(i,j)
      );
      result[i][j]=best_paths_from_start;
    }
  }

  return result;
}

// ブロック内の位置startから、各マスへの最適経路を求める
auto BlockSearch::solve_best_paths_from_start(
    const std::vector<std::vector<int>>& g,
    Pos start
) -> BestBlockPaths{
  using ll=long long;
  using namespace std;
  BestBlockPaths result;
  int n=g.size();
  int tot=n*n;
  result.paths.resize(n*n);
  result.scores.resize(n*n,-1);

// @trace-pilot a6def93c0f5e4752bed81b9463acca453f4cd73b
  vector<ll> best_score(tot,-1);
  vector<vector<bool>> used(n,vector<bool>(n,false));
  vector<Direction> path;

// @trace-pilot a6def93c0f5e4752bed81b9463acca453f4cd73b
  auto dfs=[&](auto&& self,Pos pos,int turn,ll score)->void{
    if(turn==tot-1){
      int id=pos.i*n+pos.j;
      if(score>best_score[id]){
        best_score[id]=score;
        result.paths[id]=path;
        result.scores[id]=score;
      }
      return;
    }

    for(int d=0;d<static_cast<int>(DIRS.size());d++){
      Pos next=pos+DIRS[d];
      if(next.i<0 || next.i>=n || next.j<0 || next.j>=n){
        continue;
      }
      if(used[next.i][next.j]){
        continue;
      }

      used[next.i][next.j]=true;
      path.emplace_back(static_cast<Direction>(d));

      int next_turn=turn+1;
      ll next_score=score+1LL*next_turn*g[next.i][next.j];
      self(self,next,next_turn,next_score);

      path.pop_back();
      used[next.i][next.j]=false;
    }
  };

  used[start.i][start.j]=true;
  dfs(dfs,start,0,0);

  return result;
}

// blocksの経路を求める
// @trace-pilot 211ce63df747156813362dc12d3ada14c54f3b1f
std::vector<Pos> BlockSearch::solve_block_path(){
  using namespace std;
  int b=map_size/block_size_;

  auto block_sum=[&](Pos p,bool transpose)->int{
    if(transpose){
      return blocks_[p.j][p.i].sum;
    }
    return blocks_[p.i][p.j].sum;
  };

  auto to_real_pos=[&](Pos p,bool transpose)->Pos{
    if(transpose){
      return Pos(p.j,p.i);
    }
    return p;
  };

  auto solve_horizontal_like=[&](bool transpose)->vector<Pos>{
    vector<Pos> virtual_path;
    vector<vector<bool>> visited(b,vector<bool>(b,false));

    auto push=[&](Pos p){
      assert(p.i>=0&&p.i<b&&p.j>=0&&p.j<b);
      assert(!visited[p.i][p.j]);
      virtual_path.emplace_back(p);
      visited[p.i][p.j]=true;
    };

    Pos now(0,0);
    push(now);

    if(b==1){
      vector<Pos> result;
      result.emplace_back(to_real_pos(virtual_path[0],transpose));
      return result;
    }

    if(b==2){
      Pos a(0,1);
      Pos c(1,0);
      if(block_sum(a,transpose)>block_sum(c,transpose)){
        push(c);
        push(Pos(1,1));
        push(a);
      }else{
        push(a);
        push(Pos(1,1));
        push(c);
      }

      vector<Pos> result;
      for(Pos p:virtual_path){
        result.emplace_back(to_real_pos(p,transpose));
      }
      return result;
    }

    int up=block_sum(Pos(0,1),transpose);
    int down=block_sum(Pos(1,1),transpose);
    now=up>down ? Pos(1,1) : Pos(0,1);
    push(now);

    for(int i=0;i<b;i+=2){
      while(true){
        int j=i%4==0 ? now.j+1 : now.j-1;
        assert(j>=1&&j<b-1);
        int up=block_sum(Pos(i,j),transpose);
        int down=block_sum(Pos(i+1,j),transpose);
        Pos next=up>down ? Pos(i+1,j) : Pos(i,j);

        if(j==b-2&&i%4==0){
          next=Pos(i+1,j);
        }
        if(j==1&&i%4!=0){
          next=Pos(i+1,j);
        }

        now=next;
        push(now);

        if(now.j==b-2||now.j==1){
          break;
        }
      }

      if(i+2>=b){
        break;
      }

      int j=i%4==0 ? b-2 : 1;
      now=Pos(i+2,j);
      push(now);
    }

    if(now==Pos(b-1,1)){
      for(Pos next:{
        Pos(b-2,0),
        Pos(b-1,0),
        Pos(b-2,1)
      }){
        now=next;
        push(now);
      }
    }else if(now==Pos(b-1,b-2)){
      for(Pos next:{
        Pos(b-2,b-1),
        Pos(b-1,b-1),
        Pos(b-2,b-2)
      }){
        now=next;
        push(now);
      }
    }

    for(int i=b-2;i>=0;i-=2){
      while(true){
        int j=i%4==0 ? now.j-1 : now.j+1;
        assert(j>=0&&j<b);
        Pos next=!visited[i][j] ? Pos(i,j) : Pos(i+1,j);
        if(j==0||j==b-1){
          next=Pos(i+1,j);
        }

        now=next;
        push(now);

        if(now.j==0||now.j==b-1){
          break;
        }
      }

      if(i==0){
        break;
      }

      while(now.i!=i-2){
        now=Pos(now.i-1,now.j);
        push(now);
      }
    }

    assert(static_cast<int>(virtual_path.size())==b*b);
    vector<Pos> result;
    result.reserve(virtual_path.size());
    for(Pos p:virtual_path){
      result.emplace_back(to_real_pos(p,transpose));
    }
    return result;
  };

  auto calc_score=[&](const vector<Pos>& path)->long long{
    long long result=0;
    for(int turn=0;turn<static_cast<int>(path.size());turn++){
      Pos p=path[turn];
      result+=1LL*turn*blocks_[p.i][p.j].sum;
    }
    return result;
  };

  vector<Pos> horizontal=solve_horizontal_like(false);
  vector<Pos> vertical=solve_horizontal_like(true);
  if(calc_score(vertical)>calc_score(horizontal)){
    return vertical;
  }
  return horizontal;
}

std::vector<Pos> BlockSearch::solve_best_path(
  State& state,
  Logger& logger,
  const std::vector<Pos>& block_path)
{
  std::vector<Pos> result;
  result.emplace_back(state.pos());
  if(block_path.empty()){
    return result;
  }

  Pos n_block=block_path[0];
  for(int i=1;i<static_cast<int>(block_path.size());i++){
    Pos nx_block=block_path[i];
    Direction block_dir=get_direction(n_block,nx_block);
    Pos pos=state.pos();
    Pos rel_pos=Pos(pos.i%block_size_,pos.j%block_size_); // block内から見た位置
    Pos dist_pos=select_best_square(rel_pos,n_block,block_dir);
    int dist_pos_1_dim=dist_pos.i*block_size_+dist_pos.j;
    const std::vector<Direction>& dirs=
      blocks_[n_block.i][n_block.j]
        .best_paths[rel_pos.i][rel_pos.j]
        .paths[dist_pos_1_dim];
    for(auto& dir:dirs){
      if(!state.apply(dir)){
        return result;
      }
      result.emplace_back(state.pos());
    }

    if(!state.apply(block_dir)){
      return result;
    }
    result.emplace_back(state.pos());
    n_block=nx_block;
  }

  Pos pos=state.pos();
  Pos rel_pos=Pos(pos.i%block_size_,pos.j%block_size_);
  const BestBlockPaths& best_paths=
    blocks_[n_block.i][n_block.j].best_paths[rel_pos.i][rel_pos.j];

  int best_id=0;
  for(int id=1;id<static_cast<int>(best_paths.scores.size());id++){
    if(best_paths.scores[id]>best_paths.scores[best_id]){
      best_id=id;
    }
  }

  const std::vector<Direction>& dirs=best_paths.paths[best_id];
  for(auto& dir:dirs){
    if(!state.apply(dir)){
      return result;
    }
    result.emplace_back(state.pos());
  }

  return result;
}

Pos BlockSearch::select_best_square(
  Pos rel_pos,
  Pos n_block,
  Direction dir
){
  const Block& block=blocks_[n_block.i][n_block.j];
  const BestBlockPaths& best_paths=block.best_paths[rel_pos.i][rel_pos.j];
  long long best_score=-1;
  Pos best_dist=rel_pos;

  auto update=[&](Pos candidate){
    int id=candidate.i*block_size_+candidate.j;
    assert(id>=0&&id<static_cast<int>(best_paths.scores.size()));
    long long score=best_paths.scores[id];
    if(score>best_score){
      best_score=score;
      best_dist=candidate;
    }
  };

  switch(dir){
    case Direction::UP:
      for(int j=0;j<block_size_;j++){
        update(Pos(0,j));
      }
      break;
// @trace-pilot c5dee3c42cf42753ed51299d5ba589520193fcdd
    case Direction::DOWN:
      for(int j=0;j<block_size_;j++){
        update(Pos(block_size_-1,j));
      }
      break;
    case Direction::LEFT:
      for(int i=0;i<block_size_;i++){
        update(Pos(i,0));
      }
      break;
    case Direction::RIGHT:
      for(int i=0;i<block_size_;i++){
        update(Pos(i,block_size_-1));
      }
      break;
    case Direction::UP_LEFT:
      update(Pos(0,0));
      break;
    case Direction::UP_RIGHT:
      update(Pos(0,block_size_-1));
      break;
    case Direction::DOWN_LEFT:
      update(Pos(block_size_-1,0));
      break;
    case Direction::DOWN_RIGHT:
      update(Pos(block_size_-1,block_size_-1));
      break;
    default:
      assert(false);
  }

  return best_dist;
}

std::vector<Pos> BlockSearch::solve(State& state,Logger& logger){
  create_blocks(state,logger);
  std::vector<Pos> block_path=solve_block_path();
  for(const auto& b:block_path){
    logger.log("score: "+std::to_string(blocks_[b.i][b.j].sum));
    std::string pos="("+std::to_string(b.i)+","+std::to_string(b.j)+")";
    logger.log("pos: "+pos+"\n");
  }

// @trace-pilot 134847fe8febbaa7686cea9127417080ef4713ae
  return solve_best_path(state,logger,block_path);
}
