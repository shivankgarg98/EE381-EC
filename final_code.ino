#include <CapacitiveSensor.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define COMMON_PIN      2    // The common 'send' pin for all keys
#define NUM_OF_SAMPLES  10   // Higher number whens more delay but more consistent readings
#define CAP_THRESHOLD   800  // Capactive reading that triggers a note (adjust to fit your needs)
#define OLED_RESET     12 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);

// This macro creates a capacitance "key" sensor object for each key on the piano keyboard:
#define CS(Y) CapacitiveSensor(2, Y)

// Defines the pins that the keys are connected to:
CapacitiveSensor keys[] = {CS(3), CS(4), CS(5), CS(6)};

int on = 0;
int mode = 0;
int fun = 0;
int recm = 0;
int* notes;
char button = 0;
char REC = 0;
int recorded_button[50];
int pev_button;
char button_index = 0;

void setup() {//I declare whether I'm using the pins for input/output 
  pinMode(10,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,INPUT);
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
   // Turn off autocalibrate on all channels:
  for(int i=0; i<4; ++i) {
    keys[i].set_CS_AutocaL_Millis(0xFFFFFFFF);
  }
  delay(500);
  
}

void Detect_button(){
  int notes1[] = {523,587, 659, 698, 784, 880, 988, 1047}; //An array storing all the notes. It's kind of like a dictionary.
  int notes2[] = {262, 294, 330, 349, 392, 440, 494, 523};
  long duration, distance; //Variables to store the values of time and length
  
  digitalWrite(7,LOW);
  delayMicroseconds(2);         
  digitalWrite(7,HIGH);      //This area sends out a pulse from the trigger
  delayMicroseconds(5);
  digitalWrite(7,LOW);                 
  duration = pulseIn(8, HIGH); //The echo is recieved, and saved as the duration
  
  distance = (duration/2)/29.1; // We convert the time into distance in centimeters, using the speed of sound and other factors.
  pev_button = button; //remember the previous button pressed by the user

     if(distance>4 && distance<40){
      if(fun%2 == 0){
        notes = notes1;
      }
      if(fun%2 ==1){
        notes = notes2;
      }
      if(distance>4&&distance<7){      //For a distance between 4 and 7, it plays C for 100 milliseconds
        tone(10,notes[0],100);
        button = 8;}
      else 
        if(distance>8&&distance<11){
        tone(10,notes[1],100); 
        button = 7;}     //For a distance between 8 and 11, it plays D for 100 milliseconds
      else
        if(distance>12&&distance<15){
        tone(10,notes[2],100);
        button = 6;     
        }//For a distance between 12 and 15, it plays E for 100 milliseconds
      else
        if(distance>16&&distance<19){
        tone(10,notes[3],100); 
        button = 5;  
        }//For a distance between 16 and 19, it plays F for 100 milliseconds
      else
        if(distance>20&&distance<23){
        tone(10,notes[4],100);  
        button = 4;   
        }//For a distance between 20 and 23, it plays G for 100 milliseconds
      else
        if(distance>24&&distance<27){
        tone(10,notes[5],100);  
        button = 3;   
         }//For a distance between 24 and 27, it plays A for 100 milliseconds
      else
        if(distance>28&&distance<31){
        tone(10,notes[6],100);  
        button = 2;   
        }//For a distance between 28 and 31, it plays B for 100 milliseconds
      else
        if(distance>32&&distance<35){
        tone(10,notes[7],100);  
        button = 1;   
        }//For a distance between 32 and 35, it plays high C for 100 milliseconds
        }
    else button = 0;
   
//Record the pressed buttons in a array
  if (button != pev_button && pev_button != 0)
  {
    recorded_button[button_index] = pev_button;
    button_index++;
    recorded_button[button_index] = 0;
    button_index++;
  }
//End of Recording program
} 

