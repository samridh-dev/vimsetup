#ifndef VS_CP_H
#define VS_CP_H

#define VS_CP_BUFSIZE (32 * 1024)

void vs_cp(const char* const src, 
           const char* const dst);

void vs_cpd(const char* const src, 
           const char* const dst);

void vs_cpr(const char* const src,
           const char* const dst);

#endif
