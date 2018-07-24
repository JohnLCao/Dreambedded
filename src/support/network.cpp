#include "network.h"

/*

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

*/

Network::Network() : port(portNumber) {


    pthread_create(tid, NULL, Network_thread, NULL);
}

void Network::sendPacket() {
	sinLen = sizeof(socket_in);
	sendto(
		socketDescriptor, response, strlen(response), 0,
		(struct sockaddr *) &socket_in, sinLen);
}

void* Network::thread(void* args) {
    return NULL;
}


/*
void Network_init(void)
{
	socket_in.sin_addr.s_addr = INADDR_ANY;
	socket_in.sin_family = AF_INET;
	socket_in.sin_port = htons(PORT);

	socketDescriptor = socket(PF_INET, SOCK_DGRAM, 0);
	bind(socketDescriptor, (struct sockaddr*) &socket_in, sizeof(socket_in));

	pthread_create(&tid, NULL, Network_thread, NULL);
}

void Network_cleanup(void)
{
	running = false;
	pthread_join(tid, NULL);
	close(socketDescriptor);
}

void* Network_thread(void* arg)
{
	while (running) {
    	// clear the buffers
    	memset(message, 0, MSG_MAX_LEN);
    	memset(response, 0, MSG_MAX_LEN);

    	// listen for a UDP packet
    	sinLen = sizeof(socket_in);
    	recvfrom(
    		socketDescriptor, message, MSG_MAX_LEN, 0,
			(struct sockaddr *) &socket_in, &sinLen);

    	if (!strcmp(message, SOUND_HIHAT_COMMAND)) {
    		Drumbeat_playSound(HiHat);
			sprintf(response, OK_MESSAGE);
    		Network_sendPacket();
    	}
    	else if (!strcmp(message, SOUND_BASE_COMMAND)) {
    		Drumbeat_playSound(Base);
			sprintf(response, OK_MESSAGE);
    		Network_sendPacket();
    	}
    	else if (!strcmp(message, SOUND_SNARE_COMMAND)) {
    		Drumbeat_playSound(Snare);
			sprintf(response, OK_MESSAGE);
    		Network_sendPacket();
    	}
    	else if (!strcmp(message, TEMPO_UP_COMMAND))  {
			Drumbeat_incrementBpm();
			sprintf(response, OK_MESSAGE);
    		Network_sendPacket();
    	}
    	else if (!strcmp(message, TEMPO_DOWN_COMMAND)) {
			Drumbeat_decrementBpm();
			sprintf(response, OK_MESSAGE);
    		Network_sendPacket();
    	}
		else if (!strcmp(message, VOLUME_UP_COMMAND))  {
			Drumbeat_incrementVolume();
			sprintf(response, OK_MESSAGE);
    		Network_sendPacket();
    	}
    	else if (!strcmp(message, VOLUME_DOWN_COMMAND)) {
			Drumbeat_decrementVolume();
			sprintf(response, OK_MESSAGE);
    		Network_sendPacket();
    	}
    	// set the mode (1, 2, 3)
    	else if (!strncmp(message, BEAT_COMMAND, strlen(BEAT_COMMAND))) {
			int newMode = atoi(message + strlen(BEAT_COMMAND));
			Drumbeat_setMode(newMode);
			sprintf(response, OK_MESSAGE);
    		Network_sendPacket();
    	}
		else if (!strcmp(message, GET_MODE_COMMAND)) {
			int mode = Drumbeat_getMode();
			sprintf(response, "Mode: %d", mode);
    		Network_sendPacket();
    	}
		else if (!strcmp(message, GET_VOLUME_COMMAND)) {
			int volume = AudioMixer_getVolume();
			sprintf(response, "Volume: %d", volume);
			Network_sendPacket();
		}
		else if (!strcmp(message, GET_TEMPO_COMMAND)) {
			int tempo = Drumbeat_getBpm();
			sprintf(response, "Tempo: %d", tempo);
			Network_sendPacket();
		}
		else if (!strcmp(message, GET_UPTIME_COMMAND)) {
			char data[512];

			// open /proc/uptime
			FILE* file = fopen(UPTIME_FILE, "r");
			if (!file) {
				printf("Error opening %s\n", UPTIME_FILE);
				exit(-1);
			}

			// read /proc/uptime
			size_t bytesRead = fread(data, sizeof(char), 512, file);
			if (bytesRead <= 0) {
				printf("Error with reading %s\n", UPTIME_FILE);
				exit(-1);
			}

			// truncate the decimal portion of the time
			int uptime = atoi(data);

			// Close /proc/uptime
			fclose(file);

			sprintf(response, "Uptime: %d", uptime);
			Network_sendPacket();
		}
    	// Invalid command
    	else {
    		sprintf(response, ERROR_MESSAGE);
    		Network_sendPacket();
    	}
    }
	return NULL;
}

*/
