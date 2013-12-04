#ifndef __ABSPRITE_H
#define __ABSPRITE_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#include "ab_lcd_image.h"
#include "abImage.h"

#define AB_SPRITE_SIZE 15
#define DEFAULT_MOVE_DIST 20
#define MAX_SCREEN_WIDTH 128
#define MAX_SCREEN_HEIGHT 160

class abSprite {
 private:
    int width;
    int height;
    abImage image;
 public:
    abSprite();

    int x_old;
    int x;
    int y_old;
    int y;
    int current_sheet;
    int max_sheet;

    void setImage(abImage image);
    abImage getImage();
    void setCoordinates(int x, int y);
    void setSize(int width, int height);

    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();

    void moveRight(int dist);
    void moveLeft(int dist);
    void moveUp(int dist);
    void moveDown(int dist);
    
    void undraw_old(Adafruit_ST7735 *tft, lcd_image_t *bg);
    void draw(Adafruit_ST7735 *tft);
};

#endif
