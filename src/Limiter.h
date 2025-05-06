#pragma once
#include <base/DynamicsProcessor.h>
#include <utils/extras/GainUtilities.h>

/**
 * Basic Limiter Effect
 */
template <typename SampleType>
class Limiter : public DynamicsProcessor<SampleType>
{
public:

	/**
	 * @brief Constructor
	 */
	Limiter();

	/**
	 * @brief Destructor
	 */
	~Limiter();

	/**
     * @brief Prepares object for playback
     * 
     * @param sampleRate Current sampling rate
     */
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

	/**
	 * @brief Sets the limiter threshold
	 * 
	 * @param newThreshold New threshold value in decibels
	 */
	void setThreshold(SampleType newThreshold) override;

	/**
	 * @brief Sets the limiter attack time
	 * 
	 * @param newAttack New attack time value in milliseconds
	 */
	void setAttack(SampleType newAttack) override;

	/**
	 * @brief Sets the limiter release time
	 * 
	 * @param newRelease New release time value in milliseconds
	 */
	void setRelease(SampleType newRelease) override;

	/**
	 * @brief Sets the limiter make-up gain
	 * 
	 * @param newGain New gain value in decibels
	 */
	void setGain(SampleType newGain) override;

	/**
	 * @brief Sets one of the limiter's parameters
	 * 
	 * @param index Parameter index
	 * @param newValue New parameter value
	 */
	void setParameter(int index, SampleType newValue);

	/**
	 * @brief Returns one of the limiter's parameters
	 * 
	 * @param index Parameter index
	 */
	SampleType getParameter(int index);

	/**
	 * @brief Sets the limiter knee type
	 * 
	 * @param index Knee type index
	 */
	void setKneeType(int index);

	/**
	 * @brief Returns the limiter knee type index
	 */
	int getKneeType();

	enum Parameters
	{
		Threshold = 0,	//-80 | 0 dB
		Attack,			//1ms | 100ms
		Release,		//10ms | 1000ms
		MakeupGain
	};

	enum KneeTypes
	{
		Soft = 0,
		Hard
	};

private:

	// User Parameters
	SampleType threshold{ -10.0 }; //in dB
	SampleType makeupGain{ 0.0 }; //in dB
	SampleType attack{ 10.0 }; //in ms
	SampleType release{ 100.0 }; //in ms
	int kneeType{ KneeTypes::Soft };

	//=============================================

	SampleType kneeWidth{ 10.0 }; //in dB

	//============================================

	SampleType calaculateGain(SampleType input);
};