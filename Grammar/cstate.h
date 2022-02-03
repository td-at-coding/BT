#include <ostream>

namespace cstate
{
    enum cstate : int;
    std::ostream& operator<<(std::ostream& out, cstate cs);
}


