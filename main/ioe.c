// Copyright (C) 2016-2019 Semtech (International) AG. All rights reserved.
//
// This file is subject to the terms and conditions defined in file 'LICENSE',
// which is part of this source code package.

#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "ioe.h"

// OLED --------------------------------
#define SSD1306_ADDR               0x3C

const unsigned char F6x8[][6] =
{
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00},  // sp
    {0x00, 0x00, 0x00, 0x2f, 0x00, 0x00},  // !
    {0x00, 0x00, 0x07, 0x00, 0x07, 0x00},  // "
    {0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14},  // #
    {0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12},  // $
    {0x00, 0x62, 0x64, 0x08, 0x13, 0x23},  // %
    {0x00, 0x36, 0x49, 0x55, 0x22, 0x50},  // &
    {0x00, 0x00, 0x05, 0x03, 0x00, 0x00},  // '
    {0x00, 0x00, 0x1c, 0x22, 0x41, 0x00},  // (
    {0x00, 0x00, 0x41, 0x22, 0x1c, 0x00},  // )
    {0x00, 0x14, 0x08, 0x3E, 0x08, 0x14},  // *
    {0x00, 0x08, 0x08, 0x3E, 0x08, 0x08},  // +
    {0x00, 0x00, 0x00, 0xA0, 0x60, 0x00},  // ,
    {0x00, 0x08, 0x08, 0x08, 0x08, 0x08},  // -
    {0x00, 0x00, 0x60, 0x60, 0x00, 0x00},  // .
    {0x00, 0x20, 0x10, 0x08, 0x04, 0x02},  // /
    {0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E},  // 0
    {0x00, 0x00, 0x42, 0x7F, 0x40, 0x00},  // 1
    {0x00, 0x42, 0x61, 0x51, 0x49, 0x46},  // 2
    {0x00, 0x21, 0x41, 0x45, 0x4B, 0x31},  // 3
    {0x00, 0x18, 0x14, 0x12, 0x7F, 0x10},  // 4
    {0x00, 0x27, 0x45, 0x45, 0x45, 0x39},  // 5
    {0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30},  // 6
    {0x00, 0x01, 0x71, 0x09, 0x05, 0x03},  // 7
    {0x00, 0x36, 0x49, 0x49, 0x49, 0x36},  // 8
    {0x00, 0x06, 0x49, 0x49, 0x29, 0x1E},  // 9
    {0x00, 0x00, 0x36, 0x36, 0x00, 0x00},  // :
    {0x00, 0x00, 0x56, 0x36, 0x00, 0x00},  // ;
    {0x00, 0x08, 0x14, 0x22, 0x41, 0x00},  // <
    {0x00, 0x14, 0x14, 0x14, 0x14, 0x14},  // =
    {0x00, 0x00, 0x41, 0x22, 0x14, 0x08},  // >
    {0x00, 0x02, 0x01, 0x51, 0x09, 0x06},  // ?
    {0x00, 0x32, 0x49, 0x59, 0x51, 0x3E},  // @
    {0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C},  // A
    {0x00, 0x7F, 0x49, 0x49, 0x49, 0x36},  // B
    {0x00, 0x3E, 0x41, 0x41, 0x41, 0x22},  // C
    {0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C},  // D
    {0x00, 0x7F, 0x49, 0x49, 0x49, 0x41},  // E
    {0x00, 0x7F, 0x09, 0x09, 0x09, 0x01},  // F
    {0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A},  // G
    {0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F},  // H
    {0x00, 0x00, 0x41, 0x7F, 0x41, 0x00},  // I
    {0x00, 0x20, 0x40, 0x41, 0x3F, 0x01},  // J
    {0x00, 0x7F, 0x08, 0x14, 0x22, 0x41},  // K
    {0x00, 0x7F, 0x40, 0x40, 0x40, 0x40},  // L
    {0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F},  // M
    {0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F},  // N
    {0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E},  // O
    {0x00, 0x7F, 0x09, 0x09, 0x09, 0x06},  // P
    {0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E},  // Q
    {0x00, 0x7F, 0x09, 0x19, 0x29, 0x46},  // R
    {0x00, 0x46, 0x49, 0x49, 0x49, 0x31},  // S
    {0x00, 0x01, 0x01, 0x7F, 0x01, 0x01},  // T
    {0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F},  // U
    {0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F},  // V
    {0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F},  // W
    {0x00, 0x63, 0x14, 0x08, 0x14, 0x63},  // X
    {0x00, 0x07, 0x08, 0x70, 0x08, 0x07},  // Y
    {0x00, 0x61, 0x51, 0x49, 0x45, 0x43},  // Z
    {0x00, 0x00, 0x7F, 0x41, 0x41, 0x00},  // [
    {0x00, 0x55, 0x2A, 0x55, 0x2A, 0x55},  // 55
    {0x00, 0x00, 0x41, 0x41, 0x7F, 0x00},  // ]
    {0x00, 0x04, 0x02, 0x01, 0x02, 0x04},  // ^
    {0x00, 0x40, 0x40, 0x40, 0x40, 0x40},  // _
    {0x00, 0x00, 0x01, 0x02, 0x04, 0x00},  // '
    {0x00, 0x20, 0x54, 0x54, 0x54, 0x78},  // a
    {0x00, 0x7F, 0x48, 0x44, 0x44, 0x38},  // b
    {0x00, 0x38, 0x44, 0x44, 0x44, 0x20},  // c
    {0x00, 0x38, 0x44, 0x44, 0x48, 0x7F},  // d
    {0x00, 0x38, 0x54, 0x54, 0x54, 0x18},  // e
    {0x00, 0x08, 0x7E, 0x09, 0x01, 0x02},  // f
    {0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C},  // g
    {0x00, 0x7F, 0x08, 0x04, 0x04, 0x78},  // h
    {0x00, 0x00, 0x44, 0x7D, 0x40, 0x00},  // i
    {0x00, 0x40, 0x80, 0x84, 0x7D, 0x00},  // j
    {0x00, 0x7F, 0x10, 0x28, 0x44, 0x00},  // k
    {0x00, 0x00, 0x41, 0x7F, 0x40, 0x00},  // l
    {0x00, 0x7C, 0x04, 0x18, 0x04, 0x78},  // m
    {0x00, 0x7C, 0x08, 0x04, 0x04, 0x78},  // n
    {0x00, 0x38, 0x44, 0x44, 0x44, 0x38},  // o
    {0x00, 0xFC, 0x24, 0x24, 0x24, 0x18},  // p
    {0x00, 0x18, 0x24, 0x24, 0x18, 0xFC},  // q
    {0x00, 0x7C, 0x08, 0x04, 0x04, 0x08},  // r
    {0x00, 0x48, 0x54, 0x54, 0x54, 0x20},  // s
    {0x00, 0x04, 0x3F, 0x44, 0x40, 0x20},  // t
    {0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C},  // u
    {0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C},  // v
    {0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C},  // w
    {0x00, 0x44, 0x28, 0x10, 0x28, 0x44},  // x
    {0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C},  // y
    {0x00, 0x44, 0x64, 0x54, 0x4C, 0x44},  // z
    {0x14, 0x14, 0x14, 0x14, 0x14, 0x14},  // horiz lines
};

