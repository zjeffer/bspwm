/* Copyright (c) 2012, Bastien Dejean
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <poll.h>
#include <sys/un.h>
#include <unistd.h>
#include "helpers.h"
#include "common.h"

int main(int argc, char *argv[])
{
	// Holds the socket file descriptor
	int sock_fd;
	// The address of the AF_LOCAL (aka AF_UNIX) socket
	struct sockaddr_un sock_address;
	// Holds the message to send to bspwm
	char msg[BUFSIZ];
	// Holds the received response from bspwm
	char rsp[BUFSIZ];

	if (argc < 2) {
		err("No arguments given.\n");
	}

	// TODO: describe what this does
	sock_address.sun_family = AF_UNIX;
	// TODO: what does sp stand for? socket path? sun path?
	char *sp;

	// Try to open a socket connection
	if ((sock_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		err("Failed to create the socket.\n");
	}

	sp = getenv(SOCKET_ENV_VAR);
	if (sp != NULL) {
		// save sp to sock_address.sun_path
		snprintf(sock_address.sun_path, sizeof(sock_address.sun_path), "%s", sp);
	} else {
		char *host = NULL;
		int dn = 0, sn = 0;
		if (xcb_parse_display(NULL, &host, &dn, &sn) != 0) {
			snprintf(sock_address.sun_path, sizeof(sock_address.sun_path), SOCKET_PATH_TPL, host, dn, sn);
		}
		free(host);
	}

	// try to connect to the socket
	if (connect(sock_fd, (struct sockaddr *) &sock_address, sizeof(sock_address)) == -1) {
		err("Failed to connect to the socket.\n");
	}

	argc--, argv++;
	// Length of the message to send to bspwm
	int msg_len = 0;

	// calculate the message length
	for (int offset = 0, rem = sizeof(msg), n = 0; argc > 0 && rem > 0; offset += n, rem -= n, argc--, argv++) {
		n = snprintf(msg + offset, rem, "%s%c", *argv, 0);
		msg_len += n;
	}

	// Send the message to the socket
	if (send(sock_fd, msg, msg_len, 0) == -1) {
		err("Failed to send the data.\n");
	}

	// The return code to send back to the process bspc is called from
	int ret = EXIT_SUCCESS;
	// Holds the number of bytes received
	int nb;

	// the set of file descriptors to be polled
	struct pollfd fds[] = {
		{sock_fd, POLLIN, 0},
		{STDOUT_FILENO, POLLHUP, 0},
	};

	// while at least one of the 2 descriptors return events (0 == timeout, -1 == error)
	while (poll(fds, 2, -1) > 0) {
		// if bspc receives data from bspwm (sock_fd)
		if (fds[0].revents & POLLIN) {
			// if the number of received bytes > 0, store the response in rsp
			if ((nb = recv(sock_fd, rsp, sizeof(rsp)-1, 0)) > 0) {
				// add a null termintor to the end of the response
				rsp[nb] = '\0';
				// if bspwm responds with a failure message
				if (rsp[0] == FAILURE_MESSAGE[0]) {
					// change the return code
					ret = EXIT_FAILURE;
					// print the error (to stderr)
					fprintf(stderr, "%s", rsp + 1);
					fflush(stderr);
				} else {
					// print the response (to stdout)
					fprintf(stdout, "%s", rsp);
					fflush(stdout);
				}
			} else {
				// if bspwm responds, stop polling
				break;
			}
		}
		if (fds[1].revents & (POLLERR | POLLHUP)) {
			// stop polling if stdout is closed
			break;
		}
	}

	// close the socket
	close(sock_fd);
	// return 
	return ret;
}
