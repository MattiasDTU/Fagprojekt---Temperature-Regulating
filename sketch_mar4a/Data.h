                  // .--------------------------------.
                  // |      ____        _             |
                  // |     |  _ \  __ _| |_ __ _      |
                  // |     | | | |/ _` | __/ _` |     |
                  // |     | |_| | (_| | || (_| |     |
                  // |     |____/ \__,_|\__\__,_|     |
                  // '--------------------------------'

///////////////////  Multiplex Control pins
// Mux control pins
int s0 = 28;   // Digital pin1
int s1 = 29;   // Digital pin2
int s2 = 30;   // Digital pin3
int s3 = 31;   // Digital pin4
// Mux in "SIG" pin
int SIG_pin = 15; // A Input pin

const int numSensors = 16;
const int numPoints = 102;
float temperatures[numSensors][numPoints];
int currentReading = 0;


int readMux(float &temperature, int channel) {
  int controlPin[] = {s0, s1, s2, s3};

  int muxChannel[16][4]={
    {0,0,0,0}, //channel 0
    {1,0,0,0}, //channel 1
    {0,1,0,0}, //channel 2
    {1,1,0,0}, //channel 3
    {0,0,1,0}, //channel 4
    {1,0,1,0}, //channel 5
    {0,1,1,0}, //channel 6
    {1,1,1,0}, //channel 7
    {0,0,0,1}, //channel 8
    {1,0,0,1}, //channel 9
    {0,1,0,1}, //channel 10
    {1,1,0,1}, //channel 11
    {0,0,1,1}, //channel 12
    {1,0,1,1}, //channel 13
    {0,1,1,1}, //channel 14
    {1,1,1,1}  //channel 15
  };

  // Loop through the 4 control pins
  for(int i = 0; i < 4; i++) {
    digitalWrite(controlPin[i], muxChannel[channel][i]);
  }

  // Read the value at the SIG pin
  int val = analogRead(SIG_pin);
  float temp = val * 0.09746588694; // Conv. Const.

  // Return the value
  temperature = temp;
}