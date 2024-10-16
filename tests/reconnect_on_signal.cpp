// Observable Library
// Copyright (c) 2016 David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#include "obs/signal.h"
#include "test.h"

obs::signal<void()> sig;
obs::scoped_connection conn;

void func() {
  conn = sig.connect(func);

  // This second connection produced an infinite loop in an old
  // implementation of iterators where we skipped removed nodes in the
  // same operator*(). So then the iterator::operator!=() was always
  // true.
  conn = sig.connect(func);
}

#if defined(BUILD_MONOLITHIC)
#define main observable_reconnect_on_signal_test_main
#endif

extern "C"
int main(void) {
  conn = sig.connect(func);
  sig();
	return 0;
}
