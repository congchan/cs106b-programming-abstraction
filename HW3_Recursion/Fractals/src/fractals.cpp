/*
 * File: fractals.cpp
 * --------------------------
 * Name:
 * Section leader:
 * This file contains fractal problems for CS106B.
 * Assignment 3A: Fractals
 * @Author: Cong Chen
 * @Version: 2017/06
 */


#include "fractals.h"
#include <cmath>
#include <stdexcept>
#define PI 3.14159265
using namespace std;

const int LEAF_COLOR = 0x2e8b57;   /* Color of all leaves of recursive tree (level 1) */
const int BRANCH_COLOR = 0x8b7765; /* Color of all branches of recursive tree (level >=2) */

/**
 * Draws a Sierpinski triangle of the specified size and order, placing its
 * top-left corner at position (x, y).
 *
 * This will be called by fractalgui.cpp.
 *
 * @param gw - The window in which to draw the Sierpinski triangle.
 * @param x - The x coordinate of the top-left corner of the triangle.
 * @param y - The y coordinate of the top-left corner of the triangle.
 * @param size - The length of one side of the triangle.
 * @param order - The order of the fractal.
 */
void drawSierpinskiTriangle(GWindow& gw, double x, double y, double size, int order) {
    //draw three order-1 triangle
    if (order==0) {
    } else if (order<0) {
        throw runtime_error("exception");
    } else if (order==1) {
        gw.drawLine(x,y,x+size,y);
        gw.drawLine(x,y,x+size*0.5,y+size*cos(30*PI/180));
        gw.drawLine(x+size,y,x+size*0.5,y+size*cos(30*PI/180));
    } else {
        drawSierpinskiTriangle(gw,x,y,size*0.5,order-1);
        drawSierpinskiTriangle(gw,x+size*0.5,y,size*0.5,order-1);
        drawSierpinskiTriangle(gw,x+size*0.25,y+size*0.5*cos(PI/6),size*0.5,order-1);
    }
}

/**
 * Draws a recursive tree fractal image of the specified size and order,
 * placing the bounding box's top-left corner at position (x,y).
 *
 * This will be called by fractalgui.cpp.
 *
 * @param gw - The window in which to draw the recursive tree.
 * @param x - The x coordinate of the top-left corner of the bounding box.
 * @param y - The y coordinate of the top-left corner of the bounding box.
 * @param size - The length of one side of the bounding box.
 * @param order - The order of the fractal.
 */
void drawTree(GWindow& gw, double x, double y, double size, int order, int theta) {
    // theta is the degree relative to -y in counterclockwise
    // always draw a trunk from (x,y) with length size/2 and a rotation of theta degree
    //double R = size*0.5;
    if (order==1) {
        gw.setColor("#2e8b57");
    } else {
        gw.setColor("#8b7765");
    }
    GPoint endPoint = gw.drawPolarLine(x,y,size*0.5,theta+90);

    if (order>1) {
        for (int i = -3; i<=3;i++) {
            // alpha is the degree relative to -y in counterclockwise
            //int alpha = 15*i+theta;
            drawTree(gw,endPoint.getX(),endPoint.getY(),0.5*size,order-1,15*i+theta);
        }
    }
}

/**
 * Draws a Mandelbrot Set in the graphical window give, with maxIterations
 * (size in GUI) and in a given color (zero for palette)
 *
 * This will be called by fractalgui.cpp.
 *
 * @param gw - The window in which to draw the Mandelbrot set.
 * @param minX - left-most column of grid
 * @param incX - increment value of columns of grid
 * @param minY - top-most row of grid
 * @param incY - increment value of rows of grid
 * @param maxIterations - The maximum number of iterations to run recursive step
 * @param color - The color of the fractal; zero if palette is to be used
 */
void mandelbrotSet(GWindow& gw, double minX, double incX,
                   double minY, double incY, int maxIterations, int color) {

    // Creates palette of colors
    // To use palette:
    // pixels[r][c] = palette[numIterations % palette.size()];
    Vector<int> palette = setPalette();
    int width = gw.getCanvasWidth();
    int height = gw.getCanvasHeight();
    GBufferedImage image(width,height,0xffffff);
    gw.add(&image);
    Grid<int> pixels = image.toGrid(); // Convert image to grid

    // TODO: Put your Mandelbrot Set code here
    for (int i=0;i<pixels.numCols();i++) {
        for (int j=0;j<pixels.numRows();j++) {
            Complex coord = Complex(minX + i*incX, minY + j*incY);
            int numIterations = mandelbrotSetIterations(coord,maxIterations);

            //If color was not assigned, set this pixel's color based on the return numIterations
            if (color==0) {
                pixels[j][i] = palette[numIterations % palette.size()];
            } else {
                if (numIterations==maxIterations) {
                    pixels[j][i] = color;
                }
            }

        }
    }

    image.fromGrid(pixels); // Converts and puts the grid back into the image
}

/**
 * Runs the Mandelbrot Set recursive formula on complex number c a maximum
 * of maxIterations times.
 *
 * This will be called by you. Think about how this fits with the other two functions.
 *
 * @param c - Complex number to use for recursive formula.
 * @param maxIterations - The maximum number of iterations to run recursive step
 * @return number of iterations needed to determine if c is unbounded
 */
int mandelbrotSetIterations(Complex c, int maxIterations) {
    // TODO: Write this function
    Complex z= Complex(0,0);
    return maxIterations-mandelbrotSetIterations(z,c,maxIterations);
//    return 0; // Only here to make this compile
}
/**
 * An iteration of the Mandelbrot Set recursive formula with given values z and c, to
 * run for a maximum of maxIterations.
 *
 * This will be called by you. Think about how this fits with the other two functions.
 *
 * @param z - Complex number for a given number of iterations
 * @param c - Complex number to use for recursive formula.
 * @param remainingIterations - The remaining number of iterations to run recursive step
 * @return number of iterations needed to determine if c is unbounded
 */
int mandelbrotSetIterations(Complex z, Complex c, int remainingIterations) {
    /* Return how many iteration remain after c is determined unbounded.*/
    if (z.abs()>=4){
        return remainingIterations;
    } else {
        if(remainingIterations == 0) {
            return remainingIterations;
        } else {
            Complex zNp = z*z + c;
            mandelbrotSetIterations(zNp,c,remainingIterations-1);
        }
    }
//    return 0; // Only here to make this compile
}

// Helper function to set the palette
Vector<int> setPalette() {
    Vector<int> colors;

    // Feel free to replace with any palette.
    // You can find palettes at:
    // http://www.colourlovers.com/palettes

    // Example palettes:
    // http://www.colourlovers.com/palette/4480793/in_the_middle
    // string colorSt = "#A0B965,#908F84,#BF3C43,#9D8E70,#C9BE91,#A0B965,#908F84,#BF3C43";

    // http://www.colourlovers.com/palette/4480786/Classy_Glass
    // string colorSt = "#9AB0E9,#C47624,#25269A,#B72202,#00002E,#9AB0E9,#C47624,#25269A";

    // The following is the "Hope" palette:
    // http://www.colourlovers.com/palette/524048/Hope
    string colorSt =  "#04182B,#5A8C8C,#F2D99D,#738585,#AB1111,#04182B,#5A8C8C,#F2D99D";
    Vector<string>colorsStrVec = stringSplit(colorSt,",");
    for (string color : colorsStrVec) {
        colors.add(convertColorToRGB(trim(color)));
    }
    return colors;
}
