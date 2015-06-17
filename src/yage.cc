#include "yage.h"
#include "window/window.h"

namespace yage {

int argc;
char **argv;

}  // namespace yage

extern "C" int yage_lib_init(int argc, char **argv, int (*yage_main)(int, char**))
{
  yage::argc = argc;
  yage::argv = argv;
  return yage::window::Window::init(yage_main);
}
