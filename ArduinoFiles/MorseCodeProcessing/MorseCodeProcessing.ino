const int buttonPin = 16;           // the number of the pushbutton pin
const float dot = 300;              // Time in ms
const float dash = 900;             // 3*dot
const float betweenSymbols = 300;   // 1*dot
const float betweenLetters = 900;   // 3*dot
const float betweenWords = 2100;    // 7*dot
const int letterSize = 100;
const int wordSize = 100;
const int sentenceSize = 100;

int buttonState = 0;              // variable for reading the pushbutton status
bool wasPressed = false;
bool firstPress = false;
float timestampOnPress = 0;       // timestampOnPress is used to get presstime
float timestampOnRelease = 0;     // timestampOnRelease is used to get releasetime
char letterHolder[letterSize];    // Holds current morse code word (e.g. Dash-Dot-Dot). 0 = Dot, 1 = Dash for letters
char wordHolder[wordSize];        // Holds letters for words
char sentenceHolder[sentenceSize];// Holds words for sentences

void setup() {
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  // initialize serial communication for Debugging:
  Serial.begin(19200);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  //Code in the if and else-if part will only be executed once after the button was pressed/released

  ///////////////////////////////////// PRESS ///////////////////////////////////////
  if (!wasPressed && buttonState == HIGH) {

    timestampOnPress = millis();

    if (firstPress) {
      float releaseTime = millis() - timestampOnRelease;
      Serial.print("Release Time: ");
      Serial.print(releaseTime);
      Serial.print("\n");

      //Sometimes unwanted releases with the time of 0 seconds register. We filter them out here
      if (releaseTime > 0.01f) {

        //TODO How shall we handle the times between "betweenSymbols"/"betweenLetters" and "betweenLetters"/"betweenWords"?
        if (releaseTime <= betweenSymbols) {
          //Nothing needs to happen
        } else if ((releaseTime > betweenSymbols) && (releaseTime <= betweenLetters)) {
          evalLetter();
        } else if (releaseTime > betweenLetters) {
          evalWord();
        }
      }
    }

    firstPress = true;
    wasPressed = true;
  }
  ///////////////////////////////////// RELEASE ///////////////////////////////////////
  else if (wasPressed && buttonState == LOW) {
    timestampOnRelease = millis();

    float pressTime = millis() - timestampOnPress;

    //Sometimes unwanted presses with the time of 0 seconds register. We filter them out here
    if (pressTime > 0.01f) {

      //TODO How shall we handle the times between dash and dot? Right now everything after dot time is registered as dash
      if (pressTime <= dot) {
        strcat(letterHolder, "0");
      } else {
        strcat(letterHolder, "1");
      }

      Serial.print("Symbol: ");
      Serial.print(letterHolder);
      Serial.print("\n");
    }
    wasPressed = false;
  }
}

void evalWord() {
  //Eval the last input as a letter
  evalLetter();
  //Add a space between words
  strcat(sentenceHolder, " ");
  //Add word to sentence
  strcat(sentenceHolder, wordHolder);
  
  for (int i = 1; i < wordSize; i++)
  {
    wordHolder[i] = ' ';
  }
  wordHolder[0] = '\0';

  Serial.print("Sentence: ");
  Serial.print(sentenceHolder);
  Serial.print("\n");
}

void evalLetter() {
  char letter;

  //WIESO KANN MAN IN C KEIN SWITCH STATEMENT MIT STRINGS MACHEN ARRRR
  if (strcmp(letterHolder, "01") == 0) {
    letter = 'A';
  } else if (strcmp(letterHolder, "1000") == 0) {
    letter = 'B';
  } else if (strcmp(letterHolder, "1010") == 0) {
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
    //ERROR
  }

  Serial.print("Letter: ");
  Serial.print(letter);
  Serial.print("\n");

  //Clear the letterHolder
  for (int i = 1; i < letterSize; i++)
  {
    letterHolder[i] = ' ';
  }
  letterHolder[0] = '\0';

  //Append char to wordHolder String
  strncat(wordHolder, &letter, 1);
}
