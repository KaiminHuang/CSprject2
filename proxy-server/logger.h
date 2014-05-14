#ifndef LOGGER_H

	// Log event to the log file
	void logRequest(int sockfd);

	// Get a readable time for the log
	char * getReadableTime();
#endif