#ifndef LOGGER_H

	// Log event to the log file
	void logRequest(char * ipAddress,char * port,int size,char * host);

	// Get a readable time for the log
	char * getReadableTime();
#endif