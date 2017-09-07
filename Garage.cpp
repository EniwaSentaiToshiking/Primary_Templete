#include "Garage.h"

Garage::Garage(TailController *tailController)
{
	tailWalker = new TailWalker();
	this->tailController = tailController;
}

Garage::~Garage()
{
}

void Garage::run(int color)
{

	static State state = GARAGE_IN;
	static float beginDistance = tailWalker->getDistance();

	switch (state)
	{
	case GARAGE_IN:

		if (tailWalker->getDistance() - beginDistance <= 23)
		{
			tailController->rotate(tailController->getCurrentAngle(), 50, false);
			tailWalker->lineTrace(color, 23);
		}
		else
		{
			state = STOP;
		}

		break;

	case STOP:
		tailController->rotate(85, 50, false);
		tailWalker->balance();
		state = COMPLETE;
		break;
	case COMPLETE:
		
		break;
	}
}