#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>
#include <jansson.h>

#define URL_FORMAT "https://api.polygon.io/v2/aggs/ticker/%s/range/%d/%s/%s/%s?apiKey=%s"
#define URL_SIZE 256 
#define BUFFER_SIZE 2048

struct MemoryStruct {
	char *memory;
	size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
	size_t realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *)userp;

	char *ptr = realloc(mem->memory, mem->size + realsize + 1);

	if(!ptr) {
		fprintf(stderr, "Not enough memory (realloc return NULL)\n");
		return(0);
	}

	mem->memory = ptr;
	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	return realsize;
}

struct MemoryStruct * http_get(char *url) {
	CURL *curl_handle;
	CURLcode res;
	
	struct MemoryStruct chunk;
	struct MemoryStruct * pStruct;

	chunk.memory = malloc(1); // grown as needed by the realloc above
	chunk.size = 0;

	curl_global_init(CURL_GLOBAL_ALL);

	curl_handle = curl_easy_init();

	curl_easy_setopt(curl_handle, CURLOPT_URL, url); // defines the url that will be queried
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);

	curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0"); /* setting up user agent for some websites */

	res = curl_easy_perform(curl_handle);

	if (res != CURLE_OK) {
		fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));
		curl_easy_cleanup(curl_handle);
		exit(1);
	} else {
		pStruct = &chunk;
		curl_easy_cleanup(curl_handle);
		return pStruct;
	}
}
