#include <iostream>
#include <vector>

using namespace std;

class Rational {
public:
		Rational(int numerator = 0, int denominator = 1)
        : numerator_(numerator), denominator_(denominator)
         {
        int d = gcd(abs(numerator), abs(denominator));
        numerator_ = numerator/d;
        denominator_ = denominator/d;
    }

    int Numerator() const {
        return numerator_;
    }

    int Denominator() const {
        return denominator_;
    }

    Rational operator+=(Rational right) {
        numerator_ += right.numerator_;
        denominator_ += right.denominator_;
        int d = gcd(abs(numerator_), abs(denominator_));
        numerator_ = numerator_/d;
        denominator_ = denominator_/d;
        return *this;
    }

    Rational operator-=(Rational right) {
        numerator_ -= right.numerator_;
        denominator_ -= right.denominator_;
        int d = gcd(abs(numerator_), abs(denominator_));
        numerator_ = numerator_/d;
        denominator_ = denominator_/d;
        return *this;
    }

    Rational operator*=(Rational right) {
        numerator_ *= right.numerator_;
        denominator_ *= right.denominator_;
        int d = gcd(abs(numerator_), abs(denominator_));
        numerator_ = numerator_/d;
        denominator_ = denominator_/d;
        return *this;
    }

    Rational operator/=(Rational right) {
        numerator_ *= right.denominator_;
        denominator_ *= right.numerator_;
        int d = gcd(abs(numerator_), abs(denominator_));
        numerator_ = numerator_/d;
        denominator_ = denominator_/d;
        return *this;
    }

    bool operator==(Rational right) {
        return numerator_ == right.Numerator() &&
            denominator_ == right.Denominator();
    }

    bool operator!=(Rational right) {
        return !(*this == right);
    }

    bool operator<(Rational right) {
        return numerator_ * right.Denominator() 
        < right.Numerator() * denominator_;
    }

    bool operator>(Rational right) {
        return numerator_ * right.Denominator() 
        > right.Numerator() * denominator_;
    }

    bool operator<=(Rational right) {
        return *this < right || *this == right;
    }

    bool operator>=(Rational right) {
        return *this > right || *this == right;
    }

private:
	int numerator_;
    int denominator_;

    int gcd(int a, int b) {
        if (b == 0) {
            return a;
        }
        else {
            return gcd(b, a%b);
        }
    }
};

ostream& operator<<(ostream& out, Rational r) {
    out << r.Numerator() << "/" << r.Denominator();
    return out;
}

istream& operator>>(istream& input, Rational& rational) {
    int numerator, denominator;
    char div;
    input >> numerator >> div >> denominator;
    rational = Rational{numerator, denominator};
    return input;
}

Rational AddSub(Rational left, Rational right, const char op) {
    int numerator;
    if (op == '-') {
        numerator = left.Numerator() * right.Denominator() 
        - right.Numerator() * left.Denominator();
    }
    else {
        numerator = left.Numerator() * right.Denominator() 
        + right.Numerator() * left.Denominator();
    }
    const int denominator = left.Denominator() * right.Denominator();

    return {numerator, denominator};
}

Rational operator+(Rational left, Rational right) {
    return AddSub(left, right, '+');
}

Rational operator+(Rational left) {
    return {left.Numerator(), left.Denominator()};
}

Rational operator-(Rational left, Rational right) {
    return AddSub(left, right, '-');
}

Rational operator-(Rational left) {
    return {-left.Numerator(), left.Denominator()};
}


int main () {

    Rational zero;
    cout << zero << endl;
	const Rational seven(7);
    cout << seven << endl;
	const Rational one_third(1, 3);
    cout << one_third << endl;
    vector<Rational> numbers;
    numbers.push_back(Rational{7, 8});
    numbers.push_back(Rational{3});
    numbers.push_back(3);
    Rational one_six;
    cin >> one_six;
    Rational sum = one_six + one_third;
    cout << sum << endl;
    cout << -sum << endl;
    sum+=one_six;
    cout << sum << endl;

    cout << one_six - one_third << endl;
    cout << (sum == sum) << endl;
    cout << (sum >= sum) << endl;
    cout << (sum <= sum) << endl;

    return 0;
}