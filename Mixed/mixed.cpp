#include "mixed.h"
#include <iostream>


using namespace std;

Mixed::Mixed()
{
	interger = 0;
	numerator = 0;
	denominator = 1;
}

Mixed::Mixed (int i)
{
	interger = i;
	numerator = 0;
	denominator = 1;
}

Mixed::Mixed (int i, int n, int d)
{
	if (d <= 0)
	{
		interger = 0;
		numerator = 0;
		denominator = 1;
	}
	else if (((i < 0) || (i > 0)) && (n < 0))
	{
		interger = 0;
		numerator = 0;
		denominator = 1;
	}

	else 
	{
		interger = i;
		numerator = n;
		denominator = d;
	}
}


ostream& operator<< (ostream& s, const Mixed& f)
{
	if (((f.interger <= 0) || (f.interger >= 0)) && ( f.numerator == 0))
		s << f.interger;
	else if ((f.interger == 0) && (f.numerator != 0))
		s << f.numerator << "/" << f.denominator;
	else
	s << f.interger <<" " << f.numerator << '/' << f.denominator;
  return s;
}

istream& operator>> (istream& s, Mixed& f)
{
	int i, n, d;
	char divsign;

	s >> i >> n >> divsign >> d;

	if (d <= 0)
	{
		f.interger = 0;
		f.numerator = 0;
		f.denominator = 1;
	}
	else if (((i < 0) || (i > 0)) && (n < 0))
	{
		f.interger = 0;
		f.numerator = 0;
		f.denominator = 1;
	}
	else 
	{
		f.interger = i;
		f.numerator = n;
		f.denominator = d;
	}
	return s;
}

Mixed Mixed::operator+(const Mixed& f) const
{
Mixed r;
	int temp1, temp2, temp3, temp4, remainder;

temp1 = (interger * denominator) + numerator;
temp2 = denominator;

temp3 = (f.interger * f.denominator) + f.numerator;
temp4 = f.denominator;

r.numerator = (temp1 * temp4) + (temp2 * temp3);
r.denominator = temp2 * temp4;

if (r.numerator > r.denominator)
	{
		temp1 = r.numerator / r.denominator;
		temp2 = r.numerator % r.denominator;
		r.numerator = temp2;
		r.interger =  temp1;
	}
else
r.interger = 0;

	temp1 = r.numerator;
	temp2 = r.denominator;

	 remainder = temp2 % temp1;
	
	while (remainder != 0)
	{
		temp2 = temp1;
		temp1 = remainder;
		remainder = temp2 % temp1;
	}

	r.numerator = r.numerator / temp2;
	r.denominator = r.denominator / temp2;


	return r;
}

Mixed Mixed::operator- (const Mixed& f) const
{
		Mixed r;
	int temp1, temp2, temp3, temp4, remainder;

temp1 = (interger * denominator) + numerator;
temp2 = denominator;

temp3 = (f.interger * f.denominator) + f.numerator;
temp4 = f.denominator;

r.numerator = (temp1 * temp4) - (temp2 * temp3);
r.denominator = temp2 * temp4;

if (r.numerator > r.denominator)
	{
		temp1 = r.numerator / r.denominator;
		temp2 = r.numerator % r.denominator;
		r.numerator = temp2;
		r.interger =  temp1;
	}
else
r.interger = 0;

	temp1 = r.numerator * 2;
	temp2 = r.denominator * 2;

	 remainder = temp2 % temp1;
	
	while (remainder != 0)
	{
		temp1 = remainder;
		temp2 = temp1;
		remainder = temp2 % temp1;
	}

	r.numerator = numerator / temp2;
	r.denominator = denominator / temp2;


	return r;
}
	

Mixed Mixed::operator*(const Mixed& f) const
{
	Mixed r;
	int temp1, temp2, temp3, temp4, remainder;

temp1 = (interger * denominator) + numerator;
temp2 = denominator;

temp3 = (f.interger * f.denominator) + f.numerator;
temp4 = f.denominator;

r.numerator = temp1 * temp3;
r.denominator = temp3 * temp4;

if (r.numerator > r.denominator)
	{
		temp1 = r.numerator / r.denominator;
		temp2 = r.numerator % r.denominator;
		r.numerator = temp2;
		r.interger = temp1;
	}
else
r.interger = 0;

	temp1 = r.numerator * 2;
	temp2 = r.denominator * 2;

	 remainder = temp2 % temp1;
	
	while (remainder != 0)
	{
		temp1 = remainder;
		temp2 = temp1;
		remainder = temp2 % temp1;
	}

	r.numerator = numerator / temp2;
	r.denominator = denominator / temp2;


	return r;
}


Mixed Mixed::operator/(const Mixed& f) const
{
Mixed r;
int temp1;
int temp2;
int temp3;
int temp4;
int remainder;

if (((f.interger == 0) && (f.numerator == 0)) || ((interger == 0) && (numerator == 0)))
{
	r.interger = 0;
	r.numerator = 0;
	r.denominator = 1;
}
else
{
temp1 = (interger * denominator) + numerator;
temp2 = denominator;

temp3 = (f.interger * f.denominator) + f.numerator;
temp4 = f.denominator;

r.numerator = temp1 * temp4;
r.denominator = temp2 * temp3;
}

if (r.numerator > r.denominator)
	{
		temp1 = r.numerator / r.denominator;
		temp2 = r.numerator % r.denominator;
		r.numerator = temp2;
		r.interger = temp1;
	}
else
r.interger = 0;

	temp1 = r.numerator;
	temp2 = r.denominator;

	 remainder = temp2 % temp1;
	
while (remainder != 0)
	{
		temp2 = temp1;
		temp1 = remainder;
		remainder = temp2 % temp1;
	}

	r.numerator = r.numerator / temp1;
	r.denominator = r.denominator / temp1;

	if (r.numerator > r.denominator)
	{
		temp1 = r.numerator / r.denominator;
		temp2 = r.numerator % r.denominator;
		r.numerator = temp2;
		r.interger = r.interger + temp2;
	}

	return r;
}

