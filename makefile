# Not-My-Laziest Make file

CXX=g++
CXXFLAGS=-std=c++11
SERVER_OBJECT=Server.o Protocol.o Request.o Game.o Knight.o Bishop.o Piece.o Pawn.o Queen.o King.o Rook.o
SIMPLECLIENT_OBJECT=SimpleClient.o Protocol.o Request.o

all: Server SimpleClient

Server: $(SERVER_OBJECT)
	$(CXX) -o Server $(SERVER_OBJECT) -lboost_system -lpthread -lboost_thread -lboost_serialization

SimpleClient: $(SIMPLECLIENT_OBJECT)
	$(CXX) -o SimpleClient $(SIMPLECLIENT_OBJECT) -lboost_system -lpthread -lboost_serialization

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm -rf *.o Server SimpleClient
