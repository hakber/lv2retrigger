/* retrigger.cpp
 * This code is available at <http://github.com/hakber/lv2retrigger>

 * Copyright (c) 2012, Håkan Bernhardsson
 * 	published under GPL v3.
 * See COPYING for more information about the redistribution license

 * THIS SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <lv2plugin.hpp>
#include <iostream>

using namespace LV2;


class retrigger : public Plugin<retrigger> {
public:
  uint32_t counter;
  int bufLen;
  float *lBuffer, *rBuffer;
  float sample_rate, bpm, trigger;

  retrigger(double rate)
    : Plugin<retrigger>(6) {
    sample_rate=rate;
  }
  
  void activate(){
    bufLen=(int) sample_rate * ((60/bpm)/trigger);
    int max=(int) 15*sample_rate;

    lBuffer=new float[max];
    rBuffer=new float[max];
    counter=0;
  }

  void run(uint32_t nframes) {
    
    bpm = *p(0);
    trigger = *p(1);
    bufLen=(int) sample_rate * ((60/bpm)/trigger);    
    for (uint32_t i = 0; i < nframes; ++i) {
      if(counter<bufLen){
        p(4)[i]=p(2)[i];
        p(5)[i]=p(3)[i];

        lBuffer[counter]=p(2)[i];
        rBuffer[counter]=p(3)[i];
      }
      else{
        int temp=counter%bufLen;
        p(4)[i]=lBuffer[temp];
        p(5)[i]=rBuffer[temp];
      }
      if(counter<=bufLen)counter++;
    }    
  }

};

static int _ = retrigger::register_class("http://github.com/hakber/lv2retrigger");
