#ifndef _MACROS_H
#define _MACROS_H

#ifndef max
    #define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
    #define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#define REPEAT2(x) x; x
#define REPEAT4(x) REPEAT2(REPEAT2(x))
#define REPEAT16(x) REPEAT4(REPEAT4(x))
#define REPEAT32(x) REPEAT2(REPEAT16(x))
#define REPEAT64(x) REPEAT2(REPEAT16(x))
#define REPEAT98(x) REPEAT64(x); REPEAT32(x); REPEAT2(x)

#endif
