
#include "metrics.h"

#include <memory>

namespace control {
  namespace metrics {

    using namespace prometheus;

    std::shared_ptr<Registry> registry_ptr = std::make_shared<Registry>();
    std::string identifier = "default";
    Registry& registry = *registry_ptr;
    saver_t saver (registry_ptr, std::chrono::seconds(5), std::string("./metrics.prom"));

  }
}