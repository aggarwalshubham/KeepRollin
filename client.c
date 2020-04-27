//Advanced Systems Programming Final Project Submission
//By Shubham Aggarwal(110008557) and Deepti Bamel (110008446)
//Client-Side Implementation of 2-player DICE GAME using Socket Programming

#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#define PORT 8976

int main(int argc, char const *argv[])
{
    int sock_descriptor = 0;
    
	struct sockaddr_in server_address;
	//Communication Domain - AF_INET(IPv4 Protocol)
	server_address.sin_family = AF_INET;
	//Assigning port
    server_address.sin_port = htons(PORT);
	
    char buffer[1024] = {0};
    char scoreString[20];
	
    long int size=0;
	
	char *instruction_msg = "You can now play";
	char *dice_msg = "Dice rolling....!!!";
    char *game_winner_msg = "Game over: you won the game";
	char *game_loser_msg = "Game over: you lost the game";
	char *player_win_msg = "I won the game.";
	char *player_loss_msg = "I lost the game.";
	
	char *server_connection = "Player connected to the server..";
	char *error_message_1 = "Client Side - Error encountered while socket creation...";
	char *error_message_2 = "Either the entered IP address is invalid or is not supported...";
	char *error_message_3 = "Failure encountered while connecting to server...";
    
	//Socket created using:
	//Communication Domain - AF_INET : IPv4 Protocol
	//Communication Type - SOCK_STREAM : TCP(reliable, connection oriented)
	//Protocol - 0 : Internet Protocol
	if ((sock_descriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {	
		printf("\n %s\n", error_message_1);
        return -1;
    }

    //While socket creation, AF_INET is used, 
	//Convert IPv4 or IPv6 internet network address into a string in Internet Standard Form (i.e. from text to binary form)
    if(inet_pton(AF_INET, argv[1], &server_address.sin_addr)<=0)
    {   
		printf("\n %s\n", error_message_2);
        return -1;
    }

	//Connect client sokcet to server socket
	//i.e. the socket referred by file descriptor to the address specified (Server Address)
    if (connect(sock_descriptor, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) 
    {   
		printf("\n%s\n", error_message_3);
        return -1;
    } else {
		printf("\n%s\n", server_connection);
	}
    printf("-------------------------------");
	
    while(1){
		//Reading message from the server	
		if(read(sock_descriptor , buffer, 1024)<=0)  {
			printf("\nRead Error");
			exit(1);
		}
	  
		//Dice rolls now
    	if(strcmp(buffer, instruction_msg) == 0){
    		int diceCount = 0;
			printf("\n%s\n",buffer);
			//Dice is rolled to get a value between 1-10
			printf("%s\n", dice_msg);
			diceCount =(int) time(&size)%10 + 1;
			printf("Dice score obtained: %d\n", diceCount);
			printf("\n-------------------------------\n");
			sprintf(scoreString,"%d",diceCount); 
			//Send data to the server
			write(sock_descriptor,scoreString,strlen(scoreString));    
    	}
		
		//Condition - if one or both total accumulated score reaches 100
		else{
			if(strcmp(buffer, game_winner_msg) == 0){
				printf("\n%s\n", player_win_msg);
				close(sock_descriptor);
				exit(0);
			}
			else if (strcmp (buffer, game_loser_msg) == 0){
				printf("\n%s\n", player_loss_msg);
				close(sock_descriptor);
				exit(0);
			}
		}
    }
    return 0;
}