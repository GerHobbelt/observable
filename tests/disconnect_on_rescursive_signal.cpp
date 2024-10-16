// Observable Library
// Copyright (c) 2016 David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#include "obs/signal.h"

#if defined(BUILD_MONOLITHIC)
#define main observable_disconnect_on_recursive_signal_test_main
#endif

extern "C"
int main(void) {
  obs::signal<void(int)> s;     // We have to use "obs::" because ambiguous name from sys/signal.h on macOS?
  obs::connection c = s.connect(
    [&](int i){
      if (i > 0)
        s(i-1);
      else
        c.disconnect();
    });
  s(5);
	return 0;
}
