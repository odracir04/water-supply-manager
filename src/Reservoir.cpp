#include "Reservoir.h"

Reservoir::Reservoir( std::string n, std::string m, unsigned int i, std::string c, unsigned int max)
: Vertex(c), municipality(m), id(i), maxDelivery(max) {}
