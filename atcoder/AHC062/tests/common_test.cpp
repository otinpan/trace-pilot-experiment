#include <cassert>

int map_size = 200;

#include "common.h"

void test_is_on_map() {
  assert(Pos(0, 0).is_on_map());
  assert(Pos(199, 199).is_on_map());
  assert(!Pos(-1, 0).is_on_map());
  assert(!Pos(0, -1).is_on_map());
  assert(!Pos(200, 0).is_on_map());
  assert(!Pos(0, 200).is_on_map());
}

void test_is_on_block(){
  assert(Pos(0,0).is_on_block(Pos(0,0),Pos(2,2)));
  assert(!Pos(2,1).is_on_block(Pos(0,0),Pos(2,3)));
  assert(!Pos(1,2).is_on_block(Pos(0,0),Pos(3,2)));
  assert(Pos(7,7).is_on_block(Pos(6,6),Pos(8,8)));
}

void test_pos_addition() {
  const Pos lhs(10, 20);
  const Pos rhs(-3, 5);

  assert(lhs + rhs == Pos(7, 25));
}

void test_pos_subtraction() {
  const Pos lhs(10, 20);
  const Pos rhs(3, 5);

  assert(lhs - rhs == Pos(7, 15));
}

void test_segment_constructor() {
  // Segment is not defined yet, so validate Pos construction instead.
  const Pos pos(12, 34);

  assert(pos.i == 12);
  assert(pos.j == 34);
}

void test_direction_tables() {
  assert(DIRS.size() == 8);
  assert(DIRS[static_cast<int>(Direction::UP)] == Pos(-1, 0));
  assert(DIRS[static_cast<int>(Direction::UP_RIGHT)] == Pos(-1, 1));
  assert(DIRS[static_cast<int>(Direction::RIGHT)] == Pos(0, 1));
  assert(DIRS[static_cast<int>(Direction::DOWN_RIGHT)] == Pos(1, 1));
  assert(DIRS[static_cast<int>(Direction::DOWN)] == Pos(1, 0));
  assert(DIRS[static_cast<int>(Direction::DOWN_LEFT)] == Pos(1, -1));
  assert(DIRS[static_cast<int>(Direction::LEFT)] == Pos(0, -1));
  assert(DIRS[static_cast<int>(Direction::UP_LEFT)] == Pos(-1, -1));
}

int main() {
  test_is_on_map();
  test_is_on_block();
  test_pos_addition();
  test_pos_subtraction();
  test_segment_constructor();
  test_direction_tables();
}
