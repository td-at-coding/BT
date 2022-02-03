#include <ostream>


namespace mstate
{
    enum mstate : int;

    mstate parse_character(char character);

    std::ostream& operator <<(std::ostream& out, mstate ms);

}

