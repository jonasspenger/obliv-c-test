#include <obliv.h>
#include <obliv_bits.c>

#include "oblivstatefun.h"

// adapted from setupYaoProtocol obliv_bits.c
void setupJJYaoProtocol(ProtocolDesc* pd) {
  setupYaoProtocol(pd,true);
  YaoProtocolDesc* ypd = pd->extra;
  int me = pd->thisParty;
  ypd->ownOT=false;
  ypd->gcount = ypd->gcount_offset = ypd->icount = ypd->ocount = 0;
  if(me==1) {
    gcry_randomize(ypd->R,YAO_KEY_BYTES,GCRY_STRONG_RANDOM);
    gcry_randomize(ypd->I,YAO_KEY_BYTES,GCRY_STRONG_RANDOM);
    if(true) ypd->R[0] |= 1; // flipper bit
    if(ypd->sender.sender==NULL) {
      ypd->ownOT=true;
      ypd->sender = honestOTExtSenderAbstract(honestOTExtSenderNew(pd,2));
    }
  } else if(ypd->recver.recver==NULL) {
    ypd->ownOT=true;
    ypd->recver = honestOTExtRecverAbstract(honestOTExtRecverNew(pd,1));
  }
  currentProto = pd;
}

// adapted from mainYaoProtocol obliv_bits.c
void mainJJYaoProtocol(ProtocolDesc* pd, protocol_run start, void* arg) {
  start(arg);
}

// adapted from cleanupYaoProtocol obliv_bits.c
void cleanupJJYaoProtocol(ProtocolDesc* pd) {
  cleanupYaoProtocol(pd);
}

// custom setupIntermediateJJYaoProtocol
// currently, completely restart Yao protocol in order inherit security for multi-round
void setupIntermediateJJYaoProtocol(ProtocolDesc* pd) {
  setupJJYaoProtocol(pd);
}

// custom cleanupIntermediateJJYaoProtocol
// adapted from cleanupYaoProtocol obliv_bits.c
void cleanupIntermediateJJYaoProtocol(ProtocolDesc* pd) {
  YaoProtocolDesc* ypd = pd->extra;
  ypd->gcount=0;
  ypd->gcount_offset=0;
  ypd->icount=0;
  ypd->ocount=0;
  return;
}
