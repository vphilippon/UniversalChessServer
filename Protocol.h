/******************************************************************************
  Protocol.h
  =====================
  Original author : Julian Bironneau and Vincent Philippon
  Original creation date : 2014-04-08

  This class has 2 static method to write and read a Data instance on a 
  boost tcp::socket. It serialize the Data using the boost serialization lib 
  and then uses the Request class to wrap it befor sending the byte. The 
  opposite process is done for the reading.
 *****************************************************************************/

#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include <cstdlib>
#include <string>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include "Data.h"

using namespace std;
using boost::asio::ip::tcp;

class Protocol
{
  public:
    static Data read(shared_ptr<tcp::socket> socket); 
    static void write(shared_ptr<tcp::socket> socket, Data content); 
};

#endif
