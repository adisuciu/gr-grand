/* -*- c++ -*- */
/*
 * Copyright 2022 gr-grand author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include <gnuradio/logger.h>
#include "accelerometer_impl.h"
#include <boost/format.hpp>

namespace gr {
  namespace grand {

    using output_type = float;
    accelerometer::sptr
    accelerometer::make()
    {
      return gnuradio::make_block_sptr<accelerometer_impl>(
        );
    }


    /*
     * The private constructor
     */
    accelerometer_impl::accelerometer_impl()
      : gr::sync_block("accelerometer",
                       gr::io_signature::make(0, 0, 0),
                       gr::io_signature::make(3, 3, sizeof(float))),
        gr::grand::sensor_base(ASENSOR_TYPE_ACCELEROMETER)
    {
      set_max_noutput_items(200);
    }

    /*
     * Our virtual destructor.
     */
    accelerometer_impl::~accelerometer_impl()
    {
    }

    bool
    accelerometer_impl::start()
    {
      init();
      return sync_block::start();
    }

    int
    accelerometer_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      float *outx = (float*) output_items[0];
      float *outy = (float*) output_items[1];
      float *outz = (float*) output_items[2];

      GR_INFO("grand::accelerometer", boost::str(boost::format("entered: %1%") % noutput_items));

      for(int i = 0; i < noutput_items; i++) {
        int ident = ALooper_pollOnce(-1, NULL, NULL, NULL);
        //GR_INFO("grand::accelerometer", boost::str(boost::format("LOOPER POLLED, ret: %1%") % ident));

        // Wait for callback to signal us
        block_on_sensor();

        if(ident == ALOOPER_POLL_CALLBACK) {
          if(d_sensor != NULL) {
            ASensorEvent event;
            if(ASensorEventQueue_getEvents(d_event_queue, &event, 1) > 0) {
              //GR_INFO("grand::accelerometer", boost::str(boost::format("GETTING DATA: %1%") % event.acceleration.x));
              outx[i] = event.acceleration.x;
              outy[i] = event.acceleration.y;
              outz[i] = event.acceleration.z;
            }
          }
        }
      }

      //GR_INFO("grand::accelerometer", boost::str(boost::format("ret: %1% -> %2%") \
      //                                     % noutput_items % (outx[0])));
      return noutput_items;
    }

  } /* namespace grand */
} /* namespace gr */
