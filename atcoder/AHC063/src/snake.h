#pragma once
#include <iostream>
#include <vector>
#include "common.h"
#include "stage.h"

class Snake{
  public:
    Snake(int stage_size);
    ~Snake();

    const Segment& head() const{return body_[0];}
    const Segment& tail() const{return body_[body_.size()-1];}

    // 動く直前のtailを返す
    Segment move(Direction dir);

    // u-turnしないか
    bool canMove(Direction dir);

    // old_posに餌の色のsegmentを付ける
    void grow(Pos old_pos,Color food);

    // かみちぎるか
    std::vector<Segment> bite();

    size_t size() const{
      return body_.size();
    }

  private:
   std::vector<Segment> body_;
   int stage_size_;

};
