#pragma once

#include <iostream>
#include <math.h>
#include <array>
#include <algorithm>
#include <bitset>
#include <random>

using namespace std;
const size_t ARRAY_SIZE = 128;

class BigInt {
private:
	uint32_t HEXCharToDecimal(char c);
	string removeLeadingZeros(string& BinaryString) const;
	void ShiftDigitsToHigh(const int index);
	void multOneDigit(const uint32_t& digit, BigInt& result);
	int BitLenght() const;
public:
	array<uint32_t, ARRAY_SIZE> data;
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
	BigInt operator >> (int index) const;
	BigInt operator << (int index) const;

	string toHexString() const;
	string toBinaryString() const;
	void fromBinaryString(const string& binaryString);

	BigInt ShiftBitToHigh(const int index) const;
	BigInt generateRandomHEXNumber(const int lenght);

	BigInt GCD(const BigInt& other) const;
	BigInt LCM(const BigInt& other) const;

	BigInt BarrettReduction(BigInt x, BigInt n, BigInt m) const; 

	BigInt addWithModulo(BigInt other, BigInt modulus) const;
	BigInt subWithModulo(BigInt other, BigInt modulus) const;
	BigInt multWithModulo(BigInt other, BigInt modulus) const;
	BigInt toSquareWithModulo(BigInt modulus) const;


	int DigitLength() const;
	BigInt findMu(BigInt n) const;
	BigInt powerModulo(BigInt exponent, BigInt modulus) const;

};