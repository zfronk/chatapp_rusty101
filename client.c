#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>

#define IP_ADDRESS "127.0.0.1"
#define PORT_NUMBER 3000

int main(){
	// Create the client socket
	int client_socket = socket(AF_INET, SOCK_STREAM, 0);

	if(client_socket < 0){
		perror("Opps couldn't create clinet socket!");
		exit(EXIT_FAILURE);
	} 


	// Configure the server address it will connecting to
	struct sockaddr_in server_address;

	server_address.sin_port = htons(PORT_NUMBER); // Change port number to network form
	server_address.sin_family = AF_INET;

	int ip_conversion = inet_pton(AF_INET, IP_ADDRESS, &server_address.sin_addr); // Convert the ip address to network format!

	if(ip_conversion <= 0){
		perror("Invalid IP ADDRESS!");
		close(client_socket);
		exit(EXIT_FAILURE);

	}

	printf("IP Address converted to network type!\n");

	if(connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0){
		perror("Opps couldn't connect to targeted server!");
		close(client_socket);
		exit(EXIT_FAILURE);

	}

	printf("Connected to server!\n");
	printf("\n");
	
	// Loop to ensure messages are sent back and forth "Client -> Server protocol"
	char client_buffer[1024];
	char admin_buffer[1024];
	
	while(1){
		printf("Client: ");

		fgets(client_buffer, sizeof(client_buffer), stdin); // Get the buffer form inside in put...
		int index_to_newline = strcspn(client_buffer, "\n");

		client_buffer[index_to_newline] = '\0'; // Remove the new line character!

		if(send(client_socket, client_buffer, strlen(client_buffer), 0) < 0){
			perror("Failed to send messageto server!\n");
			close(client_socket);
			exit(EXIT_FAILURE);
			break;
			
		}


		int bytes_recieved = recv(client_socket, admin_buffer, sizeof(admin_buffer), 0);
		admin_buffer[bytes_recieved] = '\0'; // Null terminate the admin message!

		if(bytes_recieved <= 0){
			perror("Opps server offline/ Error occured!");
			close(client_socket);
			break;
			
		}

		printf("Admin says: %s", admin_buffer);

		memset(client_buffer, 0, sizeof(client_buffer));
		memset(admin_buffer, 0, sizeof(admin_buffer));
		
	}

	close(client_socket);
	
	return 0;
	
}
