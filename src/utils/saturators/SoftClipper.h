#pragma once
#include <cmath>

/**
 * Basic Exponential Soft Clipping Waveshaper
 * 
 */
template <typename SampleType>
struct SoftClipper
{
  /**
   * @brief Processes a single sample
   * 
   * @param input Input sample
   * @param gain Gain
   */
  static inline SampleType processSample(SampleType input, SampleType gain = 0.6)
  {
    return input == 0 ? 0.0 : (input / std::abs(input)) * (1.0 - std::exp(-std::abs(gain*input)));
  };
};