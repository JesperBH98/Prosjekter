#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "ewpdef.h"

#define BUFFER_SIZE 10000

// Converts a 4-byte ASCII size header to an integer
int parse_size_header(struct EWA_EXAM25_TASK5_PROTOCOL_SIZEHEADER *header) {
	char temp[5];
    	memcpy(temp, header->acDataSize, 4);
    	temp[4] = '\0';
    	return atoi(temp);
}

// Set 4-byte ASCII size header with no padding and no null terminator, 006 fix
void set_size_header(char *acDataSize, size_t size) {
    	char sizebuf[5];
    	snprintf(sizebuf, sizeof(sizebuf), "%04lu", (unsigned long)size);
    	memcpy(acDataSize, sizebuf, 4);
}

// Send standard protocol for server reply, handles header and body format
void send_reply(int client_fd, const char* code, const char* message) {
    	struct EWA_EXAM25_TASK5_PROTOCOL_SERVERREPLY reply;
    	memset(&reply, 0, sizeof(reply));

    	// Header field
    	strncpy(reply.stHead.acMagicNumber, "EWP", 3);
    	set_size_header(reply.stHead.acDataSize, sizeof(reply));
    	reply.stHead.acDelimeter[0] = '|';

    	// Body field
    	strncpy(reply.acStatusCode, code, 3);
    	reply.acHardSpace[0] = ' ';
    	strncpy(reply.acFormattedString, message, sizeof(reply.acFormattedString) - 1);
    	reply.acHardZero[0] = 0;

    	send(client_fd, &reply, sizeof(reply), 0);
}

