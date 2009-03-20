/* Nintendulator - Win32 NES emulator written in C
 * Copyright (C) 2002-2009 QMT Productions
 *
 * $URL$
 * $Id$
 */

#include "stdafx.h"
#include "Nintendulator.h"
#include "resource.h"
#include "MapperInterface.h"
#include "NES.h"
#include "CPU.h"
#include "PPU.h"
#include "Genie.h"

struct tGenie Genie;

unsigned char GameGeniePRG[0x1000] = {
0x78,0xD8,0xA9,0x00,0x8D,0x00,0x20,0xA2,0xFF,0x9A,0xA9,0x00,0x8D,0xF0,0xFF,0x20,0x1E,0xF0,0x8D,0xF1,0xFF,0x20,0x1E,0xF0,0x8D,0xF0,0xFF,0x4C,0x29,0xF0,0xA2,0x60,
0xA0,0x08,0xCA,0xD0,0xFD,0x88,0xD0,0xFA,0x60,0xA2,0x0A,0xAD,0x02,0x20,0x10,0xFB,0xCA,0xD0,0xF8,0xA2,0xFF,0x9A,0xA9,0x07,0x85,0x01,0xA9,0x00,0x85,0x00,0xA8,0x91,
0x00,0xC8,0xD0,0xFB,0xC6,0x01,0x10,0xF7,0xA9,0x06,0x85,0x01,0x8D,0x01,0x20,0xA9,0x80,0x85,0x00,0x8D,0x00,0x20,0xCE,0x2B,0x00,0x4C,0x1F,0xF4,0xA9,0x01,0x8D,0x16,
0x40,0xA9,0x00,0x8D,0x16,0x40,0xA0,0x08,0xAD,0x16,0x40,0x6A,0x26,0x07,0x88,0xD0,0xF7,0xA0,0x08,0xAD,0x17,0x40,0x6A,0x26,0x08,0x88,0xD0,0xF7,0x60,0x48,0x8A,0x48,
0x98,0x48,0xA5,0x0C,0xD0,0x17,0x20,0x69,0xF1,0x20,0x74,0xF1,0xAD,0x45,0x00,0x8D,0x05,0x20,0xAD,0x46,0x00,0x8D,0x05,0x20,0xA5,0x00,0x8D,0x00,0x20,0xA9,0x01,0x8D,
0x49,0x00,0x68,0xA8,0x68,0xAA,0x68,0x40,0x86,0x17,0x84,0x18,0x20,0x38,0xF2,0xA0,0x00,0xB1,0x39,0x85,0x0D,0xC8,0xB1,0x39,0x85,0x0E,0xAD,0x39,0x00,0x18,0x69,0x02,
0x8D,0x39,0x00,0xAD,0x3A,0x00,0x69,0x00,0x8D,0x3A,0x00,0xA9,0x00,0x85,0x16,0xA9,0x00,0x85,0x15,0x20,0xE7,0xF0,0xE6,0x15,0xA5,0x15,0xC5,0x0D,0xD0,0xF5,0xE6,0x16,
0xA5,0x16,0xC5,0x0E,0xD0,0xE9,0x60,0xA5,0x16,0xA6,0x0D,0x20,0x5A,0xF1,0x18,0x65,0x15,0x8D,0x40,0x00,0x4A,0xA8,0xB1,0x39,0x85,0x04,0xAD,0x40,0x00,0x29,0x01,0xF0,
0x07,0xA5,0x04,0x29,0x0F,0x4C,0x0E,0xF1,0xA5,0x04,0x4A,0x4A,0x4A,0x4A,0x85,0x19,0xA5,0x17,0x18,0x65,0x15,0x38,0xE9,0x04,0x85,0x1E,0xA5,0x18,0x18,0x65,0x16,0x85,
0x1F,0xA5,0x1F,0x0A,0x0A,0x0A,0x85,0x20,0xA9,0x00,0x06,0x20,0x2A,0x06,0x20,0x2A,0x18,0x65,0x05,0x85,0x21,0xA5,0x20,0x18,0x65,0x1E,0x85,0x20,0xA5,0x21,0x69,0x00,
0x85,0x21,0xA5,0x21,0x8D,0x41,0x04,0xA5,0x20,0x8D,0x42,0x04,0xA5,0x19,0x8D,0x43,0x04,0xA9,0x01,0x8D,0x40,0x04,0x20,0xB9,0xF1,0x60,0x85,0x27,0xA9,0x00,0xE0,0x00,
0xF0,0x06,0x18,0x65,0x27,0xCA,0xD0,0xFB,0x60,0xA9,0x00,0x8D,0x03,0x20,0xA9,0x02,0x8D,0x14,0x40,0x60,0xA9,0x64,0x85,0x2C,0xA4,0x29,0xC4,0x2A,0xF0,0x38,0xB9,0x00,
0x03,0xAA,0x18,0x69,0x05,0x85,0x28,0xA5,0x2C,0x38,0xE5,0x28,0x90,0x28,0x85,0x2C,0xA5,0x2B,0x18,0x79,0x00,0x03,0x69,0x03,0x85,0x2B,0xC8,0xB9,0x00,0x03,0x8D,0x06,
0x20,0xC8,0xB9,0x00,0x03,0x8D,0x06,0x20,0xC8,0xB9,0x00,0x03,0x8D,0x07,0x20,0xC8,0xCA,0xD0,0xF6,0x4C,0x7A,0xF1,0x84,0x29,0x60,0xAD,0x40,0x04,0x18,0x69,0x03,0x85,
0x04,0xA5,0x2B,0xC5,0x04,0xB0,0x0A,0xA5,0x0C,0xF0,0xEE,0x20,0x74,0xF1,0x4C,0xB9,0xF1,0x38,0xE5,0x04,0x85,0x2B,0xA2,0x00,0xA4,0x2A,0xBD,0x40,0x04,0x99,0x00,0x03,
0xE8,0xC8,0xE4,0x04,0xD0,0xF4,0x84,0x2A,0x60,0x85,0x31,0x20,0x38,0xF2,0xA0,0x00,0xB1,0x39,0x85,0x34,0xAA,0xC8,0xB1,0x39,0x85,0x35,0x20,0x5A,0xF1,0x85,0x37,0x18,
0x69,0x02,0x20,0xB0,0xF5,0x85,0x38,0xAA,0xBD,0x63,0x05,0xAA,0xA5,0x34,0x9D,0x95,0x05,0xA5,0x35,0x9D,0x96,0x05,0xE8,0xE8,0xA0,0xFF,0xC8,0xB9,0x63,0x04,0xD0,0xFA,
0x98,0x9D,0x95,0x05,0xE8,0xC6,0x37,0xD0,0xF1,0xA6,0x38,0xA5,0x31,0x20,0xE0,0xF2,0xA6,0x38,0x20,0x5B,0xF2,0xA5,0x38,0x60,0x85,0x04,0xA9,0xBE,0x85,0x39,0xA9,0xFE,
0x85,0x3A,0xA5,0x04,0x10,0x02,0xE6,0x3A,0x0A,0xA8,0xB1,0x39,0x48,0xC8,0xB1,0x39,0x18,0x69,0xBE,0x85,0x39,0x68,0x69,0xFE,0x85,0x3A,0x60,0xBD,0x63,0x05,0xAA,0xBD,
0x95,0x05,0x85,0x34,0xBD,0x96,0x05,0x85,0x35,0xE8,0xE8,0xA5,0x2F,0x85,0x3C,0xA5,0x30,0x85,0x3D,0xA5,0x3D,0xD0,0x54,0xA5,0x34,0x85,0x3B,0xA5,0x2D,0x85,0x3E,0xA5,
0x2E,0x85,0x3F,0xA5,0x3F,0xD0,0x17,0xBD,0x95,0x05,0xA8,0xB9,0x23,0x05,0xF0,0x0E,0xA5,0x3E,0x99,0xA3,0x04,0xA5,0x3C,0x99,0xE3,0x04,0xE8,0x4C,0xA8,0xF2,0xBD,0x95,
0x05,0xA8,0xA9,0xFF,0x99,0xE3,0x04,0xE8,0xA5,0x3E,0x18,0x69,0x08,0x85,0x3E,0xA5,0x3F,0x69,0x00,0x85,0x3F,0xC6,0x3B,0xD0,0xCA,0xA5,0x3C,0x18,0x69,0x08,0x85,0x3C,
0xA5,0x3D,0x69,0x00,0x85,0x3D,0xC6,0x35,0xD0,0xA9,0x60,0xA5,0x34,0x85,0x3B,0xBD,0x95,0x05,0xA8,0xA9,0xFF,0x99,0xE3,0x04,0xE8,0xC6,0x3B,0xD0,0xF2,0x4C,0xB9,0xF2,
0x85,0x31,0xBD,0x63,0x05,0x18,0x69,0x02,0x48,0xA5,0x31,0x20,0x38,0xF2,0xA0,0x00,0xB1,0x39,0x85,0x34,0xC8,0xB1,0x39,0x85,0x35,0xA9,0x00,0x09,0x1C,0xA6,0x33,0x85,
0x36,0xA9,0x02,0xA0,0x01,0x84,0x41,0x85,0x40,0xA9,0x00,0x85,0x42,0x68,0xAA,0xA5,0x34,0x85,0x3B,0xA5,0x40,0x4A,0x18,0x69,0x01,0xA8,0xB1,0x39,0x85,0x04,0xA5,0x40,
0x29,0x01,0xF0,0x07,0xA5,0x04,0x29,0x0F,0x4C,0x31,0xF3,0xA5,0x04,0x4A,0x4A,0x4A,0x4A,0x48,0xBD,0x95,0x05,0xA8,0x68,0x99,0x23,0x05,0xA5,0x36,0x99,0x63,0x04,0xE8,
0xA5,0x40,0x18,0x65,0x41,0x85,0x40,0xC6,0x3B,0xD0,0xC8,0xA5,0x40,0x18,0x65,0x42,0x85,0x40,0xC6,0x35,0xD0,0xB9,0x60,0xA5,0x43,0x49,0x01,0x85,0x43,0xD0,0x17,0xA0,
0x08,0xA2,0x3D,0xBD,0x63,0x04,0xF0,0x07,0x20,0x91,0xF3,0xCA,0x10,0xF5,0x60,0x20,0xAB,0xF3,0xCA,0x10,0xEE,0x60,0xA0,0x08,0xA2,0x00,0xBD,0x63,0x04,0xF0,0x09,0x20,
0x91,0xF3,0xE8,0xE0,0x3E,0xD0,0xF3,0x60,0x20,0xAB,0xF3,0xE8,0xE0,0x3E,0xD0,0xEA,0x60,0x99,0x02,0x02,0xBD,0xE3,0x04,0x99,0x00,0x02,0xBD,0x23,0x05,0x99,0x01,0x02,
0xBD,0xA3,0x04,0x99,0x03,0x02,0xC8,0xC8,0xC8,0xC8,0x60,0xA9,0xFF,0x99,0x00,0x02,0xC8,0xC8,0xC8,0xC8,0x60,0xA5,0x1F,0x29,0x01,0x0A,0x85,0x04,0xA5,0x1E,0x29,0x01,
0x05,0x04,0xA8,0xA5,0x1F,0x0A,0x0A,0x29,0xF8,0x85,0x04,0xA5,0x1E,0x4A,0x18,0x65,0x04,0xAA,0x09,0xC0,0x8D,0x42,0x04,0xA9,0x23,0x8D,0x41,0x04,0xA9,0x01,0x8D,0x40,
0x04,0xB9,0xFB,0xF3,0x25,0x1A,0x85,0x04,0xB9,0xFB,0xF3,0x49,0xFF,0x3D,0x00,0x04,0x05,0x04,0x9D,0x00,0x04,0x8D,0x43,0x04,0x4C,0xB9,0xF1,0x03,0x0C,0x30,0xC0,0x0D,
0x00,0x00,0x2C,0x00,0x00,0x00,0x26,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x0D,0x00,0x00,0x13,0x00,0x00,0x00,0x26,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x28,0xA9,
0x01,0x85,0x0C,0xA9,0x20,0x85,0x05,0x8D,0x06,0x20,0xA9,0x00,0x8D,0x06,0x20,0xA2,0x04,0xA8,0x8D,0x07,0x20,0x88,0xD0,0xFA,0xCA,0xD0,0xF7,0x20,0xD3,0xF5,0xA2,0x00,
0xA9,0x00,0x9D,0x63,0x05,0xE8,0xE0,0x32,0xD0,0xF8,0x20,0x69,0xF1,0xA9,0x0E,0x8D,0x50,0x00,0x85,0x2D,0xA9,0x3C,0x8D,0x51,0x00,0x85,0x2F,0xA9,0x80,0x8D,0x55,0x00,
0xA9,0x96,0x8D,0x56,0x00,0xA9,0x14,0x20,0xE9,0xF1,0x8D,0x4F,0x00,0xA9,0x02,0x20,0xE9,0xF1,0x8D,0x54,0x00,0xA9,0xFF,0x85,0x2F,0xA9,0x05,0x20,0xE9,0xF1,0x8D,0x7B,
0x00,0xA2,0x13,0xBD,0x43,0xF8,0x9D,0x63,0x04,0xCA,0x10,0xF7,0xA9,0x09,0x8D,0x15,0x40,0xA9,0x20,0x8D,0x40,0x04,0xA9,0x3F,0x8D,0x41,0x04,0xA9,0x00,0x8D,0x42,0x04,
0xA0,0x00,0xB9,0xFF,0xF3,0x99,0x43,0x04,0xC8,0xC0,0x20,0xD0,0xF5,0x20,0xB9,0xF1,0xA9,0x00,0x85,0x0C,0x20,0xC9,0xF4,0xA5,0x01,0x09,0x18,0x85,0x01,0x8D,0x01,0x20,
0x20,0xD4,0xF4,0x20,0xC9,0xF4,0x4C,0xC0,0xF4,0xA9,0x00,0x8D,0x49,0x00,0xAD,0x49,0x00,0xF0,0xFB,0x60,0x20,0x5C,0xF0,0x20,0x7B,0xF6,0x20,0x92,0xF9,0x20,0xEC,0xFA,
0x20,0x82,0xFC,0x20,0xD5,0xFC,0x20,0xDA,0xF8,0x20,0xF6,0xF8,0x20,0x89,0xFD,0xAD,0x50,0x00,0x85,0x2D,0xAD,0x51,0x00,0x85,0x2F,0xAE,0x4F,0x00,0x20,0x5B,0xF2,0x20,
0x57,0xF3,0x60,0xAD,0x5A,0x00,0xD0,0x5D,0xA5,0x07,0x29,0x08,0xF0,0x2A,0xA9,0x08,0x20,0xAC,0xF7,0xF0,0x23,0xA9,0x3F,0x8D,0x59,0x00,0xA9,0xF7,0x8D,0x5A,0x00,0xA9,
0x08,0x20,0x8F,0xF7,0xF0,0x05,0xA9,0x20,0x4C,0x2D,0xF5,0xA9,0x00,0x8D,0x5B,0x00,0xA9,0x08,0x8D,0x5E,0x00,0x4C,0x65,0xF5,0xA5,0x07,0x29,0x04,0xF0,0x27,0xA9,0x04,
0x20,0xAC,0xF7,0xF0,0x20,0xA9,0xFF,0x8D,0x59,0x00,0xA9,0xF6,0x8D,0x5A,0x00,0xA9,0x04,0x20,0x8F,0xF7,0xF0,0x05,0xA9,0x20,0x4C,0x5D,0xF5,0xA9,0x00,0x8D,0x5B,0x00,
0xA9,0x04,0x8D,0x5E,0x00,0xAD,0x58,0x00,0xD0,0x45,0xA5,0x07,0x29,0x02,0xF0,0x1E,0xA9,0x02,0x20,0xAC,0xF7,0xF0,0x17,0xA9,0x3F,0x8D,0x57,0x00,0xA9,0xF7,0x8D,0x58,
0x00,0xA9,0x00,0x8D,0x5C,0x00,0xA9,0x02,0x8D,0x5D,0x00,0x4C,0xAF,0xF5,0xA5,0x07,0x29,0x01,0xF0,0x1B,0xA9,0x01,0x20,0xAC,0xF7,0xF0,0x14,0xA9,0xFF,0x8D,0x57,0x00,
0xA9,0xF6,0x8D,0x58,0x00,0xA9,0x00,0x8D,0x5C,0x00,0xA9,0x01,0x8D,0x5D,0x00,0x60,0x85,0x04,0xA2,0xFF,0xE8,0xBD,0x64,0x05,0xDD,0x63,0x05,0xD0,0xF7,0x86,0x4B,0x85,
0x4A,0xE8,0xA5,0x04,0x18,0x7D,0x63,0x05,0x9D,0x63,0x05,0xE8,0xE0,0x32,0xD0,0xF2,0xA5,0x4B,0x60,0xA9,0x00,0x85,0x45,0xA9,0x04,0x85,0x46,0xA9,0x01,0xA2,0x05,0xA0,
0x03,0x20,0xA8,0xF0,0xA9,0x03,0x85,0x4C,0xA9,0x04,0x85,0x4D,0xA9,0x08,0x85,0x4E,0xA5,0x4C,0xA6,0x4D,0xA4,0x4E,0x20,0xA8,0xF0,0xA5,0x4D,0x18,0x69,0x04,0x85,0x4D,
0xC9,0x24,0xD0,0x0B,0xA9,0x04,0x85,0x4D,0xA5,0x4E,0x18,0x69,0x04,0x85,0x4E,0xE6,0x4C,0xA5,0x4C,0xC9,0x13,0xD0,0xD9,0xA9,0x03,0x85,0x4C,0xA9,0x04,0x85,0x4D,0xA9,
0x12,0x85,0x4E,0xA9,0x13,0xA6,0x4D,0xA4,0x4E,0x20,0xA8,0xF0,0xA5,0x4D,0x18,0x69,0x04,0x85,0x4D,0xC9,0x24,0xD0,0x0B,0xA9,0x04,0x85,0x4D,0xA5,0x4E,0x18,0x69,0x04,
0x85,0x4E,0xE6,0x4C,0xA5,0x4C,0xC9,0x1B,0xD0,0xD9,0xA9,0x55,0xA2,0x04,0xA0,0x00,0x20,0xB8,0xFC,0xA9,0x00,0xA2,0x04,0xA0,0x04,0x20,0xB8,0xFC,0xA9,0xAA,0xA2,0x02,
0xA0,0x09,0x20,0xB8,0xFC,0xA9,0xFF,0xA2,0x04,0xA0,0x0B,0x20,0xB8,0xFC,0xA2,0x00,0xA0,0x00,0x20,0xEA,0xF7,0xA9,0x02,0x8D,0x82,0x00,0x60,0xA5,0x5F,0x49,0x01,0x85,
0x5F,0xD0,0x03,0x20,0x03,0xF5,0xA5,0x58,0xF0,0x32,0xA4,0x5C,0xB1,0x57,0xC9,0x80,0xD0,0x07,0xA9,0x00,0x85,0x58,0x4C,0xA0,0xF6,0xA2,0x50,0x20,0x7F,0xF7,0xF0,0x1C,
0x98,0x29,0x0F,0xC9,0x07,0xD0,0x12,0x20,0x17,0xF8,0xA5,0x07,0x25,0x5D,0xF0,0x09,0xA5,0x5D,0x20,0xAC,0xF7,0xF0,0x02,0xA0,0x0F,0xC8,0x84,0x5C,0xA5,0x5A,0xF0,0x3E,
0xA4,0x5B,0xB1,0x59,0xC9,0x80,0xD0,0x07,0xA9,0x00,0x85,0x5A,0x4C,0xD6,0xF6,0xA2,0x51,0x20,0x7F,0xF7,0xF0,0x28,0x98,0x29,0x0F,0xC9,0x07,0xD0,0x1E,0x20,0x17,0xF8,
0xA5,0x07,0x25,0x5E,0xF0,0x15,0xA5,0x5E,0x20,0xAC,0xF7,0xF0,0x0E,0xA5,0x5E,0x20,0x8F,0xF7,0xF0,0x05,0xA0,0x2F,0x4C,0xFB,0xF6,0xA0,0x0F,0xC8,0x84,0x5B,0x60,0x01,
0x01,0x02,0x02,0x03,0x03,0x04,0x04,0x03,0x03,0x02,0x02,0x02,0x01,0xFF,0x80,0x05,0x04,0x04,0x03,0x03,0x04,0x05,0x04,0x03,0x03,0x02,0x02,0x02,0x01,0xFF,0x80,0x02,
0x03,0x04,0x05,0x06,0x06,0x06,0x04,0x03,0x03,0x02,0x02,0x02,0x01,0xFF,0x80,0x05,0x06,0x07,0x08,0x07,0x06,0x05,0x04,0x03,0x03,0x02,0x02,0x02,0x01,0xFF,0x80,0xFF,
0xFF,0xFE,0xFE,0xFD,0xFD,0xFC,0xFC,0xFD,0xFD,0xFE,0xFE,0xFE,0xFF,0x01,0x80,0xFB,0xFC,0xFC,0xFD,0xFD,0xFC,0xFB,0xFC,0xFD,0xFD,0xFE,0xFE,0xFE,0xFF,0x01,0x80,0xFE,
0xFD,0xFC,0xFB,0xFA,0xFA,0xFA,0xFC,0xFD,0xFD,0xFE,0xFE,0xFE,0xFF,0x01,0x80,0xFB,0xFA,0xF9,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFD,0xFE,0xFE,0xFE,0xFF,0x01,0x80,0x48,
0x0A,0x68,0x6A,0xC6,0x5F,0xF0,0x01,0x18,0x75,0x00,0x95,0x00,0xE6,0x5F,0x60,0xC9,0x04,0xD0,0x09,0xA5,0x53,0xC9,0x02,0xD0,0x10,0xA9,0x01,0x60,0xC9,0x08,0xD0,0x09,
0xA5,0x53,0xC9,0x01,0xD0,0x03,0xA9,0x01,0x60,0xA9,0x00,0x60,0xC9,0x01,0xD0,0x0B,0xA5,0x52,0xC9,0x07,0xF0,0x31,0xE6,0x52,0x4C,0xE4,0xF7,0xC9,0x02,0xD0,0x09,0xA5,
0x52,0xF0,0x24,0xC6,0x52,0x4C,0xE4,0xF7,0xC9,0x04,0xD0,0x0B,0xA5,0x53,0xC9,0x04,0xF0,0x15,0xE6,0x53,0x4C,0xE4,0xF7,0xC9,0x08,0xD0,0x09,0xA5,0x53,0xF0,0x08,0xC6,
0x53,0x4C,0xE4,0xF7,0xA9,0x01,0x60,0xA9,0x00,0x60,0xA9,0xAA,0x85,0x1A,0x8A,0x0A,0x85,0x1E,0x98,0x0A,0x18,0x69,0x04,0xC9,0x08,0x90,0x03,0x18,0x69,0x01,0x85,0x1F,
0x20,0xB5,0xF3,0xE6,0x1E,0x20,0xB5,0xF3,0xE6,0x1F,0x20,0xB5,0xF3,0xC6,0x1E,0x4C,0xB5,0xF3,0xA9,0x00,0x4C,0xEC,0xF7,0x98,0x48,0xA6,0x60,0xA4,0x61,0x20,0x12,0xF8,
0xA5,0x53,0xC9,0x02,0xB0,0x14,0x85,0x61,0x85,0x63,0xA5,0x52,0x85,0x60,0x85,0x62,0xA6,0x60,0xA4,0x61,0x20,0xEA,0xF7,0x68,0xA8,0x60,0x85,0x63,0xA5,0x52,0x85,0x62,
0x68,0xA8,0x60,0x19,0x19,0x19,0x19,0x1A,0x19,0x19,0x19,0x19,0x1A,0x19,0x19,0x19,0x19,0x1A,0x19,0x19,0x19,0x19,0x1A,0xAD,0x77,0x04,0xC9,0x1A,0xD0,0x05,0xA9,0x18,
0x4C,0x65,0xF8,0xA9,0x1A,0xAE,0x6D,0x00,0xE0,0x07,0xB0,0x02,0x09,0x20,0x8D,0x77,0x04,0x8D,0x78,0x04,0x8D,0x79,0x04,0x8D,0x7A,0x04,0x60,0xA5,0x63,0x0A,0x0A,0x0A,
0x18,0x65,0x62,0x69,0x03,0x48,0xA5,0x65,0x0A,0x0A,0x18,0x69,0x12,0xA8,0xA5,0x64,0x0A,0x0A,0x18,0x69,0x04,0xAA,0x68,0x48,0x20,0xA8,0xF0,0x20,0x0A,0xFC,0x68,0x20,
0xD9,0xFB,0x4C,0xA5,0xF8,0xE6,0x64,0xA5,0x64,0xC9,0x06,0xD0,0x15,0xA5,0x65,0x0A,0x0A,0x0A,0x18,0x69,0x02,0xAA,0xBD,0x6B,0x06,0x38,0xE9,0x03,0x29,0x01,0xF0,0x06,
0xA5,0x64,0xC9,0x08,0xD0,0x11,0xA5,0x65,0xC9,0x02,0xF0,0x09,0xA9,0x00,0x85,0x64,0xE6,0x65,0x4C,0xD7,0xF8,0xC6,0x64,0x4C,0x0B,0xFD,0xA5,0x07,0x29,0x80,0xC5,0x66,
0xD0,0x01,0x60,0x85,0x66,0xC9,0x80,0xF0,0x01,0x60,0xA5,0x63,0xC9,0x02,0xB0,0x03,0x4C,0x7B,0xF8,0x4C,0x78,0xF9,0xA5,0x07,0x29,0x40,0xC5,0x67,0xD0,0x01,0x60,0x85,
0x67,0xC9,0x40,0xF0,0x01,0x60,0x4C,0x09,0xF9,0xA5,0x64,0xF0,0x25,0xA5,0x65,0xC9,0x02,0xD0,0x1A,0xAD,0x7D,0x06,0x38,0xE9,0x03,0x29,0x01,0xD0,0x04,0xA9,0x05,0xD0,
0x02,0xA9,0x07,0xC5,0x64,0xD0,0x06,0xAA,0xBD,0x7B,0x06,0xD0,0x0E,0x20,0xF9,0xFB,0xD0,0x26,0xA5,0x64,0x05,0x65,0xF0,0x20,0x20,0x5B,0xF9,0xA5,0x65,0x0A,0x0A,0x18,
0x69,0x12,0xA8,0xA5,0x64,0x0A,0x0A,0x18,0x69,0x04,0xAA,0x20,0xB5,0xFB,0xA9,0x13,0x20,0xA8,0xF0,0xA9,0x00,0x4C,0xD9,0xFB,0x4C,0x5B,0xF9,0xC6,0x64,0xA5,0x64,0xC9,
0xFF,0xD0,0x0F,0xA5,0x65,0xF0,0x09,0xA9,0x07,0x85,0x64,0xC6,0x65,0x4C,0x72,0xF9,0xE6,0x64,0x20,0xE2,0xFB,0x4C,0x0B,0xFD,0xA5,0x63,0x38,0xE9,0x02,0x85,0x65,0xA5,
0x62,0x85,0x64,0x20,0xE2,0xFB,0x8A,0x48,0x98,0x48,0x20,0x0B,0xFD,0x68,0xA8,0x68,0xAA,0x60,0xA5,0x65,0x0A,0x0A,0x0A,0x0A,0x0A,0x18,0x69,0x98,0x85,0x69,0xA5,0x64,
0x0A,0x0A,0x0A,0x0A,0x0A,0x18,0x69,0x0A,0x85,0x68,0xA5,0x55,0x8D,0x6E,0x00,0xA5,0x68,0x8D,0x6F,0x00,0x20,0x2F,0xFA,0x18,0x69,0x80,0x85,0x6A,0xA5,0x6B,0x20,0x56,
0xFA,0x85,0x6B,0xA5,0x56,0x8D,0x6E,0x00,0xA5,0x69,0x8D,0x6F,0x00,0x20,0x2F,0xFA,0x18,0x69,0x80,0x85,0x6A,0xA5,0x6C,0x20,0x56,0xFA,0x85,0x6C,0xA5,0x55,0x18,0x65,
0x6B,0x85,0x55,0xA5,0x56,0x18,0x65,0x6C,0x85,0x56,0xA6,0x6D,0xA5,0x55,0x18,0x7D,0x0D,0xFA,0x85,0x2D,0xA5,0x56,0x18,0x7D,0x1E,0xFA,0x85,0x2F,0xE8,0xE0,0x10,0xD0,
0x02,0xA2,0x00,0x86,0x6D,0xA6,0x54,0x20,0x5B,0xF2,0x4C,0x57,0xF8,0x00,0x04,0x07,0x09,0x0A,0x09,0x07,0x04,0x00,0xFC,0xF9,0xF7,0xF6,0xF7,0xF9,0xFC,0x00,0xF6,0xF7,
0xF9,0xFC,0x00,0x04,0x07,0x09,0x0A,0x09,0x07,0x04,0x00,0xFC,0xF9,0xF7,0xF6,0xA5,0x6E,0xC5,0x6F,0x90,0x12,0xD0,0x03,0xA9,0x00,0x60,0xA5,0x6F,0x38,0xE5,0x6E,0xA2,
0x03,0x38,0x6A,0xCA,0xD0,0xFB,0x60,0xA5,0x6F,0x38,0xE5,0x6E,0xA2,0x03,0x4A,0xCA,0xD0,0xFC,0x18,0x69,0x01,0x60,0x49,0x80,0xC5,0x6A,0x90,0x07,0xF0,0x07,0xE9,0x01,
0x4C,0x65,0xFA,0x69,0x01,0x49,0x80,0x60,0xA5,0x72,0xF0,0x0E,0xA9,0x00,0x85,0x72,0xA2,0x30,0x20,0xA8,0xFA,0xA9,0x01,0x85,0x74,0x60,0xA9,0x01,0x85,0x72,0xA2,0x20,
0x20,0xA8,0xFA,0xA9,0x01,0x85,0x73,0x60,0x00,0x06,0x08,0x06,0x00,0xFA,0xF8,0xFA,0x00,0x03,0x04,0x03,0x00,0xFD,0xFC,0xFD,0xF8,0xFA,0x00,0x06,0x08,0x06,0x00,0xFA,
0xFC,0xFD,0x00,0x03,0x04,0x03,0x00,0xFD,0xA0,0x00,0xB9,0x88,0xFA,0x18,0x65,0x70,0x9D,0xA3,0x04,0xB9,0x98,0xFA,0x18,0x65,0x71,0x9D,0xE3,0x04,0xB9,0x88,0xFA,0x9D,
0x0B,0x06,0xB9,0x98,0xFA,0x9D,0x2B,0x06,0xA9,0x01,0x9D,0x23,0x05,0xA9,0x1A,0x9D,0x63,0x04,0xE8,0xC8,0xC0,0x10,0xD0,0xD2,0xA9,0x0E,0x8D,0x0E,0x40,0xA9,0x04,0x8D,
0x0F,0x40,0xA9,0x25,0x8D,0x0C,0x40,0xA9,0x18,0x85,0x75,0x60,0xA5,0x75,0xF0,0x09,0xC6,0x75,0xD0,0x05,0xA9,0x30,0x8D,0x0C,0x40,0xA5,0x73,0xF0,0x0D,0xA2,0x20,0xE6,
0x73,0xA5,0x73,0xC9,0x18,0xF0,0x15,0x20,0x2D,0xFB,0xA5,0x74,0xF0,0x0D,0xA2,0x30,0xE6,0x74,0xA5,0x74,0xC9,0x18,0xF0,0x0E,0x20,0x2D,0xFB,0x60,0xA9,0x00,0x85,0x73,
0x20,0xA4,0xFB,0x4C,0x0A,0xFB,0xA9,0x00,0x85,0x74,0x4C,0xA4,0xFB,0x29,0x07,0x85,0x04,0xA0,0x10,0xBD,0xE3,0x04,0xC9,0xFF,0xF0,0x59,0xBD,0x63,0x04,0x49,0x02,0x9D,
0x63,0x04,0xBD,0x0B,0x06,0x10,0x09,0x18,0x7D,0xA3,0x04,0xB0,0x16,0x4C,0x56,0xFB,0x18,0x7D,0xA3,0x04,0x90,0x0D,0xA9,0xFF,0x9D,0xE3,0x04,0xA9,0x00,0x9D,0x63,0x04,
0x4C,0x93,0xFB,0x9D,0xA3,0x04,0xBD,0x2B,0x06,0x10,0x09,0x18,0x7D,0xE3,0x04,0xB0,0x09,0x4C,0x56,0xFB,0x18,0x7D,0xE3,0x04,0xB0,0xDC,0x9D,0xE3,0x04,0xA5,0x04,0xD0,
0x12,0xBD,0x0B,0x06,0x20,0x98,0xFB,0x9D,0x0B,0x06,0xBD,0x2B,0x06,0x20,0x98,0xFB,0x9D,0x2B,0x06,0xE8,0x88,0xD0,0x9C,0x60,0xF0,0x09,0x10,0x04,0x18,0x69,0x01,0x60,
0x38,0xE9,0x01,0x60,0xA0,0x10,0xA9,0x00,0x9D,0x63,0x04,0xA9,0xFF,0x9D,0xE3,0x04,0xE8,0x88,0xD0,0xF2,0x60,0x98,0x48,0x0A,0x0A,0x0A,0x18,0x69,0x0A,0x85,0x71,0x8A,
0x48,0x38,0xE9,0x04,0x0A,0x0A,0x0A,0x18,0x69,0x0D,0x85,0x70,0x20,0xF9,0xFB,0xF0,0x03,0x20,0x68,0xFA,0x68,0xAA,0x68,0xA8,0x60,0x48,0x20,0x00,0xFC,0x68,0x9D,0x6B,
0x06,0x60,0x20,0x00,0xFC,0xA5,0x64,0xF0,0x0F,0xBD,0x6B,0x06,0xD0,0x0A,0xCA,0xBD,0x6B,0x06,0xD0,0x04,0xC6,0x64,0xD0,0xF6,0x60,0x20,0x00,0xFC,0xBD,0x6B,0x06,0x60,
0xA5,0x65,0x0A,0x0A,0x0A,0x18,0x65,0x64,0xAA,0x60,0xA5,0x62,0x0A,0x0A,0x0A,0x0A,0x0A,0x85,0x76,0x85,0x2D,0xA5,0x63,0x0A,0x0A,0x0A,0x48,0x0A,0x0A,0x18,0x69,0x40,
0x85,0x77,0x85,0x2F,0x68,0x18,0x65,0x62,0x8D,0x7D,0x00,0x69,0x03,0xA6,0x7B,0x20,0xE0,0xF2,0xA6,0x7B,0x20,0x5B,0xF2,0xA5,0x65,0x0A,0x0A,0x0A,0x0A,0x0A,0x18,0x69,
0x90,0x38,0xE5,0x77,0x4A,0x4A,0x4A,0x4A,0x85,0x79,0xA5,0x64,0x38,0xE5,0x62,0x0A,0x85,0x78,0xA9,0x10,0x85,0x7A,0xAD,0x7D,0x00,0x0A,0x0A,0x0A,0x0A,0x85,0x04,0xA9,
0x00,0x06,0x04,0x2A,0x06,0x04,0x2A,0x18,0x69,0x02,0x8D,0x03,0x40,0xA5,0x04,0x8D,0x02,0x40,0xA9,0x24,0x8D,0x00,0x40,0xA9,0xF9,0x8D,0x01,0x40,0xA9,0x14,0x8D,0x7C,
0x00,0x60,0xA5,0x7C,0xF0,0x09,0xC6,0x7C,0xD0,0x05,0xA9,0x30,0x8D,0x00,0x40,0xA5,0x7A,0xD0,0x01,0x60,0xC6,0x7A,0xD0,0x09,0xA6,0x7B,0xA9,0xFF,0x85,0x2F,0x4C,0x5B,
0xF2,0xA5,0x76,0x18,0x65,0x78,0x85,0x76,0x85,0x2D,0xA5,0x77,0x18,0x65,0x79,0x85,0x77,0x85,0x2F,0xA6,0x7B,0x4C,0x5B,0xF2,0x85,0x1A,0x84,0x1F,0x86,0x7E,0xA9,0x00,
0x85,0x1E,0x20,0xB5,0xF3,0xA5,0x1E,0x18,0x69,0x01,0xC9,0x10,0xD0,0xF2,0xE6,0x1F,0xC6,0x7E,0xD0,0xEA,0x60,0xA6,0x7F,0xA4,0x80,0xC8,0xC0,0x05,0xD0,0x03,0xA0,0x00,
0xE8,0x84,0x80,0xE0,0x08,0xD0,0x02,0xA2,0x00,0x86,0x7F,0xBD,0x03,0xFD,0x8D,0x43,0x04,0xA9,0x01,0x8D,0x40,0x04,0xA9,0x3F,0x8D,0x41,0x04,0xA9,0x07,0x8D,0x42,0x04,
0x4C,0xB9,0xF1,0x21,0x2C,0x2B,0x28,0x27,0x25,0x24,0x2C,0xA6,0x81,0xA4,0x82,0x84,0x83,0xA9,0xAA,0x20,0xEC,0xF7,0xA5,0x65,0x18,0x69,0x02,0x85,0x82,0xA5,0x64,0x85,
0x81,0x20,0x3D,0xFD,0xA6,0x81,0xA4,0x82,0xA9,0x55,0x4C,0xEC,0xF7,0xAF,0xAF,0xAF,0xAF,0xAF,0xAF,0xAF,0xAF,0xFA,0xFA,0xFA,0xFA,0xFA,0xFA,0xFA,0xFA,0xA5,0x83,0xC5,
0x82,0xF0,0x45,0xA9,0x23,0x8D,0x41,0x04,0xA9,0xE0,0x8D,0x42,0x04,0xA0,0x1F,0xA9,0xFF,0x99,0x43,0x04,0x99,0x20,0x04,0x88,0x10,0xF5,0xA9,0x20,0x8D,0x40,0x04,0x20,
0xB9,0xF1,0xA5,0x82,0x38,0xE9,0x02,0x0A,0x0A,0x0A,0x18,0x69,0xE0,0x8D,0x42,0x04,0xA9,0x23,0x8D,0x41,0x04,0xA0,0x0F,0xB9,0x2D,0xFD,0x99,0x43,0x04,0x88,0x10,0xF7,
0xA9,0x10,0x8D,0x40,0x04,0x20,0xB9,0xF1,0x60,0xA5,0x07,0x29,0x30,0xD0,0x05,0xA9,0x01,0x85,0x84,0x60,0xA5,0x84,0xF0,0xFB,0xA9,0x00,0x8D,0x00,0x20,0x8D,0x01,0x20,
0xA9,0x6B,0x85,0x80,0xA9,0x06,0x85,0x81,0xA9,0x90,0x85,0x82,0xA9,0x00,0x85,0x83,0xA2,0x0F,0xA9,0xFF,0x95,0x90,0xCA,0x10,0xFB,0xA9,0x03,0x85,0x88,0xA9,0xEF,0x85,
0x86,0xA9,0x02,0x85,0x87,0xA9,0x71,0x85,0x89,0xA0,0x00,0x84,0x84,0xB1,0x80,0xF0,0x17,0x38,0xE9,0x03,0x29,0x0F,0x4A,0x05,0x84,0x91,0x80,0xA9,0x00,0x2A,0x0A,0x0A,
0x0A,0x85,0x84,0xC8,0xC0,0x08,0xD0,0xE5,0x84,0x85,0xC0,0x08,0xF0,0x07,0xC0,0x06,0xF0,0x0A,0x4C,0x70,0xFE,0xA0,0x03,0xB1,0x80,0x4C,0x00,0xFE,0xA0,0x03,0xB1,0x80,
0xA0,0x00,0xB1,0x80,0x29,0x07,0x05,0x84,0x91,0x80,0xA2,0x00,0x86,0x84,0xBC,0xB6,0xFE,0xB1,0x80,0x0A,0x0A,0x0A,0x0A,0xE8,0xBC,0xB6,0xFE,0x11,0x80,0xA4,0x84,0x99,
0x8A,0x00,0xE6,0x84,0xE8,0xE0,0x08,0xD0,0xE5,0xA5,0x8A,0x29,0x7F,0x85,0x8A,0xA5,0x8A,0xA6,0x8B,0xC5,0x90,0xD0,0x04,0xE4,0x91,0xF0,0x35,0xC5,0x94,0xD0,0x04,0xE4,
0x95,0xF0,0x2D,0xC5,0x98,0xD0,0x04,0xE4,0x99,0xF0,0x25,0xA0,0x01,0xB9,0x8A,0x00,0x91,0x82,0x88,0x10,0xF8,0xA0,0x03,0xB9,0x89,0x00,0x91,0x82,0x88,0xB9,0x8B,0x00,
0x91,0x82,0xA5,0x89,0x25,0x86,0xA6,0x85,0xE0,0x08,0xD0,0x02,0x05,0x87,0x85,0x89,0x38,0x26,0x86,0x06,0x87,0xA5,0x80,0x18,0x69,0x08,0x85,0x80,0x90,0x02,0xE6,0x81,
0xA5,0x82,0x18,0x69,0x04,0x85,0x82,0x90,0x02,0xE6,0x83,0xC6,0x88,0xF0,0x03,0x4C,0xC9,0xFD,0xA2,0x18,0xBD,0x9F,0xFE,0x95,0x10,0xCA,0x10,0xF8,0x4C,0x10,0x00,0xA2,
0x0B,0xB5,0x90,0x9D,0x01,0x80,0xCA,0x10,0xF8,0xA5,0x89,0x8D,0x00,0x80,0xA9,0x00,0x8D,0x00,0x80,0x6C,0xFC,0xFF,0x03,0x05,0x02,0x04,0x01,0x00,0x07,0x06,0x00,0x2A,
0x00,0x30,0x00,0x6E,0x00,0x72,0x00,0x7C,0x00,0x86,0x00,0x90,0x00,0x9A,0x00,0xA4,0x00,0xAE,0x00,0xB8,0x00,0xC2,0x00,0xCC,0x00,0xD6,0x00,0xE0,0x00,0xEA,0x00,0xF4,
0x00,0xFE,0x01,0x08,0x01,0x12,0x01,0x1C,0x08,0x02,0x01,0x23,0x45,0x67,0x1E,0x04,0x2C,0xC0,0x00,0x00,0x00,0x00,0x00,0x02,0xCC,0x00,0x00,0x00,0x08,0x00,0x00,0x52,
0x32,0xCC,0x5D,0x96,0x2C,0xE4,0x05,0x23,0x2C,0xE4,0xDC,0x6A,0x2C,0xE4,0x60,0x2A,0x00,0x55,0x5A,0xA0,0x40,0x06,0x02,0xA0,0x40,0x50,0xAA,0xA0,0x40,0x0C,0x40,0xC0,
0x44,0x48,0x0C,0xC4,0x00,0xC4,0x0C,0xC4,0x40,0x88,0x0C,0xC4,0x02,0x02,0xB1,0x80,0x04,0x04,0x0A,0x00,0x05,0x50,0xAC,0xE0,0xC4,0xC4,0x04,0x04,0x8D,0xE0,0x07,0x10,
0x05,0x20,0x8C,0xC0,0x04,0x04,0x8D,0x60,0x07,0x90,0x05,0x00,0x8C,0x00,0x04,0x04,0x09,0x60,0xA0,0x05,0x81,0x24,0x08,0x40,0x04,0x04,0xAC,0xE0,0x02,0x40,0x24,0x20,
0x8C,0xC0,0x04,0x04,0xE4,0xE4,0x06,0x40,0x24,0x60,0xC4,0xC4,0x04,0x04,0x8D,0x00,0x05,0x00,0x05,0x20,0x8C,0xC0,0x04,0x04,0xE4,0xE4,0xA0,0xA0,0xA0,0xA0,0x0C,0x40,
0x04,0x04,0x09,0xC5,0xA0,0x31,0x81,0x05,0x08,0xC0,0x04,0x04,0x8D,0xA4,0x07,0x40,0x05,0x60,0x8C,0x84,0x04,0x04,0x0E,0x40,0x0A,0x00,0x0A,0x00,0x0C,0x40,0x04,0x04,
0x2C,0x70,0x87,0x10,0x20,0xE0,0x0C,0x40,0x04,0x04,0xAE,0xE0,0x0A,0x00,0x0A,0x00,0x0C,0x40,0x04,0x04,0xE4,0xE4,0x81,0x90,0x06,0x40,0x08,0x00,0x04,0x04,0xE4,0xE4,
0x06,0x40,0x0A,0x00,0x0C,0x40,0x04,0x04,0xE0,0xE4,0xA6,0xA0,0xA0,0xE0,0xC4,0x80,0x04,0x04,0x00,0x00,0x23,0x31,0x00,0x00,0x00,0x00,0x05,0x04,0x00,0x70,0x03,0x3B,
0x71,0x0E,0xFF,0x50,0x0C,0xC4,0x03,0x3B,0x71,0x0E,0xFF,0x50,0x0C,0xC4,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xAA,0x7D,0xF0,0x00,0xF0,0xFF,0xFF};
unsigned char GameGenieCHR[0x400] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xF0,0xF0,0xF0,0x00,0x00,0x00,0x00,0xF0,0xF0,0xF0,0xF0,
0x00,0x00,0x00,0x00,0x0F,0x0F,0x0F,0x0F,0x00,0x00,0x00,0x00,0x0F,0x0F,0x0F,0x0F,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,
0xF0,0xF0,0xF0,0xF0,0x00,0x00,0x00,0x00,0xF0,0xF0,0xF0,0xF0,0x00,0x00,0x00,0x00,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,
0xF0,0xF0,0xF0,0xF0,0x0F,0x0F,0x0F,0x0F,0xF0,0xF0,0xF0,0xF0,0x0F,0x0F,0x0F,0x0F,0xF0,0xF0,0xF0,0xF0,0xFF,0xFF,0xFF,0xFF,0xF0,0xF0,0xF0,0xF0,0xFF,0xFF,0xFF,0xFF,
0x0F,0x0F,0x0F,0x0F,0x00,0x00,0x00,0x00,0x0F,0x0F,0x0F,0x0F,0x00,0x00,0x00,0x00,0x0F,0x0F,0x0F,0x0F,0xF0,0xF0,0xF0,0xF0,0x0F,0x0F,0x0F,0x0F,0xF0,0xF0,0xF0,0xF0,
0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0xFF,0xFF,0xFF,0xFF,0x0F,0x0F,0x0F,0x0F,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xF0,0xF0,0xF0,0xF0,0xFF,0xFF,0xFF,0xFF,0xF0,0xF0,0xF0,0xF0,
0xFF,0xFF,0xFF,0xFF,0x0F,0x0F,0x0F,0x0F,0xFF,0xFF,0xFF,0xFF,0x0F,0x0F,0x0F,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xF0,0xF0,0xF0,0x00,0x00,0x00,0x00,0xF0,0xF0,0xF0,0xF0,
0x00,0x00,0x00,0x00,0x0F,0x0F,0x0F,0x0F,0x00,0x00,0x00,0x00,0x0F,0x0F,0x0F,0x0F,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,
0xF0,0xF0,0xF0,0xF0,0x00,0x00,0x00,0x00,0xF0,0xF0,0xF0,0xF0,0x00,0x00,0x00,0x00,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,
0xF0,0xF0,0xF0,0xF0,0x0F,0x0F,0x0F,0x0F,0xF0,0xF0,0xF0,0xF0,0x0F,0x0F,0x0F,0x0F,0xF0,0xF0,0xF0,0xF0,0xFF,0xFF,0xFF,0xFF,0xF0,0xF0,0xF0,0xF0,0xFF,0xFF,0xFF,0xFF,
0x0F,0x0F,0x0F,0x0F,0x00,0x00,0x00,0x00,0x0F,0x0F,0x0F,0x0F,0x00,0x00,0x00,0x00,0x0F,0x0F,0x0F,0x0F,0xF0,0xF0,0xF0,0xF0,0x0F,0x0F,0x0F,0x0F,0xF0,0xF0,0xF0,0xF0,
0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0xFF,0xFF,0xFF,0xFF,0x0F,0x0F,0x0F,0x0F,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xF0,0xF0,0xF0,0xF0,0xFF,0xFF,0xFF,0xFF,0xF0,0xF0,0xF0,0xF0,
0xFF,0xFF,0xFF,0xFF,0x0F,0x0F,0x0F,0x0F,0xFF,0xFF,0xFF,0xFF,0x0F,0x0F,0x0F,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xF0,0xF0,0xF0,0x00,0x00,0x00,0x00,0xF0,0xF0,0xF0,0xF0,
0x00,0x00,0x00,0x00,0x0F,0x0F,0x0F,0x0F,0x00,0x00,0x00,0x00,0x0F,0x0F,0x0F,0x0F,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,
0xF0,0xF0,0xF0,0xF0,0x00,0x00,0x00,0x00,0xF0,0xF0,0xF0,0xF0,0x00,0x00,0x00,0x00,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,
0xF0,0xF0,0xF0,0xF0,0x0F,0x0F,0x0F,0x0F,0xF0,0xF0,0xF0,0xF0,0x0F,0x0F,0x0F,0x0F,0xF0,0xF0,0xF0,0xF0,0xFF,0xFF,0xFF,0xFF,0xF0,0xF0,0xF0,0xF0,0xFF,0xFF,0xFF,0xFF,
0x0F,0x0F,0x0F,0x0F,0x00,0x00,0x00,0x00,0x0F,0x0F,0x0F,0x0F,0x00,0x00,0x00,0x00,0x0F,0x0F,0x0F,0x0F,0xF0,0xF0,0xF0,0xF0,0x0F,0x0F,0x0F,0x0F,0xF0,0xF0,0xF0,0xF0,
0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0xFF,0xFF,0xFF,0xFF,0x0F,0x0F,0x0F,0x0F,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xF0,0xF0,0xF0,0xF0,0xFF,0xFF,0xFF,0xFF,0xF0,0xF0,0xF0,0xF0,
0xFF,0xFF,0xFF,0xFF,0x0F,0x0F,0x0F,0x0F,0xFF,0xFF,0xFF,0xFF,0x0F,0x0F,0x0F,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xF0,0xF0,0xF0,0x00,0x00,0x00,0x00,0xF0,0xF0,0xF0,0xF0,
0x00,0x00,0x00,0x00,0x0F,0x0F,0x0F,0x0F,0x00,0x00,0x00,0x00,0x0F,0x0F,0x0F,0x0F,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,
0xF0,0xF0,0xF0,0xF0,0x00,0x00,0x00,0x00,0xF0,0xF0,0xF0,0xF0,0x00,0x00,0x00,0x00,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,
0xF0,0xF0,0xF0,0xF0,0x0F,0x0F,0x0F,0x0F,0xF0,0xF0,0xF0,0xF0,0x0F,0x0F,0x0F,0x0F,0xF0,0xF0,0xF0,0xF0,0xFF,0xFF,0xFF,0xFF,0xF0,0xF0,0xF0,0xF0,0xFF,0xFF,0xFF,0xFF,
0x0F,0x0F,0x0F,0x0F,0x00,0x00,0x00,0x00,0x0F,0x0F,0x0F,0x0F,0x00,0x00,0x00,0x00,0x0F,0x0F,0x0F,0x0F,0xF0,0xF0,0xF0,0xF0,0x0F,0x0F,0x0F,0x0F,0xF0,0xF0,0xF0,0xF0,
0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0xFF,0xFF,0xFF,0xFF,0x0F,0x0F,0x0F,0x0F,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xF0,0xF0,0xF0,0xF0,0xFF,0xFF,0xFF,0xFF,0xF0,0xF0,0xF0,0xF0,
0xFF,0xFF,0xFF,0xFF,0x0F,0x0F,0x0F,0x0F,0xFF,0xFF,0xFF,0xFF,0x0F,0x0F,0x0F,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

