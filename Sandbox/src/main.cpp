#include <iostream>

#include <Engine/Engine.h>
#include <Engine/Application.h>

class TestApplication : public Application {
public:
    TestApplication(const char* title, uint32_t width, uint32_t height,  glm::vec3 clearColor): Application(title, width, height, clearColor) {}
public:

    void OnUpdate() override {
       std::cout << "FPS: " << 1000.0f / Time::GetDeltaTime()  << std::endl;
       ProccessInput();
    }

    void ProccessInput()
    {

    }
};

int main()
{
   TestApplication app("Test", 800, 600, {1.0f, 1.0f, 1.0f});

   Engine e(app);
   e.Run();
}
