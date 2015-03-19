#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <microhttpd.h>
#include <wiringPi.h>

#ifdef USE_STL
    #include <sstream>
    #include <string>
#endif

#define PORT 5000

enum Pins {
    _17_ = 0, 
    _18_ = 1, 
    _27_ = 2, 
    _22_ = 3, 
    _23_ = 4,
    _19_ = 24,
    _16_ = 27
};

static int g_testVar = 0;
static bool g_enabled = true;
static bool g_ledOn = true;

int print_out_key (void *cls, enum MHD_ValueKind kind,
                   const char *key, const char *value)
{
  printf ("%s: %s\n", key, value);
  return MHD_YES;
}

int answer_to_connection (void *cls, struct MHD_Connection *connection,
                          const char *url,
                          const char *method, const char *version,
                          const char *upload_data,
                          size_t *upload_data_size, void **con_cls)
{
  static int myPtr = 0;
  //const char *page  = "<html><body>Hallo Browser!</body></html>";
  
  if (0 != strcmp (method, "GET"))
    return MHD_NO;
  
  if (*con_cls != &myPtr) {
    // never respond on first call
    *con_cls = &myPtr;
    return MHD_YES;
  }
  //*con_cls = NULL;
  
#ifdef USE_STL
  std::ostringstream ss;
  ss << "../docs" << url;
  
  int fd = open(ss.str().c_str(), O_RDONLY);
#else
  
  int fd = open("../docs/links.html", O_RDONLY);
#endif
  
  /*
  struct stat sbuf;
  
  if (fd == -1 || fstat(fd, &sbuf)) {
    if (fd != -1)
      close (fd);
    
    printf("Error reading file!\n");
    return MHD_NO;
  }
  
  struct MHD_Response *response = MHD_create_response_from_fd_at_offset (sbuf.st_size, fd, 0);
  */
  
  
  int len = lseek(fd, 0, SEEK_END);
  void *page = mmap(0, len, PROT_READ, MAP_PRIVATE, fd, 0);

  struct MHD_Response *response = MHD_create_response_from_buffer (len, //strlen (page),
                                              (void*) page, MHD_RESPMEM_PERSISTENT);
  
  MHD_add_response_header (response, "Content-Type", "text/html");
  MHD_add_response_header (response, "Access-Control-Allow-Origin", "*");
  
  int ret = MHD_queue_response (connection, MHD_HTTP_OK, response);
  
  printf ("%d: %s request for %s using version %s\n", ++g_testVar, method, url, version);
  
  //MHD_get_connection_values (connection, MHD_HEADER_KIND, &print_out_key, NULL);
  MHD_get_connection_values (connection, MHD_GET_ARGUMENT_KIND, &print_out_key, NULL);
  
  const char* val = MHD_lookup_connection_value (connection, MHD_GET_ARGUMENT_KIND, "enabled");
  
  if (val) {
      g_enabled = !strcmp(val, "true");
  }
  
  val = MHD_lookup_connection_value (connection, MHD_GET_ARGUMENT_KIND, "led");
  
  if (val) {
      g_ledOn = !strcmp(val, "true");
  }
  
  MHD_destroy_response (response);
  
  return ret;
}

int main(int argc, char* argv[])
{
  // Starte die WiringPi-Api
  if (wiringPiSetup() == -1) {
      printf("Couldn't init wiring!\n");
      return 1;
  }
  pinMode(_16_, OUTPUT);
    
  struct MHD_Daemon *daemon;

  daemon = MHD_start_daemon (MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                             &answer_to_connection, NULL, MHD_OPTION_END);
                           
  if (!daemon)
    return 1;
  
  while (g_enabled) {
    digitalWrite(_16_, g_ledOn ? 1 : 0);
    delay(100);
  }

  getchar (); // keep main thread alive until key pressed to not kill server
  
  MHD_stop_daemon (daemon);

  return 0;
}
