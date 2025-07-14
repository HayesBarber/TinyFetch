#include "TinyFetch.h"
#include <MicroStorage.h>

TinyFetch::TinyFetch(const String& baseUrl) : _baseUrl(baseUrl) {}

HttpResponse TinyFetch::makeRequest(const String& path, std::function<int(HTTPClient&)> sendRequest) {
    HTTPClient http;
    HttpResponse response;

    String fullUrl = _baseUrl + path;
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

void TinyFetch::persistBaseUrl() {
    MicroStorage::set("TinyFetch",
        StringEntry("baseUrl", _baseUrl)
    );   
}

String TinyFetch::getBaseUrl() {
    auto [value] = MicroStorage::get("TinyFetch",
        StringEntry("baseUrl", "")
    );

    return value;
}

HttpResponse TinyFetch::get(const String& path) {
    return makeRequest(path, [](HTTPClient& http) {
        return http.GET();
    });
}

HttpResponse TinyFetch::post(const String& path, const String& body, const String& contentType) {
    return makeRequest(path, [&](HTTPClient& http) {
        http.addHeader("Content-Type", contentType);
        return http.POST(body);
    });
}

HttpResponse TinyFetch::put(const String& path, const String& body, const String& contentType) {
    return makeRequest(path, [&](HTTPClient& http) {
        http.addHeader("Content-Type", contentType);
        return http.PUT(body);
    });
}

HttpResponse TinyFetch::del(const String& path) {
    return makeRequest(path, [](HTTPClient& http) {
        return http.sendRequest("DELETE");
    });
}
