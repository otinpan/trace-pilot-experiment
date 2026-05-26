#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <set>
#include <utility>
#include <vector>

#include "logger.h"
#include "state.h"
#include "strategy/greedy.h"

int map_size = 0;

bool are_adjacent(const Pos& lhs,const Pos& rhs){
  const int di=std::abs(lhs.i-rhs.i);
  const int dj=std::abs(lhs.j-rhs.j);
  return std::max(di,dj)==1;
}

void test_solve_zigzag_visits_all_cells_once(){
  map_size=3;
  State state({
    {1,2,3},
    {4,5,6},
    {7,8,9},
  });
  Logger logger("/tmp/ahc062_greedy_test.log");
  Greedy greedy;

  const std::vector<Pos> result=greedy.solve(state,logger);

  assert(result.size()==static_cast<size_t>(map_size*map_size));

  std::set<std::pair<int,int>> visited;
  for(const Pos& pos:result){
    assert(pos.is_on_map());
    visited.insert({pos.i,pos.j});
  }
  assert(visited.size()==result.size());
}

void test_solve_zigzag_keeps_adjacent_steps(){
  map_size=4;
  State state({
    {1,2,3,4},
    {5,6,7,8},
    {9,10,11,12},
    {13,14,15,16},
  });
  Logger logger("/tmp/ahc062_greedy_test.log");
  Greedy greedy;

  const std::vector<Pos> result=greedy.solve(state,logger);

  for(size_t i=1;i<result.size();i++){
    assert(are_adjacent(result[i-1],result[i]));
  }
}

void test_solve_zigzag_returns_expected_order(){
  map_size=3;
  State state({
    {1,2,3},
    {4,5,6},
    {7,8,9},
  });
  Logger logger("/tmp/ahc062_greedy_test.log");
  Greedy greedy;

  const std::vector<Pos> result=greedy.solve(state,logger);
  const std::vector<Pos> expected={
    Pos(0,0),
    Pos(0,1),
    Pos(0,2),
    Pos(1,2),
    Pos(1,1),
    Pos(1,0),
    Pos(2,0),
    Pos(2,1),
    Pos(2,2),
  };

  assert(result.size()==expected.size());
  for(size_t i=0;i<expected.size();i++){
    assert(result[i]==expected[i]);
  }
}

int main(){
  test_solve_zigzag_visits_all_cells_once();
  test_solve_zigzag_keeps_adjacent_steps();
  test_solve_zigzag_returns_expected_order();
}
