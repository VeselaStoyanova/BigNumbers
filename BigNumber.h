#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class BigNumber {
private:
    std::vector<int> digits;
    bool negative = false;
    int system = 10;

public:
    //Constructors
    BigNumber(const std::string& digitsString);
    BigNumber(int number);

    int getSystem() const;
    void setSystem(int newSystem);

    //Helper functions
    std::string to_string() const;
    std::string toString() const;
    std::string intToString(int number) const;
    int size() const;
    int at(int index) const; 
    bool isPossitive() const;
    void multiplyByTen(int number);
    void removeBackZeroes();

    void removeFrontZeroes() ;
    void addZerosInfront(int number);
    void addSymbolInfront(std::string symbol);
    void removeFirstSymbol();
    void removeNegativeSign();
    void oppositeBigNumber();
    bool isEven() const;

    //Comparisson operators
    bool operator>=(const BigNumber& other) const;
    bool operator<=(const BigNumber& other) const;
    bool operator<(const BigNumber& other) const;
    bool operator==(const BigNumber& other) const;
    bool operator>(const BigNumber& other) const;
    bool operator!=(const BigNumber& other) const;
    bool isSmaller(const BigNumber& other) const;

    //Arithmetics operators
    BigNumber operator+(const BigNumber& other);
    BigNumber operator-(const BigNumber& other);
    BigNumber operator*(const BigNumber& other);
    BigNumber operator/(BigNumber& other);
    BigNumber sqrt();

    BigNumber operator+=(const BigNumber& other);
    BigNumber operator%(BigNumber& other);

    bool isValidNumberInDecimalNumeralSystem();
    bool isValidNumberInHexadecimalNumeralSystem();
    bool isValidNumber();

    BigNumber hexadecimalToDecimal(const BigNumber& hex);
    BigNumber decimalToHexadecimal(BigNumber decimal);
    BigNumber divideByTwo() const;
    BigNumber divide(BigNumber& other);
};
