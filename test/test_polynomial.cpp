#include "TPolynomial.h"
#include "gtest.h"

TEST(TPolinomial, canCreateZeroPolynomial) {
	EXPECT_NO_THROW(TPolinomial p);
}

TEST(TPolinomial, canCreateComplexPolynomial) {
	EXPECT_NO_THROW(TPolinomial p("2.5234xyz + 1000.123x9z1 - 893.543y + 4.7x - 23.52"));
}

TEST(TPolinomial, cannotCreatePolynomialOfNotPolinomialString) {
	EXPECT_ANY_THROW(TPolinomial p("hello world!"));
}

TEST(TPolinomial, cannotCreatePolynomialWithTooBigPower) {
	EXPECT_ANY_THROW(TPolinomial p("x10"));
}

TEST(TPolinomial, getStringWorksProperly) {
	TPolinomial p("2.50x9 +y + 5   - 6y +100xyz");
	string s = p.getString();
	EXPECT_EQ(p.getString(), "2.5x9 + 100xyz - 5y + 5");
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

	TPolinomial p2("3.5x9 + 350xyz - 17.5y + 17.5");
	EXPECT_EQ(p2, 3.5 * p1);
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
	TPolinomial p1("10.0x7 + 52x2y4z3");

	double res = p1.calculate(2, 15, 0.6);
	EXPECT_TRUE(fabs(p1.calculate(2, 15, 0.6) - 2275760.0) < 0.1);
}
