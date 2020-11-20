#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc , char *argv[])
{

	int socket_desc, new_socket, t;
	struct sockaddr_in server, pelanggan;
	char *message, buffer[100];

	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}


	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8888);

	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("bind failed");
		exit(1);
	}

	//Listen
	t = listen(socket_desc, 3);

	if(t == -1)
	{
		printf("Error in listening");
		exit(1);
	}

	socklen_t length = sizeof(pelanggan);

	new_socket = accept(socket_desc,(struct sockaddr*)&pelanggan,&length);
	if(new_socket == -1)
	{
		printf("Error in temporary socket creation");
		exit(1);
	}

	while(1)
	{

		t = recv(new_socket, buffer, 100, 0);

		if(t == -1)
		{
			printf("Error in receiving");
			exit(1);
		}
			printf("Client: %s",buffer); //Mesej dari client
			printf("\nServer: "); //Mesej untuk client
			fgets(buffer,100,stdin);
			if(strncmp(buffer,"bye",3)==0)
			break;
			t=send(new_socket,buffer,100,0);
			if(t==-1)
			{
			printf("Error in sending");
			exit(1);
		}
	}
	close(new_socket);
	exit(0);
	return 0;
}
