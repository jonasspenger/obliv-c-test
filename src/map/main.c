#include <stdio.h>
#include <stdlib.h>
#include <obliv.h>

#include "oblivstatefun.h"
#include "map.h"

int main(int argc,char* argv[]) {
  ProtocolDesc pd;
  ProtocolIO io;

  // parse inputs
  #ifdef STDIO
  if (argc < 4) {
   fprintf(stderr,"Usage: %s <Party> <Command> <Key> <Value>\n", argv[0]);
   fprintf(stderr,"Party: <1|2>\n");
   fprintf(stderr,"Command: <1|2|3> -- 1=Get 2=Set 3=Clear\n");
   fprintf(stderr,"Key: Int\n");
   fprintf(stderr,"Value: Int\n");
   fprintf(stderr,"Example stdio: %s 1 1 2 3\n", argv[0]);
   fprintf(stderr,"Multi-party stdio example: mkfifo temp_fifo; %1$s 1 1 2 3 < temp_fifo | %1$s 2 1 3 4 > temp_fifo; rm temp_fifo;\n", argv[0]);
   return 1;
  }
  #endif
  #ifdef TCPIO
  if (argc < 4) {
   fprintf(stderr,"Usage: %s <Party> <Host> <Port>\n", argv[0]);
   fprintf(stderr,"Party: <1|2>\n");
   fprintf(stderr,"Host: <localhost|IP>\n");
   fprintf(stderr,"Port: Int\n");
   fprintf(stderr,"Example tcpio: %s 1 localhost 3897\n", argv[0]);
   fprintf(stderr,"Multi-party tcpio example: echo -e \"1 1 1 1 1 2 1 2 2 2 1 1 3 2 0 4 0 0 5 0 0 1 1 1\" | ./a.out 1 localhost 3897 & echo -e \"1 3 3 1 3 4 1 4 4 2 3 3 3 4 0 4 0 0 5 0 0 1 2 2\" | ./a.out 2 localhost 3897;\n", argv[0]);
   return 1;
  }
  #endif

  io.party.id = atoi(argv[1]);
  #ifdef STDIO
  io.input.command = atoi(argv[2]);
  io.input.key = atoi(argv[3]);
  io.input.value = atoi(argv[4]);
  #endif
  #ifdef TCPIO
  strcpy(io.host, argv[2]);
  strcpy(io.port, argv[3]);
  #endif

  // select input
  #ifdef STDIO
  protocolUseStdio(&pd);
  #endif
  #ifdef TCPIO
  if (io.party.id == 1) {
    if(protocolAcceptTcp2P(&pd, io.port) != 0) {
      fprintf(stderr,"TCP connection error\n"); return 1;
    }
  } else if (io.party.id == 2) {
    if(protocolConnectTcp2P(&pd, io.host, io.port) != 0) {
      fprintf(stderr,"TCP connection error\n"); return 1;
    }
  }
  #endif

    // set current party
  setCurrentParty(&pd, io.party.id);

  // setup protocol instance
  setupJJYaoProtocol(&pd);

  // run initialize state
  mainJJYaoProtocol(&pd, mapsetup, &io);

  #ifdef STDIO
  // run first round
  mainJJYaoProtocol(&pd, mapexec, &io);
  protocolIOPrint(&io); // print results
  #endif
  #ifdef TCPIO
  // run rounds
  int command;
  int key;
  int value;
  while (scanf("%d %d %d", &command, &key, &value) == 3) {
    io.input.command = command;
    io.input.key = key;
    io.input.value = value;
    setupIntermediateJJYaoProtocol(&pd);
    mainJJYaoProtocol(&pd, mapexec, &io);
    protocolIOPrint(&io); // print results
    cleanupIntermediateJJYaoProtocol(&pd);
  }
  #endif
  // // clean up
  cleanupJJYaoProtocol(&pd);
  cleanupProtocol(&pd);
  return 0;
}
