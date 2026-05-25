#include<iostream>
#include<vector>

#include"logger.h"
#include"state.h"
#include"strategy/strategy.h"
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

  Logger logger("log.txt");

  State state(g);

  Strategy strategy;

  Simulator simulator(state,strategy,logger);
  std::vector<std::pair<char,char>> result=simulator.simulate();

  for(const auto& res:result){
    std::cout<<res.first<<" "<<res.second<<'\n';
  }

  return 0;
}
