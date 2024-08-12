#include <gtest/gtest.h>

#include "model.h"

TEST(CalcCPP3, Val)
{
  s21::Model model_;
  std::string v_test = "";
  int error1 = model_.Validate(v_test);
  ASSERT_EQ(error1, 1);

  std::string v_test1 = "(cos(5*pi.547/3)/87+54^3)*0.1";
  int error2 = model_.Validate(v_test1);
  ASSERT_EQ(error2, 1);

  std::string v_test2 = "fsggfdgdgfd";
  int error3 = model_.Validate(v_test2);
  ASSERT_EQ(error3, 1);

  std::string v_test3 = "lg(sin(5)+log())";
  int error4 = model_.Validate(v_test3);
  ASSERT_EQ(error4, 1);

  std::string v_test4 = "sin(5)";
  int error5 = model_.Validate(v_test4);
  ASSERT_EQ(error5, 0);
}

TEST(CalcCPP3, Simple)
{
  s21::Model model_;
  std::string test1 = "2+2";
  double answer = model_.Parser(test1);
  ASSERT_EQ(answer, 4);

  std::string test2 = "-2+1";
  double answer2 = model_.Parser(test2);
  ASSERT_EQ(answer2, -1);

  std::string test3 = "(cos(5*0.547/3)/87+54^3)/10";
  double answer3 = model_.Parser(test3);
  std::stringstream ss;
  ss << std::setprecision(7) << std::fixed << answer3;
  std::string formattedResult = ss.str();
  ASSERT_EQ(formattedResult, "15746.4007039");

  std::string test4 = "tan(tan(tan(5)))";
  double answer4 = model_.Parser(test4);
  std::stringstream ss1;
  ss1 << std::setprecision(7) << std::fixed << answer4;
  std::string formattedResult1 = ss1.str();
  ASSERT_EQ(formattedResult1, "-0.2485089");

  std::string test5 = "30%7";
  double answer5 = model_.Parser(test5);
  ASSERT_EQ(answer5, 2);

  std::string test6 = "+1+log(100)";
  double answer6 = model_.Parser(test6);
  ASSERT_EQ(answer6, 3);

  std::string test7 = "asin(1)+acos(1)+atan(1)";
  double answer7 = model_.Parser(test7);
  ASSERT_EQ(answer7, asin(1) + acos(1) + atan(1));
}

TEST(CalcCPP3, Hard)
{
  s21::Model model_;
  std::string h_test =
      "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
      "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))";
  double h_answer = model_.Parser(h_test);
  std::stringstream ss;
  ss << std::setprecision(7) << std::fixed << h_answer;
  std::string formattedResult = ss.str();
  ASSERT_EQ(formattedResult, "-30.0721649");

  std::string h_test1 = "(2914+140592/16/101-1723)*(1317-32288/32)";
  double h_answer1 = model_.Parser(h_test1);
  ASSERT_EQ(h_answer1, 393624);
}

TEST(CalcCPP3, Error)
{
  s21::Model model_;
  std::string dividebyzero = "5/0";
  float error_answer = model_.Parser(dividebyzero);
  ASSERT_EQ(std::isinf(error_answer), true);

  std::string logarithm = "log(0)";
  float error_answer1 = model_.Parser(logarithm);
  ASSERT_EQ(std::isnan(error_answer1), true);

  std::string nat_log = "ln(-1)";
  float error_answer2 = model_.Parser(nat_log);
  ASSERT_EQ(std::isnan(error_answer2), true);

  std::string square_root = "sqrt(-1)";
  float error_answer3 = model_.Parser(square_root);
  ASSERT_EQ(std::isnan(error_answer3), true);
}

TEST(CalcCPP3, AnnCredit)
{
  s21::Model model_;
  double monthpay = 0;
  double overpay = 0;
  double credit = 100000;
  int time = 50;
  double percent = 5;
  double wholesum = 0;
  wholesum = model_.AnnualCredit(credit, time, percent, monthpay, overpay);
  ASSERT_EQ(overpay, 10985.50);
  ASSERT_EQ(wholesum, 110985.50);
}

TEST(CalcCPP3, DiffCredit)
{
  s21::Model model_;
  double monthpay = 0;
  double overpay = 0;
  double credit = 100000;
  int time = 50;
  double percent = 5;
  double wholesum = 0;
  double allpay = 0;
  double lastmonth = 0;
  wholesum = model_.DiffCredit(credit, time, percent, monthpay, overpay, allpay,
                               lastmonth);
  ASSERT_EQ(overpay, 10625);
  ASSERT_EQ(wholesum, 110625);
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}