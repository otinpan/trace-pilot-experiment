#include<iostream>
#include<vector>

#include"common.h"
#include"experiment_logger.h"
#include"logger.h"
#include"simulator.h"
#include"state.h"
#include"stage.h"
#include"snake.h"
#include"strategy/greedy.h"
#include"strategy/hill_climbing.h"
#include"strategy/simulated_annealing.h"

int main() {
  int n,m,c;
  std::cin>>n>>m>>c;

  std::vector<Color> ideal(m);
  for(int i=0;i<m;i++){
    int d; std::cin>>d;
    ideal[i]=static_cast<Color>(d);
  }
  std::vector<std::vector<Color>> food(n,std::vector<Color>(n));

  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      int f; std::cin>>f;
      food[i][j]=static_cast<Color>(f);
    }
  }

  Logger logger("log.txt");
  // @trace-pilot c041b61f1898609dde303ca4926e67b605ec94da
  ExperimentLogger experiment_logger("experiment.csv");

  Snake snake(n);
  Stage stage(n,food);
  
  State state(stage,snake);

  HillClimbing strategy(ideal);

  Simulator simulator(state,strategy,logger);
  std::vector<char> result=simulator.simulate();

  for(const auto& res:result){
    std::cout<<res<<'\n';
  }
  return 0;
}
