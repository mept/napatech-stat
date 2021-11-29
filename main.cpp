#include <prometheus/registry.h>
#include <prometheus/counter.h>
#include <prometheus/gauge.h>
#include <prometheus/save_to_file.h>
#include <prometheus/gateway.h>
#include <napatech/nt.h>

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

static std::string GetHostName()
{
    char hostname[1024];

    if (::gethostname(hostname, sizeof(hostname)))
    {
        return {};
    }
    return hostname;
}

void addCounterMetric(std::shared_ptr<prometheus::Registry> registry,
                                                prometheus::CustomFamily<prometheus::Counter<double>> &counter_family,
                                                const char *label_key,
                                                const char *label_value)
{
    auto &metric_counter = counter_family.Add({{label_key, label_value}});
    metric_counter.Increment();
}

void addGaugeMetric(std::shared_ptr<prometheus::Registry> registry,
                                                prometheus::CustomFamily<prometheus::Gauge<double>> &gauge_family,
                                                const char *label_key,
                                                const char *label_value,
                                                unsigned long long metric_value)
{
    auto &metric_counter = gauge_family.Add({{label_key, label_value}});
    metric_counter.Set(metric_value);
}

void addGaugeMetric(std::shared_ptr<prometheus::Registry> registry,
                                                prometheus::CustomFamily<prometheus::Gauge<double>> &gauge_family,
                                                const char *label_key1,
                                                const char *label_value1,
                                                const char *label_key2,
                                                const char *label_value2,
                                                unsigned long long metric_value)
{
    auto &metric_counter = gauge_family.Add({{label_key1, label_value1}, {label_key2, label_value2}});
    metric_counter.Set(metric_value);
}

int main(void)
{
    NtStatStream_t hStatStream;       // Statistics stream handle
    NtStatistics_t hStat;             // Stat handle.
    char errorBuffer[NT_ERRBUF_SIZE]; // Error buffer
    int status;                       // Status variable
    const int NAPATECH_STREAMS_COUNT = 32;
    int successful_pushes = 0;
    int failed_pushes = 0;
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
    printf("--------------------------------start-------------------------------------------\n");

    // create a push gateway
    const auto labels = Gateway::GetInstanceLabel(GetHostName());
    const auto labels_sys = Gateway::GetInstanceLabel(GetHostName());
    Gateway gateway{"yar-input-02", "9091", "napatech_stat", labels};
    Gateway gateway_sys{"yar-input-02", "9091", "napatech_system", labels_sys};

    auto registry = std::make_shared<Registry>();
    auto registry_sys = std::make_shared<Registry>();

    auto &gauge_family = BuildGauge()
                             .Name("napatech_stat")
                             .Help("Napatech statistics")
                             .Register(*registry);

    auto &counter_family = BuildCounter()
                               .Name("napatech_system")
                               .Help("Napatech system statistics")
                               .Register(*registry_sys);

    hStat.cmd = NT_STATISTICS_READ_CMD_QUERY_V3;
    hStat.u.query_v3.poll = 1;  // The the current counters
    hStat.u.query_v3.clear = 0; // Do not clear statistics

    for (;;)
    {
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
            for (int p = 0; p < 2; p++)
            {
                // const char *port = std::to_string(p).c_str();
                addGaugeMetric(registry, gauge_family, "port", std::to_string(p).c_str(), "pkts_count", "total", hStat.u.query_v3.data.port.aPorts[p].rx.RMON1.pkts);
                addGaugeMetric(registry, gauge_family, "port", std::to_string(p).c_str(), "pkts_count", "drops", hStat.u.query_v3.data.port.aPorts[p].rx.RMON1.dropEvents);
                addGaugeMetric(registry, gauge_family, "port", std::to_string(p).c_str(), "pkts_count", "multicast", hStat.u.query_v3.data.port.aPorts[p].rx.RMON1.multicastPkts);
                addGaugeMetric(registry, gauge_family, "port", std::to_string(p).c_str(), "pkts_count", "vlan", hStat.u.query_v3.data.port.aPorts[p].rx.decode.pktsVlan);
            }

            for (int s = 0; s < NAPATECH_STREAMS_COUNT; s++)
            {
                // const char * stream = std::to_string(s).c_str();
                addGaugeMetric(registry, gauge_family, "stream_id", std::to_string(s).c_str(), "stream_pkts_count", "flush", hStat.u.query_v3.data.stream.streamid[s].flush.pkts);
                addGaugeMetric(registry, gauge_family, "stream_id", std::to_string(s).c_str(), "stream_pkts_count", "forward", hStat.u.query_v3.data.stream.streamid[s].forward.pkts);
                addGaugeMetric(registry, gauge_family, "stream_id", std::to_string(s).c_str(), "stream_pkts_count", "drop", hStat.u.query_v3.data.stream.streamid[s].drop.pkts);
            }

            gateway.RegisterCollectable(registry);
            auto returnCode = gateway.Push();

            // Посылаем отдельно "системную" метрику с http-кодом возврата на пуш в лейбле и счетчиком
            if (returnCode == 200)
            {
                addCounterMetric(registry_sys, counter_family, "return_code", std::to_string(returnCode).c_str());
            }
            else
            {
                std::cout << "Error while sending metrics: " << returnCode << std::endl;
                addCounterMetric(registry_sys, counter_family, "return_code", std::to_string(returnCode).c_str());
            }

            gateway_sys.RegisterCollectable(registry_sys);
            gateway_sys.Push();
        }
        else
        {
            printf("Port0 doesn't support RMON1 RX counters.\n");
        }
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