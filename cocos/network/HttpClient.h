/****************************************************************************
 Copyright (c) 2012      greathqy
 Copyright (c) 2012      cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __CCHTTPCLIENT_H__
#define __CCHTTPCLIENT_H__

#include <thread>
#include <string>
#include <condition_variable>
#include "base/CCVector.h"
#include "base/CCScheduler.h"
#include "network/HttpRequest.h"
#include "network/HttpResponse.h"
#include "network/HttpCookie.h"

/**
 * @addtogroup network
 * @{
 */

NS_CC_BEGIN

namespace network {

	// my addition
	//struct receivedStringStruct {
	//	char *pcData;
	//	size_t iLen;
	//};

/** Singleton that handles asynchronous http requests.
 *
 * Once the request completed, a callback will issued in main thread when it provided during make request.
 *
 * @lua NA
 */
class CC_DLL HttpClient
{
public:
    /**
    * The buffer size of _responseMessage
    */
    static const int RESPONSE_BUFFER_SIZE = 256;

    /**
     * Get instance of HttpClient.
     *
     * @return the instance of HttpClient.
     */
    static HttpClient *getInstance();

    /**
     * Release the instance of HttpClient.
     */
    static void destroyInstance();

    /**
     * Enable cookie support.
     *
     * @param cookieFile the filepath of cookie file.
     */
    void enableCookies(const char* cookieFile);

    /**
     * Get the cookie filename
     *
     * @return the cookie filename
     */
    const std::string& getCookieFilename();

    /**
     * Set root certificate path for SSL verification.
     *
     * @param caFile a full path of root certificate.if it is empty, SSL verification is disabled.
     */
    void setSSLVerification(const std::string& caFile);

    /**
     * Get the ssl CA filename
     *
     * @return the ssl CA filename
     */
    const std::string& getSSLVerification();

    /**
     * Add a get request to task queue
     *
     * @param request a HttpRequest object, which includes url, response callback etc.
                      please make sure request->_requestData is clear before calling "send" here.
     */
    void send(HttpRequest* request);

    /**
     * Immediate send a request
     *
     * @param request a HttpRequest object, which includes url, response callback etc.
                      please make sure request->_requestData is clear before calling "sendImmediate" here.
     */
    void sendImmediate(HttpRequest* request);

    /**
     * Set the timeout value for connecting.
     *
     * @param value the timeout value for connecting.
     */
    void setTimeoutForConnect(int value);

    /**
     * Get the timeout value for connecting.
     *
     * @return int the timeout value for connecting.
     */
    int getTimeoutForConnect();

    /**
     * Set the timeout value for reading.
     *
     * @param value the timeout value for reading.
     */
    void setTimeoutForRead(int value);

