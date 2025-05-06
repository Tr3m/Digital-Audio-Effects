#pragma once

#include <base/EffectProcessorBase.h>
#include <utils/ModulatedCombFilter.h>
#include <utils/ModulatedAllPassFilter.h>
#include <utils/LFO.h>
#include <IIRFilter.h>
#include <utils/extras/FirstOrderSmoother.h>

#define NUM_COMBS 4
#define NUM_ALLPASS 2

template <typename SampleType>
class Reverb : public EffectProcessorBase<SampleType>
{
public:
	Reverb();
	~Reverb();

	void prepare(SampleType sampleRate) override;

	/**
	 * @brief Processes a single sample
	 * 
	 * @param input Input sample
	 */
	SampleType processSample(SampleType input) override;

	/**
	 * @brief Processes a memory block that holds audio samples
	 * 
	 * @param data Memory block start pointer 
	 * @param startSample Sample index to start processing from
	 * @param endSample Number of samples to process
	 */
	void process(SampleType* data, int startSample, int endSample) override;

	void setRoomSize(SampleType newRoomSize);
	void setDecay(SampleType newDecay);
	void setCutoff(SampleType newCutoff);
	void setMix(SampleType newMix);

private:

	ModulatedCombFilter<SampleType> combFilters[NUM_COMBS];
	ModulatedAllPassFilter<SampleType> allPassFilters[NUM_ALLPASS];
	
	LFO combLFO[NUM_COMBS];
	LFO allPassLFO[NUM_ALLPASS];

	SampleType combDelayTimeValues[NUM_COMBS] {43.7, 41.1, 37.1, 29.7}; // CombFilter Delay times in ms
	SampleType combFeedbackValues[NUM_COMBS] {0.9, -0.9, 0.9, -0.9};
	SampleType combModRates[NUM_COMBS] {0.6, 0.71, 0.83, 0.95};

	SampleType allPassDelayTimeValues[NUM_ALLPASS] {5.0, 1.7}; // AllPass Delay times in ms
	SampleType allPassFeedbackValues[NUM_ALLPASS] {0.7, 0.7};
	SampleType allPassModRates[NUM_ALLPASS] {0.6, 0.83};

	FirstOrderSmoother valueSmoothers[NUM_COMBS];

	IIRFilter<SampleType> filter;

	// User Parameters
	SampleType roomSize {1.0}, decay {0.5}, filterCutoff {20000.0}, mix {0.5};
};