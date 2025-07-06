#ifndef TINY_FETCH_H
#define TINY_FETCH_H

#include <Arduino.h>
#include <HTTPClient.h>
#include <functional>

struct HttpResponse {
    int statusCode = -1;
    String payload;
};

class TinyFetch {
public:
    TinyFetch(const String& url);
    HttpResponse get(const String& path);
    HttpResponse post(const String& path, const String& body, const String& contentType = "application/json");
    HttpResponse put(const String& path, const String& body, const String& contentType = "application/json");
    HttpResponse del(const String& path);

private:
    String _baseUrl;
    HttpResponse makeRequest(const String& fullUrl, std::function<int(HTTPClient&)> sendRequest);
};

#endif