Mixed operator++ (Mixed& f)
{
	f.interger++;

	return f;
}

Mixed operator ++(Mixed &f, int h)
{
	Mixed r;

	r.interger = f.interger;
	r.numerator = f.numerator;
	r.denominator = f.denominator;

	f.interger++;

	return r;
}


void Mixed::Simplify()
{
	int temp1, temp2, remainder;

		if (numerator > denominator)
	{
		temp1 = numerator / denominator;
		temp2 = numerator % denominator;
		numerator = temp2;
		interger = interger + temp1;
	}

	temp1 = numerator;
	temp2 = denominator;

	 remainder = temp2 % temp1;
	
while (remainder != 0)
	{
		temp2 = temp1;
		temp1 = remainder;
		remainder = temp2 % temp1;
	}

	numerator = numerator / temp1;
	denominator = denominator / temp1;

	if (numerator > denominator)
	{
		temp1 = numerator / denominator;
		temp2 = numerator % denominator;
		numerator = temp2;
		interger = interger + temp2;
	}



}

Mixed operator-- (Mixed& f)
{
	f.interger-- ;

	return f;
}

Mixed operator--(Mixed& f, int fake)
{
	Mixed r;

	r.interger = f.interger;
	r.numerator = f.numerator;
	r.denominator = f.denominator;

	f.interger--;

	return r;
}


bool operator==(const Mixed& m1,const Mixed& m2)
{
int temp1,temp2,temp3,temp4,temp5,temp6;

	temp1 = (m1.interger * m1.denominator) + m1.numerator;
	temp2 = m1.denominator;

	temp3 = (m2.interger * m2.denominator) + m2.numerator;
	temp4 = m2.denominator;

	temp5 = temp1 * temp4;
	temp6 = temp3 * temp2;

		if (temp5 == temp6)
			return true;
		else
			return false;

}

bool operator>(const Mixed& m1,const Mixed& m2) 
{
	int temp1,temp2,temp3,temp4,temp5,temp6;

	temp1 = (m1.interger * m1.denominator) + m1.numerator;
	temp2 = m1.denominator;

	temp3 = (m2.interger * m2.denominator) + m2.numerator;
	temp4 = m2.denominator;

	temp5 = temp1 * temp4;
	temp6 = temp3 * temp2;

		if (temp5 > temp6)
			return true;
		else
			return false;
}

bool operator>=(const Mixed& m1,const Mixed& m2) 
{
	int temp1,temp2,temp3,temp4,temp5,temp6;

	temp1 = (m1.interger * m1.denominator) + m1.numerator;
	temp2 = m1.denominator;

	temp3 = (m2.interger * m2.denominator) + m2.numerator;
	temp4 = m2.denominator;

	temp5 = temp1 * temp4;
	temp6 = temp3 * temp2;

		if (temp5 >= temp6)
			return true;
		else
			return false;
}

bool operator<=(const Mixed& m1,const Mixed& m2)
{
	int temp1,temp2,temp3,temp4,temp5,temp6;

	temp1 = (m1.interger * m1.denominator) + m1.numerator;
	temp2 = m1.denominator;

	temp3 = (m2.interger * m2.denominator) + m2.numerator;
	temp4 = m2.denominator;

	temp5 = temp1 * temp4;
	temp6 = temp3 * temp2;

		if (temp5 <= temp6)
			return true;
		else
			return false;
}

bool operator!=(const Mixed& m1,const Mixed& m2) 
{
	int temp1,temp2,temp3,temp4,temp5,temp6;

	temp1 = (m1.interger * m1.denominator) + m1.numerator;
	temp2 = m1.denominator;

	temp3 = (m2.interger * m2.denominator) + m2.numerator;
	temp4 = m2.denominator;

	temp5 = temp1 * temp4;
	temp6 = temp3 * temp2;

		if (temp5 != temp6)
			return true;
		else
			return false;
}

bool operator< (const Mixed& m1, const Mixed& m2)
{
		int temp1,temp2,temp3,temp4,temp5,temp6;

	temp1 = (m1.interger * m1.denominator) + m1.numerator;
	temp2 = m1.denominator;

	temp3 = (m2.interger * m2.denominator) + m2.numerator;
	temp4 = m2.denominator;

	temp5 = temp1 * temp4;
	temp6 = temp3 * temp2;

		if (temp5 < temp6)
			return true;
		else
			return false;
}


double Mixed::Evaluate()
{
	double temp1, temp2, temp3, temp4;

	temp1 = interger;
	temp2 = numerator;
	temp3 = denominator;
	temp4 = temp2/temp3;

	decimal = temp1 + temp4;
	return decimal;
}

void Mixed::ToFraction()
{
	int temp1, temp2;

	if (interger < 0) 
	{
	temp1 = ((interger * (-1)) * (denominator)) + numerator;
	temp2 = denominator;

	interger = 0;
	numerator = temp1 * (-1);
	denominator = temp2;

	}

	else if (numerator < 0)
	{
	temp1 = (interger * denominator) + ( (-1) * numerator);
	temp2 = denominator;

	interger = 0;
	numerator = temp1 * (-1);
	denominator = temp2;
	}
	else
	{
	temp1 = (interger * denominator) + numerator;
	temp2 = denominator;

	interger = 0;
	numerator = temp1;
	denominator = temp2;

	}

}