#pragma once

struct data {
    uint32_t flows_cnt;
    uint32_t limit;
    uint32_t quantum;
    uint64_t tot_pkts;
    uint64_t tot_bytes;
    uint32_t length;
    uint32_t len_bytes;
    uint32_t drops;
    uint16_t max_ecnth;
    uint16_t alpha;
    uint16_t beta;
    uint32_t burst_allowance;
    uint32_t drop_prob;
    uint32_t current_qdelay;
    uint32_t qdelay_old;
    uint64_t accu_prob;
    uint32_t avg_dq_time;
    uint32_t dq_count;
};

// int drl_update_prob(int prob);
// int drl_get_buffer(void *data, int *size);
