/*
  MediaPlayer.cpp - SPI implement file for the Sparduino SDK
  Copyright (C) 2018 Sony Semiconductor Solutions Corp.
  Copyright (c) 2017 Sony Corporation  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

//***************************************************************************
// Included Files
//***************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <arch/board/board.h>

#include "MediaPlayer.h"

#include "memutil/msgq_id.h"
#include "memutil/mem_layout.h"
#include "memutil/memory_layout.h"

void  input_device_callback(uint32_t size)
{
    /* do nothing */
}

/****************************************************************************
 * Public API on MediaPlayer Class
 ****************************************************************************/

err_t MediaPlayer::begin(void)
{
  m_player0_simple_fifo_buf =
    (uint32_t*)(0xfffffffc & ((uint32_t)(malloc(MEDIAPLAYER_BUF_SIZE + 3)) + 3));
   
  m_player1_simple_fifo_buf =
    (uint32_t*)(0xfffffffc & ((uint32_t)(malloc(MEDIAPLAYER_BUF_SIZE + 3)) + 3));

  return MEDIAPLAYER_ECODE_OK;
}

/*--------------------------------------------------------------------------*/
err_t MediaPlayer::create(PlayerId id)
{
  AsCreatePlayerParam_t player_create_param;

  player_create_param.msgq_id.player = (id == Player0) ? MSGQ_AUD_PLY : MSGQ_AUD_SUB_PLY;
  player_create_param.msgq_id.mng    = MSGQ_AUD_MGR;
  player_create_param.msgq_id.mixer  = MSGQ_AUD_OUTPUT_MIX;
  player_create_param.msgq_id.dsp    = MSGQ_AUD_DSP;
  player_create_param.pool_id.es     = (id == Player0) ? DEC_ES_MAIN_BUF_POOL : DEC_ES_SUB_BUF_POOL;
  player_create_param.pool_id.pcm    = (id == Player0) ? REND_PCM_BUF_POOL : REND_PCM_SUB_BUF_POOL;
  player_create_param.pool_id.dsp    = DEC_APU_CMD_POOL;

  bool result;

  if (id == Player0)
    {
      result = AS_CreatePlayer(AS_PLAYER_ID_0, &player_create_param);
    }
  else
    {
      result = AS_CreatePlayer(AS_PLAYER_ID_1, &player_create_param);
    }

  if (!result)
    {
      print_err("Error: AS_CratePlayer() failure. system memory insufficient!\n");
      return MEDIAPLAYER_ECODE_COMMAND_ERROR;
    }

  return MEDIAPLAYER_ECODE_OK;
}

/*--------------------------------------------------------------------------*/
err_t MediaPlayer::activate(PlayerId id, uint8_t output_device, MediaPlayerCallback mpcb)
{
  CMN_SimpleFifoHandle *handle =
    (id == Player0) ?
      &m_player0_simple_fifo_handle : &m_player1_simple_fifo_handle;

  void *p_buffer =
    (id == Player0) ?
      m_player0_simple_fifo_buf : m_player1_simple_fifo_buf;


  if (CMN_SimpleFifoInitialize(handle,
                               p_buffer,
                               MEDIAPLAYER_BUF_SIZE,
                               NULL) != 0)
    {
      print_err("Fail to initialize simple FIFO.\n");
      return MEDIAPLAYER_ECODE_SIMPLEFIFO_ERROR;
    }

  CMN_SimpleFifoClear(handle);

  AsPlayerInputDeviceHdlrForRAM *p_input_dev_handler =
    (id == Player0) ?
      &m_player0_input_device_handler : &m_player1_input_device_handler;
  
  p_input_dev_handler->simple_fifo_handler = (void*)(handle);
  p_input_dev_handler->callback_function   = input_device_callback;

  AsActivatePlayer player_act;

  player_act.param.input_device  = AS_SETPLAYER_INPUTDEVICE_RAM;
  player_act.param.ram_handler   = p_input_dev_handler;
  player_act.param.output_device = output_device/*AS_SETPLAYER_OUTPUTDEVICE_SPHP*/;
  player_act.cb                  = mpcb;

  if (id == Player0)
    {
      AS_ActivatePlayer(AS_PLAYER_ID_0, player_act);
    }
  else
    {
      AS_ActivatePlayer(AS_PLAYER_ID_1, player_act);
    }

  return MEDIAPLAYER_ECODE_OK;
}

