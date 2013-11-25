#ifndef __CARD_FILE_H__
#define __CARD_FILE_H__

extern int read_file(const char *file);
extern int card_generate(int *data, int length);
extern int write_file(int fd, int *data, int length, int flag, int value_sum);

extern int card_flag_parse(int flag);
#endif
