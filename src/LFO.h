#pragma once 

class LFO
{
public:

	LFO();
	LFO(int _WaveformType);

	void prepare(double _SampleRate);
	void generateOutputSample();
	double getOutputSample(int phaseType);

	//Setters and Getters
	void setWaveformType(int _WaveformType);
	int getWaveformType();

	void setFrequency(double _Frequency);
	double getFrequency();

	void setSampleRate(double _SampleRate);
	double getSampleRate();

	double unipolarToBipolar(double value);

	enum WaveformTypes
	{
		Triangle = 0,
		Sine,
		Saw
	};

	enum PhaseTypes
	{
		Normal = 0,
		Inverted,
		QuadPhase,
		QuadPhase_Inverted
	};


private:

	//Advabce the mod counter
	void moduloAdvance(double& _ModCounter, double _PhaseInc);

	//Check the mod counter and wrap
	void moduloWrap(double& _ModCounter, double _PhaseInc);
	//Advance the mod counter and wrap
	void moduloAdvanceAndWrap(double& _ModCounter, double _PhaseInc);

	//Parabolic Sine Calculation Function (Angle ragnes from -pi to pi)
	double parabolicSine(double angle);

	//Oscillator Parameters
	double modCounter, modCounter90, phaseInc;
	double initial_SampleRate;

	//User Parameters
	double frequency, sampleRate;
	int waveformType;

	//Output Values
	double outNormal, outInverted, outQuadPhase, outQuadPhaseInverted;

	double m_pi = 3.14159265358979323846;

};