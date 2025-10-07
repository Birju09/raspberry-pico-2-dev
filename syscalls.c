#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>

/* these methods are not defined anywhere even in nosys
 * so they have to be implemented */

int _close(int file) 
{
  return 0;
}

int _lseek(int file, char* ptr, int dir)
{
  return 0;
}

int _read(int file, char* ptr, int len)
{
  return 0;
}

int _write(int file, char* ptr, int len)
{
  return 0;
}

void _exit(int code)
{
  while (1);
}

int _isatty(int fd)
{
  return 0;
}

int _fstat(int fd, struct stat *statbuf)
{
  return -1;
}

extern char __heap_end__;
// Start of heap
extern char _heap_start;
// Heap limit
extern int __HeapLimit;

// Current heap position
static char *heap_ptr = &_heap_start;

void *_sbrk(int incr) {
    char *prev_heap_ptr = heap_ptr;
    
    if (heap_ptr + incr > &__HeapLimit) {
        // No more memory
        errno = ENOMEM;
        return (void *)-1;
    }
    
    heap_ptr += incr;
    return (void *)prev_heap_ptr;
}