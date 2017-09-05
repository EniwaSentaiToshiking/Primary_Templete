#include "SonarAlert.h"

SonarAlert::SonarAlert()
{
    sonarSensor = new SonarSensor(PORT_2);
}

SonarAlert::~SonarAlert()
{
    delete sonarSensor;
}

bool SonarAlert::isAlert(int16_t alert_distance)
{

    static uint32_t counter = 0;
    bool alert = false;

    if (++counter == 40 / 4) /* 約40msec周期毎に障害物検知  */
    {
        /*
         * 超音波センサによる距離測定周期は、超音波の減衰特性に依存します。
         * NXTの場合は、40msec周期程度が経験上の最短測定周期です。
         * EV3の場合は、要確認
         */
        int16_t distance = sonarSensor->getDistance();
        if ((distance <= alert_distance) && (distance >= 0))
        {
            alert = true;
        }
        else
        {
            alert = false;
        }
        counter = 0;
    }
    return alert;
}
