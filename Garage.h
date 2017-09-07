#ifndef Gagare_H
#define Garage_H

#include "TailWalker.h"
#include "TailController.h"

using namespace ev3api;

class Garage
{

	private:
		enum State
		{
			GARAGE_IN,
			STOP,
			COMPLETE
		};

		TailWalker *tailWalker;
		TailController *tailController;

  public:
	Garage(TailController *tailController);
	void run(int color);
	virtual ~Garage();
};

#endif