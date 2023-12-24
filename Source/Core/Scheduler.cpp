#include "Executor.hpp"
#include "Scheduler.hpp"
#include <fstream>

namespace Selka
{
    Task::Task(Task&& other)
    {
        m_executor = std::forward<std::thread>(other.m_executor);
        source = std::forward<std::string>(other.source);
        state.store(other.state.load());
    }

    [[nodiscard]] auto Task::Executor() noexcept -> std::thread&
    {
        return m_executor;
    }

    Scheduler::~Scheduler()
    {
        m_finish = true;
        for(Task& task : m_tasks)
        {
            while(task.state == State::Executing);
            if(task.state == State::Finished)
                std::ofstream(m_output + task.input).write(task.source.c_str(),
                task.source.size());
            task.Executor().join();
        }
    }

    auto Execute(Scheduler& scheduler, Task& task) -> void
    {
        if(not scheduler.Finish())
        {
            if(task.state == State::Untouched)
            {
                task.state = State::Executing;
                Executor::Process(task.source);
                task.state = State::Finished;
            }
            Execute(scheduler, task);
        }
    }

    Scheduler::Scheduler(std::string&& output, Shader shader) : m_output(std::
    forward<std::string>(output)), m_shader(shader)
    {
        m_tasks.resize(std::thread::hardware_concurrency());
        for(Task& task : m_tasks)
            task.Executor() = std::thread(Execute, std::ref(*this), std::ref(task));
    }

    Scheduler::Scheduler(std::string&& output, Shader shader, std::size_t
    executors) : m_output(std::forward<std::string>(output)), m_shader(shader)
    {
        m_tasks.resize(executors);
        for(Task& task : m_tasks)
            task.Executor() = std::thread(Execute, std::ref(*this), std::ref(task));
    }

    auto Scheduler::Exchange(std::string&& input, std::string&& source) -> void
    {
        bool all_occupied = true;
        while(all_occupied)
            for(Task& task : m_tasks)
            {
                if(not all_occupied)
                    break;
                else
                    switch(task.state)
                    {
                        using enum State;
                        default:
                        break;
                        case Finished:
                            all_occupied = false;
                            std::swap(source, task.source);
                            task.state = State::Untouched;
                            std::ofstream(m_output + task.input).write(source.
                            c_str(), source.size());
                            task.input = std::filesystem::path(std::forward<std::string>(input)).stem();
                            task.input += ShaderLanguage(m_shader);
                        break;
                        case Unassigned:
                            all_occupied = false;
                            task.input = std::filesystem::path(std::forward<std::string>(input)).stem();
                            task.input += ShaderLanguage(m_shader);
                            task.source = std::forward<std::string>(source);
                            task.state = State::Untouched;
                        break;
                    }
            }
    }

    [[nodiscard]] auto Scheduler::Finish() const noexcept -> bool
    {
        return m_finish.load();
    }

    [[nodiscard]] auto Scheduler::Output() const noexcept -> const std::string&
    {
        return m_output;
    }

    [[nodiscard]] auto Scheduler::ShaderLang() const noexcept -> Shader
    {
        return m_shader;
    }
}