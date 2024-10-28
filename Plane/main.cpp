#include <iostream>
#include <string>
#include <Windows.h>

#define GRID_SIZE 21

void draw_grid(int gradient, int y_intercept, int gradient_2 = NULL, int y_intercept_2 = NULL) {
    constexpr int center = GRID_SIZE / 2;
    std::cout << "Y intercept is " << y_intercept << ". And the Gradient is " << gradient << '\n';
    if (gradient_2 != NULL && y_intercept_2 != NULL)
    {
        std::cout << "Y intercept is " << y_intercept_2 << ". And the Gradient is " << gradient_2 << '\n';
    }

    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(consoleHandle, 7);
    
    for (int y = 0; y < GRID_SIZE; y++) {
        for (int x = 0; x < GRID_SIZE; x++) {
            if (x == center) {
                // Draw vertical axis or plot the y-intercept
                if (y == center - y_intercept || (y == center - y_intercept_2 && y_intercept == NULL)) {
                    if (y_intercept_2 != NULL)
                    {
                        SetConsoleTextAttribute(consoleHandle, 9);
                        std::cout << " * ";
                        SetConsoleTextAttribute(consoleHandle, 7);
                    } else
                    {
                        SetConsoleTextAttribute(consoleHandle, 7);
                        std::cout << " * ";
                    }
                } else {
                    std::cout << " | ";
                }
            }  else if (y == center - y_intercept - gradient * (x - center)) {
                // Draw the line based on the equation
                std::cout << " * ";
            } else if (y == center - y_intercept_2 - gradient_2 * (x - center) && gradient_2 != NULL && y_intercept_2 != NULL)
            {
                SetConsoleTextAttribute(consoleHandle, 9);
                std::cout << " * ";
                SetConsoleTextAttribute(consoleHandle, 7);
            }
            else if (y == center) {
                // Draw horizontal axis
                SetConsoleTextAttribute(consoleHandle, 7);
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
    int gradient_2 = 0;
    int y_intercept_2 = 0;
    
    
    take_input(gradient, y_intercept);
    draw_grid(gradient, y_intercept);

    take_input(gradient_2, y_intercept_2);
    draw_grid(gradient, y_intercept, gradient_2, y_intercept_2);
    
    return 0;
}
