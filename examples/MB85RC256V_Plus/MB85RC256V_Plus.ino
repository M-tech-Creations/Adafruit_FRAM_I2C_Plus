#include <Wire.h>
#include "Adafruit_FRAM_I2C_Plus.h"

/* Example code for the Adafruit I2C FRAM breakout */
/* Explained to show functions for the Plus library*/

/* Connect SCL    to analog 5 / Mega Digital 21
   Connect SDA    to analog 4 / Mega Digital 20
   Connect VDD    to 5.0V DC
   Connect GROUND to common ground */
   
Adafruit_FRAM_I2C_Plus fram     = Adafruit_FRAM_I2C_Plus();
uint16_t          framAddr = 0;

void setup(void) {
  Serial.begin(9600);
  
  if (fram.begin()) {  // you can stick the new i2c addr in here, e.g. begin(0x51);
    Serial.println("Found I2C FRAM");
  } else {
    Serial.println("No I2C FRAM found ... check your connections\r\n");
    while (1);
  }
  
  // Read the first byte
  uint8_t test = fram.read8(0x0);
   Serial.print("Restarted "); Serial.print(test); Serial.println(" times");
  // Test write ++
   fram.write8(0x0, test+1);
   
   //Write 16 bit
   uint16_t test16 = 5000; //Arbitrary number to big for 8 bit
   Serial.print("\nWriting 16-bit number: "); Serial.print(test16); Serial.println(" to Memory\n");
   fram.write16(1,test16); //Writes to the second memory location
   
   //Read 16 bit
   Serial.print("Reading 16 bit number: ");
   Serial.println(fram.read16(1));  //To read back as int or any other variable
									//You can typecast by placing that type in front of
									//fram.read16 ; ex. (int)fram.read16(0);
	
	//Write String
	String string_test = "The Quick Brown Fox";
	Serial.print("\nWriting Sting: "); Serial.print(string_test); Serial.println(" to Memory\n");
	fram.write_String(3,string_test);
	
	//Read String
	Serial.print("Reading String: ");Serial.println(fram.read_String(3,string_test.length()+1));
	delay(1000);//hold for one second
	
	//Multiple Dynamic String Write and Read
	int string_Length1 = 0, string_Length2 = 0;//Place to store lengths
	
	String string_test2 = "Jumps over the Lazy Dog!";
	Serial.print("\n\nWriting second String: ");Serial.print(string_test2);Serial.println(" to Memory\n");
	
	
	string_Length1 = string_test.length()+2;//get the length of the String to store
	string_Length2 = string_test2.length()+1;//add the plus one for string terminator
	
	fram.write8(1,string_Length1);//Save lengths in memory for read, when reading
	fram.write8(2,string_Length2);//back from memory with out knowing its length
	
	fram.write_String(2+fram.read8(1)+1,string_test2);//Start from beginning of the first String then add length of first string plus null
	delay(1000);//Give processor time to finish
	Serial.println("Reading String: " + fram.read_String(3+fram.read8(1),fram.read8(2)));//repeat to read back using stored length
	delay(1000);//hold for a second
	
	//Total Message
	Serial.println("\n\nWhole Message\n");
	Serial.print(fram.read_String(3,string_Length1));//Use first memory location for String
	Serial.println(" " + fram.read_String(3+fram.read8(1),fram.read8(2)));
	
   
  // dump the entire 32K of memory!
  /*uint8_t value;
  for (uint16_t a = 0; a < 32768; a++) {
    value = fram.read8(a);
    if ((a % 32) == 0) {
      Serial.print("\n 0x"); Serial.print(a, HEX); Serial.print(": ");
    }
    Serial.print("0x"); 
    if (value < 0x1) 
      Serial.print('0');
    Serial.print(value, HEX); Serial.print(" ");
  }*/
}

void loop(void) {

}