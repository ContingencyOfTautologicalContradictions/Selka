#pragma once
#include <vector>
#include <thread>
#include <atomic>
#include "Shader.hpp"

namespace Selka
{
    enum class State : std::uint8_t
    {
        Unassigned,
        Untouched,
        Executing,
        Finished
    };

    class [[nodiscard]] Task final
    {
        std::thread m_executor;
    public:
        std::string input, source;

        std::atomic<State> state = State::Unassigned;

        Task() = default;

        Task(Task&&);

        [[nodiscard]] auto Executor() noexcept -> std::thread&;
    };

    class [[nodiscard]] Scheduler final
    {
        std::string m_output;

        Shader m_shader;
    
        std::vector<Task> m_tasks;

        std::atomic<bool> m_finish = false;
    public:
        ~Scheduler();

        Scheduler(std::string&&, Shader);

        Scheduler(std::string&&, Shader, std::size_t);

        [[nodiscard]] auto Finish() const noexcept -> bool;

        [[nodiscard]] auto Output() const noexcept -> const std::string&;

        [[nodiscard]] auto ShaderLang() const noexcept -> Shader;

        auto Exchange(std::string&&, std::string&&) -> void;
    };
}