#include "polynomials.h"

#include <iostream>
#include <cmath>

using std::cout;


// Displays a complex number in a "nice" format.
void complex::Display() const
{
	if (re != 0) {
		cout << re;
		printf(" %s ", (im > 0) ? "+" : "-");
	}
    else {
        if (im < 0)		    // We assume im != 0 if this
            cout << "-";    // function is being called
    }

    // If im == 1 or -1 then we don't display im before 'i'
    if (double pos = abs(im); pos != 1.0)
		cout << pos;
	cout << "i";
}


//-- equation class methods --\\ 

// Displays the coefficient of the first term of an equation.
/*
\param  n   Lead coefficent to be displayed (assumed to be non-zero).
*/
void equation::DisplayLeadCoeff(const double n) const
{
	if (n < 0)
		cout << "-";    // No space between '-' and first coefficient
    if (double pos = abs(n); pos != 1.0)
		cout << pos;
}


// Displays coefficient in equation that isn't the first or constant term.
/*
\param  n   The coefficient to be displayed (assumed to be non-zero).
*/
void equation::DisplayCoeff(const double n) const
{
	printf(" %s ", (n > 0) ? "+" : "-");

    if (double pos = abs(n); pos != 1.0)
		cout << pos;
}


// Displays the constant term of an equation.
/*
\param  n   The constant term to be displayed (assumed to be non-zero).
*/
void equation::DisplayConst(const double n) const
{
	printf(" %s %g", (n > 0) ? "+" : "-", abs(n));
}


//-- linear class methods --\\ 

// linear equation class constructor.
/*
\param  grad        Linear equation gradient.
\param  intercept   y-axis intercept.
*/
linear::linear(const double& grad, const double& intercept)
    : m{ grad }
    , c{ intercept }
{
	root = (-c / m != 0.0) ? -c / m : 0;
}


// Displays the solution of a linear equation after construction.
void linear::DisplaySln() const
{
	cout << "f(x) = ";

	if (m != 0)
    {
		DisplayLeadCoeff(m);
		cout << "x";

		if (c != 0)
			DisplayConst(c);

		printf(" has one real solution %g", root);
	}
	else
		printf("%g has no roots", c);
}


//-- quadratic class methods --\\ 

// quadratic equation class constructor.
/*
\param  c1      Quadratic term coefficient (assumed to be non-zero).
\param  c2      Linear term coefficient.
\param  c3      Constant term.
*/
quadratic::quadratic(const double& c1, const double& c2, const double& c3)
    : a(c1)
    , b(c2)
    , c(c3)
{
	det = b * b - 4 * a * c;    // Set det before calling FindRoots
	FindRoots();	            // Sets root1 and root2
}


// Displays the solution of the quadratic equation.
void quadratic::DisplaySln() const
{
	// Print the equation we are dealing with in a nice format
	cout << "f(x) = ";

	DisplayLeadCoeff(a);
	cout << "x^2";

	if (b != 0) {
		DisplayCoeff(b);
		cout << "x";
	}

	if (c != 0)
		DisplayConst(c);

	cout << " has two ";

	// Print the roots in differing formats depending on determinant
	if (det > 0)
		printf("distinct real roots %g and %g", root1.re, root2.re);
	else if (det == 0)
		printf("equal real roots %g", root1.re);
	else {
		cout << "complex roots ";
		root1.Display();
		cout << " and ";
		root2.Display();
	}
}


// Finds and sets the roots of the quadratic equation.
void quadratic::FindRoots()
{
	if (det >= 0)
	{
		double root = (-b - sqrt(det)) / (2 * a);	// First root from formula
		root2.re = (root != 0) ? root : 0;	        // Avoid -0 issues

		if (det != 0) {
			// we construct second root from previous
			// by adding 2*(sqrt(det)/(2a)) = sqrt(det)/a
			double conjugate = root + sqrt(det) / a;
			root1.re = (conjugate != 0) ? conjugate : 0;
		}
		else
			root1.re = root2.re;    // Roots are equal if det == 0
		
		root1.im = 0;				// Imaginary parts are zero
		root2.im = 0;
	}
	else
	{
		// If det < 0 then (-b + sqrt(det))/2a = -b/2a + i*sqrt(-det)/2a
		root1.re = (-b / (2 * a) != 0) ? -b / (2 * a) : 0;
		root1.im = sqrt(-det) / (2 * a);	// Make determinant positive
		root2.re = root1.re;
		root2.im = (-1) * root1.im;			// root2 is complex conjugate of root1
	}
}
