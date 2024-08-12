#include "credit.h"

#include "ui_credit.h"

Credit::Credit(QWidget *parent) : QDialog(parent), ui(new Ui::Credit) {
  ui->setupUi(this);
  ui->lineEdit_loansum->setValidator(
      new QDoubleValidator(1, 100000000000, 2, this));
  ui->lineEdit_loanpercent->setValidator(new QDoubleValidator(1, 100, 2, this));
  ui->lineEdit_loandate->setValidator(new QIntValidator(1, 100, this));
}

Credit::~Credit() { delete ui; }

void Credit::on_pushButton_credit_clicked() {
  double loansum = (ui->lineEdit_loansum->text()).toDouble();
  double loanpercent = (ui->lineEdit_loanpercent->text()).toDouble();
  int loandate = (ui->lineEdit_loandate->text()).toInt();
  double thewholesum = 0;
  double monthpay = 0;
  double overpay = 0;
  if (ui->radioButton_ann->isChecked()) {
    thewholesum = controller_.CreditAnn(loansum, loandate, loanpercent,
                                        monthpay, overpay);
    ui->label_everymonthpay->setText(
        QString::number(monthpay, 'f', fmod(monthpay, 10) ? 2 : 1));
    ui->label_overallpay->setText(
        QString::number(thewholesum, 'f', fmod(thewholesum, 10) ? 2 : 1));
    ui->label_overpay->setText(
        QString::number(thewholesum - loansum, 'f', fmod(overpay, 10) ? 2 : 1));
  } else if (ui->radioButton_diff->isChecked()) {
    double d_allpay = 0;
    double d_lastmonth = 0;
    thewholesum =
        controller_.CreditDiff(loansum, loandate, loanpercent, monthpay,
                               overpay, d_allpay, d_lastmonth);
    QString allpay = QString::number(d_allpay, 'f', fmod(d_allpay, 10) ? 2 : 1);
    QString lastmonth =
        QString::number(d_lastmonth, 'f', fmod(d_lastmonth, 10) ? 2 : 1);
    allpay += "..." + lastmonth;
    ui->label_everymonthpay->setText(allpay);
    ui->label_overallpay->setText(
        QString::number(thewholesum, 'f', fmod(thewholesum, 10) ? 2 : 1));
    ui->label_overpay->setText(
        QString::number(thewholesum - loansum, 'f', fmod(overpay, 10) ? 2 : 1));
  }
}
