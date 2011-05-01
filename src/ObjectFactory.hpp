#pragma once

#include <vector>

#include "Tree/Errorhandling.hpp"
#include "PathObject.hpp"

int NumObjects();
PathObjPtr GetObject( size_t num ) throw( Error::resource_not_found );

