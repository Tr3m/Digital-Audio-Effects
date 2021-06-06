#pragma once
#include "EnvelopeDetector.h"

class Compressor
{
public:

	Compressor();

	void prepare(double _sampleRate);
	double processSample(double input);

	//Setters and Getters
	void setParameter(int index, double newValue);
	double getParameter(int index);

	void setKneeType(int index);
	int getKneeType();

	enum Parameters
	{
		Threshold = 0,	//-80 | 0 dB
		Ratio,			//
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


	//User Parameters
	double threshold{ -10.0 }; //in dB
	double ratio{ 50.0 };
	double makeupGain{ 0.0 }; //in dB
	double attack{ 10.0 }; //in ms
	double release{ 100.0 }; //in ms
	int kneeType{ KneeTypes::Soft };
	//=============================================

	double kneeWidth{ 30.0 }; //in dB
	EnvelopeDetector detector;

	//============================================

	double calaculateGain(double input);
	double decibelToLinear(double dbValue);

};