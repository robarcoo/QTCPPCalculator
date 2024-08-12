#include "model.h"
/*
+ parser
+ identify_func_type
+ put_sign_type
+ put_sign_priority
+ is_sign
*/

double s21::Model::Parser(std::string equation) {
  std::stack<Node> input;
  int is_number_before = 0;
  int size = equation.size();
  for (int i = 0; i < size; i++) {
    if (isdigit(equation[i])) {
      std::string str_number = "";
      while (isdigit(equation[i]) || equation[i] == ',' || equation[i] == '.') {
        str_number += equation[i];
        i++;
      }
      i--;
      is_number_before = 1;
      Node number_to_push(stof(str_number), 0, number);
      input.push(number_to_push);
    } else if (IsSign(equation[i])) {
      Node sign_to_push(0, PutSignPriority(equation[i]),
                        PutSignType(equation[i], is_number_before));
      input.push(sign_to_push);
      is_number_before = 0;
    } else if (equation[i] == '(' || equation[i] == ')') {
      int type = equation[i] == '(' ? left_bracket : right_bracket;
      Node bracket_to_push(0, -1, type);
      input.push(bracket_to_push);
      is_number_before = type == left_bracket ? 0 : 1;
    } else if (isalpha(equation[i])) {
      std::string function = GetFunction(equation, i);
      Node function_to_push(0, 4, PutFuncType(function));
      input.push(function_to_push);
      while (equation[i + 1] != '(') {
        i++;
      }
    }
  }
  return RPN(ReverseStack(input));
}

std::stack<s21::Model::Node> s21::Model::ReverseStack(std::stack<Node> input) {
  std::stack<Node> new_stack;
  while (input.empty() != 1) {
    new_stack.push(input.top());
    input.pop();
  }
  return new_stack;
}

int s21::Model::IsSign(char str) {
  return str == '-' || str == '+' || str == '*' || str == '/' || str == '^' ||
         str == '%';
}

int s21::Model::PutSignType(char sign, int is_number_before) {
  int type = 0;
  switch (sign) {
    case '+':
      if (is_number_before) {
        type = plus;
      } else {
        type = unar_plus;
      }
      break;
    case '-':
      if (is_number_before) {
        type = minus;
      } else {
        type = unar_minus;
      }
      break;
    case '*':
      type = multiply;
      break;
    case '/':
      type = divide;
      break;
    case '^':
      type = e_pow;
      break;
    case '%':
      type = mod;
      break;
  }
  return type;
}

int s21::Model::PutSignPriority(char sign) {
  int priority = 0;
  switch (sign) {
    case '+':
      priority = 1;
      break;
    case '-':
      priority = 1;
      break;
    case '*':
      priority = 2;
      break;
    case '/':
      priority = 2;
      break;
    case '^':
      priority = 3;
      break;
    case '%':
      priority = 2;
      break;
  }
  return priority;
}

std::string s21::Model::GetFunction(std::string equation, int index) {
  std::string temp = "";
  int f_left_bracket = 0;
  int size = equation.size();
  for (int i = index; i < size && !f_left_bracket; i++) {
    if (equation[i + 1] == '(') {
      f_left_bracket++;
    }
    temp += equation[i];
  }

  return temp;
}

int s21::Model::PutFuncType(std::string func) {
  int type = 0;
  if (func.compare("sin") == 0) {
    type = e_sin;
  } else if (func.compare("cos") == 0) {
    type = e_cos;
  } else if (func.compare("tan") == 0) {
    type = e_tan;
  } else if (func.compare("asin") == 0) {
    type = e_asin;
  } else if (func.compare("acos") == 0) {
    type = e_acos;
  } else if (func.compare("atan") == 0) {
    type = e_atan;
  } else if (func.compare("sqrt") == 0) {
    type = e_sqrt;
  } else if (func.compare("log") == 0) {
    type = e_log;
  } else if (func.compare("ln") == 0) {
    type = e_ln;
  }
  return type;
}