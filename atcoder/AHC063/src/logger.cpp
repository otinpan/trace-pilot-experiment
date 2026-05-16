#include"logger.h"

Logger::Logger(const std::string& path)
  :ofs_(path)
{

}

void Logger::log(const State& state,int turn){
  ofs_<<"turn = "<<turn<<'\n';
  ofs_<<renderBoard(state);
  ofs_<<'\n';
}

void Logger::log(const std::string &s){
  ofs_<<s<<'\n';
}

std::string Logger::renderBoard(const State& state) const{
  const Stage& stage=state.stage();
  const Snake& snake=state.snake();

  int n=stage.size();

  std::vector<std::string> board(n,std::string(n,'.'));
  std::vector<std::string> food(n,std::string(n,'.'));

  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      Color c=stage.food()[i][j];
      if(c!=EMPTY){
        board[i][j]=char('0'+c);
        food[i][j]=char('0'+c);
      }
    }
  }

  const auto& body=snake.body();

  for(int i=0;i<body.size();i++){
    Pos p=body[i].pos;
    board[p.i][p.j]=char('a'+static_cast<int>(body[i].color));
  }

  std::string s;
  for(int i=0;i<n;i++){
    s+=board[i];
    s+='\n';
  }


  s+="head: ("+std::to_string(snake.head().pos.i)+","+std::to_string(snake.head().pos.j)+")\n";

  return s;
}
