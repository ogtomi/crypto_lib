#ifndef _RSA_H_
#define _RSA_H_

class RSA
{
private:
    double p;
    double q;
    double phi;
    double n;
    double e;
    double d;
    static constexpr double k = 2;

public:
    RSA(double p, double q);
    ~RSA(){};

    double encrypt(double message);
    double decrypt(double message);

private:
    void calculate_n(){n = p * q;};
    void calculate_phi(){phi = (p - 1) * (q - 1);};
    void calculate_d();
    int gcd(int a, int b);
    void choose_e();
};

#endif