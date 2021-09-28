#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "data.h"

Data _data;

Data current_data() {
  return _data;
}
