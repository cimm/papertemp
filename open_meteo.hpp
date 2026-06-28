#pragma once

#include <HTTPClient.h>
#include <ArduinoJson.h>

class OpenMeteo {
  std::string _latitude;
  std::string _longitude;

  std::string fetch_reading() {
    HTTPClient http;
    std::string url = "https://api.open-meteo.com/v1/forecast?latitude=" + _latitude + "&longitude=" + _longitude + "&current=temperature_2m";
    http.begin(url.c_str());
    uint16_t httpCode = http.GET();
    if (httpCode != HTTP_CODE_OK) {
      last_error_message = "Invalid OpenMeteo response";
    }
    std::string response = http.getString().c_str();
    http.end();
    return response;
  }

public:
  std::string last_error_message;

  OpenMeteo(std::string latitude, std::string longitude) {
    _latitude = latitude;
    _longitude = longitude;
  }

  float temperature() {
    last_error_message.clear();
    std::string response = fetch_reading();
    const size_t capacity = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + 210;
    DynamicJsonDocument doc(capacity);
    DeserializationError error = deserializeJson(doc, response);
    if (error) {
      last_error_message = "Couldn't parse temperature from OpenMeteo response";
      return 0.0f;
    }
    if (!doc["current"].containsKey("temperature_2m")) {
      last_error_message = "Couldn't parse temperature from OpenMeteo response";
      return 0.0f;
    }
    return doc["current"]["temperature_2m"].as<float>();
  }

  bool error() {
    return !last_error_message.empty();
  }
};
