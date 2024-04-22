#include <iostream>
#include "utils.hpp"

int main()
{
    double S;
    int n;
    double *w;
    double *r;

    leggifile("data.csv", S, n, w, r);

    double V, rateOfReturn;
    valoreportafoglio(S, n, w, r, V, rateOfReturn);

    stamporisultati(S, n, w, r, V, rateOfReturn);

    delete[] w;
    delete[] r;

    return 0;
}
