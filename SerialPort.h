#pragma once
#include <mysql++.h>
#include "BaseDeDatos.h"
#include "boost/asio.hpp"
#include "boost/asio/serial_port.hpp"
//#include "boost/system/error_code.hpp"
//#include "boost/system/system_error.hpp"
#include "boost/bind.hpp"
#include "boost/thread.hpp"
#include "SIOClient.h"
#include <vector>

using namespace mysqlpp;

typedef boost::shared_ptr<boost::asio::serial_port> serial_port_ptr;

#define SERIAL_PORT_READ_BUF_SIZE 256

class SerialPort
{

protected:
	boost::asio::io_service io_service_;
	serial_port_ptr port_;
	boost::mutex mutex_;

	char read_buf_raw_[SERIAL_PORT_READ_BUF_SIZE];
	std::string read_buf_str_;

	char end_of_line_char_;
  BaseDeDatos base;

private:
	SerialPort(const SerialPort &p);
	SerialPort &operator=(const SerialPort &p);
	SIOClient *sio;

public:
	SerialPort(void);
	virtual ~SerialPort(void);

	char end_of_line_char() const;
	void end_of_line_char(const char &c);
  int guardar_datos_en_base();

	virtual bool start(const char *com_port_name, int baud_rate=9600);
	virtual void stop();

	int write_some(const std::string &buf);
	int write_some(const char *buf, const int &size);

	void setSioClient(SIOClient *sio_);


protected:
	virtual void async_read_some_();
	virtual void on_receive_(const boost::system::error_code& ec, size_t bytes_transferred);
	virtual void on_receive_(const std::string &data);

};
