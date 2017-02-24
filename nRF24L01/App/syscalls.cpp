#include <reent.h>

#include <SEGGER_RTT.h>

extern "C" int _write(int f, char *bytes, int numBytes) {
    (void)(f);

    SEGGER_RTT_Write(0, bytes, numBytes);

    return (numBytes);
}

extern "C" int _write_r(struct _reent *r, int f, const void *bytes, size_t numBytes) {
    (void)(r);
    (void)(f);

    SEGGER_RTT_Write(0, bytes, numBytes);

    return (numBytes);
}
