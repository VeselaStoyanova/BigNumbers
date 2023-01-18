#include "BigNumber.h"

//Constructors
BigNumber::BigNumber(int number) {
    if (number == 0) {
        digits.push_back(0);
    }
    else {
        if (number > 0) {
            while (number != 0) {
                addSymbolInfront(intToString(number % 10));
                number /= 10;
            }
        }
        else {
            number *= -1;
            while (number != 0) {
                addSymbolInfront(intToString(number % 10));
                number /= 10;
            }
            addSymbolInfront("-");
        }
    }
    system = 10;
}

BigNumber::BigNumber(const std::string& digitsString) {
    bool isHex = false;
    for (char symbol : digitsString) {
        if (!isdigit(symbol)) {
            if (symbol == 'A' || symbol == 'B' || symbol == 'C' || symbol == 'D' || symbol == 'E' || symbol == 'F') {
                isHex = true;
            }
            else {
                throw std::invalid_argument("Invalid input string: must contain only digits or hexadecimal symbols.");
            }
        }
    }
    if (isHex) {
        BigNumber newNumber = BigNumber(digitsString);
        hexadecimalToDecimal(newNumber);
        setSystem(16);
    }
    for (char symbol : digitsString) {
        digits.push_back(symbol - '0');
        setSystem(10);
    }
}

int BigNumber::getSystem() const {
    return system;
}

void BigNumber::setSystem(int newSystem) {
    system = newSystem;
}

//Helper functions
std::string BigNumber::to_string() const {
    std::stringstream ss;
    for (int digit : digits) {
        ss << char(digit + '0');
    }
    return ss.str();
}

std::string BigNumber::toString() const {
    std::string result;
    for (int i = 0; i < this->size(); i++) {
        result += std::to_string(this->at(i));
    }
    return result;
}

std::string BigNumber::intToString(int number) const {
    if (number == 0) return "0";
    if (number == 1) return "1";
    if (number == 2) return "2";
    if (number == 3) return "3";
    if (number == 4) return "4";
    if (number == 5) return "5";
    if (number == 6) return "6";
    if (number == 7) return "7";
    if (number == 8) return "8";
    if (number == 8) return "8";
    if (number == 9) return "9";
    if (number == 10) return "A";
    if (number == 11) return "B";
    if (number == 12) return "C";
    if (number == 13) return "D";
    if (number == 14) return "E";
    if (number == 15) return "F";
    return "";
}

int BigNumber::size() const {
    return digits.size();
}

int BigNumber::at(int index) const {
    return this->digits[index];
}

bool BigNumber::isPossitive() const {
    if (digits.at(0) < 0) {
        return false;
    }
    return true;
}

void BigNumber::multiplyByTen(int number) {
    for (int i = 0; i < number; i++) {
        digits.push_back(0);
    }
}

void BigNumber::removeBackZeroes() {
    while (this->digits.size() > 1 && this->digits.back() == '0') {
        this->digits.pop_back();
    }
}

void BigNumber::removeFrontZeroes(){
    while (digits.at(0) == 0 && digits.size() > 1) {
        digits.erase(digits.begin());
    }
}

void BigNumber::addZerosInfront(int number) {
    for (int i = 0; i < number; i++) {
        digits.insert(digits.begin(), 0);
    }
}

void BigNumber::addSymbolInfront(std::string symbol) {
    digits.insert(digits.begin(), symbol.front() - '0');
}

void BigNumber::removeFirstSymbol() {
    digits.erase(digits.begin());
}

void BigNumber::removeNegativeSign() {
    while (!isPossitive()) {
        digits.erase(digits.begin());
    }
}

void BigNumber::oppositeBigNumber()  {
    if (isPossitive()) {
        addSymbolInfront("-");
    }
    else {
        removeNegativeSign();
    }
}

bool BigNumber::isEven() const {
    return digits.back() % 2 == 0;
}

