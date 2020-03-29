#include "MovingQuadReg.h"

#include <cstdlib>
#include <cstdio>
#include <iostream>

/**
 * Given an X value get a Y value that roughly follows a parabola
 * @param xValue
 * @return
 */
float genSimulatedValue(float xValue)
{
	// use a simple quadratic equation plus some randomness for the regression
	float quadraticResult = static_cast<float>(.1 * xValue * xValue - 5 * xValue + 5);
	float yValue = static_cast<float>(quadraticResult + .01 * quadraticResult * (rand() - (RAND_MAX / 2)) / (RAND_MAX));
	return yValue;
}


// test copied from Hamster test harness
template<int trialNo, int numPoints>
void testFindEquation()
{
	// use fixed random seed for consistent results
	srand(4639);

	printf("\r\n");
	printf("------------------------------------------------------\r\n");
	printf("Trial %d\r\n", trialNo);

	MovingQuadReg regression(numPoints);
	for(size_t xValue = 0; xValue < numPoints; ++xValue)
	{
		regression.addPoint(xValue, genSimulatedValue(xValue));
		regression.update();
	}

	printf("Regression Equation: %.02fx^2 + %.02fx + %.02f [R^2=%.02f]\r\n", regression.getA(), regression.getB(), regression.getC(), regression.getRSQ());

}

int main(int argc, char** argv)
{
	std::cout << ">> Testing finding a regression equation... " << std::endl;
	testFindEquation<1, 10>();
	testFindEquation<2, 30>();
	testFindEquation<3, 50>();
	testFindEquation<4, 100>();
	testFindEquation<5, 500>();
}