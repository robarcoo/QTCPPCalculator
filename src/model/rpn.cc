#include "model.h"

void s21::Model::MoveNode(std::stack<Node> &src, std::stack<Node> &dest) {
  if (src.size() > 0) {
    dest.push(src.top());
    src.pop();
  }
}

double s21::Model::RPN(std::stack<Node> input) {
  std::stack<Node> ready;
  std::stack<Node> support;
  while (input.size() > 0) {
    Node top_element = input.top();
    int top_element_type = top_element.GetType();

    if (top_element_type == number) {
      MoveNode(input, ready);
    } else if (top_element_type >= plus && top_element_type <= mod) {
      if (support.size() > 0) {
        DistributeSign(ready, support, input);
      } else {
        MoveNode(input, support);
      }
    } else if (top_element_type >= e_sin && top_element_type <= e_ln) {
      MoveNode(input, support);
    } else if (top_element_type == left_bracket) {
      MoveNode(input, support);
    } else if (top_element_type == right_bracket) {
      while (support.top().GetType() != left_bracket) {
        MoveNode(support, ready);
      }
      support.pop();
      input.pop();
    }
  }
  while (support.size() > 0) {
    MoveNode(support, ready);
  }
  return Calc(ReverseStack(ready));
}

void s21::Model::DistributeSign(std::stack<Node> &ready,
                                std::stack<Node> &support,
                                std::stack<Node> &input) {
  if (support.top().GetType() == input.top().GetType() ||
      support.top().GetPriority() >= input.top().GetPriority()) {
    MoveNode(support, ready);
    if (support.size() > 0 &&
        support.top().GetType() == input.top().GetType()) {
      MoveNode(support, ready);
    }
    MoveNode(input, support);
  } else {
    MoveNode(input, support);
  }
}