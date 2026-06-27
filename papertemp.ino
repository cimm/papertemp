#include "config.hpp"
#include "paper/paper_datetime.hpp"
#include "paper/paper_device.hpp"
#include "paper/paper_display.hpp"
#include "paper/paper_sound.hpp"
#include "paper/paper_wifi.hpp"
#include "netatmo.hpp"
#include "ui.hpp"

#include <time.h>
#include <vector>

PaperDevice device;
PaperDatetime device_datetime;
PaperDisplay device_display;
PaperSound device_sound;
PaperWifi device_wifi;
UI ui(&device_display);
bool error = false;
tm today = { 0 };

void setup() {
  Serial.begin(9600);
  connect_wifi();
  get_datetimes();
  reset_ui();
  temperature_to_display();
  refresh_datetime_to_display();
  disconnect_wifi();
  refresh_display();
  deep_sleep();
}

void loop() {}

void connect_wifi() {
  device_wifi.connect(WIFI_SSID, WIFI_PASSWORD);
}

void temperature_to_display() {
  Netatmo netatmo(NETATMO_TOKEN, NETATMO_DEVICE_ID, NETATMO_MODULE_ID);
  float temp = netatmo.temperature();
  if (netatmo.error()) {
    set_error(netatmo.last_error_message.c_str());
    return;
  }
  Serial.printf("Netatmo reported %.2f degrees\n", temp);
  ui.temperature(temp);
}

void disconnect_wifi() {
  device_wifi.disconnect();
}

void get_datetimes() {
  device_datetime.fetch(TIME_ZONE, NTP_POOL);
  today = device_datetime.time_info;
}

void reset_ui() {
  ui.reset();
}

void refresh_display() {
  device_display.enable_display();
  device_display.panel.display();
}

void set_error(const char* error_message) {
  error = true;
  Serial.println(error_message);
  device_sound.clicks(3);
  ui.footer_left(error_message);
}

void refresh_datetime_to_display() {
  char formatted_date[12];
  strftime(formatted_date, sizeof(formatted_date), "%d/%m %H:%M", &today);
  ui.footer_right(formatted_date);
}

void deep_sleep() {
  device.sleep_timer_and_button_wakeup(60 * 15); // 15 min
}
