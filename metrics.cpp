#include <prometheus/registry.h>
#include <prometheus/gauge.h>
#include <napatech/nt.h>

using namespace prometheus;

void processPortMetrics(const NtStatistics_t &hStat, Family<Gauge> &gauge_family, const int ports_count)
{
    for (int p = 0; p < ports_count; p++)
    {
        const std::string port = std::to_string(p).c_str();

        auto &pkts_count_total = gauge_family.Add({{"pkts_count", "total"}, {"port", port}});
        auto &pkts_count_drop = gauge_family.Add({{"pkts_count", "drop"}, {"port", port}});
        auto &pkts_count_multicast = gauge_family.Add({{"pkts_count", "multicast"}, {"port", port}});
        auto &pkts_count_vlan = gauge_family.Add({{"pkts_count", "vlan"}, {"port", port}});
        auto &bytes_count_total = gauge_family.Add({{"bytes_count", "total"}, {"port", port}});

        pkts_count_total.Set(hStat.u.query_v3.data.port.aPorts[p].rx.RMON1.pkts);
        pkts_count_drop.Set(hStat.u.query_v3.data.port.aPorts[p].rx.RMON1.dropEvents);
        pkts_count_multicast.Set(hStat.u.query_v3.data.port.aPorts[p].rx.RMON1.multicastPkts);
        pkts_count_vlan.Set(hStat.u.query_v3.data.port.aPorts[p].rx.decode.pktsVlan);
        bytes_count_total.Set(hStat.u.query_v3.data.port.aPorts[p].rx.RMON1.octets);
    }
}

void processStreamMetrics(const NtStatistics_t &hStat, Family<Gauge> &gauge_family, const int streams_count)
{
    for (int s = 0; s < streams_count; s++) {
        const std::string stream_id = std::to_string(s).c_str();

        auto &pkts_count_forward = gauge_family.Add({{"pkts_count", "forward"}, {"stream_id", stream_id}});
        auto &pkts_count_drop = gauge_family.Add({{"pkts_count", "drop"}, {"stream_id", stream_id}});
        auto &bytes_count_total = gauge_family.Add({{"bytes_count", "forward"}, {"stream_id", stream_id}});
        auto &bytes_count_drop = gauge_family.Add({{"bytes_count", "drop"}, {"stream_id", stream_id}});

        pkts_count_forward.Set(hStat.u.query_v3.data.stream.streamid[s].forward.pkts);
        pkts_count_drop.Set(hStat.u.query_v3.data.stream.streamid[s].drop.pkts);
        bytes_count_total.Set(hStat.u.query_v3.data.stream.streamid[s].forward.octets);
        bytes_count_drop.Set(hStat.u.query_v3.data.stream.streamid[s].drop.octets);
    }
}