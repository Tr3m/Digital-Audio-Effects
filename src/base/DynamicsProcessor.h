#pragma once
#include <base/EffectProcessorBase.h>
#include <utils/EnvelopeDetector.h>

/**
 * Base Class for Dynamics Effects Processors
 */
template <typename SampleType>
class DynamicsProcessor : public EffectProcessorBase<SampleType>
{
public:
 
	/**
	 * @brief Sets the detection threshold
	 * 
	 * @param newThreshold New threshold value in decibels
	 */
    virtual void setThreshold(SampleType newThreshold) = 0;

	/**
	 * @brief Sets the detector attack time
	 * 
	 * @param newRatio New ratio value
	 */
	virtual void setAttack(SampleType newAttack) = 0;

	/**
	 * @brief Sets the detector release time
	 * 
	 * @param newRelease New release time value in milliseconds
	 */
	virtual void setRelease(SampleType newRelease) = 0;

	/**
	 * @brief Sets the processor make-up gain
	 * 
	 * @param newGain New gain value in decibels
	 */
	virtual void setGain(SampleType newGain) = 0;
    

protected:
    EnvelopeDetector<SampleType> detector;    
};