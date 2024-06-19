#ifndef SENSOR_MANAGER_HPP
#define SENSOR_MANAGER_HPP

#include <vector>

class SensorManager {
public:
  SensorManager();
  ~SensorManager();

  std::vector<float> imuReadings;
};

#endif /* SENSOR_MANAGER_HPP */
