/*
 *  mp3_enc_installer.ino - MP3 encoder dsp installer
 *  Copyright 2018 Sony Semiconductor Solutions Corporation
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *  The DSP installer is used to load code for the Audio DSP into SPI-Flash.
 *  This needs to be done ahead of using the Audio DSP functions in any sketch.
 *  A range of Audio DSP functions are available. This skecth loads MP3 encode and decode.
 *
 *  Run the sketch and you should see
 *  Installing DSPs...
 *  Install: /mnt/spif/BIN/MP3ENC  Done.
 *  Finished.
 *
 *  The loading process only needs to be done once as the DSP code is retained when up upload a new sketch.
 *
 *  To check what DSP files are loaded is a board you have already programmed you can use Nuttx Shell to 
 *  list the files installed in the SPI-Flash. Check the directory /mnt/spif/BIN/
 *
 *  You can use dsp_inataller with a range of encoders and decoders as they become available.
 *
 *  This example code is in the public domain.
 */

#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

// Include each file generated by bin2c
#include "MP3ENC.h"

#define _FILEELEM(elem) { \
  .name = #elem, \
  .addr = elem##_start, \
  .size = &elem##_size, \
}

struct fileinfo_s {
  const char *name;
  const unsigned char *addr;
  const size_t *size;
};

struct fileinfo_s dsplist[] =
{
  // Add each file here
  _FILEELEM(MP3ENC),
};

void setup()
{
  unsigned int i;
  int ret;
  FILE *fp;
  char filepath[64];

  printf("Installing MP3ENC DSP...\n");

  mkdir(CONFIG_AUDIOUTILS_DSP_MOUNTPT, 0777);

  for (i = 0; i < sizeof(dsplist) / sizeof(dsplist[0]); i++)
    {
      snprintf(filepath, sizeof(filepath), "%s/%s",
               CONFIG_AUDIOUTILS_DSP_MOUNTPT, dsplist[i].name);

      printf("Install: %s ", filepath);

      unlink(filepath);

      fp = fopen(filepath, "wb");

      ret = fwrite(dsplist[i].addr, *dsplist[i].size, 1, fp);

      printf(" %s.\n", (ret) ? "Done" : "Fail");

      fclose(fp);
    }

  printf("Finished.\n");
}

void loop()
{
  // nothing happens after setup finishes.
}
