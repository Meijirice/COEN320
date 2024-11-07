#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/dispatch.h>
#include <vector>
#include "Aircraft.h"

int main()
{
    int coid = name_open("radar_server", 0);
    if (coid == -1)
    {
        perror("radar_server");
        return 1;
    }

    std::vector<Aircraft> aircrafts;

    Aircraft aircraft1(1, 100, 12.5f, 45.0f, 5000.0f, 1.0f, 0.5f, -0.2f);
    Aircraft aircraft2(2, 150, 25.0f, 30.0f, 7500.0f, -0.3f, 1.2f, 0.8f);
    Aircraft aircraft3(3, 200, 60.0f, 90.0f, 10000.0f, 0.6f, -0.4f, 1.0f);

    aircrafts.push_back(aircraft1);
    aircrafts.push_back(aircraft2);
    aircrafts.push_back(aircraft3);

    for (const auto &aircraft : aircrafts)
    {
        int status = MsgSend(coid, &aircraft, sizeof(aircraft), NULL, 0);
        if (status == -1)
        {
            perror("MsgSend");
            return 1;
        }
    }

    std::cout << "Sending message to computer system: " << std::endl;

    // Send message to the server and get a reply

    name_close(coid); // Close connection to the server
    return 0;
}
