#include "controller.h"

int s21::Controller::Calculate(std::string equation, double &answer) {
  int error = model_.Validate(equation);
  if (!error) {
    answer = model_.Parser(equation);
  }
  return error;
}

double s21::Controller::CreditAnn(double credit, int time, double percent,
                                  double &monthpay, double &overpay) {
  return model_.AnnualCredit(credit, time, percent, monthpay, overpay);
}
double s21::Controller::CreditDiff(double credit, int time, double percent,
                                   double &monthpay, double &overpay,
                                   double &allpay, double &lastmonth) {
  return model_.DiffCredit(credit, time, percent, monthpay, overpay, allpay,
                           lastmonth);
}