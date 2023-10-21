#pragma once
#include <cmath>

#define PI 3.14159265358979323846

/**
 * IIR Filter Class
 * 
 */
template <typename SampleType>
class IIRFilter
{
public:

	/**
	 * @brief Constructor
	 */
	IIRFilter();

	/**
	 * @brief Destructor
	 */
	~IIRFilter();

	/**
	 * @brief Prepares object for playback
	 * 
	 * @param sampleRate Current sampling rate
	 */
	void prepare(SampleType sampleRate);

	/**
	 * @brief Processes a single sample
	 * 
	 * @param input Input sample
	 */
	SampleType processSample(SampleType input);

	/**
	 * @brief Processes a memory block that holds audio samples
	 * 
	 * @param data Memory block start pointer 
	 * @param startSample Sample index to start processing from
	 * @param endSample Number of samples to process
	 */
    void process(SampleType* data, int startSample, int endSample);

	/**
	 * @brief Sets filter cutoff frequency
	 * 
	 * @param newValue New cutoff frequency value
	 * 
	 * When the filter mode is set to Parametric it sets the center frequency instead.
	 */
	void setCutoff(SampleType newValue);

	/**
	 * @brief Sets the filter type
	 * 
	 * @param filterType Filter type index
	 */
	void setFilterType(int filterType);

	/**
	 * @brief Sets the filter quality factor
	 * 
	 * @param newValue New filter quality factor
	 */
	void setQ(SampleType newValue);

	/**
	 * @brief Sets the amount of boost/attenuation of the parametric mode
	 * 
	 * @param newValue New boost/attention value in decibels
	 */
	void setGain(SampleType newValue);

	/**
	 * @brief Returns the cutoff/center frequency of the filter
	 */
	SampleType getCutoff();

	/**
	 * @brief Returns the quality factor of the filter
	 */
	SampleType getQ();

	/**
	 * @brief Returns the boost/cut value of the parametric filter mode
	 */
	SampleType getGain();

	/**
	 * @brief Returns the filter type index
	 */
	int getFilterType();
    
	enum FilterTypes
	{
		LPF = 0,	// Low Pass Fitler
		HPF,		// High Pass Filter
		Parametric,
	};


private:

	SampleType sampleRate;

	SampleType a0, a1, a2, b1, b2, c0, d0, r, C;

	// Paremetric EQ Filter Variables
	SampleType K, V0, e0, D0, alpha, beta, gamma, delta, heta;
	SampleType theta_c, u, zeta;

	// Previous in/out values
	SampleType xn_1 = 0, xn_2 = 0, yn_1 = 0, yn_2 = 0;

	// User Parameters
	SampleType fc {500.0}, Q {1.0}, notchGain {0.0};
	int filterType {FilterTypes::LPF};

	void calculateCoeffs();

};