//******************************************************************************
// File name:   main.cpp
// Author:      Anna Tymoshenko
// Date:        09/17/2024
// Class:       CS200
// Assignment:  Base Converter
// Purpose:     automatically convert a number in a specified base to equivalent 
//              numbers in the other two bases
//******************************************************************************

#include <iostream>

using namespace std;

const string BINARY_PREFIX = "0b",
             HEX_PREFIX = "Ox";
const char DECIMAL_CH = 'D',
           BINARY_CH = 'B',
           HEX_CH = 'H';

int hexCharToInt (char hexDigit);
char getBase (const string& strNumber);
string getNumber (const string& prompt);
void printTitle (const string& myTitle);
string binaryToDecimal (const string& strNumber);
string decimalToBinary (const string& strNumber);
string decimalToHex (const string& strNumber);
string hexToDecimal (const string& strNumber);
string hexToBinary (const string& strNumber);
string binaryToHex (const string& strNumber);

/***********************************************************************
Function:     main

Description:	Driver

Parameters:   None

Returned:     Exit Status
***********************************************************************/

int main () {
  const string TITLE = "HEX-DECIMAL-BINARY CONVERTER",
               EXIT = "q";

  string userInput;

  printTitle (TITLE);

  while (true) {
    userInput = getNumber("\nEnter your string to convert (q to quit): ");

    if (userInput == EXIT) {
      break;
    }
    else if (getBase(userInput) == BINARY_CH) {
      cout << "The decimal conversion is: " << binaryToDecimal(userInput)
           << endl;
      cout << "The hexadecimal conversion is: " << binaryToHex(userInput)
           << endl;
    }
    else if (getBase(userInput) == HEX_CH) {
      cout << "The decimal conversion is: " << hexToDecimal(userInput)
           << endl;
      cout << "The binary conversion is: " << hexToBinary(userInput)
           << endl;
    }
    else {
      cout << "The binary conversion is: " << decimalToBinary(userInput)
           << endl;
      cout << "The hexadecimal conversion is: " << decimalToHex(userInput)
           << endl;
    }
  }
  
  return EXIT_SUCCESS;
}

/***********************************************************************
Function:			hexCharToInt

Description:	converts hexadecimal (single) character to decimal number

              explanation: since we are basically converting char to decimal our 
              character range from 0 to 9 is equivalent to 48 to 57 range 
              decimal-wise therefore we are just subtracting the lowest value 
              character (or 48). same logic for A to F case.

Parameters:		hexDigit - hexadecimal character (0-9, A, B, C, D, E, or F)

Returned:			equivalent decimal number (0-9, 10, 11, 12, 13, 14, 15)
***********************************************************************/

int hexCharToInt (char hexDigit) {
  if (hexDigit >= '0' && hexDigit <= '9') {
    return hexDigit - '0';
  } 
  else if (hexDigit >= 'A' && hexDigit <= 'F') {
    return hexDigit - 'A' + 10; 
  }
  return -1;
}

/***********************************************************************
Function:			getBase

Description:	identifiy the base of the input string based on its prefix

Parameters:		strNumber - string representing a decimal, hexadecimal, or binary 
                          number

Returned:			one of three characters:
              • D if the number is a decimal
              • H if the user number is a hexadecimal
              • B if the number is binary.
***********************************************************************/

char getBase (const string& strNumber) {
  if (strNumber[1] == 'x') {
    return HEX_CH;
  }
  else if (strNumber[1] == 'b') {
    return BINARY_CH;
  }
  else {
    return DECIMAL_CH;
  }
}

/***********************************************************************
Function:			getNumber

Description:	prompt the user for input and returns entered number as a string

Parameters:		prompt - user prompt

Returned:			string representing a decimal, hexadecimal, or binary number
***********************************************************************/

string getNumber (const string& prompt) {
  string inputNumber;

  cout << prompt;
  cin >> inputNumber;

  return inputNumber;
}

/***********************************************************************
Function:			printTitle

Description:	prints title

Parameters:		myTitle - title to print

Returned:			void
***********************************************************************/

void printTitle (const string& myTitle) {
  cout << "**************************************" << endl;
  cout << "*****" << myTitle << "*****" << endl;
  cout << "**************************************" << endl;
}

/***********************************************************************
Function:			binaryToDecimal

Description:	converts binary number to a decimal number

Parameters:		strNumber - string representing a binary number

Returned:			string representing the decimal equivalent
***********************************************************************/

string binaryToDecimal (const string& strNumber) {
  int decimalValue = 0;
  char binaryDigit;

  for (int i = 2; i < strNumber.length(); i++) { // skipping first two chars
    binaryDigit = strNumber[i];
    decimalValue *= 2;
    if (binaryDigit == '1') {
      decimalValue += 1;
    }
  }

  return to_string(decimalValue);
}

/***********************************************************************
Function:			decimalToBinary

Description:	converts decimal number to a binary number

Parameters:		strNumber - string representing a decimal number

Returned:			string representing the binary equivalent
***********************************************************************/

string decimalToBinary (const string& strNumber) {
  int decimalValue = stoi(strNumber);
  string binaryValue;

  if (strNumber == "0") {
    return BINARY_PREFIX + strNumber;
  }

  while (decimalValue > 0) {
    if (decimalValue % 2 == 0) {
      binaryValue = "0" + binaryValue;
    }
    else {
      binaryValue = "1" + binaryValue;
    }
    decimalValue = decimalValue / 2;
  }

  return BINARY_PREFIX + binaryValue;
}

/***********************************************************************
Function:			decimalToHex

Description:	converts decimal number to a hexadecimal number

Parameters:		strNumber - string representing a decimal number

Returned:			string representing the hexadecimal equivalent
***********************************************************************/

string decimalToHex (const string& strNumber) {
  string hexValue;
  int remainder = 0;
  int decimalValue = stoi(strNumber);

  if (strNumber == "0") {
    return HEX_PREFIX + strNumber;
  }

  while (decimalValue > 0) {
    remainder = decimalValue % 16;
    if (remainder < 10) {
      hexValue = to_string(remainder) + hexValue;  // 0-9
    }
    else {
      hexValue = char(remainder - 10 + 'A') + hexValue; // 10-16
    }
    decimalValue /= 16;
  }

  return HEX_PREFIX + hexValue;
}

/***********************************************************************
Function:			hexToDecimal

Description:	converts hexadecimal number to a decimal number

Parameters:		strNumber - string representing a hexadecimal number

Returned:			string representing the decimal equivalent
***********************************************************************/

string hexToDecimal (const string& strNumber) {
  int decimalValue = 0;
  char hexDigit;
  
  for (int i = 2; i < strNumber.length(); i++) { 
    hexDigit = strNumber[i];
    decimalValue *= 16;

    decimalValue += hexCharToInt(hexDigit);
  }
  
  return to_string(decimalValue);
}

/***********************************************************************
Function:			hexToBinary

Description:	converts hexadecimal number to a binary number

Parameters:		strNumber - string representing a hexadecimal number

Returned:			string representing the binary equivalent
***********************************************************************/

string hexToBinary (const string& strNumber) {
  string decimalValue = hexToDecimal(strNumber);
  return decimalToBinary(decimalValue);
}

/***********************************************************************
Function:			binaryToHex

Description:	converts binary number to a hexadecimal number

Parameters:		strNumber - string representing a binary number

Returned:			string representing the hexadecimal equivalent
***********************************************************************/

string binaryToHex (const string& strNumber) {
  string decimalValue = binaryToDecimal(strNumber);
  return decimalToHex(decimalValue);
}