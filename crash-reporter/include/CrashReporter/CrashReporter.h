#ifndef CRASH_REPORTER_H
#define CRASH_REPORTER_H

#include <string>

namespace CrashReporter {

struct Result final : public std::pair<bool, std::string> {
    using std::pair<bool, std::string>::pair;

    inline auto isOk() const {
        return first;
    }

    inline auto getDetail() const {
        return second;
    }
};

Result init(const std::string& dumpPath);

} // namespace CrashReporter

#endif // CRASH_REPORTER_H
