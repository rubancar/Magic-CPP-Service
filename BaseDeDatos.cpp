#include "BaseDeDatos.h"
#include "tablas.h"
#include <datetime.h>
#include <ctime>

using namespace std;

BaseDeDatos::BaseDeDatos()
{

}


void BaseDeDatos::setup(const char* nombre_base_, const char* direccion_, const char* usuario_, const char* contrasenia_)
{
  nombre_base = nombre_base_;
  direccion_base = direccion_;
  usuario = usuario_;
  contrasenia = contrasenia_;
  //conectamos a la base de datos ==> direccion puede ser localhost
  conn.connect(nombre_base, direccion_base, usuario, contrasenia);
}

bool BaseDeDatos::guardar_registro_sensor(float valor_sensor, int id_sensor_, int tipo_sensor){
  try {
    time_t now = time(0);
    Query query = conn.query();

    switch (tipo_sensor) {
      case 2:{
        registro_temp registro_t(mysqlpp::DateTime(now), valor_sensor, id_sensor_);
        query.insert(registro_t);
      }
      break;

      case 1:{
        registro_humedad registro_h(mysqlpp::DateTime(now), valor_sensor, id_sensor_);
        query.insert(registro_h);
      }
      break;

      case 0:{
        registro_luz registro_l(mysqlpp::DateTime(now), valor_sensor, id_sensor_);
        query.insert(registro_l);
      }
        break;
    }
      // Show the query about to be executed.
      cout << "Query: " << query << endl;
      query.execute();

    }
    catch (const mysqlpp::BadQuery& er) {
        // Handle any query errors
        cerr << "Query error: " << er.what() << endl;
        return false;
    }
    catch (const mysqlpp::BadConversion& er) {
        // Handle bad conversions
        cerr << "Conversion error: " << er.what() << endl <<
                "\tretrieved data size: " << er.retrieved <<
                ", actual size: " << er.actual_size << endl;
        return false;
    }
    catch (const mysqlpp::Exception& er) {
        // Catch-all for any other MySQL++ exceptions
        cerr << "Error: " << er.what() << endl;
        return false;
    }

    return true;

}

BaseDeDatos::~BaseDeDatos()
{

}
