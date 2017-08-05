#ifndef PIDController_H
#define PIDController_H

#define DELTA_T 0.004

class PIDController
{
private:
	int diff[2];
	float integral;

public:
	PIDController();
	int getTurn(float p_value, float i_value, float d_value, unsigned int sensor_val, unsigned int target_val, int min, int max);
	int math_limit(int pid_value, int min, int max);

	virtual ~PIDController();
};
#endif