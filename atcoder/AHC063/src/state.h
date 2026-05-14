#pragma once
#include<iostream>

#include"common.h"
#include"stage.h"
#include"snake.h"

class State{
  public:
    State(Stage stage,Snake snake);
    ~State();

    bool apply(Direction dir);
  private:
    class Stage stage_;
    class Snake snake_;
};
