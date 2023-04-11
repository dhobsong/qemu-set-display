/*
 * Copyright 2023 IGEL Co., Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <rfb/rfbclient.h>

int width = 640;
int height = 480;

int usage(char *name) {
    printf("Usage: %s [OPTION] SERVER\n", name);
    printf("\nconnect to qemu vnc SERVER address, setting given properties");

    printf("\n\nOPTIONS:\n");
    printf("\t-w WIDTH\t\tSet horizontal resulution of display in qemu\n");
    printf("\t-h HEIGHT\t\tSet vertical resulution of display in qemu\n");
    return 0;
}

int
main(int argc, char **argv)
{
    rfbClient* client = rfbGetClient(8, 3, 4);
    int opt;

    if (argc < 2)
        return usage(argv[0]);

    while ((opt = getopt(argc, argv, "w:h:")) != -1) {
        switch (opt) {
            case 'w':
                width = atoi(optarg);
                break;
            case 'h':
                height = atoi(optarg);
                break;
            default:
                return usage(argv[0]);
        }
    }

    client = rfbGetClient(8,3,4);

    if (!rfbInitClient(client, &argc, argv))
        return 1;

    /* libvncserver won't resize the client until an
     * initial size notification from the server, which
     * qemu doesn't send, is received.  Fake it out with
     * a 1x1px screen configuration to get past the size
     * check.
     */
    client->screen.height = client->screen.width = 1;

    printf("Setting virtualized display resolution to %dx%d\n",
           width, height);

    SendExtDesktopSize(client, width, height);

    if(WaitForMessage(client,50)<0)
            return -1;
    if(!HandleRFBServerMessage(client))
            return -1;

    rfbClientCleanup(client);

    return 0;
}


