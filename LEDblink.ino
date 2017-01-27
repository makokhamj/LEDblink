//THIS IS THE BLINKING CODE PROVIDED BY GEORGE TOYE - FROM TUTORIAL
// I USED IT USED TO CONFIRM COMMUNICATION BETWEEN MY COMPUTER AND THE ARUINO

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

int keyF = 11;  // user button switch ==> faster
int keyS = 12;  // user button switch ==> slower

#define MAX_SELECT 4
int tperiod[MAX_SELECT] = {1000, 500, 250, 125};  // blink rates: 1/2sec,1/sec,2/sec,4/sec
int tselect;

long tnow, tnext = 0;
int ledState = LOW;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
  pinMode(keyF, INPUT);
  pinMode(keyS, INPUT);
  tselect = 1;      // select blink rate = 1 per sec
}

// the loop routine runs over and over again forever:
void loop() {

  tnow = millis();           // get current millisec counter value

  if (tnow >= tnext) {       // is it time to change the ledState?
    // YES: time to change, toggle ledState: HIGH->LOW, LOW->HIGH
    toggleLED();
    tnext = tnow + tperiod[tselect];    // set time of next ledState change
  }

  if (readUserKeyF()) tselect = blinkFaster();
  if (readUserKeyS()) tselect = blinkSlower(); 

  // beyond updating LED and checking on pushbuttons in this loop(), 
  // we can now do even more things here
  // between time now and when "tnext" occurs

}

void toggleLED(void) {
    if (ledState == HIGH) 
      ledState = LOW;
    else 
      ledState = HIGH;
    digitalWrite(led,ledState);  // make LED ON/OFF same as updated ledState
}

int blinkFaster(void) {
  if (tselect < MAX_SELECT-1)
    return (tselect+1);
  else
    return tselect;
}
int blinkSlower(void) {
  if (tselect > 0) 
    return (tselect - 1);
  else
    return tselect;
}

int readUserKeyF(void) {
  if (digitalRead(keyF) == LOW) return 1;
  else return 0;
}
int readUserKeyS(void) {
  if (digitalRead(keyS) == LOW) return 1;
  else return 0;
}
