# KeepRollin
## Two player online dice game based on client-server architecture
- Implemented in C using system programming concepts
- Use of socket programming for interprocess communication between client and server
- Use of fork() on server side to create child processes that are input parameters for the servicePlayers method(referee)
## Game Structure and Rules
- The server starts before any client, and goes into an infinite loop to wait for clients
- When the server gets a client, it waits for another client (two players are needed)
- When the server gets the other client (now two clients), it forks and, let the child process take care of these two clients (players) in a separate function, called servicePlayers, while the parent process goes back to wait for the next two clients (players)
- The server’s child process will be a referee for the two clients, namely TOTO and TITI, who would be the two players
- In particular, the referee first gets in an infinite loop, then
1 it sends the message "You can now play" to player TOTO,
2 it reads the scrore obtained by TOTO and adds it to TOTO’s total,
3 it sends the message "You can now play" to player TITI,
4 it reads the scrore obtained by TITI and adds it to TITI’s total,
5 If one or both accumulated scores (totals) reaches 100, the referee
5– sends "Game over: you won the game" to the winner and sends "Game over: you lost the game" to the player who lost,
5- closes both sockets (each player has its own socket) and exits,
6 otherwise, goes back to step 1
