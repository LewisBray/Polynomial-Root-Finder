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
    Complex num{ 0, 0 };
    std::cout << num << std::endl;

    std::cout << "This application finds the roots of quadratic equations of\n"
        << "the form f(x) = ax^2 + bx + c.  Enter your coefficients.\n"
        << std::endl;

    const auto [a, b, c] = getCoeffsFromUser();

    // Equation pointer can point to inherited object
	std::unique_ptr<Equation> equation;
    if (a != 0)
        equation = std::make_unique<Quadratic>(a, b, c);
	else
	    equation = std::make_unique<Linear>(b, c);
	
	std::cout << equation->formattedSolution() << "\n\n\n";

    return 0;
}
