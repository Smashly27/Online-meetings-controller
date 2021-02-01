/*

 Write short description about the code/project here

*/

#include "Keyboard.h"

#define macOS 0
#define winOS 1
#define TEAMS 2
#define ZOOM 3


// constants won't change. They're used here to set pin numbers:
const int numOfInputs = 4;
const int buttonPins[numOfInputs] = {7,8,9,10}; // the number of the pushbutton pin
const int programPin = 3;
const int platformPin = 2;

int program = ZOOM;
int platform = macOS;

// Variables will change:
int buttonPressed = 1;       
int buttonState[numOfInputs];             // the current reading from the input pin
int lastButtonState[numOfInputs] = {LOW,LOW};// the previous reading from the input pin
bool inputFlags[numOfInputs] = {LOW,LOW};
int inputCounters[numOfInputs];

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime[numOfInputs] = {0,0};  // the last time the output pin was toggled
unsigned long debounceDelay = 5;    // the debounce time; increase if the output flickers

void setup() {
  for(int i = 0; i < numOfInputs; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  pinMode(programPin, INPUT_PULLUP);
  pinMode(platformPin, INPUT_PULLUP);
  Serial.begin(9600);
}


void loop() {
  if(digitalRead(platformPin) == HIGH) {
    platform = macOS; 
  }else {
    platform = winOS;
  }
  if(digitalRead(programPin) == HIGH) {
    program = TEAMS; 
  }else {
    program = ZOOM;
  }
setInputFlags();
resolveInputFlags();

}

void setInputFlags(){
    // read the state of the switch into a local variable:
  for (int i = 0; i < numOfInputs; i++) {
    int reading = digitalRead(buttonPins[i]);

    if (reading != lastButtonState[i]) {
    // reset the debouncing timer
      lastDebounceTime[i] = millis();
    }

  if ((millis() - lastDebounceTime[i]) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState[i]) {
      buttonState[i] = reading;

      // only toggle the LED if the new button state is Low
      if (buttonState[i] == LOW) {
        inputFlags[i] = HIGH;
      }
    }
  }


  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState[i] = reading;
}
}

void resolveInputFlags(){
  for(int i = 0; i < numOfInputs; i++)  {
    if(inputFlags[i] == HIGH) {
      inputCounters[i]++;
      updateKeyPress(i);
      inputFlags[i] = LOW;
    }
  }
}

void updateKeyPress(int input){
	//
	if(input == 0) {//participants
		if(platform == macOS){
			switch (program){
				case ZOOM:
					Keyboard.press(KEY_LEFT_GUI);
          Keyboard.press('u');
          delay(100);
          Keyboard.releaseAll();
					break;
				case TEAMS:
					Serial.println("No set action");
					break;
			}
		}else if(platform == winOS){
			switch (program){
				case ZOOM:
					Keyboard.press(KEY_LEFT_ALT);
          Keyboard.press('u');
          delay(100);
          Keyboard.releaseAll();
					break;
				case TEAMS:
					Serial.println("No set action");
					break;
			}
		}
	}else if(input == 1) { //Mic Mute
		if(platform == macOS){
			switch (program) {
				case ZOOM:
					Keyboard.press(KEY_LEFT_GUI);
					Keyboard.press(KEY_LEFT_SHIFT);
          Keyboard.press('a');
          delay(100);
          Keyboard.releaseAll();
					break;
				case TEAMS:
					Keyboard.press(KEY_LEFT_GUI);
					Keyboard.press(KEY_LEFT_SHIFT);
          Keyboard.press('m');
          delay(100);
          Keyboard.releaseAll();
					break;
			}
		}else if(platform == winOS){
			switch (program){
				case ZOOM:
					Keyboard.press(KEY_LEFT_ALT);
          Keyboard.press('a');
          delay(100);
          Keyboard.releaseAll();
					break;
				case TEAMS:
				  Keyboard.press(KEY_LEFT_CTRL);
					Keyboard.press(KEY_LEFT_SHIFT);
          Keyboard.press('m');
          delay(100);
          Keyboard.releaseAll();
					break;
			}
		}
	//
	}else if(input == 2) { //Video on/off
			if(platform == macOS){
				switch (program) {
					case ZOOM:
					  Keyboard.press(KEY_LEFT_GUI);
					  Keyboard.press(KEY_LEFT_SHIFT);
            Keyboard.press('v');
            delay(100);
            Keyboard.releaseAll();
						break;
					case TEAMS:
					  Keyboard.press(KEY_LEFT_GUI);
					  Keyboard.press(KEY_LEFT_SHIFT);
            Keyboard.press('o');
            delay(100);
            Keyboard.releaseAll();
						break;
				}
			}else if(platform == winOS){
				switch (program){
					case ZOOM:
						Keyboard.press(KEY_LEFT_ALT);
            Keyboard.press('v');
            delay(100);
            Keyboard.releaseAll();
						break;
					case TEAMS:
						Keyboard.press(KEY_LEFT_CTRL);
					  Keyboard.press(KEY_LEFT_SHIFT);
            Keyboard.press('o');
            delay(100);
            Keyboard.releaseAll();
						break;
				}
			}
	//
	}else if(input == 3) {//Screen Share
			if(platform == macOS){
				switch (program) {
					case ZOOM:
						Keyboard.press(KEY_LEFT_GUI);
					  Keyboard.press(KEY_LEFT_SHIFT);
            Keyboard.press('s');
            delay(100);
            Keyboard.releaseAll();
						break;
					case TEAMS:
						Keyboard.press(KEY_LEFT_GUI);
					  Keyboard.press(KEY_LEFT_SHIFT);
            Keyboard.press(' ');
            delay(100);
            Keyboard.releaseAll();
						break;
				}
			}else if(platform == winOS){
				switch (program){
					case ZOOM:
						Keyboard.press(KEY_LEFT_ALT);
            Keyboard.press('s');
            delay(100);
            Keyboard.releaseAll();
						break;
					case TEAMS:
						Keyboard.press(KEY_LEFT_CTRL);
					  Keyboard.press(KEY_LEFT_SHIFT);
            Keyboard.press(' ');
            delay(100);
            Keyboard.releaseAll();
						break;
				}
			}
}
}