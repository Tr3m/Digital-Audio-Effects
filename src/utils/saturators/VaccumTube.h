#pragma once
#include <cmath>

/**
 * Vaccum Tube saturation model
 * 
 * @tparam SampleType 
 */
template <typename SampleType>
struct VaccumTube
{
  /**
   * @brief Processes a single sample
   * 
   * @param input Input sample
   * @param workPoint Tube work point. Affects the linearity for low input levels
   * @param dist Distortion amount
   */
  static inline SampleType processSample(SampleType input, SampleType workPoint = -0.2, SampleType dist = 10.0)
  {
    SampleType in = input;
    SampleType out = 0.0;

    if(workPoint == 0)
    {
        if(in == workPoint)
            out = 1.0 / dist;
        else
            out = in / (1.0 - std::exp(-dist * in));
    }
    else
    {
        if(in == workPoint)
            out = (1.0 / dist) + (workPoint / (1.0 - std::exp(dist * workPoint)));
        else
            out = ((in - workPoint) / (1.0 - std::exp(-dist * (in - workPoint)))) + (workPoint / (1.0 - std::exp(dist * workPoint)));
    }

    return out;
  };
};