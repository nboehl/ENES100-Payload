float inputVoltage = 0.0;
int payloadArray[16];  //intializes array with size 16 for input
int charArray[7]; //array for ASCII binary
  
void setup() {
  pinMode(A1, INPUT); // assigns input port to take in data
}

void loop() {
  /* array elements numbered from 0 to array size - 1
   * Loop below repeated reads data from payload to create array by
   * reading voltage from payload pads */
  int i = 0;
  while (i < 16) { //loops until array is filled with 16 inputs
    
    /*
     * ISSUE: READING DATA
     * When we tested reading the data, the voltage read was either 0
     * or around 3.6 volts (after converting analog read). It should either be
     * picking up only 0's or 5's (if the payload is working as it should)
     * 
     * If we successfully read 5s and 0s, then the input is reading as it should.
     * 
     * Possible reasons for issuse:
     * - voltage conversion equation below? Do we need it?
     * - Payload not working correctly? Is it really transmitting a signal?
     * - Read may be happening in between signals (while it is moving between 
     *  0 and 5 volts, so instead of 0 or 5 it is reading a value in between).
     *  
     */
     
    int analogValue = analogRead(A1); //read input and find voltage

    inputVoltage = (analogValue*5.0)/1024.0; //conversion equation
      
    Serial.println(inputVoltage);
    if (inputVoltage == 0.0) { //if signal reads 0V, 0 entered in array
      payloadArray[i] = 0;
      i = i + 1;
    } else if (inputVoltage == 5.0) { //if signal reads 5V, 1 entered in array
      payloadArray[i] = 1;
      i = i + 1;
    }
    delay(125); //SIGNAL SENT AT 8 BITS PER SECOND
  }
  //For testing, to tell when array is filled with 16 bits
  Serial.println("READ END"); 


  
  /* 
   * Takes whole received array and leaves only last 7 bits
   * Ignores first 9 bits which are the signal code.
   * Converts array into INTEGER that can be 
   * automatically converted from binary to char
   * 
   * SHOULD THE ARRAY BE CORRECT (correctly read and number in correct order,
   * this function works and will print a char.
   * This was testied by manually inputting the example in the given powerpoint,
   * and a 'Q' was printed
   */
  int sum = 0;
  /*
   * ISSUE: ARRAY IN CORRECT ORDER
   * 
   * Something that I realized is that because the payload is supposedly releasing
   * its signal continuously, if we connect IN THE MIDDLE of it transmitting a
   * signal, our array may be filled but it will not be filled in the correct order,
   * meaning we may read a completely different thing.
   * 
   * There will have to be something that checks to make sure we are reading at the
   * beginning of the signal, and if not rearranged read data to be in correct order.
   * 
   * The data will be transmitted with a 9 bit "activation signal" at the very start
   * "000000001"
   * Possible solution: create an if statement that checks that the first 9 bits
   * in the array are these exact numbers. Then if not find some way to reorder 
   * the array.
   * 
   */
  for (int i = 0; i < 7; i++){ //7 - 1 since array starts at 0
    charArray[i] = payloadArray[(i+9)];
    Serial.println(charArray[i]);
    //converts list of arrays into one int together
    sum = (sum * 10) + charArray[i];
    Serial.println(sum);
  }
  
  Serial.print("Data Received: ");
  //if the sum is a correct binary number, it will be correctly converted
  Serial.println(char(sum)); 
  //Example: 1010001 should print 'Q'

  delay(1000);
}
