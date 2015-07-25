#include <sys/socket.h>
#include <arpa/inet.h>

//int main(int argc, char * argv[])
{
	char *advice[] = {"Take smaller bites\r\n", "Go for the right jeans. No they do not make you look fat.\r\n",
		"One word: inapproperiate\r\n",
		"Just for today, be honest. Tell your boss what you *really* think\r\n",
		"You might want to rethink that haircut\r\n"
		};
		int listener_d = socket(PF_INET, SOCK_STREAM, 0);
		
		struct sockaddr_in name;
		name.sin_family = PF_INET;
		name.sin_port = (in_port_t)htons(30000);
		name.sin_addr.s_addr=htonl(INADDR_ANY);
		if(bind(listener_d, (struct socaddr *)&name, sizeof(name))==-1)
			error("Cannot bind the port");
		if(listen(listener_d, 10)==-1)
			error("Cannot listen from anyone");
		puts("Waiting for connection");
		
		while(1){
		struct sockaddr_storage client_addr;
		unsigned int address_size= sizeof(client_addr);
		int connect_d = accept(listener_d, (struct sockaddr*)&client_addr, &address_size);
		
		char *msg= advice[rand()%5];
		if(send(connect_d, msg, strlen(msg),0)==-1)
			error("Sending failure");
		close(connect_d);
		}
		return 0;
	}
		
