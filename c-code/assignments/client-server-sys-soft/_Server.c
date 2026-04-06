/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

// error function
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

// simple math functions
void doAddition(int num1, int num2, long *answer) {
    *answer = num1 + num2;
}

void doSubtraction(int num1, int num2, long *answer) {
    *answer = num1 - num2;
}

void doMultiplication(int num1, int num2, long *answer) {
    *answer = num1 * num2;
}

void doDivision(int num1, int num2, long *answer) {
    if (num2 == 0)
        printf("%s\n", "Divide by Zero error.");
        exit(0);
    *answer = num1 / num2;
}

// math function
void operationDispatcher(int *num1, int *num2, char *operator, long *answer) {
    switch(*operator) {
        case ('+'):
            doAddition(*num1, *num2, answer);
            break;
        case ('-'):
            doSubtraction(*num1, *num2, answer);
            break;
        case ('*'):
            doMultiplication(*num1, *num2, answer);
            break;
        case ('/'):
            doDivision(*num1, *num2, answer);
            break;
        default:
            printf("%s\n", "Invalid operator...");
            exit(0);
    }
}

void parseNumbers(int * num1, int * num2, char * operator, char response[]) {
    int isN1 = 0, isN2 = 0, currentIndexer = 0;
    char num1Char[12] = {0}, num2Char[12] = {0};

    for (int i = 0; response[i] != '\0'; i++) {
        if (response[i] == '\n') continue;

        if (response[i] == ' ') {
            // conditionly change state
            if (isN1 != 1) {
                isN1 = 1;
            } else {
                isN2 = 1;
            }
            currentIndexer = 0;
            continue;
        }

        if (isN1 == 0) {
            // append to number 1
            num1Char[currentIndexer] = response[i];
        } else if (isN2 == 0) {
            // append to number 2
            num2Char[currentIndexer] = response[i];
        } else {
            // set operator
            *operator = response[i];
        }
        
        currentIndexer++;
    }

    // end of string, check that all values are properly extracted
    if (isN1 == 0 || isN2 == 0) {
        printf("%s\n", "Invalid format...");
        exit(0);
    }

    // convert char arrays to numbers
    *num1 = atoi(num1Char);
    *num2 = atoi(num2Char);
}

// run ./server
int main()
{
    // define values
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    // define socket information
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
    error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));

    // define connection information
    portno = 4555;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    // bind server to socket
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        error("ERROR on binding");

    // listen to the socket
    listen(sockfd,5);

    // Create new client connection
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0) 
        error("ERROR on accept");
    
    // read buffer from socket
    bzero(buffer,256);
    n = read(newsockfd,buffer,255);
    if (n < 0) error("ERROR reading from socket");

    // define vars
    long ans = 0;
    int num1, num2;
    char operator;
    char ansMessage[256];

    // parse values from buffer
    parseNumbers(&num1, &num2, &operator, buffer);
    // send the numbers to the appropriate math function
    operationDispatcher(&num1, &num2, &operator, &ans);
    // Build the answer message
    sprintf(ansMessage, "Answer = %ld", ans);
    // right to socket
    n = write(newsockfd, ansMessage, strlen(ansMessage));
    if (n < 0) error("ERROR writing to socket");

    // CLOSE everything
    close(newsockfd);
    close(sockfd);

    return 0; 
}