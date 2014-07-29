/******************************************************************************
  Protocol.hpp
  =====================
  Original author : Julian Bironneau and Vincent Philippon
  Original creation date : 2014-04-08

  This class is used do wrap around the data sent and read on a tcp::socket.
  Using a fixed-size header, the reader can read the exact right number of 
  bytes.
 *****************************************************************************/

#ifndef REQUEST_HPP_
#define REQUEST_HPP_

#include <cstdlib>

class Request
{
  public:
    enum { header_length = sizeof(size_t) };

  private:
    size_t _bodySize;
    char* _data;

  public:
    Request(size_t s = 0);
    ~Request();

    char* data();
    size_t totalSize() const;
    size_t bodySize() const;
    char* body();
    void addBody(const char* bodyData);
    void encodeHeader();
    void decodeHeader();
};

#endif
