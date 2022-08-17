/* -*- c++ -*- */
/*
 * Copyright 2022 gr-grand author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_GRAND_LIGHT_SENSOR_IMPL_H
#define INCLUDED_GRAND_LIGHT_SENSOR_IMPL_H

#include <gnuradio/grand/light_sensor.h>
#include <android/sensor.h>

namespace gr {
  namespace grand {

    class light_sensor_impl : public light_sensor
    {
     private:
      bool start();

     public:
      light_sensor_impl();
      ~light_sensor_impl();

      int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
    };

  } // namespace grand
} // namespace gr

#endif /* INCLUDED_GRAND_LIGHT_SENSOR_IMPL_H */