int	MAPINT	GenieRead (int Bank, int Addr)
{
	int result = CPU::ReadPRG(Bank,Addr);
	if (NES.GameGenie)
	{
		if ((Genie.CodeStat & 0x10) && (Bank == Genie.Code1B) && (Addr == Genie.Code1A) && ((Genie.CodeStat & 0x02) || (result == Genie.Code1O)))
			return Genie.Code1V;
		if ((Genie.CodeStat & 0x20) && (Bank == Genie.Code2B) && (Addr == Genie.Code2A) && ((Genie.CodeStat & 0x04) || (result == Genie.Code2O)))
			return Genie.Code2V;
		if ((Genie.CodeStat & 0x40) && (Bank == Genie.Code3B) && (Addr == Genie.Code3A) && ((Genie.CodeStat & 0x08) || (result == Genie.Code3O)))
			return Genie.Code3V;
	}
	return result;
}
int	MAPINT	GenieRead1 (int Bank, int Addr)
{
	int result = CPU::ReadPRG(Bank,Addr);
	if ((NES.GameGenie) && ((Addr == Genie.Code1A) && ((Genie.CodeStat & 0x02) || (result == Genie.Code1O))))
		return Genie.Code1V;
	else	return result;
}
int	MAPINT	GenieRead2 (int Bank, int Addr)
{
	int result = CPU::ReadPRG(Bank,Addr);
	if ((NES.GameGenie) && ((Addr == Genie.Code2A) && ((Genie.CodeStat & 0x04) || (result == Genie.Code2O))))
		return Genie.Code2V;
	else	return result;
}
int	MAPINT	GenieRead3 (int Bank, int Addr)
{
	int result = CPU::ReadPRG(Bank,Addr);
	if ((NES.GameGenie) && ((Addr == Genie.Code3A) && ((Genie.CodeStat & 0x08) || (result == Genie.Code3O))))
		return Genie.Code3V;
	else	return result;
}


