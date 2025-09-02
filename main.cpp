#include <iostream>
#include <string>
#include <cstdint>
using namespace std;

class BigInt
{
    string number;
    bool isNegative;

    void removeLeadingZeros()
    {
        size_t i = 0;
        while (i < number.size() - 1 && number[i] == '0')
        {
            i++;
        }
        number = number.substr(i);

        if (number.empty())
            number = "0";
    }

    int compareMagnitude(const BigInt &other) const
    {
        if (number.size() > other.number.size())
            return 1;
        if (number.size() < other.number.size())
            return -1;

        for (size_t i = 0; i < number.size(); i++)
        {
            if (number[i] > other.number[i])
                return 1;
            if (number[i] < other.number[i])
                return -1;
        }
        return 0;
    }

public:
    // Default constructor - initialize to zero

    friend BigInt &operator*=(BigInt &, const BigInt &);
    friend BigInt &operator/=(BigInt &, const BigInt &);
    friend BigInt &operator%=(BigInt &, const BigInt &);
    friend bool operator>(const BigInt &, const BigInt &);
    friend bool operator>=(const BigInt &, const BigInt &);




    BigInt()
    {
        number = "0";
        isNegative = false;
        // TODO: Implement this constructor
    }

    // Constructor from 64-bit integer
    BigInt(int64_t value)
    {
        // TODO: Implement this constructor
        number = to_string(abs(value));
        if (value < 0)
            isNegative = true;
        else
            isNegative = false;
        removeLeadingZeros();
    }

    // Constructor from string representation
    BigInt(const string &str)
    {
        // TODO: Implement this constructor
        if (str.empty())
        {
            number = "0";
            isNegative = false;
            return;
        }
        else
        {
            if (str[0] == '-')
            {
                number = str.substr(1);
                isNegative = true;
            }
            else
            {
                number = str;
                isNegative = false;
            }
        }
        for (int i = 0; i < number.length(); i++)
        {
            if (!isdigit(number[i]))
                throw invalid_argument("Invalid character in BigInt string");
        }
        removeLeadingZeros();
    }
    // Copy constructor
    BigInt(const BigInt &other)
    {
        number = other.number;
        isNegative = other.isNegative;
    }

    // Destructor
    ~BigInt()
    {
        // we do not need to do anything.
        // TODO: Implement if needed
    }

    // Assignment operator
    BigInt &operator=(const BigInt &other)
    {
        if (this == &other)
            return *this;
        this->number = other.number;
        this->isNegative = other.isNegative;

        return *this;
    }

    // Unary negation operator (-x)
    BigInt operator-() const
    {
        BigInt result;
        result.number = this->number;
        if (result.number == "0")
        {
            result.isNegative = false; // Unknown behavior
            return result;
        }
        result.isNegative = !this->isNegative;

        return result;
    }

    // Unary plus operator (+x)
    BigInt operator+() const
    {
     // TODO: Implement this operator
        BigInt result;
        result.number = this->number;
        result.isNegative = this->isNegative;
        return result;
    }

    // Addition assignment operator (x += y)
    BigInt &operator+=(const BigInt &other)
    {
    string result = "";
    int carry = 0;
    int i = number.size() - 1;
    int j = other.number.size() - 1;

    while (i >= 0 || j >= 0 || carry)
    {
        int digit1 = i >= 0 ? number[i--] - '0' : 0;
        int digit2 = j >= 0 ? other.number[j--] - '0' : 0;
        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        result = char(sum % 10 + '0') + result;
    }

    number = result;
    isNegative = false; 
    return *this;
    }

