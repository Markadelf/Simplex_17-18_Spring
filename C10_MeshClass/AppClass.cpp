#include "AppClass.h"
void Application::InitVariables(void)
{
	//Make MyMesh object
	m_pMesh = new MyMesh();
	m_pMesh->GenerateCube(1.0f, C_WHITE);

	//Make MyMesh object
	m_pMesh1 = new MyMesh();
	m_pMesh1->GenerateCube(1.0f, C_WHITE);
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	static float deg = 0;
	std::vector<vector3> pixels;

	pixels.push_back(vector3(-5, 0, 0));
	pixels.push_back(vector3(-5, -1, 0));
	pixels.push_back(vector3(-5, -2, 0));

	pixels.push_back(vector3(-4, 0, 0));
	pixels.push_back(vector3(-4, 1, 0));
	
	pixels.push_back(vector3(-3, 4, 0));

	pixels.push_back(vector3(-3, 2, 0));
	pixels.push_back(vector3(-3, 1, 0));
	pixels.push_back(vector3(-3, 0, 0));
	pixels.push_back(vector3(-3, -1, 0));
	pixels.push_back(vector3(-3, -2, 0));

	pixels.push_back(vector3(-2, 3, 0));
	pixels.push_back(vector3(-2, 2, 0));
	pixels.push_back(vector3(-2, 0, 0));
	pixels.push_back(vector3(-2, -1, 0));
	pixels.push_back(vector3(-2, -3, 0));

	pixels.push_back(vector3(-1, 2, 0));
	pixels.push_back(vector3(-1, 1, 0));
	pixels.push_back(vector3(-1, 0, 0));
	pixels.push_back(vector3(-1, -1, 0));
	pixels.push_back(vector3(-1, -3, 0));

	pixels.push_back(vector3(0, 1, 0));
	pixels.push_back(vector3(0, 2, 0));
	pixels.push_back(vector3(0, 0, 0));
	pixels.push_back(vector3(0, -1, 0));

	pixels.push_back(vector3(5, 0, 0));
	pixels.push_back(vector3(5, -1, 0));
	pixels.push_back(vector3(5, -2, 0));

	pixels.push_back(vector3(4, 0, 0));
	pixels.push_back(vector3(4, 1, 0));

	pixels.push_back(vector3(3, 4, 0));

	pixels.push_back(vector3(3, 2, 0));
	pixels.push_back(vector3(3, 1, 0));
	pixels.push_back(vector3(3, 0, 0));
	pixels.push_back(vector3(3, -1, 0));
	pixels.push_back(vector3(3, -2, 0));

	pixels.push_back(vector3(2, 3, 0));
	pixels.push_back(vector3(2, 2, 0));
	pixels.push_back(vector3(2, 0, 0));
	pixels.push_back(vector3(2, -1, 0));
	pixels.push_back(vector3(2, -3, 0));

	pixels.push_back(vector3(1, 2, 0));
	pixels.push_back(vector3(1, 1, 0));
	pixels.push_back(vector3(1, 0, 0));
	pixels.push_back(vector3(1, -1, 0));
	pixels.push_back(vector3(1, -3, 0));


	for (size_t i = 0; i < pixels.size(); i++)
	{
		m_pMesh1->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(deg, sin(deg), 0.0f)) * ToMatrix4(m_qArcBall) * glm::translate(pixels[i]));
	}
	deg += .1f;

	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();
	
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	if (m_pMesh != nullptr)
	{
		delete m_pMesh;
		m_pMesh = nullptr;
	}
	SafeDelete(m_pMesh1);
	//release GUI
	ShutdownGUI();
}