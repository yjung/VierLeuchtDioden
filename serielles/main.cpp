#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
  
#define BAUDRATE B9600
#define MODEMDEVICE "/dev/cu.usbmodemfa131"

int main()
{
  int fd, res, i, j, p, q, r;
  struct termios oldtio, newtio;
  char buf[80], resbuf[80];
  bool recv;
  
  fd = open(MODEMDEVICE, O_RDWR | O_NOCTTY | O_NDELAY); 
  if (fd < 0) {
    perror(MODEMDEVICE); 
    exit(-1);
  }
  
  tcgetattr(fd, &oldtio); /* save current port settings */
  
  bzero(&newtio, sizeof(newtio));
  newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;
  newtio.c_iflag = IGNPAR;
  newtio.c_oflag = 0;
  
  /* set input mode (non-canonical, no echo,...) */
  newtio.c_lflag = 0;
   
  newtio.c_cc[VTIME]    = 0;   /* inter-character timer unused */
  newtio.c_cc[VMIN]     = 16;   /* blocking read until 16 chars received */
  
  tcflush(fd, TCIFLUSH);
  tcsetattr(fd, TCSANOW, &newtio);
  
  recv = false;
  res = 0;
  j = 0;
  
  while (true) {
    if (recv) {
      int n = write(fd, "1234", 4);
      if (n < 0)
        printf("Error: write() failed!\n");
      recv = false;
      usleep(500);
    }
    
    res = read(fd, buf, 80);   /* returns after 16 chars have been input */
    if (!res)
      continue;
    buf[res] = 0;              /* so we can printf... */
    
    for (i=0; i<res; i++) {
      if (buf[i] == '\n') {
        resbuf[j] = 0;
        if (sscanf(resbuf, "%d, %d: %d", &r, &p, &q) >= 3) {
          printf("%d: %d -> %d\n", r, p, q);
          recv = true;
        }
        j = 0;
      }
      else {
        resbuf[j++] = buf[i];
      }
    }
  }
  
  // TODO; SIGINT handler
  tcsetattr(fd, TCSANOW, &oldtio);
  
  return 0;
}
