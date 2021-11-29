#include "pch.h"
#include "..\mp2-lab3-stack\TCalculator.h"

TEST(TCalculator, can_create_calculator)
{
	ASSERT_NO_THROW(TCalculator c);
}

TEST(TCalculator, can_set_and_get_expression)
{
	TCalculator c;
	string expr = "5.2 + 5";
	string result;

	ASSERT_NO_THROW(c.SetExpr(expr));
	ASSERT_NO_THROW(result = c.GetExpr());
	
	EXPECT_EQ(result, expr);
}

TEST(TCalculator, can_check_brackets)
{
	TCalculator c;
	c.SetExpr("5 + 5");
	ASSERT_NO_THROW(c.CheckExpr());
}

TEST(TCalculator, can_detect_correct_brackets)
{
	TCalculator c;
	c.SetExpr("(5)");
	ASSERT_TRUE(c.CheckExpr());
}

TEST(TCalculator, can_detect_incorrect_brackets)
{
	TCalculator c;
	c.SetExpr("5)(");
	ASSERT_FALSE(c.CheckExpr());
}

TEST(TCalculator, can_convert_to_postfix_1)
{
	TCalculator c;
	c.SetExpr("1");

	ASSERT_NO_THROW(c.PreparePostfix());
	EXPECT_EQ(c.GetPostfix(), "1");
}

TEST(TCalculator, can_convert_to_postfix_2)
{
	TCalculator c;
	c.SetExpr("1.1 + 2");

	ASSERT_NO_THROW(c.PreparePostfix());
	EXPECT_EQ(c.GetPostfix(), "1.1 2 +");
}

TEST(TCalculator, can_convert_to_postfix_3)
{
	TCalculator c;
	c.SetExpr("(1 + 3) * 2.4");

	ASSERT_NO_THROW(c.PreparePostfix());
	EXPECT_EQ(c.GetPostfix(), "1 3 + 2.4 *");
}

TEST(TCalculator, can_convert_to_postfix_4)
{
	TCalculator c;
	c.SetExpr("4 * 2^3.3 + 7 - 3 / 2");

	ASSERT_NO_THROW(c.PreparePostfix());
	EXPECT_EQ(c.GetPostfix(), "4 2 3.3 ^ * 7 + 3 2 / -");
}

TEST(TCalculator, can_add)
{
	TCalculator c;
	c.SetExpr("4.5 + 5");
	c.PreparePostfix();

	EXPECT_EQ(c.CalcPostfix(), 4.5 + 5);
	EXPECT_EQ(c.Calc(), 4.5 + 5);
}

TEST(TCalculator, can_substract)
{
	TCalculator c;
	c.SetExpr("4 - 5.0");
	c.PreparePostfix();

	EXPECT_EQ(c.CalcPostfix(), 4 - 5.0);
	EXPECT_EQ(c.Calc(), 4 - 5.0);
}

TEST(TCalculator, can_multiply)
{
	TCalculator c;
	c.SetExpr("4 * 5");
	c.PreparePostfix();

	EXPECT_EQ(c.CalcPostfix(), 4 * 5);
	EXPECT_EQ(c.Calc(), 4 * 5);
}

TEST(TCalculator, can_divide)
{
	TCalculator c;
	c.SetExpr("8 / 4");
	c.PreparePostfix();

	EXPECT_EQ(c.CalcPostfix(), 8 / 4);
	EXPECT_EQ(c.Calc(), 8 / 4);
}

TEST(TCalculator, can_raise_to_the_power)
{
	TCalculator c;
	c.SetExpr("4^2");
	c.PreparePostfix();

	EXPECT_EQ(c.CalcPostfix(), pow(4, 2));
	EXPECT_EQ(c.Calc(), pow(4, 2));
}

TEST(TCalculator, can_calculate_complex_expression_1)
{
	TCalculator c;
	c.SetExpr("1 - 2.5 + 4 * 5^2");
	c.PreparePostfix();

	EXPECT_EQ(c.CalcPostfix(), 1 - 2.5 + 4 * pow(5, 2));
	EXPECT_EQ(c.Calc(), 1 - 2.5 + 4 * pow(5, 2));
}

TEST(TCalculator, can_calculate_complex_expression_2)
{
	TCalculator c;
	c.SetExpr("((1 + 9) / 2 * 4^2) - 2.1 + 3");
	c.PreparePostfix();

	EXPECT_EQ(c.CalcPostfix(), ((1 + 9) / 2 * pow(4, 2)) - 2.1 + 3);
	EXPECT_EQ(c.Calc(), ((1 + 9) / 2 * pow(4, 2)) - 2.1 + 3);
}

TEST(TCalculator, can_calculate_complex_expression_3)
{
	TCalculator c;
	c.SetExpr("((0+2)) + (((1 - 9 + 4^2 + 8) * 2+((3)) - 1.3) * 2.6)");
	c.PreparePostfix();

	EXPECT_EQ(c.CalcPostfix(), ((0 + 2)) + (((1 - 9 + pow(4, 2) + 8) * 2 + ((3)) - 1.3) * 2.6));
	EXPECT_EQ(c.Calc(), ((0 + 2)) + (((1 - 9 + pow(4, 2) + 8) * 2 + ((3)) - 1.3) * 2.6));
}