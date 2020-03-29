// MovingQuadReg.h
// Authors: Ian Heidenberger, Jamie Smith
//
// MovingQuadReg calculates an n-deep sliding quadratic regression.

#pragma once

#include <deque>
#include <stddef.h>

class MovingQuadReg {

	std::deque<float> tvals, yvals;
	float A = 0, B = 0, C = 0, t_sum = 0, y_sum = 0, RSQ = 0;

	// maximum size of the regression
	const size_t maxSize;

public:

	/**
	 * Construct a regression that holds up to the given number of elements.
	 * @param maxSize
	 */
	MovingQuadReg(size_t maxSize);

	~MovingQuadReg() = default;

	/**
	 * Add a new point to the regression.  Note that this does NOT
	 * update the results, you have to call update() for that.
	 *
	 * If maxSize points have already been added to the regression,
	 * the oldest point will be deleted.
	 * @param t
	 * @param y
	 */
	void addPoint(float t, float y);

	/**
	 * Calculate the regression constants based on the current data.
	 * Since a parabola has to be constrained by at least 3 points,
	 * 3 data points are required before any data can be returned.
	 */
	void update();

	/**
	 * Get the derivative of the regression at the most recently added point,
	 * AKA the slope of the tangent line to the parabola at this point.
	 *
	 * Note that derivative is calculated from the regression parabola,
	 * NOT the actual data.
	 */
	float getDerivative();

	/**
	 * Get the R squared value, a measure of how close the regression
	 * fits the data.  Also called the coefficient of determination.
	 *
	 * Range 1.0 (best confidence) to std::numeric_limits<float>::min() (lowest confidence).
	 * @return
	 */
	float getRSQ();

	// These functions give the coefficients for the standard
	// parabola equation, y=ax^2 + bx + c
	float getA();
	float getB();
	float getC();

	/**
	 * Get how many points have currently been added to the regression.
	 * @return
	 */
	size_t getNumPoints() { return tvals.size(); }

	/**
	 * Clear all data points from the regression and reset it back
	 * to how it was when it was constructed.
	 */
	void clear();

};

/**
 * Version of the moving quadratic regression specifically made for regressing
 * GPS altitude and calculating drogue deployment.
 *
 * NOTE: This class should be given points in METERS! NO freedom units allowed.
 * allowed.
 */
class GPSQuadReg : public MovingQuadReg
{
public:
	GPSQuadReg(size_t maxSize);

	/**
	 * Return whether the regression indicates we have reached apogee and
	 * it is time to deploy the parachutes.
	 * @return
	 */
	bool shouldDeploy();

};