BigNumber BigNumber::operator%(BigNumber& other) {
    BigNumber remainder = (*this);
    while (remainder >= other) {
        remainder = remainder - other;
    }
    return remainder;
}

BigNumber BigNumber::sqrt() {
    BigNumber left = BigNumber("0");
    BigNumber right = (*this).divideByTwo();
    BigNumber result = BigNumber("0");

    while (left <= right) {
        BigNumber sum = left + right;
        BigNumber middle = sum.divideByTwo();
        BigNumber middleSquared = middle * middle;
        BigNumber middlePlusOneSquared = (middle + 1) * (middle + 1);
        BigNumber middleMinusOneSquared = (middle - 1) * (middle - 1);

        if (middleSquared == (*this) || (middlePlusOneSquared > (*this) && (middleMinusOneSquared < (*this)))) {
            result = middle;
            if (getSystem() == 10) {
                return middle;
            }
            else {
                return decimalToHexadecimal(middle);
            }
        }
        else if (middleSquared < (*this)) {
            left = middle + BigNumber("1");
        }
        else {
            right = middle - BigNumber("1");
        }
    }
    if (getSystem() == 10) {
        return result;
    }
    else {
        return decimalToHexadecimal(result);
    }
}

//Comparisson operators
bool BigNumber::operator>=(const BigNumber& other) const {
    if (digits.size() != other.digits.size()) {
        return digits.size() > other.digits.size();
    }
    for (int i = 0; i < digits.size(); i++) {
        if (digits[i] > other.digits[i]) {
            return true;;
        }
        if (digits[i] < other.digits[i]) {
            return false;
        }
    }
    return true;
}

bool BigNumber::operator<=(const BigNumber& other) const {
    if (digits.size() != other.digits.size()) {
        return digits.size() < other.digits.size();
    }
    for (int i = 0; i < digits.size(); i++) {
        if (digits[i] < other.digits[i]) {
            return true;
        }
        if (digits[i] > other.digits[i]) {
            return false;
        }
    }
    return true;
}

bool BigNumber::operator==(const BigNumber& other) const {
    if (digits.size() != other.digits.size()) {
        return false;
    }
    for (int i = 0; i < digits.size(); i++) {
        if (digits[i] != other.digits[i]) {
            return false;
        }
    }
    return true;
}

bool BigNumber::operator<(const BigNumber& other) const {
    if (digits.size() < other.digits.size()) {
        return true;
    }
    if (digits.size() > other.digits.size()) {
        return false;
    }
    for (int i = 0; i < digits.size(); i++) {
        if (digits[i] < other.digits[i]) {
            return true;
        }
        if (digits[i] > other.digits[i]) {
            return false;
        }
    }

    return false;
}

bool BigNumber::operator>(const BigNumber& other) const {
    if (digits.size() > other.digits.size()) {
        return true;
    }
    if (digits.size() < other.digits.size()) {
        return false;
    }
    for (int i = 0; i < digits.size(); i++) {
        if (digits[i] > other.digits[i]) {
            return true;
        }
        if (digits[i] < other.digits[i]) {
            return false;
        }
    }

    return false;
}

bool BigNumber::isSmaller(const BigNumber& other) const {
    if (this->negative && !other.negative)
        return true;
    if (!this->negative && other.negative)
        return false;
    int firstBigNumberSize = this->size();
    int secondBigNumberSize = other.size();

    if (firstBigNumberSize != secondBigNumberSize)
        return firstBigNumberSize < secondBigNumberSize;

    for (int i = 0; i < firstBigNumberSize; i++)
        if (this->at(i) != other.at(i))
            return this->at(i) < other.at(i);
    return false;
}

