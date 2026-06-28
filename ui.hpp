#pragma once

#include "paper/paper_display.hpp"

#include <Fonts/FreeSansBold24pt7b.h>
#include <GxEPD2_BW.h>

class UI {
  PaperDisplay* _display;
  uint16_t _height;
  uint16_t _width;
  uint8_t _current_row = 1;
  const uint8_t PADDING = 5;

  struct SplitFloat {
    int integer_part;
    char fractional_buf[4];
  };

  SplitFloat split_float(float value) {
    SplitFloat parts;
    parts.integer_part = (int)value;
    float fractional_part = fabs(value - parts.integer_part);
    sprintf(parts.fractional_buf, ".%01d", (int)(fractional_part * 10));
    return parts;
  }

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
    _display->panel.fillTriangle(0, 0, 0, _height, _width, 0, GxEPD_BLACK);
    _display->panel.setCursor(0, 3 * PADDING);
  }

  void left_panel_value(float value) {
    _display->panel.setTextColor(GxEPD_WHITE);
    _display->panel.setFont(&FreeSansBold24pt7b);
    uint16_t x = 35;
    uint16_t y = 125;
    SplitFloat parts = split_float(value);
    // integer part
    _display->panel.setCursor(x, y);
    _display->panel.setTextSize(2);
    _display->panel.print(parts.integer_part);
    // fractional part
    uint16_t integer_width = text_width(std::to_string(parts.integer_part));
    _display->panel.setCursor(x + integer_width + 9, y + 1);  // 9 & 1 are padding
    _display->panel.setTextSize(1);
    _display->panel.print(parts.fractional_buf);
  }

  void right_panel_value(float value) {
    _display->panel.setTextColor(GxEPD_BLACK);
    _display->panel.setFont(&FreeSansBold24pt7b);
    uint16_t x = 215;
    uint16_t y = 250;
    SplitFloat parts = split_float(value);
    // integer part
    _display->panel.setCursor(x, y);
    _display->panel.setTextSize(2);
    _display->panel.print(parts.integer_part);
    // fractional part
    uint16_t integer_width = text_width(std::to_string(parts.integer_part));
    _display->panel.setCursor(x + integer_width + 9, y + 1);  // 9 & 1 are padding
    _display->panel.setTextSize(1);
    _display->panel.print(parts.fractional_buf);
  }

  void footer_left(std::string text) {
    _display->panel.setTextColor(GxEPD_BLACK);
    _display->panel.setFont();
    _display->panel.setTextSize(1);
    _display->panel.setCursor(PADDING, _height - 2 * PADDING);
    _display->panel.print(text.c_str());
  }

  void footer_right(std::string text) {
    _display->panel.setTextColor(GxEPD_BLACK);
    _display->panel.setFont();
    _display->panel.setTextSize(1);
    _display->panel.setCursor(_width - text_width(text) - PADDING, _height - 2 * PADDING);
    _display->panel.print(text.c_str());
  }
};
