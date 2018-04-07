#include "AppClass.h"
#include "MarksEntityManager.h"
using namespace Simplex;
void Application::InitVariables(void)
{
	//Set the position and target of the camera
	m_pCameraMngr->SetPositionTargetAndUp(vector3(0.0f, 3.0f, 13.0f), //Position
		vector3(0.0f, 3.0f, 12.0f),	//Target
		AXIS_Y);					//Up

	m_pLightMngr->SetPosition(vector3(0.0f, 3.0f, 13.0f), 1); //set the position of first light (0 is reserved for ambient light)

	//creeper
	MarksEntityManager::GetActive()->Add("Creeper", "Minecraft\\Creeper.obj");

	//steve
	MarksEntityManager::GetActive()->Add("Steve", "Minecraft\\Steve.obj");

	MarksEntityManager::GetActive()->Add("Cow", "Minecraft\\Cow.obj");
	MarksEntityManager::GetActive()->Add("Zombie", "Minecraft\\Zombie.obj");
	MarksEntityManager::GetActive()->Add("Pig", "Minecraft\\Pig.obj");

}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the ArcBall active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	//Set model matrix to the creeper
	matrix4 mCreeper = glm::translate(m_v3Creeper) * ToMatrix4(m_qCreeper) * ToMatrix4(m_qArcBall);
	MarksEntityManager::GetActive()->Get("Creeper")->SetModelMatrix(mCreeper);


	//Set model matrix to Steve
	matrix4 mSteve = glm::translate(vector3(2.25f, 0.0f, 0.0f)) * glm::rotate(IDENTITY_M4, -55.0f, AXIS_Z);
	MarksEntityManager::GetActive()->Get("Steve")->SetModelMatrix(mSteve);

	matrix4 mCow = glm::translate(vector3(1.55f, 1.0f, 0.0f)) * glm::rotate(IDENTITY_M4, -55.0f, AXIS_Z);
	matrix4 mPig = glm::translate(vector3(0.0f, 0.5f, -1.5f)) * glm::rotate(IDENTITY_M4, -55.0f, AXIS_Z);
	matrix4 mZombie = glm::translate(vector3(1.55f, 0.0f, -3.0f)) * glm::rotate(IDENTITY_M4, -55.0f, AXIS_Z);


	MarksEntityManager::GetActive()->Get("Cow")->SetModelMatrix(mCow);
	MarksEntityManager::GetActive()->Get("Pig")->SetModelMatrix(mPig);
	MarksEntityManager::GetActive()->Get("Zombie")->SetModelMatrix(mZombie);

	//Check collision
	bool bColliding = MarksEntityManager::GetActive()->CheckColliding();

	//Add objects to render list
	MarksEntityManager::GetActive()->AddToRenderList();
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

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
	MarksEntityManager::Release();
	//release GUI
	ShutdownGUI();
}