void	MAPINT	GenieWrite (int Bank, int Addr, int Val)
{
	int i;
	switch (Addr)
	{
	case 0:	if (Val & 1)
			Genie.CodeStat = (unsigned char)(0x80 | (Val ^ 0x7E));
		else
		{
			Genie.CodeStat &= 0x7F;

			for (i = 0x8; i < 0x10; i++)
			{	// reset PRG banks
				CPU::Readable[i] = FALSE;
				CPU::PRGPointer[i] = NULL;
			}
			for (i = 0; i < 0x10; i++)
			{	// and CHR banks
				PPU.Writable[i] = FALSE;
				PPU.CHRPointer[i] = PPU_OpenBus;
			}
			CPU::WriteHandler[0x8] = CPU::WritePRG;	// and the PRG write handler for $8000-$8FFF

			Genie_Init();	// map in the appropriate [optimized] read handlers
			MI = MI2;	// swap in the REAL mapper
			CPU::GetHandlers();	// grab a copy of CPUCycle
			PPU_GetHandlers();	// ...and PPUCycle
			if ((MI) && (MI->Reset))	// then hard-reset the mapper
				MI->Reset(RESET_HARD);
		}
		break;
	case 1:	Genie.Code1B = 8 | (Val >> 4);
		Genie.Code1A = (Genie.Code1A & 0xFF) | ((Val << 8) & 0xF00);
		break;
	case 2:	Genie.Code1A = (Genie.Code1A & 0xF00) | (Val);
		break;
	case 3:	Genie.Code1O = Val;
		break;
	case 4:	Genie.Code1V = Val;
		break;
	case 5:	Genie.Code2B = 8 | (Val >> 4);
		Genie.Code2A = (Genie.Code2A & 0xFF) | ((Val << 8) & 0xF00);
		break;
	case 6:	Genie.Code2A = (Genie.Code2A & 0xF00) | (Val);
		break;
	case 7:	Genie.Code2O = Val;
		break;
	case 8:	Genie.Code2V = Val;
		break;
	case 9:	Genie.Code3B = 8 | (Val >> 4);
		Genie.Code3A = (Genie.Code3A & 0xFF) | ((Val << 8) & 0xF00);
		break;
	case 10:Genie.Code3A = (Genie.Code3A & 0xF00) | (Val);
		break;
	case 11:Genie.Code3O = Val;
		break;
	case 12:Genie.Code3V = Val;
		break;
	}
}

