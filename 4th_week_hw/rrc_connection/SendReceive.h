#pragma once

#include <stdlib.h>
#include <string.h>
#include <asn_application.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/sctp.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void tx_send(uint8_t **buffer, ssize_t *len, uint16_t port);
void rx_receive(uint8_t **buffer, ssize_t *len, uint16_t port);