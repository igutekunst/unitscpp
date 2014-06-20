#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include "test_units.h"
using namespace units;
using namespace std;

const NT eps = 1e-15;

// Values for comparison and ordering
const NT n1 = 1;
const NT n2 = 2;
const NT n3 = 3;
const NT n4 = n3;
const Length x1 = n1*m;
const Length x2 = n2*m;
const Length x3 = n3*m;
const Length x4 = n3*m;

void TestWillNotCompile(void)
{
#ifdef WILLNOTCOMPILE
    Length x = 5*m*m;  // Dimensionally inconsistent
#endif
}

void TestClassMembers(void)
{
    // operator()
    assert(x1() == n1);
    // dim
    stringstream s;
    s << x1.dim();
    string t = "<0,1,0,0>";
    assert(t == s.str());
    // to
    assert(fabs(x1.to(mm) - 1000) < eps);
}

void TestArithmetic(void)
{
    Length answer;
    Area answer1;
    One dimensionless;

    // U + U
    answer = x1 + x2; assert(answer == (n1 + n2));
    // U - U
    answer = x1 - x2; assert(answer == (n1 - n2));
    // U * U
    answer1 = x1 * x2; assert(answer1 == (n1 * n2));
    // U / U
    dimensionless = x1 / x2; assert(dimensionless == (n1 / n2));

    // U + NT and U - NT won't compile

    // U * NT
    answer = x1 * n2; assert(answer1 == (n1 * n2));
    // U / NT
    answer = x1 / n2; assert(dimensionless == (n1 / n2));

    // NT * U
    answer = n1 * x2; assert(answer1 == (n1 * n2));
    // NT / U
    {
        Wavenumber answer = n1 / x2; 
        assert(answer == (n1 / n2));
    }

    // U += NT
    answer = x1; answer += n2; assert(answer == (n1 + n2));
    // U -= NT
    answer = x1; answer -= n2; assert(answer == (n1 - n2));
    // U *= NT
    answer = x1; answer *= n2; assert(answer == (n1 * n2));
    // U /= NT
    answer = x1; answer /= n2; assert(answer == (n1 / n2));

    // U += U
    answer = x1; answer += x2; assert(answer == (n1 + n2));
    // U -= U
    answer = x1; answer -= x2; assert(answer == (n1 - n2));
    // Note U *= U and U /= U don't make sense
}

void TestOrdering(void)
{
    // U > U
    assert(x2 > x1);
    assert(not(x1 > x2));
    // U < U
    assert(x1 < x2);
    assert(not(x2 < x1));
    // U >= U
    assert(x2 >= x1);
    assert(not(x1 >= x2));
    assert(x4 >= x3);
    assert(not(x1 >= x2));
    // U <= U
    assert(x1 <= x2);
    assert(not(x2 <= x1));
    assert(x3 <= x4);
    assert(not(x3 <= x2));

    // U > NT
    assert(x2 > n1);
    assert(not(x1 > n2));
    // U < NT
    assert(x1 < n2);
    assert(not(x2 < n1));
    // U >= NT
    assert(x2 >= n1);
    assert(not(x1 >= n2));
    assert(x4 >= n3);
    assert(not(x1 >= n2));
    // U <= NT
    assert(x1 <= n2);
    assert(not(x2 <= n1));
    assert(x3 <= n4);
    assert(not(x3 <= n2));

    // NT > U
    assert(n2 > x1);
    assert(not(n1 > x2));
    // NT < U
    assert(n1 < x2);
    assert(not(n2 < x1));
    // NT >= U
    assert(n2 >= x1);
    assert(not(n1 >= x2));
    assert(n4 >= x3);
    assert(not(n1 >= x2));
    // NT <= U
    assert(n1 <= x2);
    assert(not(n2 <= x1));
    assert(n3 <= x4);
    assert(not(n3 <= x2));
}

void TestComparisons(void)
{
    // U == U
    assert(x3 == x4);
    assert(not(x2 == x4));
    // U != U
    assert(x2 != x4);
    assert(not(x3 != x4));
    // U == NT
    assert(x3 == n4);
    assert(not(x2 == n4));
    // U != NT
    assert(x2 != n4);
    assert(not(x3 != n4));
    // NT == U
    assert(n3 == x4);
    assert(not(n2 == x4));
    // NT != U
    assert(n2 != x4);
    assert(not(n3 != x4));
}

void TestHeader()
{
    // If this compiles, the header insertion of text was successful.
    double x = sin(0.2);
    double y = x*x; 
    x = y;          // Quiets compiler warning
}

void TestTrailer()
{
    // If this compiles, the trailer insertion of text was successful.
    if (trailer_test == 0 or trailer_test != 0)
        ; // Do nothing.
}

int main()
{
    TestWillNotCompile();
    TestClassMembers();
    TestArithmetic();
    TestOrdering();
    TestComparisons();
    cout << "test_units.cpp:  tests passed" << endl;
    return 0;
}
