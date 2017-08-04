#ifndef PID_H
#define PID_H

#define DELTA_T 0.004

class PID
{
private:
	int diff[2];
	float integral;

public:
	PID();
	int getTurn(float p_value, float i_value, float d_value, unsigned int sensor_val, unsigned int target_val, int min, int max);
	int math_limit(int pid_value, int min, int max);

	virtual ~PID();
};
#endif