int inPin = 12;    // input wire is connected to digital pin 7
int delayTime = 125; //delay time must be the same as transmitter(1/8 of a second)
int val = 0;      // variable to store the value read by digitalRead
char a[0]; //char array to convert message from binary to ASCII

int lastvals[8];     //Store the contents of the last 8 values
int message = 0;     //Store the binary value of the message

void setup() {
  Serial.begin(9600);
  pinMode(inPin, INPUT);    // sets the digital pin 7 as input
  while(!digitalRead(inPin));  //waits until a connection is made (1 is recieved) before starting program
}

/*
 * Look for the key (000000001). Once the key is found decode the next 7 bits, and store them in "message". Store the message 
 * in a char array and then print out the message to the Serial Monitor
 */
void loop() {
  val = digitalRead(inPin);    //Read the value from the input pin
  //Print the value just read
  //Serial.print("Reading Value ");
  //Serial.println(val);
  delay(delayTime);     //Wait for 1/8 of a second before reading next value
  
  //Check if the key was found (i.e. Last 8 values are 000000001)
  if(lastvals[7] == 0 && lastvals[6] == 0 && lastvals[5] == 0 && lastvals[4] == 0 && lastvals[3] == 0 && lastvals[2] == 0 && lastvals[1] == 0 && lastvals[0] == 0 && val == 1){
    //Serial.println("Key Recieved");
    //Serial.print("Message is ");
    for(int i=6;i>=0;i--){
      //Read the next 7 bits and store them in a variable "message"
      val = digitalRead(inPin);  
      Serial.println(val);
      delay(delayTime);
      bitWrite(message,i,val);   //Stores the value "val" in the variable "message" at position "i"
    }
    a[0]= message;     //store the message in the char array
    Serial.print("Data Recieved. Message is ");
    Serial.println(a);     //print the ASCII value of the message
  }
  
  //update the last 8 values that have been recieved
  for(int j=6;j>=0;j--){
    lastvals[j+1]=lastvals[j];
  }
  lastvals[0]=val;
}
