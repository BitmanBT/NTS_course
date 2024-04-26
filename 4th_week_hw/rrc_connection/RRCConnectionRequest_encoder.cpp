#include "RRCConnectionRequest_encoder.h"

void RRCConnectionRequest_encoder(uint8_t **buffer, ssize_t *len)
{
    RRCConnectionRequest_t req;
    uint8_t buf[1], buf2=0;
    req.criticalExtensions.present = RRCConnectionRequest__criticalExtensions_PR_rrcConnectionRequest_r8;
    req.criticalExtensions.choice.rrcConnectionRequest_r8.ue_Identity.present = InitialUE_Identity_PR_randomValue;
    req.criticalExtensions.choice.rrcConnectionRequest_r8.ue_Identity.choice.randomValue.size = 1;
    req.criticalExtensions.choice.rrcConnectionRequest_r8.ue_Identity.choice.randomValue.bits_unused = 7;
    req.criticalExtensions.choice.rrcConnectionRequest_r8.ue_Identity.choice.randomValue.buf = buf;
    req.criticalExtensions.choice.rrcConnectionRequest_r8.establishmentCause = EstablishmentCause_mo_Signalling; //EstablishmentCause_mo_Data;
    req.criticalExtensions.choice.rrcConnectionRequest_r8.spare.buf = &buf2;
    req.criticalExtensions.choice.rrcConnectionRequest_r8.spare.size=1;
    req.criticalExtensions.choice.rrcConnectionRequest_r8.spare.bits_unused = 7;

    asn_encode_to_new_buffer_result_t res = {NULL, {0, NULL, NULL}};
    res = asn_encode_to_new_buffer(NULL, ATS_CANONICAL_XER, &asn_DEF_RRCConnectionRequest, &req);
    printf("%d\n", sizeof(res));
    printf("%d\n", strlen((const char*)res.buffer));
    free(res.buffer);
    memset(&res, 0, sizeof(res));
    res = asn_encode_to_new_buffer(NULL, ATS_ALIGNED_CANONICAL_PER, &asn_DEF_RRCConnectionRequest, &req);
    *buffer = (uint8_t*)res.buffer;
    *len = res.result.encoded;

    xer_fprint(stdout, &asn_DEF_RRCConnectionRequest, &req);
}