#include "RRCConnectionSetupComplete_encoder.h"

void RRCConnectionSetupComplete_encoder(uint8_t **buffer, ssize_t *len)
{
    RRCConnectionSetupComplete complete;
    complete.rrc_TransactionIdentifier = 1;
    complete.criticalExtensions.present = RRCConnectionSetupComplete__criticalExtensions_PR_c1;
    complete.criticalExtensions.choice.c1.present = RRCConnectionSetupComplete__criticalExtensions__c1_PR_rrcConnectionSetupComplete_r8;
    complete.criticalExtensions.choice.c1.choice.rrcConnectionSetupComplete_r8.selectedPLMN_Identity= 0;
    memset(&complete.criticalExtensions.choice.c1.choice.rrcConnectionSetupComplete_r8.dedicatedInfoNAS,0,sizeof(OCTET_STRING_t));

    asn_encode_to_new_buffer_result_t res = {NULL, {0, NULL, NULL}};
    res = asn_encode_to_new_buffer(NULL, ATS_CANONICAL_XER, &asn_DEF_RRCConnectionSetupComplete, &complete);
    printf("%d\n", sizeof(res));
    printf("%d\n", strlen((const char*)res.buffer));
    free(res.buffer);
    memset(&res, 0, sizeof(res));
    res = asn_encode_to_new_buffer(NULL, ATS_ALIGNED_CANONICAL_PER, &asn_DEF_RRCConnectionSetupComplete, &complete);
    *buffer = (uint8_t*)res.buffer;
    *len = res.result.encoded;

    xer_fprint(stdout, &asn_DEF_RRCConnectionSetupComplete, &complete);
}