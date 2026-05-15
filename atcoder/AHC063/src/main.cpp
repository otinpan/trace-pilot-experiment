#include<iostream>
#include<vector>

#include"common.h"
#include"logger.h"
#include"simulator.h"
#include"state.h"
#include"stage.h"
#include"snake.h"

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

  Snake snake(n);
  Stage stage(n,food);
  
  State state(stage,snake);

  Simulator simulator(state,logger,ideal);
  simulator.solve();

  std::vector<char> result=simulator.operation_row();

  for(const auto& res:result){
    std::cout<<res<<'\n';
  }
  return 0;
}

