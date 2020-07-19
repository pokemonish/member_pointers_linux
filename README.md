# member_pointers_linux

Program shows the internals of the member pointers in C++.
Works on Linux

Compile like this: `g++ member_pointers_linux.cpp && ./a.out`

Output sample:
```
Checking A::a: {0x55e6326ed460, (nil)} for 0x7ffff672131f
  this_adjust: 0
  is_virtual: 0
  function_pointer: 0x55e6326ed460
  call output: A::a
Checking A::b: {0x55e6326ed470, (nil)} for 0x7ffff672131f
  this_adjust: 0
  is_virtual: 0
  function_pointer: 0x55e6326ed470
  call output: A::b

Checking B::a: {0x1, (nil)} for 0x7ffff6721320
  this_adjust: 0
  is_virtual: 1
  vtable_position: 0
  function_pointer: 0x55e6326ed480
  call output: B::a
Checking B::b: {0x9, (nil)} for 0x7ffff6721320
  this_adjust: 0
  is_virtual: 1
  vtable_position: 8
  function_pointer: 0x55e6326ed490
  call output: B::b
Checking B::c: {0x11, (nil)} for 0x7ffff6721320
  this_adjust: 0
  is_virtual: 1
  vtable_position: 16
  function_pointer: 0x55e6326ed4a0
  call output: B::c

Checking C::a: {0x55e6326ed4b0, 0x7b} for 0x7ffff6721330
  this_adjust: 123
  is_virtual: 0
  function_pointer: 0x55e6326ed4b0
  call output: C2::a
Checking C2::a: {0x55e6326ed4b0, 0x7b} for 0x7ffff6721330
  this_adjust: 123
  is_virtual: 0
  function_pointer: 0x55e6326ed4b0
  call output: C2::a
Checking C::b: {0x55e6326ed4c0, 0x7b} for 0x7ffff6721330
  this_adjust: 123
  is_virtual: 0
  function_pointer: 0x55e6326ed4c0
  call output: C2::b
Checking C2::b: {0x55e6326ed4c0, 0x7b} for 0x7ffff6721330
  this_adjust: 123
  is_virtual: 0
  function_pointer: 0x55e6326ed4c0
  call output: C2::b
```
