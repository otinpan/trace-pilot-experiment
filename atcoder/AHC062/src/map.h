#pragma once
#include<iostream>
#include<vector>

class Kingdom{
  public:
    Kingdom();
    ~Kingdom();

    const std::vector<std::vector<int>>& blocks()const{return blocks_;}
  private:
    std::vector<std::vector<int>> blocks_;
};
