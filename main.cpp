#include <prometheus/registry.h>
#include <prometheus/counter.h>
#include <prometheus/exposer.h>
#include <prometheus/gauge.h>
#include <napatech/nt.h>
#include "metrics.h"

#include <array>
#include <chrono>
#include <cstdlib>
#include <memory>
#include <string>
#include <thread>
#include <iostream>
#include <signal.h>

#if defined(__linux__) || defined(__FreeBSD__)
#include <unistd.h> // sleep()
#elif defined(WIN32) || defined(WIN64)
#include <winsock2.h> // Sleep()
#endif

using namespace prometheus;
using namespace std;

struct Data_ {
    volatile sig_atomic_t stop_flag = 0;

    Data_() noexcept {
        struct sigaction act = {};
        act.sa_handler = sigproc_;
        sigaction(SIGINT,  &act, 0);
        sigaction(SIGTERM, &act, 0);
        sigaction(SIGQUIT, &act, 0);
    }
};

static Data_ data_;

static void sigproc_(int) noexcept {
    cout << "Stop signal caught, stoppin..." << endl;
    data_.stop_flag = 1;
}

int main(int argc, char* argv[])
{
    if (argc != 4) {
        cout << "Pass 3 arguments:" << endl;
        cout << "1. Hostname and port which should be accessible by the Prometheus metrics puller" << endl;
        cout << "2. Number of Napatech ports" << endl;
        cout << "3. Number of Napatech streams" << endl;
        cout << "Example: ./napatech_stat yar-sniff-01:8080 2 32" << endl;

        return -1;
    }

    NtStatStream_t hStatStream;       // Statistics stream handle
    NtStatistics_t hStat;             // Stat handle.
    NtInfo_t hInfo;
    char errorBuffer[NT_ERRBUF_SIZE]; // Error buffer
    int status;                       // Status variable
    const string PROMETHEUS_BIND_ADDRESS = argv[1];
    const int NAPATECH_PORTS_COUNT = atoi(argv[2]);
    const int NAPATECH_STREAMS_COUNT = atoi(argv[3]);
    int successful_pushes = 0;
    int failed_pushes = 0;
    
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
    Exposer exposer{PROMETHEUS_BIND_ADDRESS};
    auto registry = std::make_shared<Registry>();

    auto &gauge_family = BuildGauge()
                        .Name("napatech_stat")
                        .Help("Napatech statistics")
                        .Register(*registry);

    // ask the exposer to scrape the registry on incoming HTTP requests
    exposer.RegisterCollectable(registry);

    hStat.cmd = NT_STATISTICS_READ_CMD_QUERY_V3;
    hStat.u.query_v3.poll = 1;  // The the current counters
    hStat.u.query_v3.clear = 0; // Do not clear statistics

    while (data_.stop_flag != 1)
    {
        if ((status = NT_StatRead(hStatStream, &hStat)) != NT_SUCCESS)
        {
            // Get the status code as text
            NT_ExplainError(status, errorBuffer, sizeof(errorBuffer));
            fprintf(stderr, "NT_StatRead() failed: %s\n", errorBuffer);
            return -1;
        }

        if (hStat.u.query_v3.data.port.aPorts[0].rx.valid.RMON1)
        {
            processPortMetrics(hStat, gauge_family, NAPATECH_PORTS_COUNT);
            processStreamMetrics(hStat, gauge_family, NAPATECH_STREAMS_COUNT);
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