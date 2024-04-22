#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

void leggifile(const std::string &filename, double &S, int &n, double *&w, double *&r);
void valoreportafoglio(double S, int n, double *w, double *r, double &V, double &rateOfReturn);
void stamporisultati(double S, int n, double *w, double *r, double V, double rateOfReturn);

#endif // UTILS_HPP
