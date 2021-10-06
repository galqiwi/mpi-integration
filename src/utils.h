#include <cstddef>
#include <functional>

namespace utils {

void ExecuteInMain(const std::function<void()>& function);
double TimeIt(const std::function<void()>& function);
std::pair<size_t, size_t> GetProcessInfo();

}  // namespace utils