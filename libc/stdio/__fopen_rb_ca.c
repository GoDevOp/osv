#include "stdio_impl.h"
#include <fcntl.h>
#include <string.h>

FILE *__fopen_rb_ca(const char *filename, FILE *f, unsigned char *buf, size_t len)
{
	memset(f, 0, sizeof *f);

	f->fd = open(filename, O_RDONLY|O_LARGEFILE|O_CLOEXEC, 0);
	if (f->fd < 0) return 0;

	f->flags = F_NOWR | F_PERM;
	f->buf = buf + UNGET;
	f->buf_size = len - UNGET;
	f->read = __stdio_read;
	f->seek = __stdio_seek;
	f->close = __stdio_close;

	return f;
}
