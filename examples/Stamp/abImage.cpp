#include "abImage.h"

void abImage::setImage(char* filename, int width, int height) {
    this->lcd_image = (lcd_image_t) {filename, width, height};
}

lcd_image_t abImage::getImage() {
    return this->lcd_image;
}
