#pragma once

#include "Player.hpp"
#include <functional>
#include <memory>

namespace smb
{

using EscCallback = std::function<void()>;
class Command
{
  public:
    virtual ~Command() = default;
    virtual void execute(GameObject &gameObject) = 0;
};

class EscCommand : public Command
{
  public:
    EscCommand(EscCallback callback);
    void execute(GameObject &gameObject) override;

  private:
    EscCallback m_callback;
};

class ACommand : public Command
{
  public:
    ACommand();
    void execute(GameObject &gameObject) override;
};

class DCommand : public Command
{
  public:
    DCommand();
    void execute(GameObject &gameObject) override;
};

} // namespace smb