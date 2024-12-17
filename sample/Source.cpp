#include <iostream>
#include <iomanip>
#include "TPolynomial.h"

using namespace std;

vector<TPolinomial> v; // vector of polinomials
vector<double> opres; // vector of calculation results
int curpol = 0;

void browse() {
	cout << "List of polinomials with their names in memory:\n";
	for (int i = 0; i < curpol; i++) {
		cout << "p" << i << ": " << v[i] << '\n';
	}
	if (opres.size() != 0) {
		cout << "List of calculation results:\n";
		for (int i = 0; i < opres.size(); i++) {
			cout << "Calculation #" << i + 1 << " result: " << opres[i] << '\n';
		}
	}
	else {
		cout << "Calculations have not been performed yet.\n";
	}
}

int main() {
	cout << std::defaultfloat;

	cout << "---------------------------------------------------------------\n";
	cout << "Keywords and corresponding types of operations:\n";
	cout << "\"+\" - sum of two polinomials\n";
	cout << "\"-\" - difference of two polinomials\n";
	cout << "\"*\" - product of polinomial and constant value\n";
	cout << "---------------------------------------------------------------\n";
	cout << "Enter \"pol\" to add polynomial to memory.\nEnter \"op\" to start performing operations with polinomials.\nEnter \"eop\" to step back.\n";
	cout << "Enter \"browse\" to browse polynomials in memory. Also shows list of calculation results.\n";
	cout << "Enter \"calc\" to calculate polynomial value at a point.\n";
	cout << "Enter \"help\" to see commands.\n";
	cout << "Enter \"end\" to close the program.\n";

	v.resize(1000);

	while (true) {
		string s;
		cout << "Enter the keyword: ";
		getline(cin, s);
		if (s == "pol") {
			while (true) {
				try {
					if (curpol == v.size()) {
						v.resize(v.size() * 2);
					}
					cout << "Enter the polinomial: ";
					cin >> v[curpol];
					cout << "Polynomial is stored in p" << curpol << '\n';
					curpol++;
					break;
				}
				catch (...) {
					cout << "Incorrect polinomial. Please, try again.\n";
				}
			}
		}
		else if (s == "op") {
			while (true) {
				string tip;
				while (true) {
					cout << "Enter the type of the operation: ";
					getline(cin, tip);
					if (tip == "eop") {
						s = "eop";
						break;
					}
					if (tip == "+" || tip == "-" || tip == "*") break;
					cout << "Unknown operation type, please try again.\n";
				}

				if (s == "eop") break;

				if (tip == "+") {
					string p1, p2;
					int i1, i2;
					while (true) {
						cout << "Select the first summand by entering polinomial's name (e.g., p0): ";
						getline(cin, p1);
						if (p1 == "eop") {
							s = p1;
							break;
						}
						if (p1 == "" || p1[0] != 'p') {
							cout << "Incorrect operand name. Please, try again.\n";
							continue;
						}
						try {
							i1 = stoi(p1.substr(1));
							if (i1 < curpol)
								break;
						}
						catch (...) {}
						cout << "Incorrect operand name. Please, try again.\n";
					}

					if (s == "eop") break;

					while (true) {
						cout << "Select the second summand by entering polinomial's name (e.g., p0): ";
						getline(cin, p2);
						if (p2 == "eop") {
							s = p2;
							break;
						}
						if (p2 == "" || p2[0] != 'p') {
							cout << "Incorrect operand name. Please, try again.\n";
							continue;
						}
						try {
							i2 = stoi(p2.substr(1));
							if (i2 < curpol)
								break;
						}
						catch (...) { }
						cout << "Incorrect operand name. Please, try again.\n";
					}
					if (s == "eop") break;

					v[curpol] = v[i1] + v[i2];
					cout << "Result: " << v[curpol] << '\n';
					cout << "Result is stored in p" << curpol << ".\n";
					curpol++;
				}

				if (tip == "-") {
					string p1, p2;
					int i1, i2;
					while (true) {
						cout << "Select the minuend by entering polinomial's name (e.g., p0): ";
						getline(cin, p1);
						if (p1 == "eop") {
							s = p1;
							break;
						}
						if (p1 == "" || p1[0] != 'p') {
							cout << "Incorrect operand name. Please, try again.\n";
							continue;
						}
						try {
							i1 = stoi(p1.substr(1));
							if (i1 < curpol)
								break;
						}
						catch (...) {}
						cout << "Incorrect operand name. Please, try again.\n";
					}

					if (s == "eop") break;

					while (true) {
						cout << "Select the subtrahend by entering polinomial's name (e.g., p0): ";
						getline(cin, p2);
						if (p2 == "eop") {
							s = p2;
							break;
						}
						if (p2 == "" || p2[0] != 'p') {
							cout << "Incorrect operand name. Please, try again.\n";
							continue;
						}
						try {
							i2 = stoi(p2.substr(1));
							if (i2 < curpol)
								break;
						}
						catch (...) {}
						cout << "Incorrect operand name. Please, try again.\n";
					}
					if (s == "eop") break;

					v[curpol] = v[i1] - v[i2];
					cout << "Result: " << v[curpol] << '\n';
					cout << "Result is stored in p" << curpol << ".\n";
					curpol++;
				}

				if (tip == "*") {
					string p1, p2;
					int i1;
					double cns;
					while (true) {
						cout << "Select the polinomial to multiply by entering polinomial's name (e.g., p0): ";
						getline(cin, p1);
						if (p1 == "eop") {
							s = p1;
							break;
						}
						if (p1 == "" || p1[0] != 'p') {
							cout << "Incorrect operand name. Please, try again.\n";
							continue;
						}
						try {
							i1 = stoi(p1.substr(1));
							if (i1 < curpol)
								break;
						}
						catch (...) {}
						cout << "Incorrect operand name. Please, try again.\n";
					}

					if (s == "eop") break;

					while (true) {
						cout << "Enter the multiplier: ";
						getline(cin, p2);

						if (p2 == "eop") {
							s = p2;
							break;
						}

						try {
							cns = stod(p2);
							break;
						} catch (...) {}
						cout << "Incorrect multiplier value. Please, try again.\n";
					}

					if (s == "eop") break;

					v[curpol] = v[i1] * cns;
					cout << "Result: " << v[curpol] << '\n';
					cout << "Result is stored in p" << curpol << ".\n";
					curpol++;
				}
			}
		}
		else if (s == "browse") {
			browse();
		} else if (s == "calc") {
			string p;
			int i;
			while (true) {
				cout << "Select the polinomial to calculate by entering polinomial's name (e.g., p0): ";
				getline(cin, p);
				if (p == "eop") {
					s = p;
					break;
				}
				if (p == "" || p[0] != 'p') {
					cout << "Incorrect polinomial name. Please, try again.\n";
					continue;
				}
				try {
					i = stoi(p.substr(1));
					if (i < curpol)
						break;
				}
				catch (...) {}
				cout << "Incorrect polinomial name. Please, try again.\n";
			}

			if (s == "eop") continue;

			string xs, ys, zs;
			double x, y, z;
			while (true) {
				cout << "Enter the x coordinate: ";
				getline(cin, xs);
				if (xs == "eop") {
					s = "eop";
					break;
				}
				try {
					x = stod(xs);
					break;
				}
				catch (...) {}
				cout << "Incorrect coordinate value. Please, try again.\n";
			}

			if (s == "eop") continue;

			while (true) {
				cout << "Enter the y coordinate: ";
				getline(cin, ys);
				if (ys == "eop") {
					s = "eop";
					break;
				}
				try {
					y = stod(ys);
					break;
				}
				catch (...) {}
				cout << "Incorrect coordinate value. Please, try again.\n";
			}

			if (s == "eop") continue;

			while (true) {
				cout << "Enter the z coordinate: ";
				getline(cin, zs);
				if (zs == "eop") {
					s = "eop";
					break;
				}
				try {
					z = stod(zs);
					break;
				}
				catch (...) {}
				cout << "Incorrect coordinate value. Please, try again.\n";
			}
			
			if (s == "eop") continue;

			double res = v[i].calculate(x, y, z);
			opres.push_back(res);
			cout << "Result of calculation #" << opres.size() << "(this calculation): " << res << '\n';
		}
		else if (s == "help") {
			cout << "---------------------------------------------------------------\n";
			cout << "Keywords and corresponding types of operations:\n";
			cout << "\"+\" - sum of two polinomials\n";
			cout << "\"-\" - difference of two polinomials\n";
			cout << "\"*\" - product of polinomial and constant value\n";
			cout << "---------------------------------------------------------------\n";
			cout << "Enter \"pol\" to add polynomial to memory.\nEnter \"op\" to start performing operations with polinomials.\nEnter \"eop\" to step back.\n";
			cout << "Enter \"browse\" to browse polynomials in memory. Also shows list of calculation results.\n";
			cout << "Enter \"calc\" to calculate polynomial value at a point.\n";
			cout << "Enter \"help\" to see commands.\n";
			cout << "Enter \"end\" to close the program.\n";
		}
		else if (s == "end") {
			break;
		}
	}

	return 0;
}