void loop() {     //This is the main loop, that keeps repeating
    // If the capacitance reading is greater than the threshold, play a note:
    if(keys[0].capacitiveSensor(NUM_OF_SAMPLES) > CAP_THRESHOLD){
       on++;
       delay(100);
      }
  
  
  if(on%2 == 0){
    Intro();
  }             
  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("Piano ON : play it"));
  display.println(F(""));
  display.setTextColor(BLACK, WHITE);
  display.println(F("Change Mode : Press 2"));
  display.println(F(""));
  display.setTextColor(WHITE, BLACK);
  display.println(F("Currently : Practice"));
  display.println(F("Change Note: Press 3"));
  display.println(F("To Play Recorded : Press 4"));
  display.display();
   if(mode%2 == 0){
    for(;;){
          if(keys[0].capacitiveSensor(NUM_OF_SAMPLES) > CAP_THRESHOLD){
           on++;
           loop();
           delay(100);
          }
          if(keys[1].capacitiveSensor(NUM_OF_SAMPLES) > CAP_THRESHOLD) {
          mode++;
          delay(100);
          }
          if(keys[2].capacitiveSensor(NUM_OF_SAMPLES) > CAP_THRESHOLD) {
          fun++;
          delay(100);
          }
          if(keys[3].capacitiveSensor(NUM_OF_SAMPLES) > CAP_THRESHOLD) {
            recm++;
            delay(100);
          }
     if(recm%2==0){
      if(keys[0].capacitiveSensor(NUM_OF_SAMPLES) > CAP_THRESHOLD){
           on++;
           loop();
           delay(100);
          }
          if(keys[1].capacitiveSensor(NUM_OF_SAMPLES) > CAP_THRESHOLD) {
          mode++;
          delay(100);
          }
          if(keys[2].capacitiveSensor(NUM_OF_SAMPLES) > CAP_THRESHOLD) {
          fun++;
          delay(100);
          }
         display.clearDisplay();
         display.setTextSize(1);             // Normal 1:1 pixel scale
         display.setTextColor(WHITE);        // Draw white text
         display.setCursor(0,0);             // Start at top-left corner
         display.println(F("Piano ON : Now Recording..."));
         display.println(F(""));
         display.setTextColor(BLACK, WHITE);
         display.println(F("Change Mode : Press 2"));
         display.println(F("Change Scale: Press 3"));
         display.display();
         Detect_button();
       }
       if(recm%2==1){
            if(keys[0].capacitiveSensor(NUM_OF_SAMPLES) > CAP_THRESHOLD){
           on++;
           loop();
           delay(100);
          }
          if(keys[1].capacitiveSensor(NUM_OF_SAMPLES) > CAP_THRESHOLD) {
          mode++;
          delay(100);
          }
          if(keys[2].capacitiveSensor(NUM_OF_SAMPLES) > CAP_THRESHOLD) {
          fun++;
          delay(100);
          }
     
            display.println(F("Now Playing Your Recorded Tune..."));
            display.display();
              for (int i = 0; i < sizeof(recorded_button) / 2; i++){
                
                delay(200); //Wait for before paying next tune
                if(keys[3].capacitiveSensor(NUM_OF_SAMPLES) > CAP_THRESHOLD) {
            recm++;
            break;
            delay(100);
          }
                if (recorded_button[i] == 0)
                  noTone(10); //user dint touch any button
                else
                  tone(10, notes[(recorded_button[i] - 1)]); //play the sound corresponding to the button touched by the user
                  if(keys[3].capacitiveSensor(NUM_OF_SAMPLES) > CAP_THRESHOLD) {
            recm++;
            break;
            delay(100);
          }
              }
            delay(100);
                 
      }

    if(mode%2 == 1){
        if(keys[0].capacitiveSensor(NUM_OF_SAMPLES) > CAP_THRESHOLD){
           on++;
           loop();
           delay(100);
          }
          if(keys[1].capacitiveSensor(NUM_OF_SAMPLES) > CAP_THRESHOLD) {
          mode++;
          delay(100);
          }
          if(keys[2].capacitiveSensor(NUM_OF_SAMPLES) > CAP_THRESHOLD) {
          fun++;
          delay(100);
          }
        display.clearDisplay();
        display.setTextSize(1);             // Normal 1:1 pixel scale
        display.setTextColor(WHITE);        // Draw white text
        display.setCursor(0,0);             // Start at top-left corner
        display.println(F("Piano ON : listen it"));
        display.println(F(""));
        display.setTextColor(BLACK, WHITE);
        display.println(F("Change Mode : Press 2"));
        display.println(F(""));
        display.setTextColor(WHITE, BLACK);
        display.println(F("Now: Harry Potter"));
        
        display.println(F("Change Song: Press 3"));
        display.display();
        LoadSong(1);
        
        display.clearDisplay();
        display.setTextSize(1);             // Normal 1:1 pixel scale
        display.setTextColor(WHITE);        // Draw white text
        display.setCursor(0,0);             // Start at top-left corner
        display.println(F("Piano ON : listen..."));
        display.println(F(""));
        display.setTextColor(BLACK, WHITE);
        display.println(F("Change Mode : Press 2"));
        display.println(F(""));
        display.setTextColor(WHITE, BLACK);
        display.println(F("Now: Twinkle Twinkle"));
        
        display.println(F("Change Song: Press 3"));
        display.display();
        LoadSong(2);

        display.clearDisplay();
        display.setTextSize(2);             // Normal 1:1 pixel scale
        display.setTextColor(WHITE);        // Draw white text
        display.setCursor(0,0);             // Start at top-left corner
        display.println(F("Oops!"));
        display.println(F(""));
        display.setTextColor(BLACK, WHITE);
        display.println(F("Playlist Over"));
        display.println(F(""));
        display.setTextColor(WHITE, BLACK);
        display.println(F("Now: Practice"));
        
        display.println(F("or Play again"));
        mode = 0; fun=0;
        display.display();
    }
    }
  }
}
void Intro(){
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
  display.println(F("PRESS ON to play piano"));
  display.display();      // Show initial text
  // Scroll in various directi ons, pausing in-between:
    display.startscrollright(0x00, 0x0F);
    display.invertDisplay(true);
    delay(1000);
    display.invertDisplay(false);
    delay(1000);
    mode = 0; fun = 0;
    for(;;)
    if(keys[0].capacitiveSensor(NUM_OF_SAMPLES) > CAP_THRESHOLD || on%2==1){
       on++;
       display.stopscroll();
       break;
       delay(100);
      }
    return;
}
void LoadSong(int load){
  if(load==1){
      int tempo2 = 400;
        setTone(10, 617, tempo2 * 1);
        setTone(10, 824, tempo2 * 1.5);
        setTone(10, 980, tempo2 *1.5);
        setTone(10, 873, tempo2 * 1);
        setTone(10, 824, tempo2 * 2);
        setTone(10, 1234, tempo2 * 1);
        setTone(10, 1100, tempo2 * 2.5);
        setTone(10, 925, tempo2 * 2.5);
  
        setTone(10,824, tempo2 * 1.5);
        setTone(10, 980, tempo2 * 0.5);
        setTone(10, 873, tempo2 * 1);
        setTone(10, 777, tempo2 * 2);
        setTone(10, 873, tempo2 * 1);
        setTone(10, 617, tempo2 * 2.5);
  }

  display.display();
}


void setTone(int pin, int note, int duration) {
  tone(pin, note, duration);
  delay(duration);
  noTone(pin);
}