BigNumber BigNumber::divide(BigNumber& other) {
    BigNumber result = *this;
    int resultSize = this->digits.size() - other.digits.size() + 1;
    result.digits.resize(resultSize);

    for (int i = resultSize - 1; i >= 0; i--) {
        int res = 0;
        while (res * other.digits.back() <= digits[i + other.digits.size() - 1]) {
            res++;
        }

        res--;

        int carry = 0;
        for (int j = 0; j < other.digits.size(); j++) {
            int diff = digits[i + j] - carry - other.digits[j] * res;
            digits[i + j] = (diff + 10) % 10;
            carry = (diff < 0) ? 1 : 0;
        }
        digits[i + other.digits.size() - 1] = digits[i + other.digits.size() - 1] - carry;
        result.digits[i] = res;
    }

    result.removeBackZeroes();
    result.removeFrontZeroes();
    return result;
}

bool BigNumber::operator!=(const BigNumber& other) const {
    return !(*this == other);
}

//Arithmetics operators
BigNumber BigNumber::operator+(const BigNumber& other) {
    BigNumber result = BigNumber("");
    int digitsSize = digits.size() - 1;
    int otherDigitsSize = other.digits.size() - 1;
    int carry = 0;

    while (digitsSize >= 0 || otherDigitsSize >= 0) {
        int a = (digitsSize >= 0) ? digits[digitsSize] : 0;
        int b = (otherDigitsSize >= 0) ? other.digits[otherDigitsSize] : 0;
        int sum = a + b + carry;
        carry = sum / 10;

        result.digits.push_back(sum % 10);

        digitsSize--;
        otherDigitsSize--;
    }
    if (carry > 0) {
        result.digits.push_back(carry);
    }
    std::reverse(result.digits.begin(), result.digits.end());
    result.removeBackZeroes();

    if (getSystem() == 10) {
        return result;
    }
    else {
        return decimalToHexadecimal(result);
    }
    
}

BigNumber BigNumber::operator-(const BigNumber& other){
    BigNumber result = BigNumber("");
    BigNumber minBigNumber = BigNumber("");
    BigNumber maxBigNumber = BigNumber("");
    bool isNegative = false;

    if (*this >= other) {
        minBigNumber = other;
        maxBigNumber = *this;
        isNegative = false;
    }
    else {
        minBigNumber = *this;
        maxBigNumber = other;
        isNegative = true;
    }
    minBigNumber.addZerosInfront(maxBigNumber.size() - minBigNumber.size());
    int minusOne = 0;
    int i = 0;
    while (i < maxBigNumber.size()) {
        int temp = maxBigNumber.at(maxBigNumber.size() - 1 - i) - minusOne - minBigNumber.at(minBigNumber.size() - 1 - i);
        if (temp < 0) {
            temp += 10;
            minusOne = 1;
        }
        else {
            minusOne = 0;
        }
        result.addSymbolInfront(intToString(temp));
        i++;
    }
    result.removeFrontZeroes();
    if (isNegative) {
        result.addSymbolInfront("-");
    }
    if (getSystem() == 10) {
        return result;
    }
    else {
        return decimalToHexadecimal(result);
    }
}

BigNumber BigNumber::operator*(const BigNumber& other){
    int digitsSize = digits.size();
    int otherDigitsSize = other.digits.size();
    if (digitsSize == 0 || otherDigitsSize == 0) {
        return BigNumber("0");
    }
    std::vector<int> result(digitsSize + otherDigitsSize, 0);

    int firstNumber = 0;
    int secondNumber = 0;
    for (int i = digitsSize - 1; i >= 0; i--) {
        int carry = 0;
        int digitsElement = digits[i];
        secondNumber = 0;
        for (int j = otherDigitsSize - 1; j >= 0; j--) {
            int otherDigitsElement = other.digits[j];
            int sum = digitsElement * otherDigitsElement + result[firstNumber + secondNumber] + carry;
            carry = sum / 10;
            result[firstNumber + secondNumber] = sum % 10;
            secondNumber++;
        }
        if (carry > 0) {
            result[firstNumber + secondNumber] += carry;
        }
        firstNumber++;
    }
    BigNumber resultNumber = BigNumber("");
    int i = result.size() - 1;
    while (i >= 0 && result[i] == 0) {
        i--;
    }
    if (i == -1) {
        return BigNumber("0");
    }
    while (i >= 0) {
        resultNumber.digits.push_back(result[i--]);
    }
    resultNumber.removeBackZeroes();
    if (getSystem() == 10) {
        return resultNumber;
    }
    else {
        return decimalToHexadecimal(resultNumber);
    }
}

