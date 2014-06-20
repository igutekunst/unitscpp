*What it is and why you might want to use it*

    The package contains a python script that helps you generate C++
    types that can be used as numbers with physical units.  To do this,
    you edit a configuration text file that defines the units you want
    to use and run the *unitscpp.py* script that uses this configuration
    file to generate a C++ include file.  Your C++ project then
    includes this include file.

*Features and benefits*:  unitscpp 

  * Is easy to use.
  * Results in readable code.
  * Is easy to change to fit your needs.
  * Lets you work in your problem domain, not the library's.
  * Should work with virtually any C++ compiler that supports templates.

----

*Update 20 Jun 2014*:  The library has been tested using python 2.7.6
and 3.4.0 on a Linux system with the GNU 4.8.2 g++ compiler.  The old
packaging method was in a zip file in the Downloads area; this has
been deprecated and you now get the package from the Mercurial
repository.

Using the repository is actually quite simple, so don't be intimidated
by it.  First, you need to install Mercurial on your system.  For a
typical Linux system, this requires a command such as 

`apt-get install Mercurial`

(it will be a similar command for other UNIX-style systems).  For
Windows, you'll need to download the MSI file, then right click on it
in Explorer and select *Install* (you may also need to adjust your
path to allow it to be seen in a DOS console).  

Once you have Mercurial working (type `hg help` and you should see a
useful help message), you then cd to the directory where you want to
look at unitscpp's files and type

`hg clone https://someonesdad1@code.google.com/p/unitscpp/`

Then cd to the unitscpp directory and start working.  If you also
install git and Subversion, you should be able to get any project's
source code on Google code.

----

The library is based on the insight of Barton and Nackman in
"Scientific and Engineering C++" (1994) of using templates for units
to provide type-safe calculation with physical units.  A
statically-typed language like C++ lets you use the compiler to help
you ensure your calculations with physical units are done correctly.  

Here's a short example that illustrates the use of the library.

Suppose we wish to work with the velocities of glaciers.  We write the
following configuration file (I've left some bookkeeping cruft off to
help you see the essentials; you can see the details in the project's
example file glacier.cfg):

{{{
Unit = Length
Unit = Time

DerivedUnit = Velocity = Length/Time

Constant = const Length m = 1;
Constant = const Time s = 1;

Constant = const Length ft = 0.3048*m;
Constant = const Length mile = 5280*ft;

Constant = const Time minute = 60*s;
Constant = const Time hr = 3600*s;
Constant = const Time day = 24*3600*s;
Constant = const Time year = 365.25*3600*s;
}}}

We run the `unitscpp.py` script on this configuration file and get a
resulting `glacier.h` include file.  Then we write our application:

{{{
#include <iostream>
#include "glacier.h"

using namespace std;
using namespace units;

int main()
{
    const Length dist = 50*ft;
    const Time time = 1*day;
    Velocity v = dist/time;

    cout << "Glacier speed calculation:" << endl
         << "  Length of movement = " << dist.to(ft) << " ft" << endl
         << "  Time of movement   = " << time.to(day) << " day" <<
endl
         << "  Speed of movement  = " << v << " m/s" << endl
         << "                     = " << v.to(mile/year) 
         << " miles/year" << endl
         << endl
         << "  Velocity dimensions are " << v.dim() << endl;

    return 0;
}
}}}

When compiled and run, this produces the output

{{{
Glacier speed calculation:
  Length of movement = 50 ft
  Time of movement   = 1 day
  Speed of movement  = 0.000176389 m/s
                     = 0.144117 miles/year

  Velocity dimensions are <1,-1>
}}}

The output should be understandable, except perhaps for the last line.
The dimensions of velocity are indicated in powers of the fundamental
units; in this case, they are length and time.  Thus, the dimensions
are L*T^-1^.

While I defined the base units to be m for length and s for time in
the configuration file, there's no fundamental reason they have to be
SI units.  If we wanted to work in feet and days as our basic physical
units, we would have defined those to be unit lengths.  Then if we
wished to e.g. convert a length to meters, we'd have to provide an
appropriate conversion constant in the configuration file such as

{{{
Constant = const Length m = ft/0.3048;
}}}

This demonstrates that the unitscpp library lets you work with
whatever units you choose that are relevant for your problem at hand.
Personally, I prefer this approach over the heavyweight libraries that
try to define all the common units used in technical problems, as this
leads to big files and forces you to use the library's naming
conventions.
