#pragma once

#include "SIOEventTarget.h"
#include "SerialPort.h"

class TestTarget : public SIOEventTarget
{
public:
	TestTarget();
	~TestTarget() {};

	SerialPort *serial;


	void onMessage(const void* pSender, Array::Ptr& arg);
	void onEvent(const void* pSender, Array::Ptr& arg);
	void onEnviarSenial(const void* pSender, Array::Ptr& arg);
	void setSerialPort(SerialPort *serial_);
	void onApagarSenial(const void* pSender, Array::Ptr& arg);
};
