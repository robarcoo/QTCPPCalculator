#ifndef SMARTCALCV2_SRC_VIEW_VIEW_H_
#define SMARTCALCV2_SRC_VIEW_VIEW_H_

#include <QMainWindow>

#include "credit.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

class View : public QMainWindow {
  Q_OBJECT

 public:
  View(QWidget *parent = nullptr);
  ~View();

 private:
  Ui::View *ui;
  double xBegin, xEnd, h, X;
  int N;
  QVector<double> x, y;
  s21::Controller controller_;

 private slots:
  void calc_buttons();
  void on_pushButton_clear_clicked();
  void on_pushButton_equals_clicked();
  void on_pushButton_makegraphic_clicked();
  void on_pushButton_remove_clicked();
  void on_pushButton_change_clicked();
};

#endif  // SMARTCALCV2_SRC_VIEW_VIEW_H_