BigNumber BigNumber::operator/(BigNumber& other) {
    if (other.at(0) == 0) {
        return BigNumber("");
    }

    if (isPossitive() && other.isPossitive()) {
        return (*this).divide(other);
    }
    if (!isPossitive() && !other.isPossitive()) {
        BigNumber temp1 = *this;
        BigNumber temp2 = other;
        temp1.removeNegativeSign();
        temp2.removeNegativeSign();
        return temp1.divide(temp2);
    }
    if ((isPossitive() && !other.isPossitive()) || (!isPossitive() && other.isPossitive())) {
        BigNumber temp1 = *this;
        BigNumber temp2 = other;
        temp1.removeNegativeSign();
        temp2.removeNegativeSign();
        BigNumber result = temp1.divide(temp2);
        result.oppositeBigNumber();
        if (result.at(0) == 0) {
            result.removeNegativeSign();
        }
        return result;
    }
}

BigNumber BigNumber::operator+=(const BigNumber& other) {
    return (*this) = ((*this) + other);
}

std::ostream& operator<<(std::ostream& os, const BigNumber& other) {
    os << other.to_string();
    return os;
}

bool BigNumber::isValidNumberInDecimalNumeralSystem() {
    bool isValid = true;
    for (int i = 0; i < digits.size(); i++) {
        if (!isdigit(digits.at(i))) {
            isValid = false;
        }
    }
    return isValid;
}

bool BigNumber::isValidNumberInHexadecimalNumeralSystem() {
    bool isValidNumber = true;
    for (int i = 0; i < digits.size(); i++) {
        if ((digits.at(i) < '0' || digits.at(i) > '9') && (digits.at(i) < 'A' || digits.at(i) > 'F')) {
            isValidNumber = false;
        }
    }
    return isValidNumber;
}

bool BigNumber::isValidNumber() {
    return isValidNumberInDecimalNumeralSystem() || isValidNumberInHexadecimalNumeralSystem();
}

BigNumber BigNumber::hexadecimalToDecimal(const BigNumber& hex) {
    BigNumber result = BigNumber("");
    for (char symbol : hex.digits) {
        int digit;
        if (symbol >= '0' && symbol <= '9') {
            digit = symbol - '0';
        }
        else if (symbol >= 'a' && symbol <= 'f') {
            digit = symbol - 'a' + 10;
        }
        else if (symbol >= 'A' && symbol <= 'F') {
            digit = symbol - 'A' + 10;
        }
        else {
            throw std::invalid_argument("Invalid hexadecimal digit: " + symbol);
        }
        result = result * BigNumber("16") + BigNumber(std::to_string(digit));
    }
    system = 10;
    return result;
}

BigNumber BigNumber::decimalToHexadecimal(BigNumber decimal) {
    BigNumber hexadecimal = BigNumber("");
    BigNumber sixteen = BigNumber("16");
    BigNumber carry = BigNumber("");
    BigNumber zero = BigNumber("0");
    while (decimal != zero) {
        carry = decimal % sixteen;
        if (carry == BigNumber("10")) {
            hexadecimal = BigNumber("A") + hexadecimal;
        }
        else if (carry == BigNumber("11")) {
            hexadecimal = BigNumber("B") + hexadecimal;
        }
        else if (carry == BigNumber("12")) {
            hexadecimal = BigNumber("C") + hexadecimal;
        }
        else if (carry == BigNumber("13")) {
            hexadecimal = BigNumber("D") + hexadecimal;
        }
        else if (carry == BigNumber("14")) {
            hexadecimal = BigNumber("E") + hexadecimal;
        }
        else if (carry == BigNumber("15")) {
            hexadecimal = BigNumber("F") + hexadecimal;
        }
        else {
            hexadecimal += carry;
        }
        decimal = decimal / sixteen;
    }
    system = 16;
    return hexadecimal;
}

