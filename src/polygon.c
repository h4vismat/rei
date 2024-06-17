#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>
#include <jansson.h>

#define URL_FORMAT "https://api.polygon.io/v2/aggs/ticker/%s/range/%d/%s/%s/%s?apiKey=%s"
#define URL_SIZE 256 

int http_get(char *url, char *buffer, size_t buffer_size) {
	CURL *curl;
	CURLcode res;

	curl = curl_easy_init();

	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		
		res = curl_easy_perform(curl);
		if(res != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}

		curl_easy_cleanup(curl);
	}
	return(0);
}

int retrieve_ticker_data(char ticker[], 
		int multiplier, 
		char timespan[], 
		char from[], 
		char to[], 
		char api_key[]) {

	size_t i;
	char url[URL_SIZE];

	json_t *root;
	json_error_t error;

	snprintf(url, URL_SIZE, URL_FORMAT, &ticker, multiplier, &timespan, &from, &to, &api_key);

	return(0);
}
