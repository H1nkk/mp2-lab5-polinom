#include "TPolynomial.h"

int TPolinomial::check(string polynom) const {

	polynom.erase(std::remove(polynom.begin(), polynom.end(), ' '), polynom.end());

	std::regex pattern1(R"(^$|^(([+-]?(\d+(\.\d+)?|))?(x([0-9])?)?(y([0-9])?)?(z([0-9])?)?)([+-](\d+(\.\d+)?|)?(x([0-9])?)?(y([0-9])?)?(z([0-9])?)?)*$)");
	if (regex_match(polynom, pattern1)) {
		return 1; // valid polynomial without ^
	}

	std::regex pattern2(R"(^$|^(([+-]?(\d+(\.\d+)?|))?(x(\^\d{1})?)?(y(\^\d{1})?)?(z(\^\d{1})?)?)([+-](\d+(\.\d+)?|)?(x(\^\d{1})?)?(y(\^\d{1})?)?(z(\^\d{1})?)?)*$)");
	if (regex_match(polynom, pattern2)) {
		return 2; // valid polynomial with ^
	}

	throw invalid_argument("String is not polynomial"); // not polynomial
}

void TPolinomial::del() {
	Node* p;
	while (pFirst != nullptr) {
		p = pFirst;
		pFirst = p->pNext;
		delete p;
	}
}

TPolinomial::TPolinomial(string s) {
	string tmp = "";
	for (auto x : s) {
		if (x == '+') {
			tmp += " + ";
		}
		else if (x == '-') {
			tmp += " - ";
		}
		else {
			tmp += x;
		}
	}
	s = tmp;
	int mode = check(s); // 1 - polynomial without ^; 2 - polynomial with ^

	map<int, double> mp; // degree, coef

	stringstream ss(s);
	string token;
	int znak = 1;

	while (getline(ss, token, ' ')) {
		if (token == "") continue;
		if (token == "+") {
			znak = 1;
		}
		else if (token == "-") {
			znak = -1;
		}
		else {
			int degree = 0;
			string coef;

			if (mode == 1) {
				for (int i = 0; i < token.size(); i++) {
					char c = token[i];
					if (c == 'x') {
						if (i == token.size() - 1 || token[i + 1] == 'y' || token[i + 1] == 'z') {
							degree += 100;
						}
						else {
							degree += (token[i + 1] - '0') * 100;
							i++;
						}
					}
					else if (c == 'y') {
						if (i == token.size() - 1 || token[i + 1] == 'x' || token[i + 1] == 'z') {
							degree += 10;
						}
						else {
							degree += (token[i + 1] - '0') * 10;
							i++;
						}
					}
					else if (c == 'z') {
						if (i == token.size() - 1 || token[i + 1] == 'x' || token[i + 1] == 'y') {
							degree += 1;
						}
						else {
							degree += (token[i + 1] - '0');
							i++;
						}
					}
					else {
						coef += c;
					}
				}
			}
			else {
				for (int i = 0; i < token.size(); i++) {
					char c = token[i];
					if (c == 'x') {
						if (i == token.size() - 1 || token[i + 1] == 'y' || token[i + 1] == 'z') {
							degree += 100;
						}
						else {
							degree += (token[i + 2] - '0') * 100;
							i += 2;
						}
					}
					else if (c == 'y') {
						if (i == token.size() - 1 || token[i + 1] == 'x' || token[i + 1] == 'z') {
							degree += 10;
						}
						else {
							degree += (token[i + 2] - '0') * 10;
							i += 2;
						}
					}
					else if (c == 'z') {
						if (i == token.size() - 1 || token[i + 1] == 'x' || token[i + 1] == 'y') {
							degree += 1;
						}
						else {
							degree += (token[i + 2] - '0');
							i += 2;
						}
					}
					else {
						coef += c;
					}
				}
			}

			if (coef == "") coef = "1";
			mp[degree] += stod(coef) * znak;
		}
	}

	vector<pair<int, double>> mpcopy;
	for (auto x : mp)
		if (x.second != 0)
			mpcopy.push_back(x);
	reverse(mpcopy.begin(), mpcopy.end());

	Node* pcur = new Node();
	Node* pf = pcur;

	for (auto x : mpcopy) {
		Node* pnew = new Node(x.first, x.second);
		pcur->pNext = pnew;
		pcur = pnew;
	}

	pFirst = pf;

}

