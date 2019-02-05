#ifndef RK_GLOBAL_H
#define RK_GLOBAL_H

#include <memory>
#include <string>

#define RK_UNUSED(expr) (void)expr

#define RK_PRIVATE_IMPL(Class, Name) \
  class Class; \
  std::unique_ptr<Class> name;

#endif // RK_GLOBAL_H
