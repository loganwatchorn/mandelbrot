// Import standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Pre-compile variables
#define NUM_PIXELS_RE 151
#define NUM_PIXELS_IM 101
#define MAX_ITERATIONS 100000
#define TOLERANCE 0.005

const double RE_MIN = -2;
const double RE_MAX = 1;
const double IM_MIN = -1;
const double IM_MAX = 1;

// Complex type
typedef struct {
    double re;
    double im;
} complex;
complex mult(complex a, complex b) { return (complex) {a.re*b.re-a.im*b.im, a.im*b.re+b.im*a.re}; }
complex add(complex a, complex b) { return (complex) {a.re+b.re, a.im+b.im}; }

// Efficiently determine whether two complex numbers are equal
double distance;
bool neq(complex a, complex b) {
    distance = a.re-b.re;
    if (distance < 0) { distance *= -1; }
    if (distance <= TOLERANCE) { return false; }
    
    distance = a.im-b.im;
    if (distance < 0) { distance *= -1; }
    return (distance > TOLERANCE);
}

bool outOfBounds(complex c) {
    return (c.re < RE_MIN || c.re > RE_MAX || c.im < IM_MIN || c.im > IM_MAX);
}

bool isInMandelbrot(complex c) {
    complex zPrev = {0, 0};
    complex z = c;

    for (int i=0 ; i < MAX_ITERATIONS && neq(z, zPrev) ; i++) {
        // Print i and z
        // printf("i=%d, z=%f + %fi\n", i, z.re, z.im);

        if (outOfBounds(z)) {
            // printf("Out of bounds");
            return false;
        }

        z = add(mult(z, z), c);
    }

    return true;
}

void main() {
    // Loop over pixels by row and col, determine whether they are in the Mandelbrot set, and if so, add a black pixel to the jpg. If not, add a white pixel.
    for (int row=0 ; row<=NUM_PIXELS_IM ; row++) {
        for (int col=0 ; col<=NUM_PIXELS_RE ; col++) {
            complex c = {RE_MIN + (RE_MAX-RE_MIN)*col/NUM_PIXELS_RE, IM_MIN + (IM_MAX-IM_MIN)*row/NUM_PIXELS_IM};
            if (isInMandelbrot(c)) {
                printf("##");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
}
