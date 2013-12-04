#include "abLayer.h"
#include <stdlib.h>

abLayer::abLayer(lcd_image_t _background) {
    sprites = ll_new();
    background = _background;
    hasDrawnOnce = false;
    toEraseCount = 0;
}

abLayer::abLayer(char* bg_filename) {
   sprites = ll_new();
   lcd_image_t bg = {bg_filename, ST7735_WIDTH, ST7735_HEIGHT};
   background = bg;
   hasDrawnOnce = false;
   toEraseCount = 0;
}

abSprite* abLayer::addSprite(char* filename, int x, int y) {
  abSprite *newsprite = new abSprite();
  abImage img;
  img.setImage(filename, AB_SPRITE_SIZE, AB_SPRITE_SIZE);
  
  newsprite->setImage(img);
  newsprite->setCoordinates(x,y);
  newsprite->setSize(AB_SPRITE_SIZE, AB_SPRITE_SIZE);

  ll_append(sprites, newsprite);
  return newsprite;
}

abSprite* abLayer::addSprite(char* filename, int x, int y, int max_sheet) {
  abSprite *newsprite = new abSprite();
  abImage img;
  img.setImage(filename, AB_SPRITE_SIZE * max_sheet, AB_SPRITE_SIZE);
  
  newsprite->setImage(img);
  newsprite->setCoordinates(x,y);
  newsprite->setSize(AB_SPRITE_SIZE, AB_SPRITE_SIZE);
  newsprite->max_sheet = max_sheet;

  ll_append(sprites, newsprite);
  return newsprite;
}

void abLayer::removeSprite(abSprite *sprite) {
  ll_remove(sprites, sprite);
  toErase[toEraseCount++] = sprite;
}

void abLayer::draw(Adafruit_ST7735* tft) {
  if (!hasDrawnOnce) {
	lcd_image_draw(&background, tft,
				   0, 0,
				   0, 0,
				   128, 160);
	hasDrawnOnce = true;
  }

  abSprite* curSprite;
  ll_node* curnode;
  // UNDRAW
  curnode = sprites->head;
  while (curnode) {
	curSprite = curnode->value;
	
	// if it moved, undraw it
	if (curSprite->x != curSprite->x_old ||
		curSprite->y != curSprite->y_old) {
	  curSprite->undraw_old(tft, &background);
	}

	curnode = curnode->next;
  }

  // ERASE REMOVED SPRITES
  for (int i=0; i < toEraseCount; i++) {
	abSprite *cur = toErase[i];
	cur->x_old = cur->x;
	cur->y_old = cur->y;
	cur->undraw_old(tft, &background);
  }
  toEraseCount = 0; // reset

  // DRAW
  curnode = sprites->head;
  while (curnode) {
	curSprite = curnode->value;
	curSprite->draw(tft);
	curnode = curnode->next;
  }
}
