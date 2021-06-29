#include <Servo.h>
#include <CapacitiveSensor.h>

const int buttonPin = 16;           // the number of the pushbutton pin
const int servoPin = 2;             // the number of the Servo pin

const float dot = 300;              // Time in ms
const float dash = 900;             // 3*dot
const float betweenSymbols = 300;   // 2*dot
const float betweenLetters = 900;   // 4*dot
const float betweenWords = 2100;    // 6*dot
const float betweenHex = 3000;      //10*dot

const int letterSize = 100;
const int wordSize = 100;
const int sentenceSize = 100;
const int hexSize = 1000;

int buttonState = 0;              // variable for reading the pushbutton status
bool wasPressed = false;          // Use this bool to see if the button was pressed. After it was pressed it will be put on false. That way the if else part in void loop() will only be executed one time.
bool firstPress = true;          // See explenation when it is used
float timestampOnPress = 0;       // timestampOnPress is used to get presstime
float timestampOnRelease = 0;     // timestampOnRelease is used to get releasetime
char letterHolder[letterSize];    // Holds current morse code word (e.g. Dash-Dot-Dot). 0 = Dot, 1 = Dash for letters
char wordHolder[wordSize];        // Holds letters for words
char sentenceHolder[sentenceSize];// Holds words for sentences
char hexHolder[hexSize];

Servo myservo;

CapacitiveSensor Sensor = CapacitiveSensor(2, 4);
const int capThreshhold = 400;        // Threshold for when capacitive reading reading counts as a press or a release
long capValue;                        // Value from capacitive reading

bool enableDIYsensor = false;
bool debugging = true;

void setup() {
  myservo.attach(servoPin);
  // initialize the pushbutton pin as an input and servo as output:
  pinMode(buttonPin, INPUT);
  pinMode(servoPin, OUTPUT);
  // initialize serial communication for Debugging:
  Serial.begin(9600);
}

void loop() {
  // Small delay to keep processing effort lower
  delay(20);
  // read value of capacitive foil
  if (enableDIYsensor) capValue = Sensor.capacitiveSensor(30);
  // read the state of the pushbutton value:
  if (!enableDIYsensor) buttonState = digitalRead(buttonPin);

  // Input with Button
  if (!enableDIYsensor) {
    //Code in the if and else-if part will only be executed once after the button was pressed/released
    if (!wasPressed && buttonState == HIGH) {
      onPress();
      wasPressed = true;
    }
    else if (wasPressed && buttonState == LOW) {
      onRelease();
      wasPressed = false;
    }
  }
  // Input with DIY Sensor
  else {
    if (!wasPressed && capValue >= capThreshhold) {
      onPress();
      wasPressed = true;
    }
    else if (wasPressed && capValue < capThreshhold) {
      onRelease();
      wasPressed = false;
    }
  }
}

void onPress() {
  timestampOnPress = millis(); //Gets time since execution start and current time in ms

  if (!firstPress) { //Ignore the release time between program start and the first press. Only start after the first press was done
    float releaseTime = millis() - timestampOnRelease; //get release time in ms by subtracting the timestamp from the current time
    if (debugging) {
      Serial.print("Release Time: ");
      Serial.print(releaseTime);
      Serial.print("\n");
    }
    //Sometimes unwanted releases with the time of 0 seconds register. We filter them out here
    if (releaseTime > 0.01f) {

      //TODO How shall we handle the times between "betweenSymbols"/"betweenLetters" and "betweenLetters"/"betweenWords"?
      if (releaseTime <= betweenSymbols) {
        //Nothing needs to happen
      }
      else if ((releaseTime > betweenSymbols) && (releaseTime <= betweenLetters)) {
        evalLetter();
      }
      else if ((releaseTime > betweenLetters) && (releaseTime <= betweenHex)) {
        evalWord();
      }
      else if (releaseTime > betweenLetters) {
        TranslateToHex();
        HexTurn();
        resetHolders();
        firstPress = true;
      }
    }
  }

  firstPress = false;
}

void onRelease() {
  timestampOnRelease = millis();

  float pressTime = millis() - timestampOnPress;

  //Sometimes unwanted presses with the time of 0 seconds register. We filter them out here
  if (pressTime > 0.01f) {

    //TODO How shall we handle the times between dash and dot? Right now everything after dot time is registered as dash
    if (pressTime <= dot) {
      strcat(letterHolder, "0"); //0 means dot
    } else {
      strcat(letterHolder, "1"); //1 means dash  --> Example: "01001" means dot-dash-dot-dot-dash. This will be used in the 'evalLetter()' function
    }
    if (debugging) {
      Serial.print("Symbol: ");
      Serial.print(letterHolder);
      Serial.print("\n");
    }

  }
}

