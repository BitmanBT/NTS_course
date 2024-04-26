#include "SendReceive.h"

void tx_send(uint8_t **buffer, ssize_t *len, uint16_t port) {
    struct sockaddr_in servaddr = { AF_INET, htons(port), {inet_addr("127.0.0.1")}, {0} };

    int sockfd;

    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP);
    if (sockfd < 0) {
        printf("Error when opening socket\n");
        exit(1);
    }

    int ret = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    if (ret < 0) {
        printf("Error when connecting socket\n");
        exit(1);
    }

    ret = sctp_sendmsg(sockfd, *buffer, *len, NULL, 0, 0, 0, 0, 0, 0);
    if (ret < 0) {
        printf("Error when sending msg\n");
        exit(1);
    }

    printf("Sent packet\n");

    close(sockfd);
}

void rx_receive(uint8_t **buffer, ssize_t *len, uint16_t port)
{
    struct sockaddr_in servaddr = { AF_INET, htons(port), {inet_addr("127.0.0.1")}, {0} };

    *buffer = (uint8_t *)calloc(1, sizeof(uint8_t));

    int sockfd = socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP);
    if (sockfd < 0) {
        printf("Error when opening the socket\n");
        exit(1);
    }

    int bind_err = bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    if (bind_err < 0) {
        printf("Error when binding to the socket\n");
        exit(1);
    }

    int listen_err = listen(sockfd, 2);
    if (listen_err < 0) {
        printf("Error when listening to the socket\n");
        exit(1);
    }

    int received_err = sctp_recvmsg(sockfd, *buffer, *len, NULL, NULL, 0, 0);
    if (received_err < 0) {
        printf("Error when receiving msg\n");
        exit(1);
    }

    printf("Received packet\n");

    close(sockfd);
}