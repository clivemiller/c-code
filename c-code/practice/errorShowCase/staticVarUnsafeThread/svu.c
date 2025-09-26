// Simple array ops implementation
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "header.h"

int width;
int length;
int lightCount;

// store results in arrays for printing
#define MAX_LIGHTS 1000
static double xs[MAX_LIGHTS];
static double ys[MAX_LIGHTS];

void Set(int w, int l, int lC) {
    width = w;
    length = l;
    lightCount = lC;
}

void Calculate(void) {
    if (lightCount <= 0 || width <= 0 || length <= 0) return;
    if (lightCount > MAX_LIGHTS) lightCount = MAX_LIGHTS;

    double aspect = (double)length / (double)width;
    int best_c = 1, best_r = lightCount, best_cells = lightCount + 1;
    double best_diff = 1e100;

    int c0 = (int)round(sqrt(lightCount * aspect));
    if (c0 < 1) c0 = 1;
    for (int c = (c0 > 1 ? c0 - 1 : 1); c <= c0 + 1; ++c) {
        int r = (lightCount + c - 1) / c;
        double diff = fabs(((double)c / r) - aspect);
        int cells = r * c;
        if (diff < best_diff || (diff == best_diff && cells < best_cells)) {
            best_diff = diff;
            best_cells = cells;
            best_c = c;
            best_r = r;
        }
    }
    int c = best_c, r = best_r;

    int printed = 0;
    for (int i = 0; i < r && printed < lightCount; ++i) {
        for (int j = 0; j < c && printed < lightCount; ++j) {
            xs[printed] = ((j + 0.5) * length) / c;
            ys[printed] = ((i + 0.5) * width) / r;
            ++printed;
        }
    }
}

static int clampi(int v, int lo, int hi){ return v<lo?lo:(v>hi?hi:v); }

void PrintMeasurements(void) {
    if (length <= 0 || width <= 0 || lightCount <= 0) return;

    // Character cell width/height ratio. ~0.5 is a good default on most terminals.
    const double cw_over_ch = 0.5;

    // Choose columns; keep it readable.
    int cols = length < 100 ? (length < 30 ? 30 : length) : 100;
    // Preserve geometry: rows/ch / cols/cw = W/L  => rows = cols*(W/L)*(cw/ch)
    int rows = (int)lround((double)cols * ((double)width / (double)length) * cw_over_ch);
    if (rows < 10) rows = 10;
    if (rows > 60) rows = 60;

    // Allocate grid
    char **g = (char**)malloc(rows * sizeof(*g));
    for (int i = 0; i < rows; ++i) {
        g[i] = (char*)malloc(cols);
        for (int j = 0; j < cols; ++j) g[i][j] = ' ';
    }

    // Plot lights
    for (int k = 0; k < lightCount; ++k) {
        double nx = xs[k] / (double)length; // 0..1
        double ny = ys[k] / (double)width;  // 0..1
        int gx = (int)lround(nx * (cols - 1));
        int gy = (int)lround(ny * (rows - 1));
        if (gx < 0) gx = 0; if (gx >= cols) gx = cols - 1;
        if (gy < 0) gy = 0; if (gy >= rows) gy = rows - 1;
        g[gy][gx] = (g[gy][gx] == ' ') ? '*' : '#';
    }

    // Render
    printf("\nRoom %d x %d (L x W). Grid %d x %d\n", length, width, cols, rows);
    putchar('+'); for (int j = 0; j < cols; ++j) putchar('-'); putchar('+'); putchar('\n');
    for (int i = rows - 1; i >= 0; --i) {
        putchar('|');
        for (int j = 0; j < cols; ++j) putchar(g[i][j]);
        putchar('|');
        putchar('\n');
    }
    putchar('+'); for (int j = 0; j < cols; ++j) putchar('-'); putchar('+'); putchar('\n');
    printf("Legend: '*'=light, '#'=overlap. cell_w/ cell_h=%.2f\n", cw_over_ch);

    for (int i = 0; i < rows; ++i) free(g[i]);
    free(g);
}