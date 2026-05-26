#include"logger.h"

Logger::Logger(const std::string& path)
  :ofs_(path)
{

}

void Logger::log(const State& state){
  ofs_<<"turn = "<<state.turn()<<'\n';
  ofs_<<"pos = ("<<state.pos().i<<","<<state.pos().j<<")"<<'\n';
  ofs_<<"score = "<<state.score()<<'\n';

  ofs_<<'\n';
}

void Logger::log(const std::string &s){
  ofs_<<s<<'\n';
}
