#ifdef __cplusplus
extern "C" {
#endif
/* src/log.c */
void debug(const char *fmt, ...);
void err(const char *fmt, ...);
void notice(const char *fmt, ...);
void act(const char *fmt, ...);
void warn(const char *fmt, ...);
#ifdef __cplusplus
}
#endif

#define TRACK() {debug(" Track %s %d ",__PRETTY_FUNCTION__,__LINE__);}
