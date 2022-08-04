/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxdef.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 13:35:26 by jkong             #+#    #+#             */
/*   Updated: 2022/08/04 15:32:22 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLXDEF_H
# define MLXDEF_H

/*
 * Reference:
 * /Library/Developer/CommandLineTools/
 * SDKs/MacOSX.sdk/System/Library/Frameworks/Carbon.framework/
 * Versions/A/Frameworks/HIToolbox.framework/Versions/A/Headers/Events.h
 */

/*
 *  Summary:
 *    Virtual keycodes
 *
 *  Discussion:
 *    These constants are the virtual keycodes defined originally in
 *    Inside Mac Volume V, pg. V-191. They identify physical keys on a
 *    keyboard. Those constants with "ANSI" in the name are labeled
 *    according to the key position on an ANSI-standard US keyboard.
 *    For example, kVK_ANSI_A indicates the virtual keycode for the key
 *    with the letter 'A' in the US keyboard layout. Other keyboard
 *    layouts may have the 'A' key label on a different physical key;
 *    in this case, pressing 'A' will generate a different virtual
 *    keycode.
 */
enum e_mac_virtual_keycode_ansi
{
	kVK_ANSI_A = 0x00,
	kVK_ANSI_S = 0x01,
	kVK_ANSI_D = 0x02,
	kVK_ANSI_F = 0x03,
	kVK_ANSI_H = 0x04,
	kVK_ANSI_G = 0x05,
	kVK_ANSI_Z = 0x06,
	kVK_ANSI_X = 0x07,
	kVK_ANSI_C = 0x08,
	kVK_ANSI_V = 0x09,
	kVK_ANSI_B = 0x0B,
	kVK_ANSI_Q = 0x0C,
	kVK_ANSI_W = 0x0D,
	kVK_ANSI_E = 0x0E,
	kVK_ANSI_R = 0x0F,
	kVK_ANSI_Y = 0x10,
	kVK_ANSI_T = 0x11,
	kVK_ANSI_1 = 0x12,
	kVK_ANSI_2 = 0x13,
	kVK_ANSI_3 = 0x14,
	kVK_ANSI_4 = 0x15,
	kVK_ANSI_6 = 0x16,
	kVK_ANSI_5 = 0x17,
	kVK_ANSI_Equal = 0x18,
	kVK_ANSI_9 = 0x19,
	kVK_ANSI_7 = 0x1A,
	kVK_ANSI_Minus = 0x1B,
	kVK_ANSI_8 = 0x1C,
	kVK_ANSI_0 = 0x1D,
	kVK_ANSI_RightBracket = 0x1E,
	kVK_ANSI_O = 0x1F,
	kVK_ANSI_U = 0x20,
	kVK_ANSI_LeftBracket = 0x21,
	kVK_ANSI_I = 0x22,
	kVK_ANSI_P = 0x23,
	kVK_ANSI_L = 0x25,
	kVK_ANSI_J = 0x26,
	kVK_ANSI_Quote = 0x27,
	kVK_ANSI_K = 0x28,
	kVK_ANSI_Semicolon = 0x29,
	kVK_ANSI_Backslash = 0x2A,
	kVK_ANSI_Comma = 0x2B,
	kVK_ANSI_Slash = 0x2C,
	kVK_ANSI_N = 0x2D,
	kVK_ANSI_M = 0x2E,
	kVK_ANSI_Period = 0x2F,
	kVK_ANSI_Grave = 0x32,
	kVK_ANSI_KeypadDecimal = 0x41,
	kVK_ANSI_KeypadMultiply = 0x43,
	kVK_ANSI_KeypadPlus = 0x45,
	kVK_ANSI_KeypadClear = 0x47,
	kVK_ANSI_KeypadDivide = 0x4B,
	kVK_ANSI_KeypadEnter = 0x4C,
	kVK_ANSI_KeypadMinus = 0x4E,
	kVK_ANSI_KeypadEquals = 0x51,
	kVK_ANSI_Keypad0 = 0x52,
	kVK_ANSI_Keypad1 = 0x53,
	kVK_ANSI_Keypad2 = 0x54,
	kVK_ANSI_Keypad3 = 0x55,
	kVK_ANSI_Keypad4 = 0x56,
	kVK_ANSI_Keypad5 = 0x57,
	kVK_ANSI_Keypad6 = 0x58,
	kVK_ANSI_Keypad7 = 0x59,
	kVK_ANSI_Keypad8 = 0x5B,
	kVK_ANSI_Keypad9 = 0x5C
};

/*
 * keycodes for keys that are independent of keyboard layout
 */
