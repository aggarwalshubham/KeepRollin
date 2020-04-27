//Advanced Systems Programming Final Project Submission
//By Shubham Aggarwal(110008557) and Deepti Bamel (110008446)
//Server-Side Implementation of 2-player DICE GAME using Socket Programming

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#define PORT 8976

void servicePlayers(int, int);

int main(int argc, char const *argv[])
{
    int sock_descriptor =0;
    
	struct sockaddr_in address;
	//Communication Domain - AF_INET(IPv4 Protocol)
	address.sin_family = AF_INET;
	//Using local host address
    address.sin_addr.s_addr = INADDR_ANY;
	//Assigning port
    address.sin_port = htons(PORT);
		
	//Client socket descriptors
	int client_socket_1;
	int client_socket_2;
	
	//Error Messages for Error Handling
	char *error_message_1 = "Server Side - Error encountered while socket creation...";
	char *error_message_2 = "Error encountered while binding socket to server address...";
	char *error_message_3 = "Error encountered while listening...";
	char *error_message_4 = "Error encountered while socket creation for PLAYER 1...";
	char *error_message_5 = "Error encountered while socket creation for PLAYER 2...";
	
    //Socket created using:
	//Communication Domain - AF_INET : IPv4 Protocol
	//Communication Type - SOCK_STREAM : TCP(reliable, connection oriented)
	//Protocol - 0 : Internet Protocol
    if ((sock_descriptor = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {  
		perror(error_message_1);
        exit(EXIT_FAILURE);
    }
    
    //Bind newly created socket to given IP address and verify
    if (bind(sock_descriptor, (struct sockaddr *)&address, sizeof(address))<0)
    {   
		perror(error_message_2);
        exit(EXIT_FAILURE);
    }
    
	//Putting server socket in PASSIVE mode, where it can wait for clients to approach for connection initialisation
	//Backlog queue is initialised to 3 connections
	if (listen(sock_descriptor, 3) != 0)
    {   
		perror(error_message_3);
        exit(EXIT_FAILURE);
    }
    
	printf("---------------TWO PLAYER DICE GAME---------------\n");
	printf("Waiting for players to join...\n\n");
	
	while(1){
		
		//Extracts first connection request from pending connection queue and establishes connection
		if ((client_socket_1 = accept(sock_descriptor, (struct sockaddr *)&address, (socklen_t*)&address))<0)
    	{
			perror(error_message_4);
	       	exit(EXIT_FAILURE);
		}
		printf("Player 1 - TOTO has joined, Waiting for another player to join...\n");
    	
		if ((client_socket_2 = accept(sock_descriptor, (struct sockaddr *)&address, (socklen_t*)&address))<0)
    		{	
			perror(error_message_5);
         		exit(EXIT_FAILURE);
    		}
		printf("Player 2 - TITI is in the house...\n\n");
		
		printf("---------------LET THE BATTLE BEGIN---------------\n\n");
		if(!fork()){
			servicePlayers(client_socket_1, client_socket_2);
		}
		close(client_socket_1);
		close(client_socket_2);
    }
    return 0;
}

//Function being called in child process after forking
void servicePlayers(int player1, int player2){
	int player1_total_score=0;
	int player2_total_score=0;
	
	char *instruction_msg = "You can now play";
	char *winning_msg= "Game over: you won the game";
    char *loosing_msg= "Game over: you lost the game";
	
	//int win_msg_length = strlen(winning_msg);
	//int loss_msg_length = strlen(loosing_msg);
	
	while(1){    
		char buffer1_score[1024]={0};
	    char buffer2_score[1024]={0};
		
		sleep(1);
		
		//Player 1 - TOTO will play
		write(player1, instruction_msg,strlen(instruction_msg));
		//Reading score from Player 1
		if(read(player1, buffer1_score, 1024)<0){
			printf("Player 1 read error");
			exit(1);
		}
		player1_total_score = player1_total_score + atoi(buffer1_score);
		printf("Player 1 - TOTO's Total Score:%d \n", player1_total_score);

		//Condition - if Player 1 - TOTO's Total Score has reached 100
		if(player1_total_score >= 100){
			write(player1, winning_msg, strlen(winning_msg));
           	write(player2, loosing_msg, strlen(loosing_msg));
			exit(0);
		}
		
		sleep(1);
		
		//Player 2 - TITI will play
		write(player2, instruction_msg,strlen(instruction_msg));
		//Reading score from Player 2
		if(read(player2, buffer2_score, 1024)<0){
			printf("Player 2 read error");
			exit(1);
		}

        player2_total_score = player2_total_score + atoi(buffer2_score);
		printf("Player 2 - TITI's Total Score:%d \n\n", player2_total_score); 
		
		
		//Condition - if Player 2 - TITI's Total Score has reached 100
		if(player2_total_score >= 100){
            write(player2, winning_msg, strlen(winning_msg));
           	write(player1, loosing_msg, strlen(loosing_msg));
			exit(0);
        }
		
		printf("\n");
		
	}
	
	close(player1);
	close(player2);
}
