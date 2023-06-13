#include <wups.h>
#include <whb/log.h>
#include <whb/log_module.h>
#include <whb/log_cafe.h>
#include <whb/log_udp.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

WUPS_PLUGIN_NAME("nn_olv_logger");
WUPS_PLUGIN_DESCRIPTION("Allows the Miiverse logs to be read even if the function is stubbed.");
WUPS_PLUGIN_VERSION("v1.0");
WUPS_PLUGIN_AUTHOR("Rambo6Glaz");
WUPS_PLUGIN_LICENSE("MIT");

ON_APPLICATION_START()
{
    // Init logging
    if (!WHBLogModuleInit())
    {
        WHBLogCafeInit();
        WHBLogUdpInit();
    }
}

DECL_FUNCTION(void, Print__Q3_2nn3olv6ReportFQ3_2nn3olv10ReportTypePCce, int, const char *format, ...)
{

    va_list args;
    va_start(args, format);

    char buffer[1024]; // Assuming a maximum length of 256 characters
    vsnprintf(buffer, sizeof(buffer), format, args);

    int len = strlen(buffer);
    if (buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';

    va_end(args);

    WHBLogPrintf("[OLV_REPORT] %s", buffer);
}

WUPS_MUST_REPLACE(Print__Q3_2nn3olv6ReportFQ3_2nn3olv10ReportTypePCce, WUPS_LOADER_LIBRARY_NN_OLV, Print__Q3_2nn3olv6ReportFQ3_2nn3olv10ReportTypePCce);