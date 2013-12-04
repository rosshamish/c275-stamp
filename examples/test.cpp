/*
  Tech Demo / Functionality Testing of:
    Stamp: a 2D Sprite Library for Adafruit ST7735 for Arduino
  
  Ross Anderson & Andrew Bradshaw

*/
#include "Stamp/Stamp.h"

// How many test sections to skip
#define TEST_LEVEL 0
// DEBUG means "enable delays during tests" aka "go slow"
#define DEBUG false

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {
    Serial.begin(9600);
    tft.initR(INITR_BLACKTAB);
    tft.fillScreen(ST7735_YELLOW);

    /*
      Setup SD Card
    */
    Serial.print("init'ing SD card..");
    if (!SD.begin(SD_CS)) {
        Serial.println("failed");
        return;
    }
    Serial.println("OK!");

    /*
      abImage.h
    */
    if (TEST_LEVEL <= 0) {
        // Test 0a: Set an image by filename, and manually draw to screen
        abImage img;
        img.setImage("o.lcd", AB_SPRITE_SIZE, AB_SPRITE_SIZE);
        lcd_image_draw_transparency(&img.getImage(), &tft,
                       0, 0,      // upper-left corner of IMAGE
                       0, 0,      // upper-left corner of SCREEN
                       AB_SPRITE_SIZE, AB_SPRITE_SIZE); // size of patch drawn

        /*
          abSprite.h
        */
    
        // Test 0b: Set sprite's image to an abImage, and draw it
		tft.fillScreen(ST7735_YELLOW);
        abSprite sprite;
        sprite.setImage(img);
        sprite.draw(&tft);
		if (DEBUG) delay(200);//ms

        // Test 0c: Set coordinates to something other than (0,0), and draw it.
		tft.fillScreen(ST7735_YELLOW);
        sprite.setCoordinates(50, 70);
        sprite.draw(&tft);

        // Test 0d: Move the image and draw it at each position
        for (int i=0; i < 10; i++) {
            for (int j=0; j < 10; j++) {
                sprite.setCoordinates(10*i, 10*j);
                sprite.draw(&tft);
            }
        }

    }

    /* 
       abLayer.h
    */
    if (TEST_LEVEL <= 1) {
	    // Create a layer
        lcd_image_t bg = {"bgyellow.lcd", 128, 160};
        abLayer layer = abLayer(bg);
        
        // Add sprite to layer
        abSprite* ptr_sprite = layer.addSprite("w.lcd", 0, 0);

        // Test 1a: Draw sprite directly
        ptr_sprite->draw(&tft);
        if (DEBUG) delay(1000);//ms

        // Test 1b: Draw layer (which contains the sprite)
        tft.fillScreen(ST7735_YELLOW);
        layer.draw(&tft);
        if (DEBUG) delay(1000);//ms

        // Test 1c: Add a second sprite to layer which goes off the screen
		//          and draw both sprites directly
		tft.fillScreen(ST7735_YELLOW);
        abSprite* ptr_sprite2 = layer.addSprite("juggle.lcd",120,150);
        ptr_sprite->draw(&tft);
        ptr_sprite2->draw(&tft);
        if (DEBUG) delay(1000);//ms

        // Test 2c: Draw layer, now containing 2 sprites
        tft.fillScreen(ST7735_YELLOW);
        layer.draw(&tft);
        if (DEBUG) delay(1000);//ms
    }

    /*
      Movement
    */
    if (TEST_LEVEL <= 2) {
        // Create a layer
        lcd_image_t bg2 = {"bgyellow.lcd", 128, 160};
        abLayer layer2 = abLayer(bg2);
        
        // Add a sprite to the layer
        abSprite* ptr_sprite2_0 = layer2.addSprite("juggle.lcd",50,50);

        // Draw layer
        layer2.draw(&tft);
        if (DEBUG) delay(1000);//ms

        // Test 2a: Move sprite in x and then draw the layer
        ptr_sprite2_0->moveRight();
        layer2.draw(&tft);
        if (DEBUG) delay(1000);//ms

        // Test 2b: Move sprite in y and then draw the layer
        ptr_sprite2_0->moveUp();
        layer2.draw(&tft);
        if (DEBUG) delay(1000);//ms
        
        // Test 2c: Add a second sprite to layer and then draw the layer
		abSprite* ptr_sprite2_1 = layer2.addSprite("seehappy.lcd",50,100);
		layer2.draw(&tft);
		if (DEBUG) delay(1000);//ms
	
        // Test 2d: Move both sprites and then draw the layer
		ptr_sprite2_1->moveDown(20);
		ptr_sprite2_0->moveLeft(20);
		layer2.draw(&tft);
		if (DEBUG) delay(1000);//ms
    }

    /*
      Quick Movement
    */
    if (TEST_LEVEL <= 3) {
      tft.fillScreen(ST7735_WHITE);

      // Create a layer
      lcd_image_t bg3 = {"bgyellow.lcd", 128, 160};
      abLayer layer3 = abLayer(bg3);

      // Add a sprite to the layer
      abSprite* juggler = layer3.addSprite("juggle.lcd",0,0);

      // Test 3a: Move across screen and draw on each movement
      for (int i=0; i < 5; i++) { 
	juggler->setCoordinates(0, juggler->y);
	juggler->moveDown();
	for (int j=0; j < 7; j++) {
	  juggler->moveRight();
	  layer3.draw(&tft);
	}
      }
    }

    /*
      DEMO: PACMAN and GHOST (2 Sprite Movement)
    */
    if (TEST_LEVEL <= 4) {
      // Create a layer
      lcd_image_t bg4 = {"bgpacman.lcd", 128, 160};
      abLayer layer4 = abLayer(bg4);

      // Add pacman sprite to the layer
      abSprite* pacman = layer4.addSprite("pacman.lcd",16,0);
      // Add ghost sprite to the layer
      abSprite* ghost = layer4.addSprite("ghost-a.lcd",0,0);

      // Demo 4: Animate a chase sequence, redrawing layer on each movement
      bool movingRight = true;
      for (int i=0; i < 8; i++) {
	for (int j=0; j < 6; j++) {
	  ghost->moveRight();
	  pacman->moveRight();
	  layer4.draw(&tft);
	  if (DEBUG) delay(200);//ms
	}
	pacman->moveDown();
	ghost->moveDown();
	pacman->moveLeft(120);
	ghost->moveLeft(120);
	layer4.draw(&tft);
      }
    }

    /*
      Removing Sprites
    */
    if (TEST_LEVEL <= 5) {
      // Create a layer
      lcd_image_t bg5 = {"bgyellow.lcd", 128, 160};
      abLayer layer5 = abLayer(bg5);
      
      // Add 'w' sprite to the layer
      abSprite* sprite_w = layer5.addSprite("w.lcd",15,0);
      // Add 'r' sprite to the layer
      abSprite* sprite_r = layer5.addSprite("r.lcd",0,0);
      
      // Draw the layer
      layer5.draw(&tft);
      if (DEBUG) delay(1000);//ms
      
      // Test 5a: Remove a sprite and redraw the layer
      layer5.removeSprite(sprite_w);
      layer5.draw(&tft);
      if (DEBUG) delay(1000);//ms
      
      // Test 5b: Remove the other sprite and redraw
      layer5.removeSprite(sprite_r);
      layer5.draw(&tft);
      if (DEBUG) delay(1000);//ms
	  
      // Test 5c: Attempt to remove a sprite that is ALREADY REMOVED and redraw
      layer5.removeSprite(sprite_r);
      layer5.draw(&tft);
      if (DEBUG) delay(1000);//ms
	  
      if (DEBUG) Serial.println("Successfully removed the non-existant sprite!");
	  
      // Test 5d: Add some sprites, move them, remove some, and redraw
      abSprite* h = layer5.addSprite("h.lcd", 0, 0);
      abSprite* e = layer5.addSprite("e.lcd", 15, 0);
      abSprite* l_1 = layer5.addSprite("l.lcd", 30, 0);
      abSprite* l_2 = layer5.addSprite("l.lcd", 45, 0);
      abSprite* o = layer5.addSprite("o.lcd", 60, 0);

      layer5.draw(&tft);
      if (DEBUG) delay(1000);//ms
	  
      h->moveDown(12);
      e->moveDown(9);
      l_1->moveDown(6);
      l_2->moveDown(3);
      o->moveDown(0);
      layer5.draw(&tft);
      if (DEBUG) delay(1000);//ms
	  
      h->moveDown(0);
      e->moveDown(6);
      l_1->moveDown(12);
      l_2->moveDown(18);
      o->moveDown(24);
      layer5.draw(&tft);
      if (DEBUG) delay(1000);//ms
	  
      abSprite* toRemove[] = {h, e, l_1, l_2, o};
      for (int i=0; i < 5; i++) {
	layer5.removeSprite(toRemove[i]);
	layer5.draw(&tft);
	delay(100);//ms
      }
    }
    
    /*
      Spritesheets

      Test counting from 1 to 10 using a spritesheet animation.
    */
    if (TEST_LEVEL <= 6) {
      // Create a layer
	  
      lcd_image_t bg6 = {"bgblack.lcd", 128, 160};
      
      abLayer layer6 = abLayer(bg6);
	  
      // Add 'count' sprite to the layer
      // Third value is number of sprites in sheet
      abSprite* sprite_bar = layer6.addSprite("count.lcd",15,15,10);
      
      
      for (int i=0; i < 5; i++) {
	int sheet = 0;
	while (sheet<10){
	  layer6.draw(&tft);
	  sprite_bar->moveDown(10);
	  if (DEBUG) delay(200);//ms
	  sheet++;
	}
	sprite_bar->moveRight(10);
	sprite_bar->moveUp(100);
      }
    }

    /*
      SPRITESHEET ANIMATION DEMO
    */
    if (TEST_LEVEL <= 7) {

    }

}

void loop() {}
