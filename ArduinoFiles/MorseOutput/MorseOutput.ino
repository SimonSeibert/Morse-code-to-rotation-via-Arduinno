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

//This function receives a string and outputs the corresponding morse code message
void morseSentence(char *sentence) {
  int i = 0;
  //Go through each character until the end is reached (End of string is marked with the char '\0')
  while (sentence[i] != '\0') {
    //For debugging
    Serial.print("Now morseing letter '"); Serial.print(sentence[i]); Serial.println("'");
    //Morse the letter
    morse(sentence[i]);
    i++;
  }
}

//This function takes a boolean and outputs a morse symbol. True is dot, false is dash
void blink(bool isShort) {
  //Dot
  if (isShort) {
    digitalWrite(ledPin, HIGH);
    delay(dot);
    digitalWrite(ledPin, LOW);
    delay(betweenSymbols);
  } 
  //Dash
  else {
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(betweenSymbols);
  }
}

void doDot() {
  blink(true);
}

void doDash() {
  blink(false);
}

// This function takes a character and outputs the morse code for that letter
void morse(char c) {
  switch (c) {
    case 'A': case 'a': doDot(); doDash(); break;
    case 'B': case 'b': doDash(); doDot(); doDot(); doDot(); break;
    case 'C': case 'c': doDash(); doDot(); doDash(); doDot(); break;
    case 'D': case 'd': doDash(); doDot(); doDot(); break;
    case 'E': case 'e': doDot(); break;
    case 'F': case 'f': doDot(); doDot(); doDash(); doDot(); break;
    case 'G': case 'g': doDash(); doDash(); doDot(); break;
    case 'H': case 'h': doDot(); doDot(); doDot(); doDot(); break;
    case 'I': case 'i': doDot(); doDot(); break;
    case 'J': case 'j': doDot(); doDash(); doDash(); doDash(); break;
    case 'K': case 'k': doDash(); doDot(); doDash(); break;
    case 'L': case 'l': doDot(); doDash(); doDot(); doDot(); break;
    case 'M': case 'm': doDash(); doDash(); break;
    case 'N': case 'n': doDash(); doDot(); break;
    case 'O': case 'o': doDash(); doDash(); doDash(); break;
    case 'P': case 'p': doDot(); doDash(); doDash(); doDot(); break;
    case 'Q': case 'q': doDash(); doDash(); doDot(); doDash(); break;
    case 'R': case 'r': doDot(); doDash(); doDot(); break;
    case 'S': case 's': doDot(); doDot(); doDot(); break;
    case 'T': case 't': doDash(); break;
    case 'U': case 'u': doDot(); doDot(); doDash(); break;
    case 'V': case 'v': doDot(); doDot(); doDot(); doDash(); break;
    case 'W': case 'w': doDot(); doDash(); doDash(); break;
    case 'X': case 'x': doDash(); doDot(); doDot(); doDash(); break;
    case 'Y': case 'y': doDash(); doDot(); doDash(); doDash(); break;
    case 'Z': case 'z': doDash(); doDash(); doDot(); doDot(); break;
    case '1': doDot(); doDash(); doDash(); doDash(); doDash(); break;
    case '2': doDot(); doDot(); doDash(); doDash(); doDash(); break;
    case '3': doDot(); doDot(); doDot(); doDash(); doDash(); break;
    case '4': doDot(); doDot(); doDot(); doDot(); doDash(); break;
    case '5': doDot(); doDot(); doDot(); doDot(); doDot(); break;
    case '6': doDash(); doDot(); doDot(); doDot(); doDot(); break;
    case '7': doDash(); doDash(); doDot(); doDot(); doDot(); break;
    case '8': doDash(); doDash(); doDash(); doDot(); doDot(); break;
    case '9': doDash(); doDash(); doDash(); doDash(); doDot(); break;
    case '0': doDash(); doDash(); doDash(); doDash(); doDash(); break;
    // The space means that a word is done. The time between words is calculated like this because a das/dot always has the delay "betweenSymbols" at the end.
    // Additionally (you can see it after the switch case) a delay of "betweenLetters" is done after each letter. This is why the delay between words is calculated like this.
    // It all adds up to the value of "betweenWords" 
    case ' ': delay(betweenWords - betweenLetters - betweenSymbols); break; 
    default: Serial.println("Char not supported for LED output!"); break;
  }

  //After that the end of a letter is reached. The remaining pause time is calculated like this, because a dash/dot always has the delay "betweenSymbols" at the end.
  delay(betweenLetters - betweenSymbols);
}
