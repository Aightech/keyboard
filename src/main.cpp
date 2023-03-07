#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "ckeyboard.hpp"

int main(int argc, char **argv)
{
  cKeyboard keyboard;
  try
    {
      keyboard.connect();
    }
  catch (const std::string& err)
    {
      std::cerr << err.c_str() << std::endl;
    }
   return 0;
}
