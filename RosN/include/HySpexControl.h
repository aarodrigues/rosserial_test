
#pragma once
#include <iostream>
#include "HySpex.h"

class HySpexControl
{
public:
	HySpexControl();
	~HySpexControl();
	//Geonosis Object
	std::unique_ptr<HySpex> hySpex_;

	void movePitch(int degree);
	void moveYaw(int degree);
	std::string detectCamera();
	void detectStages();
	void startAquisition();
	void stopAquisition();
	void showFrameAquisition();
	void showPanTiltPosition();
	void showCamIds();
	void setSweepAngle(int degree);
	void setInitialPosition(int degree);
	void setOverlayPercentage(double percentage);
	void setScanNumberLines(int lines);
	void setIntegrationTime(int time);
	void setFramePeriod(int period);
	void setReturnSpeed(int speed);
	void setPrimaryCam(int id);
	void getLog();
	void getPanTilt();

};

