/*
 * Gatix
 * Copyright (C) 2014  Daniel Gatis Carrazzoni
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "std/logging.h"
#include "std/types.h"
#include "std/utils.h"
#include "std/string.h"
#include "std/vsprintf.h"

static device_t *vga_driver;
static device_t *serial_driver;

void logging_init(device_t *vga, device_t *serial)
{
  vga_driver = vga;
  serial_driver = serial;
}

int panic(const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  kprintf(fmt, args);
  va_end(args);
  for(;;);
}

int kdebugf(const char *fmt, ...)
{
  char buf[1024];
  va_list args;
  int n = 0;

  va_start(args, fmt);
  n = vsprintf(buf, fmt, args);
  va_end(args);

  serial_driver->write((uint8_t *)buf, strlen(buf));

  return n;
}

int kprintf(const char *fmt, ...)
{
  char buf[1024];
  va_list args;
  int n = 0;

  va_start(args, fmt);
  n = vsprintf(buf, fmt, args);
  va_end(args);

  vga_driver->write((uint8_t *)buf, strlen(buf));

  return n;
}
