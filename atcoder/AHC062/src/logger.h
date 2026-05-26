#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>

#include"state.h"

class Logger{
  public:
    Logger(const std::string& path);

    void log(const State& state);
    void log(const std::string& s);
  private:
    std::ofstream ofs_;
};

