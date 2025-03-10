
#ifndef _DEFS_H_
#define _DEFS_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#define PR_EXPORT(n) __attribute__((export_name(#n), used, visibility("default"))) n
#define PR_IMPORT(n) __attribute__((import_module("env"), import_name(#n))) n

void PR_EXPORT(StartFrame)(void);
void PR_EXPORT(PlayerPreThink)(void);
void PR_EXPORT(PlayerPostThink)(void);
void PR_EXPORT(ClientKill)(void);
void PR_EXPORT(ClientConnect)(void);
void PR_EXPORT(PutClientInServer)(void);
void PR_EXPORT(ClientDisconnect)(void);
void PR_EXPORT(SetNewParms)(void);
void PR_EXPORT(SetChangeParms)(void);

#ifdef __cplusplus
}
#endif
#endif /* _DEFS_H_ */
