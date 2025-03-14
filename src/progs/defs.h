/*
Copyright (C) 1996-1997 Id Software, Inc.
Copyright (C) 2025 erysdren (it/its)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, see https://www.gnu.org/licenses/
*/

#ifndef _DEFS_H_
#define _DEFS_H_
#ifdef __cplusplus
extern "C" {
#endif

/* clang required */
#if !defined(__clang__)
#error Clang is required
#endif

/* C23 required */
#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 202311L
#error C23 or higher is required
#endif

/* wasm32 required */
#if defined(__wasm__) && !defined(__wasm32__)
#error only the wasm32 target is supported
#endif

/* standard includes */
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

/* include engine progdefs */
#include "../progdefs.h"

/* import/export helper macros */
#define WASM_EXPORT(n) __attribute__((export_name(#n), used, visibility("default"))) n
#define WASM_IMPORT(n) __attribute__((import_module("env"), import_name(#n))) n

/* main.c */
extern globalvars_t globals;

/* client.c */
void PlayerPreThink(void);
void PlayerPostThink(void);
void ClientKill(void);
void ClientConnect(void);
void PutClientInServer(void);
void ClientDisconnect(void);

/* world.c */
void StartFrame(void);

#ifdef __cplusplus
}
#endif
#endif /* _DEFS_H_ */
