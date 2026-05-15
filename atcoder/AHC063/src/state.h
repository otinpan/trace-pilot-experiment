#pragma once
#include<iostream>
#include<vector>

#include"common.h"
#include"stage.h"
#include"snake.h"

class State{
  public:
    State(Stage stage,Snake snake);
    ~State();

    const Stage& stage() const {return stage_;}
    const Snake& snake() const {return snake_;}

    bool apply(Direction dir);
  private:
    Stage stage_;
    Snake snake_;
};
