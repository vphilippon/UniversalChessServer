# Not-My-Laziest Make file

CXX_FLAGS = -std=c++11
SERVER_OBJECT = Server.o Protocol.o Request.o Game.o Knight.o Bishop.o Piece.o Pawn.o Queen.o King.o Rook.o
SIMPLECLIENT_OBJECT = SimpleClient.o Protocol.o Request.o

all: Server SimpleClient

Server: $(SERVER_OBJECT)
	g++ -o Server $(SERVER_OBJECT) -lboost_system -lpthread -lboost_thread -lboost_serialization

SimpleClient: $(SIMPLECLIENT_OBJECT)
	g++ -o SimpleClient $(SIMPLECLIENT_OBJECT) -lboost_system -lpthread -lboost_serialization

%.o: %.cpp
	g++ -c $< -o $@ $(CXX_FLAGS)

clean:
	rm -rf *.o Server SimpleClient
