#include "model.h"

double s21::Model::AnnualCredit(double credit, int time, double percent,
                                double &monthpay, double &overpay)
{
  double thewholesum = 0;
  monthpay = AnnEverymonthpay(credit, time, percent / 100 / 12);
  for (int i = 0; i < time; i++)
  {
    thewholesum += monthpay;
  }
  int result = static_cast<int>(monthpay * 100) % 100;
  result = result * time;
  thewholesum = ((int)monthpay * time) + ((double)result / 100);
  overpay = thewholesum - credit;
  return thewholesum;
}

double s21::Model::DiffCredit(double credit, int time, double percent,
                              double &monthpay, double &overpay, double &allpay,
                              double &lastmonth)
{
  double thewholesum = 0;
  monthpay = DiffEverymonthpay(credit, time, percent / 100 / 12, credit);
  allpay = monthpay;
  double loan = credit / time;
  double loanleft = credit;
  for (int i = 0; i < time; i++)
  {
    thewholesum += monthpay;
    loanleft -= loan;
    lastmonth = monthpay;
    monthpay = DiffEverymonthpay(credit, time, percent / 100 / 12, loanleft);
  }
  overpay = thewholesum - credit;
  return thewholesum;
}

double s21::Model::AnnEverymonthpay(double credit, int time, double percent)
{
  return credit * ((percent * pow((1 + percent), time)) /
                   (pow((1 + percent), time) - 1));
}

double s21::Model::DiffEverymonthpay(double credit, int time, double percent,
                                     double left_credit)
{
  return (credit / time) + (left_credit * percent);
}