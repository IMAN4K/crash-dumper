#include "CrashReporter/CrashReporter.h"

#include <third_party/lss/linux_syscall_support.h>
#include <linux/handler/exception_handler.h>

namespace nonstd {
static void TerminateHandler() {
    ::printf("Unhandled exception!");
}
} // namespace nonstd

namespace CrashReporter {

namespace breakpad = google_breakpad;
using breakpad::MinidumpDescriptor;
using breakpad::ExceptionHandler;
using namespace mozilla::phc;

inline auto make_result(Result::first_type first, const Result::second_type& second = Result::second_type {}) {
    return Result(first, second);
}

template<typename T>
inline auto IsSet(const T* arg) {
    return nullptr != arg;
}

static bool mkPath(const std::string& input) {
    return true;
}

static bool MiniDumpCallBack(const MinidumpDescriptor&, void*, const AddrInfo*, bool succeeded) {
    //    time_t crashTime;
    //    struct kernel_timeval tv;
    //    ::sys_gettimeofday(&tv, nullptr);
    //    crashTime = tv.tv_sec;
    return succeeded;
}

static breakpad::ExceptionHandler* handler = nullptr;

Result init(const std::string& dumpPath) {
    Result res;

    if (mkPath(dumpPath)) {
        if (IsSet(handler)) {
            res = make_result(false, "Exception Handler is already initialized!");
        } else {
            // all relevant syscalls(malloc, dlopen etc.) must take place
            // here, that is, outside of exception handling routine

            MinidumpDescriptor descriptor(dumpPath);
            handler = new breakpad::ExceptionHandler(descriptor, nullptr, MiniDumpCallBack, nullptr, true, -1);

            if (!IsSet(handler)) {
                res = make_result(false, "Exception Handler allocation failed!");
            } else {
                std::set_terminate(nonstd::TerminateHandler);
                res = make_result(true);
            }
        }
    }

    return res;
}
} // namespace CrashReporter
