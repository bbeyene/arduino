
//Source: https://blog.manash.me/serial-communication-with-an-arduino-using-c-on-windows-d08710186498
//This code snippet will help you to read data from arduino

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SerialPort.h"
#include <fstream>

using std::cout;
using std::endl;

/*Portname must contain these backslashes, and remember to
replace the following com port*/
char *port_name = "\\\\.\\COM3";

//String for incoming data
char incomingData[MAX_DATA_LENGTH];

int main()
{
  SerialPort arduino(port_name);
  if (arduino.isConnected()) cout << "Connection Established" << endl;
  else cout << "ERROR, check port name";
  /*
  while (arduino.isConnected()){
    //Check if data has been read or not
    int read_result = arduino.readSerialPort(incomingData, MAX_DATA_LENGTH);
    //prints out data
    puts(incomingData);
    //wait a bit
    Sleep(1000);
  }
  */
  while (arduino.isConnected()){
    //Check if data has been read or not
    int read_result = arduino.readSerialPort(incomingData, MAX_DATA_LENGTH);
    //writes out data
    	if(incomingData[7] == 'O') {
    		puts(incomingData);
    		//write to file
				char *filename = "tempHumid.txt";
				std::ofstream outFile;
			
				outFile.open(filename);
				if (!outFile)
				{
					cout << "Cannot write file" << endl;
					return 1;
				}
				for(int d = 11; d < 19; d++)
				{
					outFile << incomingData[d];
				}
				outFile.close();
    		break;
		}
		else {
			continue;
		}
	}
}
