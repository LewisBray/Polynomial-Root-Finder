
// Struct for holding and displaying complex numbers.
struct complex
{
	void Display() const;

    double re;      // Real part
    double im;		// Imaginary part
};


// Class that types of polynomial equations inherit from.
/*
This supplies methods for displaying solutions as well as helper
functions for specific subclass implementations of the DisplaySln method.
*/
class equation
{
public:
	virtual void DisplaySln() const = 0;

protected:
	void DisplayLeadCoeff(const double n) const;
	void DisplayCoeff(const double n) const;
	void DisplayConst(const double n) const;
};


// Class that handles linear (or constant) equations.
class linear : public equation
{
public:
	linear(const double& grad, const double& intercept);

	void DisplaySln() const;

private:
	double m;		// Gradient
	double c;		// y-intercept
	double root;	// Solution
};


// Class that handles quadratic equations.
class quadratic : public equation
{
public:
	quadratic(const double& c1, const double& c2, const double& c3);

	void DisplaySln() const;

private:
	double a;		    // x^2 coefficent
	double b;		    // x coefficient
	double c;		    // y-intercept
	double det;		    // determinant (b^2 - 4ac)
	complex root1;	    // 2 roots (could be complex)
	complex root2;

	void FindRoots();
};
