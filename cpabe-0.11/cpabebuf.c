#include <stdlib.h>
#include "../cpabebuf.h"

cpabebuf* new_cpabebuf() {
	cpabebuf* buf = (cpabebuf*)malloc(sizeof(cpabebuf));
	return buf;
}

void free_cpabebuf(cpabebuf *buf) {
	free(buf->data);
	free(buf);
}

int cpabebuf_len(cpabebuf* buf) {
	return buf->len;
}

void* cpabebuf_data(cpabebuf* buf) {
	return (void*)buf->data;
}