/****************************************8*16 table************************************/
const unsigned char F8X16[] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //  0
    0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x30, 0x00, 0x00, 0x00,  //! 1
    0x00, 0x10, 0x0C, 0x06, 0x10, 0x0C, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //" 2
    0x40, 0xC0, 0x78, 0x40, 0xC0, 0x78, 0x40, 0x00, 0x04, 0x3F, 0x04, 0x04, 0x3F, 0x04, 0x04, 0x00,  //# 3
    0x00, 0x70, 0x88, 0xFC, 0x08, 0x30, 0x00, 0x00, 0x00, 0x18, 0x20, 0xFF, 0x21, 0x1E, 0x00, 0x00,  //$ 4
    0xF0, 0x08, 0xF0, 0x00, 0xE0, 0x18, 0x00, 0x00, 0x00, 0x21, 0x1C, 0x03, 0x1E, 0x21, 0x1E, 0x00,  //% 5
    0x00, 0xF0, 0x08, 0x88, 0x70, 0x00, 0x00, 0x00, 0x1E, 0x21, 0x23, 0x24, 0x19, 0x27, 0x21, 0x10,  //& 6
    0x10, 0x16, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //' 7
    0x00, 0x00, 0x00, 0xE0, 0x18, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00, 0x07, 0x18, 0x20, 0x40, 0x00,  //( 8
    0x00, 0x02, 0x04, 0x18, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x40, 0x20, 0x18, 0x07, 0x00, 0x00, 0x00,  //) 9
    0x40, 0x40, 0x80, 0xF0, 0x80, 0x40, 0x40, 0x00, 0x02, 0x02, 0x01, 0x0F, 0x01, 0x02, 0x02, 0x00,  //* 10
    0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x1F, 0x01, 0x01, 0x01, 0x00,  //+ 11
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xB0, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00,  //, 12
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,  //- 13
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00,  //. 14
    0x00, 0x00, 0x00, 0x00, 0x80, 0x60, 0x18, 0x04, 0x00, 0x60, 0x18, 0x06, 0x01, 0x00, 0x00, 0x00,  /// 15
    0x00, 0xE0, 0x10, 0x08, 0x08, 0x10, 0xE0, 0x00, 0x00, 0x0F, 0x10, 0x20, 0x20, 0x10, 0x0F, 0x00,  //0 16
    0x00, 0x10, 0x10, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x3F, 0x20, 0x20, 0x00, 0x00,  //1 17
    0x00, 0x70, 0x08, 0x08, 0x08, 0x88, 0x70, 0x00, 0x00, 0x30, 0x28, 0x24, 0x22, 0x21, 0x30, 0x00,  //2 18
    0x00, 0x30, 0x08, 0x88, 0x88, 0x48, 0x30, 0x00, 0x00, 0x18, 0x20, 0x20, 0x20, 0x11, 0x0E, 0x00,  //3 19
    0x00, 0x00, 0xC0, 0x20, 0x10, 0xF8, 0x00, 0x00, 0x00, 0x07, 0x04, 0x24, 0x24, 0x3F, 0x24, 0x00,  //4 20
    0x00, 0xF8, 0x08, 0x88, 0x88, 0x08, 0x08, 0x00, 0x00, 0x19, 0x21, 0x20, 0x20, 0x11, 0x0E, 0x00,  //5 21
    0x00, 0xE0, 0x10, 0x88, 0x88, 0x18, 0x00, 0x00, 0x00, 0x0F, 0x11, 0x20, 0x20, 0x11, 0x0E, 0x00,  //6 22
    0x00, 0x38, 0x08, 0x08, 0xC8, 0x38, 0x08, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00,  //7 23
    0x00, 0x70, 0x88, 0x08, 0x08, 0x88, 0x70, 0x00, 0x00, 0x1C, 0x22, 0x21, 0x21, 0x22, 0x1C, 0x00,  //8 24
    0x00, 0xE0, 0x10, 0x08, 0x08, 0x10, 0xE0, 0x00, 0x00, 0x00, 0x31, 0x22, 0x22, 0x11, 0x0F, 0x00,  //9 25
    0x00, 0x00, 0x00, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00,  //: 26
    0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x60, 0x00, 0x00, 0x00, 0x00,  //; 27
    0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x08, 0x00, 0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x00,  //< 28
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x00, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00,  //= 29
    0x00, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00,  //> 30
    0x00, 0x70, 0x48, 0x08, 0x08, 0x08, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x30, 0x36, 0x01, 0x00, 0x00,  //? 31
    0xC0, 0x30, 0xC8, 0x28, 0xE8, 0x10, 0xE0, 0x00, 0x07, 0x18, 0x27, 0x24, 0x23, 0x14, 0x0B, 0x00,  //@ 32
    0x00, 0x00, 0xC0, 0x38, 0xE0, 0x00, 0x00, 0x00, 0x20, 0x3C, 0x23, 0x02, 0x02, 0x27, 0x38, 0x20,  //A 33
    0x08, 0xF8, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00, 0x20, 0x3F, 0x20, 0x20, 0x20, 0x11, 0x0E, 0x00,  //B 34
    0xC0, 0x30, 0x08, 0x08, 0x08, 0x08, 0x38, 0x00, 0x07, 0x18, 0x20, 0x20, 0x20, 0x10, 0x08, 0x00,  //C 35
    0x08, 0xF8, 0x08, 0x08, 0x08, 0x10, 0xE0, 0x00, 0x20, 0x3F, 0x20, 0x20, 0x20, 0x10, 0x0F, 0x00,  //D 36
    0x08, 0xF8, 0x88, 0x88, 0xE8, 0x08, 0x10, 0x00, 0x20, 0x3F, 0x20, 0x20, 0x23, 0x20, 0x18, 0x00,  //E 37
    0x08, 0xF8, 0x88, 0x88, 0xE8, 0x08, 0x10, 0x00, 0x20, 0x3F, 0x20, 0x00, 0x03, 0x00, 0x00, 0x00,  //F 38
    0xC0, 0x30, 0x08, 0x08, 0x08, 0x38, 0x00, 0x00, 0x07, 0x18, 0x20, 0x20, 0x22, 0x1E, 0x02, 0x00,  //G 39
    0x08, 0xF8, 0x08, 0x00, 0x00, 0x08, 0xF8, 0x08, 0x20, 0x3F, 0x21, 0x01, 0x01, 0x21, 0x3F, 0x20,  //H 40
    0x00, 0x08, 0x08, 0xF8, 0x08, 0x08, 0x00, 0x00, 0x00, 0x20, 0x20, 0x3F, 0x20, 0x20, 0x00, 0x00,  //I 41
    0x00, 0x00, 0x08, 0x08, 0xF8, 0x08, 0x08, 0x00, 0xC0, 0x80, 0x80, 0x80, 0x7F, 0x00, 0x00, 0x00,  //J 42
    0x08, 0xF8, 0x88, 0xC0, 0x28, 0x18, 0x08, 0x00, 0x20, 0x3F, 0x20, 0x01, 0x26, 0x38, 0x20, 0x00,  //K 43
    0x08, 0xF8, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x3F, 0x20, 0x20, 0x20, 0x20, 0x30, 0x00,  //L 44
    0x08, 0xF8, 0xF8, 0x00, 0xF8, 0xF8, 0x08, 0x00, 0x20, 0x3F, 0x00, 0x3F, 0x00, 0x3F, 0x20, 0x00,  //M 45
    0x08, 0xF8, 0x30, 0xC0, 0x00, 0x08, 0xF8, 0x08, 0x20, 0x3F, 0x20, 0x00, 0x07, 0x18, 0x3F, 0x00,  //N 46
    0xE0, 0x10, 0x08, 0x08, 0x08, 0x10, 0xE0, 0x00, 0x0F, 0x10, 0x20, 0x20, 0x20, 0x10, 0x0F, 0x00,  //O 47
    0x08, 0xF8, 0x08, 0x08, 0x08, 0x08, 0xF0, 0x00, 0x20, 0x3F, 0x21, 0x01, 0x01, 0x01, 0x00, 0x00,  //P 48
    0xE0, 0x10, 0x08, 0x08, 0x08, 0x10, 0xE0, 0x00, 0x0F, 0x18, 0x24, 0x24, 0x38, 0x50, 0x4F, 0x00,  //Q 49
    0x08, 0xF8, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 0x20, 0x3F, 0x20, 0x00, 0x03, 0x0C, 0x30, 0x20,  //R 50
    0x00, 0x70, 0x88, 0x08, 0x08, 0x08, 0x38, 0x00, 0x00, 0x38, 0x20, 0x21, 0x21, 0x22, 0x1C, 0x00,  //S 51
    0x18, 0x08, 0x08, 0xF8, 0x08, 0x08, 0x18, 0x00, 0x00, 0x00, 0x20, 0x3F, 0x20, 0x00, 0x00, 0x00,  //T 52
    0x08, 0xF8, 0x08, 0x00, 0x00, 0x08, 0xF8, 0x08, 0x00, 0x1F, 0x20, 0x20, 0x20, 0x20, 0x1F, 0x00,  //U 53
    0x08, 0x78, 0x88, 0x00, 0x00, 0xC8, 0x38, 0x08, 0x00, 0x00, 0x07, 0x38, 0x0E, 0x01, 0x00, 0x00,  //V 54
    0xF8, 0x08, 0x00, 0xF8, 0x00, 0x08, 0xF8, 0x00, 0x03, 0x3C, 0x07, 0x00, 0x07, 0x3C, 0x03, 0x00,  //W 55
    0x08, 0x18, 0x68, 0x80, 0x80, 0x68, 0x18, 0x08, 0x20, 0x30, 0x2C, 0x03, 0x03, 0x2C, 0x30, 0x20,  //X 56
    0x08, 0x38, 0xC8, 0x00, 0xC8, 0x38, 0x08, 0x00, 0x00, 0x00, 0x20, 0x3F, 0x20, 0x00, 0x00, 0x00,  //Y 57
    0x10, 0x08, 0x08, 0x08, 0xC8, 0x38, 0x08, 0x00, 0x20, 0x38, 0x26, 0x21, 0x20, 0x20, 0x18, 0x00,  //Z 58
    0x00, 0x00, 0x00, 0xFE, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x40, 0x40, 0x40, 0x00,  //[ 59
    0x00, 0x0C, 0x30, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x06, 0x38, 0xC0, 0x00,  //\ 60
    0x00, 0x02, 0x02, 0x02, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x7F, 0x00, 0x00, 0x00,  //] 61
    0x00, 0x00, 0x04, 0x02, 0x02, 0x02, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //^ 62
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,  //_ 63
    0x00, 0x02, 0x02, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //` 64
    0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x19, 0x24, 0x22, 0x22, 0x22, 0x3F, 0x20,  //a 65
    0x08, 0xF8, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x11, 0x20, 0x20, 0x11, 0x0E, 0x00,  //b 66
    0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x0E, 0x11, 0x20, 0x20, 0x20, 0x11, 0x00,  //c 67
    0x00, 0x00, 0x00, 0x80, 0x80, 0x88, 0xF8, 0x00, 0x00, 0x0E, 0x11, 0x20, 0x20, 0x10, 0x3F, 0x20,  //d 68
    0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x1F, 0x22, 0x22, 0x22, 0x22, 0x13, 0x00,  //e 69
    0x00, 0x80, 0x80, 0xF0, 0x88, 0x88, 0x88, 0x18, 0x00, 0x20, 0x20, 0x3F, 0x20, 0x20, 0x00, 0x00,  //f 70
    0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x6B, 0x94, 0x94, 0x94, 0x93, 0x60, 0x00,  //g 71
    0x08, 0xF8, 0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 0x20, 0x3F, 0x21, 0x00, 0x00, 0x20, 0x3F, 0x20,  //h 72
    0x00, 0x80, 0x98, 0x98, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x3F, 0x20, 0x20, 0x00, 0x00,  //i 73
    0x00, 0x00, 0x00, 0x80, 0x98, 0x98, 0x00, 0x00, 0x00, 0xC0, 0x80, 0x80, 0x80, 0x7F, 0x00, 0x00,  //j 74
    0x08, 0xF8, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0x20, 0x3F, 0x24, 0x02, 0x2D, 0x30, 0x20, 0x00,  //k 75
    0x00, 0x08, 0x08, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x3F, 0x20, 0x20, 0x00, 0x00,  //l 76
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x20, 0x3F, 0x20, 0x00, 0x3F, 0x20, 0x00, 0x3F,  //m 77
    0x80, 0x80, 0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 0x20, 0x3F, 0x21, 0x00, 0x00, 0x20, 0x3F, 0x20,  //n 78
    0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x1F, 0x20, 0x20, 0x20, 0x20, 0x1F, 0x00,  //o 79
    0x80, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x80, 0xFF, 0xA1, 0x20, 0x20, 0x11, 0x0E, 0x00,  //p 80
    0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x0E, 0x11, 0x20, 0x20, 0xA0, 0xFF, 0x80,  //q 81
    0x80, 0x80, 0x80, 0x00, 0x80, 0x80, 0x80, 0x00, 0x20, 0x20, 0x3F, 0x21, 0x20, 0x00, 0x01, 0x00,  //r 82
    0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x33, 0x24, 0x24, 0x24, 0x24, 0x19, 0x00,  //s 83
    0x00, 0x80, 0x80, 0xE0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x20, 0x20, 0x00, 0x00,  //t 84
    0x80, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x1F, 0x20, 0x20, 0x20, 0x10, 0x3F, 0x20,  //u 85
    0x80, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0x01, 0x0E, 0x30, 0x08, 0x06, 0x01, 0x00,  //v 86
    0x80, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x80, 0x0F, 0x30, 0x0C, 0x03, 0x0C, 0x30, 0x0F, 0x00,  //w 87
    0x00, 0x80, 0x80, 0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 0x20, 0x31, 0x2E, 0x0E, 0x31, 0x20, 0x00,  //x 88
    0x80, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x81, 0x8E, 0x70, 0x18, 0x06, 0x01, 0x00,  //y 89
    0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x21, 0x30, 0x2C, 0x22, 0x21, 0x30, 0x00,  //z 90
    0x00, 0x00, 0x00, 0x00, 0x80, 0x7C, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x40, 0x40,  //{ 91
    0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00,  //| 92
    0x00, 0x02, 0x02, 0x7C, 0x80, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x3F, 0x00, 0x00, 0x00, 0x00,  //} 93
    0x00, 0x06, 0x01, 0x01, 0x02, 0x02, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //~ 94
};

