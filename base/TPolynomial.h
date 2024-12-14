#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <map>

using namespace std;

class TPolinomial {
	struct TMonomial // 0-monomial is 0x^10y^0z^0
	{
		short degree;
		int coef;

		TMonomial(short dg=1000, int cf=0) : degree(dg), coef(cf) {}
		bool operator<(const TMonomial& m) const {
			return degree < m.degree;
		}
	};
	struct Node
	{
		TMonomial monom;
		Node* pNext = nullptr;
		Node(short dg=1000, int cf=0) : monom(dg, cf) {}
	};
	Node* pFirst;

	int check(string& polynom) { // TODO

		// check without ^ (2x2y3 - 4z3) TODO
		return 1; // это если норм строка в виде без ^

		// check with ^ TODO
		return 2; // это если норм строка в виде с ^

		throw "bad string"; // это если строка не полином или не соответсвует ограничени€м
	}
public:
	TPolinomial(string s) {
		int mode = check(s); // 1 - polynomial without ^; 2 - polynomial with ^


		vector<TMonomial> tmp;
		map<short, int> mp; // мапа из степени в коэф

		stringstream ss(s);
		string token;
		int znak = 1;

		while (getline(ss, token, ' ')) {
			if (token == "+") {
				znak = 1;
			}
			else if (token == "-") {
				znak = -1;
			}
			else {
				short degree = 0;
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

				if (coef == "") coef = 1;
				mp[degree] += stoi(coef) * znak;
			}
		}

		if (mp.size() == 0) return;

		vector<pair<short, int>> mpcopy;
		for (auto x : mp) 
			if (x.second != 0)
				mpcopy.push_back(x);
		reverse(mpcopy.begin(), mpcopy.end());

		pFirst = new Node();

		Node* pcur = pFirst;

		for (auto x : mpcopy) {
			Node* pnew = new Node(x.first, x.second);
			pcur->pNext = pnew;
			pcur = pnew;
		}

		for (Node* pcur = pFirst; pcur != nullptr; pcur = pcur->pNext) { // тестовый проход, ”ƒјЋ»“№
			int g = 142;
		}
	}
	~TPolinomial() { // TODO

	}
};