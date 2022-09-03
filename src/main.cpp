
#include "assignment.h"
#include "expression.h"
#include "parser.h"
#include <string>

int main() {
    std::map<std::string, double> variables{{"var1", 1}, {"var2", 2},
                                            {"var3", 3}, {"var4", 4},
                                            {"var5", 5}, {"var6", 6}};

    std::string s;
    try {
        while (true) {
            std::cout << "Enter expression\n";
            std::getline(std::cin, s);
            auto p = parse_expression(s);
            if (std::holds_alternative<AddExpression>(p)) {
                std::cout << std::get<AddExpression>(p).evaluate(variables)
                          << '\n';
            } else if (std::holds_alternative<MultExpression>(p)) {
                std::cout << std::get<MultExpression>(p).evaluate(variables)
                          << '\n';
            } else if (std::holds_alternative<Assignment>(p)) {
                double value = std::get<Assignment>(p).a->evaluate(variables);
                std::cout << std::get<Assignment>(p).i << "=" << value << '\n';
                variables[std::string{std::get<Assignment>(p).i.str}] = value;
            } else {
                std::cerr << "Unknown value\n";
                break;
            }
        }
    } catch (std::exception &e) {
        std::cout << e.what();
    }
}