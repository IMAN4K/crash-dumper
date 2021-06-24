#include "CrashReporter/CrashReporter.h"

#include <linux/handler/exception_handler.h>

namespace CrashReporter {

namespace breakpad = google_breakpad;
using breakpad::MinidumpDescriptor;
using breakpad::ExceptionHandler;

static bool MiniDumpCallBack(const MinidumpDescriptor&,
                             void*,
                             const mozilla::phc::AddrInfo*,
                             bool success) {
    return success;
}

static breakpad::ExceptionHandler* handler = nullptr;

void init(const std::string& dumpPath) {
    if (nullptr == handler)
        handler = new breakpad::ExceptionHandler(MinidumpDescriptor(dumpPath), nullptr, MiniDumpCallBack, nullptr, true, -1);
}
} // namespace CrashReporter
