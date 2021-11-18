/* mbed Microcontroller Library
 * Copyright (c) 2018 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef STATS_REPORT_H
#define STATS_REPORT
#define TRACE_GROUP "rept"

#include "mbed.h"
#include "mbed_trace.h"
#include "rtx_os.h"

/**
 *  System Reporting library. Provides runtime information on device:
 *      - CPU sleep, idle, and wake times
 *      - Heap and stack usage
 *      - Thread information
 *      - Static system information
 */
class SystemReport {
private:
public:
    /**
     * @brief Construct a new System Report object
     *
     */
    SystemReport() {}

    ~SystemReport(void) {}
    /**
     * @brief Collect the static system information
     *
     */
    void report_system_information()
    {
        static mbed_stats_sys_t _sys_stats;
        mbed_stats_sys_get(&_sys_stats);
        string strcompiler = "";
        switch (_sys_stats.compiler_id) {
            case ARM:
                strcompiler = "ARM";
                break;
            case GCC_ARM:
                strcompiler = "GCC_ARM";
                break;
            case IAR:
                strcompiler = "IAR";
                break;
            default:
                strcompiler = "--";
                break;
        }
        tr_info("========== SYSTEM INFO  ===========");
        tr_info("Mbed OS Version : %ld", _sys_stats.os_version);
        tr_info("CPU ID          : 0x%lx", _sys_stats.cpu_id);
        tr_info("Compiler        : %s", strcompiler.c_str());
        tr_info("Compiler Version: %ld", _sys_stats.compiler_version);

        for (int i = 0; i < MBED_MAX_MEM_REGIONS; i++) {
            if (_sys_stats.ram_size[i] != 0) {
                tr_info("RAM%d: Start 0x%8lx Size: 0x%lx", i, _sys_stats.ram_start[i], _sys_stats.ram_size[i]);
            }
        }
        for (int i = 0; i < MBED_MAX_MEM_REGIONS; i++) {
            if (_sys_stats.rom_size[i] != 0) {
                tr_info("ROM%d: Start 0x%8lx Size: 0x%lx", i, _sys_stats.rom_start[i], _sys_stats.rom_size[i]);
            }
        }
    }

    /**
     *  Report on each Mbed OS Platform stats API
     */
    void report_state(void)
    {
        static std::chrono::system_clock::time_point report_elapsed = std::chrono::system_clock::now();
        SystemReport::report_cpu_stats(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - report_elapsed).count());
        SystemReport::report_heap_stats();
        SystemReport::report_thread_stats();

        // Clear next line to separate subsequent report logs
        report_elapsed = std::chrono::system_clock::now();
    }

private:
    /**
     *  Report CPU idle and awake time in terms of percentage
     */
    void report_cpu_stats(double elapsed_ms)
    {
#if MBED_CPU_STATS_ENABLED
        static mbed_stats_cpu_t _cpu_stats;
        static uint64_t         prev_idle_time = 0;
        tr_info("============ CPU STATS ============");

        // Collect and print cpu stats
        mbed_stats_cpu_get(&_cpu_stats);

        uint64_t diff = (_cpu_stats.idle_time - prev_idle_time);
        uint8_t  idle = (uint8_t)((diff * 100.0) / (elapsed_ms * 1000.0));
        if (idle > 100) {
            idle = 0;
        }
        prev_idle_time = _cpu_stats.idle_time;

        tr_info("Idle: %d%% Usage: %d%%", idle, 100 - idle);
#endif
    }

    /**
     *  Report current heap stats. Current heap refers to the current amount of
     *  allocated heap. Max heap refers to the highest amount of heap allocated
     *  since reset.
     */
    void report_heap_stats(void)
    {
#if MBED_HEAP_STATS_ENABLED
        static mbed_stats_heap_t _heap_stats;
        tr_info("=========== HEAP STATS ============");

        // Collect and print heap stats
        mbed_stats_heap_get(&_heap_stats);

        tr_info("Current heap : %lu", _heap_stats.current_size);
        tr_info("Max heap size: %lu", _heap_stats.max_size);
#endif
    }

    /**
     *  Report active thread stats
     */
    void report_thread_stats(void)
    {
#if MBED_THREAD_STATS_ENABLED
        static mbed_stats_thread_t *_thread_stats = new mbed_stats_thread_t[MBED_CONF_MYPLATFORM_SYSTEMREPORT_OUTPUT_THREAD_TEXT];
        tr_info("=========== THREAD STATS ==========");
        int count = mbed_stats_thread_get_each(_thread_stats, MBED_CONF_MYPLATFORM_SYSTEMREPORT_OUTPUT_THREAD_TEXT);
        for (int i = 0; i < count; i++) {
            tr_info("[0x%lx] %s", _thread_stats[i].id, _thread_stats[i].name);
            tr_info("    Priority   : %ld", _thread_stats[i].priority);
            tr_info("    State      : %s", this->strState(_thread_stats[i].state).c_str());
            tr_info("    Stack Size : %ld / %ld", (_thread_stats[i].stack_size - _thread_stats[i].stack_space), _thread_stats[i].stack_size);
        }
#endif
    }
    string strState(uint32_t state)
    {
        switch (state) {
            case osRtxThreadInactive:
                return "Inactive";
                break;
            case osRtxThreadReady:
                return "Ready";
                break;
            case osRtxThreadRunning:
                return "ThreadRunning";
                break;
            case osRtxThreadBlocked:
                return "Blocked";
                break;
            case osRtxThreadTerminated:
                return "Terminated";
                break;
            case osRtxThreadWaitingDelay:
                return "ThreadWaitingDelay";
                break;
            case osRtxThreadWaitingJoin:
                return "ThreadWaitingJoin";
                break;
            case osRtxThreadWaitingThreadFlags:
                return "ThreadWaitingThreadFlags";
                break;
            case osRtxThreadWaitingEventFlags:
                return "ThreadWaitingEventFlags";
                break;
            case osRtxThreadWaitingMutex:
                return "ThreadWaitingMutex";
                break;
            case osRtxThreadWaitingSemaphore:
                return "ThreadWaitingSemaphore";
                break;
            case osRtxThreadWaitingMemoryPool:
                return "ThreadWaitingMemoryPool";
                break;
            case osRtxThreadWaitingMessageGet:
                return "ThreadWaitingMessageGet";
                break;
            case osRtxThreadWaitingMessagePut:
                return "ThreadWaitingMessagePut";
                break;
            default:
                return "--";
                break;
        }
    }
};

#undef TRACE_GROUP
#endif // STATS_REPORT_H
