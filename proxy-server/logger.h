#ifndef LOGGER_H

	// Log event to the log file
	void logRequest(int sockfd, int size, char * origin);

	// Get a readable time for the log
	char * getReadableTime();
#endif