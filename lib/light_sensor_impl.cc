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
#include "light_sensor_impl.h"
#include <boost/format.hpp>

namespace gr {
  namespace grand {

    #pragma message("set the following appropriately and remove this warning")
    using output_type = float;
    light_sensor::sptr
    light_sensor::make()
    {
      return gnuradio::make_block_sptr<light_sensor_impl>(
        );
    }


    /*
     * The private constructor
     */
    light_sensor_impl::light_sensor_impl()
      : gr::sync_block("light_sensor",
                       gr::io_signature::make(0, 0, 0),
                       gr::io_signature::make(1, 1, sizeof(float))),
        gr::grand::sensor_base(ASENSOR_TYPE_LIGHT)
    {
      set_max_noutput_items(200);
    }

    /*
     * Our virtual destructor.
     */
    light_sensor_impl::~light_sensor_impl()
    {
    }

    bool
    light_sensor_impl::start()
    {
      init();
      return sync_block::start();
    }

    int
    light_sensor_impl::work(int noutput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      float *out = (float*) output_items[0];

      //GR_INFO("grand::light_sensor", boost::str(boost::format("entered: %1%") % noutput_items));

      for(int i = 0; i < noutput_items; i++) {
        int ident = ALooper_pollOnce(-1, NULL, NULL, NULL);
        //GR_INFO("grand::light_sensor", boost::str(boost::format("LOOPER POLLED, ret: %1%") % ident));

        // Wait for callback to signal us
        block_on_sensor();

        if(ident == ALOOPER_POLL_CALLBACK) {
          if(d_sensor != NULL) {
            ASensorEvent event;
            if(ASensorEventQueue_getEvents(d_event_queue, &event, 1) > 0) {
              out[i] = event.light;
            }
          }
        }
      }

      //GR_INFO("grand::light_sensor", boost::str(boost::format("ret: %1% -> %2%") \
      //                                     % noutput_items % (out[0])));
      return noutput_items;
    }

  } /* namespace grand */
} /* namespace gr */
