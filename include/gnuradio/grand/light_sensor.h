/* -*- c++ -*- */
/*
 * Copyright 2022 gr-grand author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_GRAND_LIGHT_SENSOR_H
#define INCLUDED_GRAND_LIGHT_SENSOR_H

#include <gnuradio/grand/api.h>
#include <gnuradio/sync_block.h>
#include <gnuradio/grand/sensor_base.h>

namespace gr {
  namespace grand {

    /*!
     * \brief <+description of block+>
     * \ingroup grand
     *
     */
    class GRAND_API light_sensor
      : virtual public gr::sync_block,
        virtual public gr::grand::sensor_base
    {
     public:
      typedef std::shared_ptr<light_sensor> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of grand::light_sensor.
       *
       * To avoid accidental use of raw pointers, grand::light_sensor's
       * constructor is in a private implementation
       * class. grand::light_sensor::make is the public interface for
       * creating new instances.
       */
      static sptr make();
    };

  } // namespace grand
} // namespace gr

#endif /* INCLUDED_GRAND_LIGHT_SENSOR_H */
