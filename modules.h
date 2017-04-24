
#ifndef _MODULES_H
#define _MODULES_H

/* the handlers */
char *notesModuleHandler(char *nick, const char *message);
char *profanity_handler_function(const char *message);
char *Time_Handler(char *nick, char *command, const char *message);
char *reverse_handler(const char *message);

#endif

