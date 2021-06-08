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

ACommand::ACommand(Player *player)
{
}

void ACommand::execute()
{
}

DCommand::DCommand(Player *player)
{
}

void DCommand::execute()
{
}

} // namespace smb
