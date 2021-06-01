// constants won't change. They're used here to set pin numbers:
const int buttonPin = 14;     // the number of the pushbutton pin
const int ledPin =  16;      // the number of the LED pin
const int sd = 250;
const int ld = 750;
const int pd = 250;

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

//True is short, false is long
void blink(bool isShort) {
  if(isShort) {
    digitalWrite(ledPin, HIGH);
    delay(sd);
    digitalWrite(ledPin, LOW);
    delay(pd);
  } else {
    digitalWrite(ledPin, HIGH);
    delay(ld);
    digitalWrite(ledPin, LOW);
    delay(pd);
  }
}

//Morse a letter, TODO: Add all letters
void morse(char c) {
  switch(c) {
    case 'S':
      blink(true);
      blink(true);
      blink(true);
      break;
    case 'I':
      blink(true);
      blink(true);
      break;
    case 'M':
      blink(false);
      blink(false);
      break;
    case 'O':
      blink(false);
      blink(false);
      blink(false);
      break;
    case 'N':
      blink(false);
      blink(true);
      break;
  }
}

void morseSimon() {
  morse('S');
  morse('I');
  morse('M');
  morse('O');
  morse('N');
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // blink 'Simon' in morse Code:
    morseSimon();
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
}
