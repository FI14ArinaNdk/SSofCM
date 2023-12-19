#include "BigInt.h"

BigInt::BigInt() {
    data.fill(0);
}

BigInt::BigInt(uint32_t num) : data() {
    data[0] = num;
}

BigInt::BigInt(array<uint32_t, ARRAY_SIZE> array) :data(array) {}

BigInt::BigInt(const BigInt& other) : data(other.data) {}

BigInt::BigInt(const string& StringHEX) {
    data.fill(0);
    int lenght = StringHEX.length();
    int index = 0;
    int shiftCount = 0;

    for (int i = lenght - 1; i >= 0; i--) {
        char c = StringHEX[i];
        uint32_t temporary = HEXCharToDecimal(c);

        data[index] |= (temporary << shiftCount);

        if (shiftCount == 28) {
            index++;
            shiftCount = 0;
        }
        else {
            shiftCount += 4;
        }
    }
}
uint32_t BigInt::HEXCharToDecimal(char c) {
    switch (c) {
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    case 'a': case 'A': return 10;
    case 'b': case 'B': return 11;
    case 'c': case 'C': return 12;
    case 'd': case 'D': return 13;
    case 'e': case 'E': return 14;
    case 'f': case 'F': return 15;
    default: return 0;
    }
}

string BigInt::removeLeadingZeros(string& binaryString) const {
    size_t thefirstcharacter = binaryString.find_first_not_of('0');
    if (thefirstcharacter != std::string::npos) 
        binaryString = binaryString.substr(thefirstcharacter); 
    else
        binaryString = "0";

    return binaryString;
}

void BigInt::ShiftDigitsToHigh(const int index) {
    if (index >= ARRAY_SIZE) {
        data.fill(0);
        return;
    }

    for (int i = ARRAY_SIZE - 1; i >= 0; i--) {
        if ((i - index) >= 0)
            data[i] = data[i - index];
        else
            data[i] = 0;
    }
}

void BigInt::multOneDigit(const uint32_t& digit, BigInt& result) {
    uint32_t carry = 0;

    for (int i = 0; i < data.size(); i++) {
        uint64_t temporary = static_cast<uint64_t>(data[i]) * static_cast<uint64_t>(digit) + carry;
        result.data[i] = static_cast<uint32_t>(temporary & 0xFFFFFFFF);
        carry = static_cast<uint32_t>(temporary >> 32);
    }

    result.data[ARRAY_SIZE - 1] = carry;
}

int BigInt::BitLenght() const {
    return this->toBinaryString().size();
}

BigInt& BigInt::operator = (const BigInt& other) {
    data = other.data;
    return *this;
}

BigInt BigInt::operator + (const BigInt& other) const{
    uint32_t carry = 0;
    BigInt totalresult;
    for (int i = 0; i < data.size(); i++) {
        uint64_t temporary = static_cast<uint64_t>(data[i]) + static_cast<uint64_t>(other.data[i]) + carry;
        totalresult.data[i] = static_cast<uint32_t>(temporary & 0xFFFFFFFF);
        carry = static_cast<uint32_t>(temporary >> 32);
    }
    return totalresult;
}

BigInt BigInt::operator - (const BigInt& other) const{
    uint32_t borrow = 0;
    BigInt resultdifference;
    for (int i = 0; i < data.size(); i++) {
        int64_t temp = static_cast<int64_t>(data[i]) - static_cast<int64_t>(other.data[i]) - borrow;
        if (temp >= 0) {
            resultdifference.data[i] = static_cast<uint32_t>(temp);
            borrow = 0;
        }
        else {
            resultdifference.data[i] = static_cast<uint32_t>(0xFFFFFFFF + temp + 1);
            borrow = 1;
        }
    }
    if (borrow == 1) {
        cout << "Bigger number is subtracted from the smaller" << endl;
        return 0;
    }
    return resultdifference;

 
}

BigInt BigInt::operator * (const BigInt& other) {
    BigInt result;

    for (int i = 0; i < data.size(); i++) {
        BigInt temporary;
        multOneDigit(other.data[i], temporary);
        temporary.ShiftDigitsToHigh(i);
        result = result + temporary;
    }
    return result;
}

BigInt BigInt::operator / (const BigInt& other) {
    if (other == BigInt("0")) {
        cout << "Division by zero is not allowed." << endl; 
    }

    if (*this < other) {
        return BigInt("0");
    }

    BigInt A = *this;
    BigInt B = other;
    BigInt Quotient;
    BigInt Remainder;
    int k = B.BitLenght();
    Remainder = A;
    Quotient = BigInt("0");

    while (Remainder >= B) { 
        int t = Remainder.BitLenght(); 
        BigInt C = B.ShiftBitToHigh(t - k); 
          
        if (Remainder < C) { 
            t = t - 1;
            C = B.ShiftBitToHigh(t - k); 
        } 

        Remainder = Remainder - C;
        Quotient = Quotient + BigInt("1").ShiftBitToHigh(t - k); 
    }

    return Quotient;
}

