#include <string>
#include <iostream>
#include <google_breakpad/processor/basic_source_line_resolver.h>
#include <google_breakpad/processor/minidump.h>
#include <google_breakpad/processor/minidump_processor.h>
#include <google_breakpad/processor/process_state.h>
#include <google_breakpad/processor/call_stack.h>
#include <google_breakpad/processor/stack_frame.h>
#include <processor/simple_symbol_supplier.h>

namespace breakpad = google_breakpad;
using namespace breakpad;

static string ResultToString(ProcessResult result) {
    switch (result) {
        case google_breakpad::PROCESS_OK:
            return "OK";
        case google_breakpad::PROCESS_ERROR_MINIDUMP_NOT_FOUND:
            return "ERROR_MINIDUMP_NOT_FOUND";
        case google_breakpad::PROCESS_ERROR_NO_MINIDUMP_HEADER:
            return "ERROR_NO_MINIDUMP_HEADER";
        case google_breakpad::PROCESS_ERROR_NO_THREAD_LIST:
            return "ERROR_NO_THREAD_LIST";
        case google_breakpad::PROCESS_ERROR_GETTING_THREAD:
            return "ERROR_GETTING_THREAD";
        case google_breakpad::PROCESS_ERROR_GETTING_THREAD_ID:
            return "ERROR_GETTING_THREAD_ID";
        case google_breakpad::PROCESS_ERROR_DUPLICATE_REQUESTING_THREADS:
            return "ERROR_DUPLICATE_REQUESTING_THREADS";
        case google_breakpad::PROCESS_SYMBOL_SUPPLIER_INTERRUPTED:
            return "SYMBOL_SUPPLIER_INTERRUPTED";
    }

    return std::string();
}

static bool Process(const int32_t argc, char** argv) {
    (void)argv;
    return argc > 2;
}

[[noreturn]] static void Failure(const std::string& detail) {
    std::cerr << detail << std::endl;
    ::exit(EXIT_FAILURE);
}

int32_t main(int32_t argc, char** argv) {
    if (!Process(argc, argv)) {
        Failure("invalid arguments!");
    }

    const std::string dumpPath(std::string(*(argv + 1)));
    const std::string symbolPath(std::string(*(argv + 2)));

    Minidump miniDump(dumpPath);
    if (!miniDump.Read()) {
        Failure(std::string("failed to read minidump: ") + dumpPath);
    }

    BasicSourceLineResolver resolver;
    SimpleSymbolSupplier supplier(symbolPath);
    MinidumpProcessor processor(&supplier, &resolver);
    ProcessState state;
    const auto res = processor.Process(&miniDump, &state);
    std::cerr << ResultToString(res) << std::endl;
    //    state.threads()->at(0)->frames()->at(0)->source_line;

    ::exit(EXIT_SUCCESS);
}
