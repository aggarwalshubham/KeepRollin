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
  1. it sends the message "You can now play" to player TOTO,
  2. it reads the scrore obtained by TOTO and adds it to TOTO’s total,
  3. it sends the message "You can now play" to player TITI,
  4. it reads the scrore obtained by TITI and adds it to TITI’s total,
  5. If one or both accumulated scores (totals) reaches 100, the referee
     - sends "Game over: you won the game" to the winner and sends "Game over: you lost the game" to the player who lost,
     - closes both sockets (each player has its own socket) and exits,
  6. otherwise, goes back to step 1
- Once a client (player) is connected to the server, it gets in an infinite loop then,
  1. it reads the server’s message (waits for the message)
  2. if the read message is "You can now play", client plays its dice, prints obtained score on its screen and sends it to the server, before it goes to step 1
  3. if the read message is "Game over: you won the game", player prints "I won the game" then closes socket and exit
  4. if the read message is "Game over: you lost the game", player prints "I lost the game" then closes socket and exit
## Steps to Run
- Clone https://github.com/aggarwalshubham/KeepRollin.git

- Change to "KeepRollin" as the current directory

- Open 3 Terminal windows - 1 for server and 2 for clients

- Run **gcc server.c -o server**

- Run **gcc client.c -o client**

- Run **./server** on one terminal

- Run **./client <server IP>** on other two terminals
