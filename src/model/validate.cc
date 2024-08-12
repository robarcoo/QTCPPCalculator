#include <iostream>

#include "model.h"

int s21::Model::Validate(std::string equation) {
  int sign_before = 0, func_before = 0, num_before = 0, x_before = 0;
  int left_bracket = 0, right_bracket = 0, smth_in_brackets = 0,
      count_point = 0;
  int error = 0, check_null = 0, size = equation.size();

  for (int i = 0; i < size && !error; i++) {
    check_null = 1;
    if (IsSign(equation[i])) {
      error = (sign_before == 0) ? 0 : 1;
      if (num_before == 0 && !(equation[i] == '+' || equation[i] == '-')) {
        error = 1;
      }
      sign_before = 1;
      func_before = 0;
      num_before = 0;
      x_before = 0;
    } else if (isdigit(equation[i])) {
      int count_digits = 0;
      error = (func_before == 0 && x_before == 0) ? 0 : 1;
      smth_in_brackets = left_bracket != 0 ? 1 : 0;
      while (
          (isdigit(equation[i]) || equation[i] == ',' || equation[i] == '.') &&
          !error) {
        i++;
        if (equation[i] == ',' || equation[i] == '.') {
          count_point++;
        } else {
          count_digits++;
        }
        if (count_digits > 10) {
          error = 1;
        }
      }
      i--;
      sign_before = 0;
      num_before = 1;
      if (count_point > 1) {
        error = 1;
      } else {
        count_point = 0;
      }
    } else if (isalpha(equation[i])) {
      std::string function = GetFunction(equation, i);
      error = ValidateFunc(function);
      smth_in_brackets = left_bracket != 0 ? 1 : 0;
      sign_before = 0;
      while (equation[i] != '(' && i < size) {
        i++;
      }
      if (equation[i] != '(') {
        error = 1;
      }
      i--;
    } else if (equation[i] == '(' || equation[i] == ')') {
      right_bracket =
          (equation[i] == ')') ? right_bracket + 1 : right_bracket - 1;
      left_bracket = (equation[i] == '(') ? left_bracket + 1 : left_bracket - 1;
      error = equation[i] == ')' && smth_in_brackets == 0 ? 1 : 0;
      sign_before = 0;
    } else {
      error = 1;
    }
  }

  error = right_bracket != 0 || left_bracket != 0 || sign_before == 1 ||
                  check_null == 0
              ? 1
              : error;
  return error;
}

int s21::Model::ValidateFunc(std::string function) {
  int error = 1;
  std::string funcs[] = {
      "cos", "sin", "tan", "asin", "acos", "atan", "sqrt", "log", "ln",
  };
  for (int i = 0; i < 9; i++) {
    if (function == funcs[i]) {
      error = 0;
    }
  }
  return error;
}