#include "TinyFetch.h"
#include <MicroStorage.h>

TinyFetch::TinyFetch() : _baseUrl("") {}

TinyFetch::TinyFetch(const String &baseUrl) : _baseUrl(baseUrl) {}

void TinyFetch::init() {
  if (_baseUrl.isEmpty()) {
    _baseUrl = getBaseUrl();
  } else {
    persistBaseUrl();
  }
}

void TinyFetch::setBaseUrl(const String &baseUrl) {
  _baseUrl = baseUrl;
  persistBaseUrl();
}

HttpResponse
TinyFetch::makeRequest(const String &path,
                       std::function<int(HTTPClient &)> sendRequest) {
  if (_baseUrl.isEmpty()) {
    Serial.println("[TinyFetch] No base url set");
    HttpResponse errorResponse;
    errorResponse.statusCode = -1;
    errorResponse.payload = "No base URL set.";
    return errorResponse;
  }

  HTTPClient http;
  HttpResponse response;

  String encodedPath = encodePath(path);
  String fullUrl = _baseUrl + encodedPath;
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
  MicroStorage::set("TinyFetch", StringEntry("baseUrl", _baseUrl));
}

String TinyFetch::encodePath(const String &path) {
  String encodedPath = path;
  int index = 0;
  while ((index = encodedPath.indexOf(' ', index)) >= 0) {
    encodedPath.remove(index, 1);
    encodedPath =
        encodedPath.substring(0, index) + "%20" + encodedPath.substring(index);
    index += 3;
  }
  return encodedPath;
}

String TinyFetch::getBaseUrl() {
  auto [value] = MicroStorage::get("TinyFetch", StringEntry("baseUrl", ""));

  return value;
}

HttpResponse TinyFetch::get(const String &path) {
  return makeRequest(path, [](HTTPClient &http) { return http.GET(); });
}

HttpResponse TinyFetch::post(const String &path, const String &body,
                             const String &contentType) {
  return makeRequest(path, [&](HTTPClient &http) {
    http.addHeader("Content-Type", contentType);
    return http.POST(body);
  });
}

HttpResponse TinyFetch::put(const String &path, const String &body,
                            const String &contentType) {
  return makeRequest(path, [&](HTTPClient &http) {
    http.addHeader("Content-Type", contentType);
    return http.PUT(body);
  });
}

HttpResponse TinyFetch::del(const String &path) {
  return makeRequest(
      path, [](HTTPClient &http) { return http.sendRequest("DELETE"); });
}
