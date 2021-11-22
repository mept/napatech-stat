#include </mnt/1/1/include/prometheus/registry.h>
#include </mnt/1/1/include/prometheus/counter.h>
#include </mnt/1/1/include/prometheus/gauge.h>
#include </mnt/1/1/include/prometheus/save_to_file.h>
#include </mnt/1/1/include/prometheus/gateway.h>
#include "/mnt/1/1/napatech/nt.h"

#include <array>
#include <chrono>
#include <cstdlib>
#include <memory>
#include <string>
#include <thread>
#include <iostream>

#if defined(__linux__) || defined(__FreeBSD__)
#include <unistd.h> // sleep()
#elif defined(WIN32) || defined(WIN64)
#include <winsock2.h> // Sleep()
#endif

using namespace prometheus;

static std::string GetHostName() {
  char hostname[1024];

  if (::gethostname(hostname, sizeof(hostname))) {
    return {};
  }
  return hostname;
}

std::shared_ptr<prometheus::Registry> addMetric(std::shared_ptr<prometheus::Registry> registry,
                                                prometheus::CustomFamily<prometheus::Gauge<double>>& gauge_family,
                                                const char* label_key,
                                                const char* label_value,
                                                unsigned long long metric_value) {
    auto& metric_counter = gauge_family.Add({{label_key, label_value}});
    metric_counter.Set(metric_value);
    return registry;
}

std::shared_ptr<prometheus::Registry> addMetric(std::shared_ptr<prometheus::Registry> registry,
                                                prometheus::CustomFamily<prometheus::Gauge<double>>& gauge_family,
                                                const char* label_key1,
                                                const char* label_value1,
                                                const char* label_key2,
                                                const char* label_value2,
                                                unsigned long long metric_value) {
    // std::cout << "add metric with keys: " << label_key1 << " = " << label_value1 << ", " << label_key2 << " = " << label_value2 << ", value = " << metric_value << std::endl;
    auto& metric_counter = gauge_family.Add({{label_key1, label_value1}, {label_key2, label_value2}});
    metric_counter.Set(metric_value);
    return registry;
}

