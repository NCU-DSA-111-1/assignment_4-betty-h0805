# Maze Generator and Solver

This is a project which can generate a maze and solve the generated maze.

## About ./bin/maze.txt
### Information
This is a file which will be generated after executing solve.exe.
(Please check build.md for executing guide.)

### Structure
There are three lines in `maze.txt`.
1. The first line and second line records the total rows and columns of the generated maze.
2. The third line records the status of the generated map
```
0 : available road
1 : inner walls
3 : boarder
```