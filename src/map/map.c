#include <stdio.h>
#include <time.h>
#include <obliv.oh>

#include "map.h"

#define RED   "\x1B[0;31m"
#define GRN   "\x1B[0;32m"
#define YEL   "\x1B[0;33m"
#define BLU   "\x1B[0;34m"
#define MAG   "\x1B[0;35m"
#define CYN   "\x1B[0;36m"
#define WHT   "\x1B[0;37m"
#define RESET "\x1B[0m"

clock_t t;

void protocolIOPrint(ProtocolIO *io) {
  (io->party.id == 1) ? fprintf(stderr, GRN) : fprintf(stderr, BLU);
  #ifndef DEBUG
  fprintf(stderr, "party: %d, input: <%d, %d, %d>, result: <%d, %d> <%d, %d>\n", io->party.id, io->input.command, io->input.key, io->input.value, io->result.key1, io->result.val1);
  #else
  fprintf(stderr, "party: %d, input: <%d, %d, %d>, result: <%d, %d> <%d, %d>\n", io->party.id, io->input.command, io->input.key, io->input.value, io->result.key1, io->result.val1, io->result.key2, io->result.val2);
  fprintf(stderr, "party: %d, debugPrevState: %d ", io->party.id, io->debugPrevState.len);
  for (int i = 0; i < io->debugPrevState.len; ++i) {
    fprintf(stderr, "<%d,%d> ", io->debugPrevState.karray[i], io->debugPrevState.varray[i]);
  }
  fprintf(stderr, "\n");
  fprintf(stderr, "party: %d, debugState: %d ", io->party.id, io->debugState.len);
  for (int i = 0; i < io->debugState.len; ++i) {
    fprintf(stderr, "<%d,%d> ", io->debugState.karray[i], io->debugState.varray[i]);
  }
  fprintf(stderr, "\n");
  fprintf(stderr,"GateCount: %u\n",yaoGateCount());
  if (t == 0) {
    t = clock();
  } else {
    fprintf(stderr,"Time: %f\n",(double)(clock() - t) / CLOCKS_PER_SEC);
    t = clock();
  }
  #endif
  fprintf(stderr, RESET);
  return;
}
