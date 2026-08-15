/**
 * @file chorusim_pubruntime.h
 * @brief ChoruSim Public Header
 * @author zwzhong (zwzhong23@m.fudan.edu.cn)
 * @version 0.1.0
 * @date 2026-08-15
 *
 * @copyright Copyright (c) 2026 Zewei Zhong
 *
 * @note
 * This header defines the public interface of the ChoruSim runtime library.
 *
 * @par Binary-Only Distribution
 * Due to ongoing collaborative development and industrial partnership
 * agreements, the full source code of the runtime library is not publicly
 * disclosed. Only the precompiled binary library (shared or static) is
 * provided, along with this public header for integration purposes.
 *
 * @par Paper Publication
 * The methodology and core algorithms of ChoruSim have been accepted
 * for publication in a peer-reviewed venue. To support reproducibility
 * and further research, this public API header is released to allow
 * researchers and developers to interface with the binary implementation
 * using the documented interfaces defined herein.
 *
 * @par Usage Restriction
 * External users and collaborators are granted the right to use the
 * binary library solely through the interfaces declared in this header.
 * Reverse engineering, decompilation, or disassembly of the binary
 * is strictly prohibited unless explicitly permitted by separate
 * licensing terms.
 *
 * @par Contact
 * For collaboration, licensing, or technical inquiries, please contact
 * the author via the email address above.
 */
#pragma once
#include <cstdint>
#include <memory>
#include <string>

namespace ChoruSim::simulator {

// forward declaration
class ZKSimulationRuntime;

class ChoruSim_PubRuntime {
public:
    ChoruSim_PubRuntime();
    ~ChoruSim_PubRuntime();

    // Non‑copyable and non‑movable
    ChoruSim_PubRuntime(const ChoruSim_PubRuntime &) = delete;
    ChoruSim_PubRuntime &operator=(const ChoruSim_PubRuntime &) = delete;
    ChoruSim_PubRuntime(ChoruSim_PubRuntime &&) = delete;
    ChoruSim_PubRuntime &operator=(ChoruSim_PubRuntime &&) = delete;

    /// @brief Initialize the runtime with model and waveform file paths.
    void init(const std::string &modelBaseFile, const std::string &dumpBaseFile);

    /// @brief Set the random seed
    void setRandomSeed(unsigned int seed);

    /// @brief Apply random stimuli to all primary inputs (PIs).
    void randomStimuli();

    /// @brief Set a single‑bit primary input (PI) to the specified value.
    void setValue(const std::string &sigName, uint8_t value);

    /// @brief Fetch primary outputs (POs) from GPU for runtime verification (uses PCIe bandwidth).
    void fetchPo();

    /// @brief Retrieve the value of a signal. Must be called after `fetchPo()` for correct results.
    int getValue(const std::string &sigName);

    /// @brief Trigger one simulation evaluation cycle.
    void eval();

    /// @brief Save waveform for the current tick with the given timestamp.
    void dump(uint64_t timeStamp);

    /**
     * @brief Advanced feature: simulate a single clock edge transition.
     *
     * Usage example:
     *   dut.setValue("clk", 0);
     *   dut.forwardClk();
     *   dut.setValue("clk", 1);
     *   dut.eval();
     *   dut.dump(time++);
     */
    void forwardClk();

    /// @brief save circuit snapshot to file
    void saveSnapShot(const std::string &fileName);

    /// @brief load circuit snapshot from file
    void loadSnapShot(const std::string &fileName);

private:
    /// @brief internal specific implementation
    std::unique_ptr<ZKSimulationRuntime> impl_;
};

} // namespace ChoruSim::simulator