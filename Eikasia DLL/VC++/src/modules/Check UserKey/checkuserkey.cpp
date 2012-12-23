#include <windows.h>
#include <stdio.h>
/*#include <curl/curl.h>

void tweet(void) {
	char msg[256];

	sprintf(msg, "tweet=%d", 1);
	
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
	//curl_init();

	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "http://antrixro.es/app/twitter/tweet.php");
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, msg);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
}*/