void	Genie_Reset (void)
{
	int i;
	Genie.Code1B = Genie.Code2B = Genie.Code3B = 0;
	Genie.Code1A = Genie.Code2A = Genie.Code3A = 0;
	Genie.Code1O = Genie.Code2O = Genie.Code3O = 0;
	Genie.Code1V = Genie.Code2V = Genie.Code3V = 0;
	Genie.CodeStat = 0x80;
	for (i = 0x8; i < 0x10; i++)
	{
		CPU::Readable[i] = TRUE;
		CPU::PRGPointer[i] = GameGeniePRG;
	}
	CPU::WriteHandler[0x8] = GenieWrite;
	for (i = 0; i < 8; i++)
	{
		PPU.Writable[i] = FALSE;
		PPU.CHRPointer[i] = GameGenieCHR;
	}
	EI.Mirror_V();
	MI2 = MI;
	MI = NULL;
	PPU_GetHandlers();
	CPU::GetHandlers();
}

void	Genie_Init (void)
{
	int IsCode[8] = {0,0,0,0,0,0,0,0};
	if (Genie.CodeStat & 0x10)
		IsCode[Genie.Code1B - 8]++;
	if (Genie.CodeStat & 0x20)
		IsCode[Genie.Code2B - 8]++;
	if (Genie.CodeStat & 0x40)
		IsCode[Genie.Code3B - 8]++;
	if (Genie.CodeStat & 0x10)
	{
		if (IsCode[Genie.Code1B - 8] > 1)
			CPU::ReadHandler[Genie.Code1B] = GenieRead;
		else 
			CPU::ReadHandler[Genie.Code1B] = GenieRead1;
	}
	if (Genie.CodeStat & 0x20)
	{
		if (IsCode[Genie.Code2B - 8] > 1)
			CPU::ReadHandler[Genie.Code2B] = GenieRead;
		else 
			CPU::ReadHandler[Genie.Code2B] = GenieRead2;
	}
	if (Genie.CodeStat & 0x40)
	{
		if (IsCode[Genie.Code3B - 8] > 1)
			CPU::ReadHandler[Genie.Code3B] = GenieRead;
		else 
			CPU::ReadHandler[Genie.Code3B] = GenieRead3;
	}
}

