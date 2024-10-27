#include <iostream>
#include <string>

#define GRID_SIZE 11

void draw_grid(int gradient, int y_intercept)
{
    std::cout << "Y intercept is "<< y_intercept << ". And the Gradient is " << gradient << '\n';
    for (int y = 0; y < GRID_SIZE; y++)
    {
        for (int x = 0; x < GRID_SIZE; x++)
        {
            if ((x == std::ceil(GRID_SIZE / 2) + 1) && (y == std::ceil(GRID_SIZE / 2) - y_intercept - gradient))
            {
                std::cout << " * ";
            }
            else if ((x == std::ceil(GRID_SIZE / 2) - 1) && (y == std::ceil(GRID_SIZE / 2) - y_intercept + gradient))
            {
                std::cout << " * ";
            }
            else if (x == std::ceil(GRID_SIZE / 2))
            {
                if (y != (std::ceil(GRID_SIZE / 2) - y_intercept))
                {
                    std::cout << " | ";
                }
                else if (y_intercept == 0)
                {
                    std::cout << " * ";
                }
                else if (y_intercept > 0)
                {
                    std::cout << " * ";
                }
                else if ( y_intercept < 0)
                {
                    std::cout << " * ";
                }
            } else if (y == std::ceil(GRID_SIZE / 2))
            {
                std::cout << " - ";
            }
            else
            {
                std::cout << "   ";
            }
        }
        std::cout << "\n";
    }
}

void take_input(int& gradient, int& y_intercept)
{
    size_t index = 0;
    size_t index2 = 0;
    // y = mx+b
    std::string inp;
    std::cout << "Enter equation: ";
    std::cin >> inp;

    if(inp.find('x') == std::string::npos)
    {
        std::cout << "There must be an x and y coord\n";
        exit(EXIT_FAILURE);
    }
    if (inp.find('+') == std::string::npos && inp.find('-') == std::string::npos)
    {
        std::cout << "If no y-intercept is given, please add '+0' to the end\n";
        exit(EXIT_FAILURE);
    } else
    {
            
        index = inp.find('=');
        index2 = inp.find('x');
        std::string x = std::string(&inp[index + 1], &inp[index2+1]);
    
        gradient = std::stoi(x);

        if (inp.find('+') != std::string::npos)
        {
            index = inp.find('+');
            y_intercept = inp[index+1] - '0';
        }
        else
        {
            index = inp.find('-');
            y_intercept = std::stoi(std::string(&inp[index], &inp[index+2]));
        }
        
    }

}

int main(int argc, char* argv[])
{
    int gradient = NULL;
    int y_intercept = NULL;
    take_input(gradient, y_intercept);
    draw_grid(gradient, y_intercept);
    return 0;
}
