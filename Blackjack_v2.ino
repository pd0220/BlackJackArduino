// Blackjack casino game implementation via Arduino UNO board and C++ code
// ELTE TTK BSc Physics *Mikrokontrollerek és alkalmazásaik* course

// ...ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo...

// pins to use (about orientation on the dice)
const int upleft = 13;
const int upright = 12;
const int midleft = 11;
const int midright = 10;
const int downleft = 9;
const int downright = 8;
const int middle = 7;
// pins to determine who won
const int pinPlayerONE = 5;
const int pinPlayerTWO = 4;
// pin for new dice throw button
const int throwButton = 6;
// pin for fold button
const int foldButton = 3;
// list of LEDs (by orientation)
const int LEDlist[] = {middle, downright, downleft, midright, midleft, upright, upleft};

// ...ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo...

// variables to use (and update)
// random number
int randNum = 0;

// values for the two player
int playerONE = 0;
int playerTWO = 0;
int whoIsNext = pinPlayerONE;

// values for player LEDs
int ledState = LOW;

// last time stored
unsigned long previousMillis = 0;

// if the games of folded
int folded = 0;

// ...ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo...

// dice functions -> which face of the dice should be shown?
// see https://www.arduino.cc/en/tutorial/blink
// one
void ONE()
{
  digitalWrite(middle, HIGH);
}
// two
void TWO()
{
  digitalWrite(upright, HIGH);
  digitalWrite(downleft, HIGH);
}
// three
void THREE()
{
  digitalWrite(upright, HIGH);
  digitalWrite(middle, HIGH);
  digitalWrite(downleft, HIGH);
}
// four
void FOUR()
{
  digitalWrite(upleft, HIGH);
  digitalWrite(upright, HIGH);
  digitalWrite(downleft, HIGH);
  digitalWrite(downright, HIGH);
}
// five
void FIVE()
{
  digitalWrite(upleft, HIGH);
  digitalWrite(upright, HIGH);
  digitalWrite(downleft, HIGH);
  digitalWrite(downright, HIGH);
  digitalWrite(middle, HIGH);
}
// six
void SIX()
{
  digitalWrite(upleft, HIGH);
  digitalWrite(upright, HIGH);
  digitalWrite(midleft, HIGH);
  digitalWrite(midright, HIGH);
  digitalWrite(downleft, HIGH);
  digitalWrite(downright, HIGH);
}
// zero -> show nothing...
void ZERO()
{
  for (int i = 0; i < (sizeof(LEDlist) / sizeof(int)); i++)
  {
    digitalWrite(LEDlist[i], LOW);
  }
}

// ...ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo...

// decorational series of flashes via LEDs **CASINO VIBE**
void decor()
{
  ONE();
  delay(100);
  ZERO();
  TWO();
  delay(100);
  ZERO();
  THREE();
  delay(100);
  ZERO();
  FOUR();
  delay(100);
  ZERO();
  FIVE();
  delay(100);
  ZERO();
  SIX();
  delay(100);
  ZERO();
}

// ...ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo...

// function to wait for player
void WaitForPlayer()
{
  // see https://www.arduino.cc/en/Tutorial/BlinkWithoutDelay
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 1000)
  {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
  }
  // turn on the given LED
  digitalWrite(whoIsNext, ledState);
}

// ...ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo...

// update player for next round
void UpdatePlayer()
{
  // if both players are in the game
  if (folded == 0)
  {
    // update to next player
    if (whoIsNext == pinPlayerONE)
    {
      whoIsNext = pinPlayerTWO;
    }
    else if (whoIsNext == pinPlayerTWO)
    {
      whoIsNext = pinPlayerONE;
    }
  }
}

// ...ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo...

// update value
void UpdatePlayerValue(int whoIsNext, int diceVal)
{
  if (whoIsNext == pinPlayerONE)
  {
    playerONE += diceVal;
  }
  else if (whoIsNext == pinPlayerTWO)
  {
    playerTWO += diceVal;
  }
}

// ...ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo...

// one of the players stop playing
void FoldGame()
{
  folded += 1;
}

// ...ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo...

