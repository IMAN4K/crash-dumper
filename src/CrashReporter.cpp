#include "CrashReporter/CrashReporter.h"

#include <linux/handler/exception_handler.h>
#include <minidump_file_writer.h>

namespace CrashReporter {

void init(const std::string& path) {
    (void)path;

    google_breakpad::MinidumpDescriptor d;
    d.UpdatePath();

    google_breakpad::MinidumpFileWriter writer;
    writer.Close();
}

} // namespace CrashReporter
