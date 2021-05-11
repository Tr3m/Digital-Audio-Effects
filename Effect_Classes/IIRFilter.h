#pragma once
#include "../IIRFilter Plug-In/JuceLibraryCode/JuceHeader.h"

class IIRFilter
{

public:

	//Constructors 
	IIRFilter(double sampleRate);
	IIRFilter(double sampleRate, int type);
	IIRFilter(double sampleRate, int type, float freq);


	void prepare(double sampleRate, int samplesPerBlock);
    void process(juce::AudioBuffer<float>& buffer, int channel, double sampleRate);

    
    //Might not need those...
    //==================================================
    //void setParameter(int index, float newValue);
    //float getPameter(int index);

	
    //Param Setters and Getters
    //==================================================
	void setCutoff(float newValue);
	void setFilterType(int filterType);
	void setQ(float newValue);
	void setGain(float newValue);

	float getCutoff();
	float getQ();
	float getGain();
	int getFilterType();
    
    //==================================================

	enum FilterTypes
	{
		LPF = 0,	//Low Pass Fitler
		HPF,		//High Pass Filter
		Parametric,
	};

	//==================================================

private:

	void calculateCoeffs();


	float a0, a1, a2, b1, b2, c0, d0, r, C;

	double last_SampleRate;

	float m_pi = 3.14159265358979323846;

	//Paremetric EQ Filter Variables
	float K, V0, e0, D0, alpha, beta, gamma, delta, heta;

	float theta_c, u, zeta;

	float xn_1 = 0, xn_2 = 0, yn_1 = 0, yn_2 = 0;

	//User Variables
	float fc, Q, notchGain;
	int filterType;

};