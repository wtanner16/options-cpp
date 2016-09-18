//
// Created by wjtanner on 9/2/16.
//

#include "european.h"
#include <cmath>
#include <vector>
using std::vector;

#include <iostream>
#include <tgmath.h>

using std::cin;
using std::cout;
using std::endl;

void European::parameterInfo() {

    /*
     * prints out the option parameters
     * Riskfreerate _Rate;
    Volatility _Vola;
    Basisprice _Basis;
    Strikeprice _Strike;
    Divprice _Dividend;
    Purchase _Purchasedate;
    Expiry _Expirydate;
    Optiontype _Type;
     */

    cout << "risk free rate: " << _Rate << endl;
    cout << "volatility: " << _Vola << endl;
    cout << "basis price: " << _Basis << endl;
    cout << "strike price: " << _Strike << endl;
    cout << "dividend: " << _Dividend << endl;
   // cout << "purchase date: " << _Purchasedate << endl;
    cout << "expiry date: " << _Expirydate << endl;
    cout << "time to expiry: " << _Expirydate - _Purchasedate << " years" << endl;
    if (_Type == 'c')
        cout << "option type: european call" << endl;
    else if
            (_Type == 'p')
        cout << "option type: european put" << endl;
    cout << "option price: " << optionPrice() << endl;

}

double European::cumNormDist(double x) // uses Hart algorithm for double precision... see Haug, p.466
{

    double return_val;
    double y = std::fabs(x);
    const long double d = 7.07106781186547;
    const long double k = 2.506628274631;

    // array "a" of constants
    long double a[7] =
            {
                    0.0352624965998911,
                    0.700383064443688,
                    6.37396220353165,
                    33.912866078383,
                    112.079291497871,
                    221.2135961699931,
                    220.206867912376
            };

    // array "b" of constants
    long double b[8] =
            {
                    0.0883883476483184,
                    1.75566716318264,
                    16.064177579207,
                    86.7807322029461,
                    296.564248779674,
                    637.333633378831,
                    793.826512519948,
                    440.413735824752
            };

    double A = ((((((a[0]*y + a[1])*y + a[2])*y + a[3])*y+a[4])*y+a[5])*y + a[6]);

    double B = (((((((b[0]*y + b[1])*y + b[2])*y + b[3])*y+b[4])*y+b[5])*y + b[6])*y + b[7]);

    double C = y + 1/(y + 2/(y + 3/(y + 4/(y + 0.65))));


    // return scenarios

    if (y < d)
        return_val = std::exp(-0.5*y*y)*A/B;

    if ( y >= d)
        return_val = std::exp(-0.5*y*y) / (k * C);

    if (y > 37)
        return_val = 0;

    if (x < 0)
        return return_val;

    return 1 - return_val;

};

double European::d1() {
    double A = std::log(_Basis/_Strike) + (_Rate + 0.5 *_Vola * _Vola) * (_Expirydate - _Purchasedate);
    double B = _Vola * std::sqrt(_Expirydate - _Purchasedate);

    return A / B;
}

double European::d2() {

    return d1() - _Vola * std::sqrt(_Expirydate - _Purchasedate);
}

double European::optionPrice() {
    double dT = _Expirydate - _Purchasedate;
    double callprice = _Basis * cumNormDist(d1()) - _Strike * std::exp(-_Rate * dT) * cumNormDist(d2());
    double putprice = _Strike * std::exp(-_Rate * dT) * cumNormDist(-d2()) - _Basis * cumNormDist(-d1());

    if (_Type == 'c')
        return callprice;

    return putprice;

}

void European::varyBasisPrice() {

    vector<double> S;
    double dS = 1.5 / _Basis;

    for (double s = 0; s < _Basis; s += dS)
    {
        cout << s << endl;
    }


}

