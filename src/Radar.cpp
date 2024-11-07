#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/dispatch.h>
#include <vector>
// #include "Aircraft.h"

typedef struct
{

} msg_struct;

int main()
{
    // Connect to the server by name
    int coid = name_open("radar_server", 0);
    if (coid == -1)
    {
        perror("radar_server");
        return 1;
    }

    char aircrafts('a');
    // Add all the aircrafts

    std::cout << "Sending message to computer system: " << aircrafts << std::endl;

    // Send message to the server and get a reply
    int status = MsgSend(coid, &aircrafts, sizeof(aircrafts), NULL, 0);
    if (status == -1)
    {
        perror("MsgSend");
        return 1;
    }

    name_close(coid); // Close connection to the server
    return 0;
}
