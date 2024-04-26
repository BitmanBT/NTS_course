#pragma once

#include <stdlib.h>
#include <string.h>
#include <asn_application.h>
#include <per_encoder.h>
#include <RRCConnectionSetupComplete.h>
#include <stdio.h>

void RRCConnectionSetupComplete_encoder(uint8_t **buffer, ssize_t *len);