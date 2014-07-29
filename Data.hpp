/******************************************************************************
  Data.hpp
  =====================
  Original author : Julian Bironneau and Vincent Philippon
  Original creation date : 2014-01-08

  This class represents the data transefered between the Server and the Client
  application. It can be serialized using the boost lib and te sent using
  a tcp::socket.
 *****************************************************************************/

#ifndef DATA_HPP_
#define DATA_HPP_

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class Data
{
  // Public, this is almost actually a struct.
  public:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)   
    {
      ar & status;
      ar & team;
      ar & xFrom;
      ar & yFrom;
      ar & xTo;
      ar & yTo;
      ar & promotionChoice;
    }

    enum Status
    {
      ok = 0,
      checkOnly = 1,
      checkMate = 2,
      draw = 3,
      promotion = 4,
      rejected = -1
    };

    Status status;
    int team;
    int xFrom;
    int yFrom;
    int xTo;
    int yTo;
    char promotionChoice;

    Data():
      status(ok), xFrom(0), yFrom(0), xTo(0), yTo(0), promotionChoice(' ') {}
};

#endif

