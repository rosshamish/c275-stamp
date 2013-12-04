#include "abSprite.h"

abSprite::abSprite() {
    x_old = 0;
    x = MAX_SCREEN_WIDTH;
    y_old = 0;
    y = MAX_SCREEN_HEIGHT;
    width = AB_SPRITE_SIZE;
    height = AB_SPRITE_SIZE;
    current_sheet = 0;
    max_sheet = 1;
}


void abSprite::setImage(abImage image) {
    this->image = image;
}

abImage abSprite::getImage() {
    return this->image;
}

/* Coordinates and Size */

void abSprite::setCoordinates(int x, int y) {
    this->x = x;
    this->y = y;
}

void abSprite::setSize(int width, int height) {
    this->width = width;
    this->height = height;
}

/* Movement */

void abSprite::moveRight() {
    this->moveRight(DEFAULT_MOVE_DIST);
}
void abSprite::moveLeft() {
    this->moveLeft(DEFAULT_MOVE_DIST);
}
void abSprite::moveUp() {
    this->moveUp(DEFAULT_MOVE_DIST);
}
void abSprite::moveDown() {
    this->moveDown(DEFAULT_MOVE_DIST);
}


void abSprite::moveRight(int dist) {
    this->setCoordinates(this->x + dist, this->y);
}
void abSprite::moveLeft(int dist) {
    this->setCoordinates(this->x - dist, this->y);
}
void abSprite::moveUp(int dist) {
    this->setCoordinates(this->x, this->y - dist);
}
void abSprite::moveDown(int dist) {
    this->setCoordinates(this->x, this->y + dist);
}

/* Drawing */

void abSprite::undraw_old(Adafruit_ST7735 *tft, lcd_image_t *bg) {
  // Redraw background underneath old sprite location
  lcd_image_draw(bg, tft,
		 x_old, y_old,
		 x_old, y_old,
		 width, height);
}

void abSprite::draw(Adafruit_ST7735* tft) {
    int drawWidth = 0;
    int drawHeight = 0;

    if (x + width > tft->width() ) {
        drawWidth = tft->width() - x;
    } else {
        drawWidth = width;
    }
    if (y + height > tft->height() ) {
        drawHeight = tft->height() - y;
    } else {
        drawHeight = height;
    }
    
    this->x_old = this->x;
    this->y_old = this->y;

    lcd_image_draw_transparency(&image.getImage(), tft,
				0+(current_sheet*AB_SPRITE_SIZE), 0,
				x, y,
				drawWidth,drawHeight);
    // Increase current_sheet number (for animation)
    current_sheet = (current_sheet+1) % max_sheet;
}
