#ifndef MAP_H
#define MAP_H

#define DEBUG
// #define STDIO
#define TCPIO
#if !defined STDIO && !defined TCPIO
#error one of STDIO or TCPIO must be defined
#endif

typedef struct KeyValueVector {
  int len;
  obliv int* karray;
  obliv int* varray;
} KeyValueVector;

typedef struct ProtocolState {
  KeyValueVector kvvector;
  char* serializedstate;
  char* r;
} ProtocolState;

typedef struct ProtocolDebugState {
  int len;
  int* karray;
  int* varray;
} ProtocolDebugState;

typedef struct ProtocolParty {
  int id;
} ProtocolParty;

typedef struct ProtocolInput {
  int command;
  int key;
  int value;
} ProtocolInput;

typedef struct ProtocolResult {
  int key1;
  int val1;
  int key2;
  int val2;
} ProtocolResult;

typedef struct ProtocolIO {
  ProtocolParty party;
  ProtocolInput input;
  ProtocolResult result;
  ProtocolState ps;
  ProtocolDebugState debugState;
  ProtocolDebugState debugPrevState;
  char host[16];
  char port[16];
} ProtocolIO;

void protocolIOPrint(ProtocolIO *io);
void mapsetup(void* args);
void mapexec(void* args);

#endif // MAP_H
