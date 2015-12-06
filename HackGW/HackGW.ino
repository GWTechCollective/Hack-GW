// ACM Hackathon: Hack GW
// Brandon Bernier & Mark Tentindo
// MIDI Keyboard Controlled LED Strip
// December 5, 2015
 
#define REDPIN 5
#define GREENPIN 6
#define BLUEPIN 3
#define BAUD 115200

#define NUM_KEYS 60
#define MAX_BRIGHTNESS 255 

int r, g, b;
float key=255;
float fifth, brightness;
char buffer[10];

void setup() {
  Serial.begin(BAUD);
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
}


void loop() {
  if( Serial.available() > 0 ) {
    Serial.readBytesUntil('\n', buffer, 10);
    key = atoi(buffer);
  }
  
  brightness = MAX_BRIGHTNESS;
  fifth = NUM_KEYS/5;
    
  if( key <= fifth ) {
    r = brightness - brightness*(key/fifth);
    g = 0;
    b = brightness;
  }
  else if( key <= 2*fifth ) {
    r = 0;
    g = brightness*((key-fifth)/fifth);
    b = brightness;
  }
  else if( key <= 3*fifth ) {
    r = 0;
    g = brightness;
    b = brightness - brightness*((key-2*fifth)/fifth);
  }
  else if( key <= 4*fifth ) {
    r = brightness*((key-3*fifth)/fifth);
    g = brightness;
    b = 0; 
  }
  else if( key <= 5*fifth ) {
    r = brightness;
    g = brightness - brightness*((key-4*fifth)/fifth);
    b = 0;  
  }
  else {
    r = 0;
    g = 0;
    b = 0;
  }
  
  analogWrite(REDPIN, r);
  analogWrite(GREENPIN, g);
  analogWrite(BLUEPIN, b);
}
