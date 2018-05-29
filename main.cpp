#include "polynomials.h"

#include <iostream>
#include <memory>

using std::cout;
using std::cin;


int main()
{
    cout << "This application finds the roots of quadratic equations of\n";
    cout << "the form f(x) = ax^2 + bx + c.  Enter your coefficients.\n\n";

	// Get coefficients from user
	double c1, c2, c3;

    cout << "a: ";
    cin >> c1;
    cout << "b: ";
    cin >> c2;
    cout << "c: ";
    cin >> c3;
    cout << "\n";

    // Equation pointer can point to inherited object
	std::unique_ptr<equation> pEqn;

    if (c1 != 0)
        pEqn = std::make_unique<quadratic>(c1, c2, c3);
	else
	    pEqn = std::make_unique<linear>(c2, c3);
	
	pEqn->DisplaySln();     // Constructor finds roots
	cout << "\n\n\n";

    return 0;
}
