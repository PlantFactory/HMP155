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
  flushSerialRecvBuffuer();

  digitalWrite(this->rw_pin, HIGH);
  this->stream.print("FORM 2.2 Ta \",\" 2.2 Tw \",\" 2.2 RH #r #n\r");
  this->stream.flush();
  digitalWrite(this->rw_pin, LOW);
  Serial.print("HMP155 : ");
  Serial.println(this->stream.readString());
}

bool HMP155::read(void) {
  char token_buf[20];
  char *token_ptr;

  digitalWrite(this->rw_pin, HIGH);
  this->stream.print("SEND\r");
  this->stream.flush();
  digitalWrite(this->rw_pin, LOW);

  this->stream.readBytesUntil('\n', token_buf, 20); // recv: "??.??,??.??,??.??"
  Serial.print("HMP155 : ");
  Serial.println(token_buf);

  token_ptr = strtok(token_buf, ",");
  this->_ta = atof(token_ptr);
  token_ptr = strtok(NULL, ",");
  this->_tw = atof(token_ptr);
  token_ptr = strtok(NULL, ",");
  this->_rh = atof(token_ptr);

  return true;
}

float HMP155::vpd(void) {
  float e_ta = this->calcE(this->_ta);
  float e_tw = this->calcE(this->_tw);
  float es = e_tw - 0.000662*101.325*(this->_ta - this->_tw);

  return e_ta > es ? e_ta - es : 0.0;
}
