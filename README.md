# Stamp
### an Arduino 2D Sprite Library for Adafruit ST7735
by Ross Anderson and Andrew Bradshaw


## Contents:
* [Features](#Features)
* [Setup](#Setup)
* [Boilerplate/Template](#BoilerplateTemplate)
* [Usage](#Usage)  
* [Transparency](#Transparency)
* [Animation](#Animation)
* [Converting .bmp to .lcd](#Converting-bmp-to-lcd)

- - -

## Features:
* Transparency
* Animation
  * Using spritesheets
* Layers
  * For keeping sprites in a group
* Only **one** `draw()` call per frame
  * No more drawing each image individually


## Setup:
#### Required Libraries:
These must be in your default include path:  
[Adafruit_ST7735.h](https://github.com/adafruit/Adafruit-ST7735-Library)  
[SPI.h](http://arduino.cc/en/Reference/SPI)  
[SD.h](http://arduino.cc/en/Reference/SD)

#### Pins and Wiring
These `#define`s are included in `Stamp.h`. Wire up your Adafruit ST7735 accordingly.
```
#define SD_CS    5  // Chip select line for SD card
#define TFT_CS   6  // Chip select line for TFT display
#define TFT_DC   7  // Data/command line for TFT
#define TFT_RST  8  // Reset line for TFT (or connect to +5V)
```
Initialize your `Adafruit_ST7735` like so:  
`Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);`

### Boilerplate/Template
[Example File Structure and Boilerplate can be found here](https://github.com/RossHamish/STAMP--Boilerplate)  
Currently, all files must be in the same directory as the .cpp file with `setup()` and `loop()` in it. This is a known issue and will be fixed according to interest.

## Examples
[Examples can be found here](https://github.com/RossHamish/STAMP/examples)

## Usage:

#### abSprite
abSprite is the sprite type you will use. A sprite is essentially an image with a location. The sprite can be moved and drawn directly to the screen. Generally, you will want to create sprites using an [abLayer](#abLayer).  

#### abLayer
An abLayer is a container for all the sprites in a scene. A layer could be a level, a menu, a cut-scene, or similar. When you create a sprite on a layer, it gives you back a reference to that sprite. The layer can be drawn directly, which draws the background as well as all sprites on it.  
Example:
```
abLayer level_one = abLayer("background-filename.lcd");
abSprite *main_character = level_one.addSprite("main_character_image.lcd",X_COORDINATE,Y_COORDINATE);
level_one.draw(&tft); // Where tft is the Adafruit_ST7735 object, aka the screen you want to draw to

while (gameOn) {
  if (joystick_right) {
    main_character->moveRight(); // Will move a default distance
  } else if (joystick_left) {
    main_character->moveLeft(20); // Will move the specified distance, in pixels.
  }
  level_one.draw(&tft); // Where tft is the Adafruit_ST7735 screen object.
}
```

#### Transparency
Transparency is vital to an application looking great on the LCD screen. Stamp handles transparency like so:  
The **top-left pixel** in the image is the **transparency marker**. Any other pixel that is the same color **will not be drawn**. The top-left pixel will *never* be drawn. This allows for any color of images. Just set the top-left pixel to something not in the image, and fill in the pixels you want transparent with that color. Stamp will ignore those pixels, and voila. Transparency.

#### Animation
Stamp does animation with *spritesheets*. A spritesheet is a bunch of images stacked side-by-side in a single image file. For example, if we wanted to animate a countdown, we could use the following spritesheet (imagine this is an image):  
```
countdown_spritesheet.lcd
---------------------
| 5 | 4 | 3 | 2 | 1 |
---------------------
```
In code, the only change is that we must specify the number of animation frames. In this case, there are 5.  
```
abLayer* some_level = abLayer("level_background.lcd");
abSprite* animated_countdown = abLayer.addSprite("countdown_spritesheet.lcd",X_COORDINATE,Y_COORDINATE,5);
while (gameOn) {
  some_level.draw(&tft); // Where tft is the Adafruit_ST7735 screen object.
}
```
Every time the layer draws, it will move over one image in the spritesheet. When it gets to the end, it will cycle back to the first one.

#### Converting .bmp to .lcd
You will need to convert your images to native LCD images before using the library, as it only takes filenames of type "filename.lcd". This is to improve performance. A quick google finds some information [here](http://arduinoexplained.blogspot.ca/2012/05/image-slideshow-with-arduino.html) on how to do the conversion. At the time of writing, that tool is only a Linux program, but I'm sure you can find others online. Just search "bmp to lcd conversion".

Alternatively, if you are at the University of Alberta, just use the convert-bmp-to-lcd.sh shell script provided by the CMPUT 274/275 professors.

**IMPORTANT**: The library **reads from the SD card, and the SD card **must be initialized** before use. This is outlined more clearly in the [boilerplate code](https://github.com/RossHamish/Stamp--Boilerplate) as well as in the [examples](https://github.com/RossHamish/Stamp/examples). 
=======
# Stamp
### an Arduino 2D Sprite Library for Adafruit ST7735
by Ross Anderson and Andrew Bradshaw


## Contents:
* [Features](#Features)
* [Setup](#Setup)
* [Boilerplate/Template](#BoilerplateTemplate)
* [Usage](#Usage)  
* [Transparency](#Transparency)
* [Animation](#Animation)
* [Converting .bmp to .lcd](#Converting-bmp-to-lcd)

- - -

## Features:
* Transparency
* Animation
  * Using spritesheets
* Layers
  * For keeping sprites in a group
* Only **one** `draw()` call per frame
  * No more drawing each image individually


## Setup:
#### Getting Going:
Just dump all the files inside `Stamp/` into the directory which includes your .cpp file with `setup()` and `loop()` in it. Then, `#include "Stamp.h". That's it!

To run the example, copy all the files in the `images` folder onto an SD card, put the SD card in the ST7735 Screen, and `make upload` from inside the `examples` directory.

#### Required Libraries:
These must be in your default include path:  
[Adafruit_ST7735.h](https://github.com/adafruit/Adafruit-ST7735-Library)  
[SPI.h](http://arduino.cc/en/Reference/SPI)  
[SD.h](http://arduino.cc/en/Reference/SD)

#### Pins and Wiring
These `#define`s are included in `Stamp.h`. Wire up your Adafruit ST7735 accordingly.
```
#define SD_CS    5  // Chip select line for SD card
#define TFT_CS   6  // Chip select line for TFT display
#define TFT_DC   7  // Data/command line for TFT
#define TFT_RST  8  // Reset line for TFT (or connect to +5V)
```
Initialize your `Adafruit_ST7735` like so:  
`Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);`

### Boilerplate/Template
[Example File Structure and Boilerplate can be found here](https://github.com/RossHamish/STAMP--Boilerplate)  
Currently, all files must be in the same directory as the .cpp file with `setup()` and `loop()` in it. This is a known issue and will be fixed according to interest.

## Examples
[Examples can be found here](https://github.com/RossHamish/Stamp/tree/master/examples)

## Usage:

#### abSprite
abSprite is the sprite type you will use. A sprite is essentially an image with a location. The sprite can be moved and drawn directly to the screen. Generally, you will want to create sprites using an [abLayer](#abLayer).  

#### abLayer
An abLayer is a container for all the sprites in a scene. A layer could be a level, a menu, a cut-scene, or similar. When you create a sprite on a layer, it gives you back a reference to that sprite. The layer can be drawn directly, which draws the background as well as all sprites on it.  
Example:
```
abLayer level_one = abLayer("background-filename.lcd");
abSprite *main_character = level_one.addSprite("main_character_image.lcd",X_COORDINATE,Y_COORDINATE);
level_one.draw(&tft); // Where tft is the Adafruit_ST7735 object, aka the screen you want to draw to

while (gameOn) {
  if (joystick_right) {
    main_character->moveRight(); // Will move a default distance
  } else if (joystick_left) {
    main_character->moveLeft(20); // Will move the specified distance, in pixels.
  }
  level_one.draw(&tft); // Where tft is the Adafruit_ST7735 screen object.
}
```

#### Transparency
Transparency is vital to an application looking great on the LCD screen. Stamp handles transparency like so:  
The **top-left pixel** in the image is the **transparency marker**. Any other pixel that is the same color **will not be drawn**. The top-left pixel will *never* be drawn. This allows for any color of images. Just set the top-left pixel to something not in the image, and fill in the pixels you want transparent with that color. Stamp will ignore those pixels, and voila. Transparency.

#### Animation
Stamp does animation with *spritesheets*. A spritesheet is a bunch of images stacked side-by-side in a single image file. For example, if we wanted to animate a countdown, we could use the following spritesheet (imagine this is an image):  
```
countdown_spritesheet.lcd
---------------------
| 5 | 4 | 3 | 2 | 1 |
---------------------
```
In code, the only change is that we must specify the number of animation frames. In this case, there are 5.  
```
abLayer* some_level = abLayer("level_background.lcd");
abSprite* animated_countdown = abLayer.addSprite("countdown_spritesheet.lcd",X_COORDINATE,Y_COORDINATE,5);
while (gameOn) {
  some_level.draw(&tft); // Where tft is the Adafruit_ST7735 screen object.
}
```
Every time the layer draws, it will move over one image in the spritesheet. When it gets to the end, it will cycle back to the first one.

#### Converting .bmp to .lcd
You will need to convert your images to native LCD images before using the library, as it only takes filenames of type "filename.lcd". This is to improve performance. A quick google finds some information [here](http://arduinoexplained.blogspot.ca/2012/05/image-slideshow-with-arduino.html) on how to do the conversion. At the time of writing, that tool is only a Linux program, but I'm sure you can find others online. Just search "bmp to lcd conversion".

Alternatively, if you are at the University of Alberta, just use the convert-bmp-to-lcd.sh shell script provided by the CMPUT 274/275 professors.

**IMPORTANT**: The library **reads from the SD card, and the SD card must be initialized** before use. This is outlined more clearly in the [boilerplate code](https://github.com/RossHamish/Stamp--Boilerplate) as well as in the [examples](https://github.com/RossHamish/Stamp/tree/master/examples).