static xTimerHandle led_set_tmr;
static xTimerHandle led_clr_tmr;

static int led_md = 0;
static int led_off = LED_OFF;
static int led_intv = 0;
static int led_dc = 0;

static void led_set(int mode)
{
    switch (mode) {
        case LED_OFF:
            ioe_set(IOE_LED_RED, 1);
            ioe_set(IOE_LED_GREEN, 1);
            ioe_set(IOE_LED_BLUE, 1);
            break;
        case LED_GREEN:
            ioe_set(IOE_LED_RED, 1);
            ioe_set(IOE_LED_BLUE, 1);
            ioe_set(IOE_LED_GREEN, 0);
            break;
        case LED_RED:
            ioe_set(IOE_LED_GREEN, 1);
            ioe_set(IOE_LED_BLUE, 1);
            ioe_set(IOE_LED_RED, 0);
            break;

        case LED_RG:
            ioe_set(IOE_LED_BLUE, 1);
            ioe_set(IOE_LED_RED, 0);
            ioe_set(IOE_LED_GREEN, 0);
            break;
        default:
            break;
    }
}

static void led_set_cb(xTimerHandle tmr)
{
    led_set(led_md);
    xTimerReset(led_clr_tmr, 0);
}

static void led_clear_cb(xTimerHandle tmr)
{
    led_set(led_off);
    xTimerReset(led_set_tmr, 0);
}

