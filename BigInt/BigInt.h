#pragma once

#include <iostream>
#include <math.h>
#include <array>
#include <algorithm>
#include <bitset>
#include <ctime>

using namespace std;
const size_t ARRAY_SIZE = 512;

class BigInt {
private:
	array<uint32_t, ARRAY_SIZE> data;
	uint32_t HEXCharToDecimal(char c);
	string removeLeadingZeros(string& BinaryString) const;
	void ShiftDigitsToHigh(const int index);
	void multOneDigit(const uint32_t& digit, BigInt& result);
	int BitLenght() const;
public:
	BigInt();
	BigInt(uint32_t num);
	BigInt(array<uint32_t, ARRAY_SIZE> array);
	BigInt(const BigInt& other);
	BigInt(const string& StringHEX);

	BigInt& operator = (const BigInt& other);
	BigInt operator + (const BigInt& other);
	BigInt operator - (const BigInt& other);
	BigInt operator * (const BigInt& other);
	BigInt operator / (const BigInt& other);
	BigInt operator % (const BigInt& other);
	BigInt Square();
	BigInt Pow(const BigInt& exponent);

	bool operator == (const BigInt& other) const;
	bool operator != (const BigInt& other) const;
	bool operator > (const BigInt& other) const;
	bool operator < (const BigInt& other) const;
	bool operator >= (const BigInt& other) const;
	bool operator <= (const BigInt& other) const;

	BigInt operator >> (const int shiftCount) const;
	BigInt operator << (const int shiftCount) const;

	string toHexString() const;
	string toBinaryString() const;
	void fromBinaryString(const string& binaryString);
	BigInt ShiftBitToHigh(const int index) const;

};