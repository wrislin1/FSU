#include <iostream>

using namespace std;

class Mixed
{
	friend ostream& operator<<(ostream& s, const Mixed& f);
	friend istream& operator>>(istream& s, Mixed& f);
	friend Mixed operator++ (Mixed& f);
	friend Mixed operator++ (Mixed& f, int h);
	friend Mixed operator-- (Mixed& f);
	friend Mixed operator-- (Mixed& f, int h);
	friend bool operator== (const Mixed& m1, const Mixed& m2);
	friend bool operator!= (const Mixed& m1, const Mixed& m2);
	friend bool operator<= (const Mixed& m1, const Mixed& m2);
	friend bool operator>= (const Mixed& m1, const Mixed& m2);
	friend bool operator> (const Mixed& m1, const Mixed& m2);
	friend bool operator< (const Mixed& m1, const Mixed& m2);



public:
	Mixed ();
	Mixed (int i, int n,int d);
	Mixed (int i);
	Mixed operator+ (const Mixed& f) const;
	Mixed operator- (const Mixed& f) const;
	Mixed operator* (const Mixed& f) const;
	Mixed operator/ (const Mixed& f) const;




double Evaluate ();
void Simplify ();
void ToFraction ();

private:
	int interger;
	int numerator;
	int denominator;
	double decimal;
};