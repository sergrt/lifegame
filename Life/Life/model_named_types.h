#pragma once
#include "named_type.h"
////////////////////////////////////////////////////////////////
// Types used by Model and Views
using Row = NamedType<size_t, struct RowType>;
using Column = NamedType<size_t, struct ColumnType>;
