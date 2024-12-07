import time
def part2(puzzle_input):
    # Parse the input into a 2D grid
    original_grid = [list(line) for line in puzzle_input.strip().split('\n')]
    
    # Define directions: up, right, down, left (clockwise)
    DIRECTIONS = [
        (-1, 0),   # Up
        (0, 1),    # Right
        (1, 0),    # Down
        (0, -1)    # Left
    ]
    
    # Find the initial guard position and direction
    def find_start():
        for r, row in enumerate(original_grid):
            for c, cell in enumerate(row):
                if cell in '^>v<':
                    # Map of starting directions
                    dir_map = {'^': 0, '>': 1, 'v': 2, '<': 3}
                    return r, c, dir_map[cell]
        return None
    
    def simulate_patrol(grid):
        # Track visited positions and states to detect loops
        visited_states = set()
        
        # Start the simulation
        r, c, direction = find_start()
        
        while True:
            # Create a state to track position, direction
            state = (r, c, direction)
            
            # If we've seen this state before, it's a loop
            if state in visited_states:
                return True
            
            visited_states.add(state)
            
            # Check possible moves
            dr, dc = DIRECTIONS[direction]
            next_r, next_c = r + dr, c + dc
            
            # If blocked, turn right
            if (next_r < 0 or next_r >= len(grid) or 
                next_c < 0 or next_c >= len(grid[0]) or 
                grid[next_r][next_c] == '#'):
                direction = (direction + 1) % 4
                continue
            
            # Move forward
            r, c = next_r, next_c
            
            # Check if guard has left the mapped area
            if (r == 0 or r == len(grid) - 1 or 
                c == 0 or c == len(grid[0]) - 1):
                return False
        
    # Find loop positions
    loop_positions = 0
    start_r, start_c, _ = find_start()
    
    # Try adding an obstruction to every non-blocked, non-start position
    for r in range(len(original_grid)):
        for c in range(len(original_grid[0])):
            # Skip if it's the start position or already an obstacle
            if (r, c) == (start_r, start_c) or original_grid[r][c] == '#':
                continue
            
            # Create a copy of the grid and add an obstacle
            test_grid = [row.copy() for row in original_grid]
            test_grid[r][c] = '#'
            
            # Check if this creates a loop
            if simulate_patrol(test_grid):
                loop_positions += 1
    return loop_positions

start = time.time()
puzzle_input = open('input', 'r').read()
print(part2(puzzle_input))
end = time.time()
print("Total runtime: ", start-end)