int	Genie_Save (FILE *out)
{
	int clen = 0;
	unsigned char val;
	unsigned short addr;
		//Data
	val = (unsigned char)NES.GameGenie;				fwrite(&val,1,1,out);	clen++;
	val = Genie.CodeStat;						fwrite(&val,1,1,out);	clen++;

	addr = (unsigned short)((Genie.Code1B << 12) | Genie.Code1A);	fwrite(&addr,2,1,out);	clen += 2;
	val = (unsigned char)Genie.Code1O;				fwrite(&val,1,1,out);	clen++;
	val = (unsigned char)Genie.Code1V;				fwrite(&val,1,1,out);	clen++;

	addr = (unsigned short)((Genie.Code2B << 12) | Genie.Code2A);	fwrite(&addr,2,1,out);	clen += 2;
	val = (unsigned char)Genie.Code2O;				fwrite(&val,1,1,out);	clen++;
	val = (unsigned char)Genie.Code2V;				fwrite(&val,1,1,out);	clen++;

	addr = (unsigned short)((Genie.Code3B << 12) | Genie.Code3A);	fwrite(&addr,2,1,out);	clen += 2;
	val = (unsigned char)Genie.Code3O;				fwrite(&val,1,1,out);	clen++;
	val = (unsigned char)Genie.Code3V;				fwrite(&val,1,1,out);	clen++;

	return clen;
}

