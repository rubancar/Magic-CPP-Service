#include <string>
#include <stdio.h>
#include <cstdlib>


#include "SerialPort.h"

using namespace std;

SerialPort::SerialPort(void) : end_of_line_char_('\n')
{
  base.setup("invernadero", "localhost", "root", "1991");
}


SerialPort::~SerialPort(void)
{
	stop();
}

char SerialPort::end_of_line_char() const
{
	return this->end_of_line_char_;
}

void SerialPort::end_of_line_char(const char &c)
{
	this->end_of_line_char_ = c;
}

bool SerialPort::start(const char *com_port_name, int baud_rate)
{
	boost::system::error_code ec;

	if (port_) {
		std::cout << "error : port is already opened..." << std::endl;
		return false;
	}
//port_ = NULL;
	port_ = serial_port_ptr(new boost::asio::serial_port(io_service_));
	port_->open(com_port_name, ec);
	if (ec) {
		std::cout << "error : port_->open() failed...com_port_name="
			<< com_port_name << ", e=" << ec.message().c_str() << std::endl;
		return false;
	}

	// option settings...
	port_->set_option(boost::asio::serial_port_base::baud_rate(baud_rate));
	port_->set_option(boost::asio::serial_port_base::character_size(8));
	port_->set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));
	port_->set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none));
	port_->set_option(boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none));

	boost::thread t(boost::bind(&boost::asio::io_service::run, &io_service_));

	async_read_some_();

	return true;
}

void SerialPort::stop()
{
	boost::mutex::scoped_lock look(mutex_);

	if (port_) {
		port_->cancel();
		port_->close();
		port_.reset();
	}
	io_service_.stop();
	io_service_.reset();
}

int SerialPort::write_some(const std::string &buf)
{
	return write_some(buf.c_str(), buf.size());
}

int SerialPort::write_some(const char *buf, const int &size)
{
	boost::system::error_code ec;

	if (!port_) return -1;
	if (size == 0) return 0;

	return port_->write_some(boost::asio::buffer(buf, size), ec);
}

void SerialPort::async_read_some_()
{
	if (port_.get() == NULL || !port_->is_open()) return;

	port_->async_read_some(
		boost::asio::buffer(read_buf_raw_, SERIAL_PORT_READ_BUF_SIZE),
		boost::bind(
			&SerialPort::on_receive_,
			this, boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void SerialPort::on_receive_(const boost::system::error_code& ec, size_t bytes_transferred)
{


    boost::mutex::scoped_lock look(mutex_);
    //bool test = true;
    //test = mutex_.try_lock();
    //std::cout << test << std::endl;
    if (port_.get() == NULL || !port_->is_open()) return;
    if (ec) {
      async_read_some_();
      return;
    }

    for (unsigned int i = 0; i < bytes_transferred; ++i) {
      char c = read_buf_raw_[i];
      //std::cout << c << std::endl;
      if (c == end_of_line_char_) {
        this->on_receive_(read_buf_str_);
        read_buf_str_.clear();
      }
      else {
        read_buf_str_ += c;
      }
    }

	async_read_some_();
}

void SerialPort::on_receive_(const std::string &data)
{
	std::cout << "SerialPort::on_receive_() : " << data << std::endl;
  //el ultimo parametro es el tipo de sensor
  // 2 = temperatura
  // 1 = humedad
  // 0 = luz
  float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/123.23));
  if(base.guardar_registro_sensor(r2, 1, 1)){
    sio->emit("actualizar_datos","Senial Arduino");
  }

}

void SerialPort::setSioClient(SIOClient *sio_){
  sio = sio_;

}
