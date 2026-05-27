#pragma once
#include<iostream>
#include<vector>
#include<array>

extern int map_size;
const double TIME_LIMIT=2.95;

struct Pos{
  int i,j;
  Pos(int _i,int _j)
    :i(_i)
    ,j(_j){

    }
  Pos operator+(const Pos& other) const{
    return Pos(i+other.i,j+other.j);
  }

  Pos operator-(const Pos& other) const{
    return Pos(i-other.i,j-other.j);
  }

  bool operator==(const Pos& other) const{
    return i==other.i && j==other.j;
  }

  bool operator!=(const Pos& other) const{
    return i!=other.i || j!=other.j;
  }

  bool is_on_map() const{
    return i>=0 && i<map_size && j>=0 && j<map_size;
  }

  bool is_on_block(const Pos& left_top,const Pos& right_bottom) const{
    return i>=left_top.i && i<right_bottom.i
      && j>=left_top.j && j<right_bottom.j;
  }
};



enum class Direction{
  UP,
  UP_RIGHT,
  RIGHT,
  DOWN_RIGHT,
  DOWN,
  DOWN_LEFT,
  LEFT,
  UP_LEFT,
};

const std::array<Pos,8> DIRS={
  Pos(-1,0),
  Pos(-1,1),
  Pos(0,1),
  Pos(1,1),
  Pos(1,0),
  Pos(1,-1),
  Pos(0,-1),
  Pos(-1,-1)
};


