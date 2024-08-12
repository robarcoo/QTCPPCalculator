#ifndef SMARTCALCV2_SRC_VIEW_CREDIT_H_
#define SMARTCALCV2_SRC_VIEW_CREDIT_H_

#include <QDialog>
#include <QtGui/QDoubleValidator>

#include "../../controller/controller.h"

namespace Ui {
class Credit;
}

class Credit : public QDialog {
  Q_OBJECT

 public:
  explicit Credit(QWidget *parent = nullptr);
  ~Credit();

 private slots:
  void on_pushButton_credit_clicked();

 private:
  Ui::Credit *ui;
  s21::Controller controller_;
};

#endif  // SMARTCALCV2_SRC_VIEW_CREDIT_H_
