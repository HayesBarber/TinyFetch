#ifndef TINY_FETCH_H
#define TINY_FETCH_H

#include <Arduino.h>
#include <HTTPClient.h>

struct HttpResponse {
    int statusCode = -1;
    String payload;
};

class TinyFetch {
public:
    TinyFetch(const String& url);
    HttpResponse get(const String& path);
    HttpResponse post(const String& path, const String& body, const String& contentType = "application/json");

private:
    String _baseUrl;
};

#endif
