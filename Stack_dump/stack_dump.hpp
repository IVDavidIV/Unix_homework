#include <iostream>
#include <vector>
#include <execinfo.h>
#include <cstdlib>
#include <cxxabi.h>

void stack_dump(int depth, std::ostream& out) {
    std::vector<void*> buffer(depth + 2); 
    int nptrs = backtrace(buffer.data(), buffer.size());

    if (nptrs <= 2) { 
        out << "Stack is empty \n";
        return;
    }

    char** symbols = backtrace_symbols(buffer.data(), nptrs);
    if (!symbols) {
        out << "Failed \n";
        return;
    }

    for (int i = 1; i < std::min(nptrs - 1, depth + 1); ++i) {
        char* symbol = symbols[i];
        char* demangled = nullptr;
        char* begin = nullptr;
        char* end = nullptr;

        for (char* p = symbol; *p; ++p) {
            if (*p == '(') {
                begin = p + 1;
            } else if (*p == '+' && begin) {
                end = p;
                break;
            }
        }

        if (begin && end) {
            *end = '\0';
            int status = 0;
            demangled = abi::__cxa_demangle(begin, nullptr, nullptr, &status);
        }

        if (demangled) {
            out << i << ": " << demangled << '\n';
        } else {
            out << i << ": " << symbol << '\n';
        }

        free(demangled);
    }

    free(symbols);
}
