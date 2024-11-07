#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/dispatch.h>
#include <vector>
#include "Aircraft.h"

int main()
{
    // Create a connection name for the server
    name_attach_t *attach;
    attach = name_attach(NULL, "radar_server", 0);
    if (attach == NULL)
    {
        perror("radar_server");
        return 1;
    }
    std::cout << "Computer system is running, waiting for radar\n";

    while (true)
    {
        int rcvid;
        Aircraft aircraft;
        rcvid = MsgReceive(attach->chid, &aircraft, sizeof(aircraft), NULL); // Use &msg to pass the address
        if (rcvid == -1)
        {
            perror("No Msg Received");
            continue;
        }
        std::cout << "Received message: " << std::endl;
        aircraft.printStatus();

        char reply('b');

        MsgReply(rcvid, 0, &reply, sizeof(reply)); // Use &reply to pass the address
    }

    name_detach(attach, 0); // Detach the name
    return 0;
}
