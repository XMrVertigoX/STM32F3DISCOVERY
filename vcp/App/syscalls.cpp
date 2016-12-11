#include <usbd_cdc_if.h>

extern "C" int _write(int f, char *bytes, int numBytes) {
    CDC_Transmit_FS((uint8_t *)bytes, numBytes);
    return (numBytes);
}

extern "C" int _write_r(struct _reent *r, int f, const void *bytes,
                        size_t numBytes) {
    CDC_Transmit_FS((uint8_t *)bytes, numBytes);
    return (numBytes);
}
