#include "ConexionWeb.h"
#include "boost/thread.hpp"

using namespace sio;
using namespace std;

boost::mutex mutex_;

ConexionWeb::ConexionWeb(void){}

  void ConexionWeb::setup(){

//std::mutex _lock;
  l = new connection_listener(h);

    //setmutex(&l->_lock);
    //set_condition(&l->_cond);
    //set_connect_finish(&l->connect_finish);

    h.set_open_listener(std::bind(&connection_listener::on_connected, l));
    h.set_close_listener(std::bind(&connection_listener::on_close, l, std::placeholders::_1));
    h.set_fail_listener(std::bind(&connection_listener::on_fail, l));
    h.connect("http://127.0.0.1:3000");
    cout << "entrando a lock"<< endl;

    //l->_lock.lock();
{
  boost::mutex::scoped_lock look(mutex_);
    cout << "entrando a lock despues"<< endl;
    //cout << &_lock << endl;
  //  if(!l->connect_finish)
  //  {
        //cout << &_lock << endl;
  //    l->_cond.wait(l->_lock);
        //cout << "entrando a lock despuesssss jajajaj"<< endl;
  //  }
    //l->_lock.unlock();
  }
	   current_socket = h.socket();
     bind_events(current_socket);
     cout << "saliendo de funcion"<< endl;

  }


  void ConexionWeb::bind_events(socket::ptr &socket)
  {
    cout << "bind de eventos"<< endl;
  	current_socket->on("respuesta", sio::socket::event_listener_aux([&](string const& name, message::ptr const& data, bool isAck,message::list &ack_resp)
                         {
                           boost::mutex::scoped_lock look(mutex_);
                             //l->_lock.lock();
                             string datos = data->get_map()["data"]->get_string();
                             int contador = data->get_map()["count"]->get_int();
                             cout << "data: " << datos << " count: " << contador << endl;
                            // l->_lock.unlock();
                         }));
/*
      current_socket->on("user joined",sio::socket::event_listener_aux([&](string const& name, message::ptr const& data, bool isAck,message::list &ack_resp)
                         {
                             _lock.lock();
                             string user = data->get_map()["username"]->get_string();
                             int participants  = data->get_map()["numUsers"]->get_int();
                             bool plural = participants !=1;
                            cout << "Se ha unido el usuario: " << user << " # participantes: " << participants << endl;
                            _lock.unlock();
                         }));
      current_socket->on("user left", sio::socket::event_listener_aux([&](string const& name, message::ptr const& data, bool isAck,message::list &ack_resp)
                         {
                             _lock.lock();
                             string user = data->get_map()["username"]->get_string();
                             int participants  = data->get_map()["numUsers"]->get_int();
                             bool plural = participants !=1;
                            cout << "Se ha ido el usuario: " << user << " # participantes: " << participants << endl;
                             _lock.unlock();
                         }));
                         */

  }

  void ConexionWeb::notificar_servidor(){
    string data_prueba = "data de prueba";
    current_socket->emit("pruebacpp", data_prueba);
    cout << "notificacion al servidor" << endl;
  }
/*
  void ConexionWeb::setmutex(std::mutex *_lock){
    this->_lock = _lock;
  }

  void ConexionWeb::set_condition(std::condition_variable_any *_cond){
    this->_cond = _cond;
  }

    void ConexionWeb::set_connect_finish(bool *connect_finish){
      this->connect_finish = connect_finish;
    }

*/
  ConexionWeb::~ConexionWeb()
  {
  }
