#ifndef SENSOR_MANAGER_HPP
#define SENSOR_MANAGER_HPP

#include <vector>

class SensorManager {
public:
  SensorManager();
  ~SensorManager();

  float imuReadings[7];
};

#endif /* SENSOR_MANAGER_HPP */
