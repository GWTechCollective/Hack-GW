// ACM Hackathon: Hack GW
// Brandon Bernier & Mark Tentindo
// MIDI-Keyboard Controlled LED Strip
// December 5, 2015
 
#define RED 5
#define GREEN 6
#define BLUE 3

#define NUM_KEYS 60
#define FIFTH NUM_KEYS/5
#define MAX_BRIGHTNESS 255 

#define BAUD 115200

int r, g, b;
float key = 255;
float brightness;
char buffer[10];

// Set up serial communication and define output pins
void setup() {
  Serial.begin(BAUD);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void loop() {
  if( Serial.available() > 0 ) {                 // Check to see if there is serial data available
    Serial.readBytesUntil('\n', buffer, 10);
    key = atoi(buffer);
  }
  
  // Set brightness of LEDs
  brightness = MAX_BRIGHTNESS;
  
  // Color spectrum divided into 5 ranges, then broken up based on the number of keys  
  if( key < 0 || key > 5*FIFTH ) {
    r = 0;
    g = 0;
    b = 0;
  }
  else if( key <= FIFTH ) {                      // Magenta (255-0-255) to Red (255-0-0)
    r = brightness - brightness*(key/FIFTH);
    g = 0;
    b = brightness;
  }
  else if( key <= 2*FIFTH ) {                    // Blue (0-0-255) to Cyan (0-255-255)
    r = 0;
    g = brightness*((key-FIFTH)/FIFTH);
    b = brightness;
  }
  else if( key <= 3*FIFTH ) {                    // Cyan (0-255-255) to Green (0-255-0)
    r = 0;
    g = brightness;
    b = brightness - brightness*((key-2*FIFTH)/FIFTH);
  }
  else if( key <= 4*FIFTH ) {                    // Green (0-255-0) to Yellow (255-255-0)
    r = brightness*((key-3*FIFTH)/FIFTH);
    g = brightness;
    b = 0; 
  }
  else if( key <= 5*FIFTH ) {                    // Yellow (255-255-0) to Red (255-0-0)
    r = brightness;
    g = brightness - brightness*((key-4*FIFTH)/FIFTH);
    b = 0;  
  } 
  
  // PWM to control RGB
  analogWrite(RED, r);
  analogWrite(GREEN, g);
  analogWrite(BLUE, b);

}
