#include "Engine.h"
#include "Application.h"
#include "Window.h"

#include <iostream>

Engine::Engine(Application& app)
  : m_Window(nullptr), m_App(&app)
{
  
}


void Engine::Run()
{
  
  m_Window = new Window(m_App->GetWidth(), m_App->GetHeight(), m_App->GetTitle()); 

  m_Window->SetClearColor(m_App->GetClearColor());

  m_App->SetWindow(m_Window);

  m_App->OnStart();

  while (!m_Window->ShouldClose()) {
    Time::UpdateDeltaTime();

    m_Window->BeginFrame();

    m_App->OnUpdate();

    m_Window->EndFrame();
  }

  m_App->OnExit();
}
