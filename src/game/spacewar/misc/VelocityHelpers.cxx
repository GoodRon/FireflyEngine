#include "VelocityHelpers.h"

#include <cmath>

namespace spacewar {

constexpr double pi = 3.14159265358979323846;
constexpr double degreesToRad = pi / 180.0;
constexpr double radToDegrees = 180.0 / pi;
constexpr double epsilon = 0.0001;

double normalizeAngle(double degrees) {
	if (fabs(degrees) > 360.0) {
		degrees = fmod(degrees, 360.0);
	}

	if (degrees < 0.0) {
		degrees += 360.0;
	}
	return degrees;
}

void movePoint(double& x, double& y, 
	double distance, double direction) {

	const double rad = direction * degreesToRad;
	const double deltaX = distance * sin(rad);
	const double deltaY = -distance * cos(rad);

	x += deltaX;
	y += deltaY;
}

void calculateVector(
	double magnitudeX, double magnitudeY,
	double& magnitude, double& direction) {

	magnitude = sqrt(magnitudeX * magnitudeX + magnitudeY * magnitudeY);

	double directionRad = asin(magnitudeX / magnitude);
	if (magnitudeY > 0.0) {
		directionRad = pi - directionRad;
	}

	direction = (normalizeAngle(directionRad * radToDegrees));
}

void addVector(double& magnitude, double& direction,
	double& magnitudeX, double magnitudeY,
	double deltaMagnitude, double deltaDirection) {

	deltaDirection = (normalizeAngle(deltaDirection));

	const double deltaMagnitudeRad = deltaDirection * degreesToRad;
	const double deltaMagnitudeX = deltaMagnitude * sin(deltaMagnitudeRad);
	const double deltaMagnitudeY = -deltaMagnitude * cos(deltaMagnitudeRad);

	magnitudeX += deltaMagnitudeX;
	magnitudeY += deltaMagnitudeY;

	calculateVector(magnitudeX, magnitudeY, 
		magnitude, direction);
}

void projectVector(double magnitude, double direction,
	double& magnitudeX, double& magnitudeY) {

	const double magnitudeRad = direction * degreesToRad;
	magnitudeX = magnitude * sin(magnitudeRad);
	magnitudeY = -magnitude * cos(magnitudeRad);
}

void limitMagnitude(double& magnitude, double& direction,
	double& magnitudeX, double& magnitudeY, double maxMagnitude) {

	if (maxMagnitude < epsilon) {
		return;
	}

	if (magnitude > maxMagnitude) {
		magnitude = maxMagnitude;
		projectVector(magnitude, direction,
			magnitudeX, magnitudeY);
	}
}

}
