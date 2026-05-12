# A-Maze-d

**A-Maze-d** is a pathfinding and algorithmic challenge written in C, where you control a swarm of robots trying to navigate a maze from entrance to exit in the fewest laps possible.

The project focuses on parsing structured input, constructing a graph, and applying graph traversal strategies to determine and simulate optimal robot movement.

---

## Project Objective

- Parse a maze structure from standard input.
- Validate the maze format.
- Find the shortest possible paths from the entrance to the exit.
- Simulate multiple robots navigating through the maze.
- Optimize to minimize the number of turns it takes to get all robots to the exit.

---

## Key Concepts

- Graph theory (adjacency matrix)
- Pathfinding algorithms
- Input parsing and error handling
- Simulation of concurrent movements
- Efficient memory management in C

---

## Project Details

- **Language**: C
- **Binary Name**: `amazed`
- **Build System**: `Makefile` with rules: `all`, `clean`, `fclean`, `re`
- **Allowed Functions**: `read`, `write`, `malloc`, `free`, `getline`
- **Exit Codes**: `0` on success, `84` on error

---

## File Structure

```bash
.
├── amazed
├── amazed.c
├── laby_gen.pl
├── src/
├── include/
├── lib/
├── Makefile
└── README.md
```

## Input Format

The program reads from **standard input**. A valid maze includes:

- Number of robots

- Room definitions with optional comments

- Tunnel definitions

- Special commands:

    - `##start`: marks next room as the start

    - `##end`: marks next room as the end

    - `#comment`: ignored

Example:
```bash
3
##start
0 1 0
##end
1 13 0
2 5 0
3 9 0
0-2
2-3
3-1
```

## Output Format
```bash
#number_of_robots
3
#rooms
##start
0 1 0
##end
1 13 0
2 5 0
3 9 0
#tunnels
0-2
2-3
3-1
#moves
P1-2
P1-3 P2-2
P1-1 P2-3 P3-2
P2-1 P3-3
P3-1
```

Each line of `#moves` represents one lap. Each movement is shown as `Pn-r`:

- `n`: robot number

- `r`: room name

## Compilation

```bash
make
```

To clean:

```bash
make clean
make fclean
```

To rebuild:

```bash
make re
```

## Authors
- [@ThomasVillot](https://github.com/ThomasVillot)
- [@yohandprt](https://github.com/yohandprt)
- [@BaptisteVanBunderen](https://github.com/BaptisteVanBunderen)