enum e_mac_virtual_keycode_alternative
{
	kVK_Return = 0x24,
	kVK_Tab = 0x30,
	kVK_Space = 0x31,
	kVK_Delete = 0x33,
	kVK_Escape = 0x35,
	kVK_Command = 0x37,
	kVK_Shift = 0x38,
	kVK_CapsLock = 0x39,
	kVK_Option = 0x3A,
	kVK_Control = 0x3B,
	kVK_RightShift = 0x3C,
	kVK_RightOption = 0x3D,
	kVK_RightControl = 0x3E,
	kVK_Function = 0x3F,
	kVK_F17 = 0x40,
	kVK_VolumeUp = 0x48,
	kVK_VolumeDown = 0x49,
	kVK_Mute = 0x4A,
	kVK_F18 = 0x4F,
	kVK_F19 = 0x50,
	kVK_F20 = 0x5A,
	kVK_F5 = 0x60,
	kVK_F6 = 0x61,
	kVK_F7 = 0x62,
	kVK_F3 = 0x63,
	kVK_F8 = 0x64,
	kVK_F9 = 0x65,
	kVK_F11 = 0x67,
	kVK_F13 = 0x69,
	kVK_F16 = 0x6A,
	kVK_F14 = 0x6B,
	kVK_F10 = 0x6D,
	kVK_F12 = 0x6F,
	kVK_F15 = 0x71,
	kVK_Help = 0x72,
	kVK_Home = 0x73,
	kVK_PageUp = 0x74,
	kVK_ForwardDelete = 0x75,
	kVK_F4 = 0x76,
	kVK_End = 0x77,
	kVK_F2 = 0x78,
	kVK_PageDown = 0x79,
	kVK_F1 = 0x7A,
	kVK_LeftArrow = 0x7B,
	kVK_RightArrow = 0x7C,
	kVK_DownArrow = 0x7D,
	kVK_UpArrow = 0x7E
};

/*
 * Reference: https://gitlab.freedesktop.org/xorg/proto/xorgproto
 * /-/blob/master/include/X11/X.h
 */
enum e_mlx_input_event_mask
{
	NoEventMask = 0,
	KeyPressMask = 1 << 0,
	KeyReleaseMask = 1 << 1,
	ButtonPressMask = 1 << 2,
	ButtonReleaseMask = 1 << 3,
	EnterWindowMask = 1 << 4,
	LeaveWindowMask = 1 << 5,
	PointerMotionMask = 1 << 6,
	PointerMotionHintMask = 1 << 7,
	Button1MotionMask = 1 << 8,
	Button2MotionMask = 1 << 9,
	Button3MotionMask = 1 << 10,
	Button4MotionMask = 1 << 11,
	Button5MotionMask = 1 << 12,
	ButtonMotionMask = 1 << 13,
	KeymapStateMask = 1 << 14,
	ExposureMask = 1 << 15,
	VisibilityChangeMask = 1 << 16,
	StructureNotifyMask = 1 << 17,
	ResizeRedirectMask = 1 << 18,
	SubstructureNotifyMask = 1 << 19,
	SubstructureRedirectMask = 1 << 20,
	FocusChangeMask = 1 << 21,
	PropertyChangeMask = 1 << 22,
	ColormapChangeMask = 1 << 23,
	OwnerGrabButtonMask = 1 << 24
};

/*
 * Reference: https://gitlab.freedesktop.org/xorg/proto/xorgproto
 * /-/blob/master/include/X11/X.h
 */
enum e_mlx_event_type
{
	KeyPress = 2,
	KeyRelease = 3,
	ButtonPress = 4,
	ButtonRelease = 5,
	MotionNotify = 6,
	EnterNotify = 7,
	LeaveNotify = 8,
	FocusIn = 9,
	FocusOut = 10,
	KeymapNotify = 11,
	Expose = 12,
	GraphicsExpose = 13,
	NoExpose = 14,
	VisibilityNotify = 15,
	CreateNotify = 16,
	DestroyNotify = 17,
	UnmapNotify = 18,
	MapNotify = 19,
	MapRequest = 20,
	ReparentNotify = 21,
	ConfigureNotify = 22,
	ConfigureRequest = 23,
	GravityNotify = 24,
	ResizeRequest = 25,
	CirculateNotify = 26,
	CirculateRequest = 27,
	PropertyNotify = 28,
	SelectionClear = 29,
	SelectionRequest = 30,
	SelectionNotify = 31,
	ColormapNotify = 32,
	ClientMessage = 33,
	MappingNotify = 34,
	GenericEvent = 35,
	LASTEvent = 36
};

/*
 * Reference: mlx_window.swift#get_mouse_button
 */
enum e_mlx_mouse_button
{
	MLX_MB_UNKNOWN,
	MLX_MB_LEFT,
	MLX_MB_RIGHT,
	MLX_MB_OTHER,
	MLX_MB_WHEEL_DOWN,
	MLX_MB_WHEEL_UP,
	MLX_MB_WHEEL_RIGHT,
	MLX_MB_WHEEL_LEFT
};

/*
 * Reference: mlx_window.swift#flagsChanged
 *
 * DO NOT USE VALUES FOLLOWING BELOW
 *   MLX_MOD_UNKNOWN = 8,
 *   MLX_MOD_RCONTROL = 13,
 *   MLX_MOD_CAPSLOCK = 16,
 *   MLX_MOD_FUNCTION = 23
 *
 * Initially (MLX_MOD_UNKNOWN) is returned unconditionally.
 * So after (NO_MLX_MOD_KEY), using as different meaning.
 */
enum e_mlx_modifiers
{
	MLX_MOD_LCONTROL,
	MLX_MOD_LSHIFT,
	MLX_MOD_RSHIFT,
	MLX_MOD_LCMD,
	MLX_MOD_RCMD,
	MLX_MOD_LOPTION,
	MLX_MOD_ROPTION,
	NO_MLX_MOD_KEY,
	MLX_MOD_MOUSE_LEFT,
	MLX_MOD_MOUSE_RIGHT,
	MLX_MOD_MOUSE_OTHER,
	MLX_NO_MOD
};

#endif
