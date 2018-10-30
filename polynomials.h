#ifndef __POLYNOMIALS_H__
#define __POLYNOMIALS_H__

#include <ostream>
#include <string>

// Struct for holding and displaying complex numbers.
struct Complex
{
    double re_;     // Real part
    double im_;     // Imaginary part
};

std::ostream& operator<<(std::ostream& out, const Complex& complex);


// Virtual base class that types of polynomial equations inherit from.
class Equation
{
public:
    virtual std::string formattedSolution() const = 0;
};


// Class that handles linear (or constant) equations.
class Linear : public Equation
{
public:
	Linear(const double grad, const double intercept);

    std::string formattedSolution() const;

private:
	double m_;	    // Gradient
	double c_;	    // y-intercept
	double root_;   // Solution
};


// Class that handles quadratic equations.
class Quadratic : public Equation
{
public:
	Quadratic(const double c1, const double c2, const double c3);

    std::string formattedSolution() const;

private:
    double a_;          // x^2 coefficent
	double b_;		    // x coefficient
	double c_;		    // y-intercept
	double det_;		// determinant (b^2 - 4ac)
	Complex root1_;	    // 2 roots (could be complex)
	Complex root2_;

	void findRoots();
};

#endif
