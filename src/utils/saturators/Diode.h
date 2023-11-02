#pragma once
#include <cmath>

/**
 * Diode Saturation model
 *
 */
template <typename SampleType>
struct Diode
{
  /**
   * @brief Processes a single sample
   * 
   * @param input Input sample
   * @param Vt Thermal voltage
   * @param ec Emission coefficient
   * @param Is Saturation current
   */
  static inline SampleType processSample(SampleType input, SampleType Vt = 0.0253, SampleType ec = 1.68, SampleType Is = 0.105)
  {
    return (Is * (std::exp((0.1 * input) / ec * Vt) - 1.0));
  };
};
