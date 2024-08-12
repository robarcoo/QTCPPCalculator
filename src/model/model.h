#ifndef SMARTCALCV2_SRC_MODEL_MODEL_H_
#define SMARTCALCV2_SRC_MODEL_MODEL_H_

#include <math.h>

#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stack>
#include <string>
namespace s21
{

  class Model
  {
  private:
    enum type_t
    {
      left_bracket = 1,
      right_bracket,
      number,
      x,
      plus,
      minus,
      unar_plus,
      unar_minus,
      multiply,
      divide,
      e_pow,
      mod,
      e_sin,
      e_cos,
      e_tan,
      e_asin,
      e_acos,
      e_atan,
      e_sqrt,
      e_log,
      e_ln
    } type_t;

    struct Node
    {
    public:
      Node()
      {
        this->value = 0;
        this->priority = -1;
        this->type = -1;
      }
      Node(double value, int priority, int type)
          : value(value), priority(priority), type(type) {}
      Node(const Node &other)
          : value(other.value), priority(other.priority), type(other.type) {}
      Node(Node &&other)
          : value(other.value), priority(other.priority), type(other.type)
      {
        other.value = 0;
        other.type = -1;
        other.priority = -1;
      }
      ~Node() {}

      Node &operator=(const Node &other)
      {
        if (this != &other)
        {
          value = other.value;
          priority = other.priority;
          type = other.type;
        }
        return *this;
      }

      double GetValue() const { return value; }

      int GetType() const { return type; }

      int GetPriority() const { return priority; }

    private:
      double value = 0.0000000;
      int priority = 0;
      int type = 0;
    };

  public:
    Model() {}
    ~Model() {}
    double Parser(std::string equation);
    std::stack<Node> ReverseStack(std::stack<Node> input);
    double RPN(std::stack<Node> input);
    int PutFuncType(std::string func);
    int PutSignType(char c, int is_number_before);
    int PutSignPriority(char sign);
    int IsSign(char str);
    std::string GetFunction(std::string equation, int index);
    void MoveNode(std::stack<Node> &src, std::stack<Node> &dest);
    void DistributeSign(std::stack<Node> &ready, std::stack<Node> &support,
                        std::stack<Node> &input);
    double Calc(std::stack<Node> ready);
    int ExecuteSign(double &answer, double number, int type);
    int ExecuteFunction(double &answer, int type);
    int Validate(std::string equation);
    int ValidateFunc(std::string function);
    double AnnualCredit(double credit, int time, double percent, double &monthpay,
                        double &overpay);
    double DiffCredit(double credit, int time, double percent, double &monthpay,
                      double &overpay, double &allpay, double &lastmonth);
    double AnnEverymonthpay(double credit, int time, double percent);
    double DiffEverymonthpay(double credit, int time, double percent,
                             double left_credit);
    double Dmod(double x, double y);
    int ExecuteNumbers(std::stack<Node> &numbers, std::stack<Node> &stack,
                       int top_type);
  };
} // namespace s21

#endif // SMARTCALCV2_SRC_MODEL_MODEL_H_
