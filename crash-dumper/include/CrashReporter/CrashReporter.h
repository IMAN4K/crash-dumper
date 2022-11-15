/* Copyright (c) 2022 Iman Ahmadvand
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CRASH_REPORTER_H
#define CRASH_REPORTER_H

#include <string>

namespace CrashReporter {

struct Result final : public std::pair<bool, std::string> {
    using std::pair<bool, std::string>::pair;

    auto isOk() const {
        return first;
    }

    auto getDetail() const {
        return second;
    }
};

struct Options
{
    std::string dumpPath;
};

Result init(const std::string& dumpPath);

} // namespace CrashReporter

#endif // CRASH_REPORTER_H
