int analogInput = 1; //A1 - port for analog input to connect
int payloadArray[16]; //intializes array with size 16 for input
int charArray[7]; //array for ASCII binary
float inputVoltage = 0.0;

void setup() {
  pinMode(analogInput, INPUT); // assigns input port
  Serial.begin(9600);
}

void loop() {
  /* array elements numbered from 0 to array size - 1
   * Loop below repeated reads data from payload to create array by
   * reading voltage from payload pads */
  for (int i = 0; i < 16; i++) { //16 - 1 since array starts at 0
    int analogValue = analogRead(A1); //read input and find voltage
    inputVoltage = (analogValue*5.0)/1024.0;
      //if signal reads 0V, 0 entered in array
    if (inputVoltage == 0.0) { 
      payloadArray[i] = 0;
      //if signal reads 5V, 1 entered in array
    } else if (inputVoltage == 5.0) {
      payloadArray[i] = 1;
    }
    delay(125); // wait 1/8 second for next bit
  }

  /* Takes whole received array and leaves only last 7 bits
   * Ignores first 9 bits which are the signal code
   * the print char */
  for (int i = 0; i < 7; i++){ //7 - 1 since array starts at 0
    charArray[i] = payloadArray[(i+9)];
  }
  Serial.print("Data Received: ");
  Serial.println(char(charArray)); //print recieved value
  delay(1000);
}
