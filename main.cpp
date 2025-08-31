#include <iostream>
#include <string>
#include <vector>
using namespace std;

class BigInt
{
    string number;   // Stores the number as a string
    bool isNegative; // True if number is negative

    // Remove unnecessary leading zeros from the number string
    void removeLeadingZeros()
    {
        // TODO: Implement this function
    }

    // Compare absolute values of two BigInts (ignore signs)
    // Returns: 1 if |this| > |other|, 0 if equal, -1 if |this| < |other|
    int compareMagnitude(const BigInt &other) const
    {
        // TODO: Implement this function
        return 0;
    }

public:
    // Default constructor - initialize to zero
    BigInt()
    {
        // TODO: Implement this constructor
    }

    // Constructor from 64-bit integer
    BigInt(int64_t value)
    {
        // TODO: Implement this constructor
    }

    // Constructor from string representation
    BigInt(const string &str)
    {
         // TODO: Implement this constructor

    }

    // Copy constructor
    BigInt(const BigInt &other)
    {
        // TODO: Implement this constructor
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
        if(this == &other) return *this;
    this-> number = other.number;
    this->isNegative  = other.isNegative;

        return *this;
    }

    // Unary negation operator (-x)
    BigInt operator-() const
    {
        BigInt result;
        result.number = this->number;
        if(result.number == "0"){
                result.isNegative = false; //Unknown behavior
                return result;
        }
        result.isNegative = !this->isNegative;

        return result;
    }



    // Unary plus operator (+x)
    BigInt operator+() const
    {
        BigInt result;
        // TODO: Implement this operator
        return result;
    }

    // Addition assignment operator (x += y)
    BigInt &operator+=(const BigInt &other)
    {
        // TODO: Implement this operator
        return *this;
    }

    // Subtraction assignment operator (x -= y)
    BigInt &operator-=(const BigInt &other)
    {
        // TODO: Implement this operator
        return *this;
    }

    // Multiplication assignment operator (x *= y)
    BigInt &operator*=(const BigInt &other)
    {
        // TODO: Implement this operator
        return *this;
    }

    // Division assignment operator (x /= y)
    BigInt &operator/=(const BigInt &other)
    {
        // TODO: Implement this operator
        return *this;
    }

    // Modulus assignment operator (x %= y)
    BigInt &operator%=(const BigInt &other)
    {
        // TODO: Implement this operator
        return *this;
    }

    // Pre-increment operator (++x)
    BigInt &operator++()
    {
        // TODO: Implement this operator
        return *this;
    }

    // Post-increment operator (x++)
    BigInt operator++(int)
    {
        BigInt temp;
        // TODO: Implement this operator
        return temp;
    }

    // Pre-decrement operator (--x)
    BigInt &operator--()
    {
        // TODO: Implement this operator
        return *this;
    }

    // Post-decrement operator (x--)
    BigInt operator--(int)
    {
        BigInt temp;
        // TODO: Implement this operator
        return temp;
    }

    // Convert BigInt to string representation
    string toString() const
    {
        // TODO: Implement this function
        return "";
    }

    // Output stream operator (for printing)
    friend ostream &operator<<(ostream &os, const BigInt &num)
    {
        // TODO: Implement this operator
        return os;
    }

    // Input stream operator (for reading from input)
    friend istream &operator>>(istream &is, BigInt &num)
    {
        // TODO: Implement this operator
        return is;
    }

    // Friend declarations for comparison operators
    friend bool operator==(const BigInt &lhs, const BigInt &rhs);
    friend bool operator<(const BigInt &lhs, const BigInt &rhs);
    friend BigInt operator*(BigInt lhs  ,const BigInt &rhs);
    friend BigInt operator/(BigInt lhs , const BigInt &rhs);
    friend pair <BigInt, BigInt > dividAndMode (const BigInt &lhs,const BigInt &rhs);
    friend bool operator >=(const BigInt &lhs, const BigInt &rhs) ;
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

    return lhs + (-rhs);
}

// Binary multiplication operator (x * y)
 BigInt operator*(BigInt lhs, const BigInt &rhs)
{

   if(lhs.number == "0" || rhs.number == "0" ){

    return BigInt("0");
   }
   string a = lhs.number;
   string b = rhs.number;
   int n = a.size();
   int m = b.size();
   vector<int> res (m + n , 0);
   for(int i = n-1  ; i>= 0 ; i-- ){
    for(int j = m -1  ; j >= 0 ; j--){
        int mult = (a[i] - '0' ) * (b[j] - '0') ;
        int sum = res[i +j +1] + mult;
        res[i + j + 1] = sum%10 ;
        res[i+j] += sum/10;
    }
   }
   string finalres = "";
   for(int digit : res){
    if(!(finalres.empty()&& digit == 0)){
       finalres.push_back(digit + '0');
    }
   }
   if(finalres.empty()){

    finalres = "0";
   }
   BigInt result (finalres);
   result.isNegative = (lhs.isNegative != rhs.isNegative);
   if(finalres == "0"){
    result.isNegative = false;
   }
   result.removeLeadingZeros();
    return result;

}
// Helper function
pair <BigInt, BigInt > dividAndMode(const BigInt &lhs, const BigInt &rhs)
{
    if(rhs.number == "0")
    {
        throw runtime_error ("Division by 0");
    }
    if(lhs.number == "0")
    {
        return {BigInt("0"),BigInt("0")};
    }
    bool resultsign = (lhs.isNegative != rhs.isNegative);
    string quotient = "";
    BigInt dividend = lhs;
    BigInt divisor = rhs;
    dividend.isNegative = false;
    divisor.isNegative = false;
    BigInt remainder ("0");

    for(char d : dividend.number)
    {
        remainder = remainder * BigInt(10) + BigInt(d - '0');
        int counter = 0;
        while(remainder >= divisor)
        {
            remainder = remainder - divisor ;
            counter++;
        }

        quotient.push_back(counter + '0');
    }
    BigInt q (quotient);
    q.removeLeadingZeros();
    if(q == BigInt("0"))
    {
        q.isNegative = false ;

    }
    else
    {
        q.isNegative = resultsign;
    }
    remainder.removeLeadingZeros();
    if(remainder.number == "0")
    {
        remainder.isNegative = false ;
    }
    else
    {
        remainder.isNegative = lhs.isNegative;
    }
    return {q, remainder};
}
// Binary division operator (x / y)
BigInt operator/(BigInt lhs, const BigInt &rhs)
{
    return dividAndMode(lhs , rhs).first;
}

// Binary modulus operator (x % y)
BigInt operator%(BigInt lhs, const BigInt &rhs)
{
    return dividAndMode(lhs , rhs).second;
}

// Equality comparison operator (x == y)
bool operator==(const BigInt &lhs, const BigInt &rhs)
{
    // TODO: Implement this operator
    return false;
}

// Inequality comparison operator (x != y)
bool operator!=(const BigInt &lhs, const BigInt &rhs)
{
    // TODO: Implement this operator
    return false;
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
    // TODO: Implement this operator
    return false;
}

// Greater-than-or-equal comparison operator (x >= y)
bool operator>=(const BigInt &lhs, const BigInt &rhs)
{
    // TODO: Implement this operator
    return false;
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
