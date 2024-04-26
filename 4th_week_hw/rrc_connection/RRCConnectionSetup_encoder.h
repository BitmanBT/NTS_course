#pragma once

#include <stdlib.h>
#include <string.h>
#include <asn_application.h>
#include <per_encoder.h>
#include <RRCConnectionSetup.h>
#include <stdio.h>

void RRCConnectionSetup_encoder(uint8_t **buffer, ssize_t *len);