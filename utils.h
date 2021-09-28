#include <cstddef>
#include <functional>

namespace utils {

void ExecuteInMain(std::function<void()> function);
double TimeIt(std::function<void()> function);
std::pair<size_t, size_t> GetProcessInfo();

}  // namespace utils