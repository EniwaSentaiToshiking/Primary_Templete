#ifndef LOGGER_H
#define LOGGER_H

#include "Measure.h"

class Logger
{
private:
	FILE *log_file;

public:
	Logger(const char *file_name);
	void logging(float data);

	virtual ~Logger();
};
#endif