#include "polynomials.h"

#include <iostream>
#include <sstream>

static std::string formatCoeff(const double n)
{
    std::stringstream coeff;
    coeff << ' ' << ((n > 0.0) ? '+' : '-') << ' ';

    if (const double absN = std::abs(n); absN != 1.0)
        coeff << absN;

    return coeff.str();
}

static std::string formatLeadCoeff(const double n)
{
    std::stringstream leadCoeff;

    if (n < 0.0)
        leadCoeff << '-';

    if (const double absN = std::abs(n); absN != 1.0)
        leadCoeff << absN;

    return leadCoeff.str();
}

static std::string formatConstTerm(const double n)
{
    std::stringstream constTerm;
    constTerm << ' ' << ((n > 0.0) ? '+' : '-') << ' ' << std::abs(n);

    return constTerm.str();
}

static std::string formatComplexNumber(const std::complex<double>& z)
{
    std::stringstream complexNumber;

    if (z.real() != 0.0) {
        complexNumber << z.real();
        if (z.imag() != 0.0)
            complexNumber << formatCoeff(z.imag()) << 'i';
    }
    else {
        if (z.imag() != 0.0)
            complexNumber << formatLeadCoeff(z.imag()) << 'i';
        else
            complexNumber << 0;
    }

    return complexNumber.str();
}


Linear::Linear(const double m, const double c) noexcept
    : m_{ m }
    , c_{ c }
    , root_{ (-c / m != 0.0) ? -c / m : 0.0 }
{}

std::string Linear::formattedSolution() const
{
    std::stringstream solution;
    solution << "f(x) = ";

    if (m_ != 0.0)
    {
        solution << formatLeadCoeff(m_) << 'x';

        if (c_ != 0.0)
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
    , det_{ b * b - 4 * a * c }
{
	findRoots();	                // Sets root1 and root2
}

std::string Quadratic::formattedSolution() const
{
    std::stringstream solution;
    solution << "f(x) = " << formatLeadCoeff(a_) << "x^2";

    if (b_ != 0.0)
        solution << formatCoeff(b_) << 'x';

    if (c_ != 0.0)
        solution << formatConstTerm(c_);

    solution << " has two ";

    if (det_ > 0.0)
    {
        solution << "distinct real roots "
            << formatComplexNumber(root1_)
            << " and " << formatComplexNumber(root2_);
    }
    else if (det_ == 0.0)
    {
        solution << "equal real roots "
            << formatComplexNumber(root1_);
    }
    else
    {
        solution << "complex roots "
            << formatComplexNumber(root1_)
            << " and " << formatComplexNumber(root2_);
    }

    return solution.str();
}

void Quadratic::findRoots() noexcept
{
	if (det_ >= 0.0)
	{
		const double root = (-b_ - sqrt(det_)) / (2 * a_);
        root2_ = { (root != 0.0) ? root : 0.0, 0.0 };   // Avoid -0 issues

		if (det_ != 0.0) {
			// we construct second root from previous
			// by adding 2*(sqrt(det)/(2a)) = sqrt(det)/a
			const double conjugate = root + sqrt(det_) / a_;
            root1_ = { (conjugate != 0.0) ? conjugate : 0.0, 0.0 };
		}
		else
			root1_ = root2_;    // Roots are equal if det == 0
	}
	else    // root2 is complex conjugate of root1
	{
        // If det < 0 then (-b + sqrt(det))/2a = -b/2a + i*sqrt(-det)/2a
        const double real = (-b_ / (2 * a_) != 0) ? -b_ / (2 * a_) : 0.0;
        const double imag = sqrt(-det_) / (2 * a_);

        root1_ = { real, imag };
		root2_ = std::conj(root1_);
	}
}