BigNumber readBigNumberOperationFromConsole() {
    std::string input;
    std::getline(std::cin, input);

    if (input.substr(0, 5) == "sqrt(") {
        std::string number = input.substr(5, input.size() - 6);
        return BigNumber(number).sqrt();
    }
    else {
        size_t operatorPos = std::string::npos;
        for (size_t i = 0; i < input.size(); i++) {
            if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') {
                operatorPos = i;
                break;
            }
        }
        if (operatorPos == std::string::npos) {
            throw std::invalid_argument("Invalid input: must contain an operator (+, -, *, /)");
        }
        BigNumber a(input.substr(0, operatorPos));
        BigNumber b(input.substr(operatorPos + 1));
        if (a.isValidNumber() && b.isValidNumber()) {
            char op = input[operatorPos];
            if (op == '+') {
                return a + b;
            }
            else if (op == '-') {
                return a - b;
            }
            else if (op == '*') {
                return a * b;
            }
            else if (op == '/') {
                return a / b;
            }
            else {
                throw std::invalid_argument("Invalid operator");
            }
        }
        else {
            throw std::invalid_argument("The number is not valid");
        }
    }
}

BigNumber BigNumber::divideByTwo() const {
    BigNumber result = BigNumber("");
    int currDividend = 0;
    int carry = 0;
    int index = 0;
    int nextDigit = 0;

    while (index < digits.size()) {
        currDividend = 0;
        if (carry > 0) {
            currDividend = currDividend + carry;
            currDividend = currDividend * 10;
        }
        currDividend = currDividend + digits.at(index);
        index++;

        while (currDividend < 2 && index < digits.size()) {
            currDividend = currDividend * 10;
            currDividend = currDividend + digits.at(index);
            index++;
            result.digits.push_back(0);
        }
        nextDigit = currDividend / 2;
        carry = currDividend % 2;
        result.digits.push_back(nextDigit);
    }
    result.removeFrontZeroes();
    return result;
}

void testOperatorLessThan () {
    BigNumber firstNumber = BigNumber("5");
    BigNumber secondNumber = BigNumber("10");
    bool firstResult = firstNumber < secondNumber;
    std::cout << "5 < 10: " << firstResult << std::endl;

    BigNumber thirdNumber = BigNumber("12345678987654321");
    BigNumber forthNumber = BigNumber("123456789");
    bool secondResult = thirdNumber < forthNumber;
    std::cout << "12345678987654321 < 123456789: " << secondResult << std::endl;
}

void testOperatorMoresThan() {
    BigNumber firstNumber = BigNumber("5");
    BigNumber secondNumber = BigNumber("10");
    bool firstResult = firstNumber > secondNumber;
    std::cout << "5 > 10: " << firstResult << std::endl;

    BigNumber thirdNumber = BigNumber("12345678987654321");
    BigNumber forthNumber = BigNumber("123456789");
    bool secondResult = thirdNumber > forthNumber;
    std::cout << "12345678987654321 > 123456789: " << secondResult << std::endl;
}

void testOperatorLessOrEqualThan() {
    BigNumber firstNumber = BigNumber("5");
    BigNumber secondNumber = BigNumber("10");
    bool firstResult = firstNumber <= secondNumber;
    std::cout << "5 <= 10: " << firstResult << std::endl;

    BigNumber thirdNumber = BigNumber("12345678987654321");
    BigNumber forthNumber = BigNumber("12345678987654321");
    bool secondResult = thirdNumber <= forthNumber;
    std::cout << "12345678987654321 <= 12345678987654321: " << secondResult << std::endl;

    BigNumber fifthNumber = BigNumber("12345678987654321");
    BigNumber sixthNumber = BigNumber("123456789");
    bool thirdResult = fifthNumber <= sixthNumber;
    std::cout << "12345678987654321 <= 123456789: " << thirdResult << std::endl;
}

