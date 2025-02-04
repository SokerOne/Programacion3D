#include "World.h"

World* World::GetWorld()
{
   static auto world = new World();

   return world;
}

void World::AddEntity(const std::shared_ptr<Entity>& _entity)
{
   entities.push_back(_entity);

   std::shared_ptr<Camera> auxCamera = std::dynamic_pointer_cast<Camera>(_entity);

   if (auxCamera)
   {
      cameras.push_back(auxCamera);
   }

   std::shared_ptr<Light> auxLight = std::dynamic_pointer_cast<Light>(_entity);

   if (auxLight)
   {
      lights.push_back(auxLight);
   }
}

void World::RemoveEntity(const std::shared_ptr<Entity>& _entity)
{
   std::shared_ptr<Camera> auxCamera = std::dynamic_pointer_cast<Camera>(_entity);
   if (auxCamera)
   {
      cameras.remove(auxCamera);
   }

   std::shared_ptr<Light> auxLight = std::dynamic_pointer_cast<Light>(_entity);
   if (auxLight)
   {
      lights.remove(auxLight);
   }

   entities.remove(_entity);
}

std::shared_ptr<Entity>& World::GetEntity(size_t _index)
{
   auto begin = entities.begin();
   std::advance(begin, _index);

   return *begin;
}

size_t World::GetNumEntities() const
{
   return entities.size();
}

glm::vec3 World::GetAmbient()
{
   return ambient;
}

void World::SetAmbient(glm::vec3 _ambient)
{
   ambient = _ambient;
}

void World::Update(float _deltaTime)
{
   for (auto& iterator : entities)
   {
      iterator->Update(_deltaTime);
   }
}

void World::Draw()
{
   State::GetState()->lights = lights;
   State::GetState()->ambient = ambient;

   for (auto& iterator : cameras)
   {
      iterator->Prepare();
   }

   for (auto& iterator : entities)
   {
      iterator->Draw();
   }
}
