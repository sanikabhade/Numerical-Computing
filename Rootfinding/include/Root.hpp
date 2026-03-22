#ifndef ROOT_HPP
#define ROOT_HPP

class RootFinder {
protected:
    double tol;

public:
    RootFinder(double tolerance);
    double f(double x);
    virtual double solve() = 0;
    virtual ~RootFinder() {}
};

class Bisection : public RootFinder {
private:
    double a, b;

public:
    Bisection(double tolerance);
    bool findInterval();
    double solve() override;
};

class NewtonRaphson : public RootFinder {
public:
    NewtonRaphson(double tolerance);
    double df(double x);
    double solve() override;
};

class FixedPoint : public RootFinder {
public:
    FixedPoint(double tolerance);
    double g(double x);
    double solve() override;
};

#endif