void led_mode(int mode, int intv /* [ms] */, int duty_cycle /* [%] */)
{
    if (mode == led_md && intv == led_intv && duty_cycle == led_dc ) {
        return;
    }

    led_md = mode == LED_RG ? LED_GREEN : mode;
    led_off = mode == LED_RG ? LED_RED : LED_OFF;
    led_intv = intv;
    led_dc = duty_cycle;

    xTimerStop(led_clr_tmr, 0);
    xTimerStop(led_set_tmr, 0);

    if(led_intv >= LED_MIN_INTV_MS && led_dc >= LED_MIN_DC && led_dc <= (100-LED_MIN_DC)) {
        xTimerChangePeriod( led_clr_tmr, led_intv * led_dc / 100 / portTICK_RATE_MS, 0);
        xTimerChangePeriod( led_set_tmr, led_intv * (100 - led_dc) / 100 / portTICK_RATE_MS, 0);
        led_set_cb(led_set_tmr);
    } else {
        led_set(led_md);
    }
}

void ioe_init(void)
{
    ioe_set_mode(IOE_LED_RED, 2);
    ioe_set_mode(IOE_LED_GREEN, 2);
    ioe_set_mode(IOE_LED_BLUE, 2);

    oled_init();
    oled_cls();

    led_set_tmr = xTimerCreate("TimerLedSet", 100/portTICK_RATE_MS, false, NULL, led_set_cb );
    led_clr_tmr = xTimerCreate("TimerledClr", 100/portTICK_RATE_MS, false, NULL, led_clear_cb );
}

