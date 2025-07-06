#include "TinyFetch.h"

TinyFetch::TinyFetch(const String& url) : _baseUrl(url) {}

HttpResponse TinyFetch::makeRequest(const String& fullUrl, std::function<int(HTTPClient&)> sendRequest) {
    HTTPClient http;
    HttpResponse response;

    http.begin(fullUrl);
    int status = sendRequest(http);
    response.statusCode = status;

    if (status > 0) {
        response.payload = http.getString();
    } else {
        response.payload = http.errorToString(status);
    }

    http.end();
    return response;
}

HttpResponse TinyFetch::get(const String& path) {
    return makeRequest(_baseUrl + path, [](HTTPClient& http) {
        return http.GET();
    });
}

HttpResponse TinyFetch::post(const String& path, const String& body, const String& contentType) {
    return makeRequest(_baseUrl + path, [&](HTTPClient& http) {
        http.addHeader("Content-Type", contentType);
        return http.POST(body);
    });
}
