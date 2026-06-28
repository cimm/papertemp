#pragma once

// WiFi credentials
#define WIFI_SSID "ssid"
#define WIFI_PASSWORD "password"

// Netatmo API configuration
#define NETATMO_TOKEN "token"
#define NETATMO_DEVICE_ID "device id"
#define NETATMO_MODULE_ID "module id"

// Date & time
#define TIME_ZONE "CET-1CEST,M3.5.0,M10.5.0/3"  // See https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv
#define NTP_POOL "pool.ntp.org"

#define REFRESH_RATE 900  // in seconds

constexpr bool _strings_equal(const char* a, const char* b) {
  return *a == *b && (*a == '\0' || _strings_equal(a + 1, b + 1));
}

static_assert(!_strings_equal(WIFI_SSID, "ssid"), "WIFI_SSID is still set to the default value!");
static_assert(!_strings_equal(WIFI_PASSWORD, "password"), "WIFI_PASSWORD is still set to the default value!");
