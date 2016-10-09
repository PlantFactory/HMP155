/*
 * HMP155.cpp
 *
 * Author:   Makoto Uju (ainehanta)
 * URL:      https://github.com/PlantFactory/HMP155
 * License:  MIT License
 * Created:  2016-10-10
 * Based on Hiromasa Ihara (miettal)'s Source Code
 */

#include <Arduino.h>
#include "HMP155.h"

#include <string.h>

void HMP155::begin(void) {
  digitalWrite(this->rw_pin, HIGH);
  this->stream.print("FORM 2.2 Ta \",\" 2.2 Tw \",\" 2.2 RH #r #n\r");
  this->stream.flush();
  digitalWrite(this->rw_pin, LOW);
  this->stream.readStringUntil('\n'); // recv: "OK"
}

bool HMP155::read(void) {
  String responce;
  char token_buf[20];
  char *token_ptr;

  digitalWrite(this->rw_pin, HIGH);
  this->stream.print("SEND\r");
  this->stream.flush();
  digitalWrite(this->rw_pin, LOW);
  responce = this->stream.readStringUntil('\n'); // recv: "??.??,??.??,??.??"
  responce.toCharArray(token_buf, 20);

  token_ptr = strtok(token_buf, ",");
  this->ta = atof(token_ptr);
  token_ptr = strtok(NULL, ",");
  this->tw = atof(token_ptr);
  token_ptr = strtok(NULL, ",");
  this->rh = atof(token_ptr);
}

float HMP155::vpd(void) {
  float e_ta = this->calcE(this->_ta);
  float e_tw = this->calcE(this->_tw);
  float es = e_tw - 0.000662*101.325*(this->_ta - this->_tw);

  return e_ta > es ? e_ta - es : 0.0;
}
