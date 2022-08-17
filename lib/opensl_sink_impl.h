/* -*- c++ -*- */
/*
 * Copyright 2022 gr-grand author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_GRAND_OPENSL_SINK_IMPL_H
#define INCLUDED_GRAND_OPENSL_SINK_IMPL_H

#include <gnuradio/grand/opensl_sink.h>
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <volk/volk.h>

namespace gr {
  namespace grand {

    void queue_callback(SLAndroidSimpleBufferQueueItf bq, void *context);

    class opensl_sink_impl : public opensl_sink
    {
     private:
      SLuint32 d_sample_rate;
      bool d_once;

      SLObjectItf d_engine;
      SLEngineItf d_engine_eng;
      SLObjectItf d_output_mix_obj;
      SLObjectItf d_bq_player_obj;
      SLPlayItf   d_bq_player_play;
      SLAndroidSimpleBufferQueueItf d_bq_player_buffer_queue;

     public:
      int d_size;
      short *d_buffer;
      int d_index;

      opensl_sink_impl(int sampling_rate);
      ~opensl_sink_impl();

      gr::thread::mutex mutex_lock;
      gr::thread::condition_variable condition;
      bool signal;

      void set_sample_rate(int samp_rate);
      void setup_interface();

      int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
    };

  } // namespace grand
} // namespace gr

#endif /* INCLUDED_GRAND_OPENSL_SINK_IMPL_H */