    // Subtraction assignment operator (x -= y)
    BigInt &operator-=(const BigInt &other)
    {
    string result = "";
    int borrow = 0;
    int i = number.size() - 1;
    int j = other.number.size() - 1;

    while (i >= 0)
    {
        int digit1 = number[i--] - '0' - borrow;
        int digit2 = j >= 0 ? other.number[j--] - '0' : 0;

        if (digit1 < digit2)
        {
            digit1 += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        result = char(digit1 - digit2 + '0') + result;
    }

    while (result.size() > 1 && result[0] == '0')
        result.erase(0, 1);

    number = result;
    isNegative = false;
    return *this;
    }

    // Multiplication assignment operator (x *= y)
    BigInt &operator*=(const BigInt &other)
    {
        *this = *this * other;  
        return *this;
    }

    // Division assignment operator (x /= y)
    BigInt &operator/=(const BigInt &other)
    {

    if (other.number == "0") {
        throw std::runtime_error("division by zero");
    }
       *this = *this / other;
        return *this;
    }

    // Modulus assignment operator (x %= y)
        BigInt &operator%=(const BigInt &other)
        {
        if (other.number == "0") {
        throw runtime_error("division by zero");
        }
        *this = *this % other;
        return *this;
        }

    // Pre-increment operator (++x)
    BigInt &operator++()
    {
        *this += BigInt(1);
        return *this;
    }

    // Post-increment operator (x++)
    BigInt operator++(int)
    {
        BigInt temp = *this;
        *this += BigInt(1);
        return temp;
    }

    // Pre-decrement operator (--x)
    BigInt &operator--()
    {
        *this -= BigInt(1);
        return *this;
    }

    // Post-decrement operator (x--)
    BigInt operator--(int)
    {
        BigInt temp;
        BigInt temp = *this;
        *this -= BigInt(1);
        return temp;
    }

    // Convert BigInt to string representation
    string toString() const
    {
        // TODO: Implement this function
        if (this->number == "0")
            return "0";
        if (this->isNegative == true)
            return "-" + this->number;
        return this->number;
    }

    // Output stream operator (for printing)
    friend ostream &operator<<(ostream &os, const BigInt &num)
    {
        // TODO: Implement this operator
        os << num.toString();
        return os;
    }

    // Input stream operator (for reading from input)
    friend istream &operator>>(istream &is, BigInt &num)
    {
        // TODO: Implement this operator
        string input;
        is >> input;
        if (input.empty())
        {
            num.number = "0";
            num.isNegative = false;
            return is;
        }
        if (input[0] == '-')
        {
            num.number = input.substr(1);
            num.isNegative = true;
        }
        else if (input[0] == '+')
        {
            num.number = input.substr(1);
            num.isNegative = false;
        }
        else
        {
            num.number = input;
            num.isNegative = false;
        }
        num.removeLeadingZeros();
        return is;
    }

    // Friend declarations for comparison operators
    friend bool operator==(const BigInt &lhs, const BigInt &rhs);
    friend bool operator<(const BigInt &lhs, const BigInt &rhs);
};

// Binary addition operator (x + y)
BigInt operator+(BigInt lhs, const BigInt &rhs)
{
    BigInt result;
    // TODO: Implement this operator
    return result;
}

// Binary subtraction operator (x - y)
BigInt operator-(BigInt lhs, const BigInt &rhs)
{
    BigInt result;
    // TODO: Implement this operator
    return result;
}

// Binary multiplication operator (x * y)
BigInt operator*(BigInt lhs, const BigInt &rhs)
{
    BigInt result;
    // TODO: Implement this operator
    return result;
}

// Binary division operator (x / y)
BigInt operator/(BigInt lhs, const BigInt &rhs)
{
    BigInt result;
    // TODO: Implement this operator
    return result;
}

// Binary modulus operator (x % y)
BigInt operator%(BigInt lhs, const BigInt &rhs)
{
    BigInt result;
    // TODO: Implement this operator
    return result;
}

// Equality comparison operator (x == y)
bool operator==(const BigInt &lhs, const BigInt &rhs)
{

    return (lhs.isNegative == rhs.isNegative &&
            lhs.number == rhs.number);
}

// Inequality comparison operator (x != y)
bool operator!=(const BigInt &lhs, const BigInt &rhs)
{
    return !(lhs == rhs);
}

// Less-than comparison operator (x < y)
bool operator<(const BigInt &lhs, const BigInt &rhs)
{
    if (lhs.isNegative != rhs.isNegative)
        return lhs.isNegative; 

    if (lhs.number.size() != rhs.number.size())
    {
        if (lhs.isNegative)
            return lhs.number.size() > rhs.number.size(); 
        else
            return lhs.number.size() < rhs.number.size();
    }

    if (lhs.isNegative)
        return lhs.number > rhs.number;
    else
        return lhs.number < rhs.number;
}

// Less-than-or-equal comparison operator (x <= y)
bool operator<=(const BigInt &lhs, const BigInt &rhs)
{
    return (lhs < rhs || lhs == rhs);
}



// Less-than comparison operator (x < y)
bool operator<(const BigInt &lhs, const BigInt &rhs)
{
    // TODO: Implement this operator
    return false;
}

// Less-than-or-equal comparison operator (x <= y)
bool operator<=(const BigInt &lhs, const BigInt &rhs)
{
    // TODO: Implement this operator
    return false;
}

// Greater-than comparison operator (x > y)
bool operator>(const BigInt &lhs, const BigInt &rhs)
{
    return rhs < lhs;
}

// Greater-than-or-equal comparison operator (x >= y)
bool operator>=(const BigInt &lhs, const BigInt &rhs)
{
    return !(lhs < rhs);
}


int main()
{
    cout << "=== BigInt Class Test Program ===" << endl
         << endl;
    cout << "NOTE: All functions are currently empty." << endl;
    cout << "Your task is to implement ALL the functions above." << endl;
    cout << "The tests below will work once you implement them correctly." << endl
         << endl;

    /*
      ///Testing my methods (Ahmed)
      cout << "=== Assignment Operator Tests ===" << endl;
      BigInt a("12345");
      BigInt b("-67890");

      cout << "Before assignment:" << endl;
      cout << "a = " << a << endl;   // expect 12345
      cout << "b = " << b << endl;   // expect -67890

      a = b;  // test assignment

      cout << "After a = b:" << endl;
      cout << "a = " << a << endl;   // expect -67890
      cout << "b = " << b << endl;   // expect -67890 (unchanged)

      cout << "\n=== Unary Negation Tests ===" << endl;
      BigInt c("12345");
      BigInt d("-67890");
      BigInt e("0");

      cout << "-c = " << -c << endl;   // expect -12345
      cout << "-d = " << -d << endl;   // expect 67890
      cout << "-e = " << -e << endl;   // expect 0  (no negative zero!)

      cout << "\n=== Chained Assignment Test ===" << endl;
      BigInt x("111"), y("222"), z("333");
      x = y = z;

      cout << "x = " << x << endl;   // expect 333
      cout << "y = " << y << endl;   // expect 333
      cout << "z = " << z << endl;   // expect 333
     ///End of my testing.

      // Test 1: Constructors and basic output
      cout << "1. Constructors and output:" << endl;
      BigInt a(12345);              // Should create BigInt from integer
      BigInt b("-67890");           // Should create BigInt from string
      BigInt c("0");                // Should handle zero correctly
      BigInt d = a;                 // Should use copy constructor
      cout << "a (from int): " << a << endl;        // Should print "12345"
      cout << "b (from string): " << b << endl;     // Should print "-67890"
      cout << "c (zero): " << c << endl;            // Should print "0"
      cout << "d (copy of a): " << d << endl << endl; // Should print "12345"

      // Test 2: Arithmetic operations
      cout << "2. Arithmetic operations:" << endl;
      cout << "a + b = " << a + b << endl;          // Should calculate 12345 + (-67890)
      cout << "a - b = " << a - b << endl;          // Should calculate 12345 - (-67890)
      cout << "a * b = " << a * b << endl;          // Should calculate 12345 * (-67890)
      cout << "b / a = " << b / a << endl;          // Should calculate (-67890) / 12345
      cout << "a % 100 = " << a % BigInt(100) << endl << endl; // Should calculate 12345 % 100

      // Test 3: Relational operators
      cout << "3. Relational operators:" << endl;
      cout << "a == d: " << (a == d) << endl;       // Should be true (12345 == 12345)
      cout << "a != b: " << (a != b) << endl;       // Should be true (12345 != -67890)
      cout << "a < b: " << (a < b) << endl;         // Should be false (12345 < -67890)
      cout << "a > b: " << (a > b) << endl;         // Should be true (12345 > -67890)
      cout << "c == 0: " << (c == BigInt(0)) << endl << endl; // Should be true (0 == 0)

      // Test 4: Unary operators and increments
      cout << "4. Unary operators and increments:" << endl;
      cout << "-a: " << -a << endl;                 // Should print "-12345"
      cout << "++a: " << ++a << endl;               // Should increment and print "12346"
      cout << "a--: " << a-- << endl;               // Should print "12346" then decrement
      cout << "a after decrement: " << a << endl << endl; // Should print "12345"

      // Test 5: Large number operations
      cout << "5. Large number operations:" << endl;
      BigInt num1("12345678901234567890");
      BigInt num2("98765432109876543210");
      cout << "Very large addition: " << num1 + num2 << endl;
      cout << "Very large multiplication: " << num1 * num2 << endl << endl;

      // Test 6: Edge cases and error handling
      cout << "6. Edge cases:" << endl;
      BigInt zero(0);
      BigInt one(1);
      try {
          BigInt result = one / zero;               // Should throw division by zero error
          cout << "Division by zero succeeded (unexpected)" << endl;
      } catch (const runtime_error& e) {
          cout << "Division by zero correctly threw error: " << e.what() << endl;
      }
      cout << "Multiplication by zero: " << one * zero << endl;        // Should be "0"
      cout << "Negative multiplication: " << BigInt(-5) * BigInt(3) << endl;  // Should be "-15"
      cout << "Negative division: " << BigInt(-10) / BigInt(3) << endl;       // Should be "-3"
      cout << "Negative modulus: " << BigInt(-10) % BigInt(3) << endl;        // Should be "-1"
      */

    return 0;
}
