#include "TinyFetch.h"

TinyFetch::TinyFetch(const String& url) : _baseUrl(url) {}

HttpResponse TinyFetch::get(const String& path) {
    HTTPClient http;
    HttpResponse response;

    String fullUrl = _baseUrl + path;
    http.begin(fullUrl);

    int status = http.GET();
    response.statusCode = status;

    if (status > 0) {
        response.payload = http.getString();
    } else {
        response.payload = http.errorToString(status);
    }

    http.end();
    return response;
}
