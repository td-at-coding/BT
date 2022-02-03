
#include <ostream>

namespace pattern
{

    enum pattern : int;
    std::ostream& operator << (std::ostream& out, pattern o );

    void print_styles();
    

} // namespace pattern