TPolinomial::TPolinomial(const TPolinomial& pol) {
	Node* pf = new Node();
	Node* pcur = pf, * pcurpol = pol.pFirst->pNext;
	while (pcurpol != nullptr) {
		Node* pn = new Node(pcurpol->monom.degree, pcurpol->monom.coef);
		pcur->pNext = pn;
		pcur = pn;
		pcurpol = pcurpol->pNext;
	}
	pFirst = pf;
}


string TPolinomial::getString() const {
	Node* p = pFirst;
	string res;
	bool isfirst = true, iszero = true;
	while (p != nullptr) {
		bool neg = false;
		int deg = p->monom.degree;
		if (deg == 1000) {
			p = p->pNext;
			continue;
		}
		iszero = false;
		double coef = p->monom.coef;
		if (coef < 0) {
			neg = true;
			coef = fabs(coef);
		}
		string s;
		if (coef != 1.0 || deg == 0) {
			ostringstream oss;
			oss << std::defaultfloat << coef;
			s += oss.str();
		}
		if (deg / 100 != 0) {
			s += 'x';
			if (deg / 100 != 1)
				s += to_string(deg / 100);
		}
		if (deg / 10 % 10 != 0) {
			s += 'y';
			if (deg / 10 % 10 != 1)
				s += to_string(deg / 10 % 10);
		}
		if (deg % 10 != 0) {
			s += 'z';
			if (deg % 10 != 1)
				s += to_string(deg % 10);
		}
		if (isfirst)
			if (!neg)
				res += s + ' ';
			else
				res += '-' + s + ' ';
		else
			if (!neg)
				res += "+ " + s + ' ';
			else
				res += "- " + s + ' ';
		p = p->pNext;
		isfirst = false;
	}
	if (res.length() > 0) {
		if (res[res.size() - 1] == ' ') {
			res = res.substr(0, res.size() - 1);
		}
	}
	if (iszero) {
		return "0";
	}
	return res;
}

TPolinomial TPolinomial::operator+(const TPolinomial & pol) const {
	Node* p1 = pFirst, * p2 = pol.pFirst;
	Node* npFirst = new Node();
	Node* pcur = npFirst;
	while (p1 != nullptr || p2 != nullptr) {
		int deg1 = -1, deg2 = -1;
		double coef1 = 0, coef2 = 0;
		if (p1 != nullptr) {
			deg1 = p1->monom.degree;
			coef1 = p1->monom.coef;
		}
		if (p2 != nullptr) {
			deg2 = p2->monom.degree;
			coef2 = p2->monom.coef;
		}

		int degres;
		double coefres;

		if (deg1 == deg2) { // 0-monomial is already created
			if (deg1 == 1000) {
				if (p1 != nullptr)
					p1 = p1->pNext;
				if (p2 != nullptr)
					p2 = p2->pNext;
				continue;
			}
			degres = deg1;
			coefres = coef1 + coef2;
			if (p1 != nullptr)
				p1 = p1->pNext;
			if (p2 != nullptr)
				p2 = p2->pNext;
		}
		else if (deg1 > deg2) {
			degres = deg1;
			coefres = coef1;
			p1 = p1->pNext;
		}
		else {
			degres = deg2;
			coefres = coef2;
			p2 = p2->pNext;
		}

		if (coefres == 0) continue;

		Node* pnew = new Node(degres, coefres);
		pcur->pNext = pnew;
		pcur = pnew;
	}

	TPolinomial res(npFirst);
	return res;
}


TPolinomial& TPolinomial::operator+=(const TPolinomial& pol) {
	*this = *this + pol;
	return *this;
}

