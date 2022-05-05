// c echo script to test stdin and stdout wrapping in python 
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

#define FGETS_ALLOC_N 128

char* fgets_alloc(FILE *istream) {
  char* buf = NULL;
  size_t size = 0;
  size_t used = 0;
  do {
    size += FGETS_ALLOC_N;
    char *buf_new = realloc(buf, size);
    if (buf_new == NULL) {
      // Out-of-memory
      free(buf);
      return NULL;
    }
    buf = buf_new;
    if (fgets(&buf[used], (int) (size - used), istream) == NULL) {
      // feof or ferror
      if (used == 0 || ferror(istream)) {
        free(buf);
        buf = NULL;
      }
      return buf;
    }
    size_t length = strlen(&buf[used]);
    if (length + 1 != size - used) break;
    used += length;
  } while (buf[used - 1] != '\n');
  return buf;
}

int run_repl(){
    FILE *istream = stdin;
    char *s;
    while ((s = fgets_alloc(istream)) != NULL) {
        printf("%s", s);
        free(s);
        fflush(stdout);
    }
    if (ferror(istream)) {
        puts("Input error");
    } else if (feof(istream)) {
        puts("End of file");
    } else {
        puts("Out of memory");
    }
    return 0;
}

int main() {
    return run_repl();
}
