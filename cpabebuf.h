#ifndef CPABEBUF_H
#define CPABEBUF_H

typedef struct cpabe_daata_buffer {
	char* data;
	int len;
} cpabebuf;

cpabebuf* new_cpabebuf();
void free_cpabebuf(cpabebuf* buf);
int cpabebuf_len(cpabebuf* buf);
void* cpabebuf_data(cpabebuf* buf);

#endif
