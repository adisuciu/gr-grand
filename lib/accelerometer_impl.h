/* -*- c++ -*- */
/*
 * Copyright 2022 gr-grand author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_GRAND_ACCELEROMETER_IMPL_H
#define INCLUDED_GRAND_ACCELEROMETER_IMPL_H

#include <gnuradio/grand/accelerometer.h>
#include <android/sensor.h>

namespace gr {
  namespace grand {

    class accelerometer_impl : public accelerometer
    {
     private:
      bool start() override;

     public:
      accelerometer_impl();
      ~accelerometer_impl();

      int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
    } override;

  } // namespace grand
} // namespace gr

#endif /* INCLUDED_GRAND_ACCELEROMETER_IMPL_H */
