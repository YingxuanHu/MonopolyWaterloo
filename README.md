# AlvinWatopoly

AlvinWatopoly is a C++ implementation of a Monopoly-inspired board game created for the University of Waterloo theme. The game features an object-oriented design with dedicated types for properties, players, and core game mechanics.

## Project Structure

- `include/` – public headers for the game engine, entities, and utilities.
- `src/` – implementation files that build the Watopoly executable.
- `build/` – auto-generated object files and dependency data (ignored from version control).
- `Makefile` – builds the project and manages dependencies.

## Building

1. Ensure you have a C++11-compatible compiler and `make` installed.
2. Run `make` from the repository root. The compiled binary is placed at `./watopoly`.

## Running

Execute `./watopoly` and follow the interactive prompts to set up the game. The game accepts several commands such as `roll`, `next`, `trade`, `improve`, `mortgage`, `unmortgage`, `bankrupt`, and `assets` once play begins.

Optional flags:

- `-testing` – enables deterministic dice rolls for testing.
- `-load <file>` – loads a previously saved game from the specified file.

## Documentation

The repository includes additional design documentation in `design.pdf` and the final UML reference in `uml-final.pdf`.
