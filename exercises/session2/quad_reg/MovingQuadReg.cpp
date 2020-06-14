// MovingQuadReg.cpp
// Author: Ian Heidenberger
//
// MovingQuadReg calculates an n-deep sliding quadratic regression.

#include "MovingQuadReg.h"

#include <limits>

MovingQuadReg::MovingQuadReg(size_t size):
        maxSize(size)
{

}


void MovingQuadReg::addPoint(float t, float y)
{
    if(tvals.size() == maxSize)
    {
        // remove a point
        t_sum -= tvals.front();
        y_sum -= yvals.front();
        tvals.pop_front();
        yvals.pop_front();
    }

    // add the new point
    t_sum += t;
    y_sum += y;

    tvals.push_back(t);
    yvals.push_back(y);
}

void MovingQuadReg::update()
{

    if(tvals.size() < 3)
    {
        // not enough data to fully constrain a parabola
        return;
    }

    //Calculate our sums matrix and the LSQ vector
    float a = 0.0f,b = 0.0f,c = 0.0f,d = 0.0f,e = 0.0f, z1 = 0.0f,z2 = 0.0f,z3 = 0.0f;
    float point_t = 0.0f, point_y = 0.0f,sq = 0.0f;
    for(size_t j = 0; j<tvals.size(); j++){
        point_t = tvals[j];
        point_y = yvals[j];
        sq = point_t*point_t;
        a += sq*sq;
        b += sq*point_t;
        c += sq;
        d += point_t;
        z1 += sq*point_y;
        z2 += point_t*point_y;
    }
    e = tvals.size();
    z3 = y_sum;
    //Invert the sums matrix
    float M11 = 0.0f,M12 = 0.0f,M13 = 0.0f,M22 = 0.0f,M23 = 0.0f,M33 = 0.0f,k = 0.0f;
    float tmp1 = (a*(c*e-d*d)-b*b*e+2*b*c*d-c*c*c);
    if (tmp1 == 0.0f) return;
    k = 1/tmp1;
    M11 = c*e - d*d;
    M12 = c*d - b*e;
    M13 = b*d - c*c;
    M22 = a*e - c*c;
    M23 = b*c - a*d;
    M33 = a*c - b*b;
    A = k*(M11*z1+M12*z2+M13*z3);
    B = k*(M12*z1+M22*z2+M23*z3);
    C = k*(M13*z1+M23*z2+M33*z3);

    // calculate R squared, AKA coefficient of determination.
    // Info on this can be found here: https://en.wikipedia.org/wiki/Coefficient_of_determination
    float sumSquaredResiduals = 0.0f, sumSquaredTotal = 0.0f, error = 0.0f;
    for(size_t j = 0; j<tvals.size() ;j++){
        point_t = tvals[j];
        point_y = yvals[j];
        error = point_y - (A*point_t*point_t + B*point_t + C);
        sumSquaredResiduals += error*error;
        error = point_y - (y_sum / tvals.size());
        sumSquaredTotal += error*error;
    }
    if (sumSquaredTotal == 0.0f)
    {
        RSQ = std::numeric_limits<float>::min();
    }
    else
    {
        RSQ = 1 - (sumSquaredResiduals/sumSquaredTotal);
    }
}

float MovingQuadReg::getDerivative(){
    return (2*A*tvals.back() + B);
}

float MovingQuadReg::getRSQ(){
    return RSQ;
}

float MovingQuadReg::getA(){
    return A;
}

float MovingQuadReg::getB(){
    return B;
}

float MovingQuadReg::getC(){
    return C;
}

void MovingQuadReg::clear()
{
    // clear data points
    tvals.clear();
    yvals.clear();
    t_sum = 0;
    y_sum = 0;

    // reset constants
    A = 0;
    B = 0;
    C = 0;
    RSQ = 0;
}

GPSQuadReg::GPSQuadReg(size_t maxSize) : MovingQuadReg(maxSize)
{

}

bool GPSQuadReg::shouldDeploy()
{
    // These values determined experimentally through testing on the Deja Vu data
    // using the QuadraticRegret test harness.
    // Conceptually, what we're doing is pretty simple: we just wait until
    // we have a reasonable confidence in our flight path and
    // that flight path shows we're going downward.
    return getRSQ() > 0.8 && getDerivative() < -10;
}
