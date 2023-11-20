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

BigInt BigInt::ShiftBitToHigh(const int index) const {
    if (index <= 0 || index >= ARRAY_SIZE)
        return *this;
    int CountWord = index / 32;
    int shifts = index % 32;
    uint32_t carry = 0;
    BigInt C, result;
    if (shifts != 0) {
        for (int i = 0; i < ARRAY_SIZE; i++) {
            C.data[i] = (data[i] << shifts) + carry;
            carry = data[i] >> (32 - shifts);
        }
        for (int i = CountWord; i < ARRAY_SIZE; i++)
            result.data[i] = C.data[i - CountWord];
        return result;
    }
    else {
        for (int i = 0; i < ARRAY_SIZE; i++)
            C.data[i] = data[i];
        for (int i = CountWord; i < ARRAY_SIZE; i++)
            result.data[i] = C.data[i - CountWord];
        return result;
    }
}

BigInt& BigInt::operator = (const BigInt& other) {
    data = other.data;
    return *this;
}

BigInt BigInt::operator + (const BigInt& other) {
    uint32_t carry = 0;
    BigInt totalresult;
    for (int i = 0; i < data.size(); i++) {
        uint64_t temporary = static_cast<uint64_t>(data[i]) + static_cast<uint64_t>(other.data[i]) + carry;
        totalresult.data[i] = static_cast<uint32_t>(temporary & 0xFFFFFFFF);
        carry = static_cast<uint32_t>(temporary >> 32);
    }
    return totalresult;
}

BigInt BigInt::operator - (const BigInt& other) {

    if (other > *this) {
        cout << "Bigger number is subtracted from the smaller" << endl;
        return 0;
    }

    uint32_t borrow = 0;
    BigInt resultdifference;
    for (int i = 0; i < data.size(); i++) {
        uint64_t temporary = static_cast<uint64_t>(data[i]) - static_cast<uint64_t>(other.data[i]) - borrow;
        if (temporary >> 32 == 0) {
            resultdifference.data[i] = static_cast<uint32_t>(temporary);
            borrow = 0;
        }
        else {
            resultdifference.data[i] = static_cast<uint32_t>(temporary + (1Ull << 32));
            borrow = 1;
        }
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
    if (other == BigInt())
        return BigInt(0);
    if (*this == other)
        return BigInt(1);
    int k = other.BitLenght();
    BigInt Quotient;
    BigInt Remainder = *this;
    while (Remainder >= other) {
        int t = Remainder.BitLenght();
        BigInt temporary = other.ShiftBitToHigh(t - k);
        if (Remainder < temporary) {
            t--;
            temporary = other.ShiftBitToHigh(t - k);
        }
        Remainder = Remainder - temporary;
        BigInt one(1);
        Quotient = Quotient + one.ShiftBitToHigh(t - k);
        if (Remainder == other)
            return Quotient;
    }
    return Quotient;
}

BigInt BigInt::operator % (const BigInt& other) {
    if (other == BigInt())
        return *this;

    BigInt Remainder = *this;
    while (Remainder >= other) {
        int t = Remainder.BitLenght();
        BigInt temporary = other.ShiftBitToHigh(t - other.BitLenght());
        if (Remainder < temporary) {
            t--;
            temporary = other.ShiftBitToHigh(t - other.BitLenght());
        }
        Remainder = Remainder - temporary;
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
    for (int i = 0; i < lenght; i++)
        result[i] = dis(gen);
    BigInt RandomNumber(result);
    return RandomNumber;

}
