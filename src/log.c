#ifdef __cplusplus
extern "C" {
#endif
    #include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <kore.h>
#include <syslog.h>

#include "log.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define SIZE_OF_MSG (BUFSIZ)
  
void debug(const char *fmt, ...) {
    char *debug=getenv("DEBUG");
    if (debug&&(strcmp(debug,"1")==0)) {

	va_list args;

	char msg[SIZE_OF_MSG];
	size_t len;

	va_start(args, fmt);

	vsnprintf(msg, sizeof(msg), fmt, args);
	len = strlen(msg);
	write(2, ANSI_COLOR_BLUE " [D] " ANSI_COLOR_RESET, 5+5+4);
	write(2, msg, len);
	write(2, "\n", 1);
	fsync(2);

	va_end(args);
  //  kore_log(LOG_DEBUG,msg);
    }

	return;
}

void err(const char *fmt, ...) {
	va_list args;

	char msg[SIZE_OF_MSG];
	size_t len;

	va_start(args, fmt);


    vsnprintf(msg, sizeof(msg), fmt, args);
	len = strlen(msg);
	write(2, ANSI_COLOR_RED " [!] " ANSI_COLOR_RESET, 5+5+4);
	write(2, msg, len);
	write(2, "\n", 1);
	fsync(2);

	va_end(args);


}


void notice(const char *fmt, ...) {
	va_list args;

	char msg[SIZE_OF_MSG];
	size_t len;

	va_start(args, fmt);


    vsnprintf(msg, sizeof(msg), fmt, args);
	len = strlen(msg);
	write(2, ANSI_COLOR_GREEN " (*) " ANSI_COLOR_RESET, 5+5+4);
	write(2, msg, len);
	write(2, "\n", 1);
	fsync(2);

	va_end(args);
}


void act(const char *fmt, ...) {
	va_list args;

	char msg[SIZE_OF_MSG];
	size_t len;

	va_start(args, fmt);


    vsnprintf(msg, sizeof(msg), fmt, args);
	len = strlen(msg);
	write(2, "  .  ", 5);
	write(2, msg, len);
	write(2, "\n", 1);
	fsync(2);

	va_end(args);
}

void warn(const char *fmt, ...) {
	va_list args;

	char msg[SIZE_OF_MSG];
	size_t len;

	va_start(args, fmt);

    vsnprintf(msg, sizeof(msg), fmt, args);
	len = strlen(msg);
	write(2, ANSI_COLOR_YELLOW " (*) " ANSI_COLOR_RESET, 5+5+4);
	write(2, msg, len);
	write(2, "\n", 1);
	fsync(2);

	va_end(args);
}

#ifdef __cplusplus
}
#endif
