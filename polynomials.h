#ifndef __POLYNOMIALS_H__
#define __POLYNOMIALS_H__

#include <complex>
#include <string>

// Virtual base class that types of polynomial equations inherit from.
class Equation
{
public:
    virtual ~Equation() {}

    virtual std::string formattedSolution() const = 0;
};

// Class that handles linear (or constant) equations.
class Linear final : public Equation
{
public:
	Linear(double m, double c) noexcept;

    std::string formattedSolution() const override;

private:
	double m_;	    // Gradient
	double c_;	    // y-intercept
	double root_;   // Solution
};

// Class that handles quadratic equations.
class Quadratic final : public Equation
{
public:
	Quadratic(double a, double b, double c) noexcept;

    std::string formattedSolution() const override;

private:
    double a_;                      // x^2 coefficent
	double b_;		                // x coefficient
	double c_;		                // y-intercept
	double det_;		            // determinant (b^2 - 4ac)
    std::complex<double> root1_;    // 2 roots (could be complex)
    std::complex<double> root2_;

	void findRoots() noexcept;
};

#endif