void testOperatorMoreOrEqualThan() {
    BigNumber firstNumber = BigNumber("5");
    BigNumber secondNumber = BigNumber("10");
    bool firstResult = firstNumber >= secondNumber;
    std::cout << "5 >= 10: " << firstResult << std::endl;

    BigNumber thirdNumber = BigNumber("12345678987654321");
    BigNumber forthNumber = BigNumber("12345678987654321");
    bool secondResult = thirdNumber >= forthNumber;
    std::cout << "12345678987654321 >= 12345678987654321: " << secondResult << std::endl;

    BigNumber fifthNumber = BigNumber("12345678987654321");
    BigNumber sixthNumber = BigNumber("123456789");
    bool thirdResult = fifthNumber >= sixthNumber;
    std::cout << "12345678987654321 >= 123456789: " << thirdResult << std::endl;
}

void testOperatorEqualTo() {
    BigNumber firstNumber = BigNumber("5");
    BigNumber secondNumber = BigNumber("10");
    bool firstResult = firstNumber == secondNumber;
    std::cout << "5 == 10: " << firstResult << std::endl;

    BigNumber thirdNumber = BigNumber("-5");
    BigNumber forthNumber = BigNumber("-10");
    bool secondResult = thirdNumber == forthNumber;
    std::cout << "-5 == -10: " << secondResult << std::endl;

    BigNumber fifthNumber = BigNumber("12345678987654321");
    BigNumber sixthNumber = BigNumber("123456789");
    bool thirdResult = fifthNumber == sixthNumber;
    std::cout << "12345678987654321 == 123456789: " << thirdResult << std::endl;

    BigNumber seventhNumber = BigNumber("12345678987654321");
    BigNumber eighthNumber = BigNumber("12345678987654321");
    bool forthResult = seventhNumber == eighthNumber;
    std::cout << "12345678987654321 == 12345678987654321: " << forthResult << std::endl;

    BigNumber ninthNumber = BigNumber("12345678987654321");
    BigNumber tenthNumber = BigNumber("-12345678987654321");
    bool fifthResult = ninthNumber == tenthNumber;
    std::cout << "12345678987654321 == -12345678987654321: " << fifthResult << std::endl;
}

void testOperatorDifferentFrom() {
    BigNumber firstNumber = BigNumber("5");
    BigNumber secondNumber = BigNumber("10");
    bool firstResult = firstNumber != secondNumber;
    std::cout << "5 != 10: " << firstResult << std::endl;

    BigNumber thirdNumber = BigNumber("-5");
    BigNumber forthNumber = BigNumber("-10");
    bool secondResult = thirdNumber != forthNumber;
    std::cout << "-5 != -10: " << secondResult << std::endl;

    BigNumber fifthNumber = BigNumber("12345678987654321");
    BigNumber sixthNumber = BigNumber("123456789");
    bool thirdResult = fifthNumber != sixthNumber;
    std::cout << "12345678987654321 != 123456789: " << thirdResult << std::endl;

    BigNumber seventhNumber = BigNumber("12345678987654321");
    BigNumber eighthNumber = BigNumber("12345678987654321");
    bool forthResult = seventhNumber != eighthNumber;
    std::cout << "12345678987654321 != 12345678987654321: " << forthResult << std::endl;

    BigNumber ninthNumber = BigNumber("12345678987654321");
    BigNumber tenthNumber = BigNumber("-12345678987654321");
    bool fifthResult = ninthNumber != tenthNumber;
    std::cout << "12345678987654321 != -12345678987654321: " << fifthResult << std::endl;
}

void testDivideByTwoMethod() {
    BigNumber firstNumber = BigNumber("2");
    BigNumber firstResult = firstNumber.divideByTwo();
    std::cout << "2 / 2 = " << firstResult << std::endl;

    BigNumber secondNumber = BigNumber("1230134567");
    BigNumber secondResult = secondNumber.divideByTwo();
    std::cout << "1230134567 / 2 = " << secondResult << std::endl;
}

