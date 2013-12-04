/*
  abLayer.h
    Ross Anderson, Andrew Bradshaw
  
  Keeps track of the sprites which are contained in a particular
  Layer. For use with Adafruit ST7735 TFT LCD screen.
*/
#ifndef __ABLAYER_H
#define __ABLAYER_H

#include <string.h>

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include "PinDefinitions.h"

#include "abImage.h"
#include "abSprite.h"
#include "ab_lcd_image.h"
#include "linked_list.h"

#define ST7735_WIDTH 128
#define ST7735_HEIGHT 160

class abLayer {
private:
  bool hasDrawnOnce;
  linked_list* sprites;
  lcd_image_t background;
  
  // Cache of sprites to be erased after removal (abLayer::removeSprite)
  abSprite* toErase[16];
  uint8_t toEraseCount;
    
public:
    abLayer(lcd_image_t _background);
    abLayer(char* bg_filename);

    abSprite* addSprite(char* filename, int x, int y);
    abSprite* addSprite(char* filename, int x, int y, int max_sheet);
    void removeSprite(abSprite *sprite);
    void draw(Adafruit_ST7735* tft);
};

#endif
