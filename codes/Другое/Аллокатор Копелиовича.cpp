// Код вставить до инклюдов

#include <cassert>

const int MAX_MEM = 1e8; // ~100mb
int mpos = 0;
char mem[MAX_MEM];

inline void *operator new(std::size_t n) {
  assert((mpos += n) <= MAX_MEM);
  return (void *)(mem + mpos - n);
}

inline void operator delete(void *) noexcept {} // must have!
inline void operator delete(void *, std::size_t) noexcept {} // fix!!