int main(int argc, char *argv[]) {
	int port = -1;
    	char id[256] = "";

    	// Parse command line arguments -port and -id
    	for (int i = 1; i < argc; i++) {
        	if (strcmp(argv[i], "-port") == 0 && i + 1 < argc) {
            		port = atoi(argv[++i]);
        	} else if (strcmp(argv[i], "-id") == 0 && i + 1 < argc) {
            		strncpy(id, argv[++i], sizeof(id) - 1);
        	}
    	}

    	if (port < 0 || strlen(id) == 0) {
        fprintf(stderr, "Usage: %s -port <port> -id <ID>\n", argv[0]);
        exit(1);
    	}

    	printf("Starting server on port %d with ID: %s\n", port, id);

    	// Creates the TCP socket for the connections that are incoming
    	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    	if (server_fd < 0) {
        	perror("socket");
        	exit(1);
    	}

    	// Binds socket to localhost and the specified port
    	struct sockaddr_in server_addr;
    	memset(&server_addr, 0, sizeof(server_addr));
    	server_addr.sin_family = AF_INET;
    	server_addr.sin_port = htons(port);
    	inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    	if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        	perror("bind");
        	close(server_fd);
        	exit(1);
    	}
	// Listening for a single client at the time
    	if (listen(server_fd, 1) < 0) {
        	perror("listen");
        	close(server_fd);
        	exit(1);
    	}

    	printf("Waiting for connection...\n");

    	struct sockaddr_in client_addr;
    	socklen_t client_len = sizeof(client_addr);
    	int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
    	if (client_fd < 0) {
        	perror("accept");
        	close(server_fd);
        	exit(1);
    	}

    	printf("Client connected\n");

    	// Notifying the client that the server is ready
    	send_reply(client_fd, EWA_EXAM25_TASK5_PROTOCOL_SERVERREPLY_OK, "Server Ready");

    	char buffer[BUFFER_SIZE];
    	ssize_t bytes_read;
    	char last_filename[256] = ""; // Storing filename from DATA command
	
	// The main server loop that process the incoming messages
    	while ((bytes_read = recv(client_fd, buffer, sizeof(buffer), 0)) > 0) {
        	printf("Received %ld bytes\n", bytes_read);
	// Ignores the messages that are too short to have a header
        	if (bytes_read < sizeof(struct EWA_EXAM25_TASK5_PROTOCOL_SIZEHEADER)) {
            fprintf(stderr, "Received too little data, skipping...\n");
            continue;
        }

        // Casts buffer to all the possible protocol message types
        struct EWA_EXAM25_TASK5_PROTOCOL_SIZEHEADER *size_header =
            (struct EWA_EXAM25_TASK5_PROTOCOL_SIZEHEADER *)buffer;
        struct EWA_EXAM25_TASK5_PROTOCOL_CLIENTHELO *helo =
            (struct EWA_EXAM25_TASK5_PROTOCOL_CLIENTHELO *)buffer;
        struct EWA_EXAM25_TASK5_PROTOCOL_MAILFROM *mail_from =
            (struct EWA_EXAM25_TASK5_PROTOCOL_MAILFROM *)buffer;
        struct EWA_EXAM25_TASK5_PROTOCOL_RCPTTO *rcpt_to =
            (struct EWA_EXAM25_TASK5_PROTOCOL_RCPTTO *)buffer;
        struct EWA_EXAM25_TASK5_PROTOCOL_CLIENTDATACMD *data_cmd =
            (struct EWA_EXAM25_TASK5_PROTOCOL_CLIENTDATACMD *)buffer;
        struct EWA_EXAM25_TASK5_PROTOCOL_CLOSECOMMAND *quit =
            (struct EWA_EXAM25_TASK5_PROTOCOL_CLOSECOMMAND *)buffer;

        int total_size = parse_size_header(size_header);

	// Skipping incomplete messages
        if (total_size > bytes_read) {
            fprintf(stderr, "Warning: incomplete message, expected %d bytes, got %ld\n",
                total_size, bytes_read);
            continue;
        }

        // HELO command handling, greeting client
        if (strncmp(helo->acCommand, "HELO", 4) == 0) {
            printf("HELO received: %s\n", helo->acFormattedString);

            struct EWA_EXAM25_TASK5_PROTOCOL_SERVERHELO reply;
            memset(&reply, 0, sizeof(reply));
            strncpy(reply.acStatusCode, EWA_EXAM25_TASK5_PROTOCOL_SERVERREPLY_OK, 3);
            reply.acHardSpace[0] = ' ';
            snprintf(reply.acFormattedString, sizeof(reply.acFormattedString),
                "127.0.0.1 Hello %s", helo->acFormattedString);
            reply.acHardZero[0] = 0;
            strncpy(reply.stHead.acMagicNumber, "EWP", 3);
            set_size_header(reply.stHead.acDataSize, sizeof(reply));
            reply.stHead.acDelimeter[0] = '|';
            send(client_fd, &reply, sizeof(reply), 0);
            continue;
        }

        // Handling MAIL from the command, acknowledges the senders address
        if (strncmp(mail_from->acCommand, "MAIL FROM:", 10) == 0) {
            printf("MAIL FROM received: %s\n", mail_from->acFormattedString);
            send_reply(client_fd, EWA_EXAM25_TASK5_PROTOCOL_SERVERREPLY_OK, "Sender address ok");
            continue;
        }

        // Handling RCPT command, acknowledges the recipients address
        if (strncmp(rcpt_to->acCommand, "RCPT TO:", 8) == 0) {
            printf("RCPT TO received: %s\n", rcpt_to->acFormattedString);
            send_reply(client_fd, EWA_EXAM25_TASK5_PROTOCOL_SERVERREPLY_OK, "Recipient address ok");
            continue;
        }

        // Data command handling, prepares to receive file, and store the given filename
        if (strncmp(data_cmd->acCommand, "DATA", 4) == 0) {
            printf("DATA command received for file: %s\n", data_cmd->acFormattedString);
            strncpy(last_filename, data_cmd->acFormattedString, sizeof(last_filename) - 1);
            send_reply(client_fd, EWA_EXAM25_TASK5_PROTOCOL_SERVERREPLY_READY, "Ready for message");

            // Receives the file as the next protocol message
            ssize_t file_bytes = recv(client_fd, buffer, sizeof(buffer), 0);
            if (file_bytes > 0) {
                struct EWA_EXAM25_TASK5_PROTOCOL_CLIENTDATAFILE *file_msg =
                    (struct EWA_EXAM25_TASK5_PROTOCOL_CLIENTDATAFILE *)buffer;
                int msg_size = parse_size_header(&file_msg->stHead);
                int content_size = msg_size - sizeof(struct EWA_EXAM25_TASK5_PROTOCOL_SIZEHEADER);

                printf("Received file data of %ld bytes (header says %d, content is %d)\n",
                       file_bytes, msg_size, content_size);

                // Saving the file recived file using filename from the data command
                FILE *f = fopen(last_filename, "wb");
                if (f) {
                    fwrite(file_msg->acFileContent, 1, content_size, f);
                    fclose(f);
                    printf("Saved file to %s\n", last_filename);
                } else {
                    printf("Failed to save file to %s\n", last_filename);
                }

                send_reply(client_fd, EWA_EXAM25_TASK5_PROTOCOL_SERVERREPLY_OK, "Message accepted");
            }
            continue;
        }

        // QUIT command handling, this closes the session between the server and client
        if (strncmp(quit->acCommand, "QUIT", 4) == 0) {
            printf("QUIT command received\n");
            send_reply(client_fd, EWA_EXAM25_TASK5_PROTOCOL_SERVERREPLY_CLOSED, "Goodbye");
            break;
        }

        // If unknown or unsupported command/format
        fprintf(stderr, "Unknown command or unsupported format\n");
    }
	// Cleaning the resources that are in use and closes the server
	close(client_fd);
    	close(server_fd);
    	printf("Server shut down.\n");
    	return 0;
}

