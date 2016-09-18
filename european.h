//
// Created by wjtanner on 9/2/16.
//

#ifndef BLACKSCHOLES_EUROPEAN_H
#define BLACKSCHOLES_EUROPEAN_H
typedef double Riskfreerate;
typedef double Volatility;
typedef double Basisprice;
typedef double Strikeprice;
typedef double Divprice;
typedef double Purchase;
typedef double Expiry;
typedef char Optiontype;

class European {

private:
    Riskfreerate _Rate;
    Volatility _Vola;
    Basisprice _Basis;
    Strikeprice _Strike;
    Divprice _Dividend;
    Purchase _Purchasedate;
    Expiry _Expirydate;
    Optiontype _Type;

public:
    European() = default; // default constructor

    European(Riskfreerate r, Volatility v, Basisprice s, Strikeprice k, Divprice div, Purchase t,
             Expiry T, Optiontype cp) : _Rate(r), _Vola(v), _Basis(s), _Strike(k), _Dividend(div),
            _Purchasedate(t), _Expirydate(T), _Type(cp) {};

    European operator+(const European& rhs);
    European operator-(const European& rhs)
    {
        European temp;
        temp = temp - rhs;

        return temp;
    }
    // Some methods
    void parameterInfo();
    double cumNormDist(double); // Hart algorithm
    double d1();
    double d2();

    // method for calculating option price
    double optionPrice();

    // methods for varying parameters
    void varyBasisPrice();

};
#endif //BLACKSCHOLES_EUROPEAN_H
