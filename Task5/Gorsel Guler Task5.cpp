#include <iostream>
#include <array>
#include <string>
#include <sstream>
#include <stdexcept>

class Stack {
private:
    static const int MAX_SIZE = 100;
    std::array<int, MAX_SIZE> data;
    int topIndex;

public:
    Stack() : topIndex(-1) {}

    void push(int value) {
        if (topIndex >= MAX_SIZE - 1) {
            throw std::overflow_error("Stack Overflow");
        }
        data[++topIndex] = value;
    }

    int pop() {
        if (topIndex < 0) {
            throw std::underflow_error("Stack Underflow");
        }
        return data[topIndex--];
    }

    bool isEmpty() const {
        return topIndex < 0;
    }
};

bool isOperator(const std::string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

int applyOperator(int a, int b, const std::string& op) {
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") {
        if (b == 0) throw std::runtime_error("Division by zero");
        return a / b;
    }
    throw std::invalid_argument("Invalid operator");
}

int evaluatePostfix(const std::string& expression) {
    Stack stack;
    std::stringstream ss(expression);
    std::string token;

    while (ss >> token) {
        if (isOperator(token)) {
            if (stack.isEmpty()) throw std::runtime_error("Insufficient operands");
            int operand2 = stack.pop();

            if (stack.isEmpty()) throw std::runtime_error("Insufficient operands");
            int operand1 = stack.pop();

            int result = applyOperator(operand1, operand2, token);
            stack.push(result);
        }
        else {
            try {
                int number = std::stoi(token);
                stack.push(number);
            }
            catch (const std::invalid_argument&) {
                throw std::invalid_argument("Invalid token: " + token);
            }
        }
    }

    if (stack.isEmpty()) throw std::runtime_error("No result on stack");
    int finalResult = stack.pop();

    if (!stack.isEmpty()) throw std::runtime_error("Multiple items on stack after evaluation");

    return finalResult;
}

int main() {
    std::string postfixExpression;

    std::cout << "Enter the postfix expression: ";
    std::getline(std::cin, postfixExpression);

    try {
        int result = evaluatePostfix(postfixExpression);
        std::cout << "Result: " << result << std::endl;
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}
