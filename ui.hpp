#pragma once

#include "paper/paper_display.hpp"

#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include <Fonts/FreeSansBold24pt7b.h>
#include <GxEPD2_BW.h>

class UI {
  PaperDisplay* _display;
  uint16_t _height;
  uint16_t _width;
  uint8_t _current_row = 1;
  const uint8_t PADDING = 5;
  const uint8_t LINE_HEIGHT = 40;

  uint16_t text_width(std::string text) {
    int16_t x, y;
    uint16_t width, height;
    _display->panel.getTextBounds(text.c_str(), 0, 0, &x, &y, &width, &height);
    return width;
  }

public:
  UI(PaperDisplay* display) {
    _display = display;
    _height = display->panel.height();
    _width = display->panel.width();
  }

  void reset() {
    _display->panel.fillScreen(GxEPD_WHITE);
    _display->panel.fillRect(0, 0, 0, _height, GxEPD_BLACK);  // left sidebar
    _display->panel.setCursor(0, 3 * PADDING);
  }

  void temperature(float temp) {
    _display->panel.setFont(&FreeSansBold24pt7b);
    _display->panel.setTextSize(3);
    char buf[16];
    sprintf(buf, "%.2g", temp);
    uint16_t width = text_width(buf);
    uint16_t x = (_width - width) / 2;
    uint16_t y = LINE_HEIGHT * 3;
    _display->panel.setCursor(x, y);
    _display->panel.setTextColor(GxEPD_BLACK);
    _display->panel.print(buf);
  }

  void footer_left(std::string text) {
    _display->panel.setFont();
    _display->panel.setTextSize(1);
    _display->panel.setCursor(PADDING, _height - 2 * PADDING);
    _display->panel.print(text.c_str());
  }

  void footer_right(std::string text) {
    _display->panel.setFont();
    _display->panel.setTextSize(1);
    _display->panel.setCursor(_width - text_width(text) - PADDING, _height - 2 * PADDING);
    _display->panel.print(text.c_str());
  }
};