int	Genie_Load (FILE *in)
{
	int clen = 0;
	unsigned char val;
	unsigned short addr;
	fread(&val,1,1,in);	clen++;		NES.GameGenie = val;
	fread(&val,1,1,in);	clen++;		Genie.CodeStat = val;

	fread(&addr,2,1,in);	clen += 2;	Genie.Code1A = addr & 0xFFF; Genie.Code1B = addr >> 12;
	fread(&val,1,1,in);	clen++;		Genie.Code1O = val;
	fread(&val,1,1,in);	clen++;		Genie.Code1V = val;

	fread(&addr,2,1,in);	clen += 2;	Genie.Code2A = addr & 0xFFF; Genie.Code2B = addr >> 12;
	fread(&val,1,1,in);	clen++;		Genie.Code2O = val;
	fread(&val,1,1,in);	clen++;		Genie.Code2V = val;

	fread(&addr,2,1,in);	clen += 2;	Genie.Code3A = addr & 0xFFF; Genie.Code3B = addr >> 12;
	fread(&val,1,1,in);	clen++;		Genie.Code3O = val;
	fread(&val,1,1,in);	clen++;		Genie.Code3V = val;

	if (Genie.CodeStat & 0x10)
	{
		if (Genie.CodeStat & 0x02)
			EI.DbgOut(_T("Loaded Game Genie code 1: $%01X%03X -> $%02X"), Genie.Code1B, Genie.Code1A, Genie.Code1V);
		else	EI.DbgOut(_T("Loaded Game Genie code 1: $%01X%03X : $%02X -> $%02X"), Genie.Code1B, Genie.Code1A, Genie.Code1O, Genie.Code1V);
	}
	if (Genie.CodeStat & 0x20)
	{
		if (Genie.CodeStat & 0x04)
			EI.DbgOut(_T("Loaded Game Genie code 2: $%01X%03X -> $%02X"), Genie.Code2B, Genie.Code2A, Genie.Code2V);
		else	EI.DbgOut(_T("Loaded Game Genie code 2: $%01X%03X : $%02X -> $%02X"), Genie.Code2B, Genie.Code2A, Genie.Code2O, Genie.Code2V);
	}
	if (Genie.CodeStat & 0x40)
	{
		if (Genie.CodeStat & 0x08)
			EI.DbgOut(_T("Loaded Game Genie code 3: $%01X%03X -> $%02X"), Genie.Code3B, Genie.Code3A, Genie.Code3V);
		else	EI.DbgOut(_T("Loaded Game Genie code 3: $%01X%03X : $%02X -> $%02X"), Genie.Code3B, Genie.Code3A, Genie.Code3O, Genie.Code3V);
	}

	if (NES.GameGenie)
		CheckMenuItem(hMenu,ID_CPU_GAMEGENIE,MF_CHECKED);
	else	CheckMenuItem(hMenu,ID_CPU_GAMEGENIE,MF_UNCHECKED);

	Genie_Init();		// reset the I/O handlers
	if ((MI) && (MI->Reset))
		MI->Reset(RESET_SOFT);	// and then (soft) reset the mapper again; we'll load its state momentarily
	return clen;
}