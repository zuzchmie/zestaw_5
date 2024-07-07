# ASCII Renderer

This program takes data from the file and cretes geometrical shapes in an ASCII file using the given data 

# Table of Contents


- [Getting Started and Usage](#getting-started-and-usage)
- [Features](#features)
- [Configuration File Format](#configuration-file-format)
- [Files in the Repository](#files-in-the-repository)



# Getting started and Usage
## Installation
1. Clone the repository:
git clone https://github.com/zuzchmie/zestaw_5.git

2. Create your own (or use the provided) configuration file - 'data.txt'

3. Compile the project:
g++ -std=c++20 canvas.cpp -o canvas 

4. Run the program:
./canvas

# Features

- Drawing shapes (Rectangle, Square, Triangle, Circle) on an ASCII canvas
- Configurable canvas size, symbols for shapes and the background, as well as sizes and coordinates of the shapes
- Output saved to a file

# Configuration File Format

<canvas_width> <canvas_height> <output_filename> <empty_space_symbol>  

<shape_name> <shape_parameters>
...

## Shapes and parameters:
Rectangle: Rectangle '<width>' '<height>' '<x>' '<y>' '<symbol>'

Square: Square '<side_length>' '<x>' '<y>' '<symbol>'

Triangle: Triangle '<base>' '<height>' '<x>' '<y>' '<symbol>'

Circle: Circle '<radius>' '<x>' '<y>' '<symbol>'
 


# Files in the repository
1. main file 'canvas.cpp'
2. example config file 'data.txt'
3. example output file 'file.txt'



