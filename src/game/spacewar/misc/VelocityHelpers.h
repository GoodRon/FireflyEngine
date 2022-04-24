/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_MISC_VELOCITY_HELPERS_H
#define SW_MISC_VELOCITY_HELPERS_H

namespace spacewar {

double normalizeAngle(double degrees);

void movePoint(double& x, double& y, 
	double distance, double direction);

void addVector(double& magnitude, double& direction,
	double& magnitudeX, double magnitudeY,
	double deltaMagnitude, double deltaAirection);

void calculateVector(
	double magnitudeX, double magnitudeY,
	double& magnitude, double& direction);

void projectVector(double magnitude, double direction,
	double& magnitudeX, double& magnitudeY);

void limitMagnitude(double& magnitude, double& direction,
	double& magnitudeX, double& magnitudeY, double maxMagnitude);

}

#endif // SW_MISC_VELOCITY_HELPERS_H