static void write_cmd(uint8_t cmd)
{
    i2c_esp32_write(SSD1306_ADDR, 0x00, cmd);
}

static void write_data(uint8_t data)
{
    i2c_esp32_write(SSD1306_ADDR, 0x40, data);
}

void oled_init()
{
    i2c_esp32_open();

    wait_ms(100);
    write_cmd(0xAE); //display off
    write_cmd(0x20); //Set Memory Addressing Mode
    write_cmd(0x10); //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
    write_cmd(0xb0); //Set Page Start Address for Page Addressing Mode,0-7
    write_cmd(0xc8); //Set COM Output Scan Direction
    write_cmd(0x00); //---set low column address
    write_cmd(0x10); //---set high column address
    write_cmd(0x40); //--set start line address
    write_cmd(0x81); //--set contrast control register
    write_cmd(0xff); //brightless 0x00~0xff
    write_cmd(0xa1); //--set segment re-map 0 to 127
    write_cmd(0xa6); //--set normal display
    write_cmd(0xa8); //--set multiplex ratio(1 to 64)
    write_cmd(0x3F); //
    write_cmd(0xa4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
    write_cmd(0xd3); //-set display offset
    write_cmd(0x00); //-not offset
    write_cmd(0xd5); //--set display clock divide ratio/oscillator frequency
    write_cmd(0xf0); //--set divide ratio
    write_cmd(0xd9); //--set pre-charge period
    write_cmd(0x22); //
    write_cmd(0xda); //--set com pins hardware configuration
    write_cmd(0x12);
    write_cmd(0xdb); //--set vcomh
    write_cmd(0x20); //0x20,0.77xVcc
    write_cmd(0x8d); //--set DC-DC enable
    write_cmd(0x14); //
    write_cmd(0xaf); //--turn on oled panel
}

void oled_set_pos(uint8_t x, uint8_t y) //set the start position
{
    write_cmd(0xb0 + y);
    write_cmd(((x & 0xf0) >> 4) | 0x10);
    write_cmd((x & 0x0f) | 0x01);
}

void oled_fill(uint8_t fill_Data)//fill the screen
{
    unsigned char m, n;

    for(m=0; m<8; m++) {
        write_cmd(0xb0+m);  //page0-page1
        write_cmd(0x00);    //low column start address
        write_cmd(0x10);    //high column start address
        for(n=0; n<128; n++) {
            write_data(fill_Data);
        }
    }
}

void oled_cls(void) //clear screen
{
    oled_fill(0x00);
}

void oled_on(void)
{
    write_cmd(0X8D);  //setup pump
    write_cmd(0X14);  //turn on pump
    write_cmd(0XAF);  //OLED wakeup
}

void oled_off(void)
{
    write_cmd(0X8D);  //
    write_cmd(0X10);  //close pump
    write_cmd(0XAE);  //OLED sleep
}

void oled_show_str(uint8_t x, uint8_t y, char ch[], uint8_t text_size)
{
    unsigned char c = 0, i = 0, j = 0;

    switch(text_size) {
        case 1:
            while(ch[j] != '\0') {
                if(x > 126) {
                    x = 0;
                    y++;
                }

                c = ch[j] - 32;
                oled_set_pos(x, y);
                for(i=0; i<6; i++)
                    write_data(F6x8[c][i]);
                x += 6;
                j++;
            }
            break;

        case 2:
            while(ch[j] != '\0') {
                if(x > 120) {
                    x = 0;
                    y += 2;
                }

                c = ch[j] - 32;
                oled_set_pos(x, y);
                for(i=0; i<8; i++)
                    write_data(F8X16[c * 16 + i]);

                oled_set_pos(x, y+1);
                for(i=0; i<8; i++)
                    write_data(F8X16[c * 16 + i + 8]);
                x += 8;
                j++;
            }
            break;
    }
}
