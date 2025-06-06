// #include "ECS.hpp"
// #include <iostream>

// void ExampleECSUsage() {
//     // Create the world (this manages all entities, components, and systems)
//     World world;
    
//     // Add systems to the world
//     auto* movementSystem = world.AddSystem<MovementSystem>(&world);
//     auto* renderSystem = world.AddSystem<RenderSystem>(&world);
//     auto* inputSystem = world.AddSystem<InputSystem>(&world);
    
//     // Create a player entity
//     EntityID player = world.CreateEntity();
    
//     // Add components to the player
//     world.AddComponent<TransformComponent>(player, 100.0f, 100.0f); // Start at position (100, 100)
//     world.AddComponent<VelocityComponent>(player, 0.0f, 0.0f);      // Start with no velocity
//     world.AddComponent<RenderComponent>(player, 1, 32.0f, 32.0f);   // Texture ID 1, 32x32 size
//     world.AddComponent<HealthComponent>(player, 100);               // 100 health points
//     world.AddComponent<InputComponent>(player);                     // Can receive input
    
//     // Create an enemy entity
//     EntityID enemy = world.CreateEntity();
//     world.AddComponent<TransformComponent>(enemy, 200.0f, 150.0f);
//     world.AddComponent<VelocityComponent>(enemy, -50.0f, 0.0f);     // Moving left
//     world.AddComponent<RenderComponent>(enemy, 2, 24.0f, 24.0f);
//     world.AddComponent<HealthComponent>(enemy, 50);
    
//     // Create a static decoration entity (no velocity, just render)
//     EntityID decoration = world.CreateEntity();
//     world.AddComponent<TransformComponent>(decoration, 300.0f, 200.0f);
//     world.AddComponent<RenderComponent>(decoration, 3, 16.0f, 16.0f);
    
//     std::cout << "Created " << world.GetEntities().size() << " entities\n";
    
//     // Example of component access
//     auto* playerTransform = world.GetComponent<TransformComponent>(player);
//     if (playerTransform) {
//         std::cout << "Player position: (" << playerTransform->x << ", " << playerTransform->y << ")\n";
//     }
    
//     // Example of checking components
//     if (world.HasComponent<HealthComponent>(player)) {
//         auto* health = world.GetComponent<HealthComponent>(player);
//         std::cout << "Player health: " << health->currentHealth << "/" << health->maxHealth << "\n";
//     }
    
//     // Example of getting entities with specific components
//     auto movableEntities = world.GetEntitiesWith<TransformComponent, VelocityComponent>();
//     std::cout << "Found " << movableEntities.size() << " movable entities\n";
    
//     // Example update loop (you would call this every frame)
//     float deltaTime = 1.0f / 60.0f; // 60 FPS
    
//     // Update input first
//     world.HandleInput();
    
//     // Update systems
//     world.Update(deltaTime);
    
//     // Render
//     world.Render();
    
//     // Example of removing components
//     world.RemoveComponent<InputComponent>(enemy); // Enemy can no longer receive input
    
//     // Example of destroying entities
//     // world.DestroyEntity(decoration);
// }
