#include "Request.h"
#include <cstring> // memcpy
using namespace std;

Request::Request(size_t s):
  _bodySize(s) 
{
  _data = new char[header_length + _bodySize];
}

Request::~Request()
{
  delete [] _data;
}

char* Request::data()
{
  return _data;
}

size_t Request::totalSize() const
{
  return header_length + _bodySize;
}

size_t Request::bodySize() const
{
  return _bodySize;
}

char* Request::body()
{
  return _data + header_length;
}

void Request::addBody(const char* bodyData)
{
  memcpy(body(), bodyData, _bodySize);
}

void Request::encodeHeader()
{
  memcpy(_data, &_bodySize, sizeof(size_t));
}

void Request::decodeHeader()
{
  memcpy(&_bodySize, _data, sizeof(size_t));

  char* temp = new char[header_length + _bodySize];
  memcpy(temp, _data, header_length);
  delete [] _data;
  _data = temp;
}

