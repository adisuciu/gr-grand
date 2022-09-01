/* -*- c++ -*- */
/*
 * Copyright 2022 gr-grand author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_GRAND_OPENSL_SINK_H
#define INCLUDED_GRAND_OPENSL_SINK_H

#include <gnuradio/grand/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace grand {

    /*!
     * \brief <+description of block+>
     * \ingroup grand
     *
     */
    class GRAND_API opensl_sink : virtual public gr::sync_block
    {
     public:
      typedef std::shared_ptr<opensl_sink> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of grand::opensl_sink.
       *
       * To avoid accidental use of raw pointers, grand::opensl_sink's
       * constructor is in a private implementation
       * class. grand::opensl_sink::make is the public interface for
       * creating new instances.
       */
      static sptr make(int sampling_rate);
    };

  } // namespace grand
} // namespace gr

#endif /* INCLUDED_GRAND_OPENSL_SINK_H */
