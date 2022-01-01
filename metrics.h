#pragma once

#include <prometheus/registry.h>
#include <prometheus/gauge.h>
#include <napatech/nt.h>

using namespace prometheus;

static void sigproc_(int) noexcept;

void processPortMetrics(const NtStatistics_t &hStat, Family<Gauge> &gauge_family, const int ports_count);
void processStreamMetrics(const NtStatistics_t &hStat, Family<Gauge> &gauge_family, const int streams_count);