int main(void)
{
    NtStatStream_t hStatStream;       // Statistics stream handle
    NtStatistics_t hStat;             // Stat handle.
    char errorBuffer[NT_ERRBUF_SIZE]; // Error buffer
    int status;                       // Status variable
    unsigned i;
    // Initialize the NTAPI library and thereby check if NTAPI_VERSION can be used together with this library
    if ((status = NT_Init(NTAPI_VERSION)) != NT_SUCCESS)
    {
        // Get the status code as text
        NT_ExplainError(status, errorBuffer, sizeof(errorBuffer));
        fprintf(stderr, "NT_Init() failed: %s\n", errorBuffer);
        return -1;
    }
    // Open the stat stream
    if ((status = NT_StatOpen(&hStatStream, "PrometheusStat")) != NT_SUCCESS)
    {
        // Get the status code as text
        NT_ExplainError(status, errorBuffer, sizeof(errorBuffer));
        fprintf(stderr, "NT_StatOpen() failed: %s\n", errorBuffer);
        return -1;
    }
    // Read the statistics counters to clear the statistics
    // This is an optional step. If omitted, the adapter will show statistics form the start of ntservice.
    hStat.cmd = NT_STATISTICS_READ_CMD_QUERY_V3;
    hStat.u.query_v3.poll = 0;  // Wait for a new set
    hStat.u.query_v3.clear = 1; // Clear statistics
    if ((status = NT_StatRead(hStatStream, &hStat)) != NT_SUCCESS)
    {
        // Get the status code as text
        NT_ExplainError(status, errorBuffer, sizeof(errorBuffer));
        fprintf(stderr, "NT_StatRead() failed: %s\n", errorBuffer);
        return -1;
    }
    printf("--------------------------------------------------------------------------------\n");
    for (;;)
    {
        hStat.cmd = NT_STATISTICS_READ_CMD_QUERY_V3;
        hStat.u.query_v3.poll = 1;  // The the current counters
        hStat.u.query_v3.clear = 0; // Do not clear statistics
        if ((status = NT_StatRead(hStatStream, &hStat)) != NT_SUCCESS)
        {
            // Get the status code as text
            NT_ExplainError(status, errorBuffer, sizeof(errorBuffer));
            fprintf(stderr, "NT_StatRead() failed: %s\n", errorBuffer);
            return -1;
        }
        // Print the RMON1 pkts counters
        if (hStat.u.query_v3.data.port.aPorts[0].rx.valid.RMON1)
        {
            // create a push gateway
            const auto labels = Gateway::GetInstanceLabel(GetHostName());
            Gateway gateway{"yar-input-02", "9091", "napatech_stat", labels};

            auto registry = std::make_shared<Registry>();

            auto& gauge_family = BuildGauge()
                                .Name("napatech_stat")
                                .Help("Napatech statistics")
                                .Register(*registry);

            registry = addMetric(registry, gauge_family, "port", "0", "pkts_count", "total", hStat.u.query_v3.data.port.aPorts[0].rx.RMON1.pkts);
            registry = addMetric(registry, gauge_family, "port", "0", "pkts_count", "drops", hStat.u.query_v3.data.port.aPorts[0].rx.RMON1.dropEvents);
            registry = addMetric(registry, gauge_family, "port", "0", "pkts_count", "multicast", hStat.u.query_v3.data.port.aPorts[0].rx.RMON1.multicastPkts);
            registry = addMetric(registry, gauge_family, "port", "0", "pkts_count", "vlan", hStat.u.query_v3.data.port.aPorts[0].rx.decode.pktsVlan);

            registry = addMetric(registry, gauge_family, "port", "1", "pkts_count", "total", hStat.u.query_v3.data.port.aPorts[1].rx.RMON1.pkts);
            registry = addMetric(registry, gauge_family, "port", "1", "pkts_count", "drops", hStat.u.query_v3.data.port.aPorts[1].rx.RMON1.dropEvents);
            registry = addMetric(registry, gauge_family, "port", "1", "pkts_count", "multicast", hStat.u.query_v3.data.port.aPorts[1].rx.RMON1.multicastPkts);
            registry = addMetric(registry, gauge_family, "port", "1", "pkts_count", "vlan", hStat.u.query_v3.data.port.aPorts[1].rx.decode.pktsVlan);

            for (int i = 0; i < 32; i++) {
                registry = addMetric(registry, gauge_family, "stream_id", std::to_string(i).c_str(), "stream_pkts_count", "flush", hStat.u.query_v3.data.stream.streamid[i].flush.pkts);
                registry = addMetric(registry, gauge_family, "stream_id", std::to_string(i).c_str(), "stream_pkts_count", "forward", hStat.u.query_v3.data.stream.streamid[i].forward.pkts);
                registry = addMetric(registry, gauge_family, "stream_id", std::to_string(i).c_str(), "stream_pkts_count", "drop", hStat.u.query_v3.data.stream.streamid[i].drop.pkts);
            }

            // ask the pusher to push the metrics to the pushgateway
            gateway.RegisterCollectable(registry);

            // push metrics
            auto returnCode = gateway.Push();
            std::cout << "returnCode is " << returnCode << std::endl;
        }
        else
        {
            printf("Port0 doesn't support RMON1 RX counters.\n");
        }
        printf("--------------------------------------------------------------------------------\n");
        // Sleep 10 sec
        #if defined(__linux__) || defined(__FreeBSD__)
                sleep(10);
        #elif defined(WIN32) || defined(WIN64)
                Sleep(10000); // sleep 1000 milliseconds = 1 second
        #endif
    }
    // Close the stat stream
    if ((status = NT_StatClose(hStatStream)) != NT_SUCCESS)
    {
        // Get the status code as text
        NT_ExplainError(status, errorBuffer, sizeof(errorBuffer));
        fprintf(stderr, "NT_StatClose() failed: %s\n", errorBuffer);
        return -1;
    }
    // Close down the NTAPI library
    NT_Done();
    printf("Done.\n");
    return 0;
}