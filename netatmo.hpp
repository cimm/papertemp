#pragma once

#include <HTTPClient.h>

class Netatmo {
  std::string _token;
  std::string _device_id;
  std::string _module_id;

  std::string fetch_reading() {
    HTTPClient http;
    http.begin("https://app.netatmo.net/api/getmeasure");
    http.addHeader("Authorization", ("Bearer " + _token).c_str());
    std::string payload = "{\"device_id\":\"" + _device_id + "\","
                          "\"module_id\":\"" + _module_id + "\","
                          "\"scale\":\"max\","
                          "\"type\":\"Temperature\","
                          "\"date_end\":\"last\","
                          "\"limit\":1}";
    uint16_t httpCode = http.POST(payload.c_str());
    if (httpCode != HTTP_CODE_OK) {
      last_error_message = "Invalid Netatmo response";
    }
    std::string response = http.getString().c_str();
    http.end();
    return response;
  }

public:
  std::string last_error_message;

  Netatmo(std::string token, std::string device_id, std::string module_id) {
    _token = token;
    _device_id = device_id;
    _module_id = module_id;
  }

  float temperature() {
    last_error_message.clear();
    std::string response = fetch_reading();
    const std::string pattern = "\"value\":[[";
    size_t start = response.find(pattern);
    if (start == std::string::npos) {
      last_error_message = "Couldn't parse temperature from Netatmo response";
      return 0.0f;
    }
    start += pattern.length();
    size_t end = response.find("]]", start);
    if (end == std::string::npos) {
      last_error_message = "Couldn't parse temperature from Netatmo response";
      return 0.0f;
    }
    std::string temp_str = response.substr(start, end - start);
    return std::stof(temp_str);
  }

  bool error() {
    return !last_error_message.empty();
  }
};
