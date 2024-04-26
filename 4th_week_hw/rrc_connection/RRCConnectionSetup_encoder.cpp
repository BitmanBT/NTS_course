#include "RRCConnectionSetup_encoder.h"

void RRCConnectionSetup_encoder(uint8_t **buffer, ssize_t *len)
{
    RRCConnectionSetup_t setup;
    setup.rrc_TransactionIdentifier = 1;
    setup.criticalExtensions.present = RRCConnectionSetup__criticalExtensions_PR_c1;
    setup.criticalExtensions.choice.c1.present = RRCConnectionSetup__criticalExtensions__c1_PR_rrcConnectionSetup_r8;
    setup.criticalExtensions.choice.c1.present = RRCConnectionSetup__criticalExtensions__c1_PR_rrcConnectionSetup_r8 ;
    //setup.criticalExtensions.choice.c1.choice.rrcConnectionSetup_r8.radioResourceConfigDedicated.srb_ToAddModList = *SRB_configList;
    setup.criticalExtensions.choice.c1.choice.rrcConnectionSetup_r8.radioResourceConfigDedicated.drb_ToAddModList = NULL;
    setup.criticalExtensions.choice.c1.choice.rrcConnectionSetup_r8.radioResourceConfigDedicated.drb_ToReleaseList = NULL;
    setup.criticalExtensions.choice.c1.choice.rrcConnectionSetup_r8.radioResourceConfigDedicated.sps_Config = NULL;
    // setup.criticalExtensions.choice.c1.choice.rrcConnectionSetup_r8.radioResourceConfigDedicated.physicalConfigDedicated = physicalConfigDedicated2;


    asn_encode_to_new_buffer_result_t res = {NULL, {0, NULL, NULL}};
    res = asn_encode_to_new_buffer(NULL, ATS_CANONICAL_XER, &asn_DEF_RRCConnectionSetup, &setup);
    printf("%d\n", sizeof(res));
    printf("%d\n", strlen((const char*)res.buffer));
    free(res.buffer);
    memset(&res, 0, sizeof(res));
    res = asn_encode_to_new_buffer(NULL, ATS_ALIGNED_CANONICAL_PER, &asn_DEF_RRCConnectionSetup, &setup);
    *buffer = (uint8_t*)res.buffer;
    *len = res.result.encoded;

    xer_fprint(stdout, &asn_DEF_RRCConnectionSetup, &setup);
}