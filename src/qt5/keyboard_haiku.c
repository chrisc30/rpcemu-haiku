/*
  RPCEmu - An Acorn system emulator

  Copyright (C) 2017 Matthew Howkins

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/*
 * Keyboard mapping for Haiku.
 *
 * Haiku's Qt5 port always returns 0 for nativeScanCode() and
 * nativeVirtualKey(), so we map from the Qt portable key enum
 * (Qt::Key_*) to PS/2 Set 2 make codes instead.
 *
 * The "native_scancode" field here holds the Qt::Key value,
 * which is what main_window.cpp passes via key_press_signal
 * on Haiku (see the Q_OS_HAIKU block in keyPressEvent).
 */

#include <stddef.h>
#include <stdint.h>

typedef struct {
	uint32_t	native_scancode;	/* Qt::Key value on Haiku */
	uint8_t		set_2[8];		/* PS/2 Set 2 make code   */
} KeyMapInfo;

static const KeyMapInfo key_map[] = {
	/* Function keys */
	{ 0x01000030, { 0x05 } },	/* Qt::Key_F1            */
	{ 0x01000031, { 0x06 } },	/* Qt::Key_F2            */
	{ 0x01000032, { 0x04 } },	/* Qt::Key_F3            */
	{ 0x01000033, { 0x0c } },	/* Qt::Key_F4            */
	{ 0x01000034, { 0x03 } },	/* Qt::Key_F5            */
	{ 0x01000035, { 0x0b } },	/* Qt::Key_F6            */
	{ 0x01000036, { 0x83 } },	/* Qt::Key_F7            */
	{ 0x01000037, { 0x0a } },	/* Qt::Key_F8            */
	{ 0x01000038, { 0x01 } },	/* Qt::Key_F9            */
	{ 0x01000039, { 0x09 } },	/* Qt::Key_F10           */
	{ 0x0100003a, { 0x78 } },	/* Qt::Key_F11           */
	{ 0x0100003b, { 0x07 } },	/* Qt::Key_F12           */

	/* Modifiers */
	{ 0x01000020, { 0x12 } },	/* Qt::Key_Shift (left)  */
	{ 0x01000021, { 0x14 } },	/* Qt::Key_Control (left)*/
	{ 0x01000022, { 0x11 } },	/* Qt::Key_Alt (left)    */
	{ 0x01000023, { 0xe0, 0x11 } },	/* Qt::Key_Meta/AltGr    */
	{ 0x01000024, { 0x58 } },	/* Qt::Key_CapsLock      */
	{ 0x01000025, { 0x77 } },	/* Qt::Key_NumLock       */
	{ 0x01000026, { 0x7e } },	/* Qt::Key_ScrollLock    */

	/* Navigation */
	{ 0x01000010, { 0xe0, 0x6c } },	/* Qt::Key_Home          */
	{ 0x01000011, { 0xe0, 0x69 } },	/* Qt::Key_End           */
	{ 0x01000012, { 0xe0, 0x6b } },	/* Qt::Key_Left          */
	{ 0x01000013, { 0xe0, 0x75 } },	/* Qt::Key_Up            */
	{ 0x01000014, { 0xe0, 0x74 } },	/* Qt::Key_Right         */
	{ 0x01000015, { 0xe0, 0x72 } },	/* Qt::Key_Down          */
	{ 0x01000016, { 0xe0, 0x70 } },	/* Qt::Key_Insert        */
	{ 0x01000017, { 0xe0, 0x7d } },	/* Qt::Key_PageUp        */
	{ 0x01000018, { 0xe0, 0x7a } },	/* Qt::Key_PageDown      */

	/* Misc */
	{ 0x01000000, { 0x76 } },	/* Qt::Key_Escape        */
	{ 0x01000001, { 0x0d } },	/* Qt::Key_Tab           */
	{ 0x01000003, { 0x66 } },	/* Qt::Key_Backspace     */
	{ 0x01000004, { 0x5a } },	/* Qt::Key_Return        */
	{ 0x01000005, { 0xe0, 0x5a } },	/* Qt::Key_Enter (KP)    */
	{ 0x01000007, { 0xe0, 0x71 } },	/* Qt::Key_Delete        */
	{ 0x01000008, { 0xe0, 0x1f } },	/* Qt::Key_Super_L       */
	{ 0x01000009, { 0xe0, 0x27 } },	/* Qt::Key_Super_R       */

	/* Number row */
	{ 0x60, { 0x0e } },		/* ` ~                   */
	{ 0x31, { 0x16 } },		/* 1 !                   */
	{ 0x32, { 0x1e } },		/* 2 @                   */
	{ 0x33, { 0x26 } },		/* 3 #                   */
	{ 0x34, { 0x25 } },		/* 4 $                   */
	{ 0x35, { 0x2e } },		/* 5 %                   */
	{ 0x36, { 0x36 } },		/* 6 ^                   */
	{ 0x37, { 0x3d } },		/* 7 &                   */
	{ 0x38, { 0x3e } },		/* 8 *                   */
	{ 0x39, { 0x46 } },		/* 9 (                   */
	{ 0x30, { 0x45 } },		/* 0 )                   */
	{ 0x2d, { 0x4e } },		/* - _                   */
	{ 0x3d, { 0x55 } },		/* = +                   */

	/* QWERTY row */
	{ 0x51, { 0x15 } },		/* Q                     */
	{ 0x57, { 0x1d } },		/* W                     */
	{ 0x45, { 0x24 } },		/* E                     */
	{ 0x52, { 0x2d } },		/* R                     */
	{ 0x54, { 0x2c } },		/* T                     */
	{ 0x59, { 0x35 } },		/* Y                     */
	{ 0x55, { 0x3c } },		/* U                     */
	{ 0x49, { 0x43 } },		/* I                     */
	{ 0x4f, { 0x44 } },		/* O                     */
	{ 0x50, { 0x4d } },		/* P                     */
	{ 0x5b, { 0x54 } },		/* [ {                   */
	{ 0x5d, { 0x5b } },		/* ] }                   */
	{ 0x5c, { 0x5d } },		/* \ |                   */

	/* ASDF row */
	{ 0x41, { 0x1c } },		/* A                     */
	{ 0x53, { 0x1b } },		/* S                     */
	{ 0x44, { 0x23 } },		/* D                     */
	{ 0x46, { 0x2b } },		/* F                     */
	{ 0x47, { 0x34 } },		/* G                     */
	{ 0x48, { 0x33 } },		/* H                     */
	{ 0x4a, { 0x3b } },		/* J                     */
	{ 0x4b, { 0x42 } },		/* K                     */
	{ 0x4c, { 0x4b } },		/* L                     */
	{ 0x3b, { 0x4c } },		/* ; :                   */
	{ 0x27, { 0x52 } },		/* ' "                   */
	{ 0x23, { 0x5d } },		/* # ~ (ISO key)         */

	/* ZXCV row */
	{ 0x5a, { 0x1a } },		/* Z                     */
	{ 0x58, { 0x22 } },		/* X                     */
	{ 0x43, { 0x21 } },		/* C                     */
	{ 0x56, { 0x2a } },		/* V                     */
	{ 0x42, { 0x32 } },		/* B                     */
	{ 0x4e, { 0x31 } },		/* N                     */
	{ 0x4d, { 0x3a } },		/* M                     */
	{ 0x2c, { 0x41 } },		/* , <                   */
	{ 0x2e, { 0x49 } },		/* . >                   */
	{ 0x2f, { 0x4a } },		/* / ?                   */

	/* Space */
	{ 0x20, { 0x29 } },		/* Space                 */

	/* Keypad */
	{ 0x0100003f, { 0x7c } },	/* Qt::Key_multiply (KP*)*/
	{ 0x01000022, { 0x77 } },	/* Qt::Key_NumLock       */
	{ 0x01000090, { 0x69 } },	/* Qt::Key_1 KP End      */
	{ 0x01000091, { 0x72 } },	/* Qt::Key_2 KP Down     */
	{ 0x01000092, { 0x6c } },	/* Qt::Key_7 KP Home     */  
	{ 0x01000093, { 0x6b } },	/* Qt::Key_4 KP Left     */
	{ 0x01000094, { 0x73 } },	/* Qt::Key_5 KP          */
	{ 0x01000095, { 0x74 } },	/* Qt::Key_6 KP Right    */
	{ 0x01000096, { 0x75 } },	/* Qt::Key_8 KP Up       */
	{ 0x01000097, { 0x70 } },	/* Qt::Key_0 KP Ins      */
	{ 0x01000098, { 0x7a } },	/* Qt::Key_3 KP PgDn     */
	{ 0x01000099, { 0x7d } },	/* Qt::Key_9 KP PgUp     */
	{ 0x0100009a, { 0x71 } },	/* Qt::Key_KP_Decimal    */
	{ 0x0100009b, { 0x7b } },	/* Qt::Key_KP_Subtract   */
	{ 0x0100009c, { 0xe0, 0x4a } },	/* Qt::Key_KP_Divide     */
	{ 0x0100009d, { 0x79 } },	/* Qt::Key_KP_Add        */

/* Shifted punctuation aliases - Haiku Qt reports Unicode char value */
	{ 0x3e, { 0x49 } },		/* . > (shifted) */
	{ 0x3c, { 0x41 } },		/* , < (shifted) */
	{ 0x3f, { 0x4a } },		/* / ? (shifted) */
	{ 0x3a, { 0x4c } },		/* ; : (shifted) */
	{ 0x22, { 0x52 } },		/* ' " (shifted) */
	{ 0x7b, { 0x54 } },		/* [ { (shifted) */
	{ 0x7d, { 0x5b } },		/* ] } (shifted) */
	{ 0x7c, { 0x5d } },		/* \ | (shifted) */
	{ 0x7e, { 0x0e } },		/* ` ~ (shifted) */
	{ 0x21, { 0x16 } },		/* 1 ! (shifted) */
	{ 0x40, { 0x1e } },		/* 2 @ (shifted) */
	{ 0x23, { 0x26 } },		/* 3 # (shifted) */
	{ 0x24, { 0x25 } },		/* 4 $ (shifted) */
	{ 0x25, { 0x2e } },		/* 5 % (shifted) */
	{ 0x5e, { 0x36 } },		/* 6 ^ (shifted) */
	{ 0x26, { 0x3d } },		/* 7 & (shifted) */
	{ 0x2a, { 0x3e } },		/* 8 * (shifted) */
	{ 0x28, { 0x46 } },		/* 9 ( (shifted) */
	{ 0x29, { 0x45 } },		/* 0 ) (shifted) */
	{ 0x5f, { 0x4e } },		/* - _ (shifted) */
	{ 0x2b, { 0x55 } },		/* = + (shifted) */
	{ 0, { 0, 0 } },		/* sentinel              */
};

const uint8_t *
keyboard_map_key(uint32_t native_scancode)
{
	size_t k;

	for (k = 0; key_map[k].native_scancode != 0; k++) {
		if (key_map[k].native_scancode == native_scancode) {
			return key_map[k].set_2;
		}
	}
	return NULL;
}
