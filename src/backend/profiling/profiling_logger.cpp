#include "backend/profiling/profiling_logger.hpp"

#include <iostream>

namespace profiling {

void FrameLogger::logIfDue(const CpuProfiler &cpu,
                           const VkGpuProfiler &gpu) noexcept {
  if (m_period == 0) {
    return;
  }

  ++m_frameCounter;
  if ((m_frameCounter % m_period) != 0ULL) {
    return;
  }

  const auto &st = cpu.last();

  std::cerr << "[Profiler] CPU ms: frame="
            << st.ms[(size_t)CpuProfiler::Stat::FrameTotal]
            << " acquire=" << st.ms[(size_t)CpuProfiler::Stat::Acquire]
            << " waitForFence="
            << st.ms[(size_t)CpuProfiler::Stat::WaitForFence]
            << " ubo=" << st.ms[(size_t)CpuProfiler::Stat::UpdatePerFrameUBO]
            << " record="
            << st.ms[(size_t)CpuProfiler::Stat::RecordCmd]
            // NOTE: if queueSubmit is large its likely artifical wait time
            // for vsync from FIFO present mode in swapchain
            << " queueSubmit=" << st.ms[(size_t)CpuProfiler::Stat::QueueSubmit]
            << " queuePresent="
            << st.ms[(size_t)CpuProfiler::Stat::QueuePresent]
            << " other=" << st.ms[(size_t)CpuProfiler::Stat::Other] << "\n"
            << " draws=" << st.drawCalls << " triangles=" << st.triangles
            << " pipeBinds=" << st.pipelineBinds
            << " descBinds=" << st.descriptorBinds << "\n";

  // Note: Most of other is likely from the vkWaitForFence in commands on
  // submit immediate. I didn't bother logging this since its a pain to
  // pass since mesh_store is the one who calls the uploaders who then
  // call submit immediate so I would have to pass profiler a lot. But it
  // doesn't matter since eventually submit Immediate will be removed and
  // we won't have blocking anymore

  const auto &gst = gpu.last();
  if (gst.valid) {
    std::cerr << " gpuFrame=" << gst.frameMs
              << " gpuMainPass=" << gst.mainPassMs
              << " gpuIdleGap=" << gst.idleGapMs;
  }

  std::cerr << "\n";
}

#ifndef NDEBUG
void emit(Event e, double ms) noexcept {
  std::cerr << "[Event] " << name(e) << " ms=" << ms << "\n";
}
#endif

} // namespace profiling