BigInt BigInt::operator % (const BigInt& other) {
    if (other == BigInt("0")) {
        cout << "Division by zero is not allowed." << endl;
    }

    BigInt A = *this;
    BigInt B = other;
    BigInt Remainder;
    int k = B.BitLenght();
    Remainder = A;

    while (Remainder >= B) {
        int t = Remainder.BitLenght();
        BigInt C = B.ShiftBitToHigh(t - k);

        if (Remainder < C) {
            t = t - 1;
            C = B.ShiftBitToHigh(t - k);
        }

        Remainder = Remainder - C;
    }

    return Remainder;
}

BigInt BigInt::Square() {
    return ((*this) * (*this));
}

BigInt BigInt::Pow(const BigInt& exponent) {
    string BinaryIntroduction = exponent.toBinaryString();
    BigInt base = *this;
    BigInt result(1);

    for (int i = BinaryIntroduction.size() - 1; i >= 0; i--) {
        if (BinaryIntroduction[i] == '1')
            result = result * base;

        if (i > 0)
            base = base.Square();
    }
    return result;
}

bool BigInt::operator == (const BigInt& other) const {
    for (int i = ARRAY_SIZE - 1; i >= 0; i--) {
        if (data[i] != other.data[i]) {
            return false;
        }
    }
    return true;
}
bool BigInt::operator != (const BigInt& other) const {
    for (int i = ARRAY_SIZE - 1; i >= 0; i--) {
        if (data[i] != other.data[i]) {
            return true;
        }
    }
    return false;
}
bool BigInt::operator > (const BigInt& other) const {
    for (int i = ARRAY_SIZE - 1; i >= 0; i--) {
        if (data[i] > other.data[i]) {
            return true;
        }
        else if (data[i] < other.data[i]) {
            return false;
        }
    }
    return false;
}
bool BigInt::operator < (const BigInt& other) const {
    for (int i = ARRAY_SIZE - 1; i >= 0; i--) {
        if (data[i] < other.data[i]) {
            return true;
        }
        else if (data[i] > other.data[i]) {
            return false;
        }
    }
    return false;
}
bool BigInt::operator >= (const BigInt& other) const {
    return (*this > other) || (*this == other);
}
bool BigInt::operator <= (const BigInt& other) const {
    return (*this == other) || (*this < other);
}

BigInt BigInt::operator >> (int index) const {
    BigInt result(*this);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (i + index < ARRAY_SIZE) {
            result.data[i] = result.data[i + index];
        }
        else {
            result.data[i] = 0;
        }
    }

    return result;
}

BigInt BigInt::operator << (int index) const {
    BigInt result(*this);
    for (int i = ARRAY_SIZE - 1; i >= 0; i--) {
        if (i - index >= 0) {
            result.data[i] = result.data[i - index];
        }
        else {
            result.data[i] = 0;
        }
    }
    return result;
}


string BigInt::toHexString() const {
    string HexString;
    HexString.reserve(8 * ARRAY_SIZE);
    for (int i = data.size() - 1; i >= 0; i--) {
        uint32_t value = data[i];
        for (int j = 7; j >= 0; j--) {
            char HexDigit = static_cast<char>((value >> (j * 4)) & 0xF);
            if (HexDigit < 10)
                HexString += '0' + HexDigit;
            else
                HexString += 'A' + (HexDigit - 10);
        }
    }
    removeLeadingZeros(HexString);
    return HexString;
}

string BigInt::toBinaryString() const {
    string BinaryString;
    for (int i = data.size() - 1; i >= 0; i--) {
        uint32_t value = data[i];

        for (int j = 31; j >= 0; j--)
            BinaryString += (value & (1 << j)) ? '1' : '0';
    }
    removeLeadingZeros(BinaryString);
    return BinaryString;
}

void BigInt::fromBinaryString(const string& BinaryString) {
    data.fill(0);
    int lenght = BinaryString.length();
    int index = 0;
    uint32_t CurrentWord = 0;
    int shift = 0;
    for (int i = lenght - 1; i >= 0; i--) {
        char C = BinaryString[i];
        if (C == 1)
            CurrentWord |= (1 << shift);
        shift++;
        if (shift == 32) {
            data[index] = CurrentWord;
            CurrentWord = 0;
            shift = 0;
        }
    }
    if (shift > 0)
        data[index] = CurrentWord;

}
BigInt BigInt::generateRandomHEXNumber(const int lenght) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<uint32_t> dis(0, UINT32_MAX);
    array<uint32_t, ARRAY_SIZE> result;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        result[i] = dis(gen);
    }
    BigInt RandomNumber(result);
    while (RandomNumber.toHexString().length() > lenght) { 
        RandomNumber = RandomNumber >> 1;
    }

    return RandomNumber;
}

