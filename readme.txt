Polynomial Root Finder

Used to calculate the roots of quadratic/linear polynomials that have
real-valued coefficients.

This is just a little exercise in inheritance (and polymorphism to some extent),
we have a base class (equation) in which the classes that handle quadratic and
linear/constant equations inherit from.  The base class merely provides methods
for helping to display the equations nicely and has a pure virtual function
"DisplaySln()" that both classes provide an implementation for.

A very simple struct for dealing with complex numbers was made which simply has
two data members for holding the real and imaginary parts along with a method
for displaying a complex number "nicely".  This is needed for dealing with the
situation where our quadratic equation has a negative determinant/complex roots.

I may extend this in the future by adding in support for cubic equations (and
potentially more by long division of equations).  In order to handle the cubic
equation cleanly I would need to extend the complex struct into a class and
provide overloads for the class binary mathematical operators (+, *, etc...) to
make manipulation cleaner (I would need to be able to multiply complex numbers
by scalars, add real numbers to complex numbers, etc...).
