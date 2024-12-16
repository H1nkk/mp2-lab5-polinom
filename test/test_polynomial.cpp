#include "TPolynomial.h"
#include "gtest.h"

TEST(TPolinomial, canCreateZeroPolynomial) {
	EXPECT_NO_THROW(TPolinomial p);
}

TEST(TPolinomial, canCreateComplexPolynomial) {
	EXPECT_NO_THROW(TPolinomial p("2xyz + 1000x9z1 - 893y + 4x - 23"));
}

TEST(TPolinomial, cannotCreatePolynomialOfNotPolinomialString) {
	EXPECT_ANY_THROW(TPolinomial p("hello world!"));
}

TEST(TPolinomial, cannotCreatePolynomialWithTooBigPower) {
	EXPECT_ANY_THROW(TPolinomial p("x10"));
}

TEST(TPolinomial, getStringWorksProperly) {
	TPolinomial p("x9 +y + 5   - 6y +100xyz");
	string s = p.getString();
	EXPECT_EQ(p.getString(), "x9 + 100xyz - 5y + 5");
}

TEST(TPolinomial, sumOperatorWorksProperly) {
	TPolinomial p1("x9 +y + 5   - 6y +100xyz");
	TPolinomial p2("xyz - 6");

	TPolinomial p3("x9 + 101xyz - 5y - 1");

	EXPECT_EQ(p3, p1 + p2);
}

TEST(TPolinomial, subOperatorWorksProperly) {
	TPolinomial p1("x9 +y + 5   - 6y +100xyz");
	TPolinomial p2("xyz - 6");

	TPolinomial p3("x9 + 99xyz - 5y + 11");

	EXPECT_EQ(p3, p1 - p2);
}

TEST(TPolinomial, mulOperatorWorksProperly) {
	TPolinomial p1("x9 +y + 5   - 6y +100xyz");

	TPolinomial p2("3x9 + 300xyz - 15y + 15");
	EXPECT_EQ(p2, 3 * p1);
}

TEST(TPolinomial, copiedPolynomialDoesntCopyMemoryWhenCreatedByCopying) {
	TPolinomial p1("x");
	TPolinomial p2 = p1;
	p2 -= string("x");
	EXPECT_EQ(p1, string("x"));
}

TEST(TPolinomial, copiedPolynomialDoesntCopyMemoryWhenAssignedWithAnotherPolynomial) {
	TPolinomial p1("x");
	TPolinomial p2;
	p2 = p1;
	p2 -= string("x");
	EXPECT_EQ(p1, string("x"));
}

TEST(TPolinomial, calculateWorksProperly) {
	TPolinomial p1("10x7 + 52x2y4z3");

	double res = p1.calculate(2, 15, 0.6);
	EXPECT_TRUE(fabs(p1.calculate(2, 15, 0.6) - 2275760.0) < 0.1);
}
