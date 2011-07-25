/*
 ============================================================================
 Name        : JeeLabs.cpp
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C++,
 ============================================================================
 */

#include <iostream>
#include "Channel/SerialChannel.h"

using namespace std;


int main(void) {
    SerialChannel JeeNode;
    JeeNode.setDevice("/dev/ttyUSB0");
    JeeNode.Connect();
	cout << "Hello World" << endl; /* prints Hello World */
	return 0;
}
