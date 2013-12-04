/*
  abImage.h
    Ross Anderson, Andrew Bradshaw
  
    Holds an lcd image file for other classes to use.
*/
#ifndef __ABIMAGE_H
#define __ABIMAGE_H

#include <Arduino.h>
#include "ab_lcd_image.h"

class abImage {
 private:
    lcd_image_t lcd_image;

 public:
    void setImage(char* filename, int width, int height);
    lcd_image_t getImage();
};

#endif
