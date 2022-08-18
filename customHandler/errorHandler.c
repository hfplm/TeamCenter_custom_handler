#include"Header.h"

int errorHandler(int ifail) {
	char* msg;

	if (ifail == 0) {
		TC_write_syslog("\n Test Passed !");
		printf("\n Test Passed !");
	}
	else {
		TC_write_syslog("\n Error Code : %d", ifail);
		printf("\n Error Code : %d", ifail);
		EMH_ask_error_text(ifail, &msg);
		TC_write_syslog("\n Error: %s", msg);
		printf("\n Error: %s", msg);
	}
}