	// My additions
	static int downloadProgressFunc(void *ptr, double totalToDownload, double nowDownloaded, double totalToUpLoad, double nowUpLoaded) {
	//static int downloadProgressFunc(void *clientp,   curl_off_t dltotal,   curl_off_t dlnow,   curl_off_t ultotal,   curl_off_t ulnow)	{ /cocos2dx curl version too old for this! (older than 7.32.0)
		ffDownloaded = nowDownloaded;
		//CCLOG("downloaded = %f", ffDownloaded);// This method currently never called under Android!!? IOS? - It is under windows.
		return 0;
	};
	static double getDownloaded(void) {
		return ffDownloaded;
	};
	static void zeroDownloaded(void) {ffDownloaded = 0;};
	static double ffDownloaded;
	static void freeRequest(void);
	//static CURLcode getStringUsingEasyCurl(const char* url, network::receivedStringStruct receivedString);
//	static int getStringUsingEasyCurl(const char* url, network::receivedStringStruct  *pReceivedString);
//	static size_t writeBlock(void *pvBlockData, size_t size, size_t nmemb, struct receivedStringStruct *receivedString);

// my additions

/*
	static size_t writeBlock(void *pvBlockData, size_t size, size_t nmemb, struct receivedStringStruct *receivedString) {
		size_t iThisBlockSize = size * nmemb;
		size_t iNewSize = receivedString->iLen + iThisBlockSize;
		receivedString->pcData = (char *)realloc(receivedString->pcData, iNewSize + 1); // + 1 - Allow for String terminator!
		if (receivedString->pcData == NULL) {
			fprintf(stderr, "realloc() failed\n");
			exit(EXIT_FAILURE);
		}
		else {
			//CCLOG( "pcData = %s", receivedString->pcData);
		}
		memcpy(receivedString->pcData + receivedString->iLen, pvBlockData, iThisBlockSize);
		receivedString->pcData[iNewSize] = '\0'; //String terminator!
		receivedString->iLen = iNewSize;
		return iThisBlockSize;
	}

	static int getStringUsingEasyCurl(const char* url, receivedStringStruct *pReceivedString)
	{
		CURL *curl;       // CURL objects
		CURLcode res = CURLE_FAILED_INIT;
		curl = curl_easy_init(); // init CURL library object/structure


		if (curl) {

			//struct receivedString s;
			pReceivedString->iLen = 0;
			if (pReceivedString->pcData == NULL) {
				pReceivedString->pcData = (char *)malloc(pReceivedString->iLen + 1);
				pReceivedString->pcData[pReceivedString->iLen] = '\0'; //String terminator!
			}
			//res = curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 2L);
			//        res = curl_easy_setopt(curl, CURLOPT_URL, "https://www.googleapis.com/storage/v1/b/markv/o/f1%2FFRED");//url);
			res = curl_easy_setopt(curl, CURLOPT_URL, url);
			//res = curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
			res = curl_easy_setopt(curl, CURLOPT_VERBOSE, 1); // tell us what is happening
															  //curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/4.0 (compatible; MSIE 5.01; Windows NT 5.0)");
															  //res = curl_easy_setopt(curl, CURLOPT_REDIR_PROTOCOLS, 0xffffffffffffffffL);
															  //res = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, true); // 2014_06_30 - had no effect!

															  // tell libcurl where to write the image (to a dynamic memory buffer)

			res = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &HttpClient::writeBlock);
			res = curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)pReceivedString);

			// experimental
			// For following see http://stackoverflow.com/questions/18884821/enable-ssl-connection-for-https-in-curl-php-header-blank
			///		res = curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true); // allow https verification if true
			//		res = curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2); // check common name and verify with host name
			///		res = curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0); // prevent actual verification!
			//		res = curl_easy_setopt(curl, CURLOPT_SSLVERSION, 3); // verify ssl version 2 or 3

			res = curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
			// end experimantal
			// get the image from the specified URL

			res = curl_easy_perform(curl);
			CCLOG("Curl code: %i", res);
			curl_easy_cleanup(curl);
		}
		return res;
	}
	// end of my additions
*/




// End of my additions

	/**
     * Get the timeout value for reading.
     *
     * @return int the timeout value for reading.
     */
    int getTimeoutForRead();

    HttpCookie* getCookie() const {return _cookie; }

    std::mutex& getCookieFileMutex() {return _cookieFileMutex;}

    std::mutex& getSSLCaFileMutex() {return _sslCaFileMutex;}
private:
    HttpClient();
    virtual ~HttpClient();
    bool init();

    /**
     * Init pthread mutex, semaphore, and create new thread for http requests
     * @return bool
     */
    bool lazyInitThreadSemphore();
    void networkThread();
    void networkThreadAlone(HttpRequest* request, HttpResponse* response);
    /** Poll function called from main thread to dispatch callbacks when http requests finished **/
    void dispatchResponseCallbacks();

    void processResponse(HttpResponse* response, char* responseMessage);
    void increaseThreadCount();
    void decreaseThreadCountAndMayDeleteThis();

private:
    bool _isInited;

    int _timeoutForConnect;
    std::mutex _timeoutForConnectMutex;

    int _timeoutForRead;
    std::mutex _timeoutForReadMutex;

    int  _threadCount;
    std::mutex _threadCountMutex;

    Scheduler* _scheduler;
    std::mutex _schedulerMutex;

    Vector<HttpRequest*>  _requestQueue;
    std::mutex _requestQueueMutex;

    Vector<HttpResponse*> _responseQueue;
    std::mutex _responseQueueMutex;

    std::string _cookieFilename;
    std::mutex _cookieFileMutex;

    std::string _sslCaFilename;
    std::mutex _sslCaFileMutex;

    HttpCookie* _cookie;

    std::condition_variable_any _sleepCondition;

    char _responseMessage[RESPONSE_BUFFER_SIZE];

    HttpRequest* _requestSentinel;

};

} // namespace network

NS_CC_END

// end group
/// @}

#endif //__CCHTTPCLIENT_H__

