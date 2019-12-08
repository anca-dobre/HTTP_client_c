#ifndef _REQUESTS_
#define _REQUESTS_

char *compute_get_request(char *host, char *url, char *url_params, char* cookie, char* token);
char *compute_post_request(char *host, char *url, char *form_data, char* cookie, char* method, char* type,  char* token);

#endif