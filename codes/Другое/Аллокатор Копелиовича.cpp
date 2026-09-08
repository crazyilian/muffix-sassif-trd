// insert code BEFORE includes
#include <cassert>
using namespace std;
const size_t MAX_MEM = 1e8; // ~100mb
// set ALIGN=1 if care about ML, but not UB
const size_t ALIGN = __STDCPP_DEFAULT_NEW_ALIGNMENT__;
alignas(ALIGN) unsigned char mem[MAX_MEM];
size_t mpos = 0;

void *operator new(size_t n) {
  n = ((n ? n : 1) + ALIGN - 1) & ~(ALIGN - 1);
  mpos += n;
//  assert(mpos <= MAX_MEM);
  return (void *)(mem + mpos - n);
}
void operator delete(void *) noexcept {}
void operator delete(void *, size_t) noexcept {}
