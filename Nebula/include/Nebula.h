#pragma once

/*
	FOR USE OF NEBULA APPLICATIONS ONLY

	When linking projects to the Nebula
	engine please use this file

	The real include class is located in
	"src/Nebula.h"
*/

//----API DEFINES-----
#include "Nebula/Core/API.h"
//--------------------

//----LAYERS---------
#include "Nebula/Core/Layer.h"
#include "Nebula/imgui/ImGui_Layer.h"
//--------------------

//-----MATHS----------
#include "Nebula/Maths/Maths.h"
//--------------------

//----RENDERER--------
#include "Nebula/Renderer/Shader.h"
#include "Nebula/Renderer/Texture.h"
#include "Nebula/renderer/Camera_Controller.h"
#include "Nebula/Renderer/FrameBuffer.h"

//--Buffers
#include "Nebula/Renderer/Buffer.h"
#include "Nebula/Renderer/Vertex_Array.h"

//--Renderers
#include "Nebula/Renderer/Renderer.h"
#include "Nebula/Renderer/Renderer2D.h"
#include "Nebula/Renderer/Render_Command.h"
//--------------------

//----EVENTS---------
#include "Nebula/Core/Input.h"
#include "Nebula/Events/Event.h"
#include "Nebula/Events/Key_Event.h"
#include "Nebula/Events/Mouse_Event.h"
#include "Nebula/Events/Window_Event.h"
//--------------------

//----Application-----
#include "Nebula/Core/Time.h"
#include "Nebula/Core/Window.h"

#include "Nebula/Core/Application.h"
//--------------------