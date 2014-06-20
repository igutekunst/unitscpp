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
