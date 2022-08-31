/* -*- c++ -*- */
/*
 * Copyright 2022 gr-grand author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <gnuradio/io_signature.h>
#include "opensl_sink_impl.h"
#include "buf_manager.h"
#include <boost/format.hpp>
#include <volk/volk.h>

namespace gr
{
  namespace grand
  {

    using input_type = float;
    opensl_sink::sptr
    opensl_sink::make(int sampling_rate)
    {
      return gnuradio::get_initial_sptr(new opensl_sink_impl(sampling_rate));
    }

    /*
     * The private constructor
     */
    opensl_sink_impl::opensl_sink_impl(int sampling_rate)
        : gr::sync_block("opensl_sink",
                         gr::io_signature::make(1, 1, sizeof(float)),
                         gr::io_signature::make(0, 0, 0))
    {
      set_sample_rate(sampling_rate);
      d_size = 8192;
      signal = true;

      setup_interface();

      set_output_multiple(d_size);
    }

    opensl_sink_impl::~opensl_sink_impl()
    {

      for (int i = 0; i < PLAYBUF_CNT; i++)
      {
        volk_free(d_buffer[i]);
      }
      
    }

    SLresult opensl_sink_impl::startPlayer(void)
    {
      SLuint32 state;
      SLresult result = (*d_bq_player_play)->GetPlayState(d_bq_player_play, &state);
      if (result != SL_RESULT_SUCCESS)
      {
        return SL_BOOLEAN_FALSE;
      }
      if (state == SL_PLAYSTATE_PLAYING)
      {
        return SL_BOOLEAN_TRUE;
      }

      result = (*d_bq_player_play)->SetPlayState(d_bq_player_play, SL_PLAYSTATE_STOPPED);
      SLASSERT(result);

      result = (*d_bq_player_play)->SetPlayState(d_bq_player_play, SL_PLAYSTATE_PLAYING);
      SLASSERT(result);
      return SL_BOOLEAN_TRUE;
    }
    void opensl_sink_impl::stopPlayer(void)
    {
      SLuint32 state;

      SLresult result = (*d_bq_player_play)->GetPlayState(d_bq_player_play, &state);
      SLASSERT(result);

      if (state == SL_PLAYSTATE_STOPPED)
        return;

      gr::thread::scoped_lock lock(mutex_lock);

      result = (*d_bq_player_play)->SetPlayState(d_bq_player_play, SL_PLAYSTATE_STOPPED);
      SLASSERT(result);
      (*d_bq_player_buffer_queue)->Clear(d_bq_player_buffer_queue);
    }

    bool opensl_sink_impl::start()
    {
      startPlayer();
      bufIdx = 0;

      for (int i = 0; i < PLAYBUF_CNT; i++)
      {
        d_buffer[i] = (short *)volk_malloc(d_size * sizeof(short), volk_get_alignment());
        if (!d_buffer[i])
        {
          std::string e = boost::str(boost::format("Unable to allocate audio buffer of %1% bytes") % (d_size * sizeof(short)));
          GR_ERROR("grand::audio_sink", e);
          throw std::runtime_error("grand::audio_sink");
        }
      }

      return true;
    }

    bool opensl_sink_impl::stop()
    {
      stopPlayer();
      return true;
    }
    void
    opensl_sink_impl::set_sample_rate(int samp_rate)
    {
      switch (samp_rate)
      {
      case 8000:
        d_sample_rate = SL_SAMPLINGRATE_8;
        break;
      case 11025:
        d_sample_rate = SL_SAMPLINGRATE_11_025;
        break;
      case 16000:
        d_sample_rate = SL_SAMPLINGRATE_16;
        break;
      case 22050:
        d_sample_rate = SL_SAMPLINGRATE_22_05;
        break;
      case 24000:
        d_sample_rate = SL_SAMPLINGRATE_24;
        break;
      case 32000:
        d_sample_rate = SL_SAMPLINGRATE_32;
        break;
      case 44100:
        d_sample_rate = SL_SAMPLINGRATE_44_1;
        break;
      case 48000:
        d_sample_rate = SL_SAMPLINGRATE_48;
        break;
      case 64000:
        d_sample_rate = SL_SAMPLINGRATE_64;
        break;
      case 88200:
        d_sample_rate = SL_SAMPLINGRATE_88_2;
        break;
      case 96000:
        d_sample_rate = SL_SAMPLINGRATE_96;
        break;
      case 192000:
        d_sample_rate = SL_SAMPLINGRATE_192;
        break;
      default:
        std::string e = boost::str(boost::format("Invalid sample rate: %1%") % samp_rate);
        GR_ERROR("grand::audio_source", e);
        throw std::runtime_error("grand::audio_source");
      }
    }

    void
    opensl_sink_impl::setup_interface()
    {
      SLresult result;
      uint32_t channels = 1;
      SLuint32 speakers;
      if (channels > 1)
        speakers = SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT;
      else
        speakers = SL_SPEAKER_FRONT_CENTER;

      // Open audio engine
      result = slCreateEngine(&d_engine, 0, NULL, 0, NULL, NULL);
      if (result != SL_RESULT_SUCCESS)
      {
        GR_ERROR("grand::audio_sink", "Unable to open OpenSLES audio engine");
        throw std::runtime_error("grand::audio_sink");
      }
      (void)result;

      // Realize audio engine
      result = (*d_engine)->Realize(d_engine, SL_BOOLEAN_FALSE);
      if (result != SL_RESULT_SUCCESS)
      {
        GR_ERROR("grand::audio_sink", "Unable to realize engine");
        throw std::runtime_error("grand::audio_sink");
      }
      (void)result;

      // Get audio engine interface
      result = (*d_engine)->GetInterface(d_engine, SL_IID_ENGINE, &d_engine_eng);
      if (result != SL_RESULT_SUCCESS)
      {
        GR_ERROR("grand::audio_sink", "Unable to open OpenSLES engine interface");
        throw std::runtime_error("grand::audio_sink");
      }
      (void)result;

      // Create output mixer object
      const SLInterfaceID ids[] = {};
      const SLboolean req[] = {};
      result = (*d_engine_eng)->CreateOutputMix(d_engine_eng, &d_output_mix_obj, 0, ids, req);
      if (result != SL_RESULT_SUCCESS)
      {
        GR_ERROR("grand::audio_sink", "Unable to create OpenSLES output mix");
        throw std::runtime_error("grand::audio_sink");
      }
      (void)result;

      // Realize output mixer
      result = (*d_output_mix_obj)->Realize(d_output_mix_obj, SL_BOOLEAN_FALSE);
      if (result != SL_RESULT_SUCCESS)
      {
        GR_ERROR("grand::audio_sink", "Unable to realize OpenSLES output mix");
        throw std::runtime_error("grand::audio_sink");
      }
      (void)result;

      // Audio source and sink configurations
      SLDataLocator_AndroidSimpleBufferQueue loc_bufq = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2};
      SLDataFormat_PCM format_pcm = {SL_DATAFORMAT_PCM, channels, d_sample_rate,
                                     SL_PCMSAMPLEFORMAT_FIXED_16, SL_PCMSAMPLEFORMAT_FIXED_16,
                                     speakers, SL_BYTEORDER_LITTLEENDIAN};
      SLDataSource audioSrc = {&loc_bufq, &format_pcm};

      SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX,
                                            d_output_mix_obj};
      SLDataSink audioSnk = {&loc_outmix, NULL};

      // Create audio player (set the CAPTURE_AUDIO_OUTPUT permission)
      const SLInterfaceID ids1[] = {SL_IID_ANDROIDSIMPLEBUFFERQUEUE, SL_IID_VOLUME};
      const SLboolean req1[] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};
      result = (*d_engine_eng)->CreateAudioPlayer(d_engine_eng, &d_bq_player_obj, &audioSrc, &audioSnk, 2, ids1, req1);
      if (result != SL_RESULT_SUCCESS)
      {
        GR_ERROR("grand::audio_sink", "Unable to create OpenSLES audio player");
        throw std::runtime_error("grand::audio_sink");
      }
      (void)result;

      // Realize audio player
      result = (*d_bq_player_obj)->Realize(d_bq_player_obj, SL_BOOLEAN_FALSE);
      if (result != SL_RESULT_SUCCESS)
      {
        GR_ERROR("grand::audio_sink", "Unable to realize OpenSLES audio player");
        throw std::runtime_error("grand::audio_sink");
      }
      (void)result;

      // Get interface to audio player
      result = (*d_bq_player_obj)->GetInterface(d_bq_player_obj, SL_IID_PLAY, &(d_bq_player_play));
      if (result != SL_RESULT_SUCCESS)
      {
        GR_ERROR("grand::audio_sink", "Unable to get OpenSLES audio player interface");
        throw std::runtime_error("grand::audio_sink");
      }
      (void)result;

      // Get interface to the buffer queue
      result = (*d_bq_player_obj)->GetInterface(d_bq_player_obj, SL_IID_ANDROIDSIMPLEBUFFERQUEUE, &d_bq_player_buffer_queue);
      if (result != SL_RESULT_SUCCESS)
      {
        GR_ERROR("grand::audio_sink", "Unable to get OpenSLES audio player buffer queue");
        throw std::runtime_error("grand::audio_sink");
      }
      (void)result;

      // Set callback function, called when done writing output
      result = (*d_bq_player_buffer_queue)->RegisterCallback(d_bq_player_buffer_queue, queue_callback, this);
      if (result != SL_RESULT_SUCCESS)
      {
        GR_ERROR("grand::audio_sink", "Unable to register OpenSLES buffer queue callback");
        throw std::runtime_error("grand::audio_sink");
      }
      (void)result;

      // Set player state to play
      result = (*d_bq_player_play)->SetPlayState(d_bq_player_play, SL_PLAYSTATE_STOPPED);
      if (result != SL_RESULT_SUCCESS)
      {
        GR_ERROR("grand::audio_sink", "Unable to set OpenSLES audio player state to playing");
        throw std::runtime_error("grand::audio_sink");
      }
      (void)result;
    }

    void
    queue_callback(SLAndroidSimpleBufferQueueItf bq, void *context)
    {

    }

    int
    opensl_sink_impl::work(int noutput_items,
                           gr_vector_const_void_star &input_items,
                           gr_vector_void_star &output_items)
    {
      const float *in = (const float *)input_items[0];

      float scale_factor = 16384.0f;
      gr::thread::scoped_lock lock(mutex_lock);
      
      volk_32f_s32f_convert_16i(d_buffer[bufIdx], in, scale_factor, d_size);

      // use PLAYBUF_CNT buffers circularly
      (*d_bq_player_buffer_queue)->Enqueue(d_bq_player_buffer_queue, d_buffer[bufIdx], d_size * sizeof(short)); 
      bufIdx++;
      bufIdx = bufIdx % PLAYBUF_CNT;

      // Tell runtime system how many output items we produced.
      return d_size;
    }

  } /* namespace grand */
} /* namespace gr */
