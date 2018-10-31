#include "polynomials.h"

#include <iostream>
#include <sstream>
#include <cmath>

static std::string formatCoeff(const double n)
{
    std::stringstream coeff;
    coeff << ' ' << ((n > 0) ? '+' : '-') << ' ';

    if (const double absN = std::abs(n); absN != 1.0)
        coeff << absN;

    return coeff.str();
}

static std::string formatLeadCoeff(const double n)
{
    std::stringstream leadCoeff;

    if (n < 0)
        leadCoeff << '-';

    if (const double absN = std::abs(n); absN != 1.0)
        leadCoeff << absN;

    return leadCoeff.str();
}

static std::string formatConstTerm(const double n)
{
    std::stringstream constTerm;
    constTerm << ' ' << ((n > 0) ? '+' : '-') << ' ' << std::abs(n);

    return constTerm.str();
}


std::ostream& operator<<(std::ostream& out, const Complex& complex)
{
    if (complex.re_ != 0) {
        out << complex.re_;
        if (complex.im_ != 0)
            out << formatCoeff(complex.im_) << 'i';
    }
    else {
        if (complex.im_ != 0)
            out << formatLeadCoeff(complex.im_) << 'i';
        else
            out << 0;
    }

    return out;
}


Linear::Linear(const double m, const double c) noexcept
    : m_{ m }
    , c_{ c }
{
	root_ = (-c_ / m_ != 0.0) ? -c_ / m_ : 0;
}

std::string Linear::formattedSolution() const
{
    std::stringstream solution;
    solution << "f(x) = ";

    if (m_ != 0)
    {
        solution << formatLeadCoeff(m_) << 'x';

        if (c_ != 0)
            solution << formatConstTerm(c_);

        solution << " has one real solution " << root_;
    }
    else
        solution << c_ << " has no roots";

    return solution.str();
}


Quadratic::Quadratic(const double a, const double b, const double c) noexcept
    : a_{ a }
    , b_{ b }
    , c_{ c }
{
	det_ = b_ * b_ - 4 * a_ * c_;   // Set det before calling FindRoots
	findRoots();	                // Sets root1 and root2
}

std::string Quadratic::formattedSolution() const
{
    std::stringstream solution;
    solution << "f(x) = " << formatLeadCoeff(a_) << "x^2";

    if (b_ != 0)
        solution << formatCoeff(b_) << 'x';

    if (c_ != 0)
        solution << formatConstTerm(c_);

    solution << " has two ";

    if (det_ > 0)
        solution << "distinct real roots " << root1_ << " and " << root2_;
    else if (det_ == 0)
        solution << "equal real roots " << root1_;
    else
        solution << "complex roots " << root1_ << " and " << root2_;

    return solution.str();
}

void Quadratic::findRoots() noexcept
{
	if (det_ >= 0)
	{
		const double root = (-b_ - sqrt(det_)) / (2 * a_);
        root2_.re_ = (root != 0) ? root : 0;    // Avoid -0 issues

		if (det_ != 0) {
			// we construct second root from previous
			// by adding 2*(sqrt(det)/(2a)) = sqrt(det)/a
			const double conjugate = root + sqrt(det_) / a_;
			root1_.re_ = (conjugate != 0) ? conjugate : 0;
		}
		else
			root1_.re_ = root2_.re_;            // Roots are equal if det == 0
		
		root1_.im_ = 0;				            // Imaginary parts are zero
		root2_.im_ = 0;
	}
	else
	{
		// If det < 0 then (-b + sqrt(det))/2a = -b/2a + i*sqrt(-det)/2a
		root1_.re_ = (-b_ / (2 * a_) != 0) ? -b_ / (2 * a_) : 0;
		root1_.im_ = sqrt(-det_) / (2 * a_);    // Make determinant positive
		root2_.re_ = root1_.re_;
		root2_.im_ = (-1) * root1_.im_;			// root2 is complex conjugate of root1
	}
}
