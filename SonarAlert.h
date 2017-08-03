#ifndef SonarAlert_H
#define SonarAlert_H

#include "SonarSensor.h"

using namespace ev3api;

class SonarAlert
{
private:
	SonarSensor *sonarSensor;

public:
	SonarAlert();
	bool isAlert(int16_t alert_distance);

	virtual ~SonarAlert();
};
#endif