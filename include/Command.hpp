#pragma once

#include <functional>

namespace smb
{

    using EscCallback = std::function<void()>;
    class Command
    {
    public:
        virtual ~Command() = default;
        virtual void execute() = 0;
    };

    class EscCommand : public Command
    {
    public:
        EscCommand(EscCallback callback);
        void execute() override;
    private:
        EscCallback m_callback;
    };

    class ACommand : public Command
    {
    public:
        ACommand();
        void execute() override;
    };

    class DCommand : public Command
    {
    public:
        DCommand();
        void execute() override;
    };

}