#pragma once
#include "socket.io-client-cpp/src/sio_client.h"
#include <functional>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>

using namespace sio;
using namespace std;

class connection_listener
{
    sio::client &handler;

public:

    connection_listener(sio::client& h):
    handler(h)
    {
    }


    void on_connected()
    {
        _lock.lock();
        _cond.notify_all();
        connect_finish = true;
        _lock.unlock();
    }
    void on_close(client::close_reason const& reason)
    {
        std::cout<<"sio closed "<<std::endl;
        exit(0);
    }

    void on_fail()
    {
        std::cout<<"sio failed "<<std::endl;
        exit(0);
    }

    std::mutex _lock;
    std::condition_variable_any _cond;
    bool connect_finish = false;
};

class ConexionWeb{

  public:
    void setup();
    void bind_events(socket::ptr &socket);
    void notificar_servidor();
  //  void setmutex(std::mutex *_lock);
  //  void set_condition(std::condition_variable_any *_cond);
  //  void set_connect_finish(bool *connect_finish);
    ConexionWeb(void);
    ~ConexionWeb();

  private:
    socket::ptr current_socket;
    sio::client h;
    connection_listener *l;
    //std::mutex *_lock;
    //std::condition_variable_any *_cond;
    //bool *connect_finish;


};
