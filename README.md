# TinyFetch

TinyFetch is a lightweight HTTP client wrapper using the Arduino ESP32 `HTTPClient` library. It simplifies making HTTP requests (GET, POST, PUT, DELETE) by providing a clean and consistent interface for interacting with RESTful APIs.

## Features

- Simple interface for HTTP GET, POST, PUT, DELETE
- Configurable base URL
- Returns structured responses with status code and payload

## Usage

```cpp
#include <TinyFetch.h>

TinyFetch client("http://example.com");

// GET request
HttpResponse res = client.get("/api/status");
Serial.println(res.statusCode);
Serial.println(res.payload);

// POST request
HttpResponse postRes = client.post("/api/data", "{\"key\":\"value\"}");

// PUT request
HttpResponse putRes = client.put("/api/data/1", "{\"key\":\"new value\"}");

// DELETE request
HttpResponse delRes = client.del("/api/data/1");
```

## Response Structure

The result of any request is an `HttpResponse` struct:

```cpp
struct HttpResponse {
    int statusCode;  // HTTP status code
    String payload;  // Response body
};
```