/*--------------------------------------------------------------------------*/
err_t MediaPlayer::init(PlayerId id,
                                   uint8_t codec_type,
                                   uint32_t sampling_rate,
                                   uint8_t channel_number)
{
  AsInitPlayerParam player_init;

  player_init.codec_type     = codec_type/*AS_CODECTYPE_MP3*/;
  player_init.bit_length     = AS_BITLENGTH_16;
  player_init.channel_number = channel_number/*AS_CHANNEL_STEREO*/;
  player_init.sampling_rate  = sampling_rate/*AS_SAMPLINGRATE_48000*/;

  if (id == Player0)
    {
      AS_InitPlayer(AS_PLAYER_ID_0, player_init);
    }
  else
    {
      AS_InitPlayer(AS_PLAYER_ID_1, player_init);
    }

  return MEDIAPLAYER_ECODE_OK;
}

/*--------------------------------------------------------------------------*/
err_t MediaPlayer::start(PlayerId id, DecodeDoneCallback dccb)
{
  board_external_amp_mute_control(false);

  AsPlayPlayerParam player_play;

  player_play.pcm_path = AsPcmDataReply;
  player_play.pcm_dest.callback = dccb;

  if (id == Player0)
    {
      AS_PlayPlayer(AS_PLAYER_ID_0, player_play);
    }
  else
    {
      AS_PlayPlayer(AS_PLAYER_ID_1, player_play);
    }

  return MEDIAPLAYER_ECODE_OK;
}

/*--------------------------------------------------------------------------*/
err_t MediaPlayer::stop(PlayerId id)
{
  AsStopPlayerParam player_stop;

  player_stop.stop_mode = AS_STOPPLAYER_NORMAL;

  if (id == Player0)
    {
      AS_StopPlayer(AS_PLAYER_ID_0, player_stop);
    }
  else
    {
      AS_StopPlayer(AS_PLAYER_ID_1, player_stop);
    }

  return MEDIAPLAYER_ECODE_OK;
}

/*--------------------------------------------------------------------------*/
err_t MediaPlayer::reqNextProcess(PlayerId id, AsRequestNextType type)
{
  AsRequestNextParam next;

  next.type = type;

  if (id == Player0)
    {
      AS_RequestNextPlayerProcess(AS_PLAYER_ID_0, next);
    }
  else
    {
      AS_RequestNextPlayerProcess(AS_PLAYER_ID_1, next);
    }

  return MEDIAPLAYER_ECODE_OK;
}

/*--------------------------------------------------------------------------*/
err_t MediaPlayer::deactivate(PlayerId id)
{
  AsDeactivatePlayer player_deact;

  if (id == Player0)
    {
      AS_DeactivatePlayer(AS_PLAYER_ID_0, player_deact);
    }
  else
    {
      AS_DeactivatePlayer(AS_PLAYER_ID_1, player_deact);
    }

  return MEDIAPLAYER_ECODE_OK;
}


#define WRITE_FRAME_NUM 5 
/*--------------------------------------------------------------------------*/
err_t MediaPlayer::writeFrames(PlayerId id, File& myFile)
{
  int ret = MEDIAPLAYER_ECODE_OK;
  char *buf = (id == Player0) ? m_es_player0_buf : m_es_player1_buf; 

  CMN_SimpleFifoHandle *handle =
    (id == Player0) ?
      &m_player0_simple_fifo_handle : &m_player1_simple_fifo_handle;

  for (int i = 0; i < WRITE_FRAME_NUM; i++)
    {
      ret = write_fifo(myFile, buf, handle);
      if (ret != MEDIAPLAYER_ECODE_OK) break;
    }

  return ret;
}

/*--------------------------------------------------------------------------*/
err_t MediaPlayer::write_fifo(File& myFile, char *p_es_buf, CMN_SimpleFifoHandle *handle)
{

  int vacant_size = CMN_SimpleFifoGetVacantSize(handle);
  if (vacant_size < MEDIAPLAYER_BUF_FRAME_SIZE)
    {
      return MEDIAPLAYER_ECODE_OK;
    }

  int ret = -1;

  if (myFile.available())
    {
      ret = myFile.read(p_es_buf, MEDIAPLAYER_BUF_FRAME_SIZE);
    }
  else
    {
      ret = 0;
    }

  if (ret < 0)
    {
      print_err("Fail to read file. errno:%d\n", errno);
      return MEDIAPLAYER_ECODE_FILEACCESS_ERROR;
    }

  if(ret == 0)
    {
      myFile.close();
      return MEDIAPLAYER_ECODE_FILEEND;
    }

  if (CMN_SimpleFifoOffer(handle, (const void*)(p_es_buf), ret) == 0)
    {
      print_err("Simple FIFO is full!\n");
      return MEDIAPLAYER_ECODE_SIMPLEFIFO_ERROR;
    }

  return MEDIAPLAYER_ECODE_OK;
}

