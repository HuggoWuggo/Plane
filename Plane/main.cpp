#include <iostream>
#include <string>
#include <Windows.h>
#include <climits>

#define GRID_SIZE 21

void draw_grid(int gradient, int y_intercept, int gradient_2 = INT_MIN, int y_intercept_2 = INT_MIN) {
    constexpr int center = GRID_SIZE / 2;
    std::cout << "Y intercept is " << y_intercept << ". And the Gradient is " << gradient << '\n';
    if (gradient_2 != INT_MIN && y_intercept_2 != INT_MIN) {
        std::cout << "Y intercept of second line is " << y_intercept_2 << ". And the Gradient is " << gradient_2 << '\n';
    }

    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(consoleHandle, 7);

    for (int y = 0; y < GRID_SIZE; y++) {
        for (int x = 0; x < GRID_SIZE; x++) {
            int y1 = center - y_intercept - gradient * (x - center);     // y-value for first line
            int y2 = center - y_intercept_2 - gradient_2 * (x - center);  // y-value for second line

            // Check for the intersection point
            if (gradient_2 != INT_MIN && y_intercept_2 != INT_MIN && y == y1 && y == y2) {
                SetConsoleTextAttribute(consoleHandle, 12);  // Red color
                std::cout << " * ";
                SetConsoleTextAttribute(consoleHandle, 7);    // Reset to default color
            }
            else if (x == center) {
                // Draw vertical axis or plot the y-intercepts
                if (y == center - y_intercept) {
                    SetConsoleTextAttribute(consoleHandle, 10);
                    std::cout << " * ";
                    SetConsoleTextAttribute(consoleHandle, 7);
                } else if (y == center - y_intercept_2 && y_intercept_2 != INT_MIN) {
                    SetConsoleTextAttribute(consoleHandle, 9);  // Different color for second line's y-intercept
                    std::cout << " * ";
                    SetConsoleTextAttribute(consoleHandle, 7);
                } else {
                    std::cout << " | ";
                }
            } else if (y == y1) {
                // Draw the first line
                SetConsoleTextAttribute(consoleHandle, 10);
                std::cout << " * ";
                SetConsoleTextAttribute(consoleHandle, 7);
            } else if (y == y2 && gradient_2 != INT_MIN) {
                // Draw the second line
                SetConsoleTextAttribute(consoleHandle, 9);
                std::cout << " * ";
                SetConsoleTextAttribute(consoleHandle, 7);
            } else if (y == center) {
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

    int index_x = static_cast<int>(equation.find('x'));
    gradient = std::stoi(equation.substr(2, index_x - 2));  // Extracts `m` in y=mx+b

    if (index_x + 1 < static_cast<int>(equation.size())) {
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