// check if endgame
void IsEndGame()
{
  if (folded >= 2)
  {
    int result = playerONE - playerTWO;
    // one wins
    if (result > 0)
    {
      digitalWrite(pinPlayerONE, HIGH);
      delay(7500);
      digitalWrite(pinPlayerONE, LOW);
    }
    // two wins
    else if (result < 0)
    {
      digitalWrite(pinPlayerTWO, HIGH);
      delay(7500);
      digitalWrite(pinPlayerTWO, LOW);
    }
    // draw
    else if (result == 0)
    {
      digitalWrite(pinPlayerONE, HIGH);
      digitalWrite(pinPlayerTWO, HIGH);
      delay(7500);
      digitalWrite(pinPlayerTWO, LOW);
      digitalWrite(pinPlayerONE, LOW);
    }

    // reset game
    playerONE = 0;
    playerTWO = 0;
    folded = 0;
    whoIsNext = pinPlayerONE;
  }
}

// ...ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo...

// check if value is greatee than 21
void IsValueTooHigh()
{
  // if one of the two is greater than 21
  if (playerONE > 21 || playerTWO > 21)
  {
    // two wins
    if (playerONE > 21)
    {
      digitalWrite(pinPlayerTWO, HIGH);
      delay(7500);
      digitalWrite(pinPlayerTWO, LOW);
    }
    // one wins
    else if (playerTWO > 21)
    {
      digitalWrite(pinPlayerONE, HIGH);
      delay(7500);
      digitalWrite(pinPlayerONE, LOW);
    }
    // reset game
    playerONE = 0;
    playerTWO = 0;
    folded = 0;
    whoIsNext = pinPlayerONE;
  }
}

// setup function
void setup()
{
  // outputs -> set pins for LEDs
  for (int i = 0; i < (sizeof(LEDlist) / sizeof(int)); i++)
  {
    pinMode(LEDlist[i], OUTPUT);
  }
  // outputs -> pins for winner LEDs
  pinMode(pinPlayerONE, OUTPUT);
  pinMode(pinPlayerTWO, OUTPUT);

  // inputs -> set buttons
  pinMode(throwButton, INPUT);
  pinMode(foldButton, INPUT);

  // set random number seed
  // see https://www.arduino.cc/reference/en/language/functions/random-numbers/randomseed/
  randomSeed(analogRead(0));

  // start serial
  Serial.begin(9600);
}

// ...ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo...

// loop function
void loop()
{
  // check if buttons are pushed
  // waiting
  if (digitalRead(throwButton) == HIGH && digitalRead(foldButton) == HIGH)
  {
    WaitForPlayer();
  }
  // throwing
  else if (digitalRead(throwButton) == LOW && digitalRead(foldButton) == HIGH)
  {
    // set player LEDs to dark
    digitalWrite(pinPlayerONE, LOW);
    digitalWrite(pinPlayerTWO, LOW);

    // run decor function
    decor();
    // random number generation from [1, 7) interval
    randNum = random(1, 7);

    // choosing dice function
    // six
    if (randNum == 6)
    {
      SIX();
      UpdatePlayerValue(whoIsNext, randNum);
    }
    // five
    else if (randNum == 5)
    {
      FIVE();
      UpdatePlayerValue(whoIsNext, randNum);
    }
    // four
    else if (randNum == 4)
    {
      FOUR();
      UpdatePlayerValue(whoIsNext, randNum);
    }
    // three
    else if (randNum == 3)
    {
      THREE();
      UpdatePlayerValue(whoIsNext, randNum);
    }
    // two
    else if (randNum == 2)
    {
      TWO();
      UpdatePlayerValue(whoIsNext, randNum);
    }
    // one
    else if (randNum == 1)
    {
      ONE();
      UpdatePlayerValue(whoIsNext, randNum);
    }

    delay(2500);

    // write current result to serial port
    Serial.print(playerONE);
    Serial.print(" ; ");
    Serial.println(playerTWO);
    delay(50);

    // set back to blank
    ZERO();

    // update player for next round
    UpdatePlayer();
  }
  // folding the game -> no more throws for given player
  else if (digitalRead(throwButton) == HIGH && digitalRead(foldButton) == LOW)
  {
    // set player LEDs to dark
    digitalWrite(pinPlayerONE, LOW);
    digitalWrite(pinPlayerTWO, LOW);
    // wait
    delay(500);
    UpdatePlayer();
    FoldGame();
  }

  // check if end of game
  IsEndGame();
  // if value is too high
  IsValueTooHigh();
}

// ...ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo......ooo000O000ooo...
