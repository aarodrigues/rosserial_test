#include "stdafx.h"
#include "HySpexControl.h"


HySpexControl::HySpexControl() : 
	hySpex_(std::unique_ptr<HySpex>(new HySpex()))
{
}


HySpexControl::~HySpexControl()
{
}

void HySpexControl::movePitch(int degree) 
{
	hySpex_->movePitch(degree);
}

void HySpexControl::moveYaw(int degree) 
{
	hySpex_->moveYaw(degree);
}

void HySpexControl::detectCamera()
{
	hySpex_->detectCamera();
}

void HySpexControl::detectStages() 
{
	hySpex_->detectStages();
}

void HySpexControl::startAquisition() 
{
	hySpex_->startAquisition();
}

void HySpexControl::stopAquisition() 
{
	hySpex_->stopAquisition();
}

void HySpexControl::showFrameAquisition() 
{
	hySpex_->showFrameAquisition();
}

void HySpexControl::showPanTiltPosition() 
{
	hySpex_->showPanTiltPosition();
}

void HySpexControl::showCamIds() 
{
	hySpex_->showCamIds();
}

void HySpexControl::setSweepAngle(int degree) 
{
	hySpex_->setSweepAngle(degree);
}

void HySpexControl::setInitialPosition(int degree) 
{
	hySpex_->setInitialPosition(degree);
}

void HySpexControl::setOverlayPercentage(double percentage) 
{
	hySpex_->setOverlayPercentage(percentage);
}

void HySpexControl::setScanNumberLines(int lines) 
{
	hySpex_->setScanNumberLines(lines);
}

void HySpexControl::setIntegrationTime(int time) 
{
	hySpex_->setIntegrationTime(time);
}

void HySpexControl::setFramePeriod(int period) 
{
	hySpex_->setFramePeriod(period);
}

void HySpexControl::setReturnSpeed(int speed) 
{
	hySpex_->setReturnSpeed(speed);
}

void HySpexControl::setPrimaryCam(int id) 
{
	hySpex_->setPrimaryCam(id);
}

std::string HySpexControl::getLog()
{
	return hySpex_->getLog();
}
std::string HySpexControl::getPanTilt()
{
	return hySpex_->getPanTilt();
}