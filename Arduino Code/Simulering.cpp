#pragma once
#include "Lib.h"

float originalGrid[ORIGINAL_SIZE][ORIGINAL_SIZE] = {
    {0.0, 0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0, 0.0}
};

float targetGrid[TARGET_SIZE][TARGET_SIZE] = {0};

void UpdateSmallGrid() {
    int sensorID = 0;
    for (int i = 0; i < ORIGINAL_SIZE; ++i) {
        for (int j = 0; j < ORIGINAL_SIZE; ++j) {
            originalGrid[i][j] = temperatures[sensorID][numPoints-1];
            sensorID++;
        }
    }
}

void bilinearInterpolate(float originalGrid[ORIGINAL_SIZE][ORIGINAL_SIZE], float targetGrid[TARGET_SIZE][TARGET_SIZE]) {
    float scale = (float)(ORIGINAL_SIZE - 1) / (TARGET_SIZE - 1);
    /*
    Scale sørger for at hvert punkt i det interpolerede grid vsrarer til den proportionale position i det originale grid.
    Skaleringsfaktoren, sikrer dermed, at der er en lige stor afstand mellem de originale sensor værdier i det nye grid.
    */
    for (int i = 0; i < TARGET_SIZE; ++i) {
        for (int j = 0; j < TARGET_SIZE; ++j) {
            float x = i * scale;
            float y = j * scale;

            int x1 = (int)x;
            int y1 = (int)y;
            int x2 = min(x1 + 1, ORIGINAL_SIZE - 1);
            int y2 = min(y1 + 1, ORIGINAL_SIZE - 1);

            float xWeight = x - x1;
            float yWeight = y - y1;

            float Q1 = originalGrid[x1][y1] * (1 - xWeight) * (1 - yWeight);
            float Q2 = originalGrid[x1][y2] * (1 - xWeight) * yWeight;
            float Q3 = originalGrid[x2][y1] * xWeight * (1 - yWeight);
            float Q4 = originalGrid[x2][y2] * xWeight * yWeight;

            targetGrid[i][j] = Q1 + Q2 + Q3 + Q4;
        }
    }
}

uint16_t getHeatmapColor(float value) {
    value = (value / 45.0f);
    uint8_t r = (uint8_t)(value * 255);
    uint8_t g = 0;
    uint8_t b = (uint8_t)((1 - value) * 255);
    return tft.color565(r, g, b);
}

void drawColormap(float targetGrid[TARGET_SIZE][TARGET_SIZE], int startX, int startY) {
  const int PixelSize = 8;
    for (int i = 0; i < TARGET_SIZE; ++i) {
        for (int j = 0; j < TARGET_SIZE; ++j) {
            uint16_t color = getHeatmapColor(targetGrid[i][j]);
            for (int dx = 0; dx < PixelSize; ++dx) {
                for (int dy = 0; dy < PixelSize; ++dy) {
                    tft.drawPixel(startX + j * PixelSize + dx, startY + i * PixelSize + dy, color);
                }
            }
        }
    }
}