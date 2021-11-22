
#pragma once

#include </com.docker.devenvironments.code/include/prometheus/family.h>
#include </com.docker.devenvironments.code/include/prometheus/registry.h>
#include </com.docker.devenvironments.code/include/prometheus/counter.h>
#include </com.docker.devenvironments.code/include/prometheus/gauge.h>

#include </com.docker.devenvironments.code/include/prometheus/registry.h>
#include "/com.docker.devenvironments.code/include/prometheus/text_serializer.h"

#include <thread>
#include <iostream>
#include <memory>
#include <functional>


#pragma once

#include <thread>
#include <chrono>
#include <string>
#include <fstream>
#include <memory>

namespace control {
  namespace metrics {

    constexpr const char* ID_LABLE = "app";

    class saver_t {
      std::chrono::seconds                  period{ 1 };
      std::string                           filename;
      std::unique_ptr<std::thread>          worker_thread;
      std::shared_ptr<prometheus::Registry> registry_ptr{ nullptr };
      bool                                  must_die{ false };

      void thread_ () {
        for (;;) {

          std::this_thread::sleep_for(period);

          std::fstream out_file_stream;
          out_file_stream.open(filename, std::fstream::out | std::fstream::binary);
          if (out_file_stream.is_open()) {
            prometheus::TextSerializer text_serializer;
            text_serializer.Serialize(out_file_stream, registry_ptr->Collect());
            out_file_stream.close();
          }

          if (must_die)
            return;

        }
      }

    public:
      saver_t() = default;

      saver_t( std::shared_ptr<prometheus::Registry>& registry_,
               const std::chrono::seconds& period_,
               const std::string& filename_)
        : period(period_)
        , filename(filename_)
        , registry_ptr(registry_)
      {}

      ~saver_t() {
        stop();
      }

      void init(const std::string& filename_) {
        filename = filename_;
      }

      void start() {
        must_die = false;
        worker_thread = std::make_unique<std::thread>(&saver_t::thread_, this);
      }

      void stop() {
        must_die = true;
        if (worker_thread) worker_thread->join();
      }

    };


    extern prometheus::Registry& registry;
    extern saver_t               saver;
    extern std::string           identifier;



    class counter_family_t;

    class counter_metric_t {

    public:

      using Metric = prometheus::Counter;
      using Family = prometheus::Family<Metric>;

    private:

      Family* family_{ nullptr };
      Metric* metric_{ nullptr };

      friend counter_family_t;
      counter_metric_t(Family* family, Metric& metric)
        : family_(family), metric_(&metric) {}

    public:

      // fake empty metric
      counter_metric_t() = default;

      // make new counter as simple metric without tags and with hidden family included: metric_t metric {"counter_name", "Counter description"}
      counter_metric_t(const std::string& name, const std::string& description)
        : family_(&prometheus::BuildCounter().Name(name).Help(description).Register(registry)), metric_(&family_->Add({})) {}

      void operator++ () { metric_->Increment(); }
      void operator++ (int) { metric_->Increment(); }
      void operator+= (size_t val) { metric_->Increment((double)val); }

      size_t value() const { return (size_t)metric_->Value(); }

    };

    class counter_family_t {

      typename counter_metric_t::Family* family_ { nullptr };

    public:

      counter_family_t(const std::string& name, const std::string& description)
        : family_(&prometheus::BuildCounter().Name(name).Help(description).Register(registry)) {}

      counter_metric_t Add(const std::map<std::string, std::string>& labels) {
        std::map<std::string, std::string> all_lables = labels;
        all_lables.emplace(ID_LABLE, identifier);
        return counter_metric_t (family_, family_->Add(all_lables));
      }

    };

    class gauge_family_t;

    class gauge_metric_t {

    public:

      using Metric = prometheus::Gauge;
      using Family = prometheus::Family<Metric>;

    private:

      Family* family_{ nullptr };
      Metric* metric_{ nullptr };

      friend gauge_family_t;
      gauge_metric_t(Family* family, Metric& metric)
        : family_(family), metric_(&metric) {}

    public:

      // fake empty metric
      gauge_metric_t() = default;

      // make new gauge as simple metric without tags and with hidden family included: metric {"counter_name", "Counter description"}
      gauge_metric_t(const std::string& name, const std::string& description)
        : family_(&prometheus::BuildGauge().Name(name).Help(description).Register(registry)), metric_(&family_->Add({})) {}

      void operator++ () { metric_->Increment(); }
      void operator++ (int) { metric_->Increment(); }
      void operator+= (size_t val) { metric_->Increment((double)val); }

      void operator-- () { metric_->Decrement(); }
      void operator-- (int) { metric_->Decrement(); }
      void operator-= (size_t val) { metric_->Decrement((double)val); }

      void operator= (size_t val) { metric_->Set((double)val); }

      size_t value() const { return (size_t)metric_->Value(); }

    };

    class gauge_family_t {

      typename gauge_metric_t::Family* family_{ nullptr };

    public:

      gauge_family_t(const std::string& name, const std::string& description)
        : family_(&prometheus::BuildGauge().Name(name).Help(description).Register(registry)) {}

      gauge_metric_t Add(const std::map<std::string, std::string>& labels) {
        std::map<std::string, std::string> all_lables = labels;
        all_lables.emplace(ID_LABLE, identifier);
        return gauge_metric_t (family_, family_->Add(all_lables));
      }

    };
  }
}