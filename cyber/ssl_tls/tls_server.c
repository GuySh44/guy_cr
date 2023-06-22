
#include <stdio.h> /**/
#include <unistd.h> /**/
#include <string.h> /**/
#include <signal.h> /**/
#include <sys/socket.h> /* sockaddr socket bind listen */
#include <arpa/inet.h> /**/
#include <openssl/ssl.h> /**/
#include <openssl/err.h> /**/
#include <netdb.h> /**/
#include <netinet/in.h> /**/
#include <sys/types.h>  /* SSL_CTX */

#define BUFSIZE 1024

int create_socket(int port)
{
    int s;
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) 
    {
        perror("Unable to create socket");
        exit(EXIT_FAILURE);
    }

    if (bind(s, (struct sockaddr*)&addr, sizeof(addr)) < 0) 
    {
        perror("Unable to bind");
        exit(EXIT_FAILURE);
    }

    if (listen(s, 1) < 0) 
    {
        perror("Unable to listen");
        exit(EXIT_FAILURE);
    }

    return s;
}

/* SSL context struct holding various members regarding certificates, algorithms etc. */
SSL_CTX *create_context()
{
    const SSL_METHOD *method;
    SSL_CTX *ctx;

    /* TLS_server_method is a protocol version FLEXIBLE method, supporting multiple TLS connection versions */
    method = TLS_server_method();

    ctx = SSL_CTX_new(method);
    if (!ctx) 
    {
        perror("Unable to create SSL context");
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    return ctx;
}

void configure_context(SSL_CTX *ctx)
{
    /* Set the key and cert */
    if (SSL_CTX_use_certificate_file(ctx, "/home/kali/infinity/ssl_tls/ssl_tls.crt", SSL_FILETYPE_PEM) <= 0) 
    {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    if (SSL_CTX_use_PrivateKey_file(ctx, "/home/kali/infinity/ssl_tls/ssl_tls.key", SSL_FILETYPE_PEM) <= 0 ) 
    {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv)
{
    int n; /* message byte size */
    int sock;
    SSL_CTX *ctx;
    char buf[BUFSIZE]; /* message buffer */

    /* Ignore broken pipe signals */
    signal(SIGPIPE, SIG_IGN);

    ctx = create_context();

    configure_context(ctx);

    sock = create_socket(443);

    /* Handle connections */
    while(1) {
        struct sockaddr_in addr;
        unsigned int len = sizeof(addr);
        SSL *ssl;

        int client = accept(sock, (struct sockaddr*)&addr, &len);
        if (client < 0) 
        {
            perror("Unable to accept");
            exit(EXIT_FAILURE);
        }

        ssl = SSL_new(ctx);
        SSL_set_fd(ssl, client);

        if (SSL_accept(ssl) <= 0) 
        {
            ERR_print_errors_fp(stderr);
        } 
        else 
        {
            /* read: read input string from the client */
            memset(buf, 0, BUFSIZE);
            n = SSL_read(ssl, buf, BUFSIZE);
            if (n < 0)
            {
                perror("ERROR reading from socket");
            }
            /* write: echo the input string back to the client */
            n = SSL_write(ssl, buf, strlen(buf));
            if (n < 0) 
            {
                perror("ERROR writing to socket");
            }
        }

        SSL_shutdown(ssl);
        SSL_free(ssl);
        close(client);
    }

    close(sock);
    SSL_CTX_free(ctx);

    return 0;
    (void)argc;
    (void)argv;
}
