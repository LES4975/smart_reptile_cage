from enum import Enum

class State(Enum):
    IDLE = 0
    DECREASING = 1   # 감소 방향 제어 (ex. 냉각, 가습)
    INCREASING = 2   # 증가 방향 제어 (ex. 가열, 건조)
    
class Direction(Enum):
    NONE = 0
    DOWN = -1
    UP = 1

class StateController:
    def __init__(self, tolerance: float):
        self.prev_state = State.IDLE
        self.tolerance = tolerance

    def get_direction(self, diff: float) -> Direction:
        if diff < -self.tolerance:
            return Direction.DOWN
        elif diff > self.tolerance:
            return Direction.UP
        else:
            return Direction.NONE

    def update_state(self, diff: float) -> State:
        direction = self.get_direction(diff)
        
        if self.prev_state == State.DECREASING and diff >= 0:
            self.prev_state = State.IDLE
        elif self.prev_state == State.INCREASING and diff <= 0:
            self.prev_state = State.IDLE
        elif direction == Direction.DOWN:
            self.prev_state = State.DECREASING
        elif direction == Direction.UP:
            self.prev_state = State.INCREASING
        else:
            self.prev_state = State.IDLE

        return self.prev_state

    def get_direction_value(self, diff: float) -> int:
        return self.get_direction(diff).value