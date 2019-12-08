#include <stdio.h>      /* printf, sprintf */
#include <json-c/json.h>
#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"
#include <json-c/json.h>

char* getCookie (char* response){
	
	char *parsare, *cookie;
	char *copie_response, *copy_parsare;
	char *prajiturica;
	copie_response= malloc((strlen(response)+1)*sizeof(char));
	strcpy(copie_response, response);
	parsare = strstr (copie_response, "Set-Cookie");
	copy_parsare = malloc((strlen(parsare)+1)*sizeof(char));
	strcpy(copy_parsare, parsare);
	
	cookie = parsare;
	cookie = strtok(cookie, ";");
	cookie = strstr(cookie, " ");
	cookie++;
	strcat(cookie, ";");
	prajiturica = cookie;
	copy_parsare++;

	while((copy_parsare=strstr(copy_parsare, "Set-Cookie")) != NULL){
	
		char* aux = malloc((strlen(copy_parsare)+1)*sizeof(char));
		strcpy(aux,copy_parsare);
		cookie = aux;
		cookie = strtok(cookie, ";");
		cookie = strstr(cookie, " ");	
		cookie++;
		strcat(cookie, ";");
		prajiturica = strcat(prajiturica, cookie);
		copy_parsare++;

	}
	return prajiturica;

}


