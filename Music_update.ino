/**************************************************************************
 This is an example for our Monochrome OLEDs based on SSD1306 drivers

 Pick one up today in the adafruit shop!
 ------> http://www.adafruit.com/category/63_98

 This example is for a 128x32 pixel display using I2C to communicate
 3 pins are required to interface (two I2C and one reset).

 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source
 hardware by purchasing products from Adafruit!

 Written by Limor Fried/Ladyada for Adafruit Industries,
 with contributions from the open source community.
 BSD license, check license.txt for more information
 All text above, and the splash screen below must be
 included in any redistribution.
 **************************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
int sp =10;
void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  display.clearDisplay();

  display.display();
  delay(1000);
  // display.display() is NOT necessary after every single drawing command,
  // unless that's what you want...rather, you can batch up a bunch of
  // drawing operations and then update the screen all at once by calling
  // display.display(). These examples demonstrate both approaches...
  Intro();    // Draw 'stylized' character
}

void loop() {
  display.clearDisplay();
  int val = analogRead(0);
  val = map(val, 0, 1020, 0, 15);
  analogWrite(9, val);
  volume(val); 
}

struct MusicStruct {
  int A = 550;
  int As = 582;
  int B = 617;
  int C = 654;
  int Cs = 693;
  int D = 734;
  int Ds = 777;
  int E = 824;
  int F = 873;
  int Fs = 925;
  int G = 980;
  int Gs = 1003;
  int A2 = 1100;
  int A2s = 1165;
  int B2 = 1234;
  int C3 = 1308;
  int C3s = 1385;
  int D3 = 1555;
}Music;

struct LengthStruct {
  float half = 0.5;
  float one = 1.0;
  float one_half = 1.5;
  float two = 2.0;
  float two_half = 2.5;
}Length;

int tempo2 = 400;

void piano(int val){
  display.clearDisplay();
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.print(F("Volume: ")); display.println(val);
  display.println("Piano Mode ON");

  
  display.display();
  delay(30);
   
}

void record(int val){
  display.clearDisplay();
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.print(F("Volume: ")); display.println(val);
  display.println("Record Mode ON");


  display.display();
  delay(30);
}

void play(int val){
  display.clearDisplay();
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.print(F("Volume: ")); display.println(val);
  display.println("Play Mode ON: Playing Last saved Recording");


  display.display();
  delay(30);
}
int load = 0;
void LoadSong(int val){
  display.clearDisplay();
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.print(F("Volume: ")); display.println(val);
    if(load%3==0){
        display.println("Playing Harry Potter");
        setTone(7, Music.B, tempo2 * Length.one);
        setTone(7, Music.E, tempo2 * Length.one_half);
        setTone(7, Music.G, tempo2 * Length.half);
        setTone(7, Music.F, tempo2 * Length.one);
        setTone(7, Music.E, tempo2 * Length.two);
        setTone(7, Music.B2, tempo2 * Length.one);
        setTone(7, Music.A2, tempo2 * Length.two_half);
        setTone(7, Music.Fs, tempo2 * Length.two_half);
  
        setTone(7, Music.E, tempo2 * Length.one_half);
        setTone(7, Music.G, tempo2 * Length.half);
        setTone(7, Music.F, tempo2 * Length.one);
        setTone(7, Music.Ds, tempo2 * Length.two);
        setTone(7, Music.F, tempo2 * Length.one);
        setTone(7, Music.B, tempo2 * Length.two_half);
  }
  else if(load%3==1){
     display.println("Playing Nursuery Rhymes");
     display.println("twinkle twinkle");
     char notes1[] = "ccggaag ffeeddc ggffeed ggffeed ccggaag ffeeddc "; // a space represents a rest
     int beats1[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
     int tempo1 = 300;
     int length = 15;
     for (int i = 0; i < length; i++) {
     if (notes1[i] == ' ') {
       delay(beats1[i] * tempo1); // rest
      } else {
       playNote(notes1[i], beats1[i] * tempo1);
      }
    
     // pause between notes
    delay(tempo1 / 2); 
    }
  }

  if(load%3==2){
    display.println("Playing Happy Birthday");
    int length = 28; // the number of notes
    char notes2[] = "GGAGcB GGAGdc GGxecBA yyecdc";
    int beats2[] = { 2, 2, 8, 8, 8, 16, 1, 2, 2, 8, 8,8, 16, 1, 2,2,8,8,8,8,16, 1,2,2,8,8,8,16 };
    int tempo = 150;
  for (int i = 0; i < length; i++) {
   if (notes2[i] == ' ') {
     delay(beats2[i] * tempo); // rest
   } else {
     playNote(notes2[i], beats2[i] * tempo);
 }
   // pause between notes
   delay(tempo);
}
  }

  display.display();
  delay(30);
}
void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(sp, HIGH);
    delayMicroseconds(tone);
    digitalWrite(sp, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
char names[] = {'C', 'D', 'E', 'F', 'G', 'A', 'B',    
                 'c', 'd', 'e', 'f', 'g', 'a', 'b','x', 'y' };
int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014,956,  834,  765,  593,  468,  346,  224,655 , 715 };
int SPEE = 5;
// play the tone corresponding to the note nam
    for (int i = 0; i < 17; i++) {
      if (names[i] == note) {
       int newduration = duration/SPEE;
       playTone(tones[i], newduration);
      }
    }
}
void setTone(int pin, int note, int duration) {
  tone(pin, note, duration);
  delay(duration);
  noTone(pin);
}

void volume(int val) {
  display.clearDisplay();
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.print(F("Volume: ")); display.println(val);
  display.display();
  delay(30);
}

void Intro(void) {
  display.clearDisplay();

  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(F("Shivank Garg 160658"));
  display.println(F("Shruti Shukla 160667"));
  display.println(F(""));
  display.println(F("EE381A EC Lab"));
  display.println(F("The Music Launchpad"));
  display.println(F(""));
  display.setTextColor(BLACK, WHITE); // Draw 'inverse' text
  display.println(F("PRESS ON to play"));
  
  display.display();      // Show initial text
  delay(100);
  for(;;){
  // Scroll in various directions, pausing in-between:
    display.startscrollright(0x00, 0x0F);
    display.invertDisplay(true);
    delay(1000);
    display.invertDisplay(false);
    delay(1000);
  }
}
