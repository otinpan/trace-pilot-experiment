#pragma once
#include<iostream>
#include<vector>
#include<array>
#include<map>

using Color=int;
constexpr Color EMPTY=0;
constexpr Color OUT_OF_BOUND=-1;

const int MAX_SIMULATION=100000;
const double TIME_LIMIT=1.95;

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
};


struct Segment{
  Pos pos;
  Color color;

  Segment(Pos _pos,Color _color)
    :pos(_pos)
    ,color(_color)
  {

  }
};

// @trace-pilot d5531f79a57a46ea89aa5af2179a26aea5cec62d
enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

const std::array<Pos, 4> DIRS = {
    Pos(-1,0),
    Pos(1,0),
    Pos(0,-1),
    Pos(0,1),
};

const std::array<char, 4> OUTPUT_DIR = {
    'U',
    'D',
    'L',
    'R',
};

