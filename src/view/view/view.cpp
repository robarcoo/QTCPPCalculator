#include "view.h"

#include "credit.h"
#include "ui_view.h"

View::View(QWidget *parent) : QMainWindow(parent), ui(new Ui::View) {
  ui->setupUi(this);
  connect(ui->pushButton_zero, SIGNAL(clicked()), this, SLOT(calc_buttons()));
  connect(ui->pushButton_one, SIGNAL(clicked()), this, SLOT(calc_buttons()));
  connect(ui->pushButton_two, SIGNAL(clicked()), this, SLOT(calc_buttons()));
  connect(ui->pushButton_three, SIGNAL(clicked()), this, SLOT(calc_buttons()));
  connect(ui->pushButton_four, SIGNAL(clicked()), this, SLOT(calc_buttons()));
  connect(ui->pushButton_five, SIGNAL(clicked()), this, SLOT(calc_buttons()));
  connect(ui->pushButton_six, SIGNAL(clicked()), this, SLOT(calc_buttons()));
  connect(ui->pushButton_seven, SIGNAL(clicked()), this, SLOT(calc_buttons()));
  connect(ui->pushButton_eight, SIGNAL(clicked()), this, SLOT(calc_buttons()));
  connect(ui->pushButton_nine, SIGNAL(clicked()), this, SLOT(calc_buttons()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(calc_buttons()));

  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(calc_buttons()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(calc_buttons()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(calc_buttons()));
  connect(ui->pushButton_multiply, SIGNAL(clicked()), this,
          SLOT(calc_buttons()));
  connect(ui->pushButton_divide, SIGNAL(clicked()), this, SLOT(calc_buttons()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(calc_buttons()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(calc_buttons()));

  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(calc_buttons()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(calc_buttons()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(calc_buttons()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(calc_buttons()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(calc_buttons()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(calc_buttons()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(calc_buttons()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(calc_buttons()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(calc_buttons()));
  connect(ui->pushButton_rightbracket, SIGNAL(clicked()), this,
          SLOT(calc_buttons()));
  connect(ui->pushButton_leftbracket, SIGNAL(clicked()), this,
          SLOT(calc_buttons()));
}

View::~View() { delete ui; }

void View::calc_buttons() {
  QPushButton *button = (QPushButton *)sender();
  ui->result->setText(ui->result->text() + button->text());
}

void View::on_pushButton_clear_clicked() { ui->result->setText(""); }

void View::on_pushButton_equals_clicked() {
  double answer = 0;
  int error = controller_.Calculate(
      strdup(qPrintable(ui->result->text().replace(
          ui->pushButton_x->text(), '(' + ui->lineEdit->text() + ')'))),
      answer);
  if (!error) {
    QString string_toprint = QString::number(answer);
    ui->result->setText(string_toprint);
  } else {
    ui->result->setText("Error.");
  }
}

void View::on_pushButton_makegraphic_clicked() {
  h = 0.01;
  xBegin = (ui->lineEdit_min_x->text()).toDouble();
  xEnd = (ui->lineEdit_max_x->text()).toDouble();
  ui->widget->xAxis->setRange(xBegin, xEnd);
  ui->widget->yAxis->setRange((ui->lineEdit_min_y->text()).toDouble(),
                              (ui->lineEdit_max_y->text()).toDouble());
  double answer = 0;
  QString original = ui->result->text();

  for (X = xBegin; X <= xEnd; X += h) {
    QString copy = original;
    QString step = '(' + QString::number(X) + ')';
    copy.replace(ui->pushButton_x->text(), step);
    int error = controller_.Calculate(strdup(qPrintable(copy)), answer);
    if (!error) {
      x.push_back(X);
      y.push_back(answer);
    }
  }
  ui->widget->addGraph();
  ui->widget->graph(0)->setData(x, y);
  ui->widget->replot();
  x.clear();
  y.clear();
}

void View::on_pushButton_remove_clicked() {
  QString temp = ui->result->text();
  temp.chop(1);
  ui->result->setText(temp);
}

void View::on_pushButton_change_clicked() {
  if (ui->comboBox->currentText() == "Кредитный") {
    Credit window;
    window.setModal(true);
    window.exec();
  }
}
