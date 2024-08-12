#include "model.h"

double s21::Model::Calc(std::stack<Node> stack)
{
  int error = 0;
  double answer = 0;
  std::stack<Node> numbers;
  std::stack<Node> power;
  while (stack.size() > 0 && !error)
  {
    int top_type = stack.top().GetType();
    if (top_type == number)
    {
      MoveNode(stack, numbers);
    }
    else if (top_type == unar_plus || top_type == unar_minus)
    {
      double number_one = numbers.top().GetValue();
      numbers.pop();
      error = ExecuteSign(number_one, 0, top_type);
      Node answer(number_one, 0, number);
      stack.pop();
      numbers.push(answer);
    }
    else if (top_type >= plus && top_type <= mod)
    {
      error = ExecuteNumbers(numbers, stack, top_type);
    }
    else if (top_type >= e_sin && top_type <= e_ln)
    {
      double number_one = numbers.top().GetValue();
      numbers.pop();
      error = ExecuteFunction(number_one, top_type);
      stack.pop();
      Node answer(number_one, 0, number);
      numbers.push(answer);
    }
  }
  if (error == 1)
  {
    answer = std::nan("1");
  }
  else if (error == 2)
  {
    answer = std::numeric_limits<double>::infinity();
  }
  else
  {
    answer = numbers.top().GetValue();
  }

  return answer;
}

int s21::Model::ExecuteNumbers(std::stack<Node> &numbers,
                               std::stack<Node> &stack, int top_type)
{
  int error = 0;
  double number_two = numbers.top().GetValue();
  numbers.pop();
  double number_one = numbers.top().GetValue();
  numbers.pop();
  error = ExecuteSign(number_one, number_two, top_type);
  stack.pop();
  Node answer(number_one, 0, number);
  numbers.push(answer);
  return error;
}
int s21::Model::ExecuteFunction(double &answer, int type)
{
  int error = 0;
  switch (type)
  {
  case e_sin:
    answer = sin(answer);
    break;
  case e_cos:
    answer = cos(answer);
    break;
  case e_tan:
    answer = tan(answer);
    break;
  case e_asin:
    answer = asin(answer);
    break;
  case e_acos:
    answer = acos(answer);
    break;
  case e_atan:
    answer = atan(answer);
    break;
  case e_sqrt:
    if (answer >= 0.0)
    {
      answer = sqrt(answer);
    }
    else
    {
      error = 1;
    }
    break;
  case e_log:
    if (answer > 0.0)
    {
      answer = log10(answer);
    }
    else
    {
      error = 1;
    }
    break;
  case e_ln:
    if (answer > 0.0)
    {
      answer = log(answer);
    }
    else
    {
      error = 1;
    }
    break;
  }
  return error;
}
int s21::Model::ExecuteSign(double &answer, double number, int type)
{
  int error = 0;
  int sign = 0;
  switch (type)
  {
  case plus:
    answer += number;
    break;
  case minus:
    answer -= number;
    break;
  case multiply:
    answer *= number;
    break;
  case divide:
    if (number == 0)
    {
      error = 2;
    }
    else
    {
      answer /= number;
    }
    break;
  case e_pow:
    if (answer < 0)
    {
      sign = 1;
      answer = answer * -1.0;
    }
    answer = pow(answer, number);
    if (sign && Dmod(number, 2.0) == 1)
    {
      answer = -(answer);
    }
    break;
  case mod:
    answer = Dmod(answer, number);
    break;
  case unar_minus:
    answer = -(answer);
  }
  return error;
}

double s21::Model::Dmod(double x, double y) { return x - (int)(x / y) * y; }