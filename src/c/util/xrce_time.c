#include <uxr/client/util/xrce_time.h>
#include <time.h>

#ifdef WIN32
#include <Windows.h>
#elif defined(PLATFORM_NAME_BAREMETAL)
#include <baremetal/include/baremetal_time.h>
#endif
//==================================================================
//                             PUBLIC
//==================================================================
int64_t uxr_millis(void)
{
#if defined(PLATFORM_NAME_BAREMETAL)
    return baremetal_millis();
#else
    return uxr_nanos() / 1000000;
#endif
}

int64_t uxr_nanos(void)
{
#ifdef WIN32
    SYSTEMTIME epoch_tm = {1970, 1, 4, 1, 0, 0, 0, 0};
    FILETIME epoch_ft;
    SystemTimeToFileTime(&epoch_tm, &epoch_ft);
    uint64_t epoch_time = (((uint64_t) epoch_ft.dwHighDateTime) << 32) + epoch_ft.dwLowDateTime;

    SYSTEMTIME tm;
    FILETIME ft;
    GetSystemTime(&tm);
    SystemTimeToFileTime(&tm, &ft);
    uint64_t current_time = (((uint64_t) ft.dwHighDateTime) << 32) + ft.dwLowDateTime;

    return (current_time - epoch_time) * 100;
#elif defined(PLATFORM_NAME_BAREMETAL)
    return baremetal_nanos();
#else
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return (((int64_t)ts.tv_sec) * 1000000000) + ts.tv_nsec;
#endif
}
