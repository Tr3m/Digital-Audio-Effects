#pragma once

/**
 * Basic Hard Clipping Waveshaper
 * 
 */
template <typename SampleType>
struct HardClipper
{
  /**
   * @brief Processes a single sample
   * 
   * @param input Input sample
   * @param threshold Gain limit threshold
   */
  static inline SampleType processSample(SampleType input, SampleType threshold = 0.6)
  {
    return input > threshold ? threshold : input < -threshold ? -threshold : input;
  };
};