BigInt BigInt::ShiftBitToHigh(int bits) const {

    BigInt result("0");

    if (bits <= 0) {
        return *this;
    }
    if (bits >= ARRAY_SIZE * 32) { 
        return result; 
    }

    int Count = bits / 32;
    int shifts = bits % 32;

    uint32_t carry = 0; 

    if (shifts != 0) { 
        for (int i = 0; i < ARRAY_SIZE; i++) {
            result.data[i] = (this->data[i] << shifts) + carry;
            carry = (this->data[i] >> (32 - shifts));
        }
        for (int i = ARRAY_SIZE - 1; i >= Count; i--) { 
            result.data[i] = result.data[i - Count];
        }
        for (int i = 0; i < Count; i++) {
            result.data[i] = 0;
        }
    }
    else {
        for (int i = ARRAY_SIZE - 1; i >= Count; i--) { 
            result.data[i] = this->data[i - Count]; 
        }
        for (int i = 0; i < Count; i++) { 
            result.data[i] = 0; 
        }
    }

    return result;
}

BigInt BigInt::GCD(const BigInt& other) const {
    BigInt a = *this;
    BigInt b = other;
    while (b != 0) {
        BigInt temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

BigInt BigInt::LCM(const BigInt& other) const {
    BigInt a = *this;
    BigInt b = other;
    return (a * b) / a.GCD(b);
}

BigInt BigInt::addWithModulo(BigInt other, BigInt modulus) const {
    BigInt a = *this;
    BigInt result("0");
    result = a + other;

    if (result >= modulus) {
        result = BarrettReduction(result, modulus, findMu(modulus));
    }

    return result;
}

BigInt BigInt::subWithModulo(BigInt other, BigInt modulus) const {
    BigInt a = *this;
    BigInt b = other; 
    BigInt result("0");

    if (b > modulus) { 
        b = BarrettReduction(b, modulus, findMu(modulus));  
    }
    if (b > a) {
        result = a + (b - modulus); 
    }
    if (a >= b) {
        result = a - b;
    }
   
    if (result >= modulus) {
        result = BarrettReduction(result, modulus, findMu(modulus));
    }

    return result;
}

BigInt BigInt::multWithModulo(BigInt other, BigInt modulus) const {
    BigInt a = *this;
    BigInt result = a * other;
    result = BarrettReduction(result, modulus, findMu(modulus));
    return result;
}

BigInt BigInt::findMu(const BigInt& n) const {
    int length = n.DigitLength();
    BigInt B("1");
    B = B << (2 * length); 
    BigInt temp = B / n; 
    return temp;
}

BigInt BigInt::BarrettReduction(BigInt x, BigInt n, BigInt m) const {
    int k = n.DigitLength();
    BigInt temporaryX = x;
    const BigInt temporaryN = n; 
    const BigInt temporaryM = m; 

    if (temporaryX < temporaryN) { 
        return temporaryX; 
    }

    BigInt Quotient = temporaryX >> (k - 1); 
    Quotient = Quotient * temporaryM; 
    Quotient = Quotient >> (k + 1);  

    BigInt Remainder = temporaryX - (Quotient * temporaryN); 
     
    while (Remainder >= temporaryN) { 
        Remainder = Remainder - temporaryN; 
    }

    return Remainder; 
} 

BigInt BigInt::toSquareWithModulo(BigInt modulus) const {
    BigInt a = *this;
    return BigInt(a * a) % modulus;
}


BigInt BigInt::powerModulo(BigInt other, BigInt modulus) const {
    BigInt a = *this;
    BigInt result("1");
    BigInt base = a % modulus;
    BigInt Mu = findMu(modulus);

    string binaryExp = other.toBinaryString();

    for (int i = binaryExp.length() - 1; i >= 0; --i) {
        if (binaryExp[i] == '1') {
            result = BarrettReduction(result * base, modulus, Mu);
        }
        base = BarrettReduction(base * base, modulus, Mu);
    }
    return result;
}

int BigInt::DigitLength() const {
    int length = ARRAY_SIZE;
    while (data[length - 1] == 0)
    {
        length--;
        if (length == 0)
        {
            break;
        }
    }
    return length;
}
