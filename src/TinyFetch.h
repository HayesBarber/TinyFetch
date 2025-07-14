#ifndef TINY_FETCH_H
#define TINY_FETCH_H

#include <Arduino.h>
#include <HTTPClient.h>
#include <functional>

/**
 * @brief Represents the result of an HTTP request.
 */
struct HttpResponse {
    int statusCode = -1;
    String payload;
};

/**
 * @brief A lightweight HTTP client wrapper using the Arduino HTTPClient library.
 *
 * TinyFetch simplifies making HTTP requests (GET, POST, PUT, DELETE) to a base URL.
 */
class TinyFetch {
public:
    /**
     * @brief Default constructor for TinyFetch.
     * Initializes TinyFetch and attempts to read the base URL from persistent storage.
     */
    TinyFetch();

    /**
     * @brief Constructs a TinyFetch client with the specified base URL.
     * The provided base URL will be persisted for future use.
     * @param url The base URL to which all requests will be made.
     */
    TinyFetch(const String& baseUrl);

    /**
     * @brief Sets the base URL for all subsequent HTTP requests.
     * The provided base URL will be persisted for future use.
     * @param baseUrl The base URL to which all requests will be made.
     */
    void setBaseUrl(const String& baseUrl);

    /**
     * @brief Performs an HTTP GET request.
     * @param path The path to append to the base URL.
     * @return An HttpResponse containing the status code and payload.
     */
    HttpResponse get(const String& path);

    /**
     * @brief Performs an HTTP POST request.
     * @param path The path to append to the base URL.
     * @param body The request body to send.
     * @param contentType The content type of the request body (default is "application/json").
     * @return An HttpResponse containing the status code and payload.
     */
    HttpResponse post(const String& path, const String& body, const String& contentType = "application/json");

    /**
     * @brief Performs an HTTP PUT request.
     * @param path The path to append to the base URL.
     * @param body The request body to send.
     * @param contentType The content type of the request body (default is "application/json").
     * @return An HttpResponse containing the status code and payload.
     */
    HttpResponse put(const String& path, const String& body, const String& contentType = "application/json");

    /**
     * @brief Performs an HTTP DELETE request.
     * @param path The path to append to the base URL.
     * @return An HttpResponse containing the status code and payload.
     */
    HttpResponse del(const String& path);

private:
    String _baseUrl;
    HttpResponse makeRequest(const String& path, std::function<int(HTTPClient&)> sendRequest);
    void persistBaseUrl();
    String getBaseUrl();
};

#endif
