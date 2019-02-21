#include "polynomials.h"

#include <iostream>
#include <memory>
#include <tuple>

static std::tuple<double, double, double> getCoeffsFromUser()
{
    double a, b, c;
    std::cout << "a: ";
    std::cin >> a;
    std::cout << "b: ";
    std::cin >> b;
    std::cout << "c: ";
    std::cin >> c;
    std::cout << "\n";

    return std::make_tuple(a, b, c);
}

int main()
{
    try
    {
        std::cout << "This application finds the roots of quadratic equations \n"
            << "of the form f(x) = ax^2 + bx + c.  Enter your coefficients.\n\n";

        const auto[a, b, c] = getCoeffsFromUser();

        std::unique_ptr<const Equation> equation;
        if (a != 0)
            equation = std::make_unique<const Quadratic>(a, b, c);
        else
            equation = std::make_unique<const Linear>(b, c);

        std::cout << equation->formattedSolution() << "\n\n";
    }
    catch (const std::exception& exception)
    {
        std::cout << exception.what() << "\n\n";
        return -1;
    }

    return 0;
}
