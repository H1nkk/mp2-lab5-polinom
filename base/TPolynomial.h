#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <map>
#include <cmath>
#include <iostream>
#include <regex>

using namespace std;

class TPolinomial {
	struct TMonomial // 0-monomial is 0x^10y^0z^0
	{
		int degree;
		int coef;

		TMonomial(int dg=1000, int cf=0) : degree(dg), coef(cf) {}
		bool operator<(const TMonomial& m) const { return degree < m.degree; }
	};
	struct Node
	{
		TMonomial monom;
		Node* pNext = nullptr;
		Node(int dg = 1000, int cf = 0) : monom(dg, cf) {}
	};
	Node* pFirst;


	int check(string polynom) const;
	TPolinomial(Node* n): pFirst(n) {}
	void del();
public:
	TPolinomial(string s = "");
	TPolinomial(const TPolinomial& pol);

	string getString() const;

	TPolinomial operator+(const TPolinomial& pol) const;
	TPolinomial& operator+=(const TPolinomial& pol);
	TPolinomial operator-(const TPolinomial& pol) const;
	TPolinomial& operator-=(const TPolinomial& pol);
	TPolinomial operator*(double c) const;
	TPolinomial& operator=(const TPolinomial& pol);
	TPolinomial& operator=(TPolinomial&& pol);
	bool operator==(const TPolinomial& pol) const;
	bool operator!=(const TPolinomial& pol) const;

	double calculate(double x, double y, double z) const;

	friend ostream& operator<<(ostream& os, const TPolinomial& pol);

	friend istream& operator>>(istream& is, TPolinomial& pol);

	friend TPolinomial operator*(double c, const TPolinomial& pol);

	~TPolinomial();
};