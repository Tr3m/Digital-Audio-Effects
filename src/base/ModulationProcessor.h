#pragma once
#include <base/EffectProcessorBase.h>
#include <utils/LinearInterpolationCircularBuffer.h>
#include <utils/LFO.h>

/**
 * Base Class for Modulation Effect Processors
 * 
 */
template <typename SampleType>
class ModulationProcessor : public EffectProcessorBase<SampleType>
{
public:
    
    /**
	 * @brief Sets modulation rate
	 * 
	 * @param newRate New rate value
	 */
    virtual void setRate(SampleType newRate) = 0;

    /**
	 * @brief Sets modulation depth
	 * 
	 * @param newDepth New depth value
	 */
    virtual void setDepth(SampleType newDepth) = 0;

protected:

    SampleType doUnipolarModulationFromMin(SampleType unipolarModulatorValue, SampleType minValue, SampleType maxValue)
    {
        // --- UNIPOLAR bound
        unipolarModulatorValue = fmin(unipolarModulatorValue, 1.0f);
        unipolarModulatorValue = fmax(unipolarModulatorValue, 0.0f);

        // --- modulate from minimum value upwards
        return unipolarModulatorValue * (maxValue - minValue) + minValue;
    };

    SampleType bipolarToUnipolar(SampleType value)
    {
        return 0.5 * value + 0.5;
    };

protected:
    SampleType sampleRate;
    LinearInterpolationCircularBuffer<SampleType> delayLine;
	LFO lfo;
};