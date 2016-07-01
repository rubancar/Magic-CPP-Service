#pragma once
#include <mysql++.h>
#include <string>
#include <stdio.h>

using namespace mysqlpp;
using namespace std;

class BaseDeDatos{

private:
  Connection conn;
  const char* nombre_base;
  const char* direccion_base;
  const char* usuario;
  const char* contrasenia;

public:

  bool guardar_registro_sensor(float valor_sensor, int id_sensor_, int tipo_sensor);
  void setup(const char* nombre_base_, const char* direccion_, const char* usuario_, const char* contrasenia_);
  BaseDeDatos();
  ~BaseDeDatos();

};
