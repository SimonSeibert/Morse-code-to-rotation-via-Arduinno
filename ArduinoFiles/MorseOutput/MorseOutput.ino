// constants won't change. They're used here to set pin numbers:
const int ledPin =  16;       // the number of the LED pin

int dot = 250;
int dash;
int betweenSymbols;
int betweenLetters;
int betweenWords;


// variables will change:
int buttonState = 0;          // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  //For Debugging
  Serial.begin(9600);

  //Morse Alphabet Times
  dash = dot * 3;
  betweenSymbols = dot;
  betweenLetters = dot * 3;
  betweenWords = dot * 7;

  //Test
  morseSentence("Das ist ein Test");
}

void loop() {
}

void morseSentence(char *sentence) {
  int i = 0;
  while (sentence[i] != '\0') {
    Serial.print("Now morseing letter '"); Serial.print(sentence[i]); Serial.println("'");
    morse(sentence[i]);
    i++;
  }
}

//isShort: True is dot, false is dash
void blink(bool isShort) {
  if (isShort) {
    digitalWrite(ledPin, HIGH);
    delay(dot);
    digitalWrite(ledPin, LOW);
    delay(betweenSymbols);
  } else {
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(betweenSymbols);
  }
}

// Letter to corresponding morse time
void morse(char c) {
  switch (c) {
    case 'A': case 'a': blink(true); blink(false); break;
    case 'B': case 'b': blink(false); blink(true); blink(true); blink(true); break;
    case 'C': case 'c': blink(false); blink(true); blink(false); blink(true); break;
    case 'D': case 'd': blink(false); blink(true); blink(true); break;
    case 'E': case 'e': blink(true); break;
    case 'F': case 'f': blink(true); blink(true); blink(false); blink(true); break;
    case 'G': case 'g': blink(false); blink(false); blink(true); break;
    case 'H': case 'h': blink(true); blink(true); blink(true); blink(true); break;
    case 'I': case 'i': blink(true); blink(true); break;
    case 'J': case 'j': blink(true); blink(false); blink(false); blink(false); break;
    case 'K': case 'k': blink(false); blink(true); blink(false); break;
    case 'L': case 'l': blink(true); blink(false); blink(true); blink(true); break;
    case 'M': case 'm': blink(false); blink(false); break;
    case 'N': case 'n': blink(false); blink(true); break;
    case 'O': case 'o': blink(false); blink(false); blink(false); break;
    case 'P': case 'p': blink(true); blink(false); blink(false); blink(true); break;
    case 'Q': case 'q': blink(false); blink(false); blink(true); blink(false); break;
    case 'R': case 'r': blink(true); blink(false); blink(true); break;
    case 'S': case 's': blink(true); blink(true); blink(true); break;
    case 'T': case 't': blink(false); break;
    case 'U': case 'u': blink(true); blink(true); blink(false); break;
    case 'V': case 'v': blink(true); blink(true); blink(true); blink(false); break;
    case 'W': case 'w': blink(true); blink(false); blink(false); break;
    case 'X': case 'x': blink(false); blink(true); blink(true); blink(false); break;
    case 'Y': case 'y': blink(false); blink(true); blink(false); blink(false); break;
    case 'Z': case 'z': blink(false); blink(false); blink(true); blink(true); break;
    case '1': blink(true); blink(false); blink(false); blink(false); blink(false); break;
    case '2': blink(true); blink(true); blink(false); blink(false); blink(false); break;
    case '3': blink(true); blink(true); blink(true); blink(false); blink(false); break;
    case '4': blink(true); blink(true); blink(true); blink(true); blink(false); break;
    case '5': blink(true); blink(true); blink(true); blink(true); blink(true); break;
    case '6': blink(false); blink(true); blink(true); blink(true); blink(true); break;
    case '7': blink(false); blink(false); blink(true); blink(true); blink(true); break;
    case '8': blink(false); blink(false); blink(false); blink(true); blink(true); break;
    case '9': blink(false); blink(false); blink(false); blink(false); blink(true); break;
    case '0': blink(false); blink(false); blink(false); blink(false); blink(false); break;
    case ' ': delay(betweenWords - betweenLetters - betweenSymbols); break; // Time between words is calculated like this because of the following calculation behind the switch case.
    default: Serial.println("Char not supported for LED output!"); break;
  }

  //After that the end of a letter is reached. The remaining pause time is calculated like this:
  delay(betweenLetters - betweenSymbols);
}
