#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h> // For conversions
#include <unistd.h>
#include <netinet/in.h> // For struct calls
#include <string.h>


#define PORTNUMBER 3000 // Where the service will be hooked
#define BACKLOG 3 // Accept up to three connections

int main(){

	int server_socket_fd = socket(AF_INET, SOCK_STREAM, 0); // Create the socket

	// Is socket is not created...
	if(server_socket_fd < 0){
		perror("Error creating socket!");
		exit(EXIT_FAILURE); // Exit program with debug message
	}

	printf("Nice server socket created succesfully!\n");
	printf("Configuring socket address...\n");

	struct sockaddr_in server_address;
	
	// Configure the server address
	server_address.sin_port = htons(PORTNUMBER); // Port where the server is configured // Convert to network type
	server_address.sin_addr.s_addr = INADDR_ANY; // Allow connections from all interfaces
	server_address.sin_family = AF_INET; // Use version IPV4

	size_t server_address_length =  sizeof(server_address);

	// Bind the socket to configured address and port
	if(bind(server_socket_fd, (struct sockaddr*)&server_address, server_address_length) < 0){
		perror("Failed to bind socket to configured address");
		close(server_socket_fd); // Close the server socket if bind fails!
		exit(EXIT_FAILURE);

	}

	printf("Server socket bound to configured address and port!\n");

	// Listen for connections
	if(listen(server_socket_fd, BACKLOG) < 0){
		perror("Failed to listen to incoming connections\n");
		close(server_socket_fd);
		exit(EXIT_FAILURE);

	}

	printf("Listening for incoming connections at port %d...\n", PORTNUMBER);
	
	// Accept connecting clients // A loop just so i can keep accepting clients
	while(1){
		struct sockaddr_in client_address; // Struct to store client addresses
		socklen_t client_address_size = sizeof(client_address);

		int new_client_socket = accept(server_socket_fd, (struct sockaddr*)&client_address, &client_address_size); // Declare the new client socket

		if(new_client_socket < 0){
			perror("Failed to accept client!");			
			close(server_socket_fd);
			exit(EXIT_FAILURE);
		}

		char client_IP[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &(client_address.sin_addr), client_IP, INET_ADDRSTRLEN); // Convert the Ip from network type to pretty

		printf("Hello server new connection from %s\n", client_IP); // Dsiplay new connection and the client's IP Address
		printf("\n");
		
		char client_buffer[1024]; // Store the client's messages!
		char admin_buffer[1024]; // Store the admin's messages
		
		// Another loop while connected... Client to Server and back and forth!
		while(1){
			// Read message from client
			int bytes_recieved = recv(new_client_socket, client_buffer, sizeof(client_buffer), 0); // Check for if connection still there!

			// Either an error occured all client disconnected!
			if(bytes_recieved <= 0){
				printf("Client disconnected/ Error occured!");
				close(new_client_socket);
				break;

			}

			client_buffer[bytes_recieved] = '\0'; // Null terminate the client's buffer

			printf("Client says: %s\n", client_buffer);
			sleep(1); // Wait a second before displaying admin input box

			printf("Admin: ");
			fgets(admin_buffer, sizeof(admin_buffer), stdin); // Get admin message from the standard input section!
			sleep(1); // Wait a second before sending data!

			// Send message
			send(new_client_socket, admin_buffer, strlen(admin_buffer), 0); // Send message

			// Clear the buffers after sending data for both
			memset(client_buffer, 0, sizeof(client_buffer));
			memset(admin_buffer, 0, sizeof(admin_buffer));	

		}

		
	}
	

	

	return 0;
}
