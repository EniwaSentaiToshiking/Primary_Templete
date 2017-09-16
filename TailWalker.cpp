#include "TailWalker.h"

TailWalker::TailWalker()
{
    leftMotor = new Motor(PORT_C);
    rightMotor = new Motor(PORT_B);
    clock = new Clock();
    mea = new Measure();
}

TailWalker::~TailWalker() {}

void TailWalker::balance()
{
    leftMotor->setPWM(15);
    rightMotor->setPWM(15);
    clock->sleep(300);
    stop();
}

void TailWalker::forward(int pwm, float distance)
{
    mea->measure();
    float beginDistance = mea->getCurrentDistance();

    while (mea->getCurrentDistance() - beginDistance <= float(distance))
    {
        leftMotor->setPWM(pwm);
        rightMotor->setPWM(pwm);
        mea->measure();
    }
    stop();
}

void TailWalker::backward(int pwm, float distance)
{
    mea->measure();
    float beginDistance = mea->getCurrentDistance();

    while (beginDistance - mea->getCurrentDistance() <= float(distance))
    {
        leftMotor->setPWM(pwm * -1);
        rightMotor->setPWM(pwm * -1);
        mea->measure();
    }
    stop();
}

void TailWalker::keepOnMovingForward(int pwm)
{
    leftMotor->setPWM(pwm);
    rightMotor->setPWM(pwm);
}

void TailWalker::keepOnMovingBackward(int pwm)
{
    leftMotor->setPWM(pwm * -1);
    rightMotor->setPWM(pwm * -1);
}

void TailWalker::stop()
{
    leftMotor->setPWM(0);
    rightMotor->setPWM(0);
    clock->sleep(300);
}

void TailWalker::leftTurn(int angle)
{
    mea->measure();
    float begin_direction = mea->getCurrentDirection();

    while (mea->getCurrentDirection() - begin_direction < angle)
    {
        leftMotor->setPWM(TURN_PWM * -1);
        rightMotor->setPWM(TURN_PWM);
        mea->measure();
    }
    stop();
}

void TailWalker::rightTurn(int angle)
{
    mea->measure();
    float begin_direction = mea->getCurrentDirection();

    while (begin_direction - mea->getCurrentDirection() < angle)
    {
        leftMotor->setPWM(TURN_PWM);
        rightMotor->setPWM(TURN_PWM * -1);
        mea->measure();
    }
    stop();
}

void TailWalker::lineTrace(int color, int target_color)
{
    if (color >= target_color)
    {
        rightMotor->setPWM(4);
        leftMotor->setPWM(9);
    }
    else
    {
        rightMotor->setPWM(9);
        leftMotor->setPWM(4);
    }
}

void TailWalker::reset_distance()
{
    mea->distance_reset();
}

float TailWalker::getDistance()
{
    mea->measure();
    return mea->getCurrentDistance();
}

bool TailWalker::get4msRightMotorCount()
{
    static int prevRightMotorCount = 0;
    int currentRightMotorCount = rightMotor->getCount();
    int result = currentRightMotorCount - prevRightMotorCount;
    prevRightMotorCount = currentRightMotorCount;

    if (result == 0) right_buffer[right_buffer_count++] = 0;
    else right_buffer[right_buffer_count++] = 1;

    if(right_buffer_count == BUFFER_SIZE) right_buffer_count = 0;
    
        for(int i = 0; i < BUFFER_SIZE; i++)
        {
            if(right_buffer[i] == 1)
            {
                return false;
            }
        }
    
        return true;
}

bool TailWalker::get4msLeftMotorCount()
{
    static int prevLeftMotorCount = 0;
    
    int currentLeftMotorCount = leftMotor->getCount();
    int result = currentLeftMotorCount - prevLeftMotorCount;
    prevLeftMotorCount = currentLeftMotorCount;

    if (result == 0) left_buffer[left_buffer_count++] = 0;
    else left_buffer[left_buffer_count++] = 1;

    if(left_buffer_count == BUFFER_SIZE) left_buffer_count = 0;

    for(int i = 0; i < BUFFER_SIZE; i++)
    {
        if(left_buffer[i] == 1)
        {
            return false;
        }
    }

    return true;
}

void TailWalker::bufferInit()
{
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        right_buffer[i] = 1;
        left_buffer[i] = 1;
    }

    right_buffer_count = 0;
    left_buffer_count = 0;
}