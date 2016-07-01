#include "TestTarget.h"
#include "Poco/Logger.h"
#include <iostream>

using Poco::Logger;


TestTarget::TestTarget()
{

}

void TestTarget::onMessage(const void* pSender, Array::Ptr& arg)
{
  std::string msg = "";
  for(int i=0;i<arg->size();++i)
    msg += arg->get(i).toString() + "";
	Logger::get("example").information("onMessage: %s",msg);
}

void TestTarget::onEvent(const void* pSender, Array::Ptr& arg)
{
  std::string msg = "";
  for(int i=0;i<arg->size();++i)
    msg += arg->get(i).toString() + " ";
	Logger::get("example").information("onEvent! " + msg);
}


void TestTarget::onEnviarSenial(const void* pSender, Array::Ptr& arg)
{
	Logger::get("example").information("Enviando senial a arduino!");
  serial->write_some("*");
}

void TestTarget::onApagarSenial(const void* pSender, Array::Ptr& arg)
{
	Logger::get("example").information("Enviando senial apagar actuador en arduino!");
  serial->write_some("&");
}

void TestTarget::setSerialPort(SerialPort *serial_)
{
  serial = serial_;
}
