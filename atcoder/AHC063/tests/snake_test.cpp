// @trace-pilot db36eed9961f61a2a7740613857b91b6a3701d16
#include <cassert>
#include <vector>

#include "snake.h"

namespace {

void assertSegment(const Segment& segment, const Pos& pos, Color color) {
    assert(segment.pos == pos);
    assert(segment.color == color);
}

void test_initial_state() {
    const Snake snake(8);

    assert(snake.size() == 5);
    assertSegment(snake.head(), Pos(4, 0), 1);
    assertSegment(snake.tail(), Pos(0, 0), 1);

    const std::vector<Segment>& body = snake.body();
    assertSegment(body[0], Pos(4, 0), 1);
    assertSegment(body[1], Pos(3, 0), 1);
    assertSegment(body[2], Pos(2, 0), 1);
    assertSegment(body[3], Pos(1, 0), 1);
    assertSegment(body[4], Pos(0, 0), 1);
}

void test_can_move_checks_bounds_and_u_turn() {
    Snake snake(8);

    assert(!snake.canMove(Direction::UP));
    assert(!snake.canMove(Direction::LEFT));
    assert(snake.canMove(Direction::DOWN));
    assert(snake.canMove(Direction::RIGHT));
}

void test_move_shifts_positions_and_returns_old_tail() {
    Snake snake(8);

    const Segment old_tail = snake.move(Direction::RIGHT);

    assertSegment(old_tail, Pos(0, 0), 1);
    assert(snake.size() == 5);

    const std::vector<Segment>& body = snake.body();
    assertSegment(body[0], Pos(4, 1), 1);
    assertSegment(body[1], Pos(4, 0), 1);
    assertSegment(body[2], Pos(3, 0), 1);
    assertSegment(body[3], Pos(2, 0), 1);
    assertSegment(body[4], Pos(1, 0), 1);
}

void test_grow_appends_new_tail_segment() {
    Snake snake(8);
    const Segment old_tail = snake.move(Direction::RIGHT);

    snake.grow(old_tail.pos, 6);

    assert(snake.size() == 6);
    assertSegment(snake.tail(), Pos(0, 0), 6);
}

void test_grow_ignores_empty_and_out_of_bound_colors() {
    Snake snake(8);
    const size_t original_size = snake.size();

    snake.grow(Pos(7, 7), EMPTY);
    snake.grow(Pos(6, 6), OUT_OF_BOUND);

    assert(snake.size() == original_size);
    assertSegment(snake.tail(), Pos(0, 0), 1);
}

void test_bite_returns_empty_when_no_collision() {
    Snake snake(8);
    snake.move(Direction::RIGHT);

    const std::vector<Segment> dropped = snake.bite();

    assert(dropped.empty());
    assert(snake.size() == 5);
}

void test_bite_ignores_collision_with_tail() {
    Snake snake(8);
    snake.move(Direction::RIGHT);
    snake.move(Direction::UP);
    snake.move(Direction::LEFT);

    const std::vector<Segment> dropped = snake.bite();

    assert(dropped.empty());
    assert(snake.size() == 5);
    assertSegment(snake.head(), Pos(3, 0), 1);
    assertSegment(snake.tail(), Pos(3, 0), 1);
}

void test_bite_drops_from_first_non_tail_collision_index() {
    Snake snake(8);

    const Segment old_tail = snake.move(Direction::RIGHT);
    snake.grow(old_tail.pos, 2);
    snake.move(Direction::UP);
    snake.move(Direction::LEFT);

    const std::vector<Segment> dropped = snake.bite();

    assert(dropped.size() == 2);
    assertSegment(dropped[0], Pos(3, 0), 1);
    assertSegment(dropped[1], Pos(2, 0), 2);

    assert(snake.size() == 5);
    const std::vector<Segment>& body = snake.body();
    assertSegment(body[0], Pos(3, 0), 1);
    assertSegment(body[1], Pos(3, 1), 1);
    assertSegment(body[2], Pos(4, 1), 1);
    assertSegment(body[3], Pos(4, 0), 1);
    assertSegment(body[4], Pos(3, 0), 1);
}

}  // namespace

int main() {
    test_initial_state();
    test_can_move_checks_bounds_and_u_turn();
    test_move_shifts_positions_and_returns_old_tail();
    test_grow_appends_new_tail_segment();
    test_grow_ignores_empty_and_out_of_bound_colors();
    test_bite_returns_empty_when_no_collision();
    test_bite_ignores_collision_with_tail();
    test_bite_drops_from_first_non_tail_collision_index();
    return 0;
}