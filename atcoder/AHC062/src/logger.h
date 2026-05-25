#pragma once
#include<iostream>
#include<fstream>
#include<string>

#include"state.h"

class Logger{
  public:
    Logger(const std::string& path);

    void log(const State& state,int turn);
    void log(const std::string& s);
  private:
    std::ofstream ofs_;
    std::string renderBoard(const State& state) const;
};

