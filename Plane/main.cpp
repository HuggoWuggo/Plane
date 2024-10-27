#include <iostream>
#include <string>

#define GRID_SIZE 11

void draw_grid(int gradient, int y_intercept) {
    constexpr int center = GRID_SIZE / 2;
    std::cout << "Y intercept is " << y_intercept << ". And the Gradient is " << gradient << '\n';
    
    for (int y = 0; y < GRID_SIZE; y++) {
        for (int x = 0; x < GRID_SIZE; x++) {
            if (x == center) {
                // Draw vertical axis or plot the y-intercept
                if (y == center - y_intercept) {
                    std::cout << " * ";
                } else {
                    std::cout << " | ";
                }
            }  else if (y == center - y_intercept - gradient * (x - center)) {
                // Draw the line based on the equation
                std::cout << " * ";
            }else if (y == center) {
                // Draw horizontal axis
                std::cout << " - ";
            } else {
                std::cout << "   ";
            }
        }
        std::cout << "\n";
    }
}

void take_input(int& gradient, int& y_intercept) {
    std::string equation;
    std::cout << "Enter equation (format y=mx+b): ";
    std::cin >> equation;

    if (equation.find("x") == std::string::npos || equation.find('=') == std::string::npos) {
        std::cerr << "Invalid format. Please enter equation as y=mx+b.\n";
        exit(EXIT_FAILURE);
    }

    int index_x = equation.find('x');
    gradient = std::stoi(equation.substr(2, index_x - 2));  // Extracts `m` in y=mx+b

    if (index_x + 1 < equation.size()) {
        y_intercept = std::stoi(equation.substr(index_x + 1));  // Extracts `b`
    } else {
        y_intercept = 0;  // Default to zero if no y-intercept is provided
    }
}

int main() {
    int gradient = 0;
    int y_intercept = 0;
    take_input(gradient, y_intercept);
    draw_grid(gradient, y_intercept);
    return 0;
}
