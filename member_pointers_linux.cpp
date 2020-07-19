#include <cstdio>
#include <cstring>

static_assert(sizeof(size_t) == sizeof(void*), "");
struct Ptr {
  void *a, *b;

  template <typename T>
  Ptr (const T ptr1) {
    static_assert(sizeof(ptr1) == sizeof(*this), "");
    memcpy(this, &ptr1, sizeof(Ptr));
  }
  size_t int_a() {
    return (size_t)this->a;
  }
  size_t int_b() {
    return (size_t)this->b;
  }
  template <typename function_type>
  void explain(void *self) {
    size_t this_adjust = this->int_b();
    printf("  this_adjust: %zu\n", this_adjust);
    bool is_virtual = this->int_a() & 1;
    printf("  is_virtual: %u\n", is_virtual);
    void *adjusted_this = (char*)self + this_adjust;
    
    function_type function_pointer = nullptr;
    if (is_virtual) {
      size_t vtable_position = this->int_a() - 1;
      printf("  vtable_position: %zu\n", vtable_position);
      char *vtable = *(char**)adjusted_this;
      function_pointer = (function_type)(*(void**)(vtable + vtable_position));
    } else {
      function_pointer = (function_type)this->a;
    }
    printf("  function_pointer: %p\n", function_pointer);
    printf("  call output: ");
    function_pointer(adjusted_this);
  }
};

template <typename function_type, typename class_type, typename member_pointer>
void process(const char *text, class_type value, const member_pointer raw_ptr) {
  Ptr ptr(raw_ptr);
  printf("Checking %s: {%p, %p} for %p\n", text, ptr.a, ptr.b, &value);
  ptr.explain<function_type>((void*)&value);
}

int main(int argc, char const *argv[]) {
  typedef void(*common_type)(void*);

  struct A {
    void a() {printf("A::a\n");}
    void b() {printf("A::b\n");}
  };
  process<common_type>("A::a", A(), &A::a);
  process<common_type>("A::b", A(), &A::b);

  printf("\n");

  struct B {
    virtual void a() {printf("B::a\n");}
    virtual void b() {printf("B::b\n");}
    virtual void c() {printf("B::c\n");}
  };
  process<common_type>("B::a", B(), &B::a);
  process<common_type>("B::b", B(), &B::b);
  process<common_type>("B::c", B(), &B::c);

  printf("\n");

  struct C1 {
    char nop[123];
  };
  struct C2 {
    char nop[1];
    void a() {printf("C2::a\n");};
    void b() {printf("C2::b\n");};
  };
  struct C : C1, C2 {};
  process<common_type>("C::a", C(), (void (C::*)())(&C::a));
  process<common_type>("C2::a", C(), (void (C::*)())(&C2::a));
  process<common_type>("C::b", C(), (void (C::*)())(&C::b));
  process<common_type>("C2::b", C(), (void (C::*)())(&C2::b));
}
