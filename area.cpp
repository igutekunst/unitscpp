#include <cmath>
#include "units.h"
using namespace units;

Area CircleArea(const Length & diameter)
{
    return M_PI*diameter*diameter/4;
}
