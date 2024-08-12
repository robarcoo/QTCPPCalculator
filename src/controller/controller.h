#ifndef SMARTCALCV2_SRC_CONTROLLER_CONTROLLER_H_
#define SMARTCALCV2_SRC_CONTROLLER_CONTROLLER_H_

#include <QString>

#include "../model/model.h"

namespace s21 {
class Controller {
 public:
  Controller() {}
  ~Controller() {}
  int Calculate(std::string equation, double &answer);
  double CreditAnn(double credit, int time, double percent, double &monthpay,
                   double &overpay);
  double CreditDiff(double credit, int time, double percent, double &monthpay,
                    double &overpay, double &allpay, double &lastmonth);

 private:
  Model model_;
};
}  // namespace s21

#endif  // SMARTCALCV2_SRC_CONTROLLER_CONTROLLER_H_