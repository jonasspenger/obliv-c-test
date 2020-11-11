#ifndef OBLIVSTATEFUN_H
#define OBLIVSTATEFUN_H

void setupJJYaoProtocol(ProtocolDesc* pd);
void mainJJYaoProtocol(ProtocolDesc* pd, protocol_run start, void* arg);
void cleanupJJYaoProtocol(ProtocolDesc* pd);
void setupIntermediateJJYaoProtocol(ProtocolDesc* pd);
void cleanupIntermediateJJYaoProtocol(ProtocolDesc* pd);

#endif // OBLIVSTATEFUN_H
