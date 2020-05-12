// (pseudo)random number analysis with Arduino

// setup function
void setup()
{
  // see https://www.arduino.cc/reference/en/language/functions/random-numbers/randomseed/
  // data3
  randomSeed(analogRead(random() ^ ((uint32_t) analogRead(0) << 22) ^ micros()));
  // data2
  //randomSeed(analogRead(0) ^ random());
  // data1
  //randomSeed(analogRead(0));

  // start serial
  Serial.begin(9600);
}

// loop function
void loop()
{
  // write random numbers to serial
  Serial.println(random(0, 2));
}
