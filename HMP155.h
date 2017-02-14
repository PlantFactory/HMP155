/*
 * HMP155.h
 *
 * Author:   Makoto Uju (ainehanta)
 * URL:      https://github.com/PlantFactory/HMP155
 * License:  MIT License
 * Created:  2016-10-10
 * Based on Hiromasa Ihara (miettal)'s Source Code
 */

#ifndef HMP155_h
#define HMP155_h

#include <Arduino.h>

class HMP155 {
  private:
    Stream &stream;
    uint8_t rw_pin;

    // この３つは書き込まれたくないので…
    float _ta; // Temperature of additonal sensor
    float _tw; // Temperature of wet-bulb
    float _rh; // Relative humidity

    bool ready = false;

    bool parseResponce(String responce, float result[], uint8_t result_length);

    inline float calcE(float t) { return 0.61365*exp((17.502*t)/(240.97+t)); }

  public:
    HMP155(Stream &stream, uint8_t rw_pin) : stream(stream), rw_pin(rw_pin) {
      pinMode(rw_pin, OUTPUT);
    }

    void begin(void);
    bool read(void);

    float ta(void) { return this->_ta; }
    float tw(void) { return this->_tw; }
    float rh(void) { return this->_rh; }
    float vpd(void);
};

#endif
