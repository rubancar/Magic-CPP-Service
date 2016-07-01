#include <stdio.h>
#include <iostream>
#include "SerialPort.h"
#include "Poco/ConsoleChannel.h"
#include "Poco/Exception.h"
#include "Poco/Thread.h"
#include "SIOClient.h"
#include "TestTarget.h"
#include "TestEndpointTarget.h"

using Poco::Thread;

int main(int argc, char* argv[])
{

	bool rv;
	string data_prueba = "data de prueba";
	std::string name = "/dev/ttyACM0";

	SerialPort serial;

	rv = serial.start(name.c_str(), 9600);
	if (rv == false) {
		return -1;
	}

	Logger *logger = &(Logger::get("example"));

	logger->setChannel(new Poco::ConsoleChannel());
	SIOClient *sio = SIOClient::connect("http://localhost:8080");

	//Create a target and register object its method onUpdate for the Update event
	//JS: socket.on("Update", function(data) {...});
	TestTarget *target = new TestTarget();
	target->setSerialPort(&serial);
	sio->on("message", target, callback(&TestTarget::onMessage));

	//setup is now complete, messages and events can be send and received
	logger->information("cliente de Socket.io establecido\n");

	//test the message sending
	logger->information("Enviando string de prueba");
	sio->send("Mensaje Allons-Y!!");
  logger->information("Enviando json de prueba\n");
	sio->send("{\"nombre\":\"Ruben\",\"apellido\":\"Carvajal\"}");

	//test the event emitter, this will return the same event so let's register a callback too
	/*
	sio->on("chat", target, callback(&TestTarget::onEvent));
  logger->information("Emit \"chat\" event with string");
	sio->emit("chat","Event - String");
  logger->information("Emit \"chat\" event with json");
	sio->emit("chat", "[{\"name\":\"myname\",\"type\":\"mytype\"}]");
	*/
	sio->on("senial_arduino", target, callback(&TestTarget::onEnviarSenial));

	sio->on("senial_arduino_apagar", target, callback(&TestTarget::onApagarSenial));


	logger->information("Presione ENTER para continuar...");
	std::cin.get();

	//test disconnecting a single endpoint, other endpoints stay connected
	//~ testpoint->disconnect();

	int x = 0;
	serial.end_of_line_char(0x2f);
	serial.setSioClient(sio);
	//disconnecting the default socket with no endpoint will also disconnect all endpoints
	while (true) {
    //serial.write_some("*");
		//sio->emit("senial_arduino","Senial Arduino");
		//sio->emit("chat","Event - String");
		std::cout << x << std::endl;
    x++;
		std::cin.get();
    //usleep(1 * 1000000);
  }

	sio->disconnect();

	//logger->information("Press ENTER to quit...");
	//std::cin.get();


	//std::cout << "despues de setup" << std::endl;
	//std::cout << "mod de prueba" << std::endl;
	// initialize
	//el caracter para terminar la linea es "/"
	//serial.end_of_line_char(0x2f);


	//serial.write_some("hola,");
  //usleep(1 * 1000000);

	//serial.write_some("esto es una prueba,");
  //usleep(1 * 1000000);

	//serial.write_some("hola mundo,");
	// wait
	//usleep(1 * 1000000);

	serial.stop();

	return 0;
}
