#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <stdio.h>
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"

char *compute_get_request(char *host, char *url, char *url_params, char *cookie, char *token)
{
	
    char *message = calloc(BUFLEN, sizeof(char));


    char *line = calloc(LINELEN, sizeof(char));
	
    /*
        PAS 1: Scriem numele metodei, calea, parametri din url (daca exista) si tipul protocolului
    */
    if (url_params != NULL)
    { 
        sprintf(line, "GET %s?%s HTTP/1.1", url, url_params);
    }
    else
    {
        sprintf(line, "GET %s HTTP/1.1", url);
    }
    compute_message(message, line);


    sprintf(line, "Host: %s", host);
    compute_message(message, line);
	
	
	
	if(cookie!=NULL)
	{sprintf(line, "Cookie: %s", cookie);
     compute_message(message, line);
	}
 
	if(token!=NULL)
	{sprintf(line, "Authorization: Basic %s", token);
     compute_message(message, line);
	}
	
  
    sprintf(line, "");
    compute_message(message, line);
    
    //TODO Ex 0
    return message;
}


char *compute_post_request(char *host, char *url, char *form_data, char* cookie, char* method, char* type, char* token)
{

    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));
 


    sprintf(line, "POST %s HTTP/1.1", url);
    compute_message(message, line);


    sprintf(line, "Host: %s", host);
    compute_message(message, line);


    sprintf(line, "Content-Type: %s", type);
    compute_message(message, line);
	
	 sprintf(line, "Cookie: %s", cookie);
    compute_message(message, line);
	
	
    sprintf(line, "Content-Length: %ld", strlen(form_data));
    compute_message(message, line);

	if(token!=NULL)
	{sprintf(line, "Authorization: Basic %s", token);
     compute_message(message, line);
	}  

    sprintf(line, "");
    compute_message(message, line);


    sprintf(line, "%s", form_data);
    compute_message(message, line);

   
    return message;
}


