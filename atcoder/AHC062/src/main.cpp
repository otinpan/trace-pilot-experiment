#include<iostream>
#include<vector>

#include"logger.h"
#include"state.h"
#include"strategy/strategy.h"
#include"strategy/greedy.h"
// @trace-pilot 459aadc7d949bf4c6b61391b35a1fa84905c19a6
#include"strategy/surround.h"
#include"simulator.h"
int map_size = 0;

int main(){
  int n;
  std::cin>>n;

  map_size = n;

  std::vector<std::vector<int>> g(n,std::vector<int>(n));

  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      std::cin>>g[i][j];
    }
  }

  // @trace-pilot 8df6e90bf6b89471b82eaeda517c4f1aa2bc3e1f
  /*Logger horizontal_logger("horizontal.log");
  Logger vertical_logger("vertical.log");

  State horizontal_state(g);
  State vertical_state(g);

  Greedy horizontal_strategy(false);
  Greedy vertical_strategy(true);


  horizontal_logger.log("start");
  std::vector<Pos> horizontal_result=horizontal_strategy.solve(horizontal_state,horizontal_logger);

  vertical_logger.log("start");
  std::vector<Pos> vertical_result=vertical_strategy.solve(vertical_state,vertical_logger);


  std::vector<Pos> result=horizontal_result;
  long long best_score=horizontal_state.score();
  if(vertical_state.score()>best_score){
    best_score=vertical_state.score();
    result=vertical_result;
  }*/

  State state(g);
  Surround strategy;
  Logger logger("log.txt");
  std::vector<Pos> result=strategy.solve(state,logger);

  for(const auto& res:result){
    std::cout<<res.i<<" "<<res.j<<'\n';
  }

  return 0;
}
