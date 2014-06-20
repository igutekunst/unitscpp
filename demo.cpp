#include <iostream>
#include <vector>
#include <valarray>
#include <iomanip>
#include <cmath>
#include <cassert>
#include "units.h"
using namespace std;
using namespace units;

int main()
{
    const int significant_digits = 4;

    cout << "Calculations shown to " << significant_digits 
         << setprecision(significant_digits)
         << " significant digits." << endl 
         << endl;

    // Show dimensions of a derived unit
    const int v = 800;
    const int duration = 4;
    Length x = v*mm;
    Time t(duration*s);
    cout << "Dimensions:" << endl
         << "  lengths are " << x.dim() << endl
         << "  times are " << t.dim() << endl
         << "  lengths/times are " << (x/t).dim() << endl 
         << "  force is " << N.dim() << endl 
         << "  force/area is " << (N/(m*m)).dim() << endl 
         << "  pressure is   " << psi.dim() << endl 
         << endl;

    // Show conversions work
    cout << "Conversions:" << endl
         << "  In SI, " << x.to(mm) << " mm in " << t << " s is " 
         << x/t << " m/s or " << (x/t).to(mm/s) << " mm/s" << endl
         << "  1 inch = " << in << " m" << endl;
    x = 1234*cm;
    cout << "  x/s is " << x/s << " m/s or " << (x/s).to(mi/hr)
         << " mph" << endl 
         << endl;

    // Show we can call an external function
    Length diameter = 2.36*in;
    Area CircleArea(const Length & diameter);
    Area A = CircleArea(diameter);
    cout << "Demonstrate that we can call a function in another file:" << endl
         << "  Area of " << diameter.to(mm) << " mm circle = "
         << diameter.to(in) << " inches circle = "
         << A.to(mm*mm) << " mm^2 = "
         << A.to(in*in) << " in^2" << endl
         << endl;

    // How to use in a standard math function
    cout << "Standard math:  sqrt(" << x << ") = " << sqrt(x()) << endl 
         << endl;

    // Boolean comparisons
    Length y = x.to(cm)*cm;
    cout << "Boolean comparisons:" << endl
         << "  x == y is " << (x == y) << endl
         << "  x > y is " << (x > y) << endl
         << "  x < y is " << (x < y) << endl;

    // Demonstrate two UNIT objects can be added
    cout << "Units can be added:  1 inch + 1 inch = " 
         << (in + in).to(in) << " inches" << endl << endl;

    // Density example and a more complex conversion
    double sp_gr_of_brass = 8.5;
    Density d = sp_gr_of_brass*g/(cm*cm*cm);
    cout << "Density of brass is " << d.to(g/(cm*cm*cm)) << " g/cc" << endl
         << "  or " << d.to(lb/(in*in*in)) << " lb/in^3" << endl
         << "  or " << d << " kg/m^3" << endl << endl;

    // Typical calculation:  Barlow's formula.  For a thin-walled
    // cylinder, Barlow's formula gives the wall thickness required to
    // withstand a stated pressure given a specified strength.  The
    // formula is 
    //      t = p*D/(2*(S + p))
    // where
    //      t = wall thickness in inches
    //      p = pressure in psi
    //      D = outside diameter in inches
    //      S = allowed stress in psi
    // We want a 304 stainless steel pipe to handle a 500 psi working
    // pressure at a stress of one half the yield strength of 30 kpsi.
    //
    // This is 
    // 500/(2*(15000+500)) = 500/31000 = 5/310 ~ 5/300 = 1/60 = 0.016.

    {
        Length D = 1*inch;
        Pressure p = 500*psi;
        Stress S = 15*kpsi;
        Length t = p*D/(2*(S + p));
        cout << "304 SST pipe wall thickness = " << t.to(in) 
             << " inches" << endl;
        // Show we get the same results by calculating with metric
        // dimensions.  Conversions gotten from the GNU units program.
        D = 25.4*mm;
        p = 3447378.6*Pa;
        S = 1.0342136e+08*Pa;
        t = p*D/(2*(S + p));
        cout << "  Starting with metric, got   " 
             << t.to(in) << " inches" << endl
             << "  Expected " << 5/310. << " inches" << endl << endl;
    }

    // Here's a calculation that shows you still have to be careful
    // with equations that are not in SI.  This also applies to any
    // equation that is not dimensionally correct, as the following
    // empirical equation is.  Formula from page 2243 of Machinery's
    // Handbook, 19th ed.  The
    //
    // Waterflow in a pipe.  A 1 mile long pipe with an inside
    // diameter of 12 inches discharges water under a head of 100
    // feet.  What is the velocity and rate of discharge?
    //
    // The formula for approximate mean velocity in ft/s is
    //      v = C*sqrt(h*D/(L + 54*D))
    // where
    //      C = dimensionless constant, about 48 (from table)
    //      h = head pressure in feet of water (= 0.4335275 psi)
    //      D = inside diameter of pipe in feet
    //      L = length of pipe in feet
    //
    // The flow rate will be the velocity multiplied by the
    // cross-sectional area.
    {
        const int C = 48;
        Length D = 1*ft;
        Length L = 1*mile;
        Pressure h = 100;
        // Note the deliberate conversion to ft/s.
        Velocity v = C*sqrt((h*D/(L + 54*D))())*ft/s;
        const double pi = M_PI;
        Area A = pi*D*D/4;
        VolumeFlow flow = v*A;
        cout << "Pipe flow:" << endl
             << "  Velocity = " << v << " m/s = " << v.to(ft/s)
             << " ft/s" << endl
             << "  Flow = " << flow << " m^3/s = "
             << flow.to(ft*ft*ft/s) << " ft^3/s = "
             << flow.to(gal/minute) << " gal/min" << endl
             << "  Expected flow of 5.16 ft^3/s" << endl << endl;
    }

    // Show that our numbers with units can be put in an STL
    // container.
    typedef vector<Length> aLength;
    typedef vector<Length>::const_iterator aLengthIterator;
    aLength lengths;
    lengths.push_back(1*m);
    lengths.push_back(2.0*m);
    lengths.push_back(3.14*m);
    cout << "Contents of STL vector:" << endl;
    for (aLengthIterator i=lengths.begin(); i != lengths.end(); ++i)
        cout << "  " << *i << " " << (*i).dim() << endl;
    cout << endl;

    // Show the same for valarrays
    typedef valarray<Mass> vaMass;
    const int n = 3;
    vaMass mass(n);
    mass[0] = 10*kg;
    mass[1] = 20.0*kg;
    mass[2] = 31.4*kg;
    cout << "Valarray contents:" << endl;
    for (int i=0; i < n; ++i)
        cout << "  " << mass[i] << " " << mass[i].dim() << endl;
    cout << endl;

    cout << "Size of a Length = " << sizeof(x) << endl;
    cout << "Size of a double = " << sizeof(float) << endl;
    return 0;
}
