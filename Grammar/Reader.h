
#include <ostream>
#include <vector>
#include <utility>
#include <string>
#include "cstate.h"
#include "mstate.h"

struct Reader;


Reader& create_reader();

void delete_reader(Reader& reader);

std::ostream& operator<<(std::ostream& out, const Reader& reader);

std::vector<std::pair<std::string,cstate::cstate>> parse_program( Reader& reader,  std::string program );