int main(int argc, char *argv[])
{
    char *message;
    char *response;
    int sockfd;

	struct json_object *json_to_parse;
	struct json_object *url;
	struct json_object *type;
	struct json_object *method;
	struct json_object *data;
	struct json_object *username;
	struct json_object *password;
	struct json_object *token;
	struct json_object *queryParams;
	struct json_object *id;
	struct json_object *q;
	struct json_object *APPID;


//task1

    sockfd = open_connection("185.118.200.35", 8081, AF_INET, SOCK_STREAM, 0);
    message = compute_get_request("185.118.200.35", "/task1/start", NULL, NULL, NULL);
    printf("message: %s\n", message);

    send_to_server(sockfd, message);
    response = receive_from_server(sockfd);
    printf("receive: %s\n", response);
	
	close_connection(sockfd);
	
	char* prajiturica;
	char* response_orig2; //copie a lui response
	response_orig2= malloc((strlen(response)+1)*sizeof(char));
	strcpy(response_orig2, response);
	prajiturica = getCookie(response); 
		
	char *json;
	json = strstr (response_orig2, "{");
	//salvam datele din json
	json_to_parse = json_tokener_parse(json);
	json_object_object_get_ex(json_to_parse, "url", &url);
	json_object_object_get_ex(json_to_parse, "type", &type);
	json_object_object_get_ex(json_to_parse, "method", &method);
	json_object_object_get_ex(json_to_parse, "data", &data);
	json_object_object_get_ex(data, "username", &username);
	json_object_object_get_ex(data, "password", &password);

	//creez url_params
	char structura[1000];
	sprintf(structura, "username=%s&password=%s", json_object_get_string(username), json_object_get_string(password));
	
//task2

	sockfd = open_connection("185.118.200.35", 8081, AF_INET, SOCK_STREAM, 0);
    message = compute_post_request("185.118.200.35", json_object_get_string(url), structura, prajiturica, 
											json_object_get_string(method), json_object_get_string(type), NULL);
    send_to_server(sockfd, message);
    response = receive_from_server(sockfd);
    printf("receive: %s\n", response);
	close_connection(sockfd);

	char* response_orig3;
	response_orig3= malloc((strlen(response)+1)*sizeof(char));
	strcpy(response_orig3, response);
	prajiturica = getCookie(response);
	
	char* json_task3;
	json_task3 = strstr (response_orig3, "{");
	   
	json_to_parse = json_tokener_parse(json_task3);
	json_object_object_get_ex(json_to_parse, "url", &url);
	json_object_object_get_ex(json_to_parse, "method", &method);
	json_object_object_get_ex(json_to_parse, "data", &data);
	json_object_object_get_ex(data, "token", &token);
	json_object_object_get_ex(data, "queryParams", &queryParams);
	json_object_object_get_ex(queryParams, "id", &id);

	
	char url_params[1000];
	sprintf(url_params,"raspuns1=omul&raspuns2=numele&id=%s", json_object_get_string(id));
	  
//task3
    
	sockfd = open_connection("185.118.200.35", 8081, AF_INET, SOCK_STREAM, 0);
    message = compute_get_request("185.118.200.35", json_object_get_string(url), url_params, prajiturica, 
											 json_object_get_string(token));

    send_to_server(sockfd, message);
    response = receive_from_server(sockfd);
    printf("receive: %s\n", response);
	
	close_connection(sockfd);

	char* response_orig4;
	response_orig4= malloc((strlen(response)+1)*sizeof(char));
	strcpy(response_orig4, response);
	prajiturica = getCookie(response);

	char* json_task4;
	json_task4 = strstr (response_orig4, "{");
	   
	json_to_parse = json_tokener_parse(json_task4);
	json_object_object_get_ex(json_to_parse, "url", &url);
	json_object_object_get_ex(json_to_parse, "method", &method);
	
//Task4
	
	char *token_final;
	token_final = json_object_get_string(token);
	
	sockfd = open_connection("185.118.200.35", 8081, AF_INET, SOCK_STREAM, 0);
    message = compute_get_request("185.118.200.35", json_object_get_string(url), NULL, prajiturica,  json_object_get_string(token));
    send_to_server(sockfd, message);
    response = receive_from_server(sockfd);
    printf("receive: %s\n", response);
	close_connection(sockfd);
	
	char* response_orig5;
	response_orig5= malloc((strlen(response)+1)*sizeof(char));
	strcpy(response_orig5, response);
	prajiturica = getCookie(response);
	
	char* json_task5;
	json_task5 = strstr (response_orig5, "{");	   
	json_to_parse = json_tokener_parse(json_task5);
	json_object_object_get_ex(json_to_parse, "url", &url);
	char *url1;
	url1=  json_object_get_string(url);
	json_object_object_get_ex(json_to_parse, "method", &method);
	json_object_object_get_ex(json_to_parse, "type", &type);
	json_object_object_get_ex(json_to_parse, "data", &data);
	json_object_object_get_ex(data, "url", &url);
	json_object_object_get_ex(data, "queryParams", &queryParams);
	json_object_object_get_ex(queryParams, "q", &q);
	json_object_object_get_ex(queryParams, "APPID", &APPID);
	json_object_object_get_ex(data, "method", &method);

	char *name_host, *ip_host, *new_url;
	name_host = malloc((strlen(json_object_get_string(url))+1)*sizeof(char));
	strcpy(name_host,json_object_get_string(url));
	name_host=strtok(name_host, "/");
	char host_ip[200];
	struct hostent *hp = gethostbyname(name_host);
	sprintf(host_ip,"%s ", inet_ntoa( *( struct in_addr*)( hp -> h_addr_list[0])));

	new_url = strstr (json_object_get_string(url), "/");
	char url_par[1000];
	sprintf(url_par, "q=%s&APPID=%s", json_object_get_string(q), json_object_get_string(APPID));

	
//task 5

	char *response1;
	sockfd = open_connection(host_ip, 80, AF_INET, SOCK_STREAM, 0);
	
    message = compute_get_request(host_ip, new_url, url_par, NULL, NULL);
    send_to_server(sockfd, message);
    response1 = receive_from_server(sockfd);

    printf("receive: %s\n", response1);
	json_task5 = strstr (response1, "{");
	close_connection(sockfd);

	sockfd = open_connection("185.118.200.35", 8081, AF_INET, SOCK_STREAM, 0);
	
    message = compute_post_request("185.118.200.35", url1, json_task5, prajiturica, 
						json_object_get_string(method), json_object_get_string(type), token_final);

    send_to_server(sockfd, message);
    response = receive_from_server(sockfd);
    printf("receive: %s\n", response);
	
	close_connection(sockfd);


    return 0;
}