TPolinomial TPolinomial::operator-(const TPolinomial& pol) const {
	Node* p1 = pFirst, * p2 = pol.pFirst;
	Node* npFirst = new Node();
	Node* pcur = npFirst;
	while (p1 != nullptr || p2 != nullptr) {
		int deg1 = -1, deg2 = -1;
		double coef1 = 0, coef2 = 0;

		if (p1 != nullptr) {
			deg1 = p1->monom.degree;
			coef1 = p1->monom.coef;
		}
		if (p2 != nullptr) {
			deg2 = p2->monom.degree;
			coef2 = p2->monom.coef;
		}

		int degres;
		double coefres;

		if (deg1 == deg2) { // 0-monomial is already created
			if (deg1 == 1000) {
				if (p1 != nullptr)
					p1 = p1->pNext;
				if (p2 != nullptr)
					p2 = p2->pNext;
				continue;
			}
			degres = deg1;
			coefres = coef1 - coef2;
			if (p1 != nullptr)
				p1 = p1->pNext;
			if (p2 != nullptr)
				p2 = p2->pNext;
		}
		else if (deg1 > deg2) {
			degres = deg1;
			coefres = coef1;
			p1 = p1->pNext;
		}
		else {
			degres = deg2;
			coefres = -coef2;
			p2 = p2->pNext;
		}

		if (coefres == 0) continue;

		Node* pnew = new Node(degres, coefres);
		pcur->pNext = pnew;
		pcur = pnew;
	}

	TPolinomial res(npFirst);
	return res;
}

TPolinomial& TPolinomial::operator-=(const TPolinomial& pol) {
	*this = *this - pol;
	return *this;
}

TPolinomial TPolinomial::operator*(double c) const {
	TPolinomial res(*this);
	Node* p = res.pFirst;
	while (p != nullptr) {
		p->monom.coef *= c;
		p = p->pNext;
	}
	return res;
}

TPolinomial& TPolinomial::operator=(const TPolinomial& pol) {
	del();
	Node* pf = new Node();
	Node* pcur = pf, * pcurpol = pol.pFirst->pNext;
	while (pcurpol != nullptr) {
		Node* pn = new Node(pcurpol->monom.degree, pcurpol->monom.coef);
		pcur->pNext = pn;
		pcur = pn;
		pcurpol = pcurpol->pNext;
	}
	pFirst = pf;
	return *this;
}

TPolinomial& TPolinomial::operator=(TPolinomial&& pol) {
	del();
	pFirst = pol.pFirst;
	pol.pFirst = nullptr;
	return *this;
}

bool TPolinomial::operator==(const TPolinomial& pol) const {
	Node* p1 = pFirst, * p2 = pol.pFirst;
	while (p1 != nullptr && p2 != nullptr) {
		if (p1->monom.degree != p2->monom.degree || p1->monom.coef != p2->monom.coef) {
			return false;
		}
		p1 = p1->pNext;
		p2 = p2->pNext;
	}
	if (p1 != p2) return false;
	return true;
}

bool TPolinomial::operator!=(const TPolinomial& pol) const {
	return !((*this) == pol);
}

double TPolinomial::calculate(double x, double y, double z) const {
	Node* p = pFirst;
	double res = 0.0;
	while (p != nullptr) {
		if (p->monom.degree == 1000) {
			p = p->pNext;
			continue;
		}

		double mon = 1.0;
		mon *= p->monom.coef;
		mon *= pow(x, (p->monom.degree / 100));
		mon *= pow(y, (p->monom.degree / 10 % 10));
		mon *= pow(z, (p->monom.degree % 10));

		res += mon;
		p = p->pNext;
	}

	return res;
}

ostream& operator<<(ostream& os, const TPolinomial& pol) {
	os << pol.getString();
	return os;
}

istream& operator>>(istream& is, TPolinomial& pol) {
	string s;
	getline(is, s);
	TPolinomial tmp(s);
	pol = tmp;
	return is;
}

TPolinomial operator*(double c, const TPolinomial& pol) { // ¿¿¿¿¿¿¿¿¿¿¿¿¿ Ï· ÌÂ ‰‡·Î?
	return (pol * c);
}

TPolinomial::~TPolinomial() {
	del();
}