void evalWord() {
  //Eval the last input as a letter
  evalLetter();
  //Add a space between words but not before the first one
  if (strlen(sentenceHolder) != 0) 
    strcat(sentenceHolder, " ");
  //Add word to sentence
  strcat(sentenceHolder, wordHolder);

  //Clear the wordHolder. (Maybe you can remove the for loop as "wordHolder[0] = '\0';" does the same job later.
  for (int i = 1; i < wordSize; i++)
  {
    wordHolder[i] = ' ';
  }
  //Set the first char in wordHolder to '\0'. That way it's enterpreted as an empty string.
  wordHolder[0] = '\0';

  if (debugging) {
    Serial.print("Sentence: ");
    Serial.print(sentenceHolder);
    Serial.print("\n");
  }

}

void evalLetter() {
  char letter;

  //WIESO KANN MAN IN C KEIN SWITCH STATEMENT MIT STRINGS MACHEN ARRRR
  if (strcmp(letterHolder, "01") == 0) {                //"01" means "Dot-Dash" which is A
    letter = 'A';
  } else if (strcmp(letterHolder, "1000") == 0) {       //"1000" means "Dash-Dot-Dot-Dot" which is B
    letter = 'B';
  } else if (strcmp(letterHolder, "1010") == 0) {       // Do this for all letters
    letter = 'C';
  } else if (strcmp(letterHolder, "100") == 0) {
    letter = 'D';
  } else if (strcmp(letterHolder, "0") == 0) {
    letter = 'E';
  } else if (strcmp(letterHolder, "0010") == 0) {
    letter = 'F';
  } else if (strcmp(letterHolder, "110") == 0) {
    letter = 'G';
  } else if (strcmp(letterHolder, "0000") == 0) {
    letter = 'H';
  } else if (strcmp(letterHolder, "00") == 0) {
    letter = 'I';
  } else if (strcmp(letterHolder, "0111") == 0) {
    letter = 'J';
  } else if (strcmp(letterHolder, "101") == 0) {
    letter = 'K';
  } else if (strcmp(letterHolder, "0100") == 0) {
    letter = 'L';
  } else if (strcmp(letterHolder, "11") == 0) {
    letter = 'M';
  } else if (strcmp(letterHolder, "10") == 0) {
    letter = 'N';
  } else if (strcmp(letterHolder, "111") == 0) {
    letter = 'O';
  } else if (strcmp(letterHolder, "0110") == 0) {
    letter = 'P';
  } else if (strcmp(letterHolder, "1101") == 0) {
    letter = 'Q';
  } else if (strcmp(letterHolder, "010") == 0) {
    letter = 'R';
  } else if (strcmp(letterHolder, "000") == 0) {
    letter = 'S';
  } else if (strcmp(letterHolder, "1") == 0) {
    letter = 'T';
  } else if (strcmp(letterHolder, "001") == 0) {
    letter = 'U';
  } else if (strcmp(letterHolder, "0001") == 0) {
    letter = 'V';
  } else if (strcmp(letterHolder, "011") == 0) {
    letter = 'W';
  } else if (strcmp(letterHolder, "1001") == 0) {
    letter = 'X';
  } else if (strcmp(letterHolder, "1011") == 0) {
    letter = 'Y';
  } else if (strcmp(letterHolder, "1100") == 0) {
    letter = 'Z';
  } else if (strcmp(letterHolder, "01111") == 0) {
    letter = '1';
  } else if (strcmp(letterHolder, "00111") == 0) {
    letter = '2';
  } else if (strcmp(letterHolder, "00011") == 0) {
    letter = '3';
  } else if (strcmp(letterHolder, "00001") == 0) {
    letter = '4';
  } else if (strcmp(letterHolder, "00000") == 0) {
    letter = '5';
  } else if (strcmp(letterHolder, "10000") == 0) {
    letter = '6';
  } else if (strcmp(letterHolder, "11000") == 0) {
    letter = '7';
  } else if (strcmp(letterHolder, "11100") == 0) {
    letter = '8';
  } else if (strcmp(letterHolder, "11110") == 0) {
    letter = '9';
  } else if (strcmp(letterHolder, "11111") == 0) {
    letter = '0';
  } else {
    //WARNING: A combination that isn't a word. How shall we handle this? Stop the program? Use "?" as a placeholder for "This letter doesn't exist"?
    if (debugging) Serial.println("Unknown Morse Combination. Adding '?' to word");
    letter = '?';
  }

  if (debugging) {
    Serial.print("Letter: ");
    Serial.print(letter);
    Serial.print("\n");
  }
  //Clear the letterHolder. (Maybe you can remove the for loop as "letterHolder[0] = '\0';" does the same job later.
  for (int i = 1; i < letterSize; i++)
  {
    letterHolder[i] = ' ';
  }
  //Set the first char in letterHolder to '\0'. That way it's enterpreted as an empty string.
  letterHolder[0] = '\0';

  //Append char to wordHolder String
  strncat(wordHolder, &letter, 1);
}


void TranslateToHex() { //Translate the morse code word into hex.
  evalWord();

  int i, j;         //Two counter vars we need later

  //converting str into Hex and add it into strH
  //In Ascii, every letter corresponds to 2 Hexadecimal numbers.
  //Thats why we count j+=2 but we need also a counter that increments by 1 which is i
  //We go through each charactor in our stirng
  for (i = 0, j = 0; i < strlen(sentenceHolder); i++, j += 3)
  {
    //Method declaration of sprintf: int sprintf(char *str, const char *format, ...)
    //E.g. "sprintf(str, "Value of Pi = %f", M_PI);" outputs "Value of Pi = 3.141593" and saves it in str -> That's exactly what we need
    //We go through each character in our string and convert it with the following format: (%02X) -> This turns a Ascii char into hex
    //Every converted char gets then added to strH.
    sprintf((char*) hexHolder + j, "%02X", sentenceHolder[i]);
    strcat(hexHolder, "_");
  }
  strcat(hexHolder, ".");   //Point at end of sentence
  hexHolder[j + 1] = '\0'; //Add Null at the end so we know when the string is completed

  Serial.println(hexHolder);
}

void HexTurn() {
  int turnTime = 500;
  for (int i = 0; i < hexSize; i++) {
    if (hexHolder[i] == '0') {
      myservo.write(11);
      delay(turnTime);
    }
    if (hexHolder[i] == '1') {
      myservo.write(22);
      delay(turnTime);
    }
    if (hexHolder[i] == '2') {
      myservo.write(33);
      delay(turnTime);
    }
    if (hexHolder[i] == '3') {
      myservo.write(44);
      delay(turnTime);
    }
    if (hexHolder[i] == '4') {
      myservo.write(55);
      delay(turnTime);
    }
    if (hexHolder[i] == '5') {
      myservo.write(66);
      delay(turnTime);
    }
    if (hexHolder[i] == '6') {
      myservo.write(77);
      delay(turnTime);
    }
    if (hexHolder[i] == '7') {
      myservo.write(88);
      delay(turnTime);
    }
    if (hexHolder[i] == '8') {
      myservo.write(99);
      delay(turnTime);
    }
    if (hexHolder[i] == '9') {
      myservo.write(110);
      delay(turnTime);
    }
    if (hexHolder[i] == 'A') {
      myservo.write(121);
      delay(turnTime);
    }
    if (hexHolder[i] == 'B') {
      myservo.write(132);
      delay(turnTime);
    }
    if (hexHolder[i] == 'C') {
      myservo.write(143);
      delay(turnTime);
    }
    if (hexHolder[i] == 'D') {
      myservo.write(154);
      delay(turnTime);
    }
    if (hexHolder[i] == 'E') {
      myservo.write(165);
      delay(turnTime);
    }
    if (hexHolder[i] == 'F') {
      myservo.write(176);
      delay(turnTime);
    }
    if (hexHolder[i] == '_') {
      myservo.write(0);
      delay(3000);
    }
    if (hexHolder[i] == '.') { //End of the word.
      int pos;

      for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
      }
      for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
      }

      for (int i = 1; i < letterSize; i++)
      {
        hexHolder[i] = ' ';
      }
      //Set the first char in letterHolder to '\0'. That way it's enterpreted as an empty string.
      hexHolder[0] = '\0';
      break;
    }
  }
}

void resetHolders() {
  for (int i = 1; i < letterSize; i++)
  {
    letterHolder[i] = ' ';
  }
  letterHolder[0] = '\0';

  for (int i = 1; i < wordSize; i++)
  {
    wordHolder[i] = ' ';
  }
  wordHolder[0] = '\0';

  for (int i = 1; i < sentenceSize; i++)
  {
    sentenceHolder[i] = ' ';
  }
  sentenceHolder[0] = '\0';

  for (int i = 1; i < hexSize; i++)
  {
    hexHolder[i] = ' ';
  }
  hexHolder[0] = '\0';
}
