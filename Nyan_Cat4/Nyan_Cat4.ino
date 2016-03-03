/*Nyancat for Arduboy Dev Kit
  by Fred Ting =D
 
  Nyan Cat Music
  with Bass
  Uses Arduino tone library pitches.h [http://arduino.cc/en/Tutorial/tone ]
       by electricmango
  https://electricmango.github.io

  Thanks to Sean for posting the sheet music on
  http://junket.tumblr.com/post/4776023022/heres-the-nyan-cat-sheet-music

  Version 1.0.3
  -------------------------------------------------------------------------
  Nyan Cat with Bass is licensed under the

  Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0)

  You are free to:

  Share — copy and redistribute the material in any medium or format
  Adapt — remix, transform, and build upon the material
  for any purpose, even commercially.
  The licensor cannot revoke these freedoms as long as you follow the license terms.

  Under the following terms:

  Attribution — You must give appropriate credit, provide a link to the license, and indicate if changes were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use.
  ShareAlike — If you remix, transform, or build upon the material, you must distribute your contributions under the same license as the original.

  No additional restrictions — You may not apply legal terms or technological measures that legally restrict others from doing anything the license permits.

  The full license is available at https://creativecommons.org/licenses/by-sa/4.0/legalcode

  Copyright (c) 2012 ~ 2015 electricmango
  -------------------------------------------------------------------------
  Nyan_Cat.ino
*/

#include "pitches.h"
#include "pics.h"
//#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
boolean y =0;

// If using software SPI (the default case):
#define OLED_MOSI   16//9
#define OLED_CLK   15//10
#define OLED_DC    4//11
#define OLED_CS    6//12
#define OLED_RESET 12//13
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

//notes in the melody, removed redundant notes and repeated sections instead:
const int melody[] = {
  NOTE_DS5, NOTE_E5, NOTE_FS5, 0, NOTE_B5, NOTE_E5, NOTE_DS5, NOTE_E5, NOTE_FS5, NOTE_B5, NOTE_DS6, NOTE_E6, NOTE_DS6, NOTE_AS5, NOTE_B5, 0,
  NOTE_FS5, 0, NOTE_DS5, NOTE_E5, NOTE_FS5, 0, NOTE_B5, NOTE_CS6, NOTE_AS5, NOTE_B5, NOTE_CS6, NOTE_E6, NOTE_DS6, NOTE_E6, NOTE_CS6,
  NOTE_FS4, NOTE_GS4, NOTE_D4, NOTE_DS4, NOTE_FS2, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_B3, NOTE_CS4,
  NOTE_D4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_FS4, NOTE_GS4, NOTE_DS4, NOTE_FS4, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_CS4, NOTE_B3,
  NOTE_DS4, NOTE_FS4, NOTE_GS4, NOTE_DS4, NOTE_FS4, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_D4, NOTE_DS4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_CS4,
  NOTE_D4, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_FS4, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_CS4, NOTE_B3, NOTE_CS4,
  NOTE_FS4, NOTE_GS4, NOTE_D4, NOTE_DS4, NOTE_FS2, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_B3, NOTE_CS4,
  NOTE_D4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_FS4, NOTE_GS4, NOTE_DS4, NOTE_FS4, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_CS4, NOTE_B3,
  NOTE_DS4, NOTE_FS4, NOTE_GS4, NOTE_DS4, NOTE_FS4, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_D4, NOTE_DS4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_CS4,
  NOTE_D4, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_FS4, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_CS4, NOTE_B3, NOTE_B3,
  NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_FS4,
  NOTE_B3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_FS3, NOTE_E4, NOTE_DS4, NOTE_CS4, NOTE_B3, NOTE_E3, NOTE_DS3, NOTE_E3, NOTE_FS3,
  NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_FS3,
  NOTE_B3, NOTE_B3, NOTE_AS3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_FS4, NOTE_B3, NOTE_AS3,
  NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_FS4,
  NOTE_B3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_FS3, NOTE_E4, NOTE_DS4, NOTE_CS4, NOTE_B3, NOTE_E3, NOTE_DS3, NOTE_E3, NOTE_FS3,
  NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_FS3,
  NOTE_B3, NOTE_B3, NOTE_AS3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_FS4, NOTE_B3, NOTE_CS4,
  NOTE_FS4, NOTE_GS4, NOTE_D4, NOTE_DS4, NOTE_FS2, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_B3, NOTE_CS4,

};

// note durations: 4 = quarter note, 8 = eighth note, etc
const int noteDurations[] = {
  16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
  16, 16, 16, 16, 16, 16, 8, 16, 16, 16, 16, 16, 16, 16, 16,
  8, 8, 16, 16, 16, 16, 16, 16, 8, 8, 8,
  8, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
  8, 8, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
  8, 16, 16, 16, 16, 16, 16, 16, 16, 8, 8, 8,
  8, 8, 16, 16, 16, 16, 16, 16, 8, 8, 8,
  8, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
  8, 8, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
  8, 16, 16, 16, 16, 16, 16, 16, 16, 8, 8, 8,
  8, 16, 16, 8, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
  8, 8, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
  8, 16, 16, 8, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
  8, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 8, 8,
  8, 16, 16, 8, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
  8, 8, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
  8, 16, 16, 8, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
  8, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 8, 8,
  8, 8, 16, 16, 16, 16, 16, 16, 8, 8, 8,
};

//Draw cat and move
void drawMeow(){
if (y) {
  display.clearDisplay();
  display.drawBitmap(30, 16,  nyanPic1, 48, 33, 1);
  display.display();
  y = 0;

}
else {
  display.clearDisplay();
  display.drawBitmap(40, 16,  nyanPic1, 48, 33, 1);
  display.display();
  y =1;
}
}


void setup() {
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC);
  // init done

  //Draw cat
  drawMeow();
  delay(1000);
}

void loop() {
  //Play music
  while (1) {
    //play into
    for (int thisNote = 0; thisNote < 42; thisNote++) {
      int noteDuration = 1100 / noteDurations[thisNote];
      tone(A2, melody[thisNote], noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      drawMeow();
      noTone(A2); //stop the tone playing:
    }
    display.drawBitmap(32, 16,  nyanPic1, 48, 33, 1);
    display.display();
    //iterate over the notes of the melody:
    for (int thisNote = 43; thisNote < 257; thisNote++) {
      int noteDuration = 1100 / noteDurations[thisNote];
      tone(A2, melody[thisNote], noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      drawMeow();
      noTone(A2); //stop the tone playing:
    }
    //iterate over the notes of the melody:
    for (int thisNote = 43; thisNote < 246; thisNote++) {
      int noteDuration = 1100 / noteDurations[thisNote];
      tone(A2, melody[thisNote], noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      drawMeow();
      noTone(A2); //stop the tone playing:
    }
  }
}


