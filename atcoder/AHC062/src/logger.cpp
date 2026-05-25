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
  return "";
}
