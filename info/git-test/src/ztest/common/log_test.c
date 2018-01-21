#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/common/log.h"

/**
int log_init(char *argv0, log_options_t opts,
	  log_facility_t fac, char *logfile);
void log_fini(void);


 */
int main(int argc, char *argv[])
{
	log_options_t logopts = LOG_OPTS_INITIALIZER;
	logopts.stderr_level  = LOG_LEVEL_FATAL;
	logopts.syslog_level  = LOG_LEVEL_INFO;
	/* === init === */
	// log_init("test", logopts, SYSLOG_FACILITY_DAEMON, NULL);

	/* 1. argv[0] and above "test" seems no difference */
	/* 2. jimmy.log is in current working dir */
	log_init(argv[0], logopts, SYSLOG_FACILITY_DAEMON, "jimmy.log");

	info("allocate [ node_list = %s ] to [ job_id = %u ]", "node[1-5]", 100);
	error("some thing error!!!");
	/* === fini === */
	log_fini();
	return 0;
}
