#include "Command.hpp"

namespace smb
{

EscCommand::EscCommand(EscCallback callback) : m_callback{callback}
{
}

void EscCommand::execute()
{
    m_callback();
}

ACommand::ACommand()
{
}

void ACommand::execute()
{
}

DCommand::DCommand()
{
}

void DCommand::execute()
{
}

} // namespace smb
