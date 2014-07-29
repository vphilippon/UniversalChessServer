/******************************************************************************
  Protocol.cpp
  =====================
  Original author : Julian Bironneau and Vincent Philippon
  Original creation date : 2014-04-08
  (See Protocol.hpp for details)
 *****************************************************************************/
#include "Protocol.hpp"
#include "Request.hpp"
#include <sstream> 

using namespace std;
using boost::asio::ip::tcp;

Data Protocol::read(shared_ptr<tcp::socket> socket)
{
  Request request;
  Data data;

  boost::asio::read(*socket,
      boost::asio::buffer(request.data(), request.header_length));
  request.decodeHeader();
  boost::asio::read(*socket,
      boost::asio::buffer(request.body(), request.bodySize()));

  string content = "";
  content.append(request.body(), request.bodySize());

  stringstream ss;
  ss.str(content);
  boost::archive::text_iarchive ia(ss);
  ia >> data;

  return data;
}

void Protocol::write(shared_ptr<tcp::socket> socket, Data data)
{
  stringstream ss;
  boost::archive::text_oarchive oa(ss);
  oa << data;

  string content = ss.str();

  Request request(content.length());
  request.addBody(content.c_str());
  request.encodeHeader();
  boost::asio::write(*socket, 
      boost::asio::buffer(request.data(), request.totalSize()));
}
