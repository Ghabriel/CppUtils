/* created by Ghabriel Nunes <ghabriel.nunes@gmail.com> [2017] */
#include <vector>
#include "debug.hpp"

class Redirect : public dbg::ArbitraryStream {
    Redirect& operator<<(const std::string& message) {
        std::cout << "[LOG] " << message;
        return *this;
    }
};

int main(int, char**) {
    Redirect redirector;
    DEBUG_REDIRECT(redirector);

    char k = 'A';
    TRACE_L("label", k);
    ECHO("Test message");
}
