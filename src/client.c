#include "log4c.h"
#include "test.h"

//Set overall log level
int log4c_level = LOG4C_ALL;

int main() {
  LOG(LOG4C_DEBUG, "You can also add placeholder like this [%d]", 3);
  test();
  LOG_ERROR("This is example");
  return 0;
}
