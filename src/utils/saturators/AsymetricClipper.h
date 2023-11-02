#pragma once
#include <cmath>
/**
 * Basic Asymetric Clipping Waveshaper
 *
 */
template <typename SampleType>
struct AsymetricClipper
{
  /**
   * @brief Processes a single sample
   * 
   * @param input Input sample
   * @param k Gain
   * @param g Saturation limit
   */
  static inline SampleType processSample(SampleType input, SampleType k = 1.5, SampleType g = 0.7)
  {
    return input >= 0 ? SampleType(std::atan(k * input) / std::atan(k)) : SampleType(0.5 * (std::atan(k / g) * input) / std::atan(k / g));
  };
};