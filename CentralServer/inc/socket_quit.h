#ifndef SOCKETQUIT_H_
#define SOCKETQUIT_H_

void finish(int signal);
void finishWithError(int signal);
void quit_setup();
void quit_handler(char *message);

#endif