void testOperatorSum() {
    BigNumber firstNumber = BigNumber("5");
    BigNumber secondNumber = BigNumber("10");
    BigNumber firstResult = firstNumber + secondNumber;
    std::cout << "5 + 10 = " << firstResult << std::endl;

    BigNumber thirdNumber = BigNumber("12456789031415");
    BigNumber forthNumber = BigNumber("98765432123456789");
    BigNumber secondResult = thirdNumber + forthNumber;
    std::cout << "12456789031415 + 98765432123456789 = " << secondResult << std::endl;
}

void testOperatorMinus() {
    BigNumber firstNumber = BigNumber("15");
    BigNumber secondNumber = BigNumber("5");
    BigNumber firstResult = firstNumber - secondNumber;
    std::cout << "15 - 5 = " << firstResult << std::endl;

    BigNumber thirdNumber = BigNumber("4321");
    BigNumber forthNumber = BigNumber("1234");
    BigNumber secondResult = thirdNumber - forthNumber;
    std::cout << "4321 - 1234 = " << secondResult << std::endl;

    BigNumber fifthNumber = BigNumber("1234");
    BigNumber sixthNumber = BigNumber("4321");
    BigNumber thirdResult = fifthNumber - sixthNumber;
    std::cout << "1234 - 4321 = " << thirdResult << std::endl;
}

void testOperatorMultiply() {
    BigNumber firstNumber = BigNumber("1234");
    BigNumber secondNumber = BigNumber("4321");
    BigNumber firstResult = firstNumber * secondNumber;
    std::cout << "1234 * 4321 = " << firstResult << std::endl;

    BigNumber thirdNumber = BigNumber("12456789031415");
    BigNumber forthNumber = BigNumber("98765432123456789");
    BigNumber secondResult = thirdNumber * forthNumber;
    std::cout << "12456789031415 * 98765432123456789 = " << secondResult << std::endl;
}

void testOperatorDivide() {
    BigNumber firstNumber = BigNumber("89");
    BigNumber secondNumber = BigNumber("4");
    BigNumber firstResult = firstNumber / secondNumber;
    std::cout << "89 / 4 = " << firstResult << std::endl;

    BigNumber thirdNumber = BigNumber("3693");
    BigNumber forthNumber = BigNumber("3");
    BigNumber secondResult = thirdNumber / forthNumber;
    std::cout << "3683 / 3 = " << secondResult << std::endl;
}

void testOperatorSqrt() {
    BigNumber firstNumber = BigNumber("1234");
    BigNumber firstResult = firstNumber.sqrt();
    std::cout << "sqrt(1234) = " << firstResult << std::endl;

    BigNumber secondNumber = BigNumber("12456789031415");
    BigNumber secondResult = secondNumber.sqrt();
    std::cout << "sqrt(12456789031415) = " << secondResult << std::endl;

    BigNumber thirdNumber = BigNumber("125");
    BigNumber thirdResult = thirdNumber.sqrt();
    std::cout << "sqrt(125) = " << thirdResult << std::endl;
}

int main() {
    //testOperatorLessThan();
    //testOperatorMoresThan();
    //testOperatorLessOrEqualThan();
    //testOperatorMoreOrEqualThan();
    //testOperatorEqualTo();
    //testOperatorDifferentFrom();
    //testDivideByTwoMethod();
    
    //testOperatorSum();
    //testOperatorMinus();
    //testOperatorMultiply();
    //testOperatorDivide();
    //testOperatorSqrt();
   std::cout << "Enter two big numbers separated by an operator or sqrt(BigNumber): " << std::endl;
    try {
        BigNumber result = readBigNumberOperationFromConsole();
        std::cout << "Result: " << result.toString() << std::endl;
    }
    catch (const std::invalid_argument& argument) {
        std::cout << argument.what() << std::endl;
    }
}
