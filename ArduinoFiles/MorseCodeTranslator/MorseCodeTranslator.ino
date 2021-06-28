const int buttonPin = D1;           // the number of the pushbutton pin
const float dot = 500;              // Time in ms
const float dash = 1500;             // 3*dot
const float betweenSymbols = 1000;   // 2*dot
const float betweenLetters = 2000;   // 4*dot
const float betweenWords = 3000;    // 6*dot
const float betweenHex = 5000;      //10*dot
const int letterSize = 100;
const int wordSize = 100;
const int sentenceSize = 100;
const int hexSize = 1000;

int buttonState = 0;              // variable for reading the pushbutton status
bool wasPressed = false;          // Use this bool to see if the button was pressed. After it was pressed it will be put on false. That way the if else part in void loop() will only be executed one time.
bool firstPress = false;          // See explenation when it is used
float timestampOnPress = 0;       // timestampOnPress is used to get presstime
float timestampOnRelease = 0;     // timestampOnRelease is used to get releasetime
char letterHolder[letterSize];    // Holds current morse code word (e.g. Dash-Dot-Dot). 0 = Dot, 1 = Dash for letters
char wordHolder[wordSize];        // Holds letters for words
char sentenceHolder[sentenceSize];// Holds words for sentences
char hexHolder[hexSize];
bool debugging;

#include <Servo.h>

Servo myservo;

void setup() {
  myservo.attach(D3);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  if (debugging) {
    // initialize serial communication for Debugging:
    Serial.begin(9600);
  }

}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  //Code in the if and else-if part will only be executed once after the button was pressed/released

  ///////////////////////////////////// PRESS ///////////////////////////////////////
  if (!wasPressed && buttonState == HIGH) {

    timestampOnPress = millis(); //Gets time since execution start and current time in ms

    if (firstPress) { //Ignore the release time between program start and the first press. Only start after the first press was done
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
        } else if ((releaseTime > betweenSymbols) && (releaseTime <= betweenLetters)) {
          evalLetter();
        } else if ((releaseTime > betweenLetters) && (releaseTime <= betweenHex)) {
          evalWord();
        }
        else if (releaseTime > betweenLetters) {
          TranslateToHex();
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
    wasPressed = false;
  }
}

void evalWord() {
  //Eval the last input as a letter
  evalLetter();
  //Add word to sentence
  strcat(sentenceHolder, wordHolder);
  //Add a space between words
  strcat(sentenceHolder, " ");

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
    //ERROR
    if (debugging) {
      Serial.print("Fehler!! >:( \n");      //A combination that isn't a word. How shall we handle this? Stop the program? Use "?" as a placeholder for "This letter doesn't exist"?
    }
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
  char senletter;
  char senholder[4];
  for (int i = 0; i < sentenceSize; i++) {
    senletter = sentenceHolder[i];

    if (senletter == 'A') {
      strcat(senholder, "41_");
    } else if (senletter == 'B') {
      strcat(senholder, "42_");
    } else if (senletter == 'C') {
      strcat(senholder, "43_");
    } else if (senletter == 'D') {
      strcat(senholder, "44_");
    } else if (senletter == 'E') {
      strcat(senholder, "45_");
    } else if (senletter == 'F') {
      strcat(senholder, "46_");
    } else if (senletter == 'G') {
      strcat(senholder, "47_");
    } else if (senletter == 'H') {
      strcat(senholder, "48_");
    } else if (senletter == 'I') {
      strcat(senholder, "49_");
    } else if (senletter == 'J') {
      strcat(senholder, "4A_");
    } else if (senletter == 'K') {
      strcat(senholder, "4B_");
    } else if (senletter == 'L') {
      strcat(senholder, "4C_");
    } else if (senletter == 'M') {
      strcat(senholder, "4D_");
    } else if (senletter == 'N') {
      strcat(senholder, "4E_");
    } else if (senletter == 'O') {
      strcat(senholder, "4F_");
    } else if (senletter == 'P') {
      strcat(senholder, "50_");
    } else if (senletter == 'Q') {
      strcat(senholder, "51_");
    } else if (senletter == 'R') {
      strcat(senholder, "52_");
    } else if (senletter == 'S') {
      strcat(senholder, "53_");
    } else if (senletter == 'T') {
      strcat(senholder, "54_");
    } else if (senletter == 'U') {
      strcat(senholder, "55_");
    } else if (senletter == 'V') {
      strcat(senholder, "56_");
    } else if (senletter == 'W') {
      strcat(senholder, "57_");
    } else if (senletter == 'X') {
      strcat(senholder, "58_");
    } else if (senletter == 'Y') {
      strcat(senholder, "59_");
    } else if (senletter == 'Z') {
      strcat(senholder, "5A_");
    } else if (senletter == '1') {
      strcat(senholder, "31_");
    } else if (senletter == '2') {
      strcat(senholder, "32_");
    } else if (senletter == '3') {
      strcat(senholder, "33_");
    } else if (senletter == '4') {
      strcat(senholder, "34_");
    } else if (senletter == '5') {
      strcat(senholder, "35_");
    } else if (senletter == '6') {
      strcat(senholder, "36_");
    } else if (senletter == '7') {
      strcat(senholder, "37_");
    } else if (senletter == '8') {
      strcat(senholder, "38_");
    } else if (senletter == '9') {
      strcat(senholder, "39_");
    } else if (senletter == '0') {
      strcat(senholder, "30_");
    } else if (senletter == '?') {
      strcat(senholder, "3f_");
    } else if (senletter == ' ') {
      //When the word ends (which is space in that case),the hexholder get an '.' to mark the end.
      strcat(senholder, ".");
      strcat(hexHolder, senholder);
      break;
    }
    else {
      if (debugging) {
        //ERROR
        Serial.print("Fehler2!! >:( \n");      //A combination that isn't a word. How shall we handle this? Stop the program? Use "?" as a placeholder for "This letter doesn't exist"?
      }
    }
    strcat(hexHolder, senholder);
  }
  for (int i = 1; i < letterSize; i++)
  {
    sentenceHolder[i] = ' ';
  }
  //Set the first char in sentenceHolder to '\0'. That way it's enterpreted as an empty string.
  sentenceHolder[0] = '\0';
  for (int i = 1; i < letterSize; i++)
  {
    senholder[i] = ' ';
  }
  //Set the first char in senHolder to '\0'. That way it's enterpreted as an empty string.
  senholder[0] = '\0';
  Serial.println(hexHolder);
  HexTurn();
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
