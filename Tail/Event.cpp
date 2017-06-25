#include "Event.h"
#include "Entity.h"

void Enter::Execute(Entity* entity)
{
    entity->Enter();
}

void Exit::Execute(Entity* entity)
{
    entity->Exit();
}

void Idle::Execute(Entity* entity)
{
    entity->Idling();
}

void AttackEvent::Execute(Entity* entity)
{
    entity->Attack();
}

void DamageEvent::Execute(Entity* entity)
{
    entity->TakeDamage();
}

void DeathEvent::Execute(Entity* entity)
{
    entity->Die();
}

void MoveEvent::Execute(Entity* entity)
{
    entity->Move();
}