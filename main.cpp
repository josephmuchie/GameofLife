#include <GLFW/glfw3.h>
//#include <glad/glad.h>

#include "linmath.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <random>
#include <cstring>
#include <vector>


void error_callback(int error, const char* description){
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

const int WIDTH = 400;
const int HEIGHT = 400;
const int CELL_SIZE = 10;

std::vector<std::vector<bool>> grid(WIDTH/CELL_SIZE, std::vector<bool>(HEIGHT/CELL_SIZE, false));
std::vector<std::vector<bool>> newGrid(WIDTH/CELL_SIZE, std::vector<bool>(HEIGHT/CELL_SIZE, false));

void initGrid() {
    srand(time(0));
    for(int i = 0; i < WIDTH/CELL_SIZE; i++) {
        for(int j = 0; j < HEIGHT/CELL_SIZE; j++) {
            grid[i][j] = rand() % 2;
        }
    }
}

int countNeighbors(int x, int y) {
    int count = 0;
    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            if(i == 0 && j == 0) {
                continue;
            }
            int row = (x + i + WIDTH/CELL_SIZE) % (WIDTH/CELL_SIZE);
            int col = (y + j + HEIGHT/CELL_SIZE) % (HEIGHT/CELL_SIZE);
            if(grid[row][col]) {
                count++;
            }
        }
    }
    return count;
}

void updateGrid() {
    for(int i = 0; i < WIDTH/CELL_SIZE; i++) {
        for(int j = 0; j < HEIGHT/CELL_SIZE; j++) {
            int neighbors = countNeighbors(i, j);
            if(grid[i][j]) {
                if(neighbors < 2 || neighbors > 3) {
                    newGrid[i][j] = false;
                } else {
                    newGrid[i][j] = true;
                }
            } else {
                if(neighbors == 3) {
                    newGrid[i][j] = true;
                }
            }
        }
    }
    grid = newGrid;
}

void drawCell(int x, int y) {
    if(grid[x][y]) {
        glColor3f(1.0, 1.0, 1.0);
    } else {
        glColor3f(0.0, 0.0, 0.0);
    }
    glBegin(GL_QUADS);
        glVertex2f(x*CELL_SIZE, y*CELL_SIZE);
        glVertex2f((x+1)*CELL_SIZE, y*CELL_SIZE);
        glVertex2f((x+1)*CELL_SIZE, (y+1)*CELL_SIZE);
        glVertex2f(x*CELL_SIZE, (y+1)*CELL_SIZE);
    glEnd();
}


int main(int argc, char ** argv)
{
    GLFWwindow *window;

    //glfwSetErrorCallback(error_callback);

    //initialize the library
    if(!glfwInit()){
        return -1;
    }

    //Create Windowed mode and ints OpenGL context
     window = glfwCreateWindow(WIDTH * CELL_SIZE, HEIGHT * CELL_SIZE, "Conway's Game of Life v1.0", NULL, NULL);
    if(!window)
    {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // glfwSetKeyCallback(window, key_callback);
    //make the current window context current
    glfwMakeContextCurrent(window);
    initGrid();

    //Loop until the user closes window
    while(!glfwWindowShouldClose(window))
    {
        //Render here
        //glClear(GL_COLOR_BUFFER_BIT);
        updateGrid();
               //sWAP FRONT AND BACK BUFFERS
         glClear(GL_COLOR_BUFFER_BIT);
    for(int i = 0; i < WIDTH/CELL_SIZE; i++) {
        for(int j = 0; j < HEIGHT/CELL_SIZE; j++) {
            if(grid[i][j]) {
                glColor3f(1.0, 1.0, 1.0);
                glRectf(i*CELL_SIZE, j*CELL_SIZE, (i+1)*CELL_SIZE, (j+1)*CELL_SIZE);
            }
        }
    }
    glfwSwapBuffers(window);

        //Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

