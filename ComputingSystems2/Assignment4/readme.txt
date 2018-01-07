// TO COMPILE AND RUN ON CS1:
g++ -o serverExecutable server.cpp
g++ -o clientExecutable client.cpp
./execServer portNumber &
./execClient ipAddress portNumber
// EXAMPLE:
g++ -o execServer server.cpp
g++ -o execClient client.cpp
./execServer 3453 &
./execClient 10.124.72.20 3453

/* 
CURRENT LEVEL OF FUNCTIONALITY:
-- Leaderboard output is not properly formatted, returning the number of turns after a line break.
I think this might have something to do with the stringstream input in WriteLeaderboardToClient being
improperly formatted or not being assigned correctly. If I had more time, I would investigate thie further to correct.
-- After program is finished running and connection is closed, SERVER ERROR on binding occurs.
I think this may be because the client closes the connection so then the server throws an error because it is still connected.
In order to fix this error, maybe I should have the server close the connection first. If I had more time, I would investigate further to correct.
-- Implementation DOES NOT support mulitple concurrent clients/players at the server
I was not able pass the arguments to the thread create properly in the time alloted.
If I had more time, I would spend more time debugging the multithreading rather than working
on other aspects of the program.
I would also ensure atomicity of cout & cin to ensure there wasn't overlap from multiple threads
calling them.
I would also implement the mutex when accessing the leaderboard